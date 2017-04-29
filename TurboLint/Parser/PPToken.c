
#include "PPToken.h"
#include <stdlib.h>


void PPToken_Init(PPToken * p)
{
	PPToken temp = TOKEN_INIT;
	*p = temp;
}

void PPToken_Destroy(PPToken * p)
{
	String_Destroy(&p->Lexeme);
}

void PPToken_Swap(PPToken * pA, PPToken * pB)
{
	PPToken temp = *pA;
	*pA = *pB;
	*pB = temp;
}

PPToken*  PPToken_Clone(PPToken* p)
{
	PPToken* pNew = PPToken_Create(p->Lexeme, p->Token);
	TokenSetAppendCopy(&pNew->HiddenSet, &p->HiddenSet);
	return pNew;
}

PPToken* PPToken_Create(const char* s, PPTokenType token)
{
	PPToken* p = (PPToken*)malloc(sizeof(PPToken));

	if (p != 0)
	{
		PPToken t = TOKEN_INIT;
		*p = t;
		String_Set(&p->Lexeme, s);
		p->Token = token;
	}

	return p;
}

void PPToken_Delete(PPToken * p)
{
	if (p != 0)
	{
		PPToken_Destroy(p);
		free(p);
	}
}

bool PPToken_IsIdentifier(PPToken* pHead)
{
	return pHead->Token == PPTokenType_Identifier;
}

bool PPToken_IsSpace(PPToken* pHead)
{
	if (pHead->Lexeme[0] == ' ' )
	{
		return true;
	}
	return false;
}

bool PPToken_IsStringizingOp(PPToken* pHead)
{
	return pHead->Lexeme[0] == '#' &&
		   pHead->Lexeme[1] == '\0';
}

bool PPToken_IsConcatOp(PPToken* pHead)
{
	return pHead->Lexeme[0] == '#' &&
		   pHead->Lexeme[1] == '#' &&
		   pHead->Lexeme[2] == '\0';
}

bool PPToken_IsStringLit(PPToken* pHead)
{
	return pHead->Token == PPTokenType_StringLiteral;
}

bool PPToken_IsCharLit(PPToken* pHead)
{
	return pHead->Token == PPTokenType_CharConstant;	
}

bool PPToken_IsOpenPar(PPToken* pHead)
{
	return pHead->Lexeme[0] == '('&&
		   pHead->Lexeme[1] == '\0';
}
bool PPToken_IsClosePar(PPToken* pHead)
{
	return pHead->Lexeme[0] == '(' &&
		pHead->Lexeme[1] == '\0';
}

bool PPToken_IsChar(PPToken* pHead, char ch)
{
	return pHead->Lexeme[0] == ch &&
		   pHead->Lexeme[1] == '\0';
}

bool PPToken_IsLexeme(PPToken* pHead, const char* lexeme)
{
	return strcmp(pHead->Lexeme, lexeme) == 0;
}