# Spell-Checker
Program in C that’s designed using a hash table to spell-check a file after loading a 173,531-word dictionary from disk into memory.There are three different files that are used to accomplish this task speller.c, hash.c, and dictionary.c


Speller.c is the file that does the spell checking component of the program. After checking for the correct number of arguments, the function loads in the dictionary and calculates the time in order to do that. After loading the dictionary and opening the dictionary file, there is a for loop which checks each character in the file until the it reaches the EOF. Then there is a check to only add characters to the array word if it is alphabetical character or an apostrophes and then the integer index is incremented. It also checks to make sure if the word entered is longer than the Max word length it takes in the rest of the string and then turns the index to 0 in order to count for the next word. The main function is also making sure to ignore words with numbers by using isdigit© and only appending the things that are alphabetical characters. When the index number is not at a reset point then a new word has been found so the word counter is updated and there is a null terminating character added to the word array at the position of index. 

In hash.c
