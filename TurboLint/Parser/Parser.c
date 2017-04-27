#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "Scanner.h"

bool IsTypeName(Parser* ctx, Tokens token, const char * lexeme);




bool DeclarationsMap_IsTypeDef(DeclarationsMap* map, const char* name)
{
	bool bResult = false;
	Bucket*  p = MultiMap_FindBucket(map, name);

	if (p != NULL)
	{
		for (size_t i = 0; i < p->size; i++)
		{
			if (strcmp(name, p->data[i]->key) == 0)
			{
				TAnyDeclaration *pDeclaration = (TAnyDeclaration *)p->data[i]->data;
				bResult = TAnyDeclaration_IsTypedef(pDeclaration);

				if (bResult)
					break;
			}
		}
	}

	return bResult;
}

Result Parser_InitString(Parser* parser,
	const char* name,
	const char* text)
{
	MultiMap_Init(&parser->Symbols, SYMBOL_BUCKETS_SIZE);
	Map_Init(&parser->EnumMap, SYMBOL_BUCKETS_SIZE);

	//Map_Init(&parser->TypeDefNames, SYMBOL_BUCKETS_SIZE);
	parser->bError = false;
	StrBuilder_Init(&parser->ErrorMessage, 100);
	
	


	/////////
	Scanner_InitString(&parser->Scanner, name, text);

	return RESULT_OK;
}

Result Parser_InitFile(Parser* parser, const char* fileName)
{
	DeclarationsMap_Init(&parser->Symbols, SYMBOL_BUCKETS_SIZE);
	Map_Init(&parser->EnumMap, SYMBOL_BUCKETS_SIZE);

	//Map_Init(&parser->TypeDefNames, SYMBOL_BUCKETS_SIZE);
	parser->bError = false;
	
	StrBuilder_Init(&parser->ErrorMessage, 100);
	Scanner_Init(&parser->Scanner);


	////////
	Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath);
	Scanner_Skip(&parser->Scanner);

	return RESULT_OK;
}

void Parser_PushFile(Parser* parser, const char* fileName)
{
	Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath);
	Scanner_Skip(&parser->Scanner);
}


void Parser_SetSymbol(Parser* parser,
	const char* name,
	TAnyDeclaration* pObject)
{
	Bucket*  pBucket = MultiMap_FindBucket(&parser->Symbols, name);

	if (pBucket)
	{
		//TODO verificar se os tipos sao compativeis
	}

	MultiMap_Add(&parser->Symbols, name, pObject);
	//Result result = Map_Find(&parser->TypeDefNames, name, &pOut);
	//if (result == RESULT_OK)
	//{
	//tem que ser a mesma declaracao
	//senao eh erro
	//}
	//Map_Set(&parser->TypeDefNames, name, pObject);
}

Result DeclarationsMap_Init(DeclarationsMap* p, size_t nBuckets)
{
	return MultiMap_Init(p, nBuckets);
}

void DeclarationsMap_Destroy(DeclarationsMap* p)
{
	MultiMap_Destroy(p, NULL); //OWNER IS AST
}

void Parser_Destroy(Parser* parser)
{
	DeclarationsMap_Destroy(&parser->Symbols);
	Map_Destroy(&parser->EnumMap, NULL); //OWNER IS AST

	//Map_Destroy(&parser->TypeDefNames, NULL);
	StrBuilder_Destroy(&parser->ErrorMessage);
	Scanner_Destroy(&parser->Scanner);
}

static const char* GetName()
{
	static char buffer[2];
	buffer[0] = '\0';
	//static int i = 0;
	//strcat(buffer, "__noname");
	//char bn[20];
	//_itoa(i, bn, 10);
	//strcat(buffer, bn);
	//i++;
	return buffer;
}

static bool HasErrors(Parser* pParser)
{
	return pParser->bError || pParser->Scanner.bError;
}


static void Next(Parser* parser)
{
	if (HasErrors(parser))
	{
		return;
	}

	Scanner_Next(&parser->Scanner);
}


void SetError2(Parser* parser, const char* message, const char* message2)
{
	//    ASSERT(false);
	if (!HasErrors(parser))
	{
		Scanner_GetError(&parser->Scanner, &parser->ErrorMessage);
		parser->bError = true;
		StrBuilder_Append(&parser->ErrorMessage, "(");
		StrBuilder_AppendInt(&parser->ErrorMessage, Scanner_Line(&parser->Scanner));
		StrBuilder_Append(&parser->ErrorMessage, ") : error :");
		StrBuilder_Append(&parser->ErrorMessage, message);
		StrBuilder_Append(&parser->ErrorMessage, message2);
	}

	else
	{
		//ja esta com erro entao eh ruido...
		parser->bError = true;
	}
}

void SetError(Parser* parser, const char* message)
{
	SetError2(parser, message, "");
}

Result MatchAndGet(Parser* parser, ScannerItem* scannerItem)
{
	if (HasErrors(parser))
		return RESULT_FAIL;

	Scanner_GetScannerItemCopy(&parser->Scanner, scannerItem);
	//ScannerItem_Swap(&Scanner_Top(&parser->Scanner)->currentItem, scannerItem);

	Next(parser);
	return RESULT_OK;
}

Result MatchAndPush(Parser* parser, ScannerItemStack* stack)
{
	ScannerItem item;
	ScannerItem_Init(&item);
	MatchAndGet(parser, &item);
	ScannerItemStack_PushMove(stack, &item);
	ScannerItem_Destroy(&item);
	return RESULT_OK;
}

int GetCurrentLine(Parser* parser)
{
	if (HasErrors(parser))
	{
		return -1;
	}

	return Scanner_GetCurrentLine(&parser->Scanner);
}

int GetFileIndex(Parser* parser)
{
	if (HasErrors(parser))
	{
		return -1;
	}

	return Scanner_GetFileIndex(&parser->Scanner);
}

static void GetPosition(Parser* ctx, TPosition* pPosition)
{
	pPosition->Line = GetCurrentLine(ctx);
	pPosition->FileIndex = GetFileIndex(ctx);
	//ASSERT(pPosition->FileIndex >= 0);
}

Tokens LookAheadToken(Parser* parser)
{
	if (HasErrors(parser))
	{
		return TK_ERROR;
	}

	return Scanner_GetLookAhead(&parser->Scanner)->token;
}

const char* LookAheadLexeme(Parser* parser)
{
	if (HasErrors(parser))
	{
		return "";
	}

	return Scanner_GetLookAhead(&parser->Scanner)->lexeme.c_str;
}


Tokens Token(Parser* parser)
{
	if (HasErrors(parser))
	{
		return TK_ERROR;
	}

	Tokens token = Scanner_Token(&parser->Scanner);
	if (token == TK_SPACES)
	{
		SetError(parser, "!");
		ASSERT(false);
	}
	return token;
}

Tokens Match(Parser* parser)
{
	if (HasErrors(parser))
	{
		return TK_EOF;
	}

	Next(parser);
	return Token(parser);
}

//ScannerItem* Parser_GetLookAhead(Parser* parser)
//{
///return Scanner_GetLookAhead(&parser->Scanner);
//}

Tokens MatchToken(Parser* parser, Tokens tk)
{
	if (HasErrors(parser))
	{
		return TK_EOF;
	}

	Tokens currentToken = Token(parser);

	if (tk != currentToken)
	{
		SetError2(parser, "Unexpected token - ", TokenToString(tk));
		return TK_EOF;
	}

	Next(parser);
	return Token(parser);
}

const char* GetCompletationMessage(Parser* parser)
{
	const char* pMessage = "ok";

	if (HasErrors(parser))
	{
		if (parser->Scanner.bError)
		{
			pMessage = parser->Scanner.ErrorString.c_str;
		}

		else
		{
			pMessage = parser->ErrorMessage.c_str;
		}
	}

	return pMessage;
}

const char* Lexeme(Parser* parser)
{
	if (HasErrors(parser))
	{
		ASSERT(false);
		return "";
	}

	return Scanner_Lexeme(&parser->Scanner);
}

bool ErrorOrEof(Parser* parser)
{
	return HasErrors(parser) ||
		Token(parser) == TK_EOF;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


void Expression0(Parser* ctx, TExpression2**);
void CastExpression(Parser* ctx, TExpression2**);
void GenericSelection(Parser* ctx);
void ArgumentExpressionList(Parser* ctx, TExpression2**);
void AssignmentExpression(Parser* ctx, TExpression2**);
void Initializer_List(Parser* ctx, TInitializerList* pInitializerList);
void Specifier_Qualifier_List(Parser* ctx,
	TTypeQualifier* pQualifiers,
	TTypeSpecifier** ppTypeSpecifier);
bool AbstractDeclaratorOpt(Parser* ctx, TDeclarator* pTDeclarator2);



bool IsFirstOfPrimaryExpression(Tokens token)
{
	bool bResult = false;

	switch (token)
	{
		case TK_identifier:
		case TK_string_literal:
		case TK_char_literal:
		case TK_DECIMAL_INTEGER:
		case TK_HEX_INTEGER:
		case TK_FLOAT_NUMBER:
		case TK_LEFT_PARENTHESIS:

			//desde que nao seja cast
		case TK__Generic:
			bResult = true;
			break;

		default:
			break;
	}

	return bResult;
}

void PrimaryExpression(Parser* ctx, TExpression2** ppPrimaryExpression)
{
	/*
	(6.5.1) primary-expression:
	identifier
	constant
	string-literal
	( expression )
	generic-selection
	*/

	Tokens token = Token(ctx);
	ASSERT(IsFirstOfPrimaryExpression(token));

	if (!IsFirstOfPrimaryExpression(token))
	{
		SetError(ctx, "1");
	}

	switch (token)
	{
		case TK_string_literal:
		{
			TPrimaryExpressionValue *  pPrimaryExpressionValue
				= TPrimaryExpressionValue_Create();

			pPrimaryExpressionValue->token = token;

			StrBuilder adjacentStrings = STRBUILDER_INIT;
			StrBuilder_Append(&adjacentStrings, "\"");
			while (token == TK_string_literal)
			{
				const char* lexeme = Lexeme(ctx);
				int len = strlen(lexeme);
				StrBuilder_AppendN(&adjacentStrings, lexeme + 1, len - 2);
				token = Match(ctx);
			}
			StrBuilder_Append(&adjacentStrings, "\"");
			String_Set(&pPrimaryExpressionValue->lexeme, adjacentStrings.c_str);
			*ppPrimaryExpression = (TExpression2*)  pPrimaryExpressionValue;

			StrBuilder_Destroy(&adjacentStrings);
		}
		break;

		case TK_identifier:
		case TK_char_literal:
		case TK_DECIMAL_INTEGER:
		case TK_HEX_INTEGER:
		case TK_FLOAT_NUMBER:
		{
			TPrimaryExpressionValue *   pPrimaryExpressionValue
				= TPrimaryExpressionValue_Create();

			pPrimaryExpressionValue->token = token;
			String_Set(&pPrimaryExpressionValue->lexeme, Lexeme(ctx));

			Match(ctx);
			*ppPrimaryExpression = (TExpression2*)  pPrimaryExpressionValue;
		}
		break;

		case TK_LEFT_PARENTHESIS:
		{
			Match(ctx);
			TExpression2* pExpression;
			Expression0(ctx, &pExpression);
			MatchToken(ctx, TK_RIGHT_PARENTHESIS);

			TPrimaryExpressionValue *   pPrimaryExpressionValue
				= TPrimaryExpressionValue_Create();

			pPrimaryExpressionValue->token = token;
			String_Set(&pPrimaryExpressionValue->lexeme, Lexeme(ctx));
			pPrimaryExpressionValue->pExpressionOpt = pExpression;
			*ppPrimaryExpression = (TExpression2*)  pPrimaryExpressionValue;
		}
		break;

		case TK__Generic:
			GenericSelection(ctx);
			break;

		default:
			ASSERT(false);
	}

	ASSERT(*ppPrimaryExpression != NULL);
}

void GenericSelection(Parser* ctx)
{
	//_Generic

	/*
	(6.5.1.1) generic-selection:
	_Generic ( assignment-expression , generic-assoc-list )
	*/
}

void GenericAssocList(Parser* ctx)
{

	//type-name default

	/*
	(6.5.1.1) generic-assoc-list:
	generic-association
	generic-assoc-list , generic-association
	*/
}

void GenericAssociation(Parser* ctx)
{
	//type-name default

	/*
	(6.5.1.1) generic-association:
	type-name : assignment-expression
	default : assignment-expression
	*/
}

void TypeName(Parser* ctx, TTypeName* pTypeName)
{
	/*
	type-name:
	specifier-qualifier-list abstract-declaratoropt
	*/

	Specifier_Qualifier_List(ctx,
		&pTypeName->Specifiers.TypeQualifiers,
		&pTypeName->Specifiers.pTypeSpecifierOpt);

	AbstractDeclaratorOpt(ctx, &pTypeName->Declarator);
}


void PostfixExpressionCore(Parser* ctx, TPostfixExpressionCore* pPostfixExpressionCore)
{
	//ja entra aqui sendo uma  postfix-expression antes
	/*
	(6.5.2) postfix-expression:

	postfix-expression [ expression ]
	postfix-expression ( argument-expression-listopt )
	postfix-expression . identifier
	postfix-expression -> identifier
	postfix-expression ++
	postfix-expression --

	*/

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_LEFT_PARENTHESIS:
		{
      //aqui eu posso marcar a funcao como usada.

			pPostfixExpressionCore->token = token;

			//  postfix-expression ( argument-expression-listopt )
			token = Match(ctx);

			if (token != TK_RIGHT_PARENTHESIS)
			{
				ArgumentExpressionList(ctx, &pPostfixExpressionCore->pExpressionArray);
			}

			MatchToken(ctx, TK_RIGHT_PARENTHESIS);
		}
		break;

		case TK_LEFT_SQUARE_BRACKET:
		{
			pPostfixExpressionCore->token = token;
			// postfix-expression [ expression ]
			MatchToken(ctx, TK_LEFT_SQUARE_BRACKET);
			Expression0(ctx, &pPostfixExpressionCore->pExpressionArray);
			MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET);
		}
		break;

		case TK_FULL_STOP:
		{
			// postfix-expression . identifier
			pPostfixExpressionCore->token = token;
			Match(ctx);
			String_Set(&pPostfixExpressionCore->Identifier, Lexeme(ctx));
			MatchToken(ctx, TK_identifier);
		}
		break;

		case TK_ARROW:
		{
			// postfix-expression -> identifier
			pPostfixExpressionCore->token = token;
			Match(ctx);
			String_Set(&pPostfixExpressionCore->Identifier, Lexeme(ctx));
			MatchToken(ctx, TK_identifier);
		}
		break;

		case TK_PLUSPLUS:
		{
			pPostfixExpressionCore->token = token;
			//postfix-expression ++
			Match(ctx);
		}
		break;

		case TK_MINUSMINUS:
		{
			//  postfix-expression --
			pPostfixExpressionCore->token = token;
			Match(ctx);
		}
		break;

		default:
			// ASSERT(false);
			break;
	}


	token = Token(ctx);

	switch (token)
	{
		case TK_LEFT_PARENTHESIS:
		case TK_LEFT_SQUARE_BRACKET:
		case TK_FULL_STOP:
		case TK_ARROW:
		case TK_PLUSPLUS:
		case TK_MINUSMINUS:
		{
			TPostfixExpressionCore *  pPostfixExpressionCoreNext =
				TPostfixExpressionCore_Create();
			PostfixExpressionCore(ctx, pPostfixExpressionCoreNext);
			
			ASSERT(pPostfixExpressionCore->pNext == NULL);
			pPostfixExpressionCore->pNext =  pPostfixExpressionCoreNext;
		}
		break;
	}


}

