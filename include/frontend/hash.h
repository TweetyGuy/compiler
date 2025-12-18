#ifndef HASH_H
#define HASH_H

#pragma once

#include <types.h>
#include <frontend/lexer.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


HashTable createTable(short elem_size, int size);
// void generateTable(HashTable* table, void* hashes, int size);
void generateTable(HashTable* table, token_t* hashes, int size);
uint32_t hash(token_t str, uint32_t seed);
uint32_t fnv1a(const void* data, size_t len);
void deleteTable(HashTable table);
token_t indexTable(HashTable table, token_t input);

#endif
