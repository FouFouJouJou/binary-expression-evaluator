#ifndef __CLI_H__
#define __CLI_H__

#define TOTAL_OPERATIONS 4

typedef void(*action)(char *);

void eval(char *expression);
void lex(char *expression);
void postfix(char *expression);
void all(char *expression);
void help();

static const char *operations[] = {"eval", "tokenize", "postfix", "all"};
static const action actions[] = {eval, lex, postfix, all};


#endif // __CLI_H__


