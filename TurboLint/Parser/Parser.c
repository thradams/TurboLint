#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "Scanner.h"
#include "..\Base\Path.h"
//Define to include modications
#define LANGUAGE_EXTENSIONS 
Tokens Parser_Match(Parser* parser, TScannerItemList* listOpt);
Tokens Parser_MatchToken(Parser* parser,
    Tokens tk,
    TScannerItemList* listOpt);

static bool IsPreprocessorTokenPhase(Tokens token)
{
    return
        token == TK_SPACES ||
        token == TK_COMMENT ||
        token == TK_LINE_COMMENT ||
        token == TK_BREAKLINE ||
        //Tokens para linhas do pre processador
        token == TK_PRE_INCLUDE ||
        token == TK_PRE_PRAGMA ||
        token == TK_PRE_IF ||
        token == TK_PRE_ELIF ||
        token == TK_PRE_IFNDEF ||
        token == TK_PRE_IFDEF ||
        token == TK_PRE_ENDIF ||
        token == TK_PRE_ELSE ||
        token == TK_PRE_ERROR ||
        token == TK_PRE_LINE ||
        token == TK_PRE_UNDEF ||
        token == TK_PRE_DEFINE ||
        //fim tokens preprocessador
        token == TK_MACRO_CALL ||
        token == TK_MACRO_EOF ||
        token == TK_FILE_EOF;
}

bool IsSuffix(const char* s, const char* suffix)
{
    bool bResult = false;
    int len = strlen(s);
    int len2 = strlen(suffix);
    if (len > len2)
    {
        const char* pEndPart = &s[len - len2];
        if (strcmp(pEndPart, suffix) == 0)
        {
            bResult = true;
        }
    }
    return bResult;
}
////////////////////////////////////////
bool IsTemplateFunction(const char* lexeme)
{
    return false;
    //_Create
    //_Delete
    /*
    bool bResult = false;
    if (IsSuffix(lexeme, "_Create"))
    {
      bResult = true;
    }
    else if (IsSuffix(lexeme, "Array_Push"))
    {
      bResult = true;
    }
    else if (IsSuffix(lexeme, "Array_Reserve"))
    {
      bResult = true;
    }
    return bResult;
    */
}

bool IsTemplateType(const char* lexeme)
{
    return false;
    /*bool bResult = false;
    if (IsSuffix(lexeme, "Array"))
    {
      bResult = true;
    }
    else if (strcmp(lexeme, "string") == 0)
    {
      bResult = true;
    }
    return bResult;*/
}

bool InstantiateTemplateType(const char *lexeme, StrBuilder* strBuilder)
{
    StrBuilder_Clear(strBuilder);

    bool bResult = false;
    if (IsSuffix(lexeme, "Array"))
    {
        StrBuilder tname = STRBUILDER_INIT;
        StrBuilder_SetN(&tname, lexeme, strlen(lexeme) - 5);

        StrBuilder_Append(strBuilder,
            "typedef struct ");

        StrBuilder_Append(strBuilder, tname.c_str);
        StrBuilder_Append(strBuilder, "Array {");
        StrBuilder_Append(strBuilder, tname.c_str);
        StrBuilder_Append(strBuilder, "** pItems; int Size; int Capacity; } ");
        StrBuilder_Append(strBuilder, tname.c_str);
        StrBuilder_Append(strBuilder, "Array;");

        bResult = true;
        StrBuilder_Destroy(&tname);
    }
    else if (strcmp(lexeme, "string") == 0)
    {
        StrBuilder_Append(strBuilder, "typedef char* string;");
        bResult = true;
    }

    return  bResult;
}

bool InstantiateTemplateFunction(const char *lexeme,
    StrBuilder* strBuilder,
    StrBuilder* strBuilder2)
{
    StrBuilder_Clear(strBuilder);

    bool bResult = false;
    if (IsSuffix(lexeme, "_Create"))
    {
        StrBuilder tname = STRBUILDER_INIT;
        StrBuilder_SetN(&tname, lexeme, strlen(lexeme) - 7);

        StrBuilder_Append(strBuilder, "static ");
        StrBuilder_Append(strBuilder, tname.c_str);
        StrBuilder_Append(strBuilder, "* ");
        StrBuilder_Append(strBuilder, lexeme);
        StrBuilder_Append(strBuilder, "();");


        StrBuilder_Append(strBuilder2, "static ");
        StrBuilder_Append(strBuilder2, tname.c_str);
        StrBuilder_Append(strBuilder2, "* ");
        StrBuilder_Append(strBuilder2, lexeme);
        StrBuilder_Append(strBuilder2, "()");
        StrBuilder_Append(strBuilder2, "{");
        StrBuilder_Append(strBuilder2, tname.c_str);
        StrBuilder_Append(strBuilder2, "* p = malloc(sizeof *p);");
        StrBuilder_Append(strBuilder2, "if (p) {");

        StrBuilder_Append(strBuilder2, tname.c_str);
        StrBuilder_Append(strBuilder2, " temp = {};");
        StrBuilder_Append(strBuilder2, " *p = temp;");

        StrBuilder_Append(strBuilder2, "}");
        StrBuilder_Append(strBuilder2, "return p;");
        StrBuilder_Append(strBuilder2, "}");

        StrBuilder_Destroy(&tname);

        bResult = true;
    }
    else if (IsSuffix(lexeme, "Array_Push"))
    {
        StrBuilder tname = STRBUILDER_INIT;
        StrBuilder_SetN(&tname, lexeme, strlen(lexeme) - 10);

        bResult = true;

        StrBuilder_Append(strBuilder,
            "static void ");
        StrBuilder_Append(strBuilder,
            tname.c_str);
        StrBuilder_Append(strBuilder,
            "Array_Push(");
        StrBuilder_Append(strBuilder,
            tname.c_str);
        StrBuilder_Append(strBuilder,
            "Array* pArray, ");
        StrBuilder_Append(strBuilder,
            tname.c_str);
        StrBuilder_Append(strBuilder,
            "* pItem)");

        StrBuilder_Append(strBuilder2,
            strBuilder->c_str);

        StrBuilder_Append(strBuilder,
            ";");

        StrBuilder_Append(strBuilder2, "{");

        StrBuilder_Append(strBuilder2,
            tname.c_str);
        StrBuilder_Append(strBuilder2, "Array_Reserve(pArray, pArray->Size + 1);");

        StrBuilder_Append(strBuilder2, "}");

        StrBuilder_Destroy(&tname);
    }
    else if (IsSuffix(lexeme, "Array_Reserve"))
    {
        StrBuilder tname = STRBUILDER_INIT;
        StrBuilder_SetN(&tname, lexeme, strlen(lexeme) - 13);

        bResult = true;

        StrBuilder_Append(strBuilder,
            "static void ");
        StrBuilder_Append(strBuilder,
            tname.c_str);
        StrBuilder_Append(strBuilder,
            "Array_Reserve(");
        StrBuilder_Append(strBuilder,
            tname.c_str);
        StrBuilder_Append(strBuilder,
            "Array* pArray, ");
        StrBuilder_Append(strBuilder,
            tname.c_str);
        StrBuilder_Append(strBuilder,
            "* pItem)");

        StrBuilder_Append(strBuilder2,
            strBuilder->c_str);

        StrBuilder_Append(strBuilder,
            ";");

        StrBuilder_Append(strBuilder2, "{");

        StrBuilder_Append(strBuilder2, "}");

        StrBuilder_Destroy(&tname);
    }
    return  bResult;
}
//////////////////////////////////////////////

bool Declaration(Parser* ctx, TAnyDeclaration** ppDeclaration);
void SetSymbolsFromDeclaration(Parser* ctx,
    TAnyDeclaration* pDeclaration2);

bool IsTypeName(Parser* ctx, Tokens token, const char * lexeme);


TDeclaration * FindDeclarationOfDeclarator(DeclarationsMap* map, const char* name)
{
    TDeclaration *pDeclaration = NULL;
    int bResult = 0;
    Bucket*  p = MultiMap_FindBucket(map, name);

    if (p != NULL)
    {
        for (size_t i = 0; i < p->size; i++)
        {
            if (strcmp(name, p->data[i]->key) == 0)
            {
                pDeclaration =
                    TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)p->data[i]->data);

                break;
            }
        }
    }
    return pDeclaration;
}

int DeclarationsMap_IsTypeDef(DeclarationsMap* map, const char* name)
{
    int bResult = 0;
    Bucket*  p = MultiMap_FindBucket(map, name);

    if (p != NULL)
    {
        for (size_t i = 0; i < p->size; i++)
        {
            if (strcmp(name, p->data[i]->key) == 0)
            {
                TAnyDeclaration *pDeclaration = (TAnyDeclaration *)p->data[i]->data;
                bResult = TAnyDeclaration_IsTypedef(pDeclaration) ? 1 : 0;

                if (bResult)
                    break;
            }
        }
    }

    if (bResult == 0)
    {
        if (IsTemplateType(name))
        {
            //eh um tipo mas ainda nao foi instanciado
            bResult = 2;
        }
    }
    return bResult;
}

Result Parser_InitString(Parser* parser,
    const char* name,
    const char* text)
{
    List_Init(&parser->ClueList);
    MultiMap_Init(&parser->Symbols, SYMBOL_BUCKETS_SIZE);
    Map_Init(&parser->EnumMap, SYMBOL_BUCKETS_SIZE);

    //Map_Init(&parser->TypeDefNames, SYMBOL_BUCKETS_SIZE);
    parser->bError = false;

    StrBuilder_Init(&parser->ErrorMessage, 100);


    /////////
    Scanner_InitString(&parser->Scanner, name, text);
    ArrayT_Init(&parser->Templates);
    ArrayT_Init(&parser->TemplatesInstances);

    //sair do BOF
    Parser_Match(parser, NULL);

    return RESULT_OK;
}

Result Parser_InitFile(Parser* parser, const char* fileName)
{
    List_Init(&parser->ClueList);
    DeclarationsMap_Init(&parser->Symbols, SYMBOL_BUCKETS_SIZE);
    Map_Init(&parser->EnumMap, SYMBOL_BUCKETS_SIZE);

    //Map_Init(&parser->TypeDefNames, SYMBOL_BUCKETS_SIZE);
    parser->bError = false;


    StrBuilder_Init(&parser->ErrorMessage, 100);
    Scanner_Init(&parser->Scanner);
    ArrayT_Init(&parser->Templates);
    ArrayT_Init(&parser->TemplatesInstances);


    ////////
    Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath, false);

    //Scanner_Match(&parser->Scanner);
    //sair do BOF
    Parser_Match(parser, NULL);

    return RESULT_OK;
}

void Parser_PushFile(Parser* parser, const char* fileName)
{
    Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath, false);
    Parser_Match(parser, NULL);
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
    List_Destroy(ScannerItem, &parser->ClueList);
    DeclarationsMap_Destroy(&parser->Symbols);
    Map_Destroy(&parser->EnumMap, NULL); //OWNER IS AST

    //Map_Destroy(&parser->TypeDefNames, NULL);
    StrBuilder_Destroy(&parser->ErrorMessage);
    Scanner_Destroy(&parser->Scanner);
    ArrayT_Destroy(TAnyDeclaration, &parser->Templates);
    ArrayT_Destroy(TAnyDeclaration, &parser->TemplatesInstances);
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

bool Parser_HasError(Parser* pParser)
{
    return pParser->bError || pParser->Scanner.bError;
}



