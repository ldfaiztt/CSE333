/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#include "libhw1/Assert333.h"
#include "fileparser.h"

#define ASCII_UPPER_BOUND 0x7F

// This variable is set if there is an error.
extern int errno;

// A private function for freeing a WordPositions.positions list.
static void NullWPListFree(void *payload) { }

// A private function for freeing a WordHT.
static void WordHTFree(void *payload) {
  WordPositions *pos = (WordPositions *) payload;
  FreeLinkedList(pos->positions, &NullWPListFree);
  free(pos->word);
  free(pos);
}

// A private helper function; once you've parsed out a word from the text
// file, use this helper function to add that word and its position to the
// hash table tab.
static void AddToHashtable(HashTable tab, char *word, uint64_t pos);

// A private helper function to parse a file and build up the HashTable of
// WordPosition structures.
static void LoopAndInsert(HashTable tab, char *content);

char *ReadFile(const char *filename, uint64_t *size) {
  struct stat filestat;
  char *buf;
  int result, fd;
  ssize_t numread;
  size_t left_to_read;

  // Use the stat system call to fetch a "struct stat" that describes
  // properties of the file. ("man 2 stat"). [You can assume we're on a 64-bit
  // system, with a 64-bit off_t field.]

  // STEP 1
  if (stat(filename, &filestat) == -1)
    return NULL;

  // Make sure this is a "regular file" and not a directory
  // or something else.  (use the S_ISREG macro described
  // in "man 2 stat")

  // STEP 2
  if (!S_ISREG(filestat.st_mode))
    return NULL;

  // Attempt to open the file for reading.  (man 2 open)

  // STEP 3
  fd = open(filename, O_RDONLY);
  // check if error occurred when opening the file
  if (fd == -1)
    return NULL;

  // Allocate space for the file, plus 1 extra byte to
  // NULL-terminate the string.

  // STEP 4
  buf = (char *) malloc(sizeof(char) * filestat.st_size + 1);
  // halt the program if space allocation for the buffer failed
  Assert333(buf != NULL);

  // Read in the file contents.  Use the read system call. (man 2 read.)  Be
  // sure to handle the case that (read returns -1) and errno is (either
  // EAGAIN or EINTR).  Also, note that it is not an error for read to return
  // fewer bytes than what you asked for; you'll need to put read() inside a
  // while loop, looping until you've read to the end of file or a non-
  // recoverable error.  (Read the man page for "read()" carefully, in
  // particular what the return values -1 and 0 imply.)
  left_to_read = filestat.st_size;
  numread = 0;
  while (left_to_read > 0) {
    // STEP 5
    result = read(fd, buf + numread, left_to_read);
    if (result == 0) {
      // EOF
      left_to_read = 0;
    } else if (result == -1) {
      // return NULL if a non-recoverable error happened
      if (errno != EAGAIN && errno != EINTR) {
        free(buf);
        return NULL;
      }
      // continue read the file if a recoverable error happened
      continue;
    } else {
      // update numread in order to read from the point where
      // the read stops next time if read reads fewer bytes
      // than requested
      numread += result;
      // update left_to_read to let the read knows how many
      // bytes are left to be read
      left_to_read -= result;
    }
  }

  // Great, we're done!  We hit the end of the file and we
  // read (filestat.st_size - left_to_read) bytes. Close the
  // file descriptor returned by open(), and return through the
  // "size" output parameter how many bytes we read.
  close(fd);
  *size = (uint64_t) (filestat.st_size - left_to_read);

  // Add a '\0' after the end of what we read to NULL-terminate
  // the string.
  buf[*size] = '\0';
  return buf;
}

HashTable BuildWordHT(char *filename) {
  char *filecontent;
  HashTable tab;
  uint64_t filelen, i;

  if (filename == NULL)
    return NULL;

  // Use ReadFile() to slurp in the file contents.  If the
  // file turns out to be empty (i.e., its length is 0),
  // or you couldn't read the file at all, return NULL to indicate
  // failure.

  // STEP 6
  filecontent = ReadFile(filename, &filelen);
  if (filecontent == NULL || filelen == 0)
    return NULL;

  // Verify that the file contains only ASCII text.  We won't try to index any
  // files that contain non-ASCII text; unfortunately, this means we aren't
  // Unicode friendly.
  for (i = 0; i < filelen; i++) {
    if ((filecontent[i] == '\0') ||
        ((unsigned char) filecontent[i] > ASCII_UPPER_BOUND)) {
      free(filecontent);
      return NULL;
    }
  }

  // Great!  Let's split the file up into words.  We'll allocate the hash
  // table that will store the WordPositions structures associated with each
  // word.  Since our hash table dynamically grows, we'll start with a small
  // number of buckets.
  tab = AllocateHashTable(64);

  // Loop through the file, splitting it into words and inserting a record for
  // each word.
  LoopAndInsert(tab, filecontent);

  // If we found no words, return NULL instead of a
  // zero-sized hashtable.
  if (NumElementsInHashTable(tab) == 0) {
    FreeHashTable(tab, &WordHTFree);
    tab = NULL;
  }

  // Now that we've finished parsing the document, we can free up the
  // filecontent buffer and return our built-up table.
  free(filecontent);
  filecontent = NULL;
  return tab;
}

