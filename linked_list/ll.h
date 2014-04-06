#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct linked_list linked_list;
typedef struct cons cons;
/* cons is the Racket equivalent of Lisp's car */
struct cons {
  int value;
  cons *next;
};

struct linked_list {
  int size;
  cons *list;
};

void linked_list_append(linked_list *ll, int value);
int size(linked_list *ll);
void linked_list_insert_after(linked_list *ll, int value, int index);
void linked_list_delete_at(linked_list *ll, int index);
linked_list *new_linked_list(void);
void linked_list_destroy(linked_list *ll);
int linked_list_get(linked_list *ll, int index);
void linked_list_print(linked_list *ll);