void SetError2(Parser* parser, const char* message, const char* message2)
{
    //    ASSERT(false);
    if (!Parser_HasError(parser))
    {
        Scanner_GetError(&parser->Scanner, &parser->ErrorMessage);
        parser->bError = true;
        StrBuilder_Append(&parser->ErrorMessage, "(");
        StrBuilder_AppendInt(&parser->ErrorMessage, Scanner_CurrentLine(&parser->Scanner));
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

void SetUnexpectedError(Parser* parser, const char* message, const char* message2)
{
    SetError2(parser, message, message2);
}

//void SetError(Parser* parser, const char* message)
//{
  //SetError2(parser, message, "");
//}




int GetCurrentLine(Parser* parser)
{
    if (Parser_HasError(parser))
    {
        return -1;
    }

    return Scanner_CurrentLine(&parser->Scanner);
}

int GetFileIndex(Parser* parser)
{
    if (Parser_HasError(parser))
    {
        return -1;
    }

    return Scanner_CurrentFileIndex(&parser->Scanner);
}

static void GetPosition(Parser* ctx, TPosition* pPosition)
{
    pPosition->Line = GetCurrentLine(ctx);
    pPosition->FileIndex = GetFileIndex(ctx);
    //ASSERT(pPosition->FileIndex >= 0);
}

Tokens Parser_LookAheadToken(Parser* parser)
{
    Tokens token = TK_ERROR;

    if (!Parser_HasError(parser))
    {
        for (int i = 1; i < 10; i++)
        {
            token = Scanner_LookAheadToken(&parser->Scanner, i);
            bool bActive = Scanner_LookAheadTokenActive(&parser->Scanner, i);
            if (bActive && !IsPreprocessorTokenPhase(token))
            {
                break;
            }
        }
    }

    return token;
}


const char* Parser_LookAheadLexeme(Parser* parser)
{
    if (Parser_HasError(parser))
    {
        return "";
    }

    return Scanner_LookAheadLexeme(&parser->Scanner, 1);
}


Tokens Parser_CurrentToken(Parser* parser)
{
    if (Parser_HasError(parser))
    {
        return TK_ERROR;
    }

    Tokens token = Scanner_CurrentToken(&parser->Scanner);

    if (IsPreprocessorTokenPhase(token))
    {
        SetUnexpectedError(parser, "!IsPreprocessorTokenPhase", "");
    }
    return token;
}


Tokens Parser_Match(Parser* parser, TScannerItemList* listOpt)
{
    Tokens token = TK_EOF;
    if (!Parser_HasError(parser))
    {

        if (listOpt)
        {
            List_Swap(ScannerItem, listOpt, &parser->ClueList);
        }

        Scanner_Match(&parser->Scanner);

        token = Scanner_CurrentToken(&parser->Scanner);
        while (token != TK_EOF &&
               (!Scanner_CurrentTokenIsActive(&parser->Scanner) ||
               IsPreprocessorTokenPhase(token)))
        {
            ScannerItem* pNew = ScannerItem_Create();
            StrBuilder_Set(&pNew->lexeme, Scanner_CurrentLexeme(&parser->Scanner));
            pNew->token = Scanner_CurrentToken(&parser->Scanner);
            List_Add(&parser->ClueList, pNew);

            Scanner_Match(&parser->Scanner);
            token = Scanner_CurrentToken(&parser->Scanner);
        }
    }

    return token;
}

Tokens Parser_MatchToken(Parser* parser,
    Tokens tk,
    TScannerItemList* listOpt)
{
    if (Parser_HasError(parser))
    {
        return TK_EOF;
    }

    Tokens currentToken = Parser_CurrentToken(parser);

    if (tk != currentToken)
    {
        SetError2(parser, "Unexpected token - ", TokenToString(tk));
        return TK_EOF;
    }

    Parser_Match(parser, listOpt);
    return Parser_CurrentToken(parser);
}

const char* GetCompletationMessage(Parser* parser)
{
    const char* pMessage = "ok";

    if (Parser_HasError(parser))
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
    if (Parser_HasError(parser))
    {
        ASSERT(false);
        return "";
    }

    return Scanner_CurrentLexeme(&parser->Scanner);
}

bool ErrorOrEof(Parser* parser)
{
    return Parser_HasError(parser) ||
        Parser_CurrentToken(parser) == TK_EOF;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


void Expression0(Parser* ctx, TExpression**);
void CastExpression(Parser* ctx, TExpression**);
void GenericSelection(Parser* ctx);
void ArgumentExpressionList(Parser* ctx, TExpression**);
void AssignmentExpression(Parser* ctx, TExpression**);
void Initializer_List(Parser* ctx, TInitializerList* pInitializerList);
void Specifier_Qualifier_List(Parser* ctx,
    TTypeQualifier* pQualifiers,
    TTypeSpecifier** ppTypeSpecifier);
bool AbstractDeclaratorOpt(Parser* ctx, TDeclarator** pTDeclarator2);



bool IsFirstOfPrimaryExpression(Tokens token)
{
    bool bResult = false;

    switch (token)
    {
    case TK_IDENTIFIER:
    case TK_STRING_LITERAL:
    case TK_CHAR_LITERAL:
    case TK_DECIMAL_INTEGER:
    case TK_HEX_INTEGER:
    case TK_FLOAT_NUMBER:
    case TK_LEFT_PARENTHESIS:

        //desde que nao seja cast
    case TK__GENERIC:
        bResult = true;
        break;

    default:
        break;
    }

    return bResult;
}

void PrimaryExpression(Parser* ctx, TExpression** ppPrimaryExpression)
{
    /*
    (6.5.1) primary-expression:
    identifier
    constant
    string-literal
    ( expression )
    generic-selection
    */
    *ppPrimaryExpression = NULL; //out

    Tokens token = Parser_CurrentToken(ctx);

    //PreprocessorTokenIndex(ctx);
    //-2 nem eh macro
    //-1 inicio de macro
    //-3 fim de macro


    if (!IsFirstOfPrimaryExpression(token))
    {
        SetUnexpectedError(ctx, "1", "IsFirstOfPrimaryExpression");
    }

    switch (token)
    {
    case TK_STRING_LITERAL:
    {
        TPrimaryExpressionValue *  pPrimaryExpressionValue
            = TPrimaryExpressionValue_Create();

        pPrimaryExpressionValue->token = token;

        StrBuilder adjacentStrings = STRBUILDER_INIT;
        StrBuilder_Append(&adjacentStrings, "\"");
        while (token == TK_STRING_LITERAL)
        {
            const char* lexeme = Lexeme(ctx);
            int len = strlen(lexeme);
            StrBuilder_AppendN(&adjacentStrings, lexeme + 1, len - 2);

            token = Parser_Match(ctx,
                &pPrimaryExpressionValue->ClueList0);
        }
        StrBuilder_Append(&adjacentStrings, "\"");
        String_Set(&pPrimaryExpressionValue->lexeme, adjacentStrings.c_str);
        *ppPrimaryExpression = (TExpression*)pPrimaryExpressionValue;

        StrBuilder_Destroy(&adjacentStrings);
    }
    break;

    case TK_IDENTIFIER:
    case TK_CHAR_LITERAL:
    case TK_DECIMAL_INTEGER:
    case TK_HEX_INTEGER:
    case TK_FLOAT_NUMBER:
    {
        TPrimaryExpressionValue *   pPrimaryExpressionValue
            = TPrimaryExpressionValue_Create();

        pPrimaryExpressionValue->token = token;
        String_Set(&pPrimaryExpressionValue->lexeme, Lexeme(ctx));


        Parser_Match(ctx,
            &pPrimaryExpressionValue->ClueList0);
        *ppPrimaryExpression = (TExpression*)pPrimaryExpressionValue;
    }
    break;

    case TK_LEFT_PARENTHESIS:
    {
        TPrimaryExpressionValue *   pPrimaryExpressionValue
            = TPrimaryExpressionValue_Create();

        Parser_Match(ctx,
            &pPrimaryExpressionValue->ClueList0);

        TExpression* pExpression;
        Expression0(ctx, &pExpression);

        //    //TNodeClueList_MoveToEnd(&pPrimaryExpressionValue->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx,
            TK_RIGHT_PARENTHESIS,
            &pPrimaryExpressionValue->ClueList1);


        pPrimaryExpressionValue->token = token;
        String_Set(&pPrimaryExpressionValue->lexeme, Lexeme(ctx));
        pPrimaryExpressionValue->pExpressionOpt = pExpression;


        *ppPrimaryExpression = (TExpression*)pPrimaryExpressionValue;
    }
    break;

    case TK__GENERIC:
        GenericSelection(ctx);
        break;

    default:
        SetUnexpectedError(ctx, "", "");
    }

    if (*ppPrimaryExpression == NULL)
    {
        SetUnexpectedError(ctx, "*ppPrimaryExpression != NULL", "");
    }

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
    TDeclarator* pDeclarator = NULL;
    AbstractDeclaratorOpt(ctx, &pDeclarator);
    if (pDeclarator)
    {
        pTypeName->Declarator = *pDeclarator;
    }
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

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
        //aqui eu posso marcar a funcao como usada.

        pPostfixExpressionCore->token = token;


        //  postfix-expression ( argument-expression-listopt )    
        token = Parser_Match(ctx,
            &pPostfixExpressionCore->ClueList);

        if (token != TK_RIGHT_PARENTHESIS)
        {
            ArgumentExpressionList(ctx, &pPostfixExpressionCore->pExpressionRight);
        }
        
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS,
            &pPostfixExpressionCore->ClueList);
    }
    break;

    case TK_LEFT_SQUARE_BRACKET:
    {
        pPostfixExpressionCore->token = token;
        // postfix-expression [ expression ]

        Parser_MatchToken(ctx, TK_LEFT_SQUARE_BRACKET,
            &pPostfixExpressionCore->ClueList);

        Expression0(ctx, &pPostfixExpressionCore->pExpressionRight);
        
        Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, NULL);
    }
    break;

    case TK_FULL_STOP:
    {
        // postfix-expression . identifier
        pPostfixExpressionCore->token = token;
      
        Parser_Match(ctx, &pPostfixExpressionCore->ClueList);

        String_Set(&pPostfixExpressionCore->Identifier, Lexeme(ctx));

        Parser_MatchToken(ctx, TK_IDENTIFIER,
            &pPostfixExpressionCore->ClueList);
    }
    break;

    case TK_ARROW:
    {
        // postfix-expression -> identifier
        pPostfixExpressionCore->token = token;

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList);

        String_Set(&pPostfixExpressionCore->Identifier, Lexeme(ctx));

        Parser_MatchToken(ctx, TK_IDENTIFIER, &pPostfixExpressionCore->ClueList);
    }
    break;

    case TK_PLUSPLUS:
    {
        pPostfixExpressionCore->token = token;
        //postfix-expression ++

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList);
    }
    break;

    case TK_MINUSMINUS:
    {
        //  postfix-expression --
        pPostfixExpressionCore->token = token;
        Parser_Match(ctx, &pPostfixExpressionCore->ClueList);
    }
    break;

    default:
        // ASSERT(false);
        break;
    }


    token = Parser_CurrentToken(ctx);

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

        if (pPostfixExpressionCore->pNext != NULL)
        {
            SetUnexpectedError(ctx, "", "");
        }
        pPostfixExpressionCore->pNext = pPostfixExpressionCoreNext;
    }
    break;
    }


}

