#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <postfix.h>
#include <lexer.h>
uint8_t get_operator_priority(char operator) {
  char *priorities[] = {"(", "+-", "*/", "$"};
  int n=4;
  for(int i=0; i<n; ++i) {
    if(strchr(priorities[i], operator) != NULL) return i;
  }
  fprintf(stderr, "postfix: illegal operator %c\n", operator);
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

// 3*-(1*3)
struct Token *infix_to_postfix(char *infix_expression) {
  struct Token *tokens=tokenize(infix_expression), *token=tokens;
  struct Token *result=calloc(30, sizeof(struct Token)), stack[50];
  uint8_t stack_idx=0, result_idx=0;
  while(token->type != EOS) {
    if(token->type == INT) {
      result[result_idx++]=*token;
      token+=1;
    }
    else if(token->type == O_PAREN) {
      stack[stack_idx++]=*token;
      token+=1;
    }
    else if(token->type == C_PAREN) {
      for(uint8_t i=stack_idx-1; stack[i].type != O_PAREN && stack_idx!=0; --i) {
        result[result_idx++]=stack[i];
        stack[i].type=EOS;
        stack_idx-=1;
      }
      if(stack[stack_idx-1].type == O_PAREN) {
        printf("open paren\n");
        stack[stack_idx--].type=EOS;
      }
      token+=1;
    }
    // ( + *
    //else if(get_operator_priority(*(token->value)) >= get_operator_priority(*(stack[stack_idx-1].value))) {
    //  stack[stack_idx++]=*token;
    //  token+=1;
    //} 
    else {
      while(get_operator_priority(*(token->value)) <= get_operator_priority(*(stack[stack_idx-1].value))
          && stack_idx != 0) {
        result[result_idx++]=stack[stack_idx-1];
        stack[stack_idx-1].type=EOS;
        stack_idx-=1;
      }
      stack[stack_idx++]=*token;
      token+=1;
    }
    printf("%s %d\n", token->value, stack_idx);
  }
  if(stack_idx > 0) {
    for(uint8_t i=stack_idx; i>0; --i) {
      printf_token(stack[i-1]);
      result[result_idx++]=stack[i-1];
    }
  }

  printf("Done\n");
  // Token at this point has EOS type
  result[result_idx++]=*token;
  free(tokens);
  for(int i=0; i<result_idx; ++i) printf_token(result[i]);
  printf("%d\n", result_idx);
  return result;
}
