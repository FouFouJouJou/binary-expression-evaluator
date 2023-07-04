#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <postfix.h>
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
