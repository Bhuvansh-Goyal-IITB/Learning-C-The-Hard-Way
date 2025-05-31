#include <list.h>
#include <list_algos.h>

#include "debug.h"

int List_bubble_sort(List* list, List_compare cmp) {
  check(list != NULL, "List is NULL");

  for (int i = list->count - 1; i > 0; i--) {
    ListNode* cur = list->first;
    for (int j = 0; j < i; j++) {
      if (cmp(cur->value, cur->next->value) > 0) {
        int rc = List_swap(cur, cur->next);
        check(rc == 0, "List swap failed.");
      }
      cur = cur->next;
    }
  }
  return 0;
error:
  return 1;
}

List* List_merge_sort(List* list, List_compare cmp) {
  List* sorted_list = List_create();
  int rc = 0;

  check(list != NULL, "List is NULL");

  if (list->count == 1) {
    rc = List_push(sorted_list, list->first->value);
    check(rc == 0, "List push failed.");
  } else if (list->count != 0) {
    int i = 0;
    int mid = list->count & 1 ? ((list->count - 1) / 2) : (list->count / 2);
    ListNode* split_node = list->first->next;

    LIST_FOREACH(list, first, next, cur) {
      if (i == mid) {
        split_node = cur;
        break;
      }
      i++;
    }

    List* split_list = List_split(list, split_node);
    check(split_list != NULL, "Split list failed.");

    List* left = List_merge_sort(list, cmp);
    check(left != NULL, "Left merge sort failed.");
    List* right = List_merge_sort(split_list, cmp);
    check(right != NULL, "Right merge sort failed.");

    rc = List_join(list, split_list);
    check(rc == 0, "List join failed.");
    List_destroy(split_list);

    ListNode* lp = left->first;
    ListNode* rp = right->first;

    while (lp != NULL && rp != NULL) {
      if (cmp(lp->value, rp->value) > 0) {
        rc = List_push(sorted_list, rp->value);
        check(rc == 0, "List push failed.");
        rp = rp->next;
      } else {
        rc = List_push(sorted_list, lp->value);
        check(rc == 0, "List push failed.");
        lp = lp->next;
      }
    }

    while (lp != NULL) {
      rc = List_push(sorted_list, lp->value);
      check(rc == 0, "List push failed.");
      lp = lp->next;
    }

    while (rp != NULL) {
      rc = List_push(sorted_list, rp->value);
      check(rc == 0, "List push failed.");
      rp = rp->next;
    }

    List_destroy(left);
    List_destroy(right);
  }

  return sorted_list;
error:
  if (sorted_list != NULL) {
    List_destroy(sorted_list);
  }
  return NULL;
}
