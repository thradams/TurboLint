#include "CodePrint.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Base\Path.h"



static bool TInitializerList_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, bool bIsPointer, TInitializerList*p, bool b, StrBuilder* fp);
//static bool TInitializerListType_CodePrint(TTypeSpecifier* pTypeSpecifier, bool b, StrBuilder* fp);
static bool TDeclarator_CodePrint(TProgram* program, TDeclarator* p, bool b, StrBuilder* fp);
static bool TAnyDeclaration_CodePrint(TProgram* program, TAnyDeclaration *pDeclaration, bool b, StrBuilder* fp);
static bool TTypeSpecifier_CodePrint(TProgram* program, TTypeSpecifier* p, bool b, StrBuilder* fp);
static bool TAnyStructDeclaration_CodePrint(TProgram* program, TAnyStructDeclaration* p, bool b, StrBuilder* fp);
static bool TTypeQualifier_CodePrint(TProgram* program, TTypeQualifier* p, bool b, StrBuilder* fp);
static bool TDeclaration_CodePrint(TProgram* program, TDeclaration* p, bool b, StrBuilder* fp);
static bool TExpression_CodePrint(TProgram* program, TExpression * p, const char* name, bool b, StrBuilder* fp);
static bool TStatement_CodePrint(TProgram* program, TStatement * p, bool b, StrBuilder* fp);
static bool TBlockItem_CodePrint(TProgram* program, TBlockItem * p, bool b, StrBuilder* fp);
static bool TInitializer_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, bool bIsPointer, TInitializer* p, bool b, StrBuilder* fp);
static bool TPointer_CodePrint(TProgram* program, TPointer* pPointer, bool b, StrBuilder* fp);
static bool TParameterDeclaration_CodePrint(TProgram* program, TParameterDeclaration* p, bool b, StrBuilder* fp);
static bool TInitializerListItem_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, bool bIsPointer, TInitializerListItem* p, bool b, StrBuilder* fp);

static bool bInclude = true;
static int IncludeLevel = 0;

void Output_Append(StrBuilder* p,
    const char* source)
{
    if (bInclude && IncludeLevel == 0)
        StrBuilder_Append(p, source);
}

static void TNodeClueList_CodePrint(TScannerItemList* list,
    StrBuilder* fp, int pos)
{
    ForEachListItem(ScannerItem, pNodeClue, list)
    {
        // if (pNodeClue->Position != pos)
          // continue;

        switch (pNodeClue->token)
        {
        case TK_PRE_INCLUDE:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            Output_Append(fp, "\n");
            IncludeLevel++;
            break;

        case TK_FILE_EOF:
            IncludeLevel--;
            //bInclude = true;
            break;
        case TK_PRE_DEFINE:
        case TK_PRE_UNDEF:
        case TK_PRE_PRAGMA:
        case TK_PRE_IF:
        case TK_PRE_ENDIF:
        case TK_PRE_ELSE:

            Output_Append(fp, pNodeClue->lexeme.c_str);
            Output_Append(fp, "\n");
            break;

        case TK_COMMENT:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            break;

        case TK_LINE_COMMENT:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            break;

        case TK_BREAKLINE:
            Output_Append(fp, "\n");

            break;

        case TK_MACRO_CALL:

            //Output_Append(fp, "/*");
            Output_Append(fp, pNodeClue->lexeme.c_str);
            //Output_Append(fp, "*/");
            bInclude = false;
            break;


        case TK_MACRO_EOF:
            bInclude = true;
            break;

        case TK_SPACES:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            break;

            //case NodeClueTypeNone:      
        default:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            break;
        }

    }
}

//static bool TInitializer_CodePrint(TInitializer*  p, bool b, StrBuilder* fp);

void BuildEnumSpecifierInitialization(TProgram* program,
    TEnumSpecifier* pTEnumSpecifier,
    StrBuilder* strBuilder)
{
    Output_Append(strBuilder, "0");
}


void BuildInitialization(TProgram* program,
    TTypeSpecifier* pTypeSpecifier, bool bIsPointer,
    StrBuilder* strBuilder);

void BuildSingleTypeSpecifierInitialization(TProgram* program,
    TSingleTypeSpecifier* pSingleTypeSpecifier,
    bool bIsPointer,
    StrBuilder* strBuilder)
{
    if (pSingleTypeSpecifier->bIsTypeDef)
    {
        TDeclaration * p = TProgram_GetFinalTypeDeclaration(program, pSingleTypeSpecifier->TypedefName);
        if (p)
        {
            //Tem que ver se o typedef nao era ponteiro tb
            TDeclarator* pDeclarator = TDeclaration_FindDeclarator(p, pSingleTypeSpecifier->TypedefName);
            if (pDeclarator)
            {
                BuildInitialization(program, p->Specifiers.pTypeSpecifierOpt,
                    bIsPointer || TPointerList_IsPointer(&pDeclarator->PointerList),
                    strBuilder);
            }
            else
            {
                ASSERT(false);
            }

        }
    }
    else
    {
        if (pSingleTypeSpecifier->bIsBool)
            Output_Append(strBuilder, "false");
        else if (pSingleTypeSpecifier->bIsDouble)
            Output_Append(strBuilder, "0.0");
        else
            Output_Append(strBuilder, "0");
    }
}


