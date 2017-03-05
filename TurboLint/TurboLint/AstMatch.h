#pragma once
#include "..\Parser\Ast.h"


TPostfixExpressionCore * MatchStructPointerMember(const char * varName,
	TExpression2 * pExpression);


bool MatchNULL(TExpression2 * pExpression);

const char * MatchIdentifier(TExpression2* pExpression);
const char * MatchPrimaryExpression(TExpression2* pExpression);

TExpression2 * MatchFunctionCall(TExpression2* pExpression,
	const char** funcNameOpt);

