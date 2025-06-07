#include <list.h>

List* List_create() { return calloc(1, sizeof(List)); }

void List_destroy(List* list) {
  LIST_FOREACH(list, first, next, cur) { free(cur->prev); }
  if (list != NULL) free(list->last);
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
  if (list != NULL) free(list->last);
  free(list);
}

int List_push(List* list, void* value) {
  ListNode* node = NULL;

  check_invariants(list);

  node = calloc(1, sizeof(ListNode));
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

  return 0;
error:
  return -1;
}

void* List_pop(List* list) {
  check_invariants(list);

  ListNode* node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;
error:
  return NULL;
}

int List_unshift(List* list, void* value) {
  ListNode* node = NULL;

  check_invariants(list);

  node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }

  list->count++;

  return 0;
error:
  return -1;
}

void* List_shift(List* list) {
  check_invariants(list);

  ListNode* node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;
error:
  return NULL;
}

void* List_remove(List* list, ListNode* node) {
  void* result = NULL;

  check_invariants(list);

  check(list->first && list->last, "List is empty");
  check(node, "node can't be NULL");

  if (node == list->first && node == list->last) {
    list->first = NULL;
    list->last = NULL;
  } else if (node == list->first) {
    list->first = node->next;
    check(list->first != NULL,
          "Invalid list, somehow got a first that is a NULL.");
    list->first->prev = NULL;
  } else if (node == list->last) {
    list->last = node->prev;
    check(list->last != NULL,
          "Invalid list, somehow got a last that is a NULL.");
    list->last->next = NULL;
  } else {
    node->next->prev = node->prev;
    node->prev->next = node->next;
  }

  list->count--;
  result = node->value;
  free(node);
error:
  return result;
}

int List_swap(ListNode* node1, ListNode* node2) {
  void* tmp = node1->value;

  node1->value = node2->value;
  node2->value = tmp;

  return 0;
}

List* List_split(List* list, ListNode* split_node) {
  List* split_list = List_create();

  check_invariants(list);
  check(List_count(list) > 1,
        "There should be more than 1 element to split the list.");
  check(split_list != NULL, "Failed to create list.");

  int split_list_count = List_count(list);
  int node_found = 0;
  LIST_FOREACH(list, first, next, cur) {
    if (cur == split_node) {
      node_found = 1;
      break;
    }
    split_list_count--;
  }

  check(node_found == 1, "Split node not found in list.");

  split_list->first = split_node;
  split_list->last = list->last;
  split_list->count = split_list_count;

  list->last = split_node->prev;
  list->count -= split_list_count;

  split_node->prev->next = NULL;
  split_node->prev = NULL;

  return split_list;
error:
  if (split_list != NULL) {
    List_destroy(split_list);
  }
  return NULL;
}

int List_join(List* list1, List* list2) {
  check_invariants(list1);
  check_invariants(list2);
  LIST_FOREACH(list2, first, next, cur) { List_push(list1, cur->value); }
  return 0;
error:
  return -1;
}

int List_insert_sorted(List* list, void* value, List_compare cmp) {
  ListNode* node = NULL;

  check_invariants(list);
  check(List_is_sorted(list, cmp) == 1, "List is not sorted.");

  ListNode* first_larger_node = NULL;
  int rc = 0;

  LIST_FOREACH(list, first, next, cur) {
    if (cmp(cur->value, value) > 0) {
      first_larger_node = cur;
      break;
    }
  }

  if (first_larger_node == list->first) {
    rc = List_unshift(list, value);
    check(rc == 0, "List unshift failed.");
  } else if (first_larger_node == NULL) {
    rc = List_push(list, value);
    check(rc == 0, "List push failed.");
  } else {
    node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    first_larger_node->prev->next = node;
    node->next = first_larger_node;
    node->prev = first_larger_node->prev;
    first_larger_node->prev = node;

    list->count++;
  }

  return 0;
error:
  free(node);
  return -1;
}