void PostfixExpression(Parser* ctx, TExpression** ppExpression)
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

    Tokens token = Parser_CurrentToken(ctx);


    if (token == TK_LEFT_PARENTHESIS)
    {
        const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);
        Tokens lookAheadToken = Parser_LookAheadToken(ctx);

        if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
        {
            // ( type-name ) { initializer-list }

            TPostfixExpressionCore *  pTPostfixExpressionCore =
                TPostfixExpressionCore_Create();

            Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pTPostfixExpressionCore->ClueList);

            TTypeName typeName = TTYPENAME_INIT;
            TypeName(ctx, &typeName);
            TParameterDeclaration_Destroy(&typeName);

            Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pTPostfixExpressionCore->ClueList);

            Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, &pTPostfixExpressionCore->ClueList);

            Initializer_List(ctx, &pTPostfixExpressionCore->InitializerList);

            Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, &pTPostfixExpressionCore->ClueList);

            if (Parser_CurrentToken(ctx) == TK_COMMA)
            {
                Parser_Match(ctx, &pTPostfixExpressionCore->ClueList);
            }

            *ppExpression = (TExpression*)pTPostfixExpressionCore;
        }

        else
        {
            //primary-expression
            TExpression* pPrimaryExpression;
            PrimaryExpression(ctx, &pPrimaryExpression);
            *ppExpression = pPrimaryExpression;
        }
    }

    else
    {
        //primary-expression
        TExpression* pPrimaryExpression;
        PrimaryExpression(ctx, &pPrimaryExpression);
        *ppExpression = pPrimaryExpression;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
        TPostfixExpressionCore *  pPostfixExpressionCore =
            TPostfixExpressionCore_Create();
        pPostfixExpressionCore->pExpressionLeft = *ppExpression;

        String lexemeCopy = STRING_INIT;

        TPrimaryExpressionValue* ppri =
            TExpression_As_TPrimaryExpressionValue(*ppExpression);
        if (ppri)
        {
            String_Set(&lexemeCopy, ppri->lexeme);
        }
        PostfixExpressionCore(ctx, pPostfixExpressionCore);
        *ppExpression = (TExpression*)pPostfixExpressionCore;


        if (ppri)
        {
            if (IsTemplateFunction(lexemeCopy))
            {
                TDeclaration* pDecl =
                    FindDeclarationOfDeclarator(&ctx->Symbols, lexemeCopy);
                if (!pDecl)
                {
                    StrBuilder sb = STRBUILDER_INIT;
                    StrBuilder sb2 = STRBUILDER_INIT;
                    InstantiateTemplateFunction(lexemeCopy, &sb, &sb2);

                    //nao tem a declaracao ainda
                    PushExpandedMacro(&ctx->Scanner,
                        "",
                        "",
                        sb.c_str);

                    TAnyDeclaration* pDeclaration;
                    bool bResult = Declaration(ctx,
                        &pDeclaration);
                    //expading == 0;

                    ArrayT_Push(&ctx->Templates, pDeclaration);
                    SetSymbolsFromDeclaration(ctx, pDeclaration);
                    //TDeclarations_Push(&ctx->TemplatesInstances, pDeclaration);

                    //nao tem a declaracao ainda
                    PushExpandedMacro(&ctx->Scanner,
                        "",
                        "",
                        sb2.c_str);
                    pDeclaration = NULL;
                    bResult = Declaration(ctx,
                        &pDeclaration);
                    //expading == 0;
                    ArrayT_Push(&ctx->TemplatesInstances, pDeclaration);
                    SetSymbolsFromDeclaration(ctx, pDeclaration);

                    StrBuilder_Destroy(&sb);
                    StrBuilder_Destroy(&sb2);


                }
            }
        }

        String_Destroy(&lexemeCopy);
    }
    break;
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
        *ppExpression = (TExpression*)pPostfixExpressionCore;
    }
    break;
    }

}

void ArgumentExpressionList(Parser* ctx, TExpression** ppExpression)
{
    /*(6.5.2) argument-expression-list:
    assignment-expression
    argument-expression-list , assignment-expression
    */
    TExpression* pAssignmentExpression;
    AssignmentExpression(ctx, &pAssignmentExpression);
    *ppExpression = pAssignmentExpression;

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COMMA)
    {
        Parser_Match(ctx, NULL);// &pAssignmentExpression->ClueList);

        TExpression* pAssignmentExpressionRight;
        AssignmentExpression(ctx, &pAssignmentExpressionRight);

        TBinaryExpression *  pExpr =
            TBinaryExpression_Create();

        GetPosition(ctx, &pExpr->Position);
        pExpr->token = TK_COMMA;
        pExpr->pExpressionLeft = pAssignmentExpression;
        pExpr->pExpressionRight = pAssignmentExpressionRight;



        *ppExpression = (TExpression*)pExpr;
    }

    token = Parser_CurrentToken(ctx);

    if (token == TK_COMMA)
    {
        Parser_Match(ctx, NULL);

        TBinaryExpression *  pExpr =
            TBinaryExpression_Create();

        GetPosition(ctx, &pExpr->Position);
        pExpr->token = TK_COMMA;
        pExpr->pExpressionLeft = *ppExpression;

        TExpression *pExpressionRight;
        ArgumentExpressionList(ctx, &pExpressionRight);
        pExpr->pExpressionRight = pExpressionRight;



        *ppExpression = (TExpression*)pExpr;
    }
}



static bool IsTypeQualifierToken(Tokens token)
{
    bool bResult = false;
    switch (token)
    {
        //type-qualifier
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:
        //
        bResult = true;
        break;
#ifdef LANGUAGE_EXTENSIONS
        //type-qualifier-extensions 
    case TK_OPT_QUALIFIER:
    case TK_OWN_QUALIFIER:
    case TK_DTOR_QUALIFIER:
    case TK_MDTOR_QUALIFIER:
        bResult = true;
        break;
#endif
    }
    return bResult;
}

bool IsTypeName(Parser* ctx, Tokens token, const char * lexeme)
{
    bool bResult = false;

    if (lexeme == NULL)
    {
        return false;
    }

    switch (token)
    {

    case TK_IDENTIFIER:
        bResult = DeclarationsMap_IsTypeDef(&ctx->Symbols, lexeme);
        break;

        //type-qualifier
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:

#ifdef LANGUAGE_EXTENSIONS
        //type-qualifier-extensions 
    case TK_OPT_QUALIFIER:
    case TK_OWN_QUALIFIER:
    case TK_DTOR_QUALIFIER:
    case TK_MDTOR_QUALIFIER:
#endif

        //type-specifier
    case TK_VOID:
    case TK_char:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
    case TK_FLOAT:
    case TK_DOUBLE:
    case TK_SIGNED:
    case TK_UNSIGNED:
    case TK__BOOL:
    case TK__COMPLEX:
    case TK_STRUCT:
    case TK_UNION:
    case TK_ENUM:
        bResult = true;
        break;
    }

    return bResult;
}

void UnaryExpression(Parser* ctx, TExpression** ppExpression)
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

    Tokens token0 = Parser_CurrentToken(ctx);
    Tokens tokenAhead = Parser_LookAheadToken(ctx);
    const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);

    if (IsTypeName(ctx, tokenAhead, lookAheadlexeme))
    {
        //first para postfix-expression
        TExpression * pPostfixExpression;
        PostfixExpression(ctx, &pPostfixExpression);
        *ppExpression = (TExpression*)(pPostfixExpression);
        return;
    }

    else if (IsFirstOfPrimaryExpression(token0))
    {
        //primary-expression � first para postfix-expression

        TExpression * pPostfixExpression;
        PostfixExpression(ctx, &pPostfixExpression);
        *ppExpression = (TExpression*)(pPostfixExpression);
        return;
    }

    switch (token0)
    {
    case TK_PLUSPLUS:
    case TK_MINUSMINUS:
    {
        TUnaryExpressionOperator* pUnaryExpressionOperator =
            TUnaryExpressionOperator_Create();

        Parser_Match(ctx, &pUnaryExpressionOperator->ClueList0);

        TExpression *pUnaryExpression;
        UnaryExpression(ctx, &pUnaryExpression);


        pUnaryExpressionOperator->token = token0;
        pUnaryExpressionOperator->pExpressionLeft = pUnaryExpression;
        *ppExpression = (TExpression*)pUnaryExpressionOperator;
    }
    break;

    //unary-operator cast-expression
    case TK_AMPERSAND:
    case TK_ASTERISK:
    case TK_PLUS_SIGN:
    case TK_HYPHEN_MINUS:
    case TK_TILDE:
    case TK_EXCLAMATION_MARK:

#ifdef LANGUAGE_EXTENSIONS
        //unary-operator-extension
    case TK_MOVE:
#endif
        //
    {
        Parser_Match(ctx, NULL);
        TExpression* pCastExpression;
        CastExpression(ctx, &pCastExpression);


        TUnaryExpressionOperator* pUnaryExpressionOperator =
            TUnaryExpressionOperator_Create();
        pUnaryExpressionOperator->token = token0;
        pUnaryExpressionOperator->pExpressionLeft = pCastExpression;
        *ppExpression = (TExpression*)pUnaryExpressionOperator;

    }
    break;

    //////////////

    case TK_SIZEOF:

        Parser_MatchToken(ctx, TK_SIZEOF, NULL);// &pTPostfixExpressionCore->ClueList);

        if (Parser_CurrentToken(ctx) == TK_LEFT_PARENTHESIS)
        {
            const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);
            Tokens lookAheadToken = Parser_LookAheadToken(ctx);

            if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
            {
                TUnaryExpressionOperator* pUnaryExpressionOperator =
                    TUnaryExpressionOperator_Create();



                //sizeof deste tipo
                Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, NULL);

                TypeName(ctx, &pUnaryExpressionOperator->TypeName);

                Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL);



                pUnaryExpressionOperator->token = token0;
                //pUnaryExpressionOperator->pExpressionRight = pCastExpression;
                *ppExpression = (TExpression*)pUnaryExpressionOperator;

            }

            else
            {
                //sizeof do tipo desta expressao
                TExpression *pTUnaryExpression;
                UnaryExpression(ctx, &pTUnaryExpression);

                TUnaryExpressionOperator* pUnaryExpressionOperator =
                    TUnaryExpressionOperator_Create();
                pUnaryExpressionOperator->token = token0;
                pUnaryExpressionOperator->pExpressionLeft = pTUnaryExpression;
                *ppExpression = (TExpression*)pUnaryExpressionOperator;

            }
        }

        else
        {
            //sizeof do tipo desta expressao
            TExpression *pTUnaryExpression;
            UnaryExpression(ctx, &pTUnaryExpression);

            TUnaryExpressionOperator* pUnaryExpressionOperator =
                TUnaryExpressionOperator_Create();
            pUnaryExpressionOperator->token = token0;
            pUnaryExpressionOperator->pExpressionLeft = pTUnaryExpression;
            *ppExpression = (TExpression*)pUnaryExpressionOperator;
        }

        break;

    case TK__ALINGOF:
        //Match
        ASSERT(false);
        break;
    case TK_EOF:
        break;
    default:
        //ASSERT(false);
        SetUnexpectedError(ctx, "Assert", "");

        break;
    }

}