void PostfixExpression(Parser* ctx, TExpression2** ppExpression)
{
	*ppExpression = NULL;//out

	/*
	(6.5.2) postfix-expression:
	postfix-expression ( argument-expression-listopt )
	( type-name ) { initializer-list }
	( type-name ) { initializer-list , }

	primary-expression
	postfix-expression [ expression ]
	postfix-expression . identifier
	postfix-expression -> identifier
	postfix-expression ++
	postfix-expression --

	*/

	Tokens token = Token(ctx);


	if (token == TK_LEFT_PARENTHESIS)
	{
		const char* lookAheadlexeme = LookAheadLexeme(ctx);
		Tokens lookAheadToken = LookAheadToken(ctx);

		if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
		{
			// ( type-name ) { initializer-list }

			TPostfixExpressionCore *  pTPostfixExpressionCore =
				TPostfixExpressionCore_Create();

			MatchToken(ctx, TK_LEFT_PARENTHESIS);

			TTypeName typeName = TTYPENAME_INIT;
			TypeName(ctx, &typeName);
			TParameterDeclaration_Destroy(&typeName);

			MatchToken(ctx, TK_RIGHT_PARENTHESIS);

			MatchToken(ctx, TK_LEFT_CURLY_BRACKET);

			pTPostfixExpressionCore->pInitializerList = TInitializerList_Create();
			Initializer_List(ctx, pTPostfixExpressionCore->pInitializerList);
			MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);

			if (Token(ctx) == TK_COMMA)
			{
				Match(ctx);
			}

			*ppExpression = (TExpression2*) pTPostfixExpressionCore;
		}

		else
		{
			//primary-expression
			TExpression2* pPrimaryExpression;
			PrimaryExpression(ctx, &pPrimaryExpression);
			*ppExpression = pPrimaryExpression;
		}
	}

	else
	{
		//primary-expression
		TExpression2* pPrimaryExpression;
		PrimaryExpression(ctx, &pPrimaryExpression);
		*ppExpression = pPrimaryExpression;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_LEFT_PARENTHESIS:
		case TK_LEFT_SQUARE_BRACKET:
		case TK_FULL_STOP:
		case TK_ARROW:
		case TK_PLUSPLUS:
		case TK_MINUSMINUS:
		{
			TPostfixExpressionCore *  pPostfixExpressionCore =
				TPostfixExpressionCore_Create();
			pPostfixExpressionCore->pExpressionLeft = *ppExpression;
			PostfixExpressionCore(ctx, pPostfixExpressionCore);
			*ppExpression = (TExpression2*)  pPostfixExpressionCore;
		}
		break;
	}

}

void ArgumentExpressionList(Parser* ctx, TExpression2** ppExpression)
{
	/*(6.5.2) argument-expression-list:
	assignment-expression
	argument-expression-list , assignment-expression
	*/
	TExpression2* pAssignmentExpression;
	AssignmentExpression(ctx, &pAssignmentExpression);
	*ppExpression = pAssignmentExpression;

	Tokens token = Token(ctx);

	if (token == TK_COMMA)
	{
		Match(ctx);
		TExpression2* pAssignmentExpressionRight;
		AssignmentExpression(ctx, &pAssignmentExpressionRight);

		TBinaryExpression *  pExpr =
			TBinaryExpression_Create();

		GetPosition(ctx, &pExpr->Position);
		pExpr->token = TK_COMMA;
		pExpr->pExpressionLeft = pAssignmentExpression;
		pExpr->pExpressionRight = pAssignmentExpressionRight;

		

		*ppExpression = (TExpression2*)  pExpr;
	}

	token = Token(ctx);

	if (token == TK_COMMA)
	{
		Match(ctx);
		TBinaryExpression *  pExpr =
			TBinaryExpression_Create();

		GetPosition(ctx, &pExpr->Position);
		pExpr->token = TK_COMMA;
		pExpr->pExpressionLeft = *ppExpression;

		TExpression2 *pExpressionRight;
		ArgumentExpressionList(ctx, &pExpressionRight);
		pExpr->pExpressionRight = pExpressionRight;

		

		*ppExpression = (TExpression2*)  pExpr;
	}
}



static bool IsTypeQualifierToken(Tokens token)
{
	bool bResult = false;
	switch (token)
	{
		//type-qualifier
		case TK_const:
		case TK_restrict:
		case TK_volatile:
		case TK__Atomic:
		//
			bResult = true;
			break;
		//type-qualifier-extensions 
		case TK_OPT_QUALIFIER:
		case TK_OWN_QUALIFIER:
		case TK_DTOR_QUALIFIER:
		case TK_MDTOR_QUALIFIER:
			bResult = true;
			break;
	}
	return bResult;
}

bool IsTypeName(Parser* ctx, Tokens token, const char * lexeme)
{
	bool bResult = false;

	switch (token)
	{

		case TK_identifier:
			bResult = DeclarationsMap_IsTypeDef(&ctx->Symbols, lexeme);
			break;

		//type-qualifier
		case TK_const:
		case TK_restrict:
		case TK_volatile:
		case TK__Atomic:
		
		//type-qualifier-extensions 
		case TK_OPT_QUALIFIER:
		case TK_OWN_QUALIFIER:
		case TK_DTOR_QUALIFIER:
		case TK_MDTOR_QUALIFIER:
			

		//type-specifier
		case TK_void:
		case TK_char:
		case TK_short:
		case TK_int:
		case TK_long:
		case TK_float:
		case TK_double:
		case TK_signed:
		case TK_unsigned:
		case TK__Bool:
		case TK__Complex:
		case TK_struct:
		case TK_union:
		case TK_enum:
			bResult = true;
			break;
	}

	return bResult;
}

void UnaryExpression(Parser* ctx, TExpression2** ppExpression)
{
	*ppExpression = NULL; //out

	/*(6.5.3) unary-expression:
	postfix-expression
	++ unary-expression
	-- unary-expression
	unary-operator cast-expression
	sizeof unary-expression
	sizeof ( type-name )
	alignof ( type-name )

	unary-operator: one of
	& * + - ~ !
	*/

	Tokens token0 = Token(ctx);
	Tokens tokenAhead = LookAheadToken(ctx);
	const char* lookAheadlexeme = LookAheadLexeme(ctx);

	if (IsTypeName(ctx, tokenAhead, lookAheadlexeme))
	{
		//first para postfix-expression
		TExpression2 * pPostfixExpression;
		PostfixExpression(ctx, &pPostfixExpression);
		*ppExpression = (TExpression2*)(pPostfixExpression);
		return;
	}

	else if (IsFirstOfPrimaryExpression(token0))
	{
		//primary-expression é first para postfix-expression

		TExpression2 * pPostfixExpression;
		PostfixExpression(ctx, &pPostfixExpression);
		*ppExpression = (TExpression2*)(pPostfixExpression);
		return;
	}

	switch (token0)
	{
		case TK_PLUSPLUS:
		case TK_MINUSMINUS:
		{
			Match(ctx);
			TExpression2 *pUnaryExpression;
			UnaryExpression(ctx, &pUnaryExpression);

			TUnaryExpressionOperator* pUnaryExpressionOperator =
				TUnaryExpressionOperator_Create();
			pUnaryExpressionOperator->token = token0;
			pUnaryExpressionOperator->pExpressionLeft = pUnaryExpression;
			*ppExpression = (TExpression2*)pUnaryExpressionOperator;
		}
		break;

		//unary-operator cast-expression
		case TK_AMPERSAND:
		case TK_ASTERISK:
		case TK_PLUS_SIGN:
		case TK_HYPHEN_MINUS:
		case TK_TILDE:
		case TK_EXCLAMATION_MARK:
		//unary-operator-extension
		case TK_MOVE:
	    //
		{
			Match(ctx);
			TExpression2* pCastExpression;
			CastExpression(ctx, &pCastExpression);


			TUnaryExpressionOperator* pUnaryExpressionOperator =
				TUnaryExpressionOperator_Create();
			pUnaryExpressionOperator->token = token0;
			pUnaryExpressionOperator->pExpressionLeft = pCastExpression;
			*ppExpression = (TExpression2*)pUnaryExpressionOperator;

		}
		break;

		//////////////

		case TK_SIZEOF:
			MatchToken(ctx, TK_SIZEOF);

			if (Token(ctx) == TK_LEFT_PARENTHESIS)
			{
				const char* lookAheadlexeme = LookAheadLexeme(ctx);
				Tokens lookAheadToken = LookAheadToken(ctx);

				if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
				{
					TUnaryExpressionOperator* pUnaryExpressionOperator =
						TUnaryExpressionOperator_Create();



					//sizeof deste tipo
					MatchToken(ctx, TK_LEFT_PARENTHESIS);

					TypeName(ctx, &pUnaryExpressionOperator->TypeName);

					MatchToken(ctx, TK_RIGHT_PARENTHESIS);



					pUnaryExpressionOperator->token = token0;
					//pUnaryExpressionOperator->pExpressionRight = pCastExpression;
					*ppExpression = (TExpression2*)pUnaryExpressionOperator;

				}

				else
				{
					//sizeof do tipo desta expressao
					TExpression2 *pTUnaryExpression;
					UnaryExpression(ctx, &pTUnaryExpression);

					TUnaryExpressionOperator* pUnaryExpressionOperator =
						TUnaryExpressionOperator_Create();
					pUnaryExpressionOperator->token = token0;
					pUnaryExpressionOperator->pExpressionLeft = pTUnaryExpression;
					*ppExpression = (TExpression2*)pUnaryExpressionOperator;

				}
			}

			else
			{
				//sizeof do tipo desta expressao
				TExpression2 *pTUnaryExpression;
				UnaryExpression(ctx, &pTUnaryExpression);

				TUnaryExpressionOperator* pUnaryExpressionOperator =
					TUnaryExpressionOperator_Create();
				pUnaryExpressionOperator->token = token0;
				pUnaryExpressionOperator->pExpressionLeft = pTUnaryExpression;
				*ppExpression = (TExpression2*)pUnaryExpressionOperator;
			}

			break;

		case TK__Alignof:
			//Match
			ASSERT(false);
			break;

		default:
      //ASSERT(false);
      SetError(ctx, "Assert");
			
			break;
	}

}

