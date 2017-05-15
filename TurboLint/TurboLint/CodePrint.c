#include "CodePrint.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Base\Path.h"

static bool TInitializerList_CodePrint(TInitializerList*p, bool b, StrBuilder* fp);
static bool TInitializerListType_CodePrint(TInitializerListType*p, bool b, StrBuilder* fp);
static bool TDeclarator_CodePrint(TDeclarator* p, bool b, StrBuilder* fp);
static bool TAnyDeclaration_CodePrint(TAnyDeclaration *pDeclaration, bool b, StrBuilder* fp);
static bool TTypeSpecifier_CodePrint(TTypeSpecifier* p, bool b, StrBuilder* fp);
static bool TAnyStructDeclaration_CodePrint(TAnyStructDeclaration* p, bool b, StrBuilder* fp);
static bool TTypeQualifier_CodePrint(TTypeQualifier* p, bool b, StrBuilder* fp);
static bool TDeclaration_CodePrint(TDeclaration* p, bool b, StrBuilder* fp);
static bool TExpression_CodePrint(TExpression * p, const char* name, bool b, StrBuilder* fp);
static bool TStatement_CodePrint(TStatement * p, bool b, StrBuilder* fp);
static bool TBlockItem_CodePrint(TBlockItem * p, bool b, StrBuilder* fp);
static bool TInitializer_CodePrint(TInitializer* p, bool b, StrBuilder* fp);
static bool TPointer_CodePrint(TPointer* pPointer, bool b, StrBuilder* fp);
static bool TParameterDeclaration_CodePrint(TParameterDeclaration* p, bool b, StrBuilder* fp);
static bool TInitializerListItem_CodePrint(TInitializerListItem* p, bool b, StrBuilder* fp);





static bool TCompoundStatement_CodePrint(TCompoundStatement * p, bool b, StrBuilder* fp)
{

	//
  b = true;
  StrBuilder_Append(fp, "\n{\n");

  for (size_t j = 0; j < p->BlockItemList.size; j++)
  {
    TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
    TBlockItem_CodePrint(pBlockItem, j > 0, fp);
  }

  StrBuilder_Append(fp, "}\n");
  return b;
}


static bool TLabeledStatement_CodePrint(TLabeledStatement * p, bool b, StrBuilder* fp)
{
  b = true;

  if (p->token == TK_CASE)
  {
    StrBuilder_Append(fp, "case ");
    if (p->pStatementOpt)
    {
      b = TExpression_CodePrint(p->pExpression, "", false, fp);
    }
    StrBuilder_Append(fp, ":\n");
    b = TStatement_CodePrint(p->pStatementOpt, false, fp);
  }
  else if (p->token == TK_DEFAULT)
  {
    StrBuilder_Append(fp, "default:\n");
    b = TStatement_CodePrint(p->pStatementOpt, false, fp);
  }
  else if (p->token == TK_IDENTIFIER)
  {
    StrBuilder_Append(fp, p->Identifier);
    StrBuilder_Append(fp, ":");
  }


  return b;
}

static bool TForStatement_CodePrint(TForStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "for (");
  if (p->pInitDeclarationOpt) {
    TAnyDeclaration_CodePrint(p->pInitDeclarationOpt, b, fp);
    if (p->pExpression2)
    {
      b = TExpression_CodePrint(p->pExpression2, "expr2", true, fp);
    }
    StrBuilder_Append(fp, ";");
    b = TExpression_CodePrint(p->pExpression3, "expr3", b, fp);
  }
  else
  {
    b = TExpression_CodePrint(p->pExpression1, "expr1", true, fp);
    StrBuilder_Append(fp, ";");
    b = TExpression_CodePrint(p->pExpression2, "expr2", b, fp);
    StrBuilder_Append(fp, ";");
    b = TExpression_CodePrint(p->pExpression3, "expr3", b, fp);
  }


  StrBuilder_Append(fp, ")");

  b = TStatement_CodePrint(p->pStatement, false, fp);

  return b;
}


static bool TWhileStatement_CodePrint(TWhileStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "while (");
  b = TExpression_CodePrint(p->pExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")");
  b = TStatement_CodePrint(p->pStatement, false, fp);
  return b;
}