void CastExpression(Parser* ctx, TExpression** ppExpression)
{
    *ppExpression = NULL; //out

    /*
    cast-expression:
    unary-expression
    ( type-name ) cast-expression
    */

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_PARENTHESIS)
    {
        const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);
        Tokens lookAheadToken = Parser_LookAheadToken(ctx);

        if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
        {
            Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, NULL);
            TTypeName typeName = TTYPENAME_INIT;
            TypeName(ctx, &typeName);

            token = Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL);

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

                Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, NULL);

                TPostfixExpressionCore*  pTPostfixExpressionCore =
                    TPostfixExpressionCore_Create();
                pTPostfixExpressionCore->pTypeName = TParameterDeclaration_Create();
                TParameterDeclaration_Swap(pTPostfixExpressionCore->pTypeName, &typeName);

                //pTPostfixExpressionCore->pInitializerList = TInitializerList_Create();
                Initializer_List(ctx, &pTPostfixExpressionCore->InitializerList);

                //Initializer_List(ctx, pTPostfixExpressionCore->pInitializerList);


                if (Parser_CurrentToken(ctx) == TK_COMMA)
                {
                    Parser_Match(ctx, NULL);
                }
                Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, NULL);
                *ppExpression = (TExpression*)pTPostfixExpressionCore;
                //PostfixExpressionCore(ctx, pTPostfixExpressionCore);
            }
            else
            {
                TExpression* pCastExpression;
                CastExpression(ctx, &pCastExpression);

                TCastExpressionType *pCastExpressionType =
                    TCastExpressionType_Create();

                TParameterDeclaration_Swap(&pCastExpressionType->TypeName, &typeName);
                pCastExpressionType->pExpression = pCastExpression;
                *ppExpression = (TExpression*)pCastExpressionType;

            }

            TParameterDeclaration_Destroy(&typeName);
        }
        else
        {
            TExpression* pUnaryExpression;
            UnaryExpression(ctx, &pUnaryExpression);
            *ppExpression = pUnaryExpression;
        }
    }
    else
    {
        TExpression* pUnaryExpression;
        UnaryExpression(ctx, &pUnaryExpression);

        *ppExpression = pUnaryExpression;
    }
}


void MultiplicativeExpression(Parser* ctx, TExpression** ppExpression)
{


    /*
    (6.5.5) multiplicative-expression:
    cast-expression                                // identifier  constant  string-literal  (  _Generic ++	  -- 	 & * + - ~ ! 		 sizeof 		 sizeof		 alignof
    multiplicative-expression * cast-expression
    multiplicative-expression / cast-expression
    multiplicative-expression % cast-expression
    */

    TExpression* pExpressionLeft;
    CastExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


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
        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        CastExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

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

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        MultiplicativeExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }
}

void AdditiveExpression(Parser* ctx, TExpression** ppExpression)
{

    /*
    (6.5.6) additive-expression:
    multiplicative-expression
    additive-expression + multiplicative-expression
    additive-expression - multiplicative-expression
    */

    TExpression* pExpressionLeft;
    MultiplicativeExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


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

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        MultiplicativeExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_PLUS_SIGN:
    case TK_HYPHEN_MINUS:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        AdditiveExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

}

void ShiftExpression(Parser* ctx, TExpression** ppExpression)
{

    /*(6.5.7) shift-expression:
    additive-expression
    shift-expression << additive-expression
    shift-expression >> additive-expression
    */


    TExpression* pExpressionLeft;
    AdditiveExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_GREATERGREATER:
    case TK_LESSLESS:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        AdditiveExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_GREATERGREATER:
    case TK_LESSLESS:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        ShiftExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }
}

void RelationalExpression(Parser* ctx, TExpression** ppExpression)
{
    /*
    (6.5.8) relational-expression:
    shift-expression
    relational-expression < shift-expression
    relational-expression > shift-expression
    relational-expression <= shift-expression
    relational-expression >= shift-expression
    */

    TExpression* pExpressionLeft;
    ShiftExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


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

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        ShiftExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

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

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        RelationalExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

}

void EqualityExpression(Parser* ctx, TExpression** ppExpression)
{
    /*(6.5.9) equality-expression:
    relational-expression
    equality-expression == relational-expression
    equality-expression != relational-expression
    */

    TExpression* pExpressionLeft;
    RelationalExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_EQUALEQUAL:
    case TK_NOTEQUAL:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        RelationalExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_EQUALEQUAL:
    case TK_NOTEQUAL:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        EqualityExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }
}

void AndExpression(Parser* ctx, TExpression **ppExpression)
{
    /*(6.5.10) AND-expression:
    equality-expression
    AND-expression & equality-expression
    */

    TExpression* pExpressionLeft;
    EqualityExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_AMPERSAND:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        EqualityExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_AMPERSAND:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        AndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }
}

void ExclusiveOrExpression(Parser* ctx, TExpression** ppExpression)
{
    /*
    (6.5.11) exclusive-OR-expression:
    AND-expression
    exclusive-OR-expression ^ AND-expression
    */

    TExpression* pExpressionLeft;
    AndExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_CIRCUMFLEX_ACCENT:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        AndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_CIRCUMFLEX_ACCENT:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);


        TExpression* pExpressionRight;
        ExclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

}

void InclusiveOrExpression(Parser* ctx, TExpression**ppExpression)
{

    /*
    (6.5.12) inclusive-OR-expression:
    exclusive-OR-expression
    inclusive-OR-expression | exclusive-OR-expression
    */

    TExpression* pExpressionLeft;
    ExclusiveOrExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_VERTICAL_LINE:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        ExclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_VERTICAL_LINE:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        InclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }
}

void LogicalAndExpression(Parser* ctx, TExpression** ppExpression)
{

    /*
    (6.5.13) logical-AND-expression:
    inclusive-OR-expression
    logical-AND-expression && inclusive-OR-expression
    */

    TExpression* pExpressionLeft;
    InclusiveOrExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_ANDAND:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);


        TExpression* pExpressionRight;
        InclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_ANDAND:
    {
        TBinaryExpression *pBinaryExpression =
            TBinaryExpression_Create();

        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        LogicalAndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }
}

void LogicalOrExpression(Parser* ctx, TExpression** ppExpression)
{
    /*(6.5.14) logical-OR-expression:
     logical-AND-expression
     logical-OR-expression || logical-AND-expression
     */


    TExpression* pExpressionLeft;
    LogicalAndExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_OROR:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        LogicalAndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_OROR:
    {
        TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;

        
        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression* pExpressionRight;
        LogicalOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;
    }
}


void ConditionalExpression(Parser* ctx, TExpression**ppExpression)
{
    /*(6.5.15) conditional-expression:
    logical-OR-expression
    logical-OR-expression ? expression : conditional-expression
    */
    TExpression * pLogicalOrExpressionLeft;
    LogicalOrExpression(ctx, &pLogicalOrExpressionLeft);
    *ppExpression = pLogicalOrExpressionLeft;

    if (Parser_CurrentToken(ctx) == TK_QUESTION_MARK)
    {   
        TTernaryExpression* pTernaryExpression =
            TTernaryExpression_Create();

        Parser_Match(ctx, &pTernaryExpression->ClueList0);

        TExpression* pTExpression;
        Expression0(ctx, &pTExpression);

        Parser_MatchToken(ctx, TK_COLON, &pTernaryExpression->ClueList1);

        TExpression* pConditionalExpressionRight;
        ConditionalExpression(ctx, &pConditionalExpressionRight);
        

        pTernaryExpression->token = TK_QUESTION_MARK;
        pTernaryExpression->pExpressionLeft = pLogicalOrExpressionLeft;
        pTernaryExpression->pExpressionMiddle = pTExpression;
        pTernaryExpression->pExpressionRight = pConditionalExpressionRight;
        *ppExpression = (TExpression*)pTernaryExpression;
    }


}

void AssignmentExpression(Parser* ctx, TExpression** ppExpression)
{
    /*(6.5.16) assignment-expression:
    conditional-expression
    unary-expression assignment-operator assignment-expression

    (6.5.16) assignment-operator: one of
    = *= /= %= += -= <<= >>= &= ^= |=
    */


    //N�o sei se eh  conditional-expression ou
    //unary-expression
    //Mas a conditional-expression faz tambem a
    //unary-expression
    TExpression* pConditionalExpressionLeft;
    ConditionalExpression(ctx, &pConditionalExpressionLeft);
    *ppExpression = pConditionalExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);

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
        TBinaryExpression *pBinaryExpression =
            TBinaryExpression_Create();

        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        //Significa que o anterior deve ser do tipo  unary-expression
        //embora tenhamos feito o parser de conditional-expression
        //se nao for � erro.
        TExpression* pAssignmentExpressionRight;
        AssignmentExpression(ctx, &pAssignmentExpressionRight);
        
        GetPosition(ctx, &pBinaryExpression->Position);

        pBinaryExpression->pExpressionLeft = *ppExpression;
        pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
        pBinaryExpression->token = token;
        *ppExpression = (TExpression*)pBinaryExpression;
    }
    break;

    default:
        //� apenas conditional-expression
        break;
    }
}

void Expression0(Parser* ctx, TExpression** ppExpression)
{
    *ppExpression = NULL; //out
    /*
    (6.5.17) expression:
    assignment-expression
    expression , assignment-expression
    */
    TExpression* pAssignmentExpressionLeft;
    AssignmentExpression(ctx, &pAssignmentExpressionLeft);
    *ppExpression = pAssignmentExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COMMA)
    {
        TExpression* pAssignmentExpressionRight;
        Parser_Match(ctx, NULL);
        Expression0(ctx, &pAssignmentExpressionRight);

        TBinaryExpression* pBinaryExpression =
            TBinaryExpression_Create();
        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->pExpressionLeft = *ppExpression;
        pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
        pBinaryExpression->token = TK_COMMA;

        *ppExpression = (TExpression*)pBinaryExpression;
    }
}

void ConstantExpression(Parser* ctx, TExpression** ppExpression)
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
//void Expression(Parser* ctx, TExpression** pExpression, Tokens endToken1, Tokens endToken2);
void Parameter_Declaration(Parser* ctx, TParameterDeclaration* pParameterDeclaration);
bool Declaration(Parser* ctx, TAnyDeclaration** ppDeclaration);
void Type_Qualifier_ListOpt(Parser* ctx, TTypeQualifier* pQualifier);
bool Declaration_Specifiers(Parser* ctx, TDeclarationSpecifiers* pDeclarationSpecifiers);
void Declarator(Parser* ctx, TDeclarator** pTDeclarator2);
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
    Tokens token = Parser_CurrentToken(ctx);

    if (token != TK_SEMICOLON)
    {
        Expression0(ctx, &pExpression->pExpression);
    }

    Parser_MatchToken(ctx, TK_SEMICOLON, &pExpression->ClueList0);
}