void CastExpression(Parser* ctx, TExpression2** ppExpression)
{
	*ppExpression = NULL; //out

	/*
	cast-expression:
	unary-expression
	( type-name ) cast-expression
	*/

	Tokens token = Token(ctx);

	if (token == TK_LEFT_PARENTHESIS)
	{
		const char* lookAheadlexeme = LookAheadLexeme(ctx);
		Tokens lookAheadToken = LookAheadToken(ctx);

		if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
		{
			MatchToken(ctx, TK_LEFT_PARENTHESIS);
			TTypeName typeName = TTYPENAME_INIT;
			TypeName(ctx, &typeName);

			token = MatchToken(ctx, TK_RIGHT_PARENTHESIS);

			if (token == TK_LEFT_CURLY_BRACKET)
			{
				//se isso acontecer, quer dizer que eh uma postfix-expression
				//entao deveria ter sido expandido com
				//unary-expression -> postfix-expression ->
				/*
				(6.5.2) postfix-expression:
				...
				( type-name ) { initializer-list }
				( type-name ) { initializer-list , }
				*/

				MatchToken(ctx, TK_LEFT_CURLY_BRACKET);

				TPostfixExpressionCore*  pTPostfixExpressionCore =
					TPostfixExpressionCore_Create();

				pTPostfixExpressionCore->pInitializerList = TInitializerList_Create();
				Initializer_List(ctx, pTPostfixExpressionCore->pInitializerList);

				Initializer_List(ctx, pTPostfixExpressionCore->pInitializerList);
				MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);


				if (Token(ctx) == TK_COMMA)
				{
					Match(ctx);
				}


				PostfixExpressionCore(ctx, pTPostfixExpressionCore);
			}
			else
			{
				TExpression2* pCastExpression;
				CastExpression(ctx, &pCastExpression);

				TCastExpressionType *pCastExpressionType =
					TCastExpressionType_Create();

				TParameterDeclaration_Swap(&pCastExpressionType->TypeName, &typeName);
				pCastExpressionType->pExpression = pCastExpression;
				*ppExpression = (TExpression2*)pCastExpressionType;

			}

			TParameterDeclaration_Destroy(&typeName);
		}
		else
		{
			TExpression2* pUnaryExpression;
			UnaryExpression(ctx, &pUnaryExpression);
			*ppExpression = pUnaryExpression;
		}
	}
	else
	{
		TExpression2* pUnaryExpression;
		UnaryExpression(ctx, &pUnaryExpression);
		
		*ppExpression = pUnaryExpression;
	}
}


void MultiplicativeExpression(Parser* ctx, TExpression2** ppExpression)
{


	/*
	(6.5.5) multiplicative-expression:
	cast-expression                                // identifier  constant  string-literal  (  _Generic ++	  -- 	 & * + - ~ ! 		 sizeof 		 sizeof		 alignof
	multiplicative-expression * cast-expression
	multiplicative-expression / cast-expression
	multiplicative-expression % cast-expression
	*/

	TExpression2* pExpressionLeft;
	CastExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_PERCENT_SIGN:
		case TK_SOLIDUS:
		case TK_ASTERISK:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			
			GetPosition(ctx, &pBinaryExpression->Position);
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			
			Match(ctx);
			TExpression2* pExpressionRight;
			CastExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_PERCENT_SIGN:
		case TK_SOLIDUS:
		case TK_ASTERISK:
		{
			TBinaryExpression *pBinaryExpression = 
				TBinaryExpression_Create();

			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			MultiplicativeExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}
}

void AdditiveExpression(Parser* ctx, TExpression2** ppExpression)
{

	/*
	(6.5.6) additive-expression:
	multiplicative-expression
	additive-expression + multiplicative-expression
	additive-expression - multiplicative-expression
	*/

	TExpression2* pExpressionLeft;
	MultiplicativeExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_PLUS_SIGN:
		case TK_HYPHEN_MINUS:
		{
			TBinaryExpression *pBinaryExpression = 
				TBinaryExpression_Create();
			GetPosition(ctx, &pBinaryExpression->Position);
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			
			Match(ctx);
			TExpression2* pExpressionRight;
			MultiplicativeExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_PLUS_SIGN:
		case TK_HYPHEN_MINUS:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			AdditiveExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

}

void ShiftExpression(Parser* ctx, TExpression2** ppExpression)
{

	/*(6.5.7) shift-expression:
	additive-expression
	shift-expression << additive-expression
	shift-expression >> additive-expression
	*/


	TExpression2* pExpressionLeft;
	AdditiveExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_GREATERGREATER:
		case TK_LESSLESS:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			AdditiveExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_GREATERGREATER:
		case TK_LESSLESS:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			ShiftExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}
}

void RelationalExpression(Parser* ctx, TExpression2** ppExpression)
{
	/*
	(6.5.8) relational-expression:
	shift-expression
	relational-expression < shift-expression
	relational-expression > shift-expression
	relational-expression <= shift-expression
	relational-expression >= shift-expression
	*/

	TExpression2* pExpressionLeft;
	ShiftExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_LESS_THAN_SIGN:
		case TK_GREATER_THAN_SIGN:
		case TK_GREATEREQUAL:
		case TK_LESSEQUAL:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			ShiftExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_LESS_THAN_SIGN:
		case TK_GREATER_THAN_SIGN:
		case TK_GREATEREQUAL:
		case TK_LESSEQUAL:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			RelationalExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

}

void EqualityExpression(Parser* ctx, TExpression2** ppExpression)
{
	/*(6.5.9) equality-expression:
	relational-expression
	equality-expression == relational-expression
	equality-expression != relational-expression
	*/

	TExpression2* pExpressionLeft;
	RelationalExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_EQUALEQUAL:
		case TK_NOTEQUAL:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			RelationalExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_EQUALEQUAL:
		case TK_NOTEQUAL:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			EqualityExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}
}

void AndExpression(Parser* ctx, TExpression2 **ppExpression)
{
	/*(6.5.10) AND-expression:
	equality-expression
	AND-expression & equality-expression
	*/

	TExpression2* pExpressionLeft;
	EqualityExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_AMPERSAND:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			EqualityExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_AMPERSAND:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			AndExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}
}

void ExclusiveOrExpression(Parser* ctx, TExpression2** ppExpression)
{
	/*
	(6.5.11) exclusive-OR-expression:
	AND-expression
	exclusive-OR-expression ^ AND-expression
	*/

	TExpression2* pExpressionLeft;
	AndExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_CIRCUMFLEX_ACCENT:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			AndExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_CIRCUMFLEX_ACCENT:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			ExclusiveOrExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

}

void InclusiveOrExpression(Parser* ctx, TExpression2**ppExpression)
{

	/*
	(6.5.12) inclusive-OR-expression:
	exclusive-OR-expression
	inclusive-OR-expression | exclusive-OR-expression
	*/

	TExpression2* pExpressionLeft;
	ExclusiveOrExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_VERTICAL_LINE:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			ExclusiveOrExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_VERTICAL_LINE:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			InclusiveOrExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}
}

void LogicalAndExpression(Parser* ctx, TExpression2** ppExpression)
{

	/*
	(6.5.13) logical-AND-expression:
	inclusive-OR-expression
	logical-AND-expression && inclusive-OR-expression
	*/

	TExpression2* pExpressionLeft;
	InclusiveOrExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_ANDAND:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			GetPosition(ctx, &pBinaryExpression->Position);
			Match(ctx);
			TExpression2* pExpressionRight;
			InclusiveOrExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_ANDAND:
		{
			TBinaryExpression *pBinaryExpression = 
				TBinaryExpression_Create();

			GetPosition(ctx, &pBinaryExpression->Position);
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			
			Match(ctx);
			TExpression2* pExpressionRight;
			LogicalAndExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}
}

