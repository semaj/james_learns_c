#include <stdio.h>

char *copy_string(char *destination, const char *source) {
  char *start = destination;
  while (*source != '\0') {
    *destination++ = *source++;
  }
  *destination = '\0';
  return start;
}

char *mystrcat(char *destination, const char *source) {
  char *copy = destination;
  while (*copy != '\0') {
    copy++;
  }
  while (*source != '\0') {
    *copy++ = *source++;
  }
  *copy = '\0';
  return destination;
}

void put_string(const char *output) {
  while (*output != '\0') {
    printf("%c",*output++);
  }
  printf("\n");
}

char *cat_string(const char *to_cat, char *destination) {
    char *copy = destination;
    put_string(to_cat);
    while (*copy != '\0') {
        copy++;                 /* Removed superfluous dereference. */
    }
    do {                        /* Changing to a do-while loop takes */
        *copy++ = *to_cat++;    /* care of copying the NUL terminator */
        put_string(to_cat);
        put_string("-");
        put_string(copy);
    } while (*to_cat != '\0');  /* automatically. */
    return destination;
}



void put_int(int output) {
  printf("%d", output);
  printf("\n");
}

int string_length(char *s) {
  int length = 0;
  while (*s) {
    length++;
    s++;
  }
  return length;
}

int main() {
  char a[20] = "hello";
  char b = '\0';
  char *pA = a;
  char *pB = &b;
  int x = 10;
  int y = 20;
  printf("%d : %d", x, y);
  put_int(string_length(a));
  return 0;
}
