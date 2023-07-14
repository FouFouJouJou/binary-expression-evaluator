#ifndef __BINARY_EXPR_TREE_h__
#define __BINARY_EXPR_TREE_h__
#include <stdint.h>
#include <postfix.h>
// TODO: add expression type to make switch cases
// and prevent future bugs
enum ExpressionType {
  INT_LITERAL_TYPE
};

struct IntLiteral {
  int16_t value;
};

struct Negate {
  struct Expression *expression;
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

void traverse_expression_tree(struct Expression *expr, uint8_t level);
int16_t evaluate_expression_tree(struct Expression *expr);
struct Expression *build_tree(char *expression_string);
void free_expression_tree(struct Expression *root);
#endif
