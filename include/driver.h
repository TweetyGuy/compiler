#ifndef DRIVER_H
#define DRIVER_H

#include <errors.h>
#include <lexer.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse(int argc, char** argv);
void preprocess(char** files, int n);
int compile(char** files, int n, char* outfile);

#endif