void LogicalOrExpression(Parser* ctx, TExpression2** ppExpression)
{
	/*(6.5.14) logical-OR-expression:
	 logical-AND-expression
	 logical-OR-expression || logical-AND-expression
	 */


	TExpression2* pExpressionLeft;
	LogicalAndExpression(ctx, &pExpressionLeft);
	*ppExpression = pExpressionLeft;

	Tokens token = Token(ctx);


	switch (token)
	{
		case TK_OROR:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			GetPosition(ctx, &pBinaryExpression->Position);
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			
			Match(ctx);
			TExpression2* pExpressionRight;
			LogicalAndExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}

	token = Token(ctx);

	switch (token)
	{
		case TK_OROR:
		{
			TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
			GetPosition(ctx, &pBinaryExpression->Position);
			pBinaryExpression->token = token;
			pBinaryExpression->pExpressionLeft = *ppExpression;
			
			Match(ctx);
			TExpression2* pExpressionRight;
			LogicalOrExpression(ctx, &pExpressionRight);
			pBinaryExpression->pExpressionRight = pExpressionRight;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;
	}
}


void ConditionalExpression(Parser* ctx, TExpression2**ppExpression)
{
	/*(6.5.15) conditional-expression:
	logical-OR-expression
	logical-OR-expression ? expression : conditional-expression
	*/
	TExpression2 * pLogicalOrExpressionLeft;
	LogicalOrExpression(ctx, &pLogicalOrExpressionLeft);
	*ppExpression = pLogicalOrExpressionLeft;

	if (Token(ctx) == TK_QUESTION_MARK)
	{
		Match(ctx);
		TExpression2* pTExpression2;
		Expression0(ctx, &pTExpression2);
		MatchToken(ctx, TK_COLON);

		TExpression2* pConditionalExpressionRight;
		ConditionalExpression(ctx, &pConditionalExpressionRight);

		TTernaryExpression* pTernaryExpression =
			TTernaryExpression_Create();
		pTernaryExpression->token = TK_QUESTION_MARK;
		pTernaryExpression->pExpressionLeft = pLogicalOrExpressionLeft;
		pTernaryExpression->pExpressionMiddle = pTExpression2;
		pTernaryExpression->pExpressionRight = pConditionalExpressionRight;
		*ppExpression = (TExpression2*)pTernaryExpression;
	}


}

void AssignmentExpression(Parser* ctx, TExpression2** ppExpression)
{
	/*(6.5.16) assignment-expression:
	conditional-expression
	unary-expression assignment-operator assignment-expression

	(6.5.16) assignment-operator: one of
	= *= /= %= += -= <<= >>= &= ^= |=
	*/


	//Não sei se eh  conditional-expression ou
	//unary-expression
	//Mas a conditional-expression faz tambem a
	//unary-expression
	TExpression2* pConditionalExpressionLeft;
	ConditionalExpression(ctx, &pConditionalExpressionLeft);
	*ppExpression = pConditionalExpressionLeft;

	Tokens token = Token(ctx);

	switch (token)
	{

		case TK_EQUALS_SIGN:
		case TK_MULTIEQUAL:
		case TK_DIVEQUAL:
		case TK_PERCENT_EQUAL:
		case TK_PLUSEQUAL:
		case TK_MINUS_EQUAL:
		case TK_LESSLESSEQUAL:
		case TK_GREATERGREATEREQUAL:
		case TK_ANDEQUAL:
		case TK_CARETEQUAL:
		case TK_OREQUAL:
		{
			Match(ctx);
			//Significa que o anterior deve ser do tipo  unary-expression
			//embora tenhamos feito o parser de conditional-expression
			//se nao for é erro.
			TExpression2* pAssignmentExpressionRight;
			AssignmentExpression(ctx, &pAssignmentExpressionRight);

			TBinaryExpression *pBinaryExpression =
				TBinaryExpression_Create();
			GetPosition(ctx, &pBinaryExpression->Position);

			pBinaryExpression->pExpressionLeft = *ppExpression;
			pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
			pBinaryExpression->token = token;
			*ppExpression = (TExpression2*)pBinaryExpression;
		}
		break;

		default:
			//É apenas conditional-expression
			break;
	}
}

void Expression0(Parser* ctx, TExpression2** ppExpression)
{
	*ppExpression = NULL; //out
	/*
	(6.5.17) expression:
	assignment-expression
	expression , assignment-expression
	*/
	TExpression2* pAssignmentExpressionLeft;
	AssignmentExpression(ctx, &pAssignmentExpressionLeft);
	*ppExpression = pAssignmentExpressionLeft;

	Tokens token = Token(ctx);

	if (token == TK_COMMA)
	{
		TExpression2* pAssignmentExpressionRight;
		Match(ctx);
		Expression0(ctx, &pAssignmentExpressionRight);

		TBinaryExpression* pBinaryExpression =
			TBinaryExpression_Create();
		GetPosition(ctx, &pBinaryExpression->Position);
		pBinaryExpression->pExpressionLeft = *ppExpression;
		pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
		pBinaryExpression->token = TK_COMMA;
		
		*ppExpression = (TExpression2*)pBinaryExpression;
	}
}

void ConstantExpression(Parser* ctx, TExpression2** ppExpression)
{
	*ppExpression = NULL; //out

	/*
	(6.6) constant-expression:
	conditional-expression
	*/
	ConditionalExpression(ctx, ppExpression);
}


///////////////////////////////////////////////////////////////////////////////


void Designator(Parser* ctx, TDesignator* pDesignator);
void Designator_List(Parser* ctx, TDesignatorList* pDesignatorList);
void Designation(Parser* ctx, TDesignatorList* pDesignatorList);
void Initializer_List(Parser* ctx, TInitializerList* pInitializerList);
//void Assignment_Expression(Parser* ctx, TExpressionStatement* pExpressionStatement, Tokens endToken1, Tokens endToken2);
bool Statement(Parser* ctx, TStatement** ppStatement);
//void Constant_Expression(Parser* ctx, Tokens endToken1, Tokens endToken2, ScannerItemStack* outStack);
void Compound_Statement(Parser* ctx, TStatement** ppStatement);
void Expression(Parser* ctx, TExpression2** pExpression, Tokens endToken1, Tokens endToken2);
void Parameter_Declaration(Parser* ctx, TParameterDeclaration* pParameterDeclaration);
bool Declaration(Parser* ctx, TAnyDeclaration** ppDeclaration);
void Type_Qualifier_ListOpt(Parser* ctx, TTypeQualifier* pQualifier);
bool Declaration_Specifiers(Parser* ctx, TDeclarationSpecifiers* pDeclarationSpecifiers);
void Declarator(Parser* ctx, TDeclarator* pTDeclarator2);
bool Type_Specifier(Parser* ctx, TTypeSpecifier** ppTypeSpecifier, int* typedefCount);
bool Type_Qualifier(Parser* ctx, TTypeQualifier* pQualifier);
void Initializer(Parser* ctx,
	TInitializer** ppInitializer,
	Tokens endToken1,
	Tokens endToken2);


void Expression_Statement(Parser* ctx, TStatement** ppStatement)
{
	/*
	expression-statement:
	expressionopt;
	*/
	TExpressionStatement* pExpression = TExpressionStatement_Create();
	*ppStatement = (TStatement*)pExpression;
	Tokens token = Token(ctx);

	if (token != TK_SEMICOLON)
	{
		Expression0(ctx, &pExpression->pExpression);
	}

	MatchToken(ctx, TK_SEMICOLON);
}

void Selection_Statement(Parser* ctx, TStatement** ppStatement)
{
	/*
	selection-statement:
	if ( expression ) statement
	if ( expression ) statement else statement
	switch ( expression ) statement
	*/
	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_IF:
		{
			TIfStatement* pIfStatement = TIfStatement_Create();
			*ppStatement = (TStatement*)pIfStatement;
			Match(ctx);
			MatchToken(ctx, TK_LEFT_PARENTHESIS);
			//      TExpression0 * pExpression =
			//      NewObject(pStatement, "expression");
			Expression0(ctx, &pIfStatement->pConditionExpression);
			MatchToken(ctx, TK_RIGHT_PARENTHESIS);
			//TStatement0 * pTrueStatement =
			//NewObject(pStatement, "statement-true");
			Statement(ctx, &pIfStatement->pStatement);
			token = Token(ctx);

			if (token == TK_ELSE)
			{
				Match(ctx);
				// TStatement0 * pElseStatement =
				//  NewObject(pStatement, "statement-else");
				Statement(ctx, &pIfStatement->pElseStatement);
			}
		}
		break;

		case TK_SWITCH:
		{
			TSwitchStatement* pSelectionStatement = TSwitchStatement_Create();
			*ppStatement = (TStatement*)pSelectionStatement;
			Match(ctx);
			MatchToken(ctx, TK_LEFT_PARENTHESIS);
			//TExpression0 * pExpression =
			//NewObject(pStatement, "expression");
			Expression0(ctx, &pSelectionStatement->pConditionExpression);
			MatchToken(ctx, TK_RIGHT_PARENTHESIS);
			//TStatement0 * pStatement0 =
			// NewObject(pStatement, "statement");
			Statement(ctx, &pSelectionStatement->pExpression);
		}
		break;

		default:
			ASSERT(false);
			break;
	}
}

void Jump_Statement(Parser* ctx, TStatement** ppStatement)
{
	/*
	jump-statement:
	goto identifier ;
	continue ;
	break ;
	return expressionopt ;
	*/
	//jump-statement
	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_GOTO:
		{
			TJumpStatement* pJumpStatement = TJumpStatement_Create();
			pJumpStatement->token = token;
			*ppStatement = (TStatement*)pJumpStatement;
			Match(ctx);
			MatchToken(ctx, TK_identifier);
		}
		break;

		case TK_CONTINUE:
		{
			TJumpStatement* pJumpStatement = TJumpStatement_Create();
			pJumpStatement->token = token;
			*ppStatement = (TStatement*)pJumpStatement;
			Match(ctx);
			MatchToken(ctx, TK_SEMICOLON);
		}
		break;

		case TK_BREAK:
		{
			TJumpStatement* pJumpStatement = TJumpStatement_Create();
			pJumpStatement->token = token;
			*ppStatement = (TStatement*)pJumpStatement;
			Match(ctx);
			MatchToken(ctx, TK_SEMICOLON);
		}
		break;

		case TK_RETURN:
		{
			TReturnStatement* pReturnStatement = TReturnStatement_Create();

			*ppStatement = (TStatement*)pReturnStatement;
			token = Match(ctx);

			if (token != TK_SEMICOLON)
			{
				Expression0(ctx, &pReturnStatement->pExpression);
			}

			MatchToken(ctx, TK_SEMICOLON);
		}
		break;

		default:
			ASSERT(false);
			break;
	}
}

void Iteration_Statement(Parser* ctx, TStatement** ppStatement)
{
	/*
	iteration-statement:
	while ( expression ) statement
	do statement while ( expression ) ;
	for ( expressionopt ; expressionopt ; expressionopt ) statement
	for ( declaration expressionopt ; expressionopt ) statement
	*/
	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_WHILE:
		{
			TWhileStatement* pWhileStatement = TWhileStatement_Create();
			*ppStatement = (TStatement*)pWhileStatement;
			Match(ctx);
			MatchToken(ctx, TK_LEFT_PARENTHESIS);
			Expression0(ctx, &pWhileStatement->pExpression);
			MatchToken(ctx, TK_RIGHT_PARENTHESIS);
			Statement(ctx, &pWhileStatement->pStatement);
		}
		break;

		case TK_DO:
		{
			TDoStatement* pDoStatement = TDoStatement_Create();
			*ppStatement = (TStatement*)pDoStatement;
			Match(ctx);
			Statement(ctx, &pDoStatement->pStatement);
			MatchToken(ctx, TK_WHILE);
			MatchToken(ctx, TK_LEFT_PARENTHESIS);
			Expression0(ctx, &pDoStatement->pExpression);
			MatchToken(ctx, TK_RIGHT_PARENTHESIS);
			MatchToken(ctx, TK_SEMICOLON);
		}
		break;

		case TK_FOR:
		{
			TForStatement* pIterationStatement = TForStatement_Create();
			*ppStatement = (TStatement*)pIterationStatement;
			Match(ctx);
			token = MatchToken(ctx, TK_LEFT_PARENTHESIS);

			//primeira expressao do for
			if (token != TK_SEMICOLON)
			{
				//
				//for (expressionopt; expressionopt; expressionopt) statement
				//for (declaration expressionopt; expressionopt) statement

				bool bHasDeclaration = Declaration(ctx, &pIterationStatement->pInitDeclarationOpt);

				if (bHasDeclaration)
				{
					token = Token(ctx);

					if (token != TK_SEMICOLON)
					{
						//Esta eh a 2 expressao do for, a declaracao ja comeu 1
						Expression0(ctx, &pIterationStatement->pExpression2);
						MatchToken(ctx, TK_SEMICOLON);
					}
					else
					{
						//segunda expressao vazia
						MatchToken(ctx, TK_SEMICOLON);
					}
				}

				else
				{
					token = Token(ctx);

					if (token != TK_SEMICOLON)
					{
						//primeira expressao do for
						Expression0(ctx, &pIterationStatement->pExpression1);
						MatchToken(ctx, TK_SEMICOLON);
					}

					token = Token(ctx);

					if (token != TK_SEMICOLON)
					{
						//segunda expressao do for
						Expression0(ctx, &pIterationStatement->pExpression2);
						MatchToken(ctx, TK_SEMICOLON);
					}

					else
					{
						//segunda expressao vazia
						MatchToken(ctx, TK_SEMICOLON);
					}

				}
			}

			else
			{
				//primeira expressao do for vazia
				MatchToken(ctx, TK_SEMICOLON);
				token = Token(ctx);

				if (token != TK_SEMICOLON)
				{
					//Esta eh a 2 expressao do for, a declaracao ja comeu 1
					Expression0(ctx, &pIterationStatement->pExpression2);
					MatchToken(ctx, TK_SEMICOLON);
				}

				else
				{
					//segunda expressao do for vazia tb
					MatchToken(ctx, TK_SEMICOLON);
				}
			}

			token = Token(ctx);

			//terceira expressao do for
			if (token != TK_RIGHT_PARENTHESIS)
			{
				Expression0(ctx, &pIterationStatement->pExpression3);
			}

			MatchToken(ctx, TK_RIGHT_PARENTHESIS);
			Statement(ctx, &pIterationStatement->pStatement);
		}
		break;

		default:
			ASSERT(false);
			break;
	}
}


void Labeled_Statement(Parser* ctx, TStatement** ppStatement)
{
	/*
	labeled-statement:
	identifier : statement (ver Labeled_StatementLabel)
	case constant-expression : statement
	default : statement
	*/
	TLabeledStatement* pLabeledStatement = TLabeledStatement_Create();
	*ppStatement = (TStatement*)pLabeledStatement;
	Tokens token = Token(ctx);
	pLabeledStatement->token = token;

	if (token == TK_identifier)
	{
		//aqui nao eh um tipo
		String_Set(&pLabeledStatement->Identifier, Lexeme(ctx));
		Match(ctx);
		MatchToken(ctx, TK_COLON);
		Statement(ctx, &pLabeledStatement->pStatementOpt);
	}

	else if (token == TK_case)
	{
		Match(ctx);
		ConstantExpression(ctx, &pLabeledStatement->pExpression);
		MatchToken(ctx, TK_COLON);
		Statement(ctx, &pLabeledStatement->pStatementOpt);				
	}

	else if (token == TK_DEFAULT)
	{
		Match(ctx);
		MatchToken(ctx, TK_COLON);
		Statement(ctx, &pLabeledStatement->pStatementOpt);
	}
}

