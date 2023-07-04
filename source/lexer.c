#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <lexer.h>


struct Token *make_token(enum TokenType token_type, char *value) {
  struct Token *token = malloc(sizeof(struct Token));
  token->type=token_type;
  token->value=strdup(value);
  return token;
}

void free_token(struct Token *token) {
  free(token->value);
  free(token);
}

char *token_type_to_string(enum TokenType token_type) {
  switch(token_type) {
  case INT:
    return "INT";
  case PLUS:
    return "PLUS";
  case MINUS:
    return "MINUS";
  case SLASH:
    return "SLASH";
  case STAR:
    return "STAR";
  case O_PAREN:
    return "O_PAREN";
  case C_PAREN:
    return "C_PAREN";
  case EOS:
    return "EOS";
  default:
    fprintf(stderr, "token type illegal\n");
  }
  return 0;
}

void printf_token(struct Token token) {
  printf("(%s, %s) \n", token_type_to_string(token.type), token.value);
}

void push(struct Token *stack, struct Token *token, uint8_t *stack_idx) {
  stack[*stack_idx]=*token;
  (*stack_idx)+=1;
  free(token);
}

struct Token *tokenize(char *source_code) {
  struct Token *token_stack=calloc(30, sizeof(struct Token));
  uint8_t stack_idx=0;
  char operators[7]="+-/*()^";
  while(*source_code != '\0') {
    if(*source_code == ' ') source_code += 1;
    else if(*source_code >= '0' && *source_code <= '9') {
      size_t n=strcspn(source_code, operators);
      push(token_stack, make_token(INT, strndupa(source_code, n)), &stack_idx);
      source_code+=n;
    }
    else {
      switch(*source_code) {
        case '+': 
          push(token_stack, make_token(PLUS, strndupa(source_code, 1)), &stack_idx);
          break;
        case '-': 
          push(token_stack, make_token(MINUS, strndupa(source_code, 1)), &stack_idx);
          break;
        case '/': 
          push(token_stack, make_token(SLASH, strndupa(source_code, 1)), &stack_idx);
          break;
        case '*': 
          push(token_stack, make_token(STAR, strndupa(source_code, 1)), &stack_idx);
          break;
        case '(': 
          push(token_stack, make_token(O_PAREN, strndupa(source_code, 1)), &stack_idx);
          break;
        case ')': 
          push(token_stack, make_token(C_PAREN, strndupa(source_code, 1)), &stack_idx);
          break;
        default:
          fprintf(stderr, "lexer: operator not supported (%c)\n", *strndupa(source_code, 1));
          exit(420);
      }
      source_code+=1;
    }
  }
  push(token_stack, make_token(EOS, ""), &stack_idx);
  return token_stack;
}