static bool TReturnStatement_CodePrint(TReturnStatement * p, bool b, StrBuilder* fp)
{
  StrBuilder_Append(fp, "return ");
  TExpression_CodePrint(p->pExpression, "return-statement", false, fp);
  StrBuilder_Append(fp, ";\n");
  return true;
}

static bool TDoStatement_CodePrint(TDoStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "do {");
  b = TStatement_CodePrint(p->pStatement, false, fp);
  StrBuilder_Append(fp, "} while (");
  b = TExpression_CodePrint(p->pExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")\n");

  return b;
}


static bool TExpressionStatement_CodePrint(TExpressionStatement * p, bool b, StrBuilder* fp)
{
  TExpression_CodePrint(p->pExpression, "", b, fp);
  StrBuilder_Append(fp, ";\n");
  return true;
}


static bool TJumpStatement_CodePrint(TJumpStatement * p, bool b, StrBuilder* fp)
{


  StrBuilder_Append(fp,  TokenToString(((TBinaryExpression*)p)->token));
  if (p->pExpression)
  {

    b = TExpression_CodePrint(p->pExpression, "statement", false, fp);
  }

  if (p->token == TK_BREAK)
  {
    StrBuilder_Append(fp, ";\n");
  }
  else
  {
    StrBuilder_Append(fp, ";");
  }

  return true;
}

static bool TAsmStatement_CodePrint(TAsmStatement * p, bool b, StrBuilder* fp)
{
  StrBuilder_Append(fp, "\"type\":\"asm-statement\"");
  return true;
}

static bool TSwitchStatement_CodePrint(TSwitchStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "switch (");
  b = TExpression_CodePrint(p->pConditionExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")");
  b = TStatement_CodePrint(p->pExpression, false, fp);
  return b;
}


static bool TIfStatement_CodePrint(TIfStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "if (");


  b = TExpression_CodePrint(p->pConditionExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")");

  if (p->pStatement->type != TCompoundStatement_ID)
    StrBuilder_Append(fp, "\n");

  if (p->pStatement)
  {
    b = TStatement_CodePrint(p->pStatement, false, fp);
  }

  if (p->pElseStatement)
  {
    StrBuilder_Append(fp, "else\n");
    b = TStatement_CodePrint(p->pElseStatement, false, fp);
  }

  return b;
}