void Asm_Statement(Parser* ctx, TStatement** ppStatement)
{
	/*
	__asm assembly-instruction ;opt
	__asm { assembly-instruction-list };opt
	*/
	TAsmStatement * pAsmStatement = TAsmStatement_Create();
	*ppStatement = (TStatement*)pAsmStatement;
	MatchToken(ctx, TK__Asm);
	Tokens token = Token(ctx);

	if (token == TK_LEFT_CURLY_BRACKET)
	{
		Match(ctx);

		for (; ;)
		{
			if (ErrorOrEof(ctx))
			{
				break;
			}

			token = Token(ctx);

			if (token == TK_RIGHT_CURLY_BRACKET)
			{
				Match(ctx);
				break;
			}

			Match(ctx);
		}
	}

	else
	{
		//sem ;
		//    __asm int 0x2c
		//chato
		token = Token(ctx);

		for (; ;)
		{
			if (ErrorOrEof(ctx))
			{
				break;
			}

			token = Token(ctx);

			if (token == TK_RIGHT_CURLY_BRACKET)
			{
				//__asm mov al, 2   __asm mov dx, 0xD007   __asm out dx, al
				//chute na verdade..
				//dificil saber aonde termina
				//https://msdn.microsoft.com/en-us/library/45yd4tzz.aspx
				break;
			}

			if (token == TK_SEMICOLON)
			{
				break;
			}

			Match(ctx);
		}
	}

	//opcional
	token = Token(ctx);

	if (token == TK_SEMICOLON)
	{
		Match(ctx);
	}
}

bool Statement(Parser* ctx, TStatement** ppStatement)
{
	ASSERT(*ppStatement == NULL);

	if (HasErrors(ctx))
	{
		return false;
	}

	bool bResult = false;
	Tokens token = Token(ctx);
	const char * lexeme = Lexeme(ctx);

	switch (token)
	{
		case TK__Asm:
			bResult = true;
			Asm_Statement(ctx, ppStatement);
			break;

		case TK_LEFT_CURLY_BRACKET:
		{
			bResult = true;
			Compound_Statement(ctx, ppStatement);
		}
		break;

		case TK_case:
		case TK_DEFAULT:
			bResult = true;
			Labeled_Statement(ctx, ppStatement);
			break;

		case TK_SWITCH:
			bResult = true;
			Selection_Statement(ctx, ppStatement);
			break;

		case TK_IF:
			bResult = true;
			Selection_Statement(ctx, ppStatement);
			break;

		case TK_ELSE:
			//Ele tem que estar fazendo os statement do IF!
			bResult = true;
			Match(ctx); //else
			//poderia retornar uma coisa so  p dizer q eh else
			//Statement(ctx, obj);
			break;

			//iteration-statement
		case TK_WHILE:
		case TK_FOR:
		case TK_DO:
			bResult = true;
			Iteration_Statement(ctx, ppStatement);
			break;

			//jump-statement
		case TK_GOTO:
		case TK_CONTINUE:
		case TK_BREAK:
		case TK_RETURN:
			bResult = true;
			Jump_Statement(ctx, ppStatement);
			break;

			//lista de first para expressões
			//expression-statement
		case TK_LEFT_PARENTHESIS:
		case TK_SEMICOLON:
		
		case TK_DECIMAL_INTEGER:
		case TK_FLOAT_NUMBER:
		case TK_string_literal:
		

		//unary
		case TK_PLUSPLUS:
		case TK_MINUSMINUS:

		case TK_SIZEOF:

		//unary-operator
		case TK_AMPERSAND:
		case TK_ASTERISK:
		case TK_PLUS_SIGN:
		case TK_HYPHEN_MINUS:
		case TK_TILDE:
		case TK_EXCLAMATION_MARK:
			//unary-operator-extension
		case TK_ANDAND: //&&

			bResult = true;
			Expression_Statement(ctx, ppStatement);
			break;

		case TK_identifier:

			if (DeclarationsMap_IsTypeDef(&ctx->Symbols, lexeme))
			{
				//É uma declaracao
			}
			else
			{
				if (LookAheadToken(ctx) == TK_COLON)
				{
					//era um label..
					Labeled_Statement(ctx, ppStatement);
				}

				else
				{
					Expression_Statement(ctx, ppStatement);
				}

				bResult = true;
			}

			break;

		case TK_inline:
		case TK__Noreturn:
		case TK__Alignas:
		
		//type-qualifier
		case TK_const:
		case TK_restrict:
		case TK_volatile:
		case TK__Atomic:
		
		//type-qualifier-extensions 
		case TK_OPT_QUALIFIER:
		case TK_OWN_QUALIFIER:
		case TK_DTOR_QUALIFIER:
		case TK_MDTOR_QUALIFIER:
		//
		
		case TK_typedef:
		case TK_extern:
		case TK_static:
		case TK__Thread_local:
		case TK_auto:
		case TK_register:
		case TK_void:
		case TK_char:
		case TK_short:
		case TK_int:
		case TK_long:
		case TK_float:
		case TK_double:
		case TK_signed:
		case TK_unsigned:
		case TK__Bool:
		case TK__Complex:
		case TK_struct:
		case TK_union:
		case TK_enum:
			bResult = false;
			break;

		default:
			ASSERT(false);
			//bResult = true;
			//SetType(pStatement, "expression-statement");
			//Expression_Statement(ctx, pStatement);
			break;
	}

	return bResult;
}

void Block_Item(Parser* ctx, TBlockItem** ppBlockItem)
{
	/*
	block-item:
	declaration
	statement
	*/
	*ppBlockItem = NULL;
	TStatement* pStatement = NULL;

	if (Statement(ctx, &pStatement))
	{
		*ppBlockItem = (TAnyDeclaration*)pStatement;
		ASSERT(*ppBlockItem != NULL);
	}

	else
	{
		TAnyDeclaration* pDeclaration;
		Declaration(ctx, &pDeclaration);
		*ppBlockItem = (TAnyDeclaration*)pDeclaration;
		ASSERT(*ppBlockItem != NULL);
	}
}

void Block_Item_List(Parser* ctx, TBlockItemList* pBlockItemList)
{
	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		TBlockItem* pBlockItem = NULL;
		Block_Item(ctx, &pBlockItem);
		TBlockItemList_Push(pBlockItemList, pBlockItem);
		Tokens token = Token(ctx);

		if (token == TK_RIGHT_CURLY_BRACKET)
		{
			//terminou
			break;
		}

		if (ErrorOrEof(ctx))
			break;
	}
}

void Compound_Statement(Parser* ctx, TStatement** ppStatement)
{
	/*
	compound-statement:
	{ block-item-listopt }
	*/
	TCompoundStatement* pCompoundStatement = TCompoundStatement_Create();
	*ppStatement = (TStatement*)pCompoundStatement;
	MatchToken(ctx, TK_LEFT_CURLY_BRACKET);
	Tokens token = Token(ctx);

	if (token != TK_RIGHT_CURLY_BRACKET)
	{
		Block_Item_List(ctx, &pCompoundStatement->BlockItemList);
	}

	MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);
}

void Struct_Or_Union(Parser* ctx,
	TStructUnionSpecifier* pStructUnionSpecifier)
{
	/*
	struct-or-union:
	struct
	union
	*/
	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_struct:
			pStructUnionSpecifier->bIsStruct = true;
			Match(ctx);
			break;

		case TK_union:
			pStructUnionSpecifier->bIsStruct = false;
			Match(ctx);
			break;

		default:
			ASSERT(false);
			break;
	}
}

void Static_Assert_Declaration(Parser* ctx, TStaticAssertDeclaration* pStaticAssertDeclaration)
{
	/*
	static_assert-declaration:
	_Static_assert ( constant-expression , string-literal ) ;
	*/
	Tokens token = Token(ctx);

	if (token == TK__Static_assert)
	{
		Match(ctx);
		MatchToken(ctx, TK_LEFT_PARENTHESIS);

		ConstantExpression(ctx,
			&pStaticAssertDeclaration->pConstantExpression);

		MatchToken(ctx, TK_COMMA);
		MatchToken(ctx, TK_string_literal);
		MatchToken(ctx, TK_RIGHT_PARENTHESIS);
		MatchToken(ctx, TK_SEMICOLON);
	}
}

void Specifier_Qualifier_List(Parser* ctx,
	TTypeQualifier* pQualifiers,
	TTypeSpecifier** ppTypeSpecifier)
{
	/*specifier-qualifier-list:
	type-specifier specifier-qualifier-listopt
	type-qualifier specifier-qualifier-listopt
	*/
	int typdefcount = 0;
	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		if (Type_Specifier(ctx, ppTypeSpecifier, &typdefcount))
		{
		}
		else if (Type_Qualifier(ctx, pQualifiers))
		{
		}
		else
		{
			break;
		}
	}
}

void Struct_Declarator(Parser* ctx,

	TStructDeclarator* pTDeclarator2)
{
	/**
	struct-declarator:
	declarator
	declaratoropt : constant-expression
	*/
	Tokens token = Token(ctx);

	if (token == TK_COLON)
	{
		//AST TODO
		Match(ctx);
		TExpression2* p = NULL;
		ConstantExpression(ctx, &p);
		TExpression2_Delete(p);
	}

	else
	{
		Declarator(ctx, pTDeclarator2);
		token = Token(ctx);

		if (token == TK_COLON)
		{
			Match(ctx);
			TExpression2* p = NULL;
			ConstantExpression(ctx, &p);
			TExpression2_Delete(p);
		}

		else if (token == TK_EQUALS_SIGN)
		{
			//TODO COMPILER EXTENSION! SHOW ERROR IF EXTENSIONS NOT ENABLED
			//struct { int i = 1; }
			Match(ctx);
			Initializer(ctx, &pTDeclarator2->pInitializer, TK_SEMICOLON, TK_SEMICOLON);
		}
	}
}

void Struct_Declarator_List(Parser* ctx,

	TStructDeclaratorList* pStructDeclarationList)
{
	/*
	struct-declarator-list:
	struct-declarator
	struct-declarator-list , struct-declarator
	*/
	TStructDeclarator* pTDeclarator2 = TDeclarator_Create();
	TDeclaratorList_Push(pStructDeclarationList, pTDeclarator2);
	Struct_Declarator(ctx, pTDeclarator2);

	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		Tokens token = Token(ctx);

		if (token == TK_COMMA)
		{
			Match(ctx);
			Struct_Declarator_List(ctx, pStructDeclarationList);
		}

		else if (token == TK_SEMICOLON)
		{
			break;
		}

		else
		{
			SetError(ctx, "Struct_Declarator_List unexpected");
			break;
		}
	}
}

void Struct_Declaration(Parser* ctx,
	TAnyStructDeclaration** ppStructDeclaration)
{
	/**
	struct-declaration:
	specifier-qualifier-list struct-declarator-listopt ;
	static_assert-declaration
	*/
	Tokens token = Token(ctx);

	if (token != TK__Static_assert)
	{
		TStructDeclaration* pStructDeclarationBase = TStructDeclaration_Create();
		*ppStructDeclaration = (TAnyStructDeclaration*)pStructDeclarationBase;
		Specifier_Qualifier_List(ctx,
			&pStructDeclarationBase->Qualifier,
			&pStructDeclarationBase->pSpecifier);
		token = Token(ctx);

		if (token != TK_SEMICOLON)
		{
			Struct_Declarator_List(ctx,
				&pStructDeclarationBase->DeclaratorList);
			MatchToken(ctx, TK_SEMICOLON);
		}

		else
		{
			MatchToken(ctx, TK_SEMICOLON);
		}
	}

	else
	{
		TStaticAssertDeclaration* pStaticAssertDeclaration = TStaticAssertDeclaration_Create();
		*ppStructDeclaration = (TAnyStructDeclaration*)pStaticAssertDeclaration;
		Static_Assert_Declaration(ctx, pStaticAssertDeclaration);
	}
}

void Struct_Declaration_List(Parser* ctx,

	TStructDeclarationList* pStructDeclarationList)
{
	/*
	struct-declaration-list:
	struct-declaration
	struct-declaration-list struct-declaration
	*/
	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		Tokens token = Token(ctx);

		if (token == TK_RIGHT_CURLY_BRACKET)
			break;

		TAnyStructDeclaration* pStructDeclaration = NULL;
		Struct_Declaration(ctx, &pStructDeclaration);
		TStructDeclarationList_Push(pStructDeclarationList, pStructDeclaration);
	}
}

