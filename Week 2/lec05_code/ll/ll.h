// A "Node" is the structure we use as a node in a linked
// list.
typedef struct node_st {
  void *element;         // the payload of the node
  struct node_st *next;  // the next node in the list, or NULL if at tail
} Node;

// Allocate and push a new node onto the head of the linked list.
// Deliberately crashes with a failed assertion if there is
// an out-of-memory error.
//
// Arguments:
//
// - head:    the current head of the linked list
// - element: the payload of the new node
//
//
// Returns:
//
// - the new head of the linked list
Node *Push(Node *head, void *element);

// Pop and deallocate the node that is at the head of the
// linked list.
//
// Arguments:
//
// - old_head: the current head of the linked list
//
// - new_head: a return parameter through which the new
//   head of the linked list is returned if the pop
//   operation was successful.
//
// Returns:
//
// - the payload (i.e., element field) of the node that
//   was popped and deallocated, or NULL if the linked
//   was empty (i.e., old_head was NULL).  If the linked
//   list was null.
void *Pop(Node *old_head, Node **new_head);
