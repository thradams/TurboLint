#include "CodePrint.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Base\Path.h"

static bool TInitializerList_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, TInitializerList*p, bool b, StrBuilder* fp);
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
static bool TInitializer_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, TInitializer* p, bool b, StrBuilder* fp);
static bool TPointer_CodePrint(TProgram* program, TPointer* pPointer, bool b, StrBuilder* fp);
static bool TParameterDeclaration_CodePrint(TProgram* program, TParameterDeclaration* p, bool b, StrBuilder* fp);
static bool TInitializerListItem_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, TInitializerListItem* p, bool b, StrBuilder* fp);




//static bool TInitializer_CodePrint(TInitializer*  p, bool b, StrBuilder* fp);

void BuildEnumSpecifierInitialization(TProgram* program,
  TEnumSpecifier* pTEnumSpecifier,
  StrBuilder* strBuilder)
{
  StrBuilder_Append(strBuilder, "0");
}


void BuildInitialization(TProgram* program,
  TTypeSpecifier* pTypeSpecifier,
  StrBuilder* strBuilder);

void BuildSingleTypeSpecifierInitialization(TProgram* program,
  TSingleTypeSpecifier* pSingleTypeSpecifier,
  StrBuilder* strBuilder)
{
  if (pSingleTypeSpecifier->bIsTypeDef)
  {
    TDeclaration * p = TProgram_GetFinalTypeDeclaration(program, pSingleTypeSpecifier->TypedefName);
    if (p)
    {
      BuildInitialization(program, p->Specifiers.pTypeSpecifierOpt, strBuilder);
    }
  }
  else
  {
    StrBuilder_Append(strBuilder, "0");
  }
}


void BuildStructUnionSpecifierInitialization(TProgram* program,
  TStructUnionSpecifier* pStructUnionSpecifier,
  StrBuilder* strBuilder)
{
  StrBuilder_Append(strBuilder, "{");
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
        StrBuilder_Append(strBuilder, ",");
      }

      FOR_EACH_INITDECLARATOR(pDeclarator, pStructDeclaration->DeclaratorList)
      {
        if (pDeclarator->pInitializer)
        {
          TInitializer_CodePrint(program, pStructDeclaration->pSpecifier,  pDeclarator->pInitializer, false, strBuilder);
        }
        else
        {
          BuildInitialization(program,
            pStructDeclaration->pSpecifier,
            strBuilder);
        }
        k++;
      }
    }
  }
  StrBuilder_Append(strBuilder, "}");
}

void BuildInitialization(TProgram* program,
  TTypeSpecifier* pTypeSpecifier,
  StrBuilder* strBuilder)
{
  switch (pTypeSpecifier->type)
  {
  case TSingleTypeSpecifier_ID:
    BuildSingleTypeSpecifierInitialization(program, (TSingleTypeSpecifier*)pTypeSpecifier, strBuilder);
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

static bool TCompoundStatement_CodePrint(TProgram* program, TCompoundStatement * p, bool b, StrBuilder* fp)
{

	//
  b = true;
  StrBuilder_Append(fp, "\n{\n");

  for (size_t j = 0; j < p->BlockItemList.size; j++)
  {
    TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
    TBlockItem_CodePrint(program, pBlockItem, j > 0, fp);
  }

  StrBuilder_Append(fp, "}\n");
  return b;
}


static bool TLabeledStatement_CodePrint(TProgram* program, TLabeledStatement * p, bool b, StrBuilder* fp)
{
  b = true;

  if (p->token == TK_CASE)
  {
    StrBuilder_Append(fp, "case ");
    if (p->pStatementOpt)
    {
      b = TExpression_CodePrint(program, p->pExpression, "", false, fp);
    }
    StrBuilder_Append(fp, ":\n");
    b = TStatement_CodePrint(program, p->pStatementOpt, false, fp);
  }
  else if (p->token == TK_DEFAULT)
  {
    StrBuilder_Append(fp, "default:\n");
    b = TStatement_CodePrint(program, p->pStatementOpt, false, fp);
  }
  else if (p->token == TK_IDENTIFIER)
  {
    StrBuilder_Append(fp, p->Identifier);
    StrBuilder_Append(fp, ":");
  }


  return b;
}

static bool TForStatement_CodePrint(TProgram* program, TForStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "for (");
  if (p->pInitDeclarationOpt) {
    TAnyDeclaration_CodePrint(program, p->pInitDeclarationOpt, b, fp);
    if (p->pExpression2)
    {
      b = TExpression_CodePrint(program, p->pExpression2, "expr2", true, fp);
    }
    StrBuilder_Append(fp, ";");
    b = TExpression_CodePrint(program, p->pExpression3, "expr3", b, fp);
  }
  else
  {
    b = TExpression_CodePrint(program, p->pExpression1, "expr1", true, fp);
    StrBuilder_Append(fp, ";");
    b = TExpression_CodePrint(program, p->pExpression2, "expr2", b, fp);
    StrBuilder_Append(fp, ";");
    b = TExpression_CodePrint(program, p->pExpression3, "expr3", b, fp);
  }


  StrBuilder_Append(fp, ")");

  b = TStatement_CodePrint(program, p->pStatement, false, fp);

  return b;
}


static bool TWhileStatement_CodePrint(TProgram* program, TWhileStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "while (");
  b = TExpression_CodePrint(program, p->pExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")");
  b = TStatement_CodePrint(program, p->pStatement, false, fp);
  return b;
}


