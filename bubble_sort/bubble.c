#include "../linked_list/ll.h"

void sort_linked_list(linked_list *list) {
  assert(list);
  int sorted = 1;
  for (int x = 0; x < list->size; x++) {
    /* don't do it if this is the last value */
    if (x + 1 == list->size) {
      continue;
    }
    int first = linked_list_get(list, x);
    int second = linked_list_get(list, x + 1);
    if (first > second) {
      sorted = 0;
      int temp = linked_list_get(list, x);
      /* {1, 7, 3}, 1 -> {1, 3} */
      linked_list_delete_at(list, x);
      /* {1, 3}, 7, 1 -> {1, 3, 7} */ 
      linked_list_insert_after(list, temp, x);
    }
  }
  /* do it again if it's not fully sorted */
  if (!sorted) {
    sort_linked_list(list);
  }
}

void sort_array(int *array, int size) {
  assert(size >= 0);
  int sorted = 1;
  for (int x = 0; x < size; x++) {
    /* don't do it if this is the last value */
    if (x + 1 == size) {
      break;
    }
    /* get int address */
    int *first = array + x;
    /* get int address after that one */
    int *second = first + 1;
    if (*first > *second) {
      /* we did some sorting so not sorted */
      sorted = 0;
      int temp = *first;
      int temp2 = *second;
      /* swap values */
      *first = temp2;
      *second = temp;
    }
  }
  /* do it again if it's not fully sorted */
  if (sorted == 0) {
    sort_array(array, size);
  }
}

void print_array(int *array, int size) {
  printf("{ ");
  for (int x = 0; x < size; x++) {
    printf("%d ", *array);
    array++;
  }
  printf("}\n");
}


int main() {
  linked_list *list = new_linked_list();
  linked_list_append(list, 7);
  linked_list_append(list, 5);
  linked_list_append(list, 3);
  linked_list_append(list, 8);
  linked_list_append(list, 1);
  linked_list_print(list);
  sort_linked_list(list);
  linked_list_print(list);
  int a[5] = {7, 5, 3, 8, 1};
  print_array(a, 5);
  sort_array(a, 5);
  print_array(a, 5);
  return 0;
}
