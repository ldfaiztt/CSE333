/*Copyright 2013 Chuong Dao*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NUM_ARGS 2

// function check if a given strings is a palindrome
// returns 1 if a given string is a palindrome
// returns 0 otherwise
int isPalindrome(char *strings, uint64_t size);

// shows usage information
void Usage();

int main(int argc, char **argv) {

    // validate number of arguments
    if (argc != NUM_ARGS) {
        Usage();
        return EXIT_FAILURE;
    }

    // get the size of the strings
    uint64_t size = strlen(argv[1]);

    // output the result
    if (isPalindrome(argv[1], size)) {
        printf("The string \"%s\" is a palindrome\n", argv[1]);
    } else {
        printf("The string \"%s\" is NOT a palindrome\n", argv[1]);
    }
    // success
    return EXIT_SUCCESS;
}


void Usage() {
    printf("palindrome [string]\n");
}

int isPalindrome(char *strings, uint64_t size) {
    // empty string  and sindgle character strings are palindromes
    if (size == 0 || size == 1) {
        return 1;
    }

    // general case
    // pointers to the end and begining of the strings
    char *begin = strings;
    char *end = strings + (size - 1);

    // traverse the strings using these pointers to check
    // if a strings are a palindrome or not
    for (int i = 0; i < (size / 2); i++) {
        // there is a mismatch => not a palindrome
      if (*begin != *end) {
         return 0;
      } 
      else {
            // advance the begin pointer forward
            // move the end poitner backward
            begin++;
            end--;
        }
    }

    // no mismatch => the given string is a palindrome
    return 1;
}


