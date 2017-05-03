
#pragma once

#include "Result.h"
#include <stdbool.h>
#include <CRTDEFS.H>
#include <stdlib.h>

typedef struct
{
    void** pItems;
    size_t size;
    size_t capacity;

} Array;

#define ARRAY_INIT { NULL , 0 , 0 }

Result Array_Reserve(Array* p, size_t nelements);
Result Array_Grow(Array* p, size_t nelements);
void Array_Pop(Array* p, void(*pfDestroyData)(void*));
void* Array_PopGet(Array* p);
void* Array_Top(Array* p);
Result Array_Push(Array* p, void* pItem);
void Array_Clear(Array* p, void(*pfDestroyData)(void*));
Result Array_Init(Array* p);
Result Array_Create(Array** pp);
void Array_Destroy(Array* st, void(*pfDestroyData)(void*));
void Array_Delete(Array* st, void(*pfDestroyData)(void*));
void Array_Swap(Array* p1, Array* p2);
void* Array_PopFront(Array* p);
void* Array_RemoveAt(Array* p, int index);
//////


typedef struct
{
    const char** pItems;
    size_t size;
    size_t capacity;

} StrArray;

#define STRARRAY_INIT { NULL , 0 , 0 }

Result StrArray_Reserve(StrArray* p, size_t nelements);
Result StrArray_Push(StrArray* p, const char* pItem);
void StrArray_Clear(StrArray* p);
Result StrArray_Init(StrArray* p);
void StrArray_Destroy(StrArray* st);


typedef struct
{
    int* pItems;
    size_t size;
    size_t capacity;

} ArrayInt;

Result ArrayInt_Reserve(ArrayInt* p, size_t nelements);

bool ArrayInt_IsEmpty(ArrayInt* p);

int ArrayInt_Pop(ArrayInt* p);

int ArrayInt_Top(ArrayInt* p);

Result ArrayInt_Push(ArrayInt* p, int pItem);

void ArrayInt_Clear(ArrayInt* p);

Result ArrayInt_Init(ArrayInt* p);

Result ArrayInt_Create(ArrayInt** pp);

void ArrayInt_Destroy(ArrayInt* st);

void ArrayInt_Delete(ArrayInt* st);


#define ARRAYOF(TYPES, TYPE)\
inline void TYPES##_Push(TYPES* p, TYPE* pItem)\
{\
  Array_Push((Array*)p, pItem);\
}\
inline void TYPES##_Destroy(TYPES * p)\
{\
  Array_Destroy((Array*)p, TYPE##_DeleteVoid);\
}\
inline TYPES* TYPES##_Create()\
{\
  TYPES* p = (TYPES*)malloc(sizeof * p);\
  if (p)\
  {\
    Array_Init((Array*)p); \
  }\
  return p;\
}\
inline Result TYPES##_Reserve(TYPES* p, size_t n)\
{\
    return Array_Reserve((Array*)p, n); \
}\
inline void TYPES##_Delete(TYPES * p)\
{\
  if (p)\
  {\
    Array_Destroy((Array*)p, TYPE##_DeleteVoid); \
    free(p);\
  }\
}

