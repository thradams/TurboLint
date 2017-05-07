#include "CodePrint.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Base\Path.h"

static bool TInitializerList_CodePrint(TInitializerList*p, bool b, FILE* fp);
static bool TInitializerListType_CodePrint(TInitializerListType*p, bool b, FILE* fp);
static bool TDeclarator_CodePrint(TDeclarator* p, bool b, FILE* fp);
static bool TAnyDeclaration_CodePrint(TAnyDeclaration *pDeclaration, bool b, FILE* fp);
static bool TTypeSpecifier_CodePrint(TTypeSpecifier* p, bool b, FILE* fp);
static bool TAnyStructDeclaration_CodePrint(TAnyStructDeclaration* p, bool b, FILE* fp);
static bool TTypeQualifier_CodePrint(TTypeQualifier* p, bool b, FILE* fp);
static bool TDeclaration_CodePrint(TDeclaration* p, bool b, FILE* fp);
static bool TExpression_CodePrint(TExpression * p, const char* name, bool b, FILE* fp);
static bool TStatement_CodePrint(TStatement * p, bool b, FILE* fp);
static bool TBlockItem_CodePrint(TBlockItem * p, bool b, FILE* fp);
static bool TInitializer_CodePrint(TInitializer* p, bool b, FILE* fp);
static bool TPointer_CodePrint(TPointer* pPointer, bool b, FILE* fp);
static bool TParameterDeclaration_CodePrint(TParameterDeclaration* p, bool b, FILE* fp);
static bool TInitializerListItem_CodePrint(TInitializerListItem* p, bool b, FILE* fp);

static bool TCompoundStatement_CodePrint(TCompoundStatement * p, bool b, FILE* fp)
{

	//
  b = true;
  fprintf(fp, "\n{\n");

  for (size_t j = 0; j < p->BlockItemList.size; j++)
  {
    TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
    TBlockItem_CodePrint(pBlockItem, j > 0, fp);
  }

  fprintf(fp, "}\n");
  return b;
}


static bool TLabeledStatement_CodePrint(TLabeledStatement * p, bool b, FILE* fp)
{
  b = true;

  if (p->token == TK_CASE)
  {
    fprintf(fp, "case ");
    if (p->pStatementOpt)
    {
      b = TExpression_CodePrint(p->pExpression, "", false, fp);
    }
    fprintf(fp, ":\n");
    b = TStatement_CodePrint(p->pStatementOpt, false, fp);
  }
  else if (p->token == TK_DEFAULT)
  {
    fprintf(fp, "default:\n");
    b = TStatement_CodePrint(p->pStatementOpt, false, fp);
  }
  else if (p->token == TK_IDENTIFIER)
  {
    fprintf(fp, "%s:", p->Identifier);
  }


  return b;
}

static bool TForStatement_CodePrint(TForStatement * p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, "for (");
  if (p->pInitDeclarationOpt) {
    TAnyDeclaration_CodePrint(p->pInitDeclarationOpt, b, fp);
    if (p->pExpression2)
    {
      b = TExpression_CodePrint(p->pExpression2, "expr2", true, fp);
    }
    fprintf(fp, ";");
    b = TExpression_CodePrint(p->pExpression3, "expr3", b, fp);
  }
  else
  {
    b = TExpression_CodePrint(p->pExpression1, "expr1", true, fp);
    fprintf(fp, ";");
    b = TExpression_CodePrint(p->pExpression2, "expr2", b, fp);
    fprintf(fp, ";");
    b = TExpression_CodePrint(p->pExpression3, "expr3", b, fp);
  }


  fprintf(fp, ")");

  b = TStatement_CodePrint(p->pStatement, false, fp);

  return b;
}


static bool TWhileStatement_CodePrint(TWhileStatement * p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, "while (");
  b = TExpression_CodePrint(p->pExpression, "expr", false, fp);
  fprintf(fp, ")");
  b = TStatement_CodePrint(p->pStatement, false, fp);
  return b;
}


static bool TReturnStatement_CodePrint(TReturnStatement * p, bool b, FILE* fp)
{
  fprintf(fp, "return ");
  TExpression_CodePrint(p->pExpression, "return-statement", false, fp);
  fprintf(fp, ";\n");
  return true;
}

static bool TDoStatement_CodePrint(TDoStatement * p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, "do {");
  b = TStatement_CodePrint(p->pStatement, false, fp);
  fprintf(fp, "} while (");
  b = TExpression_CodePrint(p->pExpression, "expr", false, fp);
  fprintf(fp, ")\n");

  return b;
}


