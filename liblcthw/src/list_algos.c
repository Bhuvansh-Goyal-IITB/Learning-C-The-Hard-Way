#include <list_algos.h>

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
  return -1;
}

static inline List* merge_step(ListNode* left_start, ListNode* right_start,
                               int width, List_compare cmp) {
  List* result = List_create();
  check(result != NULL, "List create failed.");

  int left_count = 0;
  int right_count = 0;

  int rc = 0;

  while (left_start != NULL && left_count < width && right_start != NULL &&
         right_count < width) {
    if (cmp(left_start->value, right_start->value) > 0) {
      rc = List_push(result, right_start->value);
      check(rc == 0, "List push failed");
      right_start = right_start->next;
      right_count++;
    } else {
      rc = List_push(result, left_start->value);
      check(rc == 0, "List push failed");
      left_start = left_start->next;
      left_count++;
    }
  }

  while (left_start != NULL && left_count < width) {
    rc = List_push(result, left_start->value);
    check(rc == 0, "List push failed");
    left_start = left_start->next;
    left_count++;
  }

  while (right_start != NULL && right_count < width) {
    rc = List_push(result, right_start->value);
    check(rc == 0, "List push failed");
    right_start = right_start->next;
    right_count++;
  }

  return result;
error:
  List_destroy(result);
  return NULL;
}

List* List_merge_sort(List* list, List_compare cmp) {
  List* current_iteration = list;
  List* next_iteration = List_create();

  List* merge_list = NULL;

  check(next_iteration != NULL, "List creation failed.");
  check(list != NULL, "List is NULL.");

  if (List_count(list) == 0) {
    return next_iteration;
  }

  int rc = 0;

  if (List_count(list) == 1) {
    rc = List_push(next_iteration, List_first(list));
    check(rc == 0, "List push failed");
  } else if (List_count(list) != 0) {
    int width = 1;
    for (; width < List_count(list); width *= 2) {
      ListNode* left_start = NULL;
      ListNode* right_start = NULL;

      int length = 0;

      LIST_FOREACH(current_iteration, first, next, cur) {
        if (length == 2 * width) {
          length = 0;
        }

        if (length == 0) {
          if (right_start != NULL) {
            merge_list = merge_step(left_start, right_start, width, cmp);
            check(merge_list != NULL, "Merge list failed.");

            rc = List_join(next_iteration, merge_list);
            check(rc == 0, "List join failed.");

            List_destroy(merge_list);

            right_start = NULL;
          }
          left_start = cur;
        } else if (length == width) {
          right_start = cur;
        }
        length++;
      }

      if (right_start != NULL) {
        merge_list = merge_step(left_start, right_start, width, cmp);
        check(merge_list != NULL, "Merge list failed.");

        rc = List_join(next_iteration, merge_list);
        check(rc == 0, "List join failed.");

        List_destroy(merge_list);
      } else if (left_start != NULL) {
        while (left_start != NULL) {
          rc = List_push(next_iteration, left_start->value);
          check(rc == 0, "List push failed");
          left_start = left_start->next;
        }
      }

      if (current_iteration != list) List_destroy(current_iteration);
      current_iteration = next_iteration;
      next_iteration = List_create();
      check(next_iteration != NULL, "List creation failed.");
    }
  }

  List_destroy(next_iteration);
  return current_iteration;
error:
  List_destroy(merge_list);
  List_destroy(next_iteration);
  return NULL;
}
