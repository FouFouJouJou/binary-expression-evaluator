#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lexer.h>
#include <binary_expression_tree.h>
#define TOTAL_OPERATIONS 4

typedef void(*action)(char *);

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

void run(char *expression) {
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


const char *operations[] = {"eval", "tokenize", "postfix", "run"};
action actions[] = {eval, lex, postfix, run};

int main(int argc, char **argv) {
  if(argc != 3) {
    fprintf(stderr, "No expression provided: expr argument is (nil)\n");
    exit(69);
  }

  char *cli_operation = argv[1];

  for (size_t i=0; i<sizeof(operations)/sizeof(operations[0]); ++i) {
    if (!strncmp(cli_operation, operations[i], strlen(operations[i]))) {
      actions[i](argv[2]);
      return EXIT_SUCCESS;
    }
  }
  fprintf(stderr, "Operation '%s' is not supported\n", cli_operation);
  exit(69);
}
