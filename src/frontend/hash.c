#include <frontend/hash.h>
#include <stdlib.h>

HashTable createTable(short elem_size, int size)
{
  HashTable hashTable = {
    .table    = malloc(elem_size * size),
    .elem_size = elem_size,
    .size     = size,
  };

  memset(hashTable.table, 0, hashTable.elem_size * hashTable.size);
  return hashTable;
}

void generateTable(HashTable* table, token_t* hashes, int size)
{
  // make a table to check for double indexes
  int use_size = table->size * sizeof(int);
  int use[use_size];
  memset(use, 0, use_size);

  // loop for each member of the possible hash lookup values given
  for (int i = 0; i < size; i++)
  {
    // hash the lookup value
    uint32_t code = hash(hashes[i] /*+ (i * table->elem_size) */, table->seed) % table->size;
    memcpy(&table->table[code], &hashes[i], sizeof(token_t));
    printf("code : %d; lexeme : %s\n", code, hashes[i].lexeme);
    // check if its used more than once, if so increment the seed and reset the loop and tables
    if (use[code]++ >= 1)
    {
      table->seed++;
      i = -1;
      memset(use, 0, use_size);
      memset(table->table, 0, table->size * table->elem_size);
      printf("\n----reset----\n");
    }
  }
}

uint32_t hash(token_t tok, uint32_t seed)
{
  char* front = tok.lexeme;
  char* back = tok.lexeme + tok.len - 2; // works idk why

  uint32_t input = 0;
  input = *(uint16_t*)back;
  input <<= 16;
  input |= *(uint16_t*)front;

  input += seed;

  uint32_t code = fnv1a(&input, 4);
  return code;
}

uint32_t fnv1a(const void* data, size_t len)
{
    uint32_t hash = 2166136261u;
    const unsigned char* p = data;

    for (size_t i = 0; i < len; i++) {
        hash ^= p[i];
        hash *= 16777619u;
    }
    return hash;
}

void deleteTable(HashTable table)
{
  free(table.table);
}

token_t indexTable(HashTable table, token_t input)
{
  uint32_t code = hash(input, table.seed) % table.size;
  token_t token = table.table[code];
  if (strncmp(token.lexeme, input.lexeme, input.len) != 0) token.type = NIL;
  return token;
}
