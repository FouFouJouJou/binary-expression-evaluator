#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <lexer.h>


struct Token *make_token(enum TokenType token_type, char *value) {
  struct Token *token = malloc(sizeof(struct Token));
  token->type=token_type;
  token->value=value;
  return token;
}

void free_tokens(struct Token *tokens) {
  for (struct Token *token = tokens; token->type != EOS; token++) {
    free_token(token);
  }
  free(tokens);
}

void free_token(struct Token *token) {
  free(token->value);
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
  case EOS:
    return "EOS";
  default:
    fprintf(stderr, "[lexer] Error: token type illegal (%d)\n", token_type);
  }
  return 0;
}

void printf_token(struct Token token) {
  printf("(%s, '%s') \n", token_type_to_string(token.type), token.value);
}

void printf_tokens(struct Token *tokens, void(*printf_token)(struct Token token)) {
  struct Token *token = tokens;
  while (token->type != EOS) {
    printf_token(*token++);
  }
}
void push(struct Token *stack, struct Token *token, uint8_t *stack_idx) {
  stack[*stack_idx]=*token;
  (*stack_idx)+=1;
  free(token);
}

struct Token *tokenize(char *source_code) {
  struct Token *token_stack=calloc(30, sizeof(struct Token));
  uint8_t stack_idx=0;
  char binary_operators[9]="&|°+-/*^";
  char digits[11]="0123456789";
  char *source_code_pointer=source_code;
  while(*source_code_pointer != '\0') {
    if(*source_code_pointer == ' ') source_code_pointer += 1;
    else if(*source_code_pointer >= '0' && *source_code_pointer <= '9') {
      size_t n = strspn(source_code_pointer, digits);
      push(token_stack, make_token(INT, strndup(source_code_pointer, n)), &stack_idx);
      source_code_pointer+=n;
    }
    else {
      switch(*source_code_pointer) {
      case '|':
	push(token_stack, make_token(OR, strndup(source_code_pointer,1)), &stack_idx);
	break;
      case '&':
	push(token_stack, make_token(AND, strndup(source_code_pointer,1)), &stack_idx);
	break;
      case '!':
	push(token_stack, make_token(NOT, strndup(source_code_pointer,1)), &stack_idx);
	break;
      case '+':
	if(source_code == source_code_pointer
	   || *(source_code_pointer-1) == '('
	   || strchr(binary_operators, *(source_code_pointer-1)) != 0) {
	  push(token_stack, make_token(PREF_PLUS, "°"), &stack_idx);
	}
	push(token_stack, make_token(PLUS, strndup(source_code_pointer, 1)), &stack_idx);
	break;
      case '-':
	if(source_code == source_code_pointer
	   || *(source_code_pointer-1) == '('
	   || strchr(binary_operators, *(source_code_pointer-1)) != 0) {
	  push(token_stack, make_token(NEGATE, "$"), &stack_idx);
	}
	else {
	  push(token_stack, make_token(MINUS, strndup(source_code_pointer, 1)), &stack_idx);
	}
	break;
      case '/':
	push(token_stack, make_token(SLASH, strndup(source_code_pointer, 1)), &stack_idx);
	break;
      case '*':
	push(token_stack, make_token(STAR, strndup(source_code_pointer, 1)), &stack_idx);
	break;
      case '(':
	push(token_stack, make_token(O_PAREN, strndup(source_code_pointer, 1)), &stack_idx);
	break;
      case ')':
	push(token_stack, make_token(C_PAREN, strndup(source_code_pointer, 1)), &stack_idx);
	break;
      default:
	fprintf(stderr, "[lexer] Error: token not supported (%c)\n", *strndup(source_code_pointer, 1));
	exit(420);
      }
      source_code_pointer+=1;
    }
  }
  push(token_stack, make_token(EOS, ""), &stack_idx);
  return token_stack;
}
