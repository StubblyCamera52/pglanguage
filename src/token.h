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
    TOKEN_DIVIDE,
    TOKEN_MULTIPLY,
    TOKEN_SEMICOLON,
    TOKEN_LEFTBRACE,
    TOKEN_RIGHTBRACE,

    // single or maybe multi char tokens
    TOKEN_EQUAL,
    TOKEN_EQUALEQUAL,
    TOKEN_LESS,
    TOKEN_GREATER,

    // keywords
    TOKEN_VAR,
    TOKEN_IF,
    TOKEN_WHILE,

    TOKEN_EOF,
    TOKEN_ERROR,

    // comands
    TOKEN_PRINTENV,
    TOKEN_END,
} TokenType;

typedef struct {
    TokenType type;
    const char *start; // original text start pos
    int length;
    int line;
} Token ;

#endif
