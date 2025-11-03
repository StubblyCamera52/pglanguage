#include "lexer.h"
#include "token.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int is_at_end(Lexer *lexer) {
    return *lexer->current == '\0';
}

static char advance(Lexer *lexer) {
    lexer->current++;
    return lexer->current[-1];
}

static char peek(Lexer *lexer) {
    return *lexer->current;
}

static char peek_next(Lexer *lexer) {
    if (is_at_end(lexer)) return '\0';
    return lexer->current[1];
}

static int match(Lexer *lexer, char expected) {
    if (is_at_end(lexer)) return 0;
    if (peek(lexer)!=expected) return 0;
    lexer->current++;
    return 1;
}

static void skip_whitespace(Lexer *lexer) {
    for (;;) {
        char c = peek(lexer);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance(lexer);
                break;
            case '\n':
                lexer->line++;
                advance(lexer);
                break;
            case '/':
                if (peek_next(lexer) == '/') {
                    while (peek(lexer) != '\n' && !is_at_end(lexer)) advance(lexer);
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

static Token make_token(Lexer *lexer, TokenType type) {
    Token token;
    token.type = type;
    token.start = lexer->start;
    token.length = (int)(lexer->current - lexer->start);
    token.line = lexer->line;
    return token;
}

static Token error_token(const char *message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = 0;
    return token;
}

// keywords and literals

static TokenType check_keyword(Lexer *lexer, int start, int length, const char *rest, TokenType type) {
    if (memcmp(lexer->start + start, rest, length) == 0) {
            return type;
        }
    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type(Lexer *lexer) {
    switch (lexer->start[0]) {
        case 'v': {
            return check_keyword(lexer, 1, 2, "ar", TOKEN_VAR);
        } // "var"
        case 'i': {
            return check_keyword(lexer, 1, 1, "f", TOKEN_IF);
        }
        case 'w': {
          return check_keyword(lexer, 1, 4, "hile", TOKEN_WHILE);
        }
        case 'p': {
          return check_keyword(lexer, 1, 7, "rintenv", TOKEN_PRINTENV);
        }
        case 'e': {
          return check_keyword(lexer, 1, 2, "nd", TOKEN_END);
        }
    }
    return TOKEN_IDENTIFIER;
}

static Token string(Lexer *lexer) {
    while (peek(lexer) != '"' && !is_at_end(lexer)) {
        if (peek(lexer) == '\n') lexer->line++;
        advance(lexer);
    }

    if (is_at_end(lexer)) return error_token("Unterminated string.");

    advance(lexer); // for closing quote
    return make_token(lexer, TOKEN_STRING);
}

static Token number(Lexer *lexer) {
    while (isdigit(peek(lexer))) advance(lexer);

    if (peek(lexer) == '.' && isdigit(peek_next(lexer))) {
        advance(lexer); // consume "."
        while (isdigit(peek(lexer))) advance(lexer);
    }

    return make_token(lexer, TOKEN_NUMBER);
}

static Token identifier(Lexer *lexer) {
    TokenType type = identifier_type(lexer);
    while (isalnum(peek(lexer)) || peek(lexer) == '_') advance(lexer);
    return make_token(lexer, type);
}

void init_lexer(Lexer *lexer, const char *source) {
    lexer->start = source;
    lexer->current = source;
    lexer->line = 1;
}

Token next_token(Lexer *lexer) {
    skip_whitespace(lexer);
    lexer->start = lexer->current;

    if (is_at_end(lexer)) return make_token(lexer, TOKEN_EOF);

    char c = advance(lexer);

    if (isalpha(c) || c == '_') return identifier(lexer);
    if (isdigit(c)) return number(lexer);

    switch (c) {
        case '=': {
          if (match(lexer, '=')) {
            return make_token(lexer, TOKEN_EQUALEQUAL);
          } else return make_token(lexer, TOKEN_EQUAL);
        };
        case ';': return make_token(lexer, TOKEN_SEMICOLON);
        case '+': return make_token(lexer, TOKEN_PLUS);
        case '-': return make_token(lexer, TOKEN_MINUS);
        case '*': return make_token(lexer, TOKEN_MULTIPLY);
        case '/': return make_token(lexer, TOKEN_DIVIDE);
        case '<': return make_token(lexer, TOKEN_LESS);
        case '>': return make_token(lexer, TOKEN_GREATER);
        case '{': return make_token(lexer, TOKEN_LEFTBRACE);
        case '}': return make_token(lexer, TOKEN_RIGHTBRACE);
        case '"': return string(lexer);
    }

    return error_token("unexpected character");
}
