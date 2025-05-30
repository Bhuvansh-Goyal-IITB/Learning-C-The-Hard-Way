#include <debug.h>
#include <list.h>

List* List_create() { return calloc(1, sizeof(List)); }

void List_destroy(List* list) {
  LIST_FOREACH(list, first, next, cur) { free(cur->prev); }
  free(list->last);
  free(list);
}

void List_clear(List* list) {
  LIST_FOREACH(list, first, next, cur) { free(cur->value); }
}

void List_clear_destroy(List* list) {
  LIST_FOREACH(list, first, next, cur) {
    free(cur->value);
    free(cur->prev);
  }
  free(list->last);
  free(list);
}

void List_push(List* list, void* value) {
  ListNode* node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->last == NULL) {
    list->last = node;
    list->first = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }

  list->count++;
error:
  return;
}
