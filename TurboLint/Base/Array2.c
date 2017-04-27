
#include <stdlib.h>
#include "Array2.h"
#include <string.h>

#define ASSERT(X)

int Array2_Reserve(Array2* p, int nelements)
{
	int result = -1;
	if (nelements > p->capacity)
	{
		void** pnew = p->pItems;
		pnew = (void**)realloc(pnew, nelements * sizeof(void*));
		if (pnew)
		{
			p->pItems = pnew;
			p->capacity = nelements;
			result = nelements;
		}
	}
	return result;
}


int Array2_Grow(Array2* p, int nelements)
{
	int result = -1;
	if (nelements > p->capacity)
	{
		int new_nelements = p->capacity + p->capacity / 2;
		if (new_nelements < nelements)
		{
			new_nelements = nelements;
		}
		result = Array2_Reserve(p, new_nelements);
	}
	else
	{
		result = p->capacity;
	}
	return result;
}

void* Array2_Pop(Array2* p)
{
	ASSERT(p->size > 0);

	void* pItem = p->pItems[p->size - 1];
	p->pItems[p->size - 1] = NULL;
	p->size--;
	return pItem;
}

void* Array2_Top(Array2* p)
{
	ASSERT(p->size > 0);
	return p->pItems[p->size - 1];
}

int Array2_Push(Array2* p, void* pItem)
{
	int result = Array2_Grow(p, p->size + 1);
	if (result >= 0)
	{
		p->pItems[p->size] = pItem;
		p->size++;
	}
	return result;
}

void Array2_Clear(Array2* p)
{
	for (int i = 0; i < p->size; i++)
	{
		//PPToken_Delete(p[i]->pItems[i]);
	}

	free(p->pItems);
	p->pItems = NULL;
	p->size = 0;
	p->capacity = 0;
}


void Array2_Init(Array2* p)
{
	Array2 temp = ARRAY2_INIT;
	*p = temp;
}

Array2* Array2_Create()
{
	Array2* p = (Array2*)malloc(sizeof * p);
	if (p)
	{
		Array2_Init(p);
	}
	return p;
}

void Array2_Destroy(Array2* st)
{
	Array2_Clear(st);
}

void Array2_Swap(Array2* p1, Array2* p2)
{
	Array2 temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void Array2_Delete(Array2* st)
{
	Array2_Destroy(st);
	free(st);
}

void* Array2_Begin(Array2* p)
{
	return p->pItems[0];
}

void* Array2_End(Array2* p)
{
	return p->pItems[p->size];
}

void* Array2_RemoveAt(Array2* p, int index)
{
	if (index != p->size - 1)
	{
		void* t = p->pItems[index];
		p->pItems[index] = p->pItems[p->size - 1];
		p->pItems[p->size - 1] = t;		
	}

	return Array2_Pop(p);
}

void* Array2_PopFront(Array2* p)
{
	void* pItem = NULL;
	ASSERT(p->size > 0);
	if (p->size > 0)
	{
		pItem = p->pItems[0];
		if (p->size > 1)
		{
			memmove(p->pItems, p->pItems + 1, sizeof(void*) * (p->size - 1));			
		}
		p->size--;
	}
	return pItem;
}




