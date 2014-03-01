    #include "ll.h"

    /* cons is the Racket equivalent of Lisp's car */
    struct cons {
      int value;
      cons *next;
    };

    struct linked_list {
      int size;
      cons *list;
    };

    static void append(cons *c, int value) {
      if (c->next) {
        append(c->next, value);
      } else {
        /* allocated new memory for the next, because we're at the end */
        cons *new = malloc(sizeof(cons));
        new->value = value;
        new->next = NULL;
        /* make this new cons the new tail */
        c->next = new;
      }
    }

    static int get(cons *c, int index, int current) {
      if (index == current) {
        return c->value;
      } else {
        return get(c->next, index, ++current);
      }
    }

    static void destroy(cons *c) {
      if (c) {
        destroy(c->next);
        free(c);
      }
    }

    static void cons_print(cons *c) {
      if (c) {
        printf("%d ", c->value);
        cons_print(c->next);
      } else {
        printf("\n");
      }
    }

    void insert_after(cons *c, int value, int index, int current) {
      if (index == current) {
        cons *new = malloc(sizeof(cons));
        new->value = value;
        new->next = c->next;
        c->next = new;
      } else { 
        insert_after(c->next, value, index, ++current);
      }
    }

    linked_list *new_linked_list(void) {
      linked_list *ll = malloc(sizeof(linked_list));
      assert(ll);
      ll->size = 0;
      ll->list = NULL;
      return ll;
    }

    int linked_list_get(linked_list *ll, int index) {
      assert(ll);
      assert(index >= 0);
      assert(index <= (ll->size - 1));
      return get(ll->list, index, 0);
    }

    void linked_list_append(linked_list *ll, int value) {
      assert(ll);
      (ll->size)++;
      if (ll->list) {
        append(ll->list, value);
      } else {
        /* list is null, so we're at the end - allocate space for new tail */
        cons *new = malloc(sizeof(cons));
        new->value = value;
        /* the next of the tail is NULL */
        new->next = NULL;
        /* assign it */
        ll->list = new;
      }
    }

    void linked_list_insert_after(linked_list *ll, int value, int index) {
      assert(ll);
      assert(index >= 0);
      assert(index <= (ll->size - 1));
      ll->size++;
      insert_after(ll->list, value, index, 0);
    }

    int linked_list_size(linked_list *ll) {
      if (ll) {
        return ll->size;
      } else {
        return -1;
      }
    }

    void linked_list_delete_at(linked_list *ll, int index) {
      assert(ll);
      assert(index >= 0);
      assert(index <= (ll->size - 1));
      /* store the list */
      cons *list = ll->list;
      /* store the list again, will be the last node */
      cons *last = list;
      int current = 0;
      while (list) {
        if (index == current) {
          /* skip over pointer to list, then free it */
          last->next = list->next;
          free(list);
          ll->size--;
          break;
        }
        /* will always be one node behind (except at beginning) */
        last = list;
        /* go to next */
        list = list->next;
        current++;
      }
    }

    void linked_list_destroy(linked_list *ll) {
      if (ll) {
        destroy(ll->list);
        free(ll);
      }
    }

    void linked_list_print(linked_list *ll) {
      assert(ll);
      cons_print(ll->list);
    }

    int main(void) {
      linked_list *list = new_linked_list();
      linked_list_print(list);
      linked_list_append(list, 2);
      linked_list_print(list); // 2
      linked_list_append(list, 3);
      linked_list_print(list); // 2 3
      linked_list_append(list, 4);
      linked_list_print(list); // 2 3 4
      linked_list_insert_after(list, 15, 1);
      linked_list_print(list); // 2 3 15 4
      linked_list_delete_at(list, 1);
      linked_list_print(list); // 2 15 4
      printf("get 0: %d\n", linked_list_get(list, 0));
      printf("get 2: %d\n", linked_list_get(list, 2));
      printf("get 1: %d\n", linked_list_get(list, 1));
      printf("size 3: %d\n", linked_list_size(list));
      linked_list_destroy(list);
      return 0;
    }
