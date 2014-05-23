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

#ifndef _BST_H_
#define _BST_H_

// A "TreeNode" is the structure we use as a node in a BST.
typedef struct TreeNode {
  void *element;           // the payload of the node
  struct TreeNode *left;   // the left child, or NULL
  struct TreeNode *right;  // the right child, or NULL
} TreeNode;

// Customer has to provide us with a comparator function.
typedef int (*TreeComparator)(void *element1, void *element2);

// Push a new element into the tree.
//
// Arguments:
//
// - root:    the root of the tree to insert into
// - element: the element to push into the tree 
// - f: the comparator function to use to compare nodes
// - newroot: an output parameter with the new root, if appropriate.
//
// Returns:
//
// - 1 if the element was added
// - 0 if we ran out of memory
// - -1 if the element was already in the tree, in which case
//   nothing is malloc'ed and the element is not re-added.
//   (The element already being in the tree implies the
//   comparator returned 0 for some element.)
int Insert(TreeNode *root, void *element,
           TreeComparator f, TreeNode **newroot);

// Find an element in the tree.
//
// Arguments:
//
// - root: the root of the tree
// - findme: the element to find
// - f: the comparator function to use to compare nodes
// - element: an output parameter through which the found
//   payload is returned
//
// Returns:
//
// - 1 if a matching element was found
// - 0 otherwise
int Lookup(TreeNode *root, void *findme, TreeComparator f,
           void **element);

#endif  // _BST_H_
