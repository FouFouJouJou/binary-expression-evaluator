#ifndef __BINARY_EXPR_TREE_h__
#define __BINARY_EXPR_TREE_h__
#include <stdint.h>
#include <postfix.h>
struct IntLiteral {
  uint16_t value;
};

struct BinaryExpression {
  enum BinaryOperator operator;
  struct Expression *left_expression;
  struct Expression *right_expression;
};

struct Expression {
  char *type;
  void *expression;
};

struct Expression *make_expression(char *type, void *expression, size_t bytes);
struct Expression *make_int_literal(uint16_t value);
struct Expression *make_binary_expression(enum BinaryOperator op, struct Expression *left, struct Expression *right);
void traverse_expression_tree(struct Expression *expr, uint8_t level);
uint16_t evaluate_expression_tree(struct Expression *expr);
struct Expression *build_tree(char *expression_string);
void free_expression_tree(struct Expression *root);
#endif
