#ifndef DRIVER_H
#define DRIVER_H

#include <lexer.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errors.h>

int haserror = 0;

int parse(int argc, char** argv);
void preprocess(char** files, int n);
int compile(char** files, int n, char* outfile);

#endif