static bool TStatement_CodePrint(TStatement *  p, bool b, StrBuilder* fp)
{
  if (p == NULL)
  {
    return false;
  }

  switch (p->type)
  {
  case TExpressionStatement_ID:
    b = TExpressionStatement_CodePrint((TExpressionStatement*)p, b, fp);
    break;

  case TSwitchStatement_ID:
    b = TSwitchStatement_CodePrint((TSwitchStatement*)p, b, fp);
    break;

  case TLabeledStatement_ID:
    b = TLabeledStatement_CodePrint((TLabeledStatement*)p, b, fp);
    break;

  case TForStatement_ID:
    b = TForStatement_CodePrint((TForStatement*)p, b, fp);
    break;

  case TJumpStatement_ID:
    b = TJumpStatement_CodePrint((TJumpStatement*)p, b, fp);
    break;

  case TAsmStatement_ID:
    b = TAsmStatement_CodePrint((TAsmStatement*)p, b, fp);
    break;

  case TCompoundStatement_ID:
    b = TCompoundStatement_CodePrint((TCompoundStatement*)p, b, fp);
    break;

  case TIfStatement_ID:
    b = TIfStatement_CodePrint((TIfStatement*)p, b, fp);
    break;

  case TDoStatement_ID:
    TDoStatement_CodePrint((TDoStatement*)p, b, fp);
    break;

  case TReturnStatement_ID:
    TReturnStatement_CodePrint((TReturnStatement*)p, b, fp);
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

static bool TBlockItem_CodePrint(TBlockItem *  p, bool b, StrBuilder* fp)
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

    b = TSwitchStatement_CodePrint((TSwitchStatement*)p, false, fp);

    break;

  case TJumpStatement_ID:

    b = TJumpStatement_CodePrint((TJumpStatement*)p, false, fp);

    break;

  case TForStatement_ID:

    b = TForStatement_CodePrint((TForStatement*)p, false, fp);

    break;

  case TIfStatement_ID:

    b = TIfStatement_CodePrint((TIfStatement*)p, false, fp);

    break;

  case TWhileStatement_ID:

    b = TWhileStatement_CodePrint((TWhileStatement*)p, b, fp);

    break;

  case TDoStatement_ID:

    b = TDoStatement_CodePrint((TDoStatement*)p, false, fp);

    break;

  case TDeclaration_ID:
    b = TDeclaration_CodePrint((TDeclaration*)p, false, fp);
    StrBuilder_Append(fp, "\n");
    break;

  case TLabeledStatement_ID:

    b = TLabeledStatement_CodePrint((TLabeledStatement*)p, false, fp);

    break;

  case TCompoundStatement_ID:
    b = TCompoundStatement_CodePrint((TCompoundStatement*)p, false, fp);
    break;

  case TExpressionStatement_ID:

    b = TExpressionStatement_CodePrint((TExpressionStatement*)p, false, fp);

    break;

  case TReturnStatement_ID:

    b = TReturnStatement_CodePrint((TReturnStatement*)p, false, fp);

    break;

  case TAsmStatement_ID:

    b = TAsmStatement_CodePrint((TAsmStatement*)p, false, fp);

    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

static bool TPostfixExpressionCore_CodePrint(TPostfixExpressionCore * p, bool b, StrBuilder* fp)
{

  b = false;

  if (p->pExpressionLeft)
  {
    b = TExpression_CodePrint(p->pExpressionLeft, "l", b, fp);
  }

  if (p->pInitializerList)
  {
    //falta imprimeir typename
    //TTypeName_Print*
    b = TInitializerList_CodePrint(p->pInitializerList, b, fp);
  }

  switch (p->token)
  {
  case TK_FULL_STOP:
    StrBuilder_Append(fp, ".");
    StrBuilder_Append(fp, p->Identifier);
    b = true;
    break;
  case TK_ARROW:
    StrBuilder_Append(fp, "->");
    StrBuilder_Append(fp, p->Identifier);
    b = true;
    break;

  case TK_LEFT_SQUARE_BRACKET:
    StrBuilder_Append(fp, "[");
    b = TExpression_CodePrint(p->pExpressionRight, "r", b, fp);
    StrBuilder_Append(fp, "]");
    break;

  case TK_LEFT_PARENTHESIS:
    StrBuilder_Append(fp, "(");
    b = TExpression_CodePrint(p->pExpressionRight, "r", b, fp);
    StrBuilder_Append(fp, ")");
    break;

  case TK_PLUSPLUS:
    StrBuilder_Append(fp, "++");
    b = true;
    break;
  case TK_MINUSMINUS:
    StrBuilder_Append(fp, "--");
    b = true;
    break;
    break;
  }


  b = true;
  if (p->pNext)
  {
    b = TPostfixExpressionCore_CodePrint(p->pNext, false, fp);
  }

  b = true;
  return b;
}

static bool TExpression_CodePrint(TExpression *  p,
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
      b = TExpression_CodePrint(((TBinaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
    StrBuilder_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
    b = TExpression_CodePrint(((TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
    break;

    CASE(TTernaryExpression) :
      b = TExpression_CodePrint(((TTernaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
    StrBuilder_Append(fp, " ? ");
    b = TExpression_CodePrint(((TTernaryExpression*)p)->pExpressionMiddle, "m-expr", b, fp);
    StrBuilder_Append(fp, " : ");
    b = TExpression_CodePrint(((TTernaryExpression*)p)->pExpressionRight, "r-expr", b, fp);

    break;

    CASE(TPrimaryExpressionValue) :
    {
      TPrimaryExpressionValue* pPrimaryExpressionValue =
        (TPrimaryExpressionValue*)p;

      if (pPrimaryExpressionValue->MacroExpansion != NULL)
      {
        StrBuilder_Append(fp,  pPrimaryExpressionValue->MacroExpansion);
      }
      else
      {

        if (pPrimaryExpressionValue->pExpressionOpt != NULL)
        {
          StrBuilder_Append(fp, "(");
          b = TExpression_CodePrint(pPrimaryExpressionValue->pExpressionOpt, "expr", b, fp);
          StrBuilder_Append(fp, ")");
        }
        else
        {
          StrBuilder_Append(fp, pPrimaryExpressionValue->lexeme);
        }
      }
      b = true;
    }
    break;

    CASE(TPostfixExpressionCore) :
    {
      TPostfixExpressionCore* pPostfixExpressionCore =
        (TPostfixExpressionCore*)p;
      b = TPostfixExpressionCore_CodePrint(pPostfixExpressionCore, b, fp);
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
          StrBuilder_Append(fp, "sizeof (");
          b = TTypeQualifier_CodePrint(&pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
          b = TTypeSpecifier_CodePrint(pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
          b = TDeclarator_CodePrint(&pTUnaryExpressionOperator->TypeName.Declarator, b, fp);
          StrBuilder_Append(fp, ")");

        }
        else
        {
          StrBuilder_Append(fp, "sizeof ");
          b = TExpression_CodePrint(pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);
          StrBuilder_Append(fp, "");
        }
      }
      else
      {
        StrBuilder_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
        b = TExpression_CodePrint(pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);

      }


    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;

      StrBuilder_Append(fp, "(");
      b = TTypeQualifier_CodePrint(&pCastExpressionType->TypeName.Specifiers.TypeQualifiers, false, fp);
      b = TTypeSpecifier_CodePrint(pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
      b = TDeclarator_CodePrint(&pCastExpressionType->TypeName.Declarator, b, fp);
      StrBuilder_Append(fp, ")");
      b = TExpression_CodePrint(pCastExpressionType->pExpression, "expr", b, fp);
    }
    break;

  default:

    ASSERT(false);
  }


  return b;
}



static   bool TEnumerator_CodePrint(TEnumerator* pTEnumerator, bool b, StrBuilder* fp)
{

  StrBuilder_Append(fp,  pTEnumerator->Name);

  if (pTEnumerator->pExpression)
  {
    StrBuilder_Append(fp, " = ");
    TExpression_CodePrint(pTEnumerator->pExpression, "expr", true, fp);

    //int r;
    //EvaluateConstantExpression(pTEnumerator->pExpression,  &r);

  }
  else
  {
    //vou criar uma expressionp enum?
  }

  return true;
}

static bool TEnumSpecifier_CodePrint(TEnumSpecifier* p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, " enum ");
  StrBuilder_Append(fp, p->Name);
  StrBuilder_Append(fp, "\n{\n");

  for (size_t i = 0; i < p->EnumeratorList.size; i++)
  {
    TEnumerator *pTEnumerator = p->EnumeratorList.pItems[i];

    TEnumerator_CodePrint(pTEnumerator, false, fp);

    if (i + 1 < p->EnumeratorList.size)
      StrBuilder_Append(fp, ",\n");
    else
      StrBuilder_Append(fp, "\n");

  }


  StrBuilder_Append(fp, "}");
  return true;
}


static bool TStructUnionSpecifier_CodePrint(TStructUnionSpecifier* p, bool b, StrBuilder* fp)
{
  b = true;

  if (p->bIsStruct)
    StrBuilder_Append(fp, " struct ");

  else
    StrBuilder_Append(fp, " union ");

  StrBuilder_Append(fp, p->Name);
  //struct point pt = {}
  if (p->StructDeclarationList.size > 0)
  {
    StrBuilder_Append(fp, " {\n");

    for (size_t i = 0; i < p->StructDeclarationList.size; i++)
    {
      TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
      b = TAnyStructDeclaration_CodePrint(pStructDeclaration, b, fp);
      StrBuilder_Append(fp, ";\n");
    }


    StrBuilder_Append(fp, "}");
  }

  return true;
}

static bool TSingleTypeSpecifier_CodePrint(TSingleTypeSpecifier* p, bool b, StrBuilder* fp)
{

  b = true;

  int i = 0;

  if (p->bIsVoid)
  {
    StrBuilder_Append(fp, " void");
    b = true;
  }

  if (p->bIsUnsigned)
  {
    StrBuilder_Append(fp, " unsigned");
    b = true;
  }

  if (p->bIsBool)
  {
    //StrBuilder_Append(fp, " _Bool");
    StrBuilder_Append(fp, " bool");
    b = true;
  }

  if (p->bIsChar)
  {
    StrBuilder_Append(fp, " char");
    b = true;
  }

  if (p->bIsShort)
  {
    StrBuilder_Append(fp, " short");
    b = true;
  }

  for (int j = 0; j < p->nLong; j++)
  {
    StrBuilder_Append(fp, " long");
    b = true;
  }

  if (p->bIsInt)
  {
    StrBuilder_Append(fp, " int");
    b = true;
  }

  if (p->bIsDouble)
  {
    StrBuilder_Append(fp, " double");
    b = true;
  }

  if (p->bIsFloat)
  {
    StrBuilder_Append(fp, " float");
    b = true;
  }

  if (p->bIsTypeDef)
  {
    StrBuilder_Append(fp, " ");
    StrBuilder_Append(fp, p->TypedefName);
    b = true;
  }


  return b;
}

static bool TTypeSpecifier_CodePrint(TTypeSpecifier*  p, bool b, StrBuilder* fp)
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
    b = TStructUnionSpecifier_CodePrint((TStructUnionSpecifier*)p, b, fp);
    break;

  case TEnumSpecifier_ID:
    b = TEnumSpecifier_CodePrint((TEnumSpecifier*)p, b, fp);
    break;

  case TSingleTypeSpecifier_ID:
    b = TSingleTypeSpecifier_CodePrint((TSingleTypeSpecifier*)p, b, fp);
    break;

  default:
    break;
  }

  return b;
}

static bool TDesignator_CodePrint(TDesignator* p, bool b, StrBuilder* fp)
{
  if (b)
    StrBuilder_Append(fp, ",");

  StrBuilder_Append(fp, "{");

  //
  if (p->Name)
  {
    //.identifier
    StrBuilder_Append(fp, ".");
    StrBuilder_Append(fp, p->Name);
  }

  else
  {
    //[constant-expression]
    TExpression_CodePrint(p->pExpression, "index", b, fp);
  }

  StrBuilder_Append(fp, "}");
  return b;
}


static bool TInitializerList_CodePrint(TInitializerList*p, bool b, StrBuilder* fp)
{

  b = false;
  StrBuilder_Append(fp, "{");

  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    TInitializerListItem* pItem = p->pItems[i];
    b = TInitializerListItem_CodePrint(pItem, b, fp);
  }

  StrBuilder_Append(fp, "}");

  return true;
}

static bool TInitializerListType_CodePrint(TInitializerListType*p, bool b, StrBuilder* fp)
{
  if (p->MacroExpansion != NULL)
  {
    StrBuilder_Append(fp, p->MacroExpansion);
  }
  else
  {
    b = TInitializerList_CodePrint(&p->InitializerList, b, fp);
  }

  return true;
}

static bool TInitializer_CodePrint(TInitializer*  p, bool b, StrBuilder* fp)
{
  if (p == NULL)
  {
    return false;
  }
  if (p->type == TInitializerListType_ID)
  {
    b = TInitializerListType_CodePrint((TInitializerListType*)p, b, fp);
  }
  else
  {
    b = TExpression_CodePrint((TExpression*)p, "", false, fp);
  }

  return b;
}



static bool TPointerList_CodePrint(TPointerList *p, bool b, StrBuilder* fp)
{
  b = false;

  for (size_t i = 0; i < p->size; i++)
  {
    TPointer * pItem = p->pItems[i];
    b = TPointer_CodePrint(pItem, b, fp);
  }

  return true;
}



static bool TParameterList_CodePrint(TParameterList *p, bool b, StrBuilder* fp)
{
  b = false;
  StrBuilder_Append(fp, "(");

  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    TParameterDeclaration * pItem = p->pItems[i];
    b = TParameterDeclaration_CodePrint(pItem, b, fp);
  }

  StrBuilder_Append(fp, ")");
  return true;
}

static bool TDeclarator_PrintCore(TDeclarator* p, 
                                  bool b, 
                                  StrBuilder * fp)
{
  /*if (p->token == TK_LEFT_PARENTHESIS &&
    p->pParametersOpt == NULL)
  {
    // ( declarator ) 
    StrBuilder_Append(fp, "(");
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
    StrBuilder_Append(fp, local.c_str);
    StrBuilder_Destroy(&local);
  }
  else
  {
    if (p->Name != NULL)
    {
      StrBuilder_Append(fp, " ");
      StrBuilder_Append(fp, p->Name);
    }
  }

  if (p->token == TK_LEFT_PARENTHESIS &&
    p->pParametersOpt == NULL)
  {
    // ( declarator ) 
    StrBuilder_Append(fp, ")");
  }

  if (p->pParametersOpt != NULL)
  {
    b = TParameterList_CodePrint(p->pParametersOpt, b, fp);
  }

  if (p->token == TK_LEFT_SQUARE_BRACKET)
  {
    //tem que revisar..isso fica no p->pDeclaratorOpt
    StrBuilder_Append(fp, "[");
    b = TExpression_CodePrint(p->pExpression, "", b, fp);
    StrBuilder_Append(fp, "]");

  }
  */
}

static bool TDeclarator_PrintCore2(TDeclarator* p, bool b, StrBuilder* fp)
{
  /*b = false;

  if (p->PointerList.size > 0)
  {
    b = TPointerList_CodePrint(&p->PointerList, b, fp);
  }


  if (p->pDeclaratorOpt)
  {
    StrBuilder_Append(fp, "(");
    b = TDeclarator_PrintCore2(p->pDeclaratorOpt, b, fp);
    StrBuilder_Append(fp, ")");
  }
  else
  {

  
    b = TTypeQualifier_CodePrint(&p->Qualifiers, b, fp);

    if (p->Name != NULL)
    {
      StrBuilder_Append(fp, " ");
      StrBuilder_Append(fp, p->Name);
    }
  }

  

  if (p->pParametersOpt != NULL)
  {
    b = TParameterList_CodePrint(p->pParametersOpt, b, fp);
  }

  if (p->token == TK_LEFT_SQUARE_BRACKET)
  {
    //tem que revisar..isso fica no p->pDeclaratorOpt
    StrBuilder_Append(fp, "[");
    b = TExpression_CodePrint(p->pExpression, "", b, fp);
    StrBuilder_Append(fp, "]");

  }
  
  else
  {
    //StrBuilder_Append(fp, "\"name\": null");
  }

  


  */
  return true;
}
static bool TDirectDeclarator_CodePrint(TDirectDeclarator* pDirectDeclarator,
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
    StrBuilder_Append(fp, " ");
    StrBuilder_Append(fp, pDirectDeclarator->Identifier);
    b = true;
  }
  else  if (pDirectDeclarator->pDeclarator)
  {
    //( declarator )
    StrBuilder_Append(fp, "(");
    b = TDeclarator_CodePrint(pDirectDeclarator->pDeclarator, b, fp);
    StrBuilder_Append(fp, ")");
  }

  if (pDirectDeclarator->token == TK_LEFT_SQUARE_BRACKET)
  {
    /*
    direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
    direct-declarator [ static type-qualifier-listopt assignment-expression ]
    direct-declarator [ type-qualifier-list static assignment-expression ]
    */

    StrBuilder_Append(fp, "[");
    if (pDirectDeclarator->pExpression)
    {
      b = TExpression_CodePrint(pDirectDeclarator->pExpression, "assignment-expression", b, fp);
    }
    StrBuilder_Append(fp, "]");
  }
  

  if (pDirectDeclarator->pParametersOpt)
  {
    //( parameter-type-list )
    //fprintf(fp, ",");
    //fprintf(fp, "\"parameter-type-list\":");
    TParameterList_CodePrint(pDirectDeclarator->pParametersOpt, b, fp);
  }

  if (pDirectDeclarator->pDirectDeclarator)
  {
    //fprintf(fp, "\"direct-declarator\":");
    TDirectDeclarator_CodePrint(pDirectDeclarator->pDirectDeclarator, b, fp);
  }


  //fprintf(fp, "}");
  return b;
}

static bool TDeclarator_CodePrint(TDeclarator* p, bool b, StrBuilder* fp)
{
  //fprintf(fp, "{");
  b = false;

  //fprintf(fp, "\"pointer\":");
  b = TPointerList_CodePrint(&p->PointerList, b, fp);

  //if (b)
  //{
    //fprintf(fp, ",");
  //}
  //fprintf(fp, "\"direct-declarator\":");
  b = TDirectDeclarator_CodePrint(p->pDirectDeclarator, b, fp);

  //fprintf(fp, "}");
  return b;
}


static bool TDeclaratorList_CodePrint(TDeclaratorList *p, bool b, StrBuilder* fp)
{
  b = false;


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    TDeclarator* pItem = p->pItems[i];
    b = TDeclarator_CodePrint(pItem, b, fp);
  }


  return true;
}

static bool TStructDeclaration_CodePrint(TStructDeclaration* p, bool b, StrBuilder* fp)
{
  b = TTypeQualifier_CodePrint(&p->Qualifier, false, fp);
  b = TTypeSpecifier_CodePrint(p->pSpecifier, b, fp);
  b = TDeclaratorList_CodePrint(&p->DeclaratorList, b, fp);
  return true;
}

static bool TAnyStructDeclaration_CodePrint(TAnyStructDeclaration* p, bool b, StrBuilder* fp)
{
  switch (p->type)
  {
  case TStructDeclaration_ID:
    b = TStructDeclaration_CodePrint((TStructDeclaration*)p, b, fp);
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

static bool StorageSpecifier_CodePrint(TStorageSpecifier* p, bool b, StrBuilder* fp)
{

  if (p->bIsAuto)
  {
    StrBuilder_Append(fp, " auto");
    b = true;
  }

  if (p->bIsExtern)
  {
    StrBuilder_Append(fp, " extern");
    b = true;
  }

  if (p->bIsRegister)
  {
    StrBuilder_Append(fp, " register");
    b = true;
  }

  if (p->bIsStatic)
  {
    StrBuilder_Append(fp, " static");
    b = true;
  }




  if (p->bIsThread_local)
  {
    StrBuilder_Append(fp, " [Thread_local]");
    b = true;
  }

  if (p->bIsTypedef)
  {
    StrBuilder_Append(fp, " typedef");
    b = true;
  }

  return b;
}

static bool TFunctionSpecifier_CodePrint(TFunctionSpecifier* p, bool b, StrBuilder* fp)
{
  if (p->bIsInline)
  {
    StrBuilder_Append(fp, " inline");
    b = true;
  }
  if (p->bIsNoReturn)
  {
    StrBuilder_Append(fp, " [noreturn]");
    b = true;
  }
  return b;
}


static bool TTypeQualifier_CodePrint(TTypeQualifier* p, bool b, StrBuilder* fp)
{

  if (p->bIsAtomic)
  {
    StrBuilder_Append(fp, " _Atomic");
    b = true;
  }

  if (p->bIsConst)
  {
    StrBuilder_Append(fp, " const");
    b = true;
  }

  if (p->bIsRestrict)
  {
    StrBuilder_Append(fp, " restrict");
    b = true;
  }
  if (p->bIsVolatile)
  {
    StrBuilder_Append(fp, " volatile");
    b = true;
  }
  return b;
}

static bool TPointer_CodePrint(TPointer* pPointer, bool b, StrBuilder* fp)
{
  if (pPointer->bPointer)
  {
    StrBuilder_Append(fp, "*");
  }
  TTypeQualifier_CodePrint(&pPointer->Qualifier, false, fp);

  return true;
}

static bool TDeclarationSpecifiers_CodePrint(TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, StrBuilder* fp)
{
  b = TFunctionSpecifier_CodePrint(&pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
  b = StorageSpecifier_CodePrint(&pDeclarationSpecifiers->StorageSpecifiers, b, fp);
  b = TTypeQualifier_CodePrint(&pDeclarationSpecifiers->TypeQualifiers, b, fp);
  b = TTypeSpecifier_CodePrint(pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
  return b;
}

bool TInitDeclarator_CodePrint(TInitDeclarator* p, bool b, StrBuilder* fp)
{

  
  b = false;

  
  b = TDeclarator_CodePrint(p->pDeclarator, b, fp);

  if (p->pInitializer)
  {    
    StrBuilder_Append(fp, " = ");
    TInitializer_CodePrint(p->pInitializer, b, fp);
  }

  
  return true;
}


bool TInitDeclaratorList_CodePrint(TInitDeclaratorList *p, bool b, StrBuilder* fp)
{
  b = false;
  //fprintf(fp, "[");
  TInitDeclarator* pInitDeclarator = p->pInitDeclaratorHeap;
  int i = 0;
  while (pInitDeclarator)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    b = TInitDeclarator_CodePrint(pInitDeclarator, b, fp);
    pInitDeclarator = pInitDeclarator->pInitDeclaratorNext;
    i++;
  }

//  fprintf(fp, "]");
  return true;
}

static bool TDeclaration_CodePrint(TDeclaration* p,
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

  b = TDeclarationSpecifiers_CodePrint(&p->Specifiers, false, fp);

  b = TInitDeclaratorList_CodePrint(&p->InitDeclaratorList, b, fp);

  if (p->pCompoundStatementOpt != NULL)
  {
    TCompoundStatement_CodePrint(p->pCompoundStatementOpt, b, fp);
  }
  else
  {
    StrBuilder_Append(fp, ";");
  }

  if (p->PreprocessorAndCommentsString.size > 0)
  {
    StrBuilder_Append(fp, "\n");
    StrBuilder_Append(fp, p->PreprocessorAndCommentsString.c_str);
  }

  return true;
}


static bool TParameterDeclaration_CodePrint(TParameterDeclaration* p, bool b, StrBuilder* fp)
{

  b = TDeclarationSpecifiers_CodePrint(&p->Specifiers, false, fp);


  b = TDeclarator_CodePrint(&p->Declarator, b, fp);

  return b;
}

static bool TAnyDeclaration_CodePrint(TAnyDeclaration *pDeclaration, bool b, StrBuilder* fp)
{
  switch (pDeclaration->type)
  {
  case TStaticAssertDeclaration_ID:
    break;

  case TDeclaration_ID:
    b = TDeclaration_CodePrint((TDeclaration*)pDeclaration, b, fp);
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

static bool TDesignatorList_CodePrint(TDesignatorList *p, bool b, StrBuilder* fp)
{
  b = false;


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    TDesignator* pItem = p->pItems[i];
    b = TDesignator_CodePrint(pItem, b, fp);
  }


  return true;
}


static bool TInitializerListItem_CodePrint(TInitializerListItem* p, bool b, StrBuilder* fp)
{

  b = false;

  if (p->pDesignatorList)
  {
    b = TDesignatorList_CodePrint(p->pDesignatorList, b, fp);
  }

  b = TInitializer_CodePrint(p->pInitializer, b, fp);

  return true;
}


static bool TDeclarations_CodePrint(TDeclarations *p, bool b, StrBuilder* fp)
{
  b = false;


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    TAnyDeclaration* pItem = p->pItems[i];
    b = TAnyDeclaration_CodePrint(pItem, b, fp);

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

  StrBuilder_Append(fp, "/*external files*/\n");
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
      StrBuilder_Append(fp, "#include <");
      StrBuilder_Append(fp, pFile->IncludePath);
      StrBuilder_Append(fp, ">\n");		  
	  }
	  else
	  {
      StrBuilder_Append(fp, "#include \"");
      StrBuilder_Append(fp, pFile->IncludePath);
      StrBuilder_Append(fp, "\"\n");		  
	  }
      
    }
  }
  StrBuilder_Append(fp, "\n");
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
  TProgram_PrintFiles(pProgram, &sb, inputFileName);
  fprintf(fp, "%s", sb.c_str);
  StrBuilder_Clear(&sb);

  for (size_t i = 0; i < pProgram->Declarations.size; i++)
  {
    

    TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];
    int fileIndex = TAnyDeclaration_GetFileIndex(pItem);
    TFile *pFile = pProgram->Files2.pItems[fileIndex];
    const char * path = pFile->FullPath;

    bool bPrintThisDeclaration = false;
    if (inputFileName == NULL)
    {
      //Gerando amalgamation
      for (int i = 0; i < pProgram->MySourceDir.size; i++)
      {
        const char* mydir = pProgram->MySourceDir.pItems[i];
        if (IsInPath(pFile->FullPath, mydir))
        {
          bPrintThisDeclaration = true;
          break;
        }
      }
    }
    else
    {
      //Gerando 1 arquivo
      if (strcmp(pFile->FullPath, inputFileName) == 0)
      {
        bPrintThisDeclaration = true;
      }
    }
    if (bPrintThisDeclaration)
    {
      b = TAnyDeclaration_CodePrint(pItem, b, &sb);
      StrBuilder_Append(&sb, "\n\n");
      fprintf(fp, "%s", sb.c_str);
      StrBuilder_Clear(&sb);
      k++;
    }
  }
  StrBuilder_Destroy(&sb);
  fclose(fp);
}