void BuildStructUnionSpecifierInitialization(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    StrBuilder* strBuilder)
{
    Output_Append(strBuilder, "{");
    int k = 0;
    for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.size; i++)
    {
        TAnyStructDeclaration* p =
            pStructUnionSpecifier->StructDeclarationList.pItems[i];
        TStructDeclaration* pStructDeclaration =
            TAnyStructDeclaration_As_TStructDeclaration(p);

        if (pStructDeclaration)
        {
            if (k > 0)
            {
                Output_Append(strBuilder, ",");
            }

            ForEachListItem(TInitDeclarator, pDeclarator, &pStructDeclaration->DeclaratorList)
            {
                if (pDeclarator->pInitializer)
                {
                    TInitializer_CodePrint(program, pStructDeclaration->pSpecifier,
                        &pStructDeclaration->Qualifier,
                        pDeclarator->pInitializer, false, strBuilder);
                }
                else
                {
                    BuildInitialization(program,
                        pStructDeclaration->pSpecifier,
                        TPointerList_IsPointer(&pDeclarator->pDeclarator->PointerList),
                        strBuilder);
                }
                k++;
            }
        }
    }
    Output_Append(strBuilder, "}");
}

void BuildInitialization(TProgram* program,
    TTypeSpecifier* pTypeSpecifier,
    bool bIsPointer,
    StrBuilder* strBuilder)
{
    if (bIsPointer)
    {
        Output_Append(strBuilder, "NULL");
    }
    else
    {
        switch (pTypeSpecifier->type)
        {
        case TSingleTypeSpecifier_ID:
            BuildSingleTypeSpecifierInitialization(program, (TSingleTypeSpecifier*)pTypeSpecifier, bIsPointer, strBuilder);
            break;
        case TEnumSpecifier_ID:
            BuildEnumSpecifierInitialization(program, (TEnumSpecifier*)pTypeSpecifier, strBuilder);
            break;
        case TStructUnionSpecifier_ID:
            BuildStructUnionSpecifierInitialization(program, (TStructUnionSpecifier*)pTypeSpecifier, strBuilder);
            break;
        default:
            ASSERT(false);
            break;
        }
    }
}

static bool TCompoundStatement_CodePrint(TProgram* program, TCompoundStatement * p, bool b, StrBuilder* fp)
{

    //
    b = true;

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 0);
    Output_Append(fp, "{");

    for (size_t j = 0; j < p->BlockItemList.size; j++)
    {
        TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_CodePrint(program, pBlockItem, j > 0, fp);
    }

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 1);
    Output_Append(fp, "}");
    return b;
}


static bool TLabeledStatement_CodePrint(TProgram* program, TLabeledStatement * p, bool b, StrBuilder* fp)
{
    b = true;

    if (p->token == TK_CASE)
    {
        Output_Append(fp, "case ");
        if (p->pStatementOpt)
        {
            b = TExpression_CodePrint(program, p->pExpression, "", false, fp);
        }
        Output_Append(fp, ":");
        b = TStatement_CodePrint(program, p->pStatementOpt, false, fp);
    }
    else if (p->token == TK_DEFAULT)
    {
        Output_Append(fp, "default:");
        b = TStatement_CodePrint(program, p->pStatementOpt, false, fp);
    }
    else if (p->token == TK_IDENTIFIER)
    {
        Output_Append(fp, p->Identifier);
        Output_Append(fp, ":");
    }


    return b;
}

static bool TForStatement_CodePrint(TProgram* program, TForStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    Output_Append(fp, "for (");
    if (p->pInitDeclarationOpt) {
        TAnyDeclaration_CodePrint(program, p->pInitDeclarationOpt, b, fp);
        if (p->pExpression2)
        {
            b = TExpression_CodePrint(program, p->pExpression2, "expr2", true, fp);
        }
        Output_Append(fp, ";");
        b = TExpression_CodePrint(program, p->pExpression3, "expr3", b, fp);
    }
    else
    {
        b = TExpression_CodePrint(program, p->pExpression1, "expr1", true, fp);
        Output_Append(fp, ";");
        b = TExpression_CodePrint(program, p->pExpression2, "expr2", b, fp);
        Output_Append(fp, ";");
        b = TExpression_CodePrint(program, p->pExpression3, "expr3", b, fp);
    }


    Output_Append(fp, ")");

    b = TStatement_CodePrint(program, p->pStatement, false, fp);

    return b;
}


static bool TWhileStatement_CodePrint(TProgram* program, TWhileStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    Output_Append(fp, "while (");
    b = TExpression_CodePrint(program, p->pExpression, "expr", false, fp);
    Output_Append(fp, ")");
    b = TStatement_CodePrint(program, p->pStatement, false, fp);
    return b;
}


static bool TReturnStatement_CodePrint(TProgram* program, TReturnStatement * p, bool b, StrBuilder* fp)
{
    Output_Append(fp, "return ");
    TExpression_CodePrint(program, p->pExpression, "return-statement", false, fp);
    Output_Append(fp, ";");
    return true;
}

static bool TDoStatement_CodePrint(TProgram* program, TDoStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    Output_Append(fp, "do {");
    b = TStatement_CodePrint(program, p->pStatement, false, fp);
    Output_Append(fp, "} while (");
    b = TExpression_CodePrint(program, p->pExpression, "expr", false, fp);
    Output_Append(fp, ")");

    return b;
}


static bool TExpressionStatement_CodePrint(TProgram* program, TExpressionStatement * p, bool b, StrBuilder* fp)
{
    TExpression_CodePrint(program, p->pExpression, "", b, fp);

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 0);
    Output_Append(fp, ";");

    return true;
}


static bool TJumpStatement_CodePrint(TProgram* program, TJumpStatement * p, bool b, StrBuilder* fp)
{


    Output_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
    if (p->pExpression)
    {

        b = TExpression_CodePrint(program, p->pExpression, "statement", false, fp);
    }

    if (p->token == TK_BREAK)
    {
        Output_Append(fp, ";");
    }
    else
    {
        Output_Append(fp, ";");
    }

    return true;
}

static bool TAsmStatement_CodePrint(TProgram* program, TAsmStatement * p, bool b, StrBuilder* fp)
{
    Output_Append(fp, "\"type\":\"asm-statement\"");
    return true;
}

