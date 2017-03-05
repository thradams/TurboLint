#pragma once


typedef struct
{
	void** pItems;
	int size;
	int capacity;
} Array2;

#define ARRAY2_INIT {0, 0, 0}

int Array2_Reserve(Array2* p, int nelements);
int Array2_Grow(Array2* p, int nelements);
void* Array2_Pop(Array2* p);
void* Array2_PopFront(Array2* p);
void* Array2_Top(Array2* p);
int   Array2_Push(Array2* p, void* pItem);
void  Array2_Clear(Array2* p);
void  Array2_Init(Array2* p);
Array2* Array2_Create();
void Array2_Destroy(Array2* st);
void Array2_Delete(Array2* st);
void Array2_Swap(Array2* p1, Array2* p2);
void* Array2_RemoveAt(Array2* p, int index);