void Struct_Or_Union_Specifier(Parser* ctx,
	TStructUnionSpecifier* pStructUnionSpecifier)
{
	/*
	struct-or-union-specifier:
	struct-or-union identifieropt { struct-declaration-list }
	struct-or-union identifier
	*/
	Struct_Or_Union(ctx, pStructUnionSpecifier);//TODO
	Tokens token0 = Token(ctx);
	const char* lexeme = Lexeme(ctx);

	if (token0 == TK_identifier)
	{
		String_Set(&pStructUnionSpecifier->Name, lexeme);
	}

	else
	{
		const char* name = GetName();
		String_Set(&pStructUnionSpecifier->Name, name);
	}

	//tem que vir depois
	Match(ctx);
	Tokens token1 = Token(ctx);

	if (token0 == TK_identifier)
	{
		//ja foi feito match do identificador
		if (token1 == TK_LEFT_CURLY_BRACKET)
		{
			Match(ctx);
			Struct_Declaration_List(ctx,
				&pStructUnionSpecifier->StructDeclarationList);
			MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);
		}

		else
		{
			//
		}
	}
	else if (token0 == TK_LEFT_CURLY_BRACKET)
	{
		//const char* name = GetName();
		//ja foi feito o Match do {
		Struct_Declaration_List(ctx, &pStructUnionSpecifier->StructDeclarationList);
		MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);
	}

	else
	{
		SetError(ctx, "expected name or {");
	}
}

void Enumeration_Constant(Parser* ctx,
	TEnumerator* pEnumerator2)
{
	const char* lexeme = Lexeme(ctx);
	String_Set(&pEnumerator2->Name, lexeme);

	//TODO colocar um ponteiro
	Map_Set(&ctx->EnumMap, lexeme, (void*)1);

	MatchToken(ctx, TK_identifier);
}

bool EnumeratorC(Parser* ctx, TEnumerator* pEnumerator2)
{
	/*
	enumerator:
	enumeration-constant
	enumeration-constant = constant-expression
	*/
	bool bValueAssigned = false;
	Enumeration_Constant(ctx, pEnumerator2);


	Tokens token = Token(ctx);

	if (token == TK_EQUALS_SIGN)
	{
		Match(ctx);
		ConstantExpression(ctx, &pEnumerator2->pExpression);
		bValueAssigned = true;
	}

	return bValueAssigned;
}

void Enumerator_List(Parser* ctx,
	TEnumeratorList* pEnumeratorList2)
{
	/*
	enumerator-list:
	enumerator
	enumerator-list , enumerator
	*/
	int currentValue = 0;
	//pelo menos 1
	TEnumerator* pEnumerator2 = TEnumerator_Create();
	TEnumeratorList_Push(pEnumeratorList2, pEnumerator2);

	if (!EnumeratorC(ctx, pEnumerator2))
	{
		//atribui um valor
		//pEnumerator2->Value = currentValue;
		currentValue++;
	}

	else
	{
		//TODO
		//comeca com o valor do primeiro?
		//currentValue = pEnumerator2->Value;
		currentValue++;
	}

	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		Tokens token = Token(ctx);

		if (token == TK_COMMA)
		{
			//tem mais
			Match(ctx);
			token = Token(ctx);

			//o enum aceita uma , no fim
			if (token != TK_RIGHT_CURLY_BRACKET)
			{
				TEnumerator* pEnumerator3 = TEnumerator_Create();
				TEnumeratorList_Push(pEnumeratorList2, pEnumerator3);

				if (!EnumeratorC(ctx, pEnumerator3))
				{
					//atribui um valor
					//pEnumerator2->Value = currentValue;
					currentValue++;
				}
			}
		}

		else
		{
			ASSERT(token == TK_RIGHT_CURLY_BRACKET);
			//acabou
			break;
		}
	}
}

void Enum_Specifier(Parser* ctx, TEnumSpecifier* pEnumSpecifier2)
{
	/*
	enum-specifier:
	enum identifieropt { enumerator-list }
	enum identifieropt { enumerator-list, }
	enum identifier
	*/
	MatchToken(ctx, TK_enum);
	Tokens token = Token(ctx);

	if (token == TK_identifier)
	{
		const char* lexeme = Lexeme(ctx);
		String_Set(&pEnumSpecifier2->Name, lexeme);
	}

	else
	{
		const char* name = GetName();
		String_Set(&pEnumSpecifier2->Name, name);
	}

	Match(ctx);

	if (token == TK_identifier)
	{
		//Ja fez Match do identifier
		token = Token(ctx);

		if (token == TK_LEFT_CURLY_BRACKET)
		{
			Match(ctx);
			Enumerator_List(ctx, &pEnumSpecifier2->EnumeratorList);
			MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);
		}

		else
		{
			//enum identifier
			//                  ^
		}
	}
	else if (token == TK_LEFT_CURLY_BRACKET)
	{
		//ja foi feito o Match do {
		Enumerator_List(ctx, &pEnumSpecifier2->EnumeratorList);
		MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);
	}

	else
	{
		SetError(ctx, "expected enum name or {");
	}
}

bool Function_Specifier(Parser* ctx,
	TFunctionSpecifier* pFunctionSpecifier)
{
	/*
	function-specifier:
	inline
	_Noreturn
	*/
	bool bResult = false;
	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_inline:
			pFunctionSpecifier->bIsInline = true;
			Match(ctx);
			bResult = true;
			break;

		case TK__Noreturn:
			pFunctionSpecifier->bIsNoReturn = true;
			Match(ctx);
			bResult = true;
			break;

		default:
			break;
	}

	return bResult;
}

bool Storage_Class_Specifier(Parser* ctx,

	TStorageSpecifier* pStorageSpecifier)
{
	/*
	storage - class-specifier:
	typedef
	extern
	static
	_Thread_local
	auto
	register
	*/
	bool bResult = false;
	Tokens token = Token(ctx);

	//const char* lexeme = Lexeme(ctx);
	switch (token)
	{
		case TK_typedef:
			pStorageSpecifier->bIsTypedef = true;
			Match(ctx);
			bResult = true;
			break;

		case TK_extern:
			pStorageSpecifier->bIsExtern = true;
			Match(ctx);
			bResult = true;
			break;

		case TK_static:
			pStorageSpecifier->bIsStatic = true;
			Match(ctx);
			bResult = true;
			break;

		case TK__Thread_local:
			pStorageSpecifier->bIsThread_local = true;
			Match(ctx);
			bResult = true;
			break;

		case TK_auto:
			pStorageSpecifier->bIsAuto = true;
			Match(ctx);
			bResult = true;
			break;

		case TK_register:
			pStorageSpecifier->bIsRegister = true;
			Match(ctx);
			bResult = true;
			break;

		default:
			break;
	}

	return bResult;
}

void Parameter_List(Parser* ctx,
	TParameterList* pParameterList)
{
	/*
	parameter-list:
	parameter-declaration
	parameter-list, parameter-declaration
	*/
	Tokens token = Token(ctx);

	TParameterDeclaration*  pParameter = TParameterDeclaration_Create();
	TParameterList_Push(pParameterList,  pParameter);
	Parameter_Declaration(ctx, pParameter);

	//Tem mais?
	token = Token(ctx);
	if (token == TK_COMMA)
	{
		Match(ctx);
		Parameter_List(ctx, pParameterList);
	}
}



void AbstractDeclarator(Parser* ctx, TDeclarator* pTDeclarator2)
{
	/*
	abstract-declarator:
	pointer
	pointeropt direct-abstract-declarator
	*/
	//TODO!!! esta sendo usado como se fosse a mesma coisa?
	Declarator(ctx, pTDeclarator2);
}

bool AbstractDeclaratorOpt(Parser* ctx, TDeclarator* pTDeclarator2)
{
	bool bResult = false;
	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_ASTERISK:
			AbstractDeclarator(ctx, pTDeclarator2);
			break;
	}

	return bResult;
}


void DirectAbstractDeclarator(Parser* ctx)
{
	ASSERT(false);
	/*
	direct-abstract-declarator:
	 ( abstract-declarator )
	 direct-abstract-declaratoropt [ type-qualifier-listopt
	 assignment-expressionopt ]
	 direct-abstract-declaratoropt [ static type-qualifier-listopt
	 assignment-expression ]
	 direct-abstract-declaratoropt [ type-qualifier-list static
	 assignment-expression ]
	 direct-abstract-declaratoropt [ * ]
	 direct-abstract-declaratoropt ( parameter-type-listopt )
	*/

	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_LEFT_PARENTHESIS:
			//AbstractDeclarator(ctx, pTDeclarator2);
			break;

		case TK_LEFT_SQUARE_BRACKET:

			break;
	}
}


void Parameter_Declaration(Parser* ctx,
	TParameterDeclaration* pParameterDeclaration)
{
	/*
	parameter-declaration:
	declaration-specifiers declarator
	declaration-specifiers abstract-declaratoropt
	*/
	Declaration_Specifiers(ctx,
		&pParameterDeclaration->Specifiers);

	AbstractDeclarator(ctx, &pParameterDeclaration->Declarator);
}

void Parameter_Type_List(Parser* ctx,
	TParameterList* pParameterList)
{
	/*
	parameter-type-list:
	parameter-list
	parameter-list , ...
	*/
	//TODO  make ... as a type of parameter
	Parameter_List(ctx, pParameterList);
	Tokens token = Token(ctx);

	if (token == TK_DOTDOTDOT)
	{
		//TODO ADD this parameter
		Match(ctx);
	}
}

void Direct_DeclaratorCore(Parser* ctx, TDeclarator* pDeclarator2)
{

	//ja entra aqui como sendo um direct-declarator

	if (ErrorOrEof(ctx))
		return;


	/*
	direct-declarator:
	direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
	direct-declarator [ static type-qualifier-listopt assignment-expression ]
	direct-declarator [ type-qualifier-list static assignment-expression ]
	direct-declarator [ type-qualifier-listopt * ]
	direct-declarator ( parameter-type-list )
	direct-declarator ( identifier-listopt )
	*/

	Tokens token = Token(ctx);
	switch (token)
	{
		case TK_LEFT_SQUARE_BRACKET:
		{
			/*
			direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
			direct-declarator [ static type-qualifier-listopt assignment-expression ]
			direct-declarator [ type-qualifier-list static assignment-expression ]
			direct-declarator [ type-qualifier-listopt * ]
			*/
			pDeclarator2->token = token;
			token = MatchToken(ctx, TK_LEFT_SQUARE_BRACKET);
			if (token == TK_static)
			{
			}
			else
			{
        if (token != TK_RIGHT_SQUARE_BRACKET)
        {
          ASSERT(pDeclarator2->pExpression == NULL);
          AssignmentExpression(ctx, &pDeclarator2->pExpression);
        }
        else
        {
          //array vazio é permitido se for o ultimo cara da struct          
          //struct X { int ElementCount;  int Elements[]; };           
        }
			}

			MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET);

		}
		break;
		case TK_LEFT_PARENTHESIS:
		{
			/*
			direct-declarator ( parameter-type-list )
			direct-declarator ( identifier-listopt )
			*/
			pDeclarator2->token = token;
			ASSERT(pDeclarator2->pParametersOpt == NULL);
			pDeclarator2->pParametersOpt = TParameterList_Create();
			token = MatchToken(ctx, TK_LEFT_PARENTHESIS);

			if (token != TK_RIGHT_PARENTHESIS)
			{
				//opt
				Parameter_Type_List(ctx, pDeclarator2->pParametersOpt);
			}
			MatchToken(ctx, TK_RIGHT_PARENTHESIS);

		}break;
	}

	//Tem mais?

	token = Token(ctx);
	switch (token)
	{
		case TK_LEFT_SQUARE_BRACKET:
			ASSERT(pDeclarator2->pDeclaratorOpt == NULL);
			pDeclarator2->pDeclaratorOpt = TDeclarator_Create();
			Direct_DeclaratorCore(ctx, pDeclarator2->pDeclaratorOpt);
			break;
		case TK_LEFT_PARENTHESIS:
		{
			Tokens token2 = LookAheadToken(ctx);
			if (token2 == TK_ASTERISK)
			{
				ASSERT(false); //cai aqui?
				MatchToken(ctx, TK_LEFT_PARENTHESIS);
				Declarator(ctx, pDeclarator2);
				MatchToken(ctx, TK_RIGHT_PARENTHESIS);
			}
			else
			{
				ASSERT(pDeclarator2->pDeclaratorOpt == NULL);
				pDeclarator2->pDeclaratorOpt = TDeclarator_Create();
				Direct_DeclaratorCore(ctx, pDeclarator2->pDeclaratorOpt);
			}
		}	break;

	}
}

