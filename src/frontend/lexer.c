#include <lexer.h>

token_t tokens[32] = {
  { AUTO, "auto", 4},
  { BREAK, "break", 5},
  { CASE, "case", 4},
  { CHAR, "char", 4},
  { CONST, "const", 5},
  { CONTINUE, "continue", 8},
  { DEFAULT, "default", 7},
  { DO, "do", 2},
  { DOUBLE, "double", 6},
  { ELSE, "else", 4},
  { ENUM, "enum", 4},
  { EXTERN, "extern", 6},
  { FLOAT, "float", 5},
  { FOR, "for", 3},
  { GOTO, "goto", 4},
  { IF, "if", 2},
  { INT, "int", 3},
  { LONG, "long", 4},
  { REGISTER, "register", 8},
  { RETURN, "return", 6},
  { SHORT, "short", 5},
  { SIGNED, "signed", 6},
  { SIZEOF, "sizeof", 6},
  { STATIC, "static", 6},
  { STRUCT, "struct", 6},
  { SWITCH, "switch", 6},
  { TYPEDEF, "typedef", 7},
  { UNION, "union", 5},
  { UNSIGNED, "unsigned", 8},
  { VOID, "void", 4},
  { VOLATILE, "volatile", 8},
  { WHILE, "while", 5}
};

// append a given token to the end of the token_list
void addToken(token_t token, token_list_t* token_list)
{
  if (token_list->size == 0) token_list->size = 256;
  token_list->use++;
  // manage token_list resizes
  if (token_list->use >= token_list->size)
  {
    token_list->size *= 2;
    token_list->tokens = reallocarray(token_list->tokens, token_list->size, sizeof(token_t));
  }

  token_list->tokens[token_list->use - 1] = token;
}

int isAtEnd(file_t* file)
{
  return file->current >= file->size - 1;
}

char advance(file_t* file)
{
  return file->data[file->current++];
}

char peek(file_t* file)
{
  if (isAtEnd(file)) return '\0';
  return file->data[file->current];
}

int isAlpha(char c)
{
  return (c > 64 && c < 91) || (c > 96 && c < 123);
}

int isNum(char c)
{
  return (c > 47 && c < 58);
}

int isAlphaNum(char c)
{
  return isAlpha(c) || isNum(c);
}

void number(file_t* file, token_list_t* token_list)
{
  char c = file->current;
  token_type_t type = INT;
  do
  {
    if (c == '.')
    {
      if (type != INT)
        error(file->name, file->data, file->size, file->line, file->current, "Invalid Expression. More than one use of '.' in number.");
      else
        type = DOUBLE;
    }
    if (file->data[file->current + 1] == 'f' && type == DOUBLE)
      type = FLOAT;
    c = advance(file);
  }
  while (isNum(c) || c == '.' || c == 'f');

  addToken((token_t){type, 
      &file->data[file->start],
      file->current - file->start - 1, // account for the fact that current was incremented after return
      file->line, file->start}, 
      token_list
  );
}

void identifier(file_t* file, token_list_t* token_list, HashTable table)
{
  for (char c = advance(file); isAlphaNum(c); c = advance(file));

  size_t len = file->current - 1 - file->start;
  char* lexeme = file->data + file->start;

  token_t token = {
    .type   = IDENTIFIER, 
    .lexeme = lexeme,
    .len    = len,
    .line   = file->line,
    .column = file->start
  };

  if (len < 2 || len > 8)
  {
    addToken(token, token_list);
    return;
  } 

  token_t index = indexTable(table, token);
  if (index.type == NIL)
    addToken(token, token_list);
  else 
    addToken(index, token_list);
}

void literal()
{
}

void scanNextToken(file_t* file, token_list_t* token_list, HashTable table)
{
  char c = advance(file);
  switch(c)
  {
    case '(': 
    {
      addToken((token_t){OPEN_PAREN, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case ')':
    {
        addToken((token_t){CLOSE_PAREN, 0, 0, file->line, file->start}, token_list);
        break; 
    }
    case '{':
    {
      addToken((token_t){OPEN_BRACE, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '}':
    {
      addToken((token_t){CLOSE_BRACE, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '+':
    {
      addToken((token_t){PLUS, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '-':
    {
      addToken((token_t){MINUS, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '*':
    {
      addToken((token_t){TIMES, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '/':
    {
      if (file->data[file->current + 1] == '/')
      {
        addToken((token_t){SLASH_SLASH, 0, 0, file->line, file->start}, token_list);
        file->line++;
      }
      else
        addToken((token_t){SLASH, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '%':
    {
      addToken((token_t){MODULO, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '!':
    {
      addToken((token_t){NOT, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case ',':
    {
      addToken((token_t){COMMA, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case ';':
    {
      addToken((token_t){SEMICOLON, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '=':
    {
      addToken((token_t){EQUAL, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '>':
    {
      addToken((token_t){GREATER, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '<':
    {
      addToken((token_t){LESS, 0, 0, file->line, file->start}, token_list);
      break;
    }
    case '\n':
      file->line++;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\"':
    {
      literal();
      break;
    }
    case '\'':
    {
      literal();
      break;
    }
    default:
    {
      if (isNum(c) || c == '.')
      {
        number(file, token_list);
        // token_t token = token_list->tokens[token_list->use - 1];
        // printf("New %s token %.*s\n", (token.type == INT) ? "int" : (token.type == DOUBLE) ? "double" : "float", token.len, token.lexeme);
        break;
      }

      else if (isAlpha(c))
      {
        identifier(file, token_list, table);
        // token_t token = token_list->tokens[token_list->use - 1];
        // printf("New identifier token %.*s\n", token.len, token.lexeme);
        break;
      }

      error(file->name, file->data, file->size, file->line, file->start, "unexpected token.");
      break;
    }
  }
}

void lex(char* name, char* buffer, int size)
{

  HashTable table = createTable(sizeof(token_t), 32 * 4);
  generateTable(&table, tokens, 32);
  printf(".seed = %d\n", table.seed);

  file_t* file = malloc(sizeof(file_t));
  *file = (file_t){
    .name = name,
    .start = 0,
    .current = 0,
    .line = 1,
    .size = size,
    .data = buffer
  };

  token_list_t* token_list = malloc(sizeof(token_list_t));
  *token_list = (token_list_t){
    .size = 256,
    .use = 0,
    .tokens = calloc(token_list->size, sizeof(token_t))
  };

  while(!isAtEnd(file))
  {
    file->start = file->current;
    scanNextToken(file, token_list, table);
  }

  deleteTable(table);

  free(token_list);
  free(file);
}