void Selection_Statement(Parser* ctx, TStatement** ppStatement)
{
    /*
    selection-statement:
    if ( expression ) statement
    if ( expression ) statement else statement
    switch ( expression ) statement
    */
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_IF:
    {
        TIfStatement* pIfStatement = TIfStatement_Create();
        *ppStatement = (TStatement*)pIfStatement;

        //TNodeClueList_MoveToEnd(&pIfStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pIfStatement->ClueList);

        //TNodeClueList_MoveToEnd(&pIfStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pIfStatement->ClueList);

        //      TExpression0 * pExpression =
        //      NewObject(pStatement, "expression");
        Expression0(ctx, &pIfStatement->pConditionExpression);

        //    //TNodeClueList_MoveToEnd(&pIfStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pIfStatement->ClueList);

        //TStatement0 * pTrueStatement =
        //NewObject(pStatement, "statement-true");
        Statement(ctx, &pIfStatement->pStatement);
        token = Parser_CurrentToken(ctx);

        if (token == TK_ELSE)
        {
            //TNodeClueList_MoveToEnd(&pIfStatement->ClueList, &ctx->Scanner.ClueList);
            Parser_Match(ctx, &pIfStatement->ClueList);
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

        //TNodeClueList_MoveToEnd(&pSelectionStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pSelectionStatement->ClueList);

        //TNodeClueList_MoveToEnd(&pSelectionStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pSelectionStatement->ClueList);

        //TExpression0 * pExpression =
        //NewObject(pStatement, "expression");
        Expression0(ctx, &pSelectionStatement->pConditionExpression);

        //TNodeClueList_MoveToEnd(&pSelectionStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pSelectionStatement->ClueList);

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
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_GOTO:
    {
        TJumpStatement* pJumpStatement = TJumpStatement_Create();
        pJumpStatement->token = token;
        *ppStatement = (TStatement*)pJumpStatement;

        //TNodeClueList_MoveToEnd(&pJumpStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pJumpStatement->ClueList);

        //TNodeClueList_MoveToEnd(&pJumpStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_IDENTIFIER, &pJumpStatement->ClueList);
    }
    break;

    case TK_CONTINUE:
    {
        TJumpStatement* pJumpStatement = TJumpStatement_Create();
        pJumpStatement->token = token;
        *ppStatement = (TStatement*)pJumpStatement;

        //TNodeClueList_MoveToEnd(&pJumpStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pJumpStatement->ClueList);

        //TNodeClueList_MoveToEnd(&pJumpStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList);
    }
    break;

    case TK_BREAK:
    {
        TJumpStatement* pJumpStatement = TJumpStatement_Create();
        pJumpStatement->token = token;
        *ppStatement = (TStatement*)pJumpStatement;

        //TNodeClueList_MoveToEnd(&pJumpStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pJumpStatement->ClueList);

        //    //TNodeClueList_MoveToEnd(&pJumpStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList);
    }
    break;

    case TK_RETURN:
    {
        TReturnStatement* pReturnStatement = TReturnStatement_Create();

        *ppStatement = (TStatement*)pReturnStatement;

        token = Parser_Match(ctx, &pReturnStatement->ClueList0);

        if (token != TK_SEMICOLON)
        {
            Expression0(ctx, &pReturnStatement->pExpression);
        }
        
        Parser_MatchToken(ctx, TK_SEMICOLON, &pReturnStatement->ClueList1);
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
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_WHILE:
    {
        TWhileStatement* pWhileStatement = TWhileStatement_Create();
        *ppStatement = (TStatement*)pWhileStatement;

        //TNodeClueList_MoveToEnd(&pWhileStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pWhileStatement->ClueList);

        //    //TNodeClueList_MoveToEnd(&pWhileStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pWhileStatement->ClueList);

        Expression0(ctx, &pWhileStatement->pExpression);

        //    //TNodeClueList_MoveToEnd(&pWhileStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pWhileStatement->ClueList);

        Statement(ctx, &pWhileStatement->pStatement);
    }
    break;

    case TK_DO:
    {
        TDoStatement* pDoStatement = TDoStatement_Create();
        *ppStatement = (TStatement*)pDoStatement;

        //    //TNodeClueList_MoveToEnd(&pDoStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pDoStatement->ClueList);

        Statement(ctx, &pDoStatement->pStatement);

        //    //TNodeClueList_MoveToEnd(&pDoStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_WHILE, &pDoStatement->ClueList);

        //    //TNodeClueList_MoveToEnd(&pDoStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDoStatement->ClueList);

        Expression0(ctx, &pDoStatement->pExpression);

        //    //TNodeClueList_MoveToEnd(&pDoStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDoStatement->ClueList);

        ////TNodeClueList_MoveToEnd(&pDoStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_SEMICOLON, &pDoStatement->ClueList);
    }
    break;

    case TK_FOR:
    {
        TForStatement* pIterationStatement = TForStatement_Create();
        *ppStatement = (TStatement*)pIterationStatement;

        ////TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pIterationStatement->ClueList);

        ////TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
        token = Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS,
            &pIterationStatement->ClueList);

        //primeira expressao do for
        if (token != TK_SEMICOLON)
        {
            //
            //for (expressionopt; expressionopt; expressionopt) statement
            //for (declaration expressionopt; expressionopt) statement

            bool bHasDeclaration = Declaration(ctx, &pIterationStatement->pInitDeclarationOpt);

            if (bHasDeclaration)
            {
                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    //Esta eh a 2 expressao do for, a declaracao ja comeu 1
                    Expression0(ctx, &pIterationStatement->pExpression2);

                    ////TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);
                }
                else
                {
                    //segunda expressao vazia
                    ////TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);
                }
            }

            else
            {
                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    //primeira expressao do for
                    Expression0(ctx, &pIterationStatement->pExpression1);

                    ////TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);
                }

                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    //segunda expressao do for
                    Expression0(ctx, &pIterationStatement->pExpression2);

                    //TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);
                }

                else
                {
                    //segunda expressao vazia
                    //TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);
                }

            }
        }

        else
        {
            //primeira expressao do for vazia
            //TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
            Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);

            token = Parser_CurrentToken(ctx);

            if (token != TK_SEMICOLON)
            {
                //Esta eh a 2 expressao do for, a declaracao ja comeu 1
                Expression0(ctx, &pIterationStatement->pExpression2);

                //TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
                Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);
            }

            else
            {
                //segunda expressao do for vazia tb
                //TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
                Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList);
            }
        }

        token = Parser_CurrentToken(ctx);

        //terceira expressao do for
        if (token != TK_RIGHT_PARENTHESIS)
        {
            Expression0(ctx, &pIterationStatement->pExpression3);
        }

        //TNodeClueList_MoveToEnd(&pIterationStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pIterationStatement->ClueList);

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
    Tokens token = Parser_CurrentToken(ctx);
    pLabeledStatement->token = token;

    if (token == TK_IDENTIFIER)
    {
        //aqui nao eh um tipo
        String_Set(&pLabeledStatement->Identifier, Lexeme(ctx));

        //TNodeClueList_MoveToEnd(&pLabeledStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pLabeledStatement->ClueList);

        //TNodeClueList_MoveToEnd(&pLabeledStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_COLON, &pLabeledStatement->ClueList);

        Statement(ctx, &pLabeledStatement->pStatementOpt);
    }

    else if (token == TK_CASE)
    {
        //TNodeClueList_MoveToEnd(&pLabeledStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pLabeledStatement->ClueList);

        ConstantExpression(ctx, &pLabeledStatement->pExpression);

        //TNodeClueList_MoveToEnd(&pLabeledStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_COLON, &pLabeledStatement->ClueList);

        Statement(ctx, &pLabeledStatement->pStatementOpt);
    }

    else if (token == TK_DEFAULT)
    {
        //TNodeClueList_MoveToEnd(&pLabeledStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pLabeledStatement->ClueList);

        //TNodeClueList_MoveToEnd(&pLabeledStatement->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_COLON, &pLabeledStatement->ClueList);

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
    Parser_MatchToken(ctx, TK__ASM, NULL);
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_CURLY_BRACKET)
    {
        Parser_Match(ctx, NULL);

        for (; ;)
        {
            if (ErrorOrEof(ctx))
            {
                break;
            }

            token = Parser_CurrentToken(ctx);

            if (token == TK_RIGHT_CURLY_BRACKET)
            {
                Parser_Match(ctx, NULL);
                break;
            }

            Parser_Match(ctx, NULL);
        }
    }

    else
    {
        //sem ;
        //    __asm int 0x2c
        //chato
        token = Parser_CurrentToken(ctx);

        for (; ;)
        {
            if (ErrorOrEof(ctx))
            {
                break;
            }

            token = Parser_CurrentToken(ctx);

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

            Parser_Match(ctx, NULL);
        }
    }

    //opcional
    token = Parser_CurrentToken(ctx);

    if (token == TK_SEMICOLON)
    {
        Parser_Match(ctx, NULL);
    }
}

bool Statement(Parser* ctx, TStatement** ppStatement)
{
    ASSERT(*ppStatement == NULL);

    if (Parser_HasError(ctx))
    {
        return false;
    }

    bool bResult = false;
    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);

    switch (token)
    {
    case TK__ASM:
        bResult = true;
        Asm_Statement(ctx, ppStatement);
        break;

    case TK_LEFT_CURLY_BRACKET:
    {
        bResult = true;
        Compound_Statement(ctx, ppStatement);
    }
    break;

    case TK_CASE:
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
        Parser_Match(ctx, NULL); //else
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

        //lista de first para express�es
        //expression-statement
    case TK_LEFT_PARENTHESIS:
    case TK_SEMICOLON:

    case TK_DECIMAL_INTEGER:
    case TK_FLOAT_NUMBER:
    case TK_STRING_LITERAL:


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
#ifdef LANGUAGE_EXTENSIONS
        //unary-operator-extension
    case TK_ANDAND: //&&
#endif
        bResult = true;
        Expression_Statement(ctx, ppStatement);
        break;

    case TK_IDENTIFIER:

        if (DeclarationsMap_IsTypeDef(&ctx->Symbols, lexeme))
        {
            //� uma declaracao
        }
        else
        {
            if (Parser_LookAheadToken(ctx) == TK_COLON)
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

    case TK_INLINE:
    case TK__NORETURN:
    case TK__ALIGNAS:

        //type-qualifier
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:

#ifdef LANGUAGE_EXTENSIONS
        //type-qualifier-extensions 
    case TK_OPT_QUALIFIER:
    case TK_OWN_QUALIFIER:
    case TK_DTOR_QUALIFIER:
    case TK_MDTOR_QUALIFIER:
        //
#endif

    case TK_TYPEDEF:
    case TK_EXTERN:
    case TK_STATIC:
    case TK__THREAD_LOCAL:
    case TK_AUTO:
    case TK_REGISTER:
    case TK_VOID:
    case TK_char:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
    case TK_FLOAT:
    case TK_DOUBLE:
    case TK_SIGNED:
    case TK_UNSIGNED:
    case TK__BOOL:
    case TK__COMPLEX:
    case TK_STRUCT:
    case TK_UNION:
    case TK_ENUM:
        bResult = false;
        break;

    default:

        SetUnexpectedError(ctx, "e", "");
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
        ArrayT_Push(pBlockItemList, pBlockItem);
        Tokens token = Parser_CurrentToken(ctx);

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

    
    Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, &pCompoundStatement->ClueList0);

    Tokens token = Parser_CurrentToken(ctx);

    if (token != TK_RIGHT_CURLY_BRACKET)
    {
        Block_Item_List(ctx, &pCompoundStatement->BlockItemList);
    }

    Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, &pCompoundStatement->ClueList1);
}

