#include <errors.h>

char* grabline(char* data, int size, int number, int* linesize, int* newline)
{
  int newlines = 0;
  char* ret = data;
  for (int i = 0; i < size; i++)
  {
    if (data[i] == '\n')
    {
      newlines++;
      if (newlines == number - 1) // line numbers start at 1 so - 1
      {
        ret = data + i + 1; // account for \n. starts the ret string at the next line
        *newline = i + 1;
      }

      if (newlines == number)
      {
        *linesize = (char*)(data + i) - ret;
        return ret;
      }
    }
  }

  return NULL;
}

void error(char* name, char* data, int size, int line, int offset, char* what)
{
  hasError = 1;
  int line_size = 0;
  int newline = 0;
  char* line_data = grabline(data, size, line, &line_size, &newline);
  int column = offset - newline;
  printf("%s:%d:%d: Error: %s\n\n\t%d | %.*s\n", name, line, column, what, line, line_size, line_data);
  printf("\t    ");
  for (int i = 0; i < column; i++)
    printf(" ");
  printf("^");
  for (int i = 0; i < line_size - column - 1; i++)
    printf("~");
  printf("\n");
}

void warning(char* name, char* data, int size, int line, int offset, char* what)
{
  hasError = 1;
  int line_size = 0;
  int newline = 0;
  char* line_data = grabline(data, size, line, &line_size, &newline);
  int column = offset - newline;
  printf("%s:%d:%d: Warning: %s\n\n\t%d | %.*s\n", name, line, column, what, line, line_size, line_data);
  printf("\t    ");
  for (int i = 0; i < column; i++)
    printf(" ");
  printf("^");
  for (int i = 0; i < line_size - column - 1; i++)
    printf("~");
  printf("\n");
}
