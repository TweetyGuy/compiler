#ifndef ERRORS_H
#define ERRORS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int hasError;

// file name, ptr to file data, size of file data, erroneous line line, column of error, error message
void error(char* name, char* data, int size, int line, int column, char* what);
// file name, ptr to file data, size of file data, erroneous line line, column of error, error message
void warning(char* name, char* data, int size, int line, int offset, char* what);

#endif