void Direct_Declarator(Parser* ctx, TDeclarator* pDeclarator2)
{
	/*
	direct-declarator:
	identifier
	( declarator )
	direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
	direct-declarator [ static type-qualifier-listopt assignment-expression ]
	direct-declarator [ type-qualifier-list static assignment-expression ]
	direct-declarator [ type-qualifier-listopt * ]
	direct-declarator ( parameter-type-list )
	direct-declarator ( identifier-listopt )
	*/


	if (ErrorOrEof(ctx))
		return;



	Tokens token = Token(ctx);

	switch (token)
	{
		case TK_LEFT_PARENTHESIS:
		{
			
			MatchToken(ctx, TK_LEFT_PARENTHESIS);
			//ASSERT(pDeclarator2->pDeclaratorOpt == NULL);
			//pDeclarator2->pDeclaratorOpt = TDeclarator_Create();
			Declarator(ctx, pDeclarator2);
			
			pDeclarator2->token = token;
			
			MatchToken(ctx, TK_RIGHT_PARENTHESIS);

		}
		break;

		case TK_identifier:
		{
			//identifier
			pDeclarator2->token = token;
			const char* lexeme = Lexeme(ctx);
			String_Set(&pDeclarator2->Name, lexeme);
            pDeclarator2->Position.Line = GetCurrentLine(ctx);
            pDeclarator2->Position.FileIndex = GetFileIndex(ctx);

			Match(ctx);

		}  break;
	}

	//Tem mais?

	token = Token(ctx);
	switch (token)
	{
		case TK_LEFT_PARENTHESIS:
		case TK_LEFT_SQUARE_BRACKET:
			ASSERT(pDeclarator2->pDeclaratorOpt == NULL);
			pDeclarator2->pDeclaratorOpt = TDeclarator_Create();
			Direct_DeclaratorCore(ctx, pDeclarator2->pDeclaratorOpt);
			break;
	}

}

bool Type_Qualifier(Parser* ctx, TTypeQualifier* pQualifier)
{
	/*
	type-qualifier:
	const
	restrict
	volatile
	_Atomic
	*/
	bool bResult = false;
	Tokens token = Token(ctx);

	//const char* lexeme = Lexeme(ctx);
	switch (token)
	{
		
		

		case TK_const:
			pQualifier->bIsConst = true;
			Match(ctx);
			bResult = true;
			break;

		case TK_restrict:
			pQualifier->bIsRestrict = true;
			Match(ctx);
			bResult = true;
			break;

		case TK_volatile:
			pQualifier->bIsVolatile = true;
			Match(ctx);
			bResult = true;
			break;

		case TK__Atomic:
			pQualifier->bIsAtomic = true;
			Match(ctx);
			bResult = true;
			break;
		
		//type-qualifier-extensions 
		case TK_OPT_QUALIFIER:
			pQualifier->bIsOpt = true;
			Match(ctx);
			bResult = true;
			break;
		case TK_OWN_QUALIFIER:
			pQualifier->bIsOwner = true;
			Match(ctx);
			bResult = true;
			break;
		case TK_DTOR_QUALIFIER:
			pQualifier->bIsDestructor = true;
			Match(ctx);
			bResult = true;
			break;
		case TK_MDTOR_QUALIFIER:
			pQualifier->bIsMemDestructor = true;
			Match(ctx);
			bResult = true;
			break;

		default:
			break;
	}

	return bResult;
}

void Type_Qualifier_ListOpt(Parser* ctx,
	TTypeQualifier* pQualifiers)
{
	/*
	type-qualifier-list:
	type-qualifier
	type-qualifier-list type-qualifier
	*/
	while (Type_Qualifier(ctx, pQualifiers))
	{
	}
}

int PointerOpt(Parser* ctx, TPointerList* pPointerList)
{
	/*
	exemplo
	int _wexecv(int const* const* _ArgList);
	*/
	/*
	pointer:
	* type-qualifier-listopt
	* type-qualifier-listopt pointer
	*/
	int ns = 0;
	//Empilha pointer to
	Tokens token = Token(ctx);

	while (IsTypeQualifierToken(token) ||
		   token == TK_ASTERISK)   //pointer
	{
		TPointer* pPointer = TPointer_Create();
		TPointerList_Push(pPointerList, pPointer);
		
		if (IsTypeQualifierToken(token))			
		{
			Type_Qualifier_ListOpt(ctx, &pPointer->Qualifier);
		}
		else if (token == TK_ASTERISK)
		{
			pPointer->bPointer = true;
			Match(ctx);
		}

		token = Token(ctx);
		ns++;
	}

	//Retorna numero de items empilhados
	return ns;
}

//pag 123 C
void Declarator(Parser* ctx, TDeclarator* pTDeclarator2)
{
	/*
	declarator:
	pointeropt direct-declarator
	*/
	PointerOpt(ctx, &pTDeclarator2->PointerList);

	Direct_Declarator(ctx, pTDeclarator2);
}


bool Alignment_Specifier(Parser* ctx,
	TAlignmentSpecifier* pAlignmentSpecifier)
{
	bool bResult = false;
	/*
	alignment - specifier:
	_Alignas(type - name)
	_Alignas(constant - expression)
	*/
	Tokens token = Token(ctx);

	if (token == TK__Alignas)
	{
		MatchToken(ctx, TK_LEFT_PARENTHESIS);
		ASSERT(false);//TODO
		MatchToken(ctx, TK_RIGHT_PARENTHESIS);
		bResult = true;
	}

	return bResult;
}

bool Type_Specifier(Parser* ctx,
	TTypeSpecifier** ppTypeSpecifier, int *typedefCount)
{
	/*
	type-specifier:
	void
	char
	short
	int
	long
	float
	double
	signed
	unsigned
	_Bool
	_Complex
	atomic-type-specifier
	struct-or-union-specifier
	enum-specifier
	typedef-name
	*/
	TSingleTypeSpecifier*  pSingleTypeSpecifier = NULL;

	if (*ppTypeSpecifier != NULL)
	{
		if ((*ppTypeSpecifier)->type == TSingleTypeSpecifier_ID)
		{
			pSingleTypeSpecifier = (TSingleTypeSpecifier*)(*ppTypeSpecifier);
		}

		else
		{
      //ver caso a caso
      /*
      //exemplo
      typedef struct X X;
      typedef struct X {  int i; } X;
      */
			//long long long int
		}
	}

	bool bResult = false;
	const char* lexeme = Lexeme(ctx);
	Tokens token = Token(ctx);

	switch (token)
	{
		//type - specifier
		case TK_void:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsVoid = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_char:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsChar = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_short:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsShort = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_int:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsInt = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_long:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->nLong++;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_float:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsFloat = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_double:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsDouble = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_signed:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsSigned = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK_unsigned:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsUnsigned = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK__Bool:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsBool = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		case TK__Complex:
		{
			if (pSingleTypeSpecifier == NULL)
			{
				pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
			}

			pSingleTypeSpecifier->bIsComplex = true;
			bResult = true;
			Match(ctx);
			*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
		}
		break;

		//atomic-type-specifier
		case TK_struct:
		case TK_union:
		{
			ASSERT(*ppTypeSpecifier == NULL);
			bResult = true;
			TStructUnionSpecifier* pStructUnionSpecifier = TStructUnionSpecifier_Create();
			*ppTypeSpecifier = (TTypeSpecifier*)pStructUnionSpecifier;
			Struct_Or_Union_Specifier(ctx, pStructUnionSpecifier);
		}
		break;

		case TK_enum:
		{
			ASSERT(*ppTypeSpecifier == NULL);
			bResult = true;
			TEnumSpecifier* pEnumSpecifier2 = TEnumSpecifier_Create();
			*ppTypeSpecifier = (TTypeSpecifier*)pEnumSpecifier2;
			Enum_Specifier(ctx, pEnumSpecifier2);
		}
		break;

		case TK_identifier:
		{
			bool bIsTypedef = DeclarationsMap_IsTypeDef(&ctx->Symbols, lexeme);

			if (bIsTypedef)
			{
        if (*typedefCount == 0 /*&&
            ppTypeSpecifier == NULL*/)
        {

          if (*ppTypeSpecifier == NULL)
          {
            *typedefCount = 1;

            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
            pSingleTypeSpecifier->bIsTypeDef = true;
            String_Set(&pSingleTypeSpecifier->TypedefName, lexeme);
            bResult = true;
            Match(ctx);
            *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
          }
          else
          {
            bResult = false;
            //ERROR
            //typedef int INT;
            //typedef  double INT;
            

            //OK
            //typedef int INT;
            //typedef  int INT;

            //if ((*ppTypeSpecifier)->type)
            //daria este problema se wchar_t ja tivesse sido definido
            //typedef unsigned short wchar_t;

            //typedef int INT;
          // SetError(ctx, "??");
            //*typedefCount = 1;

            //pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
            //pSingleTypeSpecifier->bIsTypeDef = true;
            //String_Set(&pSingleTypeSpecifier->TypedefName, lexeme);
            //bResult = true;
            //Match(ctx);
            //*ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
          }
        }
        else
        {
          bResult = false;
        }
			}

			else
			{
				bResult = false;
			}
		}
		break;

		default:
			break;
	}

	//ASSERT((bResult && *ppTypeSpecifier != NULL) ||
	//  (!bResult && *ppTypeSpecifier == NULL));
	return bResult;
}

bool Declaration_Specifiers(Parser* ctx,
	TDeclarationSpecifiers* pDeclarationSpecifiers)
{
	/*
	declaration-specifiers:
	storage-class-specifier declaration-specifiersopt
	type-specifier          declaration-specifiersopt
	type-qualifier          declaration-specifiersopt
	function-specifier      declaration-specifiersopt
	alignment-specifier     declaration-specifiersopt
	*/
	bool bResult = false;
	int typedefCount = 0;
	/*
	typedef unsigned A;
	typedef int  B;
    A B;	
	*/
	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		if (Type_Specifier(ctx, &pDeclarationSpecifiers->pTypeSpecifierOpt, &typedefCount) ||
			Storage_Class_Specifier(ctx, &pDeclarationSpecifiers->StorageSpecifiers) ||
			Type_Qualifier(ctx, &pDeclarationSpecifiers->TypeQualifiers) ||
			Function_Specifier(ctx, &pDeclarationSpecifiers->FunctionSpecifiers) ||
			Alignment_Specifier(ctx, &pDeclarationSpecifiers->AlignmentSpecifier))
		{
			bResult = true; //retorna true se achou algo
			continue;
		}

		else
		{
			break;
		}
	}

	return bResult;
}



void Initializer(Parser* ctx,
	TInitializer** ppInitializer,
	Tokens endToken1,
	Tokens endToken2)
{
	ASSERT(*ppInitializer == NULL);
	/*
	initializer:
	assignment-expression
	{ initializer-list }
	{ initializer-list , }
	*/
	Tokens token = Token(ctx);

	if (token == TK_LEFT_CURLY_BRACKET)
	{
		TInitializerListType* pTInitializerList = TInitializerListType_Create();
		*ppInitializer = (TInitializer*)pTInitializerList;
		Match(ctx);
		Initializer_List(ctx, &pTInitializerList->InitializerList);
		MatchToken(ctx, TK_RIGHT_CURLY_BRACKET);
	}

	else
	{
		TExpression2* pExpression = NULL;
		AssignmentExpression(ctx, &pExpression);
		*ppInitializer = (TInitializer*)pExpression;
	}
}

void Initializer_List(Parser* ctx, TInitializerList* pInitializerList)
{
	/*
	initializer-list:
	designationopt initializer
	initializer-list , designationopt initializer
	*/
	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		TInitializerListItem* pTInitializerListItem = TInitializerListItem_Create();
		TInitializerList_Push(pInitializerList, pTInitializerListItem);
		Tokens token = Token(ctx);

		if (token == TK_LEFT_SQUARE_BRACKET ||
			token == TK_FULL_STOP)
		{
			pTInitializerListItem->pDesignatorList = TDesignatorList_Create();
			Designation(ctx, pTInitializerListItem->pDesignatorList);
		}

		Initializer(ctx, &pTInitializerListItem->pInitializer, TK_COMMA, TK_RIGHT_CURLY_BRACKET);
		//push
		token = Token(ctx);

		if (token == TK_COMMA)
		{
			Match(ctx);
			//tem mais
		}

		else
		{
			break;
		}
	}
}

void Designation(Parser* ctx, TDesignatorList* pDesignatorList)
{
	/*
	designation:
	designator-list =
	*/
	Designator_List(ctx, pDesignatorList);
	MatchToken(ctx, TK_EQUALS_SIGN);
}