static bool TExpressionStatement_CodePrint(TExpressionStatement * p, bool b, FILE* fp)
{
  TExpression_CodePrint(p->pExpression, "", b, fp);
  fprintf(fp, ";\n");
  return true;
}


static bool TJumpStatement_CodePrint(TJumpStatement * p, bool b, FILE* fp)
{


  fprintf(fp, "%s", TokenToString(((TBinaryExpression*)p)->token));
  if (p->pExpression)
  {

    b = TExpression_CodePrint(p->pExpression, "statement", false, fp);
  }

  if (p->token == TK_BREAK)
  {
    fprintf(fp, ";\n");
  }
  else
  {
    fprintf(fp, ";");
  }

  return true;
}

static bool TAsmStatement_CodePrint(TAsmStatement * p, bool b, FILE* fp)
{
  fprintf(fp, "\"type\":\"asm-statement\"");
  return true;
}

static bool TSwitchStatement_CodePrint(TSwitchStatement * p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, "switch (");
  b = TExpression_CodePrint(p->pConditionExpression, "expr", false, fp);
  fprintf(fp, ")");
  b = TStatement_CodePrint(p->pExpression, false, fp);
  return b;
}


static bool TIfStatement_CodePrint(TIfStatement * p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, "if (");


  b = TExpression_CodePrint(p->pConditionExpression, "expr", false, fp);
  fprintf(fp, ")");

  if (p->pStatement->type != TCompoundStatement_ID)
    fprintf(fp, "\n");

  if (p->pStatement)
  {
    b = TStatement_CodePrint(p->pStatement, false, fp);
  }

  if (p->pElseStatement)
  {
    fprintf(fp, "else\n");
    b = TStatement_CodePrint(p->pElseStatement, false, fp);
  }

  return b;
}

static bool TStatement_CodePrint(TStatement *  p, bool b, FILE* fp)
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

static bool TBlockItem_CodePrint(TBlockItem *  p, bool b, FILE* fp)
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
    fprintf(fp, "\n");
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

