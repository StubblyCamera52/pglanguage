#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    const char *start;
    const char *current;
    int line;
} Lexer ;

void init_lexer(Lexer *lexer, const char *source);
Token next_token(Lexer *lexer);

#endif
