 
#include "String2.h"
#include <stdlib.h>
#include <string.h>

const char * const String2_Empty_Constant = "";

int String2_Init(String2* pString, const char* sourceOpt)
{
	int length = -1;
	if (sourceOpt == NULL ||
		sourceOpt[0] == '\0')
	{
		*((const char**)pString) = String2_Empty_Constant;
		length = 0;
	}
	else
	{
		size_t sourceLen = strlen(sourceOpt);
		void * pNew = malloc(sizeof(char) * sourceLen + 1);
		if (pNew != 0)
		{
			memcpy(pNew, sourceOpt, sourceLen + 1);
			*((const char**)pString) = (const char*)pNew;
			length = (int)sourceLen;
		}
	}

	return length;
}

void String2_Destroy(String2* pString)
{
	if (*pString != String2_Empty_Constant)
	{
		free((void*)*pString);
	}
}

void String2_Swap(String2* pA, String2* pB)
{
	String2 tmp = *pA;
	*((const char**)pA) = *pB;
	*((const char**)pB) = tmp;
}

int String2_Set(String2 *pS1, const char* psz1)
{
	String2 local = STRING2_INIT;
	int i = String2_Init(&local, psz1);
	if (i >= 0)
	{
		String2_Swap(&local, pS1);
		String2_Destroy(&local);
	}
	return i;
}

static int IsEmptyStr_RemoveThis(const char*  psz)
{
	return psz == NULL || psz[0] == '\0';
}

int StrBuilder2_Init(StrBuilder2* p, size_t capacity)
{
	int result = -1;

	p->c_str = NULL;
	p->size = 0;
	p->capacity = 0;

	if (capacity > 0)
	{
		result = StrBuilder2_Reserve(p, capacity);
	}

	return result;
}

void StrBuilder2_Swap(StrBuilder2* str1,
	StrBuilder2* str2)
{
	StrBuilder2 temp_Moved = *str1;
	*str1 = *str2;
	*str2 = temp_Moved;
}

void StrBuilder2_Destroy(StrBuilder2* p)
{
	if (p)
	{
		free(p->c_str);
		p->c_str = NULL;
		p->size = 0;
		p->capacity = 0;
	}
}

int StrBuilder2_Reserve(StrBuilder2* p, size_t nelements)
{
	int r = p->capacity;

	if (nelements > p->capacity)
	{
		char* pnew = (char*)realloc(p->c_str,
			(nelements + 1) * sizeof(p->c_str[0]));

		if (pnew)
		{
			if (p->c_str == NULL)
			{
				pnew[0] = '\0';
			}

			p->c_str = pnew;
			p->capacity = nelements;
			r = p->capacity;
		}

		else
		{
			r = -1;
		}
	}

	return r;
}

static int StrBuilder2_Grow(StrBuilder2* p, size_t nelements)
{
	int r = p->capacity;

	if (nelements > p->capacity)
	{
		size_t new_nelements = p->capacity + p->capacity / 2;

		if (new_nelements < nelements)
		{
			new_nelements = nelements;
		}

		r = StrBuilder2_Reserve(p, new_nelements);
	}

	return r;
}


int StrBuilder2_AppendN(StrBuilder2* p,
                       const char* source,
	                   size_t nelements)
{
	if (IsEmptyStr_RemoveThis(source))
	{
		return 0;
	}

	int r = StrBuilder2_Grow(p, p->size + nelements);

	if (r > 0)
	{
		strncpy_s(p->c_str + p->size,
			(p->capacity + 1) - p->size,
			source,
			nelements);
		p->c_str[p->size + nelements] = '\0';
		p->size += nelements;
	}

	return r;
}

int StrBuilder2_Append(StrBuilder2* p,
	const char* source)
{
	if (IsEmptyStr_RemoveThis(source))
	{
		return 0;
	}

	return StrBuilder2_AppendN(p, source, strlen(source));
}

void StrBuilder2_Clear(StrBuilder2* p)
{
	if (p->c_str != NULL)
	{
		p->c_str[0] = '\0';
		p->size = 0;
	}
}

char* StrBuilder2_Release(StrBuilder2* p)
{
	char* pResult = p->c_str;

	if (pResult != NULL)
	{
		p->c_str = NULL;
		p->size = 0;
		p->capacity = 0;
	}

	return pResult;
}



int StrBuilder2_AppendChar(StrBuilder2* p, char ch)
{
	return StrBuilder2_AppendN(p, &ch, 1);
}

void StrBuilder2_Trim(StrBuilder2* p)
{
	StrBuilder2 temp;
	StrBuilder2_Init(&temp, p->size);
	bool bCopy = false;

	for (size_t i = 0; i < p->size; i++)
	{
		char ch = p->c_str[i];

		if (!bCopy && ch != ' ')
		{
			//a partir de agora copia
			bCopy = true;
		}

		if (bCopy)
			StrBuilder2_AppendChar(&temp, ch);
	}

	//indice do ultimo que nao eh espaco
	int k = ((int)(temp.size)) - 1;

	for (; k >= 0; k--)
	{
		char ch = temp.c_str[k];

		if (ch != ' ')
		{
			break;
		}
	}

	temp.c_str[k + 1] = '\0';
	temp.size = k + 1;
	StrBuilder2_Swap(&temp, p);
	StrBuilder2_Destroy(&temp);
}