static bool TPostfixExpressionCore_CodePrint(TPostfixExpressionCore * p, bool b, FILE* fp)
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
    fprintf(fp, ".%s", p->Identifier);
    b = true;
    break;
  case TK_ARROW:
    fprintf(fp, "->%s", p->Identifier);
    b = true;
    break;

  case TK_LEFT_SQUARE_BRACKET:
    fprintf(fp, "[");
    b = TExpression_CodePrint(p->pExpressionRight, "r", b, fp);
    fprintf(fp, "]");
    break;

  case TK_LEFT_PARENTHESIS:
    fprintf(fp, "(");
    b = TExpression_CodePrint(p->pExpressionRight, "r", b, fp);
    fprintf(fp, ")");
    break;

  case TK_PLUSPLUS:
    fprintf(fp, "++");
    b = true;
    break;
  case TK_MINUSMINUS:
    fprintf(fp, "--");
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
  FILE* fp)
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
    fprintf(fp, "%s", TokenToString(((TBinaryExpression*)p)->token));
    b = TExpression_CodePrint(((TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
    break;

    CASE(TTernaryExpression) :
      b = TExpression_CodePrint(((TTernaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
    fprintf(fp, " ? ");
    b = TExpression_CodePrint(((TTernaryExpression*)p)->pExpressionMiddle, "m-expr", b, fp);
    fprintf(fp, " : ");
    b = TExpression_CodePrint(((TTernaryExpression*)p)->pExpressionRight, "r-expr", b, fp);

    break;

    CASE(TPrimaryExpressionValue) :
    {
      TPrimaryExpressionValue* pPrimaryExpressionValue =
        (TPrimaryExpressionValue*)p;

      if (pPrimaryExpressionValue->MacroExpansion != NULL)
      {
        fprintf(fp, "%s", pPrimaryExpressionValue->MacroExpansion);
      }
      else
      {

        if (pPrimaryExpressionValue->pExpressionOpt != NULL)
        {
          fprintf(fp, "(");
          b = TExpression_CodePrint(pPrimaryExpressionValue->pExpressionOpt, "expr", b, fp);
          fprintf(fp, ")");
        }
        else
        {
          fprintf(fp, "%s", pPrimaryExpressionValue->lexeme);
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
          fprintf(fp, "sizeof (");
          b = TTypeQualifier_CodePrint(&pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
          b = TTypeSpecifier_CodePrint(pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
          b = TDeclarator_CodePrint(&pTUnaryExpressionOperator->TypeName.Declarator, b, fp);
          fprintf(fp, ")");

        }
        else
        {
          fprintf(fp, "sizeof ");
          b = TExpression_CodePrint(pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);
          fprintf(fp, "");
        }
      }
      else
      {
        fprintf(fp, "%s", TokenToString(((TBinaryExpression*)p)->token));
        b = TExpression_CodePrint(pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);

      }


    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;

      fprintf(fp, "(");
      b = TTypeQualifier_CodePrint(&pCastExpressionType->TypeName.Specifiers.TypeQualifiers, false, fp);
      b = TTypeSpecifier_CodePrint(pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
      b = TDeclarator_CodePrint(&pCastExpressionType->TypeName.Declarator, b, fp);
      fprintf(fp, ")");
      b = TExpression_CodePrint(pCastExpressionType->pExpression, "expr", b, fp);
    }
    break;

  default:

    ASSERT(false);
  }


  return b;
}



static   bool TEnumerator_CodePrint(TEnumerator* pTEnumerator, bool b, FILE* fp)
{

  fprintf(fp, "%s", pTEnumerator->Name);

  if (pTEnumerator->pExpression)
  {
    fprintf(fp, " = ");
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

static bool TEnumSpecifier_CodePrint(TEnumSpecifier* p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, " enum ");
  fprintf(fp, " %s", p->Name);
  fprintf(fp, "\n{\n");

  for (size_t i = 0; i < p->EnumeratorList.size; i++)
  {
    TEnumerator *pTEnumerator = p->EnumeratorList.pItems[i];

    TEnumerator_CodePrint(pTEnumerator, false, fp);

    if (i + 1 < p->EnumeratorList.size)
      fprintf(fp, ",\n");
    else
      fprintf(fp, "\n");

  }


  fprintf(fp, "}");
  return true;
}


static bool TStructUnionSpecifier_CodePrint(TStructUnionSpecifier* p, bool b, FILE* fp)
{
  b = true;

  if (p->bIsStruct)
    fprintf(fp, " struct ");

  else
    fprintf(fp, " union");

  fprintf(fp, " %s", p->Name);
  //struct point pt = {}
  if (p->StructDeclarationList.size > 0)
  {
    fprintf(fp, " {\n");

    for (size_t i = 0; i < p->StructDeclarationList.size; i++)
    {
      TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
      b = TAnyStructDeclaration_CodePrint(pStructDeclaration, b, fp);
      fprintf(fp, ";\n");
    }


    fprintf(fp, "}");
  }

  return true;
}

static bool TSingleTypeSpecifier_CodePrint(TSingleTypeSpecifier* p, bool b, FILE* fp)
{

  b = true;

  int i = 0;

  if (p->bIsVoid)
  {
    fprintf(fp, " void");
    b = true;
  }

  if (p->bIsUnsigned)
  {
    fprintf(fp, " unsigned");
    b = true;
  }

  if (p->bIsBool)
  {
    //fprintf(fp, " _Bool");
    fprintf(fp, " bool");
    b = true;
  }

  if (p->bIsChar)
  {
    fprintf(fp, " char");
    b = true;
  }

  if (p->bIsShort)
  {
    fprintf(fp, " short");
    b = true;
  }

  for (int j = 0; j < p->nLong; j++)
  {
    fprintf(fp, " long");
    b = true;
  }

  if (p->bIsInt)
  {
    fprintf(fp, " int");
    b = true;
  }

  if (p->bIsDouble)
  {
    fprintf(fp, " double");
    b = true;
  }

  if (p->bIsFloat)
  {
    fprintf(fp, " float");
    b = true;
  }

  if (p->bIsTypeDef)
  {
    fprintf(fp, " %s", p->TypedefName);
    b = true;
  }


  return b;
}

static bool TTypeSpecifier_CodePrint(TTypeSpecifier*  p, bool b, FILE* fp)
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

static bool TDesignator_CodePrint(TDesignator* p, bool b, FILE* fp)
{
  if (b)
    fprintf(fp, ",");

  fprintf(fp, "{");

  //
  if (p->Name)
  {
    //.identifier
    fprintf(fp, ".%s", p->Name);
  }

  else
  {
    //[constant-expression]
    TExpression_CodePrint(p->pExpression, "index", b, fp);
  }

  fprintf(fp, "}");
  return b;
}


static bool TInitializerList_CodePrint(TInitializerList*p, bool b, FILE* fp)
{

  b = false;
  fprintf(fp, "{");

  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      fprintf(fp, ",");

    TInitializerListItem* pItem = p->pItems[i];
    b = TInitializerListItem_CodePrint(pItem, b, fp);
  }

  fprintf(fp, "}");

  return true;
}

static bool TInitializerListType_CodePrint(TInitializerListType*p, bool b, FILE* fp)
{
  if (p->MacroExpansion != NULL)
  {
    fprintf(fp, "%s", p->MacroExpansion);
  }
  else
  {
    b = TInitializerList_CodePrint(&p->InitializerList, b, fp);
  }

  return true;
}

static bool TInitializer_CodePrint(TInitializer*  p, bool b, FILE* fp)
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


static bool TPointerList_CodePrint(TPointerList *p, bool b, FILE* fp)
{
  b = false;

  for (size_t i = 0; i < p->size; i++)
  {
    TPointer * pItem = p->pItems[i];
    b = TPointer_CodePrint(pItem, b, fp);
  }

  return true;
}

static bool TParameterList_CodePrint(TParameterList *p, bool b, FILE* fp)
{
  b = false;
  fprintf(fp, "(");

  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      fprintf(fp, ",");

    TParameterDeclaration * pItem = p->pItems[i];
    b = TParameterDeclaration_CodePrint(pItem, b, fp);
  }

  fprintf(fp, ")");
  return true;
}

static bool TDeclarator_PrintCore2(TDeclarator* p, bool b, FILE* fp)
{
  b = false;

  if (p->token == TK_LEFT_PARENTHESIS &&
    p->pParametersOpt == NULL)
  {
    // ( declarator ) 
    fprintf(fp, "(");
  }

  if (p->PointerList.size > 0)
  {
    b = TPointerList_CodePrint(&p->PointerList, b, fp);
  }



  b = TTypeQualifier_CodePrint(&p->Qualifiers, b, fp);

  if (p->Name != NULL)
  {
    fprintf(fp, " %s", p->Name);
  }

  if (p->pParametersOpt != NULL)
  {
    b = TParameterList_CodePrint(p->pParametersOpt, b, fp);
  }

  if (p->token == TK_LEFT_SQUARE_BRACKET)
  {
    //tem que revisar..isso fica no p->pDeclaratorOpt
    fprintf(fp, "[");
    b = TExpression_CodePrint(p->pExpression, "", b, fp);
    fprintf(fp, "]");

  }




  else
  {
    //fprintf(fp, "\"name\": null");
  }

  if (p->token == TK_LEFT_PARENTHESIS &&
    p->pParametersOpt == NULL)
  {
    // ( declarator ) 
    fprintf(fp, ")");
  }

  if (p->pDeclaratorOpt)
  {
    b = TDeclarator_PrintCore2(p->pDeclaratorOpt, b, fp);
  }



  return true;
}

static bool TDeclarator_CodePrint(TDeclarator* p, bool b, FILE* fp)
{
  TDeclarator_PrintCore2(p, b, fp);
  if (p->pInitializer != NULL)
  {
    fprintf(fp, " = ");
    b = TInitializer_CodePrint(p->pInitializer, b, fp);
  }
  return b;
}


static bool TDeclaratorList_CodePrint(TDeclaratorList *p, bool b, FILE* fp)
{
  b = false;


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      fprintf(fp, ",");

    TDeclarator* pItem = p->pItems[i];
    b = TDeclarator_CodePrint(pItem, b, fp);
  }


  return true;
}

static bool TStructDeclaration_CodePrint(TStructDeclaration* p, bool b, FILE* fp)
{
  b = TTypeQualifier_CodePrint(&p->Qualifier, false, fp);
  b = TTypeSpecifier_CodePrint(p->pSpecifier, b, fp);
  b = TDeclaratorList_CodePrint(&p->DeclaratorList, b, fp);
  return true;
}

static bool TAnyStructDeclaration_CodePrint(TAnyStructDeclaration* p, bool b, FILE* fp)
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

static bool StorageSpecifier_CodePrint(TStorageSpecifier* p, bool b, FILE* fp)
{

  if (p->bIsAuto)
  {
    fprintf(fp, " auto");
    b = true;
  }

  if (p->bIsExtern)
  {
    fprintf(fp, " extern");
    b = true;
  }

  if (p->bIsRegister)
  {
    fprintf(fp, " register");
    b = true;
  }

  if (p->bIsStatic)
  {
    fprintf(fp, " static");
    b = true;
  }




  if (p->bIsThread_local)
  {
    fprintf(fp, " [Thread_local]");
    b = true;
  }

  if (p->bIsTypedef)
  {
    fprintf(fp, " typedef");
    b = true;
  }

  return b;
}

static bool TFunctionSpecifier_CodePrint(TFunctionSpecifier* p, bool b, FILE* fp)
{
  if (p->bIsInline)
  {
    fprintf(fp, " inline");
    b = true;
  }
  if (p->bIsNoReturn)
  {
    fprintf(fp, " [noreturn]");
    b = true;
  }
  return b;
}



static bool TTypeQualifier_CodePrint(TTypeQualifier* p, bool b, FILE* fp)
{

  if (p->bIsAtomic)
  {
    fprintf(fp, " _Atomic");
    b = true;
  }

  if (p->bIsConst)
  {
    fprintf(fp, " const");
    b = true;
  }

  if (p->bIsRestrict)
  {
    fprintf(fp, " restrict");
    b = true;
  }
  if (p->bIsVolatile)
  {
    fprintf(fp, " volatile");
    b = true;
  }
  return b;
}

static bool TPointer_CodePrint(TPointer* pPointer, bool b, FILE* fp)
{
  if (pPointer->bPointer)
  {
    fprintf(fp, "*");
  }
  TTypeQualifier_CodePrint(&pPointer->Qualifier, false, fp);

  return true;
}

static bool TDeclarationSpecifiers_CodePrint(TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, FILE* fp)
{
  b = TFunctionSpecifier_CodePrint(&pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
  b = StorageSpecifier_CodePrint(&pDeclarationSpecifiers->StorageSpecifiers, b, fp);
  b = TTypeQualifier_CodePrint(&pDeclarationSpecifiers->TypeQualifiers, b, fp);
  b = TTypeSpecifier_CodePrint(pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
  return b;
}

static bool TDeclaration_CodePrint(TDeclaration* p,
  bool b,
  FILE* fp)
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

  b = TDeclaratorList_CodePrint(&p->Declarators, b, fp);

  if (p->pCompoundStatementOpt != NULL)
  {
    TCompoundStatement_CodePrint(p->pCompoundStatementOpt, b, fp);
  }
  else
  {
    fprintf(fp, ";");
  }

  if (p->PreprocessorAndCommentsString.size > 0)
  {
    fprintf(fp, "\n");
    fprintf(fp, p->PreprocessorAndCommentsString.c_str);
  }

  return true;
}


static bool TParameterDeclaration_CodePrint(TParameterDeclaration* p, bool b, FILE* fp)
{

  b = TDeclarationSpecifiers_CodePrint(&p->Specifiers, false, fp);


  b = TDeclarator_CodePrint(&p->Declarator, b, fp);

  return b;
}

static bool TAnyDeclaration_CodePrint(TAnyDeclaration *pDeclaration, bool b, FILE* fp)
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

static bool TDesignatorList_CodePrint(TDesignatorList *p, bool b, FILE* fp)
{
  b = false;


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      fprintf(fp, ",");

    TDesignator* pItem = p->pItems[i];
    b = TDesignator_CodePrint(pItem, b, fp);
  }


  return true;
}


static bool TInitializerListItem_CodePrint(TInitializerListItem* p, bool b, FILE* fp)
{

  b = false;

  if (p->pDesignatorList)
  {
    b = TDesignatorList_CodePrint(p->pDesignatorList, b, fp);
  }

  b = TInitializer_CodePrint(p->pInitializer, b, fp);

  return true;
}


static bool TDeclarations_CodePrint(TDeclarations *p, bool b, FILE* fp)
{
  b = false;


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      fprintf(fp, ",");

    TAnyDeclaration* pItem = p->pItems[i];
    b = TAnyDeclaration_CodePrint(pItem, b, fp);

  }

  return true;
}

/*
static void TProgram_PrintToFile(TProgram* pProgram,
                        const char* fileName)
{
  FILE * fp = fopen(fileName, "w");
  TDeclarations_CodePrint(&pProgram->Declarations, false, fp);
  fclose(fp);
}*/


static void TProgram_PrintFiles(TProgram* pProgram,
  FILE* fp,
  const char* userpath)
{
  //TODO tem que ter um teste especial..

  //o arqquivo externo que foi incluido por um aquivo local
  //deve ser incluido..se ele foi incluido por outro nao.
  //tem que marcar se foi incluido por um da lista de includes e nao incluir

  fprintf(fp, "/*external files*/\n");
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
		  fprintf(fp, "#include <%s>\n", pFile->IncludePath);
	  }
	  else
	  {
		  fprintf(fp, "#include \"%s\"\n", pFile->IncludePath);
	  }
      
    }
  }
  fprintf(fp, "\n");
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

  TProgram_PrintFiles(pProgram, fp, inputFileName);

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
      b = TAnyDeclaration_CodePrint(pItem, b, fp);
      fprintf(fp, "\n\n");
      k++;
    }
  }

  fclose(fp);
}


