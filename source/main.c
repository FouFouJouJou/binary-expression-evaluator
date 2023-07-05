#include <stdlib.h>
#include <stdio.h>
#include <postfix.h>
#include <binary_expression_tree.h>
#include <lexer.h>

uint16_t evaluate(char *expression_string) {
  struct Expression *root=build_tree(expression_string);
  uint16_t result=evaluate_expression_tree(root);
  traverse_expression_tree(root,0);
  free_expression_tree(root);
  return result;
}

int main(int argc, char **argv) {
  if(argc != 2) {
    fprintf(stderr, "No expression provided: expr argument is (nil)\n");
    exit(420);
  }
  char *expression=argv[1];
  printf("evaluating: %s\n", expression);
  printf("result: %d\n", evaluate(expression));
  return EXIT_SUCCESS;
}
