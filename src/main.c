#include "interpreter.h"
#include "lexer.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static char *read_file(const char *path) {
  FILE *file = fopen(path, "rb");

  if (!file) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(1);
  }

  // find the size of the source file
  fseek(file, 0L, SEEK_END); // seek the end of the file
  size_t size =
      ftell(file); // print byte offset at end (equates to the size of the file)
  rewind(file);    // rewind the cursor back to the beginning

  char *buffer = (char *)malloc(size + 1); // +1 for the string terminator

  if (!buffer) {
    fprintf(stderr, "Not enough memory to read file \"%s\"\n", path);
    exit(1);
  }

  fread(buffer, sizeof(char), size, file); // read the file to the buffer
  buffer[size] =
      '\0'; // add the null terminator so we dont run into issues later

  fclose(file); // should always close files after reading them

  return buffer;
}

static const char *token_type_name(TokenType type) {
  switch (type) {
  case TOKEN_IDENTIFIER:
    return "IDENTIFIER";
  case TOKEN_NUMBER:
    return "NUMBER";
  case TOKEN_STRING:
    return "STRING";
  case TOKEN_PLUS:
    return "PLUS";
  case TOKEN_MINUS:
    return "MINUS";
  case TOKEN_EQUAL:
    return "EQUAL";
  case TOKEN_VAR:
    return "VAR";
  case TOKEN_SEMICOLON:
    return "SEMICOLON";
  case TOKEN_EOF:
    return "EOF";
  case TOKEN_IF:
    return "IF";
  default:
    return "OTHER";
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <source-file>\n", argv[0]);
    return 1;
  }

  char *source = read_file(argv[1]);

  Lexer lexer;
  init_lexer(&lexer, source);

  // token array (has to be dynamic bc idk the size)
  size_t capacity = 16;
  size_t count = 0;
  Token *tokens = (Token *)malloc(capacity * sizeof(Token));

  for (;;) {
    Token token = next_token(&lexer);

    if (count >= capacity) { // resize the array if we need more space
      capacity += 16;
      Token *new_tokens = (Token *)realloc(tokens, capacity * sizeof(Token));
      tokens = new_tokens;
    }

    tokens[count++] = token;

    printf("%d: %.*s (%s)\n", token.line, token.length, token.start,
           token_type_name(token.type));
    if (token.type == TOKEN_EOF)
      break;
  }

  Enviroment *env = new_env();
  interpret(tokens, env, count);

  free(tokens);
  free(source);
  return 0;
}
