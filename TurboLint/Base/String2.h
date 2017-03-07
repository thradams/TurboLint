#pragma once
#include <string.h>
#include <stdbool.h>

typedef char * String2;
#define STRING2_INIT 0

int    String2_Init(String2* pString, const char* source);
void   String2_Destroy(String2* pString);
void   String2_Swap(String2* pA, String2* pB);
int    String2_Set(String2 *pS1, const char* psz1);


typedef struct
{
	char*  c_str;
	size_t size;
	size_t capacity;

} StrBuilder2;

#define STRBUILDER2_INIT { 0, 0, 0 }
#define STRBUILDER2_DEFAULT_SIZE 17

int StrBuilder2_Init(StrBuilder2* p, size_t capacity);

int StrBuilder2_Reserve(StrBuilder2* p, size_t nelements);



void StrBuilder2_Destroy(StrBuilder2* wstr);
void StrBuilder2_Swap(StrBuilder2* str1, StrBuilder2* str2);


void StrBuilder2_Clear(StrBuilder2* wstr);

int StrBuilder2_SetN(StrBuilder2* p,
	const char* source,
	size_t nelements);

int StrBuilder2_Set(StrBuilder2* p,
	const char* source);

int StrBuilder2_AppendN(StrBuilder2* p,
	const char* source,
	size_t nelements);

int StrBuilder2_Append(StrBuilder2* p,
	const char* source);

char* StrBuilder2_Release(StrBuilder2* p);

int StrBuilder2_AppendInt(StrBuilder2 * p, int i);


int StrBuilder2_AppendWChar(StrBuilder2 * p, wchar_t wch);
int StrBuilder2_AppendW(StrBuilder2 * p, const wchar_t* psz);
int StrBuilder2_AppendChar(StrBuilder2 * p, char wch);
void StrBuilder2_Trim(StrBuilder2* p);
int StrBuilder2_AppendUpper(StrBuilder2 *p, const char* s);
