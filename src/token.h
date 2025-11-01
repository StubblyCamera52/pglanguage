#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    // literals
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,

    // single char tokens
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_SEMICOLON,
    TOKEN_LEFTBRACE,
    TOKEN_RIGHTBRACE,

    // single or maybe multi char tokens
    TOKEN_EQUAL,
    TOKEN_EQUALEQUAL,
    TOKEN_LESS,

    // keywords
    TOKEN_VAR,
    TOKEN_IF,

    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    const char *start; // original text start pos
    int length;
    int line;
} Token ;

#endif