void Struct_Or_Union(Parser* ctx,
    TStructUnionSpecifier* pStructUnionSpecifier)
{
    /*
    struct-or-union:
    struct
    union
    */
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_STRUCT:
        pStructUnionSpecifier->bIsStruct = true;
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList0);
        break;

    case TK_UNION:
        pStructUnionSpecifier->bIsStruct = false;
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList0);
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
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK__STATIC_ASSERT)
    {
        //TNodeClueList_MoveToEnd(&pStaticAssertDeclaration->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pStaticAssertDeclaration->ClueList);

        //TNodeClueList_MoveToEnd(&pStaticAssertDeclaration->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pStaticAssertDeclaration->ClueList);

        ConstantExpression(ctx,
            &pStaticAssertDeclaration->pConstantExpression);

        //TNodeClueList_MoveToEnd(&pStaticAssertDeclaration->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_COMMA, &pStaticAssertDeclaration->ClueList);

        //TNodeClueList_MoveToEnd(&pStaticAssertDeclaration->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_STRING_LITERAL, &pStaticAssertDeclaration->ClueList);

        //TNodeClueList_MoveToEnd(&pStaticAssertDeclaration->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pStaticAssertDeclaration->ClueList);

        //TNodeClueList_MoveToEnd(&pStaticAssertDeclaration->ClueList, &ctx->Scanner.ClueList);
        Parser_MatchToken(ctx, TK_SEMICOLON, &pStaticAssertDeclaration->ClueList);
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

    TStructDeclarator** ppTDeclarator2)
{
    /**
    struct-declarator:
    declarator
    declaratoropt : constant-expression
    */
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COLON)
    {
        //AST TODO
        ////TNodeClueList_MoveToEnd(&ppTDeclarator2->ClueList, &ctx->Scanner.ClueList);

        Parser_Match(ctx, NULL);// &ppTDeclarator2->ClueList);
        TExpression* p = NULL;
        ConstantExpression(ctx, &p);
        TExpression_Delete(p);
    }

    else
    {
        TInitDeclarator* pInitDeclarator =
            TInitDeclarator_Create();

        *ppTDeclarator2 = pInitDeclarator;

        ASSERT(pInitDeclarator->pDeclarator == NULL);
        Declarator(ctx, &pInitDeclarator->pDeclarator);

        token = Parser_CurrentToken(ctx);

        if (token == TK_COLON)
        {
            Parser_Match(ctx, &pInitDeclarator->ClueList0);

            TExpression* p = NULL;
            ConstantExpression(ctx, &p);
            TExpression_Delete(p);
        }
#ifdef LANGUAGE_EXTENSIONS
        else if (token == TK_EQUALS_SIGN)
        {
            //TNodeClueList_MoveToEnd(&pInitDeclarator->ClueList, &ctx->Scanner.ClueList);
            //TODO COMPILER EXTENSION! SHOW ERROR IF EXTENSIONS NOT ENABLED
            //struct { int i = 1; }
            Parser_Match(ctx, NULL);

            Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);

        }
#endif
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
    TStructDeclarator* pTDeclarator2 = NULL;// TDeclarator_Create();

    Struct_Declarator(ctx, &pTDeclarator2);
    List_Add(pStructDeclarationList, pTDeclarator2);

    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        Tokens token = Parser_CurrentToken(ctx);

        if (token == TK_COMMA)
        {

            
            Parser_Match(ctx, &pTDeclarator2->ClueList0);

            Struct_Declarator_List(ctx, pStructDeclarationList);
        }

        else if (token == TK_SEMICOLON)
        {
            break;
        }

        else
        {
            SetUnexpectedError(ctx, "Struct_Declarator_List unexpected", "");
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
    Tokens token = Parser_CurrentToken(ctx);

    if (token != TK__STATIC_ASSERT)
    {
        TStructDeclaration* pStructDeclarationBase = TStructDeclaration_Create();
        *ppStructDeclaration = (TAnyStructDeclaration*)pStructDeclarationBase;
        Specifier_Qualifier_List(ctx,
            &pStructDeclarationBase->Qualifier,
            &pStructDeclarationBase->pSpecifier);
        token = Parser_CurrentToken(ctx);

        if (token != TK_SEMICOLON)
        {
            Struct_Declarator_List(ctx,
                &pStructDeclarationBase->DeclaratorList);

            Parser_MatchToken(ctx, TK_SEMICOLON, &pStructDeclarationBase->ClueList1);
        }
        else
        {
            Parser_MatchToken(ctx, TK_SEMICOLON, &pStructDeclarationBase->ClueList1);
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
    if (ErrorOrEof(ctx))
    {
        return;
    }

    TAnyStructDeclaration* pStructDeclaration = NULL;
    Struct_Declaration(ctx, &pStructDeclaration);
    ArrayT_Push(pStructDeclarationList, pStructDeclaration);

    Tokens token = Parser_CurrentToken(ctx);
    if (token != TK_RIGHT_CURLY_BRACKET)
    {
        //Tem mais?
        Struct_Declaration_List(ctx, pStructDeclarationList);
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


    Tokens token0 = Parser_CurrentToken(ctx);
    const char* lexeme = Lexeme(ctx);

    if (token0 == TK_IDENTIFIER)
    {

        String_Set(&pStructUnionSpecifier->Name, lexeme);
        
        //name
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList1);
    }

    else
    {
        const char* name = GetName();
        String_Set(&pStructUnionSpecifier->Name, name);
        //{
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList2);
    }
    

    Tokens token1 = Parser_CurrentToken(ctx);

    if (token0 == TK_IDENTIFIER)
    {
        //ja foi feito match do identificador
        if (token1 == TK_LEFT_CURLY_BRACKET)
        {
            Parser_Match(ctx, &pStructUnionSpecifier->ClueList2);

            Struct_Declaration_List(ctx,
                &pStructUnionSpecifier->StructDeclarationList);

            Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
                &pStructUnionSpecifier->ClueList3);
        }
        else
        {
            //
        }
    }
    else if (token0 == TK_LEFT_CURLY_BRACKET)
    {
        Struct_Declaration_List(ctx, &pStructUnionSpecifier->StructDeclarationList);

        Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
            &pStructUnionSpecifier->ClueList3);
    }

    else
    {
        SetError2(ctx, "expected name or {", "");
    }
}

void Enumeration_Constant(Parser* ctx,
    TEnumerator* pEnumerator2)
{
    const char* lexeme = Lexeme(ctx);
    String_Set(&pEnumerator2->Name, lexeme);

    //TODO colocar um ponteiro
    Map_Set(&ctx->EnumMap, lexeme, (void*)1);

    //TNodeClueList_MoveToEnd(&pEnumerator2->ClueList, &ctx->Scanner.ClueList);
    Parser_MatchToken(ctx, TK_IDENTIFIER, &pEnumerator2->ClueList);
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


    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_EQUALS_SIGN)
    {
        //TNodeClueList_MoveToEnd(&pEnumerator2->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pEnumerator2->ClueList);

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
    List_Add(pEnumeratorList2, pEnumerator2);

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

        Tokens token = Parser_CurrentToken(ctx);

        if (token == TK_COMMA)
        {
            //tem mais
            ////TNodeClueList_MoveToEnd(&pPointer->ClueList, &ctx->Scanner.ClueList);
            Parser_Match(ctx, NULL);
            token = Parser_CurrentToken(ctx);

            //o enum aceita uma , no fim
            if (token != TK_RIGHT_CURLY_BRACKET)
            {
                TEnumerator* pEnumerator3 = TEnumerator_Create();
                List_Add(pEnumeratorList2, pEnumerator3);

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

    Parser_MatchToken(ctx, TK_ENUM, &pEnumSpecifier2->ClueList0);

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_IDENTIFIER)
    {
        const char* lexeme = Lexeme(ctx);
        String_Set(&pEnumSpecifier2->Name, lexeme);
        Parser_Match(ctx, &pEnumSpecifier2->ClueList1);
    }

    else
    {
        const char* name = GetName();
        String_Set(&pEnumSpecifier2->Name, name);
        Parser_Match(ctx, &pEnumSpecifier2->ClueList2);
    }


    if (token == TK_IDENTIFIER)
    {
        //Ja fez Match do identifier
        token = Parser_CurrentToken(ctx);

        if (token == TK_LEFT_CURLY_BRACKET)
        {
            Parser_Match(ctx, &pEnumSpecifier2->ClueList2);

            Enumerator_List(ctx, &pEnumSpecifier2->EnumeratorList);

            Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
                &pEnumSpecifier2->ClueList3);
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
        
        Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
            &pEnumSpecifier2->ClueList3);
    }

    else
    {
        SetError2(ctx, "expected enum name or {", "");
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
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_INLINE:
        pFunctionSpecifier->bIsInline = true;
        Parser_Match(ctx, NULL);
        bResult = true;
        break;

    case TK__NORETURN:
        pFunctionSpecifier->bIsNoReturn = true;
        Parser_Match(ctx, NULL);
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
    Tokens token = Parser_CurrentToken(ctx);

    //const char* lexeme = Lexeme(ctx);
    switch (token)
    {
    case TK_TYPEDEF:
        pStorageSpecifier->bIsTypedef = true;
        Parser_Match(ctx, &pStorageSpecifier->ClueList0);
        bResult = true;
        break;

    case TK_EXTERN:
        pStorageSpecifier->bIsExtern = true;
        Parser_Match(ctx, &pStorageSpecifier->ClueList0);
        bResult = true;
        break;

    case TK_STATIC:
        pStorageSpecifier->bIsStatic = true;
        Parser_Match(ctx, &pStorageSpecifier->ClueList0);
        bResult = true;
        break;

    case TK__THREAD_LOCAL:
        pStorageSpecifier->bIsThread_local = true;
        Parser_Match(ctx, &pStorageSpecifier->ClueList0);
        bResult = true;
        break;

    case TK_AUTO:
        pStorageSpecifier->bIsAuto = true;
        Parser_Match(ctx, &pStorageSpecifier->ClueList0);
        bResult = true;
        break;

    case TK_REGISTER:
        pStorageSpecifier->bIsRegister = true;
        Parser_Match(ctx, &pStorageSpecifier->ClueList0);
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
    Tokens token = Parser_CurrentToken(ctx);

    TParameterDeclaration*  pParameter = TParameterDeclaration_Create();
    List_Add(pParameterList, pParameter);
    Parameter_Declaration(ctx, pParameter);

    //Tem mais?
    token = Parser_CurrentToken(ctx);
    if (token == TK_COMMA)
    {
        Parser_Match(ctx, NULL);
        Parameter_List(ctx, pParameterList);
    }
}



void AbstractDeclarator(Parser* ctx, TDeclarator** ppTDeclarator2)
{
    /*
    abstract-declarator:
    pointer
    pointeropt direct-abstract-declarator
    */
    //TODO!!! esta sendo usado como se fosse a mesma coisa?
    Declarator(ctx, ppTDeclarator2);
}

bool AbstractDeclaratorOpt(Parser* ctx, TDeclarator** ppTDeclarator2)
{
    bool bResult = false;
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_ASTERISK:
        AbstractDeclarator(ctx, ppTDeclarator2);
        break;
    }

    return bResult;
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

    TDeclarator *pDeclarator = NULL;
    AbstractDeclarator(ctx, &pDeclarator);
    if (pDeclarator)
    {
        pParameterDeclaration->Declarator = *pDeclarator;
    }
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
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_DOTDOTDOT)
    {
        //TODO ADD this parameter
        Parser_Match(ctx, NULL);
    }
}

void Direct_Abstract_Declarator(Parser* ctx, TDeclarator** ppDeclarator2)
{
    /*
    direct-abstract-declarator:
      ( abstract-declarator )
      direct-abstract-declaratoropt [ type-qualifier-listopt assignment-expressionopt ]
      direct-abstract-declaratoropt [ static type-qualifier-listopt assignment-expression ]
      direct-abstract-declaratoropt [ type-qualifier-list static assignment-expression ]
      direct-abstract-declaratoropt [ * ]
      direct-abstract-declaratoropt ( parameter-type-listopt )
    */
}

