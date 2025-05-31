#ifndef __list_h__
#define __list_h__

#include <stdlib.h>

typedef struct ListNode {
  struct ListNode* prev;
  struct ListNode* next;
  void* value;
} ListNode;

typedef struct List {
  int count;
  ListNode* first;
  ListNode* last;
} List;

List* List_create();

// destroy destroys the nodes and clear destroys the data held by the nodes not
// the nodes themselves
void List_destroy(List* list);
void List_clear(List* list);
void List_clear_destroy(List* list);

#define List_count(A) ((A) != NULL ? (A)->count : 0)
#define List_first(A) \
  ((A) != NULL && (A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) \
  ((A) != NULL && (A)->last != NULL ? (A)->last->value : NULL)

int List_push(List* list, void* value);
void* List_pop(List* list);

// unshift adds an element to the head and shift removes the first element
int List_unshift(List* list, void* value);
void* List_shift(List* list);

// removes the given node
void* List_remove(List* list, ListNode* node);

int List_swap(ListNode* node1, ListNode* node2);
List* List_split(List* list, ListNode* split_node);
int List_join(List* list1, List* list2);

// macro for making iteration over all the elements easier
#define LIST_FOREACH(L, S, M, V) \
  for (ListNode* V = (L != NULL ? L->S : NULL); V != NULL; V = V->M)

#endif
