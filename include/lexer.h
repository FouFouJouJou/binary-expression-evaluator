// int array[50]
// [token {}, token {}, token {}, token { eof }]
// i

#ifndef __LEXER_H__
#define __LEXER_H__
#include <stdint.h>
enum TokenType {
  INT=0
  ,PLUS
  ,MINUS
  ,SLASH
  ,STAR
  ,O_PAREN
  ,C_PAREN
  ,AND
  ,OR
  ,XOR
  ,NOT
  ,EOS
  ,NEGATE='$'
  ,PREF_PLUS='#'
};

struct Token {
  enum TokenType type;
  char *value;
};

struct Token *make_token(enum TokenType token_type, char *value);
void free_token(struct Token *token);
void free_tokens(struct Token *tokens);
char *token_type_to_string(enum TokenType token_type);
void printf_token(struct Token token);
void printf_tokens(struct Token *tokens, void(*printf_token)(struct Token token));
void push(struct Token stack[], struct Token *token, uint8_t *stack_idx);
struct Token *tokenize(char *source_code);
#endif
