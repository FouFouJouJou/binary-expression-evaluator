#include <stdint.h>

enum BinaryOperator {
  NONE
  ,ADD='+'
  ,SUB='-'
  ,DIV='/'
  ,MULT='*'
};


struct IntLiteral {
  int value;
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
struct Expression *make_int_literal(char value);
struct Expression *make_binary_expression(enum BinaryOperator op, struct Expression *left, struct Expression *right);
uint8_t get_operator_priority(char opertor);
char *reverse_string(char *string);
char *reversed(char *string);
char *infix_to_postfix(char *infix_expression);
void run_test();
void traverse_expression_tree(struct Expression *expr, uint8_t level);
int evaluate_expression_tree(struct Expression *expr);
struct Expression *build_tree(char *expression_string);
void free_expression_tree(struct Expression *root);
int evaluate(char *expression_string);
