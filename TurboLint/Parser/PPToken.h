#pragma once
#include "String.h"
#include  "TokenArray.h"

typedef struct PPToken
{
	String2 Lexeme;
	TokenSet HiddenSet;
} PPToken;

#define TOKEN_INIT { STRING2_INIT }

void PPToken_Init(PPToken* p);
void PPToken_Destroy(PPToken* p);

PPToken*  PPToken_Create(const char* s);
PPToken*  PPToken_Clone(PPToken* p);
void PPToken_Delete(PPToken * p);
void PPToken_Swap(PPToken * pA, PPToken * pB);


bool PPToken_IsIdentifier(PPToken* pHead);
bool PPToken_IsSpace(PPToken* pHead);
bool PPToken_IsStringizingOp(PPToken* pHead);
bool PPToken_IsConcatOp(PPToken* pHead);
bool PPToken_IsStringLit(PPToken* pHead);
bool PPToken_IsCharLit(PPToken* pHead);
bool PPToken_IsOpenPar(PPToken* pHead);
bool PPToken_IsClosePar(PPToken* pHead);
bool PPToken_IsChar(PPToken* pHead, char ch);