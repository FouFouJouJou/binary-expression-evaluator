#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

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



uint8_t get_operator_priority(char opertor) {
  char *priorities[] = {"()", "+-", "*/", "^"};
  int n=4;
  for(int i=0; i<n; ++i) {
    if(strchr(priorities[i], opertor) != NULL) return i;
  }
  exit(69);
}

char *reverse_string(char *string) {
  int length = strlen(string);
  char *end_of_string=string+length;
  char *reverse=calloc(length, sizeof(char));
  while(string != end_of_string) {
    int idx = end_of_string-string-1;
    *(reverse+idx)=*string;
    ++string;
  }
  return reverse;
}

char *reversed(char *string) {
  char *start=string;
  char *end=string+strlen(string)-1;
  while(start < end) {
    char current=*start;
    *start=*end;
    *end=current;
    start++;
    end--;
  }
  return string;
}

char *infix_to_postfix(char *infix_expression) {
  char *result=calloc(strlen(infix_expression)+1, sizeof(char));
  char operators[7]="*+/-()^";
  char stack[50], *operator, *start=infix_expression, *result_pointer=result;
  uint8_t stack_idx=0;
  while(*start != '\0') {
    if(*start >= '0' && *start <= '9') {
      *result_pointer=*start;
      result_pointer++;
    }
    else if((operator=strchr(operators, *start)) != NULL) {
      if(stack_idx == 0 || *operator == '(') {
        stack[stack_idx++]=*operator;
      }
      else if(*operator == ')') {
        for(uint8_t i=stack_idx-1; stack[i] != '(' && stack_idx!=0; --i) {
          *result_pointer++=stack[i];
          stack_idx--;
        }
        stack[stack_idx--]='\0';
      }
      else if(get_operator_priority(*operator) >= get_operator_priority(stack[stack_idx-1])) {
        stack[stack_idx++]=*operator;
      } 
      else if(get_operator_priority(*operator) < get_operator_priority(stack[stack_idx-1])) {
        while(get_operator_priority(*operator) < get_operator_priority(stack[stack_idx-1])
            && stack_idx != 0) {
          *result_pointer=stack[stack_idx-1];
          stack[stack_idx-1]='\0';
          stack_idx--;
          result_pointer++;
        }
        stack[stack_idx++]=*operator;
      }
    }
    start++;
  }
  if(stack_idx > 0) {
    for(uint8_t i=stack_idx; i>0; --i) {
      *result_pointer++=stack[i-1];
    }
  }
  return result;
}

void run_test() {
  char *expr1="1+2", *postfix1=infix_to_postfix(expr1);
  char *expr2="1+2+3", *postfix2=infix_to_postfix(expr2);
  char *expr3="1+2*3", *postfix3=infix_to_postfix(expr3);
  char *expr4="1+(2*3)", *postfix4=infix_to_postfix(expr4);
  char *expr5="(9*2)+(2*3)", *postfix5=infix_to_postfix(expr5);
  char *expr6="(9*(2+1)) + (2*(3+1*3))", *postfix6=infix_to_postfix(expr6);
  assert(!strcmp(postfix1,"12+"));
  assert(!strcmp(postfix2,"123++"));
  assert(!strcmp(postfix3,"123*+"));
  assert(!strcmp(postfix4,"123*+"));
  assert(!strcmp(postfix5,"92*23*+"));
  assert(!strcmp(postfix6,"921+*2313*+*+"));
  free(postfix1);
  free(postfix2);
  free(postfix3);
  free(postfix4);
  free(postfix5);
  free(postfix6);
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
  char *postfix_expression = infix_to_postfix(expression_string), *postfix_start=postfix_expression;
  struct Expression *expression_stack[40];
  uint8_t stack_idx=0;
  while(*postfix_start != '\0') {
    if(*postfix_start >= '0' && *postfix_start <='9') {
      expression_stack[stack_idx++]=make_int_literal(*postfix_start);
    } else {
      assert(stack_idx > 1);
      struct Expression *n_1=expression_stack[stack_idx-1];
      struct Expression *n_2=expression_stack[stack_idx-2];
      struct Expression *bin_op=make_binary_expression(*postfix_start, n_2, n_1);
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
