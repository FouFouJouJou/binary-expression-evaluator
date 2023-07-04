#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <postfix.h>
#include <binary_expression_tree.h>

int evaluate(char *expression_string) {
  struct Expression *root=build_tree(expression_string);
  int result=evaluate_expression_tree(root);
  traverse_expression_tree(root,0);
  free_expression_tree(root);
  return result;
}

int main(int argc, char **argv) {
  if(argc != 2) {
    fprintf(stderr, "No params provided\n");
    exit(420);
  }
  char *expression=argv[1];
  printf("evaluating: %s\n", expression);
  printf("result: %i\n", evaluate(expression));
  return EXIT_SUCCESS;
}
