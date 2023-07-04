#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include <stdint.h>

enum BinaryOperator {
  ADD='+'
  ,SUB='-'
  ,DIV='/'
  ,MULT='*'
};

uint8_t get_operator_priority(char opertor);
char *reverse_string(char *string);
char *reversed(char *string);
char *infix_to_postfix(char *infix_expression);
int evaluate(char *expression_string);
#endif
