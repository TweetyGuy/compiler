#ifndef LEXER_H
#define LEXER_H

#pragma once

#include <types.h>
#include <hash.h>
#include <errors.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


void addToken(token_t token, token_list_t* token_list);
int isAtEnd(file_t* file);

int isNum(char c);
int isAlpha(char c);
int isAlphaNum(char c);

void number(file_t* file, token_list_t* token_list);
void identifier(file_t* file, token_list_t* token_list, HashTable table);
void literal();

void scanNextToken(file_t* file, token_list_t* token_list, HashTable table);
void lex(char* name, char* buffer, int size);

#endif