void Designator_List(Parser* ctx, TDesignatorList* pDesignatorList)
{
	// http://www.drdobbs.com/the-new-c-declarations-initializations/184401377
	/*
	designator-list:
	designator
	designator-list designator
	*/
	TDesignator* pDesignator = TDesignator_Create();
	Designator(ctx, pDesignator);
	TDesignatorList_Push(pDesignatorList, pDesignator);

	for (; ;)
	{
		if (ErrorOrEof(ctx))
			break;

		Tokens token = Token(ctx);

		if (token == TK_LEFT_SQUARE_BRACKET ||
			token == TK_FULL_STOP)
		{
			TDesignator* pDesignatorNew = TDesignator_Create();
			Designator(ctx, pDesignatorNew);
			TDesignatorList_Push(pDesignatorList, pDesignatorNew);
		}

		else
		{
			break;
		}
	}
}

void Designator(Parser* ctx, TDesignator* p)
{
	/*
	designator:
	[ constant-expression ]
	. identifier
	*/
	Tokens token = Token(ctx);

	if (token == TK_LEFT_SQUARE_BRACKET)
	{
		Match(ctx);
		ConstantExpression(ctx, &p->pExpression);
		MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET);
	}

	else if (token == TK_FULL_STOP)
	{
		Match(ctx);
		String_Set(&p->Name, Lexeme(ctx));
		MatchToken(ctx, TK_identifier);
	}
}

void Init_Declarator(Parser* ctx,
	TDeclarator* pDeclarator2)
{
	/*
	init-declarator:
	declarator
	declarator = initializer
	*/
	Declarator(ctx, pDeclarator2);
	Tokens token = Token(ctx);

	if (token == TK_EQUALS_SIGN)
	{
		Match(ctx);
		Initializer(ctx, &pDeclarator2->pInitializer, TK_SEMICOLON, TK_SEMICOLON);
	}
}

void Init_Declarator_List(Parser* ctx,

	TDeclaratorList* pDeclaratorList2)
{
	/*
	init-declarator-list:
	init-declarator
	init-declarator-list , init-declarator
	*/
	TDeclarator* pDeclarator2 = TDeclarator_Create();
	TDeclaratorList_Push(pDeclaratorList2, pDeclarator2);
	Init_Declarator(ctx, pDeclarator2);

	//Tem mais?
	Tokens token = Token(ctx);
	if (token == TK_COMMA)
	{
		Match(ctx);
		Init_Declarator_List(ctx, pDeclaratorList2);
	}

}

bool  Declaration(Parser* ctx,
	TAnyDeclaration** ppDeclaration)
{
	/*
	declaration:
	declaration-specifiers init-declarator-listopt ;
	static_assert-declaration
	*/

	bool bHasDeclaration = false;
	Tokens token = Token(ctx);

	if (token == TK__Static_assert)
	{
		TStaticAssertDeclaration* pStaticAssertDeclaration = TStaticAssertDeclaration_Create();
		*ppDeclaration = (TAnyDeclaration*)pStaticAssertDeclaration;
		Static_Assert_Declaration(ctx, pStaticAssertDeclaration);
		bHasDeclaration = true;
	}

	else
	{
		TDeclaration* pFuncVarDeclaration = TDeclaration_Create();

		if (token == TK_SEMICOLON)
		{
			//declaracao vazia como ;
			bHasDeclaration = true;
			//Match(ctx);
		}

		else
		{
			bHasDeclaration =
				Declaration_Specifiers(ctx, &pFuncVarDeclaration->Specifiers);
		}

		*ppDeclaration = (TAnyDeclaration*)pFuncVarDeclaration;
		pFuncVarDeclaration->FileIndex = GetFileIndex(ctx);
		pFuncVarDeclaration->Line = GetCurrentLine(ctx);
		ASSERT(pFuncVarDeclaration->FileIndex >= 0);

		if (bHasDeclaration)
		{
			token = Token(ctx);

			if (token == TK_SEMICOLON)
			{
				Match(ctx);
			}

			else
			{
				//Agora vem os declaradores que possuem os ponteiros
				Init_Declarator_List(ctx, &pFuncVarDeclaration->Declarators);
				token = Token(ctx);

				if (token == TK_LEFT_CURLY_BRACKET)
				{
					TStatement* pStatement;
					Compound_Statement(ctx, &pStatement);
					//TODO cast
					pFuncVarDeclaration->pCompoundStatementOpt = (TCompoundStatement*)pStatement;
				}

				else
				{
					MatchToken(ctx, TK_SEMICOLON);
				}
			}
		}
	}

	return bHasDeclaration;
}

void SetSymbolsFromDeclaration(Parser* ctx,

	TAnyDeclaration* pDeclaration2)
{
	//Extrai as declaracoes de tipos variaveis e funcoes da declaracao
	if (pDeclaration2->type == TDeclaration_ID)
	{
		TDeclaration* pTFuncVarDeclaration = (TDeclaration*)pDeclaration2;
		//if (pTFuncVarDeclaration->Specifiers.StorageSpecifiers.bIsTypedef)
		{

			for (size_t i = 0; i < pTFuncVarDeclaration->Declarators.size; i++)
			{
				TDeclarator* pDeclarator = pTFuncVarDeclaration->Declarators.pItems[i];
				const char* declaratorName = TDeclarator_FindName(pDeclarator);

				if (declaratorName == NULL)
				{
					//declaracao vazia ;
					//SetError(ctx, "empty declarator");
					//ASSERT(false);
				}
				else
				{
					Parser_SetSymbol(ctx, declaratorName, pDeclaration2);
				}
			}
		}
	}
}

void Parse_Declarations(Parser* ctx, TDeclarations* declarations)
{
	int declarationIndex = 0;

	while (!ErrorOrEof(ctx))
	{
		TAnyDeclaration* pDeclarationOut = NULL;
		bool bHasDecl = Declaration(ctx, &pDeclarationOut);
		if (bHasDecl)
		{
			TDeclarations_Push(declarations, pDeclarationOut);
			declarationIndex++;
			SetSymbolsFromDeclaration(ctx, pDeclarationOut);		
		}
		else
		{
      if (Token(ctx) == TK_EOF)
      {
        //ok
      }
      else
      {
        //nao ter mais declaracao nao eh erro
        SetError(ctx, "declaration expected");
      }      
			break;
		}

		if (HasErrors(ctx))
			break;

	}
}

void Parser_Main(Parser* ctx, TDeclarations* declarations)
{
	Parse_Declarations(ctx, declarations);
}

static void TFileMapToStrArray(TFileMap* map, TFileArray* arr)
{
	TFileArray_Reserve(arr, map->Size);
	arr->size = map->Size;

	for (size_t i = 0; i < map->buckets.size; i++)
	{
		Bucket*  data = map->buckets.data[i];

		if (data != NULL)
		{
			for (size_t k = 0; k < data->size; k++)
			{
				BucketItem* node = data->data[k];
				TFile* pFile = (TFile*)node->data;

				if (pFile->FileIndex >= 0 &&
					pFile->FileIndex < (int)arr->size)
				{
					arr->pItems[pFile->FileIndex] = pFile;
					node->data = NULL; //movido para array
				}
			}
		}
	}
}

bool GetAST(const char*  filename,
	const char* configFileName,
	TProgram* pProgram)
{
	bool bResult = false;
	String fullFileNamePath = STRING_INIT;
	GetFullPath(filename, &fullFileNamePath);
	String fullConfigFilePath = STRING_INIT;
	GetFullPath(configFileName, &fullConfigFilePath);

	Parser parser;
	Parser_InitFile(&parser, fullConfigFilePath);
	Parser_Main(&parser, &pProgram->Declarations);

	//parser.scanner.bPrintIncludes = true;
	if (filename != NULL)
	{
		Parser_PushFile(&parser, fullFileNamePath);
		Parser_Main(&parser, &pProgram->Declarations);
	}

	TFileMapToStrArray(&parser.Scanner.FilesIncluded, &pProgram->Files2);
	printf("%s\n", GetCompletationMessage(&parser));
	MultiMap_Swap(&parser.Symbols, &pProgram->Symbols);

	MacroMap2_Swap(&parser.Scanner.Defines2, &pProgram->Defines);
	Map_Swap(&parser.EnumMap, &pProgram->EnumMap);

	bResult = !parser.bError;

	Parser_Destroy(&parser);
	String_Destroy(&fullFileNamePath);
	String_Destroy(&fullConfigFilePath);
	return bResult;
}




#if 0


void PrintString(const char* psz)
{
	printf("\"");

	while (*psz)
	{
		switch (*psz)
		{
			case '"':
				printf("\\\"");
				break;

			case '/':
				printf("\\/");
				break;

			case '\b':
				printf("\\b");
				break;

			case '\f':
				printf("\\f");
				break;

			case '\n':
				printf("\\n");
				break;

			case L'\r':
				printf("\\r");
				break;

			case L'\t':
				printf("\\t");
				break;

			case L'\\':
				printf("\\\\");
				break;

			default:
				printf("%c", *psz);
				break;
		}

		psz++;
	}

	printf("\"");
}

void PrintTokens(Scanner* scanner)
{
	while (Scanner_Token(scanner) != TK_EOF)
	{
		printf("%s : ", Scanner_TokenString(scanner));
		PrintString(Scanner_Lexeme(scanner));
		printf("\n");
		Scanner_Next(scanner);
	}
}

void PrintTokensOfFile(const char* fileName)
{
	Scanner scanner;
	Scanner_Init(&scanner);
	Scanner_IncludeFile(&scanner, fileName, FileIncludeTypeFullPath);
	PrintTokens(&scanner);
	Scanner_Destroy(&scanner);
}


void PrintPreprocessedToConsole(const char* fileIn)
{
	Scanner scanner;
	Scanner_Init(&scanner);
	Scanner_IncludeFile(&scanner, fileIn, FileIncludeTypeFullPath);
	scanner.bIncludeSpaces = true;

	while (Scanner_Token(&scanner) != TK_EOF)
	{
		Tokens token = Scanner_Top(&scanner)->currentItem.token;
		const char* lexeme = Scanner_Top(&scanner)->currentItem.lexeme.c_str;

		if (token == TK_BREAKLINE)
		{
			printf("%s", lexeme);
		}

		if (token == TK_LINE_COMMENT ||
			token == TK_COMMENT)
		{
			//fprintf(fp, "%s", lexeme);
		}
		else
		{
			printf("%s", lexeme);
		}

		Scanner_Next(&scanner);
	}

	Scanner_Destroy(&scanner);
}


void GetUnprocessedTokens(const char* fileIn/*, JObj* pOutArray*/)
{
	BasicScanner scanner;
	BasicScanner_InitFile(&scanner, fileIn);

	while (scanner.currentItem.token != TK_EOF)
	{
		Tokens token = scanner.currentItem.token;
		const char* lexeme = scanner.currentItem.lexeme.c_str;
		//JObj *pNew = JObj_PushNewArray(pOutArray);
		//JObj_PushString(pNew, TokenToString(token));
		//JObj_PushString(pNew, lexeme);
		BasicScanner_Next(&scanner);
	}

	BasicScanner_Destroy(&scanner);
}

void GetProcessedTokens2(const char* fileIn/*, JObj* pOutArray*/)
{
	Scanner scanner;
	Scanner_Init(&scanner);
	Scanner_IncludeFile(&scanner, fileIn, FileIncludeTypeFullPath);

	while (Scanner_Token(&scanner) != TK_EOF)
	{
		Tokens token = Scanner_Token(&scanner);
		const char* lexeme = Scanner_Lexeme(&scanner);
		//JObj *pNew = JObj_PushNewArray(pOutArray);
		//JObj_PushString(pNew, TokenToString(token));
		//JObj_PushString(pNew, lexeme);
		Scanner_Next(&scanner);
	}

	Scanner_Destroy(&scanner);
}

void GetProcessedTokens(const char* fileIn/*, JObj* pOutArray*/)
{
	Scanner scanner;
	Scanner_Init(&scanner);
	scanner.bIncludeSpaces = true;
	Scanner_IncludeFile(&scanner, fileIn, FileIncludeTypeFullPath);

	while (Scanner_Token(&scanner) != TK_EOF)
	{
		Tokens token = Scanner_Top(&scanner)->currentItem.token;
		const char* lexeme = Scanner_Top(&scanner)->currentItem.lexeme.c_str;
		//JObj *pNew = JObj_PushNewObject(pOutArray);
		//JObj_SetString(pNew, "token", TokenToString(token));
		//JObj_SetString(pNew, "lexeme", lexeme);
		Scanner_Next(&scanner);
	}

	Scanner_Destroy(&scanner);
}



#endif


