#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>
#include <stdlib.h>
#include <errors.h>
#include <stdio.h>
#include <ctype.h>

typedef enum token_type {
  OPEN_PAREN,               // (
  CLOSE_PAREN,              // )
  OPEN_BRACE,               // {
  CLOSE_BRACE,              // }
  PLUS,                     // +
  MINUS,                    // -
  TIMES,                    // *
  SLASH,                    // /
  MODULO,                   // %
  NOT,                      // !
  COMMA,                    // ,
  SEMICOLON,                // ;
  EQUAL,                    // =
  GREATER,                  // >
  LESS,                     // <

  POST_INC,                 // a++
  PRE_INC,                  // ++a
  POST_DEC,                 // a--
  PRE_DEC,                  // --a

  EQUAL_EQUAL,              // ==
  NOT_EQUAL_TO,             // !=
  GREATER_EQUAL,            // >=
  LESS_EQUAL,               // <=

  AND,                      // &&
  OR,                       // ||
  
  SLASH_SLASH,              // //
  
  IDENTIFIER,
  STRING,
  
  AUTO,
  BREAK,
  CASE,
  CHAR,
  CONST,
  CONTINUE,
  DEFAULT,
  DO,
  DOUBLE,
  ELSE,
  ENUM,
  EXTERN,
  FLOAT,
  FOR,
  GOTO,
  IF,
  INT,
  LONG,
  REGISTER,
  RETURN,
  SHORT,
  SIGNED,
  SIZEOF,
  STATIC,
  STRUCT,
  SWITCH,
  TYPEDEF,
  UNION,
  UNSIGNED,
  VOID,
  VOLATILE,
  WHILE

} token_type_t;

typedef struct token {
  uint8_t type;
  const char* lexeme;
  uint16_t line;
  uint8_t column;
} token_t;

typedef struct file {
  char* name;
  int start;
  int current;
  int line;
  int size;
  char* buffer;
} file_t;

typedef struct token_list {
  int size;
  int use;
  token_t* tokens;
} token_list_t;

void addToken(token_t token, token_list_t* token_list);
int isAtEnd(file_t* file);
void scanNextToken(file_t* file, token_list_t* token_list);
void lex(char* name, char* buffer, int size);

#endif
