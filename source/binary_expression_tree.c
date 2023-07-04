#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <binary_expression_tree.h>

struct Expression *make_expression(char *type, void *expression, size_t bytes) {
  struct Expression *expr = malloc(sizeof(struct Expression));
  expr->type=strdup(type);
  expr->expression=malloc(bytes);
  memcpy(expr->expression, expression, bytes);
  return expr;
}

struct Expression *make_int_literal(char value) {
  struct IntLiteral *int_literal=malloc(sizeof(struct IntLiteral));
  int_literal->value=value-'0';
  struct Expression *expr=make_expression("int", int_literal, sizeof(*int_literal));
  return expr;
}


struct Expression *make_binary_expression(enum BinaryOperator op, struct Expression *left, struct Expression *right) {
  struct BinaryExpression *bin_op= malloc(sizeof(struct BinaryExpression));
  bin_op->operator=op;
  bin_op->left_expression=left;
  bin_op->right_expression=right;
  struct Expression *expr = make_expression("bin_op", bin_op, sizeof(*bin_op));
  return expr;
}

void traverse_expression_tree(struct Expression *expr, uint8_t level) {
  for(uint8_t i=0; i<level; ++i) printf(" ");
  if(!strcmp(expr->type, "int")) {
    printf("%i", ((struct IntLiteral *)(expr->expression))->value);
  }
  else {
    struct BinaryExpression *bin_op = ((struct BinaryExpression *)(expr->expression));
    printf("(%c", bin_op->operator);
    traverse_expression_tree(bin_op->left_expression,level+1);
    traverse_expression_tree(bin_op->right_expression, level+1);
    printf(")");
  }
  if(level == 0) printf("\n");
}

int evaluate_expression_tree(struct Expression *expr) {
  if(!strcmp(expr->type, "int")) {
    return ((struct IntLiteral *)(expr->expression))->value;
  }
  else {
    struct BinaryExpression *bin_op = ((struct BinaryExpression *)(expr->expression));
    int left_eval=evaluate_expression_tree(bin_op->left_expression);
    int right_eval=evaluate_expression_tree(bin_op->right_expression);
    switch(bin_op->operator) {
      case '+':
        return left_eval + right_eval;
      case '-':
        return left_eval - right_eval;
      case '*':
        return left_eval * right_eval;
      case '/':
        return left_eval / right_eval;
    }
  }
}

struct Expression *build_tree(char *expression_string) {
  struct Token *postfix_expression = infix_to_postfix(expression_string), *postfix_start=postfix_expression;
  struct Expression *expression_stack[40];
  uint8_t stack_idx=0;
  while(postfix_start->type != EOS) {
  printf("%li\n", postfix_start-postfix_expression);
    if(postfix_start->type == INT) {
      expression_stack[stack_idx++]=make_int_literal(*(postfix_start->value));
    } else {
      assert(stack_idx > 1);
      struct Expression *n_1=expression_stack[stack_idx-1];
      struct Expression *n_2=expression_stack[stack_idx-2];
      struct Expression *bin_op=make_binary_expression(*(postfix_start->value), n_2, n_1);
      expression_stack[stack_idx-1]=expression_stack[stack_idx-2]=NULL;
      stack_idx-=2;
      stack_idx++;
      expression_stack[stack_idx-1]=bin_op;
      assert(stack_idx >= 1);
    }
    postfix_start++;
  }
  free(postfix_expression);
  assert(stack_idx == 1);
  return expression_stack[0];
}

void free_expression_tree(struct Expression *root) {
  if(!strcmp(root->type, "int")) {
    free(root->type);
    free(root->expression);
    free(root);
  }
  else {
    struct BinaryExpression *bin_op = root->expression;
    free_expression_tree(bin_op->left_expression);
    free_expression_tree(bin_op->right_expression);
    free(bin_op);
  }
}
