/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is the solution to an exercise problem posed during
 *  one of the UW CSE 333 lectures (333exercises).
 *
 *  333exercises is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exercises is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333exercises.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ll.h"

// Lecture 5, exercise 1

// Extend the linked list program we covered in class:
//  - implement a program that builds a list of lists.
//    i.e., it builds a linked list, but each element in the
//    list is a (different) linked list

int main(int argc, char **argv) {
  Node *main_list = NULL;
  Node *embedded_list_1 = NULL, *embedded_list_2 = NULL;
  
  // Build up the embedded lists
  {
    // dynamically allocate some strings using strdup
    char *string1 = strdup("Hi!!");
    char *string2 = strdup("second stringer");
    char *string3 = strdup("supercalifragilisticexpialadocious");
    char *string4 = strdup("");

    // build up embedded list 1
    embedded_list_1 = Push(embedded_list_1, string1);
    embedded_list_1 = Push(embedded_list_1, string2);

    // build up embedded list 2
    embedded_list_2 = Push(embedded_list_2, string3);
    embedded_list_2 = Push(embedded_list_2, string4);
  }

  // Build up the list of lists
  {
    // Note that the main list's elements (the pointers
    // to the embedded lists) are stack-allocated via
    // variables embedded_list_1 and embedded_list_2.
    // That means when it's time to clean up the main list,
    // we don't need to do any free()'ing of its elements.
    main_list = Push(main_list, embedded_list_1);
    main_list = Push(main_list, embedded_list_2);
  }

  // Traverse the list of lists
  {
    Node *tmp = main_list;
    int  maincount = 0;

    while (tmp != NULL) {
      Node *embed = (Node *) tmp->element;
      int embedcount = 0;

      printf("Main list[%d]:\n", maincount++);
      // traverse the embedded list
      while (embed != NULL) {
        printf(" embed[%d]: '%s'\n",
               embedcount++,
               (char *) embed->element);
        embed = embed->next;
      }
      tmp = tmp->next;
    }
  }

  // Free up everything.
  {
    while (main_list != NULL) {
      Node *embed = (Node *) Pop(main_list, &main_list);

      while (embed != NULL) {
        char *to_free = (char *) Pop(embed, &embed);
        free(to_free);
      }
    }
  }

  return 0;
}
