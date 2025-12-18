#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdlib.h>

typedef enum token_type {
  NIL,                      // FALSE TOKEN

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
  char* lexeme;
  uint8_t len;
  uint32_t line;
  uint8_t column;
} token_t;

typedef struct file {
  char* name;
  int start;
  int current;
  int line;
  int size;
  char* data;
} file_t;

typedef struct token_list {
  int size;
  int use;
  token_t* tokens;
} token_list_t;

typedef struct {
  token_t* table;
  size_t elem_size;
  int size;
  uint32_t seed;
} HashTable;

#endif
