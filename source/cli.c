#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lexer.h>
#include <cli.h>
#include <binary_expression_tree.h>

void eval(char *expression) {
  printf("evaluating: %s\n", expression);
  struct Expression *root=build_tree(expression);
  int16_t result=evaluate_expression_tree(root);
  free_expression_tree(root);
  printf("result: %d\n", result);
}

void lex(char *expression) {
  printf("tokenizing: %s\n", expression);
  struct Token *tokens=tokenize(expression);
  printf_tokens(tokens, printf_token);
  free_tokens(tokens);
}

void postfix(char *expression) {
  struct Expression *root=build_tree(expression);
  printf("postfix: %s", expression);
  traverse_expression_tree(root,0);
  free_expression_tree(root);
}

void all(char *expression) {
  printf("tokenizing: %s\n", expression);
  struct Token *tokens=tokenize(expression);
  printf_tokens(tokens, printf_token);
  free_tokens(tokens);

  struct Expression *root=build_tree(expression);
  printf("postfix: %s", expression);
  traverse_expression_tree(root, 0);
  int16_t result=evaluate_expression_tree(root);
  free_expression_tree(root);
  printf("result: %d\n", result);
}

void help() {
  printf("./main <operation> <expression>\n");
  printf("Supported <operation>: [");
  const size_t total_operations = sizeof(operations)/sizeof(operations[0]);
  for (size_t i=0; i<total_operations; ++i) {
    printf("%s", operations[i]);
    if (i+1 != total_operations) {
      printf("|");
    }
  }
  printf("]\n");
  printf("<expression> can be any supported arithmatic expression.\n");
}
