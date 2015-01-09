/****************************************************************************
 * speller.c
 *
 * MPATE-GE 2618
 * Problem Set 5
 * 
 * Implements a spell-checker. 
 * Original Code by D. Malan, slight modifications by M. Farbood.
 ***************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/times.h>

#include "dictionary.h"

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
const int MAX_WORD_LEN = 45;

// default dictionary
char *WORDS = "words.txt";

// prototype
double calculate(struct rusage *, struct rusage *);


int main(int argc, char *argv[])
{
    // check for correct number of args
    if (argc != 2 && argc != 3) {
        printf("Usage: speller [dict] file\n");
        return 1;
    }

    // structs for timing data
    struct rusage before, after;

    // benchmarks
    double startup = 0., lookups = 0., sizing = 0.;

    // determine dictionary to use
    char *dict = (argc == 3) ? argv[1] : WORDS;

    // load dictionary
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dict);
    getrusage(RUSAGE_SELF, &after);

    // abort if dictionary not loaded
    if (!loaded) {
        printf("Could not load %s.\n", dict);
        return 2;
    }

    // calculate time to load dictionary
    startup = calculate(&before, &after);

    // try to open file 
    char * file = (argc == 3) ? argv[2] : argv[1];
    FILE * fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Could not open %s.\n", file);
        return 3;
    }

    // prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[MAX_WORD_LEN+1];
    bool isLastWord = false; // necessary if last word not followed by a return or space

    // spell-check each word in file
    for (int c = fgetc(fp); c != EOF || !isLastWord; c = fgetc(fp)) {
        if (c == EOF) {
            isLastWord = true;
        }
        // allow alphabetical characters and apostrophes (for possessives)
        if (isalpha(c) || (c == '\'' && index > 0)) {
            // append character to word
            word[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            if (index > MAX_WORD_LEN) {
                // consume remainder of string
                while ((c = fgetc(fp)) != EOF && isalpha(c));

                // prepare for new word
                index = 0;
            }
        }  // ignore words with numbers (like MS Word)
        else if (isdigit(c)) {
            // consume remainder of string until next non-alphanumeric character
            while ((c = fgetc(fp)) != EOF && isalnum(c));

            // prepare for new word
            index = 0;
        } // we must have found a whole word
        else if (index > 0) {
            // terminate current word
            word[index] = '\0';

            // update counter
            words++;

            // check word's spelling
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // update benchmark
            lookups += calculate(&before, &after);

            // print word if misspelled
            if (misspelled) {
                printf("%s\n", word);
                misspellings++;
            }

            // prepare for next word
            index = 0;
        }
    }

    // check for error
    if (ferror(fp)) {
        fclose(fp);
        printf("Error reading %s.\n", file);
        return 4;
    }

    // close file
    fclose(fp);

    // determine dictionary's size
    getrusage(RUSAGE_SELF, &before);
    int n = size();
    getrusage(RUSAGE_SELF, &after);

    // calculate time to determine dictionary's size
    sizing = calculate(&before, &after);

    // report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN FILE:        %d\n", words);
    printf("STARTUP TIME:         %f\n", startup);
    printf("LOOKUP TIME:          %f\n", lookups);
    printf("SIZING TIME:          %f\n", sizing);
    printf("TOTAL TIME:           %f\n\n", startup + lookups + sizing);

    cleanUp();
    return 0;
}


/* Returns number of seconds between b and a. */
double calculate(struct rusage *b, struct rusage *a)
{
    if (b == NULL || a == NULL)
        return 0;
    else
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                        (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                    ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                     (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) 
                / 1000000.);
}
