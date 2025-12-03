// TODO
// get file stream and read each line
// continue if space
// read until it hits a single line character, +-*/=<>!|&^()[]{}.,:;
#include <lexer.h>

void addToken(token_t token, token_list_t* token_list)
{
  token_list->use++;
  if (token_list->use >= token_list->size)
  {
    token_list->size += 4;
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
  return file->buffer[file->current++];
}

void scanNextToken(file_t* file, token_list_t* token_list)
{
  char c = advance(file);
  switch(c)
  {
    case '(': 
    {
      addToken((token_t){OPEN_PAREN, 0, file->line, file->start}, token_list);
      break;
    }
    case ')':
    {
        addToken((token_t){CLOSE_PAREN, 0, file->line, file->start}, token_list);
        break; 
    }
    case '{':
    {
      addToken((token_t){OPEN_BRACE, 0, file->line, file->start}, token_list);
      break;
    }
    case '}':
    {
      addToken((token_t){CLOSE_BRACE, 0, file->line, file->start}, token_list);
      break;
    }
    case '+':
    {
      addToken((token_t){PLUS, 0, file->line, file->start}, token_list);
      break;
    }
    case '-':
    {
      addToken((token_t){MINUS, 0, file->line, file->start}, token_list);
      break;
    }
    case '*':
    {
      addToken((token_t){TIMES, 0, file->line, file->start}, token_list);
      break;
    }
    case '/':
    {
      if (file->buffer[file->current + 1] == '/')
      {
        addToken((token_t){SLASH_SLASH, 0, file->line, file->start}, token_list);
        file->line++;
      }
      else
        addToken((token_t){SLASH, 0, file->line, file->start}, token_list);
      break;
    }
    case '%':
    {
      addToken((token_t){MODULO, 0, file->line, file->start}, token_list);
      break;
    }
    case '!':
    {
      addToken((token_t){NOT, 0, file->line, file->start}, token_list);
      break;
    }
    case ',':
    {
      addToken((token_t){COMMA, 0, file->line, file->start}, token_list);
      break;
    }
    case ';':
    {
      addToken((token_t){SEMICOLON, 0, file->line, file->start}, token_list);
      break;
    }
    case '=':
    {
      addToken((token_t){EQUAL, 0, file->line, file->start}, token_list);
      break;
    }
    case '>':
    {
      addToken((token_t){GREATER, 0, file->line, file->start}, token_list);
      break;
    }
    case '<':
    {
      addToken((token_t){LESS, 0, file->line, file->start}, token_list);
      break;
    }
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
    {
      file->line++;
      break;
    }
    default:
    {
      error(file->name, file->buffer, file->size, file->line, file->start, "unexpected token.");
      break;
    }
  }
  // hash map
}

void lex(char* name, char* buffer, int size)
{
  file_t* file = malloc(sizeof(file_t));
  *file = (file_t){
    .name = name,
    .start = 0,
    .current = 0,
    .line = 1,
    .size = size,
    .buffer = buffer
  };

  token_list_t* token_list = malloc(sizeof(token_list_t));
  *token_list = (token_list_t){
    .size = 0,
    .use = 0,
    .tokens = calloc(token_list->size, sizeof(token_t))
  };

  while(!isAtEnd(file))
  {
    file->start = file->current;
    scanNextToken(file, token_list);
  }

  free(token_list);
  free(file);
}