void Direct_Declarator(Parser* ctx, TDirectDeclarator** ppDeclarator2)
{
    *ppDeclarator2 = NULL; //out

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
    TDirectDeclarator *pDirectDeclarator = NULL;

    if (ErrorOrEof(ctx))
        return;


    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDirectDeclarator->ClueList0);
        
        ASSERT(pDirectDeclarator == NULL);
        pDirectDeclarator = TDirectDeclarator_Create();
        Declarator(ctx, &pDirectDeclarator->pDeclarator);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDirectDeclarator->ClueList1);

        //Para indicar que eh uma ( declarator )
        pDirectDeclarator->Type = TDirectDeclaratorTypeDeclarator;
        // ) para nao confundir com funcao (
    }
    break;

    case TK_IDENTIFIER:
    {
        //identifier
        pDirectDeclarator = TDirectDeclarator_Create();

        //Para indicar que eh uma identificador

        pDirectDeclarator->Type = TDirectDeclaratorTypeIdentifier;

        const char* lexeme = Lexeme(ctx);
        String_Set(&pDirectDeclarator->Identifier, lexeme);
        pDirectDeclarator->Position.Line = GetCurrentLine(ctx);
        pDirectDeclarator->Position.FileIndex = GetFileIndex(ctx);
        Parser_Match(ctx, &pDirectDeclarator->ClueList0);
    }
    break;

    default:
        //assert(false);
        break;
    }



    if (pDirectDeclarator == NULL)
    {
        //Por enquanto esta funcao esta sendo usada para
        //abstract declarator que nao tem nome.
        //vou criar aqui por enquanto um cara vazio
        pDirectDeclarator = TDirectDeclarator_Create();
        String_Set(&pDirectDeclarator->Identifier, "");
        pDirectDeclarator->Position.Line = GetCurrentLine(ctx);
        pDirectDeclarator->Position.FileIndex = GetFileIndex(ctx);

        //Para indicar que eh uma identificador

        pDirectDeclarator->Type = TDirectDeclaratorTypeIdentifier;

        //Quando tiver abstract declarator vai ser 
        //bug cair aqui
    }

    *ppDeclarator2 = pDirectDeclarator;

    for (;;)
    {
        ASSERT(pDirectDeclarator != NULL);

        token = Parser_CurrentToken(ctx);
        switch (token)
        {
        case TK_LEFT_PARENTHESIS:

            /*
            direct-declarator ( parameter-type-list )
            direct-declarator ( identifier-listopt )
            */
            //      pDirectDeclarator->token = token;
      //      ASSERT(pDirectDeclarator->pParametersOpt == NULL);
      //      pDirectDeclarator->pParametersOpt = TParameterList_Create();
            token = Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDirectDeclarator->ClueList2);

            //Para indicar que eh uma funcao

            pDirectDeclarator->Type = TDirectDeclaratorTypeFunction;

            if (token != TK_RIGHT_PARENTHESIS)
            {
                //opt
                Parameter_Type_List(ctx, &pDirectDeclarator->Parameters);
            }
            Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDirectDeclarator->ClueList3);
            break;

        case TK_LEFT_SQUARE_BRACKET:
            /*
            direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
            direct-declarator [ static type-qualifier-listopt assignment-expression ]
            direct-declarator [ type-qualifier-list static assignment-expression ]
            direct-declarator [ type-qualifier-listopt * ]
            */

            //ASSERT(pDirectDeclarator->pParametersOpt == NULL);
            //pDirectDeclarator->pParametersOpt = TParameterList_Create();

            //Para indicar que eh um array

            pDirectDeclarator->Type = TDirectDeclaratorTypeArray;

            token = Parser_MatchToken(ctx, TK_LEFT_SQUARE_BRACKET, &pDirectDeclarator->ClueList2);
            if (token == TK_STATIC)
            {
            }
            else
            {
                if (token != TK_RIGHT_SQUARE_BRACKET)
                {
                    ASSERT(pDirectDeclarator->pExpression == NULL);
                    AssignmentExpression(ctx, &pDirectDeclarator->pExpression);
                }
                else
                {
                    //array vazio � permitido se for o ultimo cara da struct          
                    //struct X { int ElementCount;  int Elements[]; };           
                }
            }

            Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, &pDirectDeclarator->ClueList3);

            break;
        }

        token = Parser_CurrentToken(ctx);
        if (token != TK_LEFT_PARENTHESIS &&   token != TK_LEFT_SQUARE_BRACKET)
        {
            break;
        }
        else
        {
            TDirectDeclarator *pDirectDeclaratorNext = TDirectDeclarator_Create();
            pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
            pDirectDeclarator = pDirectDeclaratorNext;
        }
    }

    token = Parser_CurrentToken(ctx);
    if (token == TK_LEFT_PARENTHESIS ||
        token == TK_IDENTIFIER)
    {
        //tem mais
        TDirectDeclarator *pDirectDeclaratorNext = NULL;
        Direct_Declarator(ctx, &pDirectDeclaratorNext);
        pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
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
    Tokens token = Parser_CurrentToken(ctx);

    //const char* lexeme = Lexeme(ctx);
    switch (token)
    {



    case TK_CONST:
        pQualifier->bIsConst = true;
        //TNodeClueList_MoveToEnd(&pQualifier->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &pQualifier->ClueList1);
        bResult = true;
        break;

    case TK_RESTRICT:
        //TNodeClueList_MoveToEnd(&pQualifier->ClueList, &ctx->Scanner.ClueList);
        pQualifier->bIsRestrict = true;
        Parser_Match(ctx, &pQualifier->ClueList1);
        bResult = true;
        break;

    case TK_VOLATILE:
        //TNodeClueList_MoveToEnd(&pQualifier->ClueList, &ctx->Scanner.ClueList);
        pQualifier->bIsVolatile = true;
        Parser_Match(ctx, &pQualifier->ClueList1);
        bResult = true;
        break;

    case TK__ATOMIC:
        //TNodeClueList_MoveToEnd(&pQualifier->ClueList, &ctx->Scanner.ClueList);
        pQualifier->bIsAtomic = true;
        Parser_Match(ctx, &pQualifier->ClueList1);
        bResult = true;
        break;

#ifdef LANGUAGE_EXTENSIONS
        //type-qualifier-extensions 
    case TK_OPT_QUALIFIER:
        pQualifier->bIsOpt = true;
        Parser_Match(ctx, NULL);
        bResult = true;
        break;
    case TK_OWN_QUALIFIER:
        pQualifier->bIsOwner = true;

        Parser_Match(ctx, NULL);
        bResult = true;
        break;
    case TK_DTOR_QUALIFIER:
        pQualifier->bIsDestructor = true;
        Parser_Match(ctx, NULL);
        bResult = true;
        break;
    case TK_MDTOR_QUALIFIER:
        pQualifier->bIsMemDestructor = true;
        Parser_Match(ctx, NULL);
        bResult = true;
        break;
#endif
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
    Tokens token = Parser_CurrentToken(ctx);

    while (IsTypeQualifierToken(token) ||
        token == TK_ASTERISK)   //pointer
    {
        TPointer* pPointer = TPointer_Create();
        List_Add(pPointerList, pPointer);

        if (IsTypeQualifierToken(token))
        {
            Type_Qualifier_ListOpt(ctx, &pPointer->Qualifier);
        }
        else if (token == TK_ASTERISK)
        {
            pPointer->bPointer = true;
            //TNodeClueList_MoveToEnd(&pPointer->ClueList, &ctx->Scanner.ClueList);
            Parser_Match(ctx, &pPointer->ClueList);
        }

        token = Parser_CurrentToken(ctx);
        ns++;
    }

    //Retorna numero de items empilhados
    return ns;
}

void Abstract_Declarator(Parser* ctx, TDeclarator** ppTDeclarator2)
{
    /*
    abstract-declarator:
    pointer
    pointeropt direct-abstract-declarator
    */
}

//pag 123 C
void Declarator(Parser* ctx, TDeclarator** ppTDeclarator2)
{
    *ppTDeclarator2 = NULL; //out
    TDeclarator* pDeclarator = TDeclarator_Create();
    /*
    declarator:
    pointeropt direct-declarator
    */
    PointerOpt(ctx, &pDeclarator->PointerList);

    ASSERT(pDeclarator->pDirectDeclarator == NULL);
    Direct_Declarator(ctx, &pDeclarator->pDirectDeclarator);

    *ppTDeclarator2 = pDeclarator;
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
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK__ALIGNAS)
    {
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, NULL);
        ASSERT(false);//TODO
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL);
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
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
        //type - specifier
    case TK_VOID:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
        }

        pSingleTypeSpecifier->bIsVoid = true;
        bResult = true;

        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

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

        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK_SHORT:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsShort = true;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK_INT:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsInt = true;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK_LONG:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->nLong++;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK_FLOAT:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsFloat = true;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK_DOUBLE:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsDouble = true;
        bResult = true;
        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK_SIGNED:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsSigned = true;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK_UNSIGNED:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsUnsigned = true;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK__BOOL:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsBool = true;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    case TK__COMPLEX:
    {
        if (pSingleTypeSpecifier == NULL)
        {
            pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

        }

        pSingleTypeSpecifier->bIsComplex = true;
        bResult = true;

        
        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
    }
    break;

    //atomic-type-specifier
    case TK_STRUCT:
    case TK_UNION:
    {
        ASSERT(*ppTypeSpecifier == NULL);
        bResult = true;
        TStructUnionSpecifier* pStructUnionSpecifier = TStructUnionSpecifier_Create();

        *ppTypeSpecifier = (TTypeSpecifier*)pStructUnionSpecifier;
        Struct_Or_Union_Specifier(ctx, pStructUnionSpecifier);
    }
    break;

    case TK_ENUM:
    {
        ASSERT(*ppTypeSpecifier == NULL);
        bResult = true;
        TEnumSpecifier* pEnumSpecifier2 = TEnumSpecifier_Create();
        *ppTypeSpecifier = (TTypeSpecifier*)pEnumSpecifier2;
        Enum_Specifier(ctx, pEnumSpecifier2);
    }
    break;

    case TK_IDENTIFIER:
    {
        int bIsTypedef = DeclarationsMap_IsTypeDef(&ctx->Symbols, lexeme);

        if (bIsTypedef)
        {
            const char* lexeme = Lexeme(ctx);
            String lexemeCopy = STRING_INIT;
            String_Set(&lexemeCopy, lexeme);
            static int expading = 0;
            if (bIsTypedef == 2 && expading == 0)
            {
                //se ainda nao foi instanciada pegar por 
                //bIsTypedef entao criar a declaracao
                //que fica numa lista e depois eh inserida antes
                //da declaracao atual.


                if (IsTemplateType(lexeme))
                {
                    StrBuilder sb = STRBUILDER_INIT;
                    InstantiateTemplateType(lexeme, &sb);
                    //Match(ctx);
                    expading = 1;
                    PushExpandedMacro(&ctx->Scanner,
                        "template",
                        "",
                        sb.c_str);
                    TAnyDeclaration* pDeclaration;
                    bResult = Declaration(ctx,
                        &pDeclaration);
                    expading = 0;
                    ArrayT_Push(&ctx->Templates, pDeclaration);
                    SetSymbolsFromDeclaration(ctx, pDeclaration);
                    StrBuilder_Destroy(&sb);
                }
            }

            lexeme = lexemeCopy;
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

                    
                    Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

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

            String_Destroy(&lexemeCopy);

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
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_CURLY_BRACKET)
    {
        TInitializerListType* pTInitializerList = TInitializerListType_Create();
        *ppInitializer = (TInitializer*)pTInitializerList;

        Parser_Match(ctx, &pTInitializerList->ClueList0);

        Initializer_List(ctx, &pTInitializerList->InitializerList);

        Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
            &pTInitializerList->ClueList1);
    }

    else
    {
        TExpression* pExpression = NULL;
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
        List_Add(pInitializerList, pTInitializerListItem);
        Tokens token = Parser_CurrentToken(ctx);
#ifdef LANGUAGE_EXTENSIONS
        if (token == TK_RIGHT_CURLY_BRACKET)
        {
            //Empty initializer
            break;
        }
#endif
        if (token == TK_LEFT_SQUARE_BRACKET ||
            token == TK_FULL_STOP)
        {
            Designation(ctx, &pTInitializerListItem->DesignatorList);
        }

        Initializer(ctx, &pTInitializerListItem->pInitializer, TK_COMMA, TK_RIGHT_CURLY_BRACKET);
        //push
        token = Parser_CurrentToken(ctx);

        if (token == TK_COMMA)
        {
            //TNodeClueList_MoveToEnd(&pTInitializerListItem->ClueList, &ctx->Scanner.ClueList);
            Parser_Match(ctx, &pTInitializerListItem->ClueList);
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
    Parser_MatchToken(ctx, TK_EQUALS_SIGN, NULL);//tODO
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
    List_Add(pDesignatorList, pDesignator);

    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        Tokens token = Parser_CurrentToken(ctx);

        if (token == TK_LEFT_SQUARE_BRACKET ||
            token == TK_FULL_STOP)
        {
            TDesignator* pDesignatorNew = TDesignator_Create();
            Designator(ctx, pDesignatorNew);
            List_Add(pDesignatorList, pDesignatorNew);
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
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_SQUARE_BRACKET)
    {
        Parser_Match(ctx, &p->ClueList0);

        ConstantExpression(ctx, &p->pExpression);

        Parser_Match(ctx, &p->ClueList1);
        Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, NULL);
    }

    else if (token == TK_FULL_STOP)
    {
        //TNodeClueList_MoveToEnd(&p->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &p->ClueList0);

        String_Set(&p->Name, Lexeme(ctx));
        Parser_MatchToken(ctx, TK_IDENTIFIER, NULL);
    }
}

