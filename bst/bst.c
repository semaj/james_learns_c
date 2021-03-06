#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node node;

struct node {
  int value;
  int is_leaf;
  struct node *right;
  struct node *left;
};

node *new_leaf(void) {
  node *leaf = malloc(sizeof(node));
  assert(leaf);
  leaf->is_leaf = 1;
  leaf->value = 0;
  leaf->right = NULL;
  leaf->left = NULL;
  return leaf;
}

int insert(node *node, int value) {
  assert(node);
  if (node->is_leaf) {
    node->is_leaf = 0;
    node->value = value;
    node->left = new_leaf();
    node->right = new_leaf();
    return 1;
  } else if (node->value < value) {
    return insert(node->left, value);
  } else if (node->value > value) {
    return insert(node->right, value);
  }
  return 0;
}

int contains(node *node, int value) {
  assert(node);
  if (node->is_leaf) {
    return 0;
  } else if (node->value < value) {
    return contains(node->left, value);
  } else if (node->value > value) {
    return contains(node->right, value);
  } 
  return 1;
}

int max_height(node *node) {
  assert(node);
  if (node->is_leaf) {
    return 0;
  } 
  int left_height = max_height(node->left);
  int right_height = max_height(node->right);
  if (left_height > right_height) {
    return 1 + left_height;
  } else {
    return 1 + right_height;
  }
}

void destroy(node *tree) {
  if (tree) {
    free(tree);
    destroy(tree->left);
    destroy(tree->right);
  }
}
  

int main(void) {
  node *tree = new_leaf();
  insert(tree, 7);
  printf("contains 7? : %d\n", contains(tree, 7));
  insert(tree, 6);
  printf("contains 6? : %d\n", contains(tree, 6));
  insert(tree, 5);
  printf("contains 5? : %d\n", contains(tree, 5));
  printf("height should be 3, is : %d\n", max_height(tree));
  insert(tree, 8);
  printf("contains 8? : %d\n", contains(tree, 8));
  printf("height should be 3, is : %d\n", max_height(tree));
  printf("no contains 1? : %d\n", contains(tree, 9));
  destroy(tree);
}
