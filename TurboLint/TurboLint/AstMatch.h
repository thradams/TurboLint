#pragma once
#include "..\Parser\Ast.h"


TPostfixExpressionCore *_opt MatchStructPointerMember(const char * varName,
	TExpression2 * pExpression);


bool MatchNULL(TExpression2 * pExpression);

const char *_opt MatchIdentifier(TExpression2* pExpression);
const char *_opt MatchPrimaryExpression(TExpression2* pExpression);

TExpression2 *_opt MatchFunctionCall(TExpression2* pExpression,
	const char** funcNameOpt);