static bool TReturnStatement_CodePrint(TProgram* program, TReturnStatement * p, bool b, StrBuilder* fp)
{
  StrBuilder_Append(fp, "return ");
  TExpression_CodePrint(program, p->pExpression, "return-statement", false, fp);
  StrBuilder_Append(fp, ";\n");
  return true;
}

static bool TDoStatement_CodePrint(TProgram* program, TDoStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "do {");
  b = TStatement_CodePrint(program, p->pStatement, false, fp);
  StrBuilder_Append(fp, "} while (");
  b = TExpression_CodePrint(program, p->pExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")\n");

  return b;
}


static bool TExpressionStatement_CodePrint(TProgram* program, TExpressionStatement * p, bool b, StrBuilder* fp)
{
  TExpression_CodePrint(program, p->pExpression, "", b, fp);
  StrBuilder_Append(fp, ";\n");
  return true;
}


static bool TJumpStatement_CodePrint(TProgram* program, TJumpStatement * p, bool b, StrBuilder* fp)
{


  StrBuilder_Append(fp,  TokenToString(((TBinaryExpression*)p)->token));
  if (p->pExpression)
  {

    b = TExpression_CodePrint(program, p->pExpression, "statement", false, fp);
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

static bool TAsmStatement_CodePrint(TProgram* program, TAsmStatement * p, bool b, StrBuilder* fp)
{
  StrBuilder_Append(fp, "\"type\":\"asm-statement\"");
  return true;
}

static bool TSwitchStatement_CodePrint(TProgram* program, TSwitchStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "switch (");
  b = TExpression_CodePrint(program, p->pConditionExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")");
  b = TStatement_CodePrint(program, p->pExpression, false, fp);
  return b;
}


static bool TIfStatement_CodePrint(TProgram* program, TIfStatement * p, bool b, StrBuilder* fp)
{
  b = true;
  StrBuilder_Append(fp, "if (");


  b = TExpression_CodePrint(program, p->pConditionExpression, "expr", false, fp);
  StrBuilder_Append(fp, ")");

  if (p->pStatement->type != TCompoundStatement_ID)
    StrBuilder_Append(fp, "\n");

  if (p->pStatement)
  {
    b = TStatement_CodePrint(program, p->pStatement, false, fp);
  }

  if (p->pElseStatement)
  {
    StrBuilder_Append(fp, "else\n");
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
    StrBuilder_Append(fp, "\n");
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
    TTypeSpecifier* pTypeSpecifier = NULL;
    if (p->pTypeName)
    {

      StrBuilder_Append(fp, "(");
      TParameterDeclaration_CodePrint(program, p->pTypeName, b, fp);
      StrBuilder_Append(fp, ")");

      pTypeSpecifier = p->pTypeName->Specifiers.pTypeSpecifierOpt;
      
    }
    //falta imprimeir typename
    //TTypeName_Print*
    b = TInitializerList_CodePrint(program, pTypeSpecifier, &p->InitializerList, b, fp);
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
    b = TExpression_CodePrint(program, p->pExpressionRight, "r", b, fp);
    StrBuilder_Append(fp, "]");
    break;

  case TK_LEFT_PARENTHESIS:
    StrBuilder_Append(fp, "(");
    b = TExpression_CodePrint(program, p->pExpressionRight, "r", b, fp);
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
    StrBuilder_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
    b = TExpression_CodePrint(program, ((TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
    break;

    CASE(TTernaryExpression) :
      b = TExpression_CodePrint(program, ((TTernaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
    StrBuilder_Append(fp, " ? ");
    b = TExpression_CodePrint(program, ((TTernaryExpression*)p)->pExpressionMiddle, "m-expr", b, fp);
    StrBuilder_Append(fp, " : ");
    b = TExpression_CodePrint(program, ((TTernaryExpression*)p)->pExpressionRight, "r-expr", b, fp);

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
          b = TExpression_CodePrint(program, pPrimaryExpressionValue->pExpressionOpt, "expr", b, fp);
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
          StrBuilder_Append(fp, "sizeof (");
          b = TTypeQualifier_CodePrint(program, &pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
          b = TTypeSpecifier_CodePrint(program, pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
          b = TDeclarator_CodePrint(program, &pTUnaryExpressionOperator->TypeName.Declarator, b, fp);
          StrBuilder_Append(fp, ")");

        }
        else
        {
          StrBuilder_Append(fp, "sizeof ");
          b = TExpression_CodePrint(program, pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);
          StrBuilder_Append(fp, "");
        }
      }
      else
      {
        StrBuilder_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
        b = TExpression_CodePrint(program, pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);

      }


    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;

      StrBuilder_Append(fp, "(");
      b = TTypeQualifier_CodePrint(program, &pCastExpressionType->TypeName.Specifiers.TypeQualifiers, false, fp);
      b = TTypeSpecifier_CodePrint(program, pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
      b = TDeclarator_CodePrint(program, &pCastExpressionType->TypeName.Declarator, b, fp);
      StrBuilder_Append(fp, ")");
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

  StrBuilder_Append(fp,  pTEnumerator->Name);

  if (pTEnumerator->pExpression)
  {
    StrBuilder_Append(fp, " = ");
    TExpression_CodePrint(program, pTEnumerator->pExpression, "expr", true, fp);

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
  StrBuilder_Append(fp, " enum ");
  StrBuilder_Append(fp, p->Name);
  StrBuilder_Append(fp, "\n{\n");

  
  ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
  {
  
    TEnumerator_CodePrint(program, pTEnumerator, false, fp);

    if (List_IsLastItem(&p->EnumeratorList, pTEnumerator))
    {
      StrBuilder_Append(fp, "\n");
    }
    else
    {
      //tem mais
      StrBuilder_Append(fp, ",\n");
    }        
  }


  StrBuilder_Append(fp, "}");
  return true;
}


static bool TStructUnionSpecifier_CodePrint(TProgram* program, TStructUnionSpecifier* p, bool b, StrBuilder* fp)
{
  b = true;

  if (p->bIsStruct)
    StrBuilder_Append(fp, " struct ");

  else
    StrBuilder_Append(fp, " union ");

  StrBuilder_Append(fp, p->Name);
  
  if (p->StructDeclarationList.size > 0)
  {
    StrBuilder_Append(fp, " {\n");

    for (size_t i = 0; i < p->StructDeclarationList.size; i++)
    {
      TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
      b = TAnyStructDeclaration_CodePrint(program, pStructDeclaration, b, fp);
      StrBuilder_Append(fp, ";\n");
    }

    StrBuilder_Append(fp, "}");
  }
 /* StrBuilder_Append(fp, "typedef struct ");
  StrBuilder_Append(fp, p->Name);
  StrBuilder_Append(fp, " ");
  StrBuilder_Append(fp, p->Name);
  StrBuilder_Append(fp, ";\n");

  StrBuilder_Append(fp, "#define ");
  StrBuilder_Append(fp, p->Name);
  StrBuilder_Append(fp, "_INIT ");
  
  StrBuilder_Append(fp, "\n");
  */

  return true;
}

static bool TSingleTypeSpecifier_CodePrint(TProgram* program, TSingleTypeSpecifier* p, bool b, StrBuilder* fp)
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
    TExpression_CodePrint(program, p->pExpression, "index", b, fp);
  }

  StrBuilder_Append(fp, "}");
  return b;
}


static bool TInitializerList_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, TInitializerList*p, bool b, StrBuilder* fp)
{

  b = false;

  if (List_HasOneItem(p) &&
      List_Back(p)->pInitializer == NULL &&
	  pTypeSpecifier != NULL)  
  {
    //a partir de {} e um tipo consegue gerar o final
    BuildInitialization(program, pTypeSpecifier, fp);
  }
  else
  {
    StrBuilder_Append(fp, "{");
	ForEachListItem(TInitializerListItem, pItem, p)
    {
      if (!List_IsFirstItem(p, pItem))
        StrBuilder_Append(fp, ",");

      b = TInitializerListItem_CodePrint(program, pTypeSpecifier, pItem, b, fp);
    }

    StrBuilder_Append(fp, "}");
  }
  

  return true;
}

static bool TInitializerListType_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, TInitializerListType*p, bool b, StrBuilder* fp)
{
  if (p->MacroExpansion != NULL)
  {
    StrBuilder_Append(fp, p->MacroExpansion);
  }
  else
  {
    b = TInitializerList_CodePrint(program, pTypeSpecifier, &p->InitializerList, b, fp);
  }

  return true;
}

static bool TInitializer_CodePrint(TProgram* program, TTypeSpecifier*  pTTypeSpecifier,
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
    b = TInitializerListType_CodePrint(program, pTTypeSpecifier, (TInitializerListType*)p, b, fp);
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
  StrBuilder_Append(fp, "(");

  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    TParameterDeclaration * pItem = p->pItems[i];
    b = TParameterDeclaration_CodePrint(program, pItem, b, fp);
  }

  StrBuilder_Append(fp, ")");
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

static bool TDeclarator_PrintCore2(TProgram* program, TDeclarator* p, bool b, StrBuilder* fp)
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
    StrBuilder_Append(fp, " ");
    StrBuilder_Append(fp, pDirectDeclarator->Identifier);
    b = true;
  }
  else  if (pDirectDeclarator->pDeclarator)
  {
    //( declarator )
    StrBuilder_Append(fp, "(");
    b = TDeclarator_CodePrint(program, pDirectDeclarator->pDeclarator, b, fp);
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
      b = TExpression_CodePrint(program, pDirectDeclarator->pExpression, "assignment-expression", b, fp);
    }
    StrBuilder_Append(fp, "]");
  }
  

  if (pDirectDeclarator->pParametersOpt)
  {
    //( parameter-type-list )
    //fprintf(fp, ",");
    //fprintf(fp, "\"parameter-type-list\":");
    TParameterList_CodePrint(program, pDirectDeclarator->pParametersOpt, b, fp);
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
    StrBuilder_Append(fp, " /* = ");
    TInitializer_CodePrint(program, NULL, p->pInitializer, b, fp);
    StrBuilder_Append(fp, " */");
  }
  return true;
}

static bool TStructDeclaratorList_CodePrint(TProgram* program, TStructDeclaratorList *p, bool b, StrBuilder* fp)
{
  b = false;


  int i = 0;
  FOR_EACH_INITDECLARATOR(pItem, *p)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");
    b = TStructDeclarator_CodePrint(program, pItem, b, fp);
    i++;
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

static bool TFunctionSpecifier_CodePrint(TProgram* program, TFunctionSpecifier* p, bool b, StrBuilder* fp)
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


static bool TTypeQualifier_CodePrint(TProgram* program, TTypeQualifier* p, bool b, StrBuilder* fp)
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

static bool TPointer_CodePrint(TProgram* program, TPointer* pPointer, bool b, StrBuilder* fp)
{
  if (pPointer->bPointer)
  {
    StrBuilder_Append(fp, "*");
  }
  TTypeQualifier_CodePrint(program, &pPointer->Qualifier, false, fp);

  return true;
}

static bool TDeclarationSpecifiers_CodePrint(TProgram* program, TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, StrBuilder* fp)
{
  b = TFunctionSpecifier_CodePrint( program, &pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
  b = StorageSpecifier_CodePrint( program, &pDeclarationSpecifiers->StorageSpecifiers, b, fp);
  b = TTypeQualifier_CodePrint(program, &pDeclarationSpecifiers->TypeQualifiers, b, fp);
  b = TTypeSpecifier_CodePrint(program, pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
  return b;
}

bool TInitDeclarator_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier,
  TInitDeclarator* p,
  bool b, StrBuilder* fp)
{
  b = false;
  b = TDeclarator_CodePrint(program, p->pDeclarator, b, fp);
  if (p->pInitializer)
  {    
    StrBuilder_Append(fp, " = ");
    b = TInitializer_CodePrint(program, pTypeSpecifier, p->pInitializer, b, fp);          
  }
  return true;
}

//bool TInitDeclarator_CodePrint(TInitDeclarator* p, bool b, StrBuilder* fp);

bool TInitDeclaratorList_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier,
      TInitDeclaratorList *p,
  bool b,
  StrBuilder* fp)
{
  b = false;
  //fprintf(fp, "[");
  TInitDeclarator* pInitDeclarator = p->pInitDeclaratorHeap;
  int i = 0;
  while (pInitDeclarator)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

    b = TInitDeclarator_CodePrint(program, pTypeSpecifier, pInitDeclarator, b, fp);
    pInitDeclarator = pInitDeclarator->pInitDeclaratorNext;
    i++;
  }

//  fprintf(fp, "]");
  return true;
}

static bool TDeclaration_CodePrint(TProgram* program, TDeclaration* p,
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

  b = TInitDeclaratorList_CodePrint(program, p->Specifiers.pTypeSpecifierOpt,  &p->InitDeclaratorList, b, fp);

  if (p->pCompoundStatementOpt != NULL)
  {
    TCompoundStatement_CodePrint(program, p->pCompoundStatementOpt, b, fp);
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
      StrBuilder_Append(fp, ",");
    }
    b = TDesignator_CodePrint(program, pItem, b, fp);
  }


  return true;
}


static bool TInitializerListItem_CodePrint(TProgram* program, TTypeSpecifier* pTypeSpecifier, TInitializerListItem* p, bool b, StrBuilder* fp)
{

  b = false;

  if (!List_IsEmpty(&p->DesignatorList))
  {
    b = TDesignatorList_CodePrint(program, &p->DesignatorList, b, fp);
  }

  b = TInitializer_CodePrint(program, pTypeSpecifier, p->pInitializer, b, fp);

  return true;
}


static bool TDeclarations_CodePrint(TProgram* program, TDeclarations *p, bool b, StrBuilder* fp)
{
  b = false;


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
      StrBuilder_Append(fp, ",");

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
      b = TAnyDeclaration_CodePrint(pProgram, pItem, b, &sb);
      StrBuilder_Append(&sb, "\n\n");
      fprintf(fp, "%s", sb.c_str);
      StrBuilder_Clear(&sb);
      k++;
    }
  }
  StrBuilder_Destroy(&sb);
  fclose(fp);
}


