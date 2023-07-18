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
  case PREF_PLUS:
    return "PREF_PLUS";
  case NEGATE:
    return "NEGATE";
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
  case AND:
    return "AND";
  case OR:
    return "OR";
  case NOT:
    return "NOT";
  case XOR:
    return "XOR";
  default:
    fprintf(stderr, "[lexer] Error: token type illegal (%d)\n", token_type);
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
  char binary_operators[6]="+-/*^";
  char digits[10]="0123456789";
  char *source_code_pointer=source_code;
  while(*source_code_pointer != '\0') {
    if(*source_code_pointer == ' ') source_code_pointer += 1;
    else if(*source_code_pointer >= '0' && *source_code_pointer <= '9') {
      size_t n=strspn(source_code_pointer, digits);
      push(token_stack, make_token(INT, strndupa(source_code_pointer, n)), &stack_idx);
      source_code_pointer+=n;
    }
    else {
      switch(*source_code_pointer) {
        case '|':
          push(token_stack, make_token(OR, strndupa(source_code_pointer,1)), &stack_idx);
          break;
        case '&':
          push(token_stack, make_token(AND, strndupa(source_code_pointer,1)), &stack_idx);
          break;
        case '!':
          push(token_stack, make_token(NOT, strndupa(source_code_pointer,1)), &stack_idx);
          break;
        case '+': 
          if(source_code == source_code_pointer
              || *(source_code_pointer-1) == '(' 
              || strchr(binary_operators, *(source_code_pointer-1)) != 0)
            push(token_stack, make_token(PREF_PLUS, "£"), &stack_idx);
          push(token_stack, make_token(PLUS, strndupa(source_code_pointer, 1)), &stack_idx);
          break;
        case '-': 
          if(source_code == source_code_pointer
              || *(source_code_pointer-1) == '(' 
              || strchr(binary_operators, *(source_code_pointer-1)) != 0)
            push(token_stack, make_token(NEGATE, "$"), &stack_idx);
          else
            push(token_stack, make_token(MINUS, strndupa(source_code_pointer, 1)), &stack_idx);
          break;
        case '/': 
          push(token_stack, make_token(SLASH, strndupa(source_code_pointer, 1)), &stack_idx);
          break;
        case '*': 
          push(token_stack, make_token(STAR, strndupa(source_code_pointer, 1)), &stack_idx);
          break;
        case '(': 
          push(token_stack, make_token(O_PAREN, strndupa(source_code_pointer, 1)), &stack_idx);
          break;
        case ')': 
          push(token_stack, make_token(C_PAREN, strndupa(source_code_pointer, 1)), &stack_idx);
          break;
        default:
          fprintf(stderr, "[lexer] Error: token not supported (%c)\n", *strndupa(source_code_pointer, 1));
          exit(420);
      }
      source_code_pointer+=1;
    }
  }
  push(token_stack, make_token(EOS, ""), &stack_idx);
  return token_stack;
}
