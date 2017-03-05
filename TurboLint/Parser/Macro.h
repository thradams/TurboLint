#pragma once
#include <stdbool.h>
#include "PPToken.h"
#include "TokenArray.h"
#include "..\Base\Map2.h"

typedef struct
{
	String2 Name;
	bool bIsFunction;
	TokenArray TokenSequence;
	TokenArray FormalArguments;
} Macro;

#define MACRO_INIT { STRING2_INIT, false , TOKENARRAY_INIT, TOKENARRAY_INIT}
Macro* Macro_Create();


typedef struct MacroMapItem
{
	struct MapItem2* pNext;
	unsigned int HashValue;
	String2 Key;
	Macro* pValue;
} MacroMapItem;

typedef struct
{
	MacroMapItem** pHashTable;
	unsigned int nHashTableSize;
	size_t  nCount;
} MacroMap;


#define MACROMAP_INIT { NULL, 0, 0 }

int MacroMap2_SetAt(MacroMap* pMap,
	const char* Key,
	Macro* newValue);

bool MacroMap2_Lookup(const MacroMap* pMap,
	const char*  Key,
	Macro** rValue);

bool MacroMap2_RemoveKey(MacroMap* pMap,
	const char*  Key);

void MacroMap2_Init(MacroMap* p);
void MacroMap2_Destroy(MacroMap* p);

MacroMap*  MacroMap2_Create();
void MacroMap2_Delete(MacroMap * p);

void MacroMap2_Swap(MacroMap * pA, MacroMap * pB);

Macro* MacroMap2_Find(const MacroMap* pMap, const char*  Key);



void ExpandMacro(const TokenArray* tsOriginal,
	const MacroMap* macros,
	bool get_more,
	bool skip_defined,
	Macro* caller,
	TokenArray* pOutputSequence);

void ExpandMacroToText(const TokenArray* pTokenSequence,
	const MacroMap* macros,
	bool get_more,
	bool skip_defined,
	Macro* caller,
	StrBuilder2* strBuilder);

