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

#include <stdio.h>    // for NULL
#include <stdlib.h>   // for malloc(), free()
#include <assert.h>   // for assert()

#include "bst.h"

int Insert(TreeNode *root, void *element,
           TreeComparator f, TreeNode **newroot) {
  int compvalue;

  if (root == NULL) {
    // we went past a leaf, so do the insert and
    // update the parent via newroot.
    TreeNode *newnode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newnode == NULL)
      return 0;
    newnode->element = element;
    newnode->left = newnode->right = NULL;
    *newroot = newnode;
    return 1;
  }

  // not at root, so traverse downwards
  compvalue = f(element, root->element);
  if (compvalue > 0) {
    return Insert(root->right, element, f, &(root->right));
  } else if (compvalue < 0) {
    return Insert(root->left, element, f, &(root->left));
  } else {
    return -1;
  }

}

int Lookup(TreeNode *root, void *findme, TreeComparator f,
           void **element) {
  int compvalue;

  // see if we went past a leaf
  if (root == NULL)
    return 0;

  compvalue = f(findme, root->element);
  if (compvalue == 0) {
    // found it!
    *element = root->element;
    return 1;
  }

  // traverse down
  if (compvalue > 0)
    return Lookup(root->right, findme, f, element);
  
  return Lookup(root->left, findme, f, element);
}
