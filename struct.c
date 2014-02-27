#include <stdio.h>
int main() {
  int (*p)[10];
  printf("%ld",sizeof(*p));
}
