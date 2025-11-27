// TODO
// call the lex function on each file
// fix reallocarray error handling

#include <driver.h>
#include <string.h>

int parse(int argc, char** argv)
{
  char* outfile = "a.out";
  char** files = malloc(1);
  int n = 0;

  if (argc < 2)
  {
    printf("Error: Not enough arguments to compile. Specify at least one input file.\n");
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    if (strcmp("-o", argv[i]) == 0)
    {
      if (i + 1 < argc)
      {
        printf("outfile = %s\n", argv[i+1]);
        outfile = argv[i+1];
        i++;
      }
      else
      {
        printf("Error: Not enough arguments after -o. Specify a name.\n");
        return 1;
      }
    }
    else
    {
      n++;

      if (reallocarray(files, n, sizeof(char*)) == NULL)
      {
        printf("Error: Failed to add file %s to compile list.\n", argv[i]);
        return 1;
      }

      files[n-1] = argv[i];
    }
  }
  preprocess(files, n);
  compile(files, n, outfile);
  free(files);

  return 0;
}

void preprocess(char** files, int n)
{
  for (int i = 0; i < n; i++)
  {
    int gcc_cmd = sizeof("gcc -E -P -o ");
    int file_len = strlen(files[i]);
    char* cmd = malloc(gcc_cmd + sizeof(".i") + 2 * file_len);
    strcpy(cmd, "gcc -E -P -o ");
    strcpy(cmd + gcc_cmd - 1, files[i]);
    strcpy(cmd + gcc_cmd - 1 + file_len - 2, ".i ");
    strcpy(cmd + gcc_cmd - 1 + file_len - 2 + strlen(".i "), files[i]);
    system(cmd);
    free(cmd);
    files[i][strlen(files[i]) - 1] = 'i';
  }
}

int compile(char** files, int n, char* outfile)
{
  for (int i = 0; i < n; i++)
  {
    FILE* fd = fopen(files[i], "r");
    if (fd == 0)
    {
      printf("Error: Failed to open file %s.\n", files[i]);
      return 1;
    }

    int len;
    fseek(fd, 0, SEEK_END);
    len = ftell(fd);
    rewind(fd);
    fseek(fd, 0, SEEK_SET);

    char* buffer = malloc(len);
    if (buffer == 0)
    {
      printf("Error: Failed to malloc buffer to read file %s.\n", files[i]);
      return 1;
    }

    fread(buffer, 1, len, fd);
    lex(files[i], buffer, len);

    free(buffer);
    fclose(fd);
  }

  return 0;
}

int main(int argc, char *argv[]) {  return parse(argc, argv); }
