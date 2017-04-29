#pragma once

#include "..\Base\StringEx.h"

typedef struct PPToken PPToken;

typedef struct
{
  PPToken** pItems;
  int Size;
  int Capacity;
} TokenArray;

#define TOKENARRAY_INIT {0, 0, 0}

int      TokenArray2_Reserve(TokenArray* p, int nelements);
int      TokenArray2_Grow(TokenArray* p, size_t nelements);
void     TokenArray2_Pop(TokenArray* p);

PPToken* TokenArray2_PopFront(TokenArray* p);

PPToken*      TokenArray2_Top(TokenArray* p);
int      TokenArray2_Push(TokenArray* p, PPToken* pItem);
void     TokenArray2_Clear(TokenArray* p);
void     TokenArray2_Init(TokenArray* p);
TokenArray* TokenArray2_Create();
void     TokenArray2_Destroy(TokenArray* st);
void     TokenArray2_Delete(TokenArray* st);
void     TokenArray2_Swap(TokenArray* p1, TokenArray* p2);

PPToken*      TokenArray2_Begin(TokenArray* p);
PPToken*      TokenArray2_End(TokenArray* p);

//


bool TokenArray2_Contain(TokenArray *pArray, PPToken* pToken);

void TokenArray2_AppendCopy(TokenArray *pArrayTo, const TokenArray *pArrayFrom);
void TokenArray2_AppendMove(TokenArray *pArrayTo, TokenArray *pArrayFrom);
//void TokenArray2_AppendTokensCopy(TokenArray *pArray, Token** pToken, int len);
//void TokenArray2_AppendTokensMove(TokenArray *pArray, Token** pToken, int len);
void TokenArray2_Print(const TokenArray* tokens);

PPToken* TokenArray2_Find(const TokenArray *pArray, const char * lexeme);
void TokenArray2_Erase(TokenArray *pArray, int begin, int end);


///////////////////////////////




typedef struct TokenArrayMapItem
{
  struct MapItem2* pNext;
  unsigned int HashValue;
  String Key;
  TokenArray* pValue;
} TokenArrayMapItem;

typedef struct
{
  TokenArrayMapItem** pHashTable;
  unsigned int nHashTableSize;
  size_t  nCount;
} TokenArrayMap;


#define TOKENARRAYMAP_INIT { NULL, 0, 0 }

int TokenArrayMap_SetAt(TokenArrayMap* pMap,
                        const char* Key,
                        TokenArray* newValue);

bool TokenArrayMap_Lookup(const TokenArrayMap* pMap,
                          const char*  Key,
                          TokenArray** rValue);

bool TokenArrayMap_RemoveKey(TokenArrayMap* pMap,
                             const char*  Key);

void TokenArrayMap_Init(TokenArrayMap* p);
void TokenArrayMap_Destroy(TokenArrayMap* p);

TokenArrayMap*  TokenArrayMap_Create();
void TokenArrayMap_Delete(TokenArrayMap * p);

void TokenArrayMap_Swap(TokenArrayMap * pA, TokenArrayMap * pB);


typedef struct
{
  PPToken** pItems;
  int Size;
  int Capacity;
} TokenSet;
#define TOKENSET_INIT { NULL, 0, 0 }

int TokenSet_Add(TokenSet* p, PPToken* pItem);
void TokenSetAppendCopy(TokenSet *pArrayTo, const TokenSet *pArrayFrom);
PPToken* TokenSet_Find(const TokenSet *pArray, const char * lexeme);
void TokenSet_Destroy(TokenSet *pArray);

void SetIntersection(const TokenSet *p1,
                     const TokenSet *p2,
                     TokenSet *pResult);