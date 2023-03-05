/********************************************************************************* 
* Anya Rajan, arajan2
* 2022 Spring CSE101 PA1 
* List.c 
* List.c to define List ADT functions 
***********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "List.h"

// structs ----------------------------------------------------------------------- 

// private NodeObj type
typedef struct NodeObj {
	void *data;
	Node previous;
	Node next;
} NodeObj;

// private ListObj
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors Node --------------------------------------------------

// newNode()
// Returns reference to a new Node object. Initializes data, previous, and next fields.
Node newNode (void *data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->previous = NULL;
	N->next = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode (Node* pN) {
	if (pN != NULL && *pN != NULL) {
		// free(pN->next);
		// free(pN->previous);
		// pN->next = NULL;
		// pN->previous = NULL;
		free(*pN);
		*pN = NULL;
	}
}
// Constructors-Destructors List ---------------------------------------------------

// newList()
// Returns reference to new List object.
List newList (void) {
	// List L;
	List L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList (List *pL) {
	// need to figure this function out
	if (*pL == NULL || pL == NULL) {
		printf("List Error: calling freeList on NULL List reference\n");
		exit(EXIT_FAILURE);
	}	
	// Node x;
	moveFront(*pL);
	while (length(*pL) != 0) {
		deleteFront(*pL);
	} 
	free(*pL);
	*pL = NULL;
	
}

// Access functions -----------------------------------------------------------

// length()
// returns the number of elements in L
int length (List L) {
	if (L == NULL) {
		printf("List Error: calling length() on NULL List.\n");
		exit(EXIT_FAILURE);
	}
	return(L->length);
}

// index()
// returns index of cursor element if defined, -1 otherwise
int index (List L) {
	if (L != NULL) {
		return (L->index);
	}
	else {
		return(-1);
	}
}

// front()
// returns front element of L
// Pre: length() > 0
void * front (List L) {
	if (L == NULL) {
		printf("List Error: calling front() on NULL List\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		printf("List Error: calling front() on List with no length\n");
                exit(EXIT_FAILURE);
	}
	else {
		return (L->front->data);
	}
}

// back()
// returns back element of L
// Pre: length() > 0
void * back (List L) {
	if (L == NULL) {
                printf("List Error: calling back() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) <= 0) {
		printf("List Error: calling back() on List with no length\n");
                exit(EXIT_FAILURE);
	}
	else {
		return (L->back->data);
	}
}

// get()
// returns cursor element of L
// Pre: length() > 0, index >= 0
void * get(List L) {
	if (L == NULL) {
                printf("List Error: calling get() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) <=  0) {
		printf("List Error: calling get() on List with no length\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling get() on List with undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	
	return (L->cursor->data);
	
	
}

// Manipulation procedures ------------------------------------------------------------------

// clear()
// Resets L to its original empty state
void clear (List L) {
	moveFront(L);
        while (length(L) != 0) {
                deleteFront(L);
        }
	L->cursor = NULL;	
	L->length = 0;
	L->index = -1;
}

// set()
// Overwrites the cursor element's data with x
// Pre: length() > 0, index() >= 0
void set (List L, void *x) {
	if (L == NULL) {
                printf("List Error: calling set() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) <= 0) {
		printf("List Error: calling set() on List with length less than or equal to 0\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling set() on List with undefined cursor index\n");
		exit(EXIT_FAILURE);
	}
	else {
		L->cursor->data = x;
	}
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise it does nothing
void moveFront (List L) {
	if (L == NULL) {
                printf("List Error: calling moveFront() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

// moveBack()
// If cursor L is non-empty, sets cursor to back element, otherwise it does nothing
void moveBack (List L) {
	if (L == NULL) {
                printf("List Error: calling moveBack() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) > 0) {
		L->cursor = L->back;
		L->index = (L->length)-1;
	}
}

// movePrev()
// If cursor is defined and not at the front, move cursor one step toward the front of L; if cursor is defined
// and at the front, cursor becomes undefined; if cursor is undefined, do nothin
void movePrev (List L) {
	if (L == NULL) {
                printf("List Error: calling moveBack() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor != NULL && L->cursor != L->front) {
		L->cursor = L->cursor->previous;
		L->index = L->index - 1;
		return;
	}
	// if (L->cursor != NULL && L->cursor == L->front) {
		L->cursor = NULL;
		L->index = -1;
	//	return;
	//}
}

// moveNext ()
// If cursor is defined and not at the back, move cursor one step toward the back of L; if the cursor is defined
// and at the back, cursor becomes undefined; if the cursor is undefined, do nothin
void moveNext (List L) {
	if (L == NULL) {
                printf("List Error: calling moveBack() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (L->cursor != NULL && L->cursor != L->back) {
		L->cursor = L->cursor->next;
		L->index = L->index + 1;
		return;
	}
	if (L->cursor == NULL) {
		return;
	}
	//(L->cursor != NULL && L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
		return;
	
	//}
	// L->cursor = L->cursor->next;
        // L->index = L->index + 1;
}

// prepend()
// Insert new element in L. If L is non-empty, insertion takes place before the front element.
void prepend(List L, void *x) {
	Node m = newNode(x);
	if (L == NULL) {
                printf("List Error: calling prepend() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	
	if (L->front == NULL) {
		// Node m = newNode(x);
	
		L->front = L->back = m;
		L->length = L->length + 1;
		L->index = 0;
		return;
	}
	
	 if (L->cursor != NULL) {
		L->index = L->index + 1;
	}
         m->previous = NULL;
         m->next = L->front;
                
         L->front->previous = m; 
         L->length = L->length + 1;
                
         L->front = m;
	 // L->index = L->index + 1;
	
}

// append()
// Insert new element in L. If L is non-empty, insertion takes place after the back element.
void append(List L, void *x) {
	Node n = newNode(x);
	if (L == NULL) {
                printf("List Error: calling append() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (L->back == NULL) {
		//Node n = newNode(x);

		L->front = L->back = n;
		L->length = L->length + 1;
		return;	
	}

	//Node n = newNode(x);
        // n->data = x;
        n->previous = L->back;
        n->next = NULL;

        L->back->next = n;
        L->length = L->length + 1;

        L->back = n;
}

// insertBefore()
// Insert element before cursor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, void *x) {
	if (L == NULL) {
                printf("List Error: calling insertBefore() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) <= 0) {
		printf("List Error: calling insertBefore() on List of no length\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		printf("List Error: calling insertBefore() on List with undefined cursor index\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->front) {
		prepend(L, x);
		return;
	}
		
	Node new = newNode(x);

	new->previous = L->cursor->previous;
	new->next = L->cursor;

	L->cursor->previous->next = new;
	L->cursor->previous = new;	
	L->length = L->length + 1;
	L->index = L->index + 1;
}

// insertAfter()
// Insert new element after cursor
// Pre: Pre: length()>0, index()>=0
void insertAfter(List L, void *x) {
	if (L == NULL) {
                printf("List Error: calling insertAfter() on NULL List\n");
                exit(EXIT_FAILURE);
        }
        if (length(L) <= 0) {
                printf("List Error: calling insertAfter() on List of no length\n");
                exit(EXIT_FAILURE);
        }
        if (L->index < 0) {
                printf("List Error: calling insertAfter() on List with undefined cursor index\n");
                exit(EXIT_FAILURE);
        }
	if (L->cursor == L->back) {
		append(L, x);
		return;	
	}
	
	Node new = newNode(x);

	new->next = L->cursor->next;
	new->previous = L->cursor;
	// new->next = L->cursor->next;

	L->cursor->next->previous = new;
	L->cursor->next = new;
	L->length = L->length + 1;
	
}

// deleteFront()
// Delete the front element.
// Pre: Pre: length()>0
void deleteFront(List L) {
	if (L == NULL) {
                printf("List Error: calling deleteFront() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) <= 0) {
		printf("List Error: calling deleteFront() on List of no length\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) == 1) {
		free(L->front);
		L->back = L->front = NULL;
	
		L->index = -1;
		L->length = 0;
		return;
	}
	if (L->cursor == L->front) {
		L->front = L->front->next;
		free(L->front->previous);
		L->front->previous = NULL;

		L->cursor = NULL;
		L->index = -1;
		L->length = L->length - 1;
		return;
	}

	L->front = L->front->next;
	free(L->front->previous);
	L->front->previous = NULL;

	L->index = L->index - 1;
	L->length = L->length - 1;
}

// deleteBack()
// Delete the back element.
// Pre: length()>0
void deleteBack(List L) {
	if (L == NULL) {
                printf("List Error: calling deleteBack() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) <= 0) {
		printf("List Error: calling deleteBack() on List of no length\n");
                exit(EXIT_FAILURE);
	} 
	if (length(L) == 1) {
                free(L->back);
                L->back = L->front = NULL;
		
		L->index = -1;
                L->length = 0;
		return;
        }
	if (L->cursor == L->back) {
		L->back = L->back->previous;
		free(L->back->next);
		L->back->next = NULL;

		L->cursor = NULL;
		L->index = -1;
		L->length = L->length - 1;
		return;
	}

	L->back = L->back->previous;
	free(L->back->next);
	L->back->next = NULL;

	L->length = L->length - 1;
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
	if (L == NULL) {
                printf("List Error: calling delete() on NULL List\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) <= 0) {
                printf("List Error: calling delete() on List of no length\n");
                exit(EXIT_FAILURE);
        }
	if (index(L) < 0) {
                printf("List Error: calling delete() undefined cursor\n");
                exit(EXIT_FAILURE);
        }
	if (L->cursor == L->back) {
		deleteBack(L);
		return;
	}
	if (L->cursor == L->front) {
		deleteFront(L);
		return;
	}

	// need help
	L->cursor->previous->next = L->cursor->next;
	L->cursor->next->previous = L->cursor->previous;

	L->index = -1;
	free(L->cursor);
	L->cursor = NULL;

	L->length = L->length - 1;
	
}

// Other operations --------------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
/*void printList(FILE* out, List L) {
	Node N = NULL;

   	if (L == NULL) {
		printf("List Error: calling printList() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}

   	for(N = L->front; N != NULL; N = N->next){
      		fprintf(out, "%p ", N->data);
   	}
	// fprintf(out, "%s", "\n");
} */