void Init_Declarator(Parser* ctx,
    TInitDeclarator** ppDeclarator2)
{
    /*
    init-declarator:
    declarator
    declarator = initializer
    */
    TInitDeclarator* pInitDeclarator =
        TInitDeclarator_Create();

    ASSERT(pInitDeclarator->pDeclarator == NULL);
    Declarator(ctx, &pInitDeclarator->pDeclarator);
    Tokens token = Parser_CurrentToken(ctx);

    //Antes do =
    *ppDeclarator2 = pInitDeclarator;

    if (token == TK_EQUALS_SIGN)
    {
        ASSERT(*ppDeclarator2 != NULL);
        
        Parser_Match(ctx, &pInitDeclarator->ClueList0);

        Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);
        ////TNodeClueList_MoveToEnd(&pInitDeclarator->ClueList, &ctx->Scanner.ClueList);
    }
}

void Init_Declarator_List(Parser* ctx,
    TInitDeclaratorList* pInitDeclaratorList)
{
    /*
    init-declarator-list:
    init-declarator
    init-declarator-list , init-declarator
    */

    TInitDeclarator* pInitDeclarator = NULL;
    Init_Declarator(ctx, &pInitDeclarator);
    List_Add(pInitDeclaratorList, pInitDeclarator);

    //Tem mais?
    Tokens token = Parser_CurrentToken(ctx);
    if (token == TK_COMMA)
    {        
        Parser_Match(ctx, &pInitDeclarator->ClueList0);

        Init_Declarator_List(ctx, pInitDeclaratorList);
    }

}

void TemplateParameter(Parser* ctx,
    TTemplateParameter** ppTemplateParameter)
{
    *ppTemplateParameter = NULL;
    /*
    template-parameter:
     type-parameter
     parameter-declaration
    */
    Tokens token = Parser_CurrentToken(ctx);
    if (token == TK_CLASS)
    {
        Parser_MatchToken(ctx, TK_CLASS, NULL);
        TTemplateParameter *p = TTemplateParameter_Create();
        String_Set(&p->Name, Lexeme(ctx));
        Parser_MatchToken(ctx, TK_IDENTIFIER, NULL);
        *ppTemplateParameter = p;
    }
    else
    {
        SetError2(ctx, "e", "e");
    }
}

void TemplateParameterList(Parser* ctx, TTemplateParameterList* list)
{
    /*
    template-parameter-list:
    template-parameter
    template-parameter-list , template-parameter
    */
    TTemplateParameter *pTemplateParameter = NULL;

    TemplateParameter(ctx,
        &pTemplateParameter);

    List_Add(list, pTemplateParameter);

    Tokens token = Parser_CurrentToken(ctx);
    if (token == TK_COMMA)
    {
        Parser_Match(ctx, NULL);
        TemplateParameterList(ctx, list);
    }
}

void TemplateDeclaration(Parser* ctx, TDeclaration* pFuncVarDeclaration)
{
    /*
    template-declaration:
    template < template-parameter-list > declaration
    */

    //template
    Parser_MatchToken(ctx, TK_TEMPLATE, NULL);
    Parser_MatchToken(ctx, TK_LESS_THAN_SIGN, NULL);
    TemplateParameterList(ctx, &pFuncVarDeclaration->TemplateParameters);
    Parser_MatchToken(ctx, TK_GREATER_THAN_SIGN, NULL);
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
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK__STATIC_ASSERT)
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

            if (token == TK_TEMPLATE)
            {
                //Tem que ter um escopo de tipos aqui
                //que � passado.
                //talvez uma map de tipos que seja uma pilha
                bHasDeclaration = true;
                TemplateDeclaration(ctx, pFuncVarDeclaration);
            }


            if (Declaration_Specifiers(ctx, &pFuncVarDeclaration->Specifiers))
            {
                bHasDeclaration = true;
            }
        }



        if (bHasDeclaration)
        {
            *ppDeclaration = (TAnyDeclaration*)pFuncVarDeclaration;
            pFuncVarDeclaration->FileIndex = GetFileIndex(ctx);
            pFuncVarDeclaration->Line = GetCurrentLine(ctx);
            //ASSERT(pFuncVarDeclaration->FileIndex >= 0);

            token = Parser_CurrentToken(ctx);

            if (token == TK_SEMICOLON)
            {
                Parser_Match(ctx, &pFuncVarDeclaration->ClueList0);
            }

            else
            {
                //Agora vem os declaradores que possuem os ponteiros
                Init_Declarator_List(ctx, &pFuncVarDeclaration->InitDeclaratorList);
                token = Parser_CurrentToken(ctx);

                if (token == TK_LEFT_CURLY_BRACKET)
                {
                    TStatement* pStatement;
                    Compound_Statement(ctx, &pStatement);
                    //TODO cast
                    pFuncVarDeclaration->pCompoundStatementOpt = (TCompoundStatement*)pStatement;
                }

                else
                {
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pFuncVarDeclaration->ClueList0);
                }
            }

            // StrBuilder_Swap(&pFuncVarDeclaration->PreprocessorAndCommentsString,
              // &ctx->Scanner.PreprocessorAndCommentsString);


        }
        else
        {
            TDeclaration_Delete(pFuncVarDeclaration);
        }
    }

    return bHasDeclaration;
}

void SetSymbolsFromDeclaration(Parser* ctx,
    TAnyDeclaration* pDeclaration2)
{
    if (Parser_HasError(ctx))
    {
        return;
    }
    //Extrai as declaracoes de tipos variaveis e funcoes da declaracao
    if (pDeclaration2->type == TDeclaration_ID)
    {
        TDeclaration* pTFuncVarDeclaration = (TDeclaration*)pDeclaration2;
        //if (pTFuncVarDeclaration->Specifiers.StorageSpecifiers.bIsTypedef)
        {
            ForEachListItem(TInitDeclarator, pDeclarator, &pTFuncVarDeclaration->InitDeclaratorList)
            {
                //        TDeclarator* pDeclarator = pTFuncVarDeclaration->Declarators.pItems[i];
                const char* declaratorName = TInitDeclarator_FindName(pDeclarator);

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
            for (int i = 0; i < ctx->Templates.size; i++)
            {
                ArrayT_Push(declarations, ctx->Templates.pItems[i]);
                declarationIndex++;
            }
            ctx->Templates.size = 0;

            //TDeclarations_Destroy(&ctx->Templates);
            //TDeclarations_Init(&ctx->Templates);

            //printf("%s", ctx->Scanner.PreprocessorAndCommentsString);
           // StrBuilder_Clear(&ctx->Scanner.PreprocessorAndCommentsString);

            //Cada Declaration poderia ter out uma lista TDeclarations
            //publica que vai ser inserida aqui.
            //
            ArrayT_Push(declarations, pDeclarationOut);
            declarationIndex++;
            SetSymbolsFromDeclaration(ctx, pDeclarationOut);
        }
        else
        {
            if (Parser_CurrentToken(ctx) == TK_EOF)
            {
                //ok
            }
            else
            {
                //nao ter mais declaracao nao eh erro
                SetError2(ctx, "declaration expected", "");
            }
            break;
        }

        if (Parser_HasError(ctx))
            break;

    }

    for (int i = 0; i < ctx->TemplatesInstances.size; i++)
    {
        ArrayT_Push(declarations, ctx->TemplatesInstances.pItems[i]);
        declarationIndex++;
        //SetSymbolsFromDeclaration(ctx, ctx->Templates.pItems[i]);
    }
    ctx->TemplatesInstances.size = 0;

}

void Parser_Main(Parser* ctx, TDeclarations* declarations)
{
    Parse_Declarations(ctx, declarations);
}

static void TFileMapToStrArray(TFileMap* map, TFileArray* arr)
{
    ArrayT_Reserve(arr, map->Size);
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
    const char* configFileName /*optional*/,
    bool bAmalgamationMode,
    TProgram* pProgram)
{
    bool bResult = false;


    Parser parser;

    if (configFileName != NULL)
    {
        //opcional   
        String fullConfigFilePath = STRING_INIT;
        GetFullPath(configFileName, &fullConfigFilePath);

        Parser_InitFile(&parser, fullConfigFilePath);
        Parser_Main(&parser, &pProgram->Declarations);

        //Some com o arquivo de config
        List_Clear(ScannerItem, &parser.ClueList);
        BasicScannerStack_Pop(&parser.Scanner.stack);
        //Some com o arquivo de config
        String_Destroy(&fullConfigFilePath);
    }

    String fullFileNamePath = STRING_INIT;
    GetFullPath(filename, &fullFileNamePath);

    //parser.scanner.bPrintIncludes = true;
    if (filename != NULL)
    {
        if (configFileName == NULL)
        {
            Parser_InitFile(&parser, fullFileNamePath);
        }
        else
        {
            Parser_PushFile(&parser, fullFileNamePath);
        }
        Parser_Main(&parser, &pProgram->Declarations);
    }

    TFileMapToStrArray(&parser.Scanner.FilesIncluded, &pProgram->Files2);
    printf("%s\n", GetCompletationMessage(&parser));
    MultiMap_Swap(&parser.Symbols, &pProgram->Symbols);

    MacroMap_Swap(&parser.Scanner.Defines2, &pProgram->Defines);
    Map_Swap(&parser.EnumMap, &pProgram->EnumMap);


    bResult = !parser.bError;

    Parser_Destroy(&parser);
    String_Destroy(&fullFileNamePath);

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
    while (Scanner_CurrentToken(scanner) != TK_EOF)
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

    while (Scanner_CurrentToken(&scanner) != TK_EOF)
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

    while (Scanner_CurrentToken(&scanner) != TK_EOF)
    {
        Tokens token = Scanner_CurrentToken(&scanner);
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

    while (Scanner_CurrentToken(&scanner) != TK_EOF)
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