void FreeWordHT(HashTable table) {
  FreeHashTable(table, &WordHTFree);
}

static void LoopAndInsert(HashTable tab, char *content) {
  char *curptr = content, *wordstart = content;

  // This is the interesting part of Part A!
  //
  // "content" contains a C string with the full contents
  // of the file.  You need to implement a loop that steps through the
  // file content  a character at a time, testing to see whether a
  // character is an alphabetic character or not.  If a character is
  // alphabetic, it's part of a word.  If a character is not
  // alphabetic, it's part of the boundary between words.
  // You can use the string.h "isalpha()" macro to test whether
  // a character is alphabetic or not.  ("man isalpha").
  //
  // So, for example, here's a string with the words within
  // it underlined with "=", and boundary characters underlined
  // with "+":
  //
  // The  Fox  Can't   CATCH the  Chicken.
  // ===++===++===+=+++=====+===++=======+
  //
  // As you loop through, anytime you detect the start of a
  // word, you should use the "wordstart" pointer to remember
  // where the word started.  You should also use the "tolower"
  // macro to convert alphabetic characters to lowercase.
  // (e.g.,  *curptr = tolower(*curptr);  ).  Finally, as
  // a hint, you can overwrite boundary characters with '\0' (null
  // terminators) in place in the buffer to create valid C
  // strings out of each parsed word.
  //
  // Each time you find a word that you want to record in
  // the hashtable, call the AddToHashtable() helper
  // function with appropriate arguments, e.g.,
  //
  //    AddToHashtable(tab, wordstart, pos);
  //

  while (1) {
    // STEP 7
    if (*curptr == '\0') {
      break;
    } else if (isalpha(*curptr) != 0) {
      *curptr = tolower(*curptr);
    } else {
      *curptr = '\0';
      // if the current pointer points to a non-empty word,
      // add the word and its position to hashtable
      if (curptr != content && isalpha(*(curptr - 1)) != 0)
        AddToHashtable(tab, wordstart, (wordstart - content));
      wordstart = curptr + 1;
    }
    curptr++;
  }
}


static void AddToHashtable(HashTable tab, char *word, uint64_t pos) {
  uint64_t hashval;
  int retval;
  HTKeyValue kv;

  // Hash the string.
  hashval = FNVHash64((unsigned char *) word, strlen(word));

  // Have we already encountered this word within this file?
  // If so, it's already in the hashtable.
  retval = LookupHashTable(tab, hashval, &kv);
  if (retval == 1) {
    // Yes; we just need to add a position in using AppendLinkedList().  Note
    // how we're casting the uint64_t position variable to a (void *) to store
    // it in the linked list payload without needing to malloc space for it.
    // Ugly, but it works!
    WordPositions *wp = (WordPositions *) kv.value;
    retval = AppendLinkedList(wp->positions, (void *) ((intptr_t) pos));
    Assert333(retval != 0);
  } else {
    // No; this is the first time we've seen this word.  Allocate and prepare
    // a new WordPositions structure, and append the new position to its list
    // using a similar ugly hack as right above.
    WordPositions *wp;
    char *newstr;
    HTKeyValue oldkv;

    // STEP 8
    // allocate space for WordPositions
    wp = (WordPositions *) malloc(sizeof(WordPositions));
    Assert333(wp != NULL);

    // allocate space for string in WordPositions
    newstr = (char *) malloc(strlen(word) + 1);
    Assert333(newstr != NULL);

    // copy the characters from the argument "word" passed in
    strncpy(newstr, word, strlen(word) + 1);
    wp->word = newstr;

    // allocate space for linkedlist (positions in WordPositions)
    wp->positions = AllocateLinkedList();
    Assert333(wp->positions != NULL);

    // append the position of the string to the positions list
    retval = AppendLinkedList(wp->positions, (void *) ((intptr_t) pos));
    Assert333(retval != 0);

    // insert the key (hash value of the string) and
    // value (that string's WordPositions) into hashtable
    kv.key = hashval;
    kv.value = (void *) wp;
    retval = InsertHashTable(tab, kv, &oldkv);
    Assert333(retval == 1);
  }
}