static bool TSwitchStatement_CodePrint(TProgram* program, TSwitchStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    Output_Append(fp, "switch (");
    b = TExpression_CodePrint(program, p->pConditionExpression, "expr", false, fp);
    Output_Append(fp, ")");
    b = TStatement_CodePrint(program, p->pExpression, false, fp);
    return b;
}


static bool TIfStatement_CodePrint(TProgram* program, TIfStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    Output_Append(fp, "if (");


    b = TExpression_CodePrint(program, p->pConditionExpression, "expr", false, fp);
    Output_Append(fp, ")");

    if (p->pStatement->type != TCompoundStatement_ID)
        Output_Append(fp, "");

    if (p->pStatement)
    {
        b = TStatement_CodePrint(program, p->pStatement, false, fp);
    }

    if (p->pElseStatement)
    {
        Output_Append(fp, "else");
        b = TStatement_CodePrint(program, p->pElseStatement, false, fp);
    }

    return b;
}

static bool TStatement_CodePrint(TProgram* program, TStatement *  p, bool b, StrBuilder* fp)
{
    if (p == NULL)
    {
        return false;
    }

    switch (p->type)
    {
    case TExpressionStatement_ID:
        b = TExpressionStatement_CodePrint(program, (TExpressionStatement*)p, b, fp);
        break;

    case TSwitchStatement_ID:
        b = TSwitchStatement_CodePrint(program, (TSwitchStatement*)p, b, fp);
        break;

    case TLabeledStatement_ID:
        b = TLabeledStatement_CodePrint(program, (TLabeledStatement*)p, b, fp);
        break;

    case TForStatement_ID:
        b = TForStatement_CodePrint(program, (TForStatement*)p, b, fp);
        break;

    case TJumpStatement_ID:
        b = TJumpStatement_CodePrint(program, (TJumpStatement*)p, b, fp);
        break;

    case TAsmStatement_ID:
        b = TAsmStatement_CodePrint(program, (TAsmStatement*)p, b, fp);
        break;

    case TCompoundStatement_ID:
        b = TCompoundStatement_CodePrint(program, (TCompoundStatement*)p, b, fp);
        break;

    case TIfStatement_ID:
        b = TIfStatement_CodePrint(program, (TIfStatement*)p, b, fp);
        break;

    case TDoStatement_ID:
        TDoStatement_CodePrint(program, (TDoStatement*)p, b, fp);
        break;

    case TReturnStatement_ID:
        TReturnStatement_CodePrint(program, (TReturnStatement*)p, b, fp);
        break;

    default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool TBlockItem_CodePrint(TProgram* program, TBlockItem *  p, bool b, StrBuilder* fp)
{
    if (p == NULL)
    {
        ASSERT(false);
        return false;
    }


    switch (p->type)
    {
    case TStaticAssertDeclaration_ID:
        break;

    case TSwitchStatement_ID:

        b = TSwitchStatement_CodePrint(program, (TSwitchStatement*)p, false, fp);

        break;

    case TJumpStatement_ID:

        b = TJumpStatement_CodePrint(program, (TJumpStatement*)p, false, fp);

        break;

    case TForStatement_ID:

        b = TForStatement_CodePrint(program, (TForStatement*)p, false, fp);

        break;

    case TIfStatement_ID:

        b = TIfStatement_CodePrint(program, (TIfStatement*)p, false, fp);

        break;

    case TWhileStatement_ID:

        b = TWhileStatement_CodePrint(program, (TWhileStatement*)p, b, fp);

        break;

    case TDoStatement_ID:

        b = TDoStatement_CodePrint(program, (TDoStatement*)p, false, fp);

        break;

    case TDeclaration_ID:
        b = TDeclaration_CodePrint(program, (TDeclaration*)p, false, fp);
        //Output_Append(fp, "\n");
        break;

    case TLabeledStatement_ID:

        b = TLabeledStatement_CodePrint(program, (TLabeledStatement*)p, false, fp);

        break;

    case TCompoundStatement_ID:
        b = TCompoundStatement_CodePrint(program, (TCompoundStatement*)p, false, fp);
        break;

    case TExpressionStatement_ID:

        b = TExpressionStatement_CodePrint(program, (TExpressionStatement*)p, false, fp);

        break;

    case TReturnStatement_ID:

        b = TReturnStatement_CodePrint(program, (TReturnStatement*)p, false, fp);

        break;

    case TAsmStatement_ID:

        b = TAsmStatement_CodePrint(program, (TAsmStatement*)p, false, fp);

        break;

    default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool TPostfixExpressionCore_CodePrint(TProgram* program, TPostfixExpressionCore * p, bool b, StrBuilder* fp)
{

    b = false;

    if (p->pExpressionLeft)
    {
        b = TExpression_CodePrint(program, p->pExpressionLeft, "l", b, fp);
    }


    {
        bool bIsPointer = false;
        TTypeSpecifier* pTypeSpecifier = NULL;
        if (p->pTypeName)
        {

            Output_Append(fp, "(");
            TParameterDeclaration_CodePrint(program, p->pTypeName, b, fp);
            Output_Append(fp, ")");

            pTypeSpecifier = p->pTypeName->Specifiers.pTypeSpecifierOpt;
            bIsPointer = TPointerList_IsPointer(&p->pTypeName->Declarator.PointerList);

            //falta imprimeir typename
            //TTypeName_Print*
            b = TInitializerList_CodePrint(program, pTypeSpecifier,
                bIsPointer,
                &p->InitializerList, b, fp);
        }

    }

    switch (p->token)
    {
    case TK_FULL_STOP:
        Output_Append(fp, ".");
        Output_Append(fp, p->Identifier);
        b = true;
        break;
    case TK_ARROW:
        Output_Append(fp, "->");
        Output_Append(fp, p->Identifier);
        b = true;
        break;

    case TK_LEFT_SQUARE_BRACKET:
        Output_Append(fp, "[");
        b = TExpression_CodePrint(program, p->pExpressionRight, "r", b, fp);
        Output_Append(fp, "]");
        break;

    case TK_LEFT_PARENTHESIS:
        Output_Append(fp, "(");
        b = TExpression_CodePrint(program, p->pExpressionRight, "r", b, fp);
        Output_Append(fp, ")");
        break;

    case TK_PLUSPLUS:
        Output_Append(fp, "++");
        b = true;
        break;
    case TK_MINUSMINUS:
        Output_Append(fp, "--");
        b = true;
        break;
        break;
    }


    b = true;
    if (p->pNext)
    {
        b = TPostfixExpressionCore_CodePrint(program, p->pNext, false, fp);
    }

    b = true;
    return b;
}

static bool TExpression_CodePrint(TProgram* program, TExpression *  p,
    const char* name,
    bool b,
    StrBuilder* fp)
{
    if (p == NULL)
    {
        //ASSERT(false);
        return b;
    }

    b = false;

    switch (p->type)
    {
        CASE(TBinaryExpression) :
            b = TExpression_CodePrint(program, ((TBinaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
        Output_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
        b = TExpression_CodePrint(program, ((TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
        break;

        CASE(TTernaryExpression) :
            b = TExpression_CodePrint(program, ((TTernaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
        Output_Append(fp, " ? ");
        b = TExpression_CodePrint(program, ((TTernaryExpression*)p)->pExpressionMiddle, "m-expr", b, fp);
        Output_Append(fp, " : ");
        b = TExpression_CodePrint(program, ((TTernaryExpression*)p)->pExpressionRight, "r-expr", b, fp);

        break;

        CASE(TPrimaryExpressionValue) :
        {
            TPrimaryExpressionValue* pPrimaryExpressionValue =
                (TPrimaryExpressionValue*)p;


            TNodeClueList_CodePrint(&pPrimaryExpressionValue->NodeClueList, fp, 0);

            if (pPrimaryExpressionValue->pExpressionOpt != NULL)
            {
                Output_Append(fp, "(");
                b = TExpression_CodePrint(program, pPrimaryExpressionValue->pExpressionOpt, "expr", b, fp);
                Output_Append(fp, ")");
            }
            else
            {
                Output_Append(fp, pPrimaryExpressionValue->lexeme);
            }
        }
        b = true;

        break;

        CASE(TPostfixExpressionCore) :
        {
            TPostfixExpressionCore* pPostfixExpressionCore =
                (TPostfixExpressionCore*)p;
            b = TPostfixExpressionCore_CodePrint(program, pPostfixExpressionCore, b, fp);
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {
            TUnaryExpressionOperator* pTUnaryExpressionOperator =
                (TUnaryExpressionOperator*)p;

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {

                if (pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt != NULL)
                {
                    Output_Append(fp, "sizeof (");
                    b = TTypeQualifier_CodePrint(program, &pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
                    b = TTypeSpecifier_CodePrint(program, pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
                    b = TDeclarator_CodePrint(program, &pTUnaryExpressionOperator->TypeName.Declarator, b, fp);
                    Output_Append(fp, ")");

                }
                else
                {
                    Output_Append(fp, "sizeof ");
                    b = TExpression_CodePrint(program, pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);
                    Output_Append(fp, "");
                }
            }
            else
            {
                Output_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
                b = TExpression_CodePrint(program, pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);

            }


        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType*)p;

            Output_Append(fp, "(");
            b = TTypeQualifier_CodePrint(program, &pCastExpressionType->TypeName.Specifiers.TypeQualifiers, false, fp);
            b = TTypeSpecifier_CodePrint(program, pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
            b = TDeclarator_CodePrint(program, &pCastExpressionType->TypeName.Declarator, b, fp);
            Output_Append(fp, ")");
            b = TExpression_CodePrint(program, pCastExpressionType->pExpression, "expr", b, fp);
        }
        break;

    default:

        ASSERT(false);
    }


    return b;
}



static   bool TEnumerator_CodePrint(TProgram* program, TEnumerator* pTEnumerator, bool b, StrBuilder* fp)
{

    TNodeClueList_CodePrint(&pTEnumerator->NodeClueList, fp, 0);
    Output_Append(fp, pTEnumerator->Name);

    if (pTEnumerator->pExpression)
    {
        TNodeClueList_CodePrint(&pTEnumerator->NodeClueList, fp, 1);
        Output_Append(fp, " = ");

        TExpression_CodePrint(program, pTEnumerator->pExpression, "expr", true, fp);

        TNodeClueList_CodePrint(&pTEnumerator->NodeClueList, fp, 2);
        //int r;
        //EvaluateConstantExpression(pTEnumerator->pExpression,  &r);

    }
    else
    {
        //vou criar uma expressionp enum?
    }

    return true;
}

static bool TEnumSpecifier_CodePrint(TProgram* program, TEnumSpecifier* p, bool b, StrBuilder* fp)
{
    b = true;

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 0);
    Output_Append(fp, " enum ");

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 1);
    Output_Append(fp, p->Name);

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 2);
    Output_Append(fp, "{");
    //TNodeClueList_CodePrint(&p->NodeClueList, fp, 3);

    ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
    {

        TEnumerator_CodePrint(program, pTEnumerator, false, fp);

        if (List_IsLastItem(&p->EnumeratorList, pTEnumerator))
        {
            //Output_Append(fp, "\n");
        }
        else
        {
            //tem mais
            Output_Append(fp, ",");
        }
    }

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 3);
    Output_Append(fp, "}");
    return true;
}


static bool TStructUnionSpecifier_CodePrint(TProgram* program, TStructUnionSpecifier* p, bool b, StrBuilder* fp)
{
    TNodeClueList_CodePrint(&p->NodeClueList, fp, 0);

    b = true;

    if (p->bIsStruct)
        Output_Append(fp, " struct ");

    else
        Output_Append(fp, " union ");

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 1);
    Output_Append(fp, p->Name);

    if (p->StructDeclarationList.size > 0)
    {
        TNodeClueList_CodePrint(&p->NodeClueList, fp, 2);

        Output_Append(fp, " {");
        TNodeClueList_CodePrint(&p->NodeClueList, fp, 3);


        for (size_t i = 0; i < p->StructDeclarationList.size; i++)
        {
            TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
            b = TAnyStructDeclaration_CodePrint(program, pStructDeclaration, b, fp);
            Output_Append(fp, ";");
        }

        TNodeClueList_CodePrint(&p->NodeClueList, fp, 4);

        //TNodeClueList_CodePrint(&p->NodeClueList, fp, 4);

        Output_Append(fp, "}");
    }
    /* Output_Append(fp, "typedef struct ");
     Output_Append(fp, p->Name);
     Output_Append(fp, " ");
     Output_Append(fp, p->Name);
     Output_Append(fp, ";\n");

     Output_Append(fp, "#define ");
     Output_Append(fp, p->Name);
     Output_Append(fp, "_INIT ");

     Output_Append(fp, "\n");
     */

    return true;
}

static bool TSingleTypeSpecifier_CodePrint(TProgram* program, TSingleTypeSpecifier* p, bool b, StrBuilder* fp)
{

    TNodeClueList_CodePrint(&p->NodeClueList, fp, 0);


    b = true;

    int i = 0;

    if (p->bIsVoid)
    {
        Output_Append(fp, " void");
        b = true;
    }

    if (p->bIsUnsigned)
    {
        Output_Append(fp, " unsigned");
        b = true;
    }

    if (p->bIsBool)
    {
        //Output_Append(fp, " _Bool");
        Output_Append(fp, " bool");
        b = true;
    }

    if (p->bIsChar)
    {
        Output_Append(fp, " char");
        b = true;
    }

    if (p->bIsShort)
    {
        Output_Append(fp, " short");
        b = true;
    }

    for (int j = 0; j < p->nLong; j++)
    {
        Output_Append(fp, " long");
        b = true;
    }

    if (p->bIsInt)
    {
        Output_Append(fp, " int");
        b = true;
    }

    if (p->bIsDouble)
    {
        Output_Append(fp, " double");
        b = true;
    }

    if (p->bIsFloat)
    {
        Output_Append(fp, " float");
        b = true;
    }

    if (p->bIsTypeDef)
    {
        Output_Append(fp, " ");
        Output_Append(fp, p->TypedefName);
        b = true;
    }


    return b;
}

static bool TTypeSpecifier_CodePrint(TProgram* program, TTypeSpecifier*  p, bool b, StrBuilder* fp)
{
    if (p == NULL)
    {
        //declaracao vazia: ;
        return true;
    }

    switch (p->type)
    {
    case TStructUnionSpecifier_ID:
        //TAnyStructDeclaration_CodePrint();
        b = TStructUnionSpecifier_CodePrint(program, (TStructUnionSpecifier*)p, b, fp);
        break;

    case TEnumSpecifier_ID:
        b = TEnumSpecifier_CodePrint(program, (TEnumSpecifier*)p, b, fp);
        break;

    case TSingleTypeSpecifier_ID:
        b = TSingleTypeSpecifier_CodePrint(program, (TSingleTypeSpecifier*)p, b, fp);
        break;

    default:
        break;
    }

    return b;
}

static bool TDesignator_CodePrint(TProgram* program, TDesignator* p, bool b, StrBuilder* fp)
{
    if (b)
        Output_Append(fp, ",");

    Output_Append(fp, "{");

    //
    if (p->Name)
    {
        //.identifier
        Output_Append(fp, ".");
        Output_Append(fp, p->Name);
    }

    else
    {
        //[constant-expression]
        TExpression_CodePrint(program, p->pExpression, "index", b, fp);
    }

    Output_Append(fp, "}");
    return b;
}


static bool TInitializerList_CodePrint(TProgram* program,
    TTypeSpecifier* pTypeSpecifier,
    bool bIsPointer,
    TInitializerList*p,
    bool b, StrBuilder* fp)
{
    

    b = false;

    if (List_HasOneItem(p) &&
        List_Back(p)->pInitializer == NULL &&
        pTypeSpecifier != NULL)
    {
        //a partir de {} e um tipo consegue gerar o final
        BuildInitialization(program, pTypeSpecifier, bIsPointer, fp);
    }
    else
    {
        //TNodeClueList_CodePrint(&p->NodeClueList, fp, 0);
        
        //Output_Append(fp, "{");

        ForEachListItem(TInitializerListItem, pItem, p)
        {
            if (!List_IsFirstItem(p, pItem))
                Output_Append(fp, ",");

            b = TInitializerListItem_CodePrint(program, pTypeSpecifier, bIsPointer, pItem, b, fp);
        }

        //Output_Append(fp, "}");
    }


    return true;
}

static bool TInitializerListType_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, bool bIsPointer, TInitializerListType*p, bool b, StrBuilder* fp)
{

    TNodeClueList_CodePrint(&p->NodeClueList1, fp, 0);
    Output_Append(fp, "{");
    b = TInitializerList_CodePrint(program, pTypeSpecifier,
        bIsPointer,
        &p->InitializerList, b, fp);
    Output_Append(fp, "}");
    TNodeClueList_CodePrint(&p->NodeClueList2, fp, 0);

    return true;
}

static bool TInitializer_CodePrint(TProgram* program,
    TTypeSpecifier*  pTTypeSpecifier,
    bool bIsPointer,
    TInitializer*  p,
    bool b,
    StrBuilder* fp)
{
    if (p == NULL)
    {
        return false;
    }
    if (p->type == TInitializerListType_ID)
    {
        b = TInitializerListType_CodePrint(program,
            pTTypeSpecifier,
            bIsPointer,
            (TInitializerListType*)p, b, fp);
    }
    else
    {
        b = TExpression_CodePrint(program, (TExpression*)p, "", false, fp);
    }

    return b;
}



static bool TPointerList_CodePrint(TProgram* program, TPointerList *p, bool b, StrBuilder* fp)
{
    b = false;

    ForEachListItem(TPointer, pItem, p)
    {
        b = TPointer_CodePrint(program, pItem, b, fp);
    }

    return true;
}



static bool TParameterList_CodePrint(TProgram* program, TParameterList *p, bool b, StrBuilder* fp)
{
    b = false;
    Output_Append(fp, "(");

    ForEachListItem(TParameterDeclaration, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            Output_Append(fp, ",");

        //TParameterDeclaration * pItem = p->pItems[i];
        b = TParameterDeclaration_CodePrint(program, pItem, b, fp);
    }

    Output_Append(fp, ")");
    return true;
}

static bool TDeclarator_PrintCore(TProgram* program,
    TDeclarator* p,
    bool b,
    StrBuilder * fp)
{
    /*if (p->token == TK_LEFT_PARENTHESIS &&
      p->pParametersOpt == NULL)
    {
      // ( declarator )
      Output_Append(fp, "(");
    }

    if (p->PointerList.size > 0)
    {
      b = TPointerList_CodePrint(&p->PointerList, b, fp);
    }

    b = TTypeQualifier_CodePrint(&p->Qualifiers, b, fp);

    if (p->pDeclaratorOpt)
    {
      StrBuilder local = STRBUILDER_INIT;
      TDeclarator_PrintCore(p->pDeclaratorOpt, b, &local);
      Output_Append(fp, local.c_str);
      StrBuilder_Destroy(&local);
    }
    else
    {
      if (p->Name != NULL)
      {
        Output_Append(fp, " ");
        Output_Append(fp, p->Name);
      }
    }

    if (p->token == TK_LEFT_PARENTHESIS &&
      p->pParametersOpt == NULL)
    {
      // ( declarator )
      Output_Append(fp, ")");
    }

    if (p->pParametersOpt != NULL)
    {
      b = TParameterList_CodePrint(p->pParametersOpt, b, fp);
    }

    if (p->token == TK_LEFT_SQUARE_BRACKET)
    {
      //tem que revisar..isso fica no p->pDeclaratorOpt
      Output_Append(fp, "[");
      b = TExpression_CodePrint(p->pExpression, "", b, fp);
      Output_Append(fp, "]");

    }
    */
}

static bool TDeclarator_PrintCore2(TProgram* program, TDeclarator* p, bool b, StrBuilder* fp)
{
    /*b = false;

    if (p->PointerList.size > 0)
    {
      b = TPointerList_CodePrint(&p->PointerList, b, fp);
    }


    if (p->pDeclaratorOpt)
    {
      Output_Append(fp, "(");
      b = TDeclarator_PrintCore2(p->pDeclaratorOpt, b, fp);
      Output_Append(fp, ")");
    }
    else
    {


      b = TTypeQualifier_CodePrint(&p->Qualifiers, b, fp);

      if (p->Name != NULL)
      {
        Output_Append(fp, " ");
        Output_Append(fp, p->Name);
      }
    }



    if (p->pParametersOpt != NULL)
    {
      b = TParameterList_CodePrint(p->pParametersOpt, b, fp);
    }

    if (p->token == TK_LEFT_SQUARE_BRACKET)
    {
      //tem que revisar..isso fica no p->pDeclaratorOpt
      Output_Append(fp, "[");
      b = TExpression_CodePrint(p->pExpression, "", b, fp);
      Output_Append(fp, "]");

    }

    else
    {
      //Output_Append(fp, "\"name\": null");
    }




    */
    return true;
}
static bool TDirectDeclarator_CodePrint(TProgram* program, TDirectDeclarator* pDirectDeclarator,
    bool b,
    StrBuilder* fp)
{
    if (pDirectDeclarator == NULL)
    {
        return false;
    }
    //fprintf(fp, "{");
    b = false;

    if (pDirectDeclarator->Identifier)
    {
        //identifier
        Output_Append(fp, " ");
        Output_Append(fp, pDirectDeclarator->Identifier);
        b = true;
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        //( declarator )
        Output_Append(fp, "(");
        b = TDeclarator_CodePrint(program, pDirectDeclarator->pDeclarator, b, fp);
        Output_Append(fp, ")");
    }

    if (pDirectDeclarator->Type == TDirectDeclaratorTypeArray)
    {
        /*
        direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
        direct-declarator [ static type-qualifier-listopt assignment-expression ]
        direct-declarator [ type-qualifier-list static assignment-expression ]
        */

        Output_Append(fp, "[");
        if (pDirectDeclarator->pExpression)
        {
            b = TExpression_CodePrint(program, pDirectDeclarator->pExpression, "assignment-expression", b, fp);
        }
        Output_Append(fp, "]");
    }


    if (pDirectDeclarator->Type == TDirectDeclaratorTypeFunction)
    {
        //( parameter-type-list )
        //fprintf(fp, ",");
        //fprintf(fp, "\"parameter-type-list\":");
        TParameterList_CodePrint(program, &pDirectDeclarator->Parameters, b, fp);
    }

    if (pDirectDeclarator->pDirectDeclarator)
    {
        //fprintf(fp, "\"direct-declarator\":");
        TDirectDeclarator_CodePrint(program, pDirectDeclarator->pDirectDeclarator, b, fp);
    }


    //fprintf(fp, "}");
    return b;
}

static bool TDeclarator_CodePrint(TProgram* program, TDeclarator* p, bool b, StrBuilder* fp)
{
    //fprintf(fp, "{");
    b = false;

    //fprintf(fp, "\"pointer\":");
    b = TPointerList_CodePrint(program, &p->PointerList, b, fp);

    //if (b)
    //{
      //fprintf(fp, ",");
    //}
    //fprintf(fp, "\"direct-declarator\":");
    b = TDirectDeclarator_CodePrint(program, p->pDirectDeclarator, b, fp);

    //fprintf(fp, "}");
    return b;
}

bool TInitDeclarator_CodePrint(TProgram* program, TInitDeclarator* p, bool b, StrBuilder* fp);



bool TStructDeclarator_CodePrint(TProgram* program, TStructDeclarator* p, bool b, StrBuilder* fp)
{
    b = false;
    b = TDeclarator_CodePrint(program, p->pDeclarator, b, fp);
    if (p->pInitializer)
    {
        Output_Append(fp, " /* = ");
        TInitializer_CodePrint(program, NULL, NULL, p->pInitializer, b, fp);
        Output_Append(fp, " */");
    }
    return true;
}

static bool TStructDeclaratorList_CodePrint(TProgram* program, TStructDeclaratorList *p, bool b, StrBuilder* fp)
{
    b = false;



    ForEachListItem(TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            Output_Append(fp, ",");
        b = TStructDeclarator_CodePrint(program, pItem, b, fp);
    }


    return true;
}

static bool TStructDeclaration_CodePrint(TProgram* program, TStructDeclaration* p, bool b, StrBuilder* fp)
{
    b = TTypeQualifier_CodePrint(program, &p->Qualifier, false, fp);
    b = TTypeSpecifier_CodePrint(program, p->pSpecifier, b, fp);
    b = TStructDeclaratorList_CodePrint(program, &p->DeclaratorList, b, fp);
    return true;
}

static bool TAnyStructDeclaration_CodePrint(TProgram* program, TAnyStructDeclaration* p, bool b, StrBuilder* fp)
{
    switch (p->type)
    {
    case TStructDeclaration_ID:
        b = TStructDeclaration_CodePrint(program, (TStructDeclaration*)p, b, fp);
        break;

    default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool StorageSpecifier_CodePrint(TProgram* program, TStorageSpecifier* p, bool b, StrBuilder* fp)
{

    if (p->bIsAuto)
    {
        Output_Append(fp, " auto");
        b = true;
    }

    if (p->bIsExtern)
    {
        Output_Append(fp, " extern");
        b = true;
    }

    if (p->bIsRegister)
    {
        Output_Append(fp, " register");
        b = true;
    }

    if (p->bIsStatic)
    {
        Output_Append(fp, " static");
        b = true;
    }




    if (p->bIsThread_local)
    {
        Output_Append(fp, " [Thread_local]");
        b = true;
    }

    if (p->bIsTypedef)
    {
        Output_Append(fp, " typedef");
        b = true;
    }

    return b;
}

static bool TFunctionSpecifier_CodePrint(TProgram* program, TFunctionSpecifier* p, bool b, StrBuilder* fp)
{
    if (p->bIsInline)
    {
        Output_Append(fp, " inline");
        b = true;
    }
    if (p->bIsNoReturn)
    {
        Output_Append(fp, " [noreturn]");
        b = true;
    }
    return b;
}


static bool TTypeQualifier_CodePrint(TProgram* program, TTypeQualifier* p, bool b, StrBuilder* fp)
{

    if (p->bIsAtomic)
    {
        Output_Append(fp, " _Atomic");
        b = true;
    }

    if (p->bIsConst)
    {
        Output_Append(fp, " const");
        b = true;
    }

    if (p->bIsRestrict)
    {
        Output_Append(fp, " restrict");
        b = true;
    }
    if (p->bIsVolatile)
    {
        Output_Append(fp, " volatile");
        b = true;
    }
    return b;
}

static bool TPointer_CodePrint(TProgram* program, TPointer* pPointer, bool b, StrBuilder* fp)
{
    if (pPointer->bPointer)
    {
        Output_Append(fp, "*");
    }
    TTypeQualifier_CodePrint(program, &pPointer->Qualifier, false, fp);

    return true;
}

static bool TDeclarationSpecifiers_CodePrint(TProgram* program, TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, StrBuilder* fp)
{
    b = TFunctionSpecifier_CodePrint(program, &pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
    b = StorageSpecifier_CodePrint(program, &pDeclarationSpecifiers->StorageSpecifiers, b, fp);
    b = TTypeQualifier_CodePrint(program, &pDeclarationSpecifiers->TypeQualifiers, b, fp);
    b = TTypeSpecifier_CodePrint(program, pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
    return b;
}

bool TInitDeclarator_CodePrint(TProgram* program,
    TTypeSpecifier* pTypeSpecifier,
    bool bIsPointer,
    TInitDeclarator* p,
    bool b, StrBuilder* fp)
{
    b = false;
    b = TDeclarator_CodePrint(program, p->pDeclarator, b, fp);
    if (p->pInitializer)
    {
        Output_Append(fp, " = ");
        b = TInitializer_CodePrint(program, pTypeSpecifier, bIsPointer, p->pInitializer, b, fp);
    }
    return true;
}

//bool TInitDeclarator_CodePrint(TInitDeclarator* p, bool b, StrBuilder* fp);

bool TInitDeclaratorList_CodePrint(TProgram* program,
    TTypeSpecifier* pTypeSpecifier,
    TInitDeclaratorList *p,
    bool b,
    StrBuilder* fp)
{
    b = false;
    //fprintf(fp, "[");
    ForEachListItem(TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            Output_Append(fp, ",");
        bool bIsPointer =
            TPointerList_IsPointer(&pInitDeclarator->pDeclarator->PointerList);

        b = TInitDeclarator_CodePrint(program, pTypeSpecifier, bIsPointer, pInitDeclarator, b, fp);
    }

    //  fprintf(fp, "]");
    return true;
}



static bool TDeclaration_CodePrint(TProgram* program,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{



    //para amalgamation eh util transformar a funcao em static
#ifdef amalgamation 
    if (p->Declarators.size > 0 &&
        p->Declarators.pItems[0]->pDeclaratorOpt != NULL &&
        p->Declarators.pItems[0]->pDeclaratorOpt->token == TK_LEFT_PARENTHESIS)
    {
        if (!p->Specifiers.StorageSpecifiers.bIsStatic)
        {
            p->Specifiers.StorageSpecifiers.bIsStatic = true;
        }
    }
#endif

    b = TDeclarationSpecifiers_CodePrint(program, &p->Specifiers, false, fp);


    b = TInitDeclaratorList_CodePrint(program,
        p->Specifiers.pTypeSpecifierOpt,
        &p->InitDeclaratorList, b, fp);

    if (p->pCompoundStatementOpt != NULL)
    {
        TCompoundStatement_CodePrint(program, p->pCompoundStatementOpt, b, fp);
    }
    else
    {
        Output_Append(fp, ";");
    }


    return true;
}


static bool TParameterDeclaration_CodePrint(TProgram* program, TParameterDeclaration* p, bool b, StrBuilder* fp)
{

    b = TDeclarationSpecifiers_CodePrint(program, &p->Specifiers, false, fp);


    b = TDeclarator_CodePrint(program, &p->Declarator, b, fp);

    return b;
}

static bool TAnyDeclaration_CodePrint(TProgram* program, TAnyDeclaration *pDeclaration, bool b, StrBuilder* fp)
{
    switch (pDeclaration->type)
    {
    case TStaticAssertDeclaration_ID:
        break;

    case TDeclaration_ID:
        b = TDeclaration_CodePrint(program, (TDeclaration*)pDeclaration, b, fp);
        break;

    default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool TDesignatorList_CodePrint(TProgram* program, TDesignatorList *p, bool b, StrBuilder* fp)
{
    b = false;


    ForEachListItem(TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            Output_Append(fp, ",");
        }
        b = TDesignator_CodePrint(program, pItem, b, fp);
    }


    return true;
}


static bool TInitializerListItem_CodePrint(TProgram* program,
    TTypeSpecifier* pTypeSpecifier,
    bool bIsPointer,
    TInitializerListItem* p, bool b, StrBuilder* fp)
{

    b = false;

    if (!List_IsEmpty(&p->DesignatorList))
    {
        b = TDesignatorList_CodePrint(program, &p->DesignatorList, b, fp);
    }

    b = TInitializer_CodePrint(program, pTypeSpecifier, bIsPointer,
        p->pInitializer, b, fp);

    return true;
}


static bool TDeclarations_CodePrint(TProgram* program, TDeclarations *p, bool b, StrBuilder* fp)
{
    b = false;


    for (size_t i = 0; i < p->size; i++)
    {
        if (i > 0)
            Output_Append(fp, ",");

        TAnyDeclaration* pItem = p->pItems[i];
        b = TAnyDeclaration_CodePrint(program, pItem, b, fp);

    }

    return true;
}

/*
static void TProgram_PrintToFile(TProgram* pProgram,
                        const char* fileName)
{
  StrBuilder * fp = fopen(fileName, "w");
  TDeclarations_CodePrint(&pProgram->Declarations, false, fp);
  fclose(fp);
}*/


static void TProgram_PrintFiles(TProgram* pProgram,
    StrBuilder* fp,
    const char* userpath)
{
    //TODO tem que ter um teste especial..

    //o arqquivo externo que foi incluido por um aquivo local
    //deve ser incluido..se ele foi incluido por outro nao.
    //tem que marcar se foi incluido por um da lista de includes e nao incluir

    Output_Append(fp, "/*external files*/\n");
    for (int i = 0; i < pProgram->Files2.size; i++)
    {
        TFile *pFile = pProgram->Files2.pItems[i];
        if (pFile->bDirectInclude)
        {
            //char drive[_MAX_DRIVE];
            //char dir[_MAX_DIR];
            //char fname[_MAX_FNAME];
            //char ext[_MAX_EXT];
            //SplitPath(pFile->IncludePath, drive, dir, fname, ext); // C4996

            if (pFile->bSystemLikeInclude)
            {
                Output_Append(fp, "#include <");
                Output_Append(fp, pFile->IncludePath);
                Output_Append(fp, ">\n");
            }
            else
            {
                Output_Append(fp, "#include \"");
                Output_Append(fp, pFile->IncludePath);
                Output_Append(fp, "\"\n");
            }

        }
    }
    Output_Append(fp, "\n");
}


void TProgram_PrintCodeToFile(TProgram* pProgram,
    const char* outFileName,
    const char* inputFileName)
{
    FILE * fp = fopen(outFileName, "w");
    bool b = false;

    int k = 0;

    for (int i = 0; i < pProgram->Files2.size; i++)
    {
        TFile *pFile = pProgram->Files2.pItems[i];
        printf("\"%s\"\n", pFile->FullPath);
    }

    StrBuilder sb = STRBUILDER_INIT;

    for (size_t i = 0; i < pProgram->Declarations.size; i++)
    {
        TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];
        //int fileIndex = TAnyDeclaration_GetFileIndex(pItem);
        //TFile *pFile = pProgram->Files2.pItems[fileIndex];
        //const char * path = pFile->FullPath;

        b = TAnyDeclaration_CodePrint(pProgram, pItem, b, &sb);

        fprintf(fp, "%s", sb.c_str);
        StrBuilder_Clear(&sb);
        k++;

    }
    StrBuilder_Destroy(&sb);
    fclose(fp);
}


