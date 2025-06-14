#ifndef __list_h__
#define __list_h__

#include <debug.h>
#include <stdlib.h>

typedef int (*List_compare)(const void* a, const void* b);

typedef struct ListNode {
  struct ListNode* prev;
  struct ListNode* next;
  void* value;
} ListNode;

typedef struct List {
  size_t count;
  ListNode* first;
  ListNode* last;
} List;

#define check_invariants(A)                                      \
  check((A) != NULL, "List is NULL.");                           \
  if ((A)->count > 0)                                            \
    check((A)->first != NULL && (A)->last != NULL,               \
          "first or last element is NULL in a non empty List."); \
  if ((A)->count == 0)                                           \
    check((A)->first == NULL && (A)->last == NULL,               \
          "first or last element is not NULL in an empty List.");

List* List_create();

// Destroy destroys the nodes and clear destroys the data held by the nodes not
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

// Unshift adds an element to the head and shift removes the first element
int List_unshift(List* list, void* value);
void* List_shift(List* list);

// Removes the given node
void* List_remove(List* list, ListNode* node);

// Swaps the data of 2 nodes
int List_swap(ListNode* node1, ListNode* node2);

// The left half of the split is the ptr list and the returned List* ptr is the
// right half of the split
List* List_split(List* list, ListNode* split_node);

// Joins the list2 elements at the end of list1
int List_join(List* list1, List* list2);

// Inserts the new value such that the list remains sorted, list must be sorted
// already to begin with
int List_insert_sorted(List* list, void* value, List_compare cmp);

// macro for making iteration over all the elements easier
#define LIST_FOREACH(L, S, M, V) \
  for (ListNode* V = (L != NULL ? L->S : NULL); V != NULL; V = V->M)

// Tells whether list is sorted or not
static inline int List_is_sorted(List* list, List_compare cmp) {
  check_invariants(list);

  LIST_FOREACH(list, first, next, cur) {
    if (cur->next && cmp(cur->value, cur->next->value) > 0) return 0;
  }

  return 1;
error:
  return -1;
}

#endif
