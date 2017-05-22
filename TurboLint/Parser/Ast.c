#include "Ast.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

void TCompoundStatement_Destroy(TCompoundStatement *p)
{
  ArrayT_Destroy(TBlockItem, &p->BlockItemList);
}

void TLabeledStatement_Destroy(TLabeledStatement *p)
{
  TStatement_Delete(p->pStatementOpt);
  String_Destroy(&p->Identifier);
  TExpression_Delete(p->pExpression);
}

void TForStatement_Destroy(TForStatement *p)
{
  TAnyDeclaration_Delete(p->pInitDeclarationOpt);
  TExpression_Delete(p->pExpression1);
  TExpression_Delete(p->pExpression2);
  TExpression_Delete(p->pExpression3);
  TStatement_Delete(p->pStatement);
}

void TWhileStatement_Destroy(TWhileStatement *p)
{
  TExpression_Delete(p->pExpression);
  TStatement_Delete(p->pStatement);
}

void TReturnStatement_Destroy(TReturnStatement *p)
{
  TExpression_Delete(p->pExpression);
}

void TDoStatement_Destroy(TDoStatement *p)
{
  TExpression_Delete(p->pExpression);
  TStatement_Delete(p->pStatement);
}

void TExpressionStatement_Destroy(TExpressionStatement *p)
{
  TExpression_Delete(p->pExpression);
}

void TJumpStatement_Destroy(TJumpStatement *p)
{
  TExpression_Delete(p->pExpression);
}

void TAsmStatement_Destroy(TAsmStatement *p)
{
  p->Type.type = TypeNull;
}

void TSwitchStatement_Destroy(TSwitchStatement *p)
{
  TExpression_Delete(p->pConditionExpression);
  TStatement_Delete(p->pExpression);
}

void TIfStatement_Destroy(TIfStatement *p)
{
  TExpression_Delete(p->pConditionExpression);
  TStatement_Delete(p->pStatement);
  TStatement_Delete(p->pElseStatement);
}

void TStatement_Destroy(TStatement* p)
{
  switch (p->type)
  {
  case TExpressionStatement_ID:
    TExpressionStatement_Destroy((TExpressionStatement*)p);
    break;
  case TSwitchStatement_ID:
    TSwitchStatement_Destroy((TSwitchStatement*)p);
    break;
  case TLabeledStatement_ID:
    TLabeledStatement_Destroy((TLabeledStatement*)p);
    break;
  case TForStatement_ID:
    TForStatement_Destroy((TForStatement*)p);
    break;
  case TJumpStatement_ID:
    TJumpStatement_Destroy((TJumpStatement*)p);
    break;
  case TAsmStatement_ID:
    TAsmStatement_Destroy((TAsmStatement*)p);
    break;
  case TCompoundStatement_ID:
    TCompoundStatement_Destroy((TCompoundStatement*)p);
    break;
  case TIfStatement_ID:
    TIfStatement_Destroy((TIfStatement*)p);
    break;
  case TDoStatement_ID:
    TDoStatement_Destroy((TDoStatement*)p);
    break;
  case TReturnStatement_ID:
    TReturnStatement_Destroy((TReturnStatement*)p);
    break;
  default:
    ASSERT(false);
    break;
  }
}

void TBlockItem_Destroy(TBlockItem* p)
{

  switch (p->type)
  {
  case TDeclaration_ID:
    TDeclaration_Destroy((TDeclaration*)p);
    break;
  case TJumpStatement_ID:
    TJumpStatement_Destroy((TJumpStatement*)p);
    break;
  case TAsmStatement_ID:
    TAsmStatement_Destroy((TAsmStatement*)p);
    break;
  case TSwitchStatement_ID:
    TSwitchStatement_Destroy((TSwitchStatement*)p);
    break;
  case TExpressionStatement_ID:
    TExpressionStatement_Destroy((TExpressionStatement*)p);
    break;
  case TCompoundStatement_ID:
    TCompoundStatement_Destroy((TCompoundStatement*)p);
    break;
  case TLabeledStatement_ID:
    TLabeledStatement_Destroy((TLabeledStatement*)p);
    break;
  case TForStatement_ID:
    TForStatement_Destroy((TForStatement*)p);
    break;
  case TWhileStatement_ID:
    TWhileStatement_Destroy((TWhileStatement*)p);
    break;
  case TIfStatement_ID:
    TIfStatement_Destroy((TIfStatement*)p);
    break;
  case TReturnStatement_ID:
    TReturnStatement_Destroy((TReturnStatement*)p);
    break;
  case TDoStatement_ID:
    TDoStatement_Destroy((TDoStatement*)p);
    break;
    //Statement
  default:
    ASSERT(false);
    break;
  }

}

void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue* p)
{
  TExpression_Delete(p->pExpressionOpt);
  String_Destroy(&p->lexeme);
}

void TPostfixExpressionCore_Destroy(TPostfixExpressionCore* p)
{
  TInitializerList_Destroy(&p->InitializerList);
  String_Destroy(&p->Identifier);
  String_Destroy(&p->lexeme);
  TExpression_Delete(p->pExpressionLeft);
  TExpression_Delete(p->pExpressionRight);
  TParameterDeclaration_Delete(p->pTypeName);
}

void TBinaryExpression_Destroy(TBinaryExpression* p)
{
  TExpression_Delete(p->pExpressionLeft);
  TExpression_Delete(p->pExpressionRight);
}

void TUnaryExpressionOperator_Destroy(TUnaryExpressionOperator* p)
{
  TExpression_Delete(p->pExpressionLeft);
  TParameterDeclaration_Destroy(&p->TypeName);
  // TExpression_Delete(p->pExpressionRight);
}

void TCastExpressionType_Destroy(TCastExpressionType* p)
{
  TExpression_Delete(p->pExpression);
  TParameterDeclaration_Destroy(&p->TypeName);
}

void TTernaryExpression_Destroy(TTernaryExpression* p)
{
  TExpression_Delete(p->pExpressionLeft);
  TExpression_Delete(p->pExpressionMiddle);
  TExpression_Delete(p->pExpressionRight);
}

void TExpression_Destroy(TExpression* p)
{
  switch (p->type)
  {
    CASE(TPrimaryExpressionValue) :
      TPrimaryExpressionValue_Destroy((TPrimaryExpressionValue*)p);
    break;
    CASE(TPostfixExpressionCore) :
      TPostfixExpressionCore_Destroy((TPostfixExpressionCore*)p);
    break;
    CASE(TBinaryExpression) :
      TBinaryExpression_Destroy((TBinaryExpression*)p);
    break;
    CASE(TUnaryExpressionOperator) :
      TUnaryExpressionOperator_Destroy((TUnaryExpressionOperator*)p);
    break;
    CASE(TCastExpressionType) :
      TCastExpressionType_Destroy((TCastExpressionType*)p);
    break;

    CASE(TTernaryExpression) :
      TTernaryExpression_Destroy((TTernaryExpression*)p);
    break;

  default:
    ASSERT(false);
    break;
  }

}


void TStaticAssertDeclaration_Destroy(TStaticAssertDeclaration* p)
{
  p->Type.type = TypeNull;
  TExpression_Delete(p->pConstantExpression);
}

void TEnumerator_Destroy(TEnumerator* p)
{
  String_Destroy(&p->Name);
  TExpression_Delete(p->pExpression);
}

void TEnumSpecifier_Destroy(TEnumSpecifier* p)
{
  String_Destroy(&p->Name);
  List_Destroy(TEnumerator, &p->EnumeratorList);
}

void TStructUnionSpecifier_Destroy(TStructUnionSpecifier* p)
{
  String_Destroy(&p->Name);
  ArrayT_Destroy(TAnyStructDeclaration, &p->StructDeclarationList);
}

void TSingleTypeSpecifier_Destroy(TSingleTypeSpecifier* p)
{
  String_Destroy(&p->TypedefName);
}


void TTypeSpecifier_Destroy(TTypeSpecifier* p)
{
  switch (p->type)
  {
  case TSingleTypeSpecifier_ID:
    TSingleTypeSpecifier_Destroy((TSingleTypeSpecifier*)p);
    break;
  case TEnumSpecifier_ID:
    TEnumSpecifier_Destroy((TEnumSpecifier*)p);
    break;
  case TStructUnionSpecifier_ID:
    TStructUnionSpecifier_Destroy((TStructUnionSpecifier*)p);
    break;
  default:
    ASSERT(false);
    break;
  }
}

void TDeclarator_Destroy(TDeclarator* p)
{
  List_Destroy(TPointer, &p->PointerList);
  TDirectDeclarator_Delete(p->pDirectDeclarator);
}

void TInitDeclarator_Destroy(TInitDeclarator* p)
{
  //nao deletar aqui
  //TInitDeclarator_Delete(p->pInitDeclaratorNext);
  TDeclarator_Delete(p->pDeclarator);
  TInitializer_Delete(p->pInitializer);
}



void TDirectDeclarator_Destroy(TDirectDeclarator* p)
{
  String_Destroy(&p->Identifier);
  //TParameterList_Delete(p->pParametersOpt);
  //T/PointerList_Destroy(&p->PointerList);
  TDeclarator_Delete(p->pDeclarator);
  //TInitializer_Delete(p->pInitializer);
  //TExpression_Delete(p->pExpression);
}


const char* TDeclarator_FindName(TDeclarator*   p)
{
  TDirectDeclarator* pDirectDeclarator = p->pDirectDeclarator;
  while (pDirectDeclarator != NULL)
  {
    if (pDirectDeclarator->Identifier != NULL)
      return pDirectDeclarator->Identifier;
    if (pDirectDeclarator->pDeclarator)
    {
      const char* name =
        TDeclarator_FindName(pDirectDeclarator->pDeclarator);
      if (name != NULL)
      {
        return name;
      }
    }
    pDirectDeclarator =
      pDirectDeclarator->pDirectDeclarator;
  }
  return NULL;
}

const char* TInitDeclarator_FindName(TInitDeclarator* p)
{
  ASSERT(p->pDeclarator != NULL);
  return TDeclarator_FindName(p->pDeclarator);
}



void TAlignmentSpecifier_Destroy(TAlignmentSpecifier* p)
{
  String_Destroy(&p->TypeName);
}



void TStructDeclaration_Destroy(TStructDeclaration* p)
{
  List_Destroy(TInitDeclarator, &p->DeclaratorList);
  TTypeSpecifier_Delete(p->pSpecifier);
  //TTypeQualifier_Destroy(&p->Qualifier);
}

void TAnyStructDeclaration_Destroy(TAnyStructDeclaration* p)
{
  switch (p->type)
  {
  case TStructDeclaration_ID:
    TStructDeclaration_Destroy((TStructDeclaration*)p);
    break;
  case TStaticAssertDeclaration_ID:
    TStaticAssertDeclaration_Destroy((TStaticAssertDeclaration*)p);
    break;
  default:
    ASSERT(false);
    break;
  }
}

bool TPointerList_IsPointer(TPointerList* pPointerlist)
{
  bool bIsPointer = false;
  ForEachListItem(TPointer, pItem, pPointerlist)
  {
    if (pItem->bPointer)
    {
      bIsPointer = true;
      break;
    }
  }
  return bIsPointer;
}

void TPointer_Destroy(TPointer* p)
{
  //p->Qualifier.
}

void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
  TAlignmentSpecifier_Destroy(&pDeclarationSpecifiers->AlignmentSpecifier);
  TTypeSpecifier_Delete(pDeclarationSpecifiers->pTypeSpecifierOpt);
}

TDeclarator* TDeclaration_FindDeclarator(TDeclaration*  p, const char* name)
{
  if (p == NULL)
  {
    return NULL;
  }
  TDeclarator*  pResult = NULL;

  ForEachListItem(TInitDeclarator, pInitDeclarator, &p->InitDeclaratorList)
  {
    if (pInitDeclarator->pDeclarator &&
      pInitDeclarator->pDeclarator->pDirectDeclarator &&
      pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier)
    {
      if (strcmp(pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier, name) == 0)
      {
        pResult = pInitDeclarator->pDeclarator;
        break;
      }
    }
  }
  return pResult;
}

/*
bool TDeclaration_Is_FunctionDeclaration(TDeclaration*  p)
{
  if (p != NULL && p->Declarators.size == 1)
  {
    if (p->Declarators.pItems[0]->pParametersOpt != NULL)
    {
      if (p->pCompoundStatementOpt == NULL)
      {
        return true;
      }
    }
  }
  return false;
}
*/
/*
const char* TDeclaration_GetFunctionThis(TDeclaration*  p)
{
  const char*  thisName = NULL;
  if (p != NULL && p->Declarators.size == 1)
  {
    if (p->Declarators.pItems[0]->pParametersOpt != NULL &&
        p->Declarators.pItems[0]->pParametersOpt->size >= 1)
    {
        thisName = p->Declarators.pItems[0]->pParametersOpt->pItems[0]->Declarator.Name;
    }
  }
  return thisName;
}
*/

bool TDeclaration_Is_FunctionDefinition(TDeclaration*  p)
{
  return p != NULL && p->pCompoundStatementOpt != NULL;
}

bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration* p)
{
  return
    TTypeSpecifier_As_TStructUnionSpecifier(p->Specifiers.pTypeSpecifierOpt) != NULL;
}

bool TDeclaration_Is_EnumDeclaration(TDeclaration* p)
{
  return
    TTypeSpecifier_As_TEnumSpecifier(p->Specifiers.pTypeSpecifierOpt) != NULL;
}


void TTemplateParameter_Destroy(TTemplateParameter* p)
{
  String_Destroy(&p->Name);
}

void TDeclaration_Destroy(TDeclaration* p)
{
  TCompoundStatement_Delete(p->pCompoundStatementOpt);
  TDeclarationSpecifiers_Destroy(&p->Specifiers);
  List_Destroy(TInitDeclarator, &p->InitDeclaratorList);
  List_Destroy(TTemplateParameter, &p->TemplateParameters);
}

void TParameterDeclaration_Swap(TParameterDeclaration* a, TParameterDeclaration* b)
{
  TParameterDeclaration temp = *a;
  *a = *b;
  *b = temp;
}

void TParameterDeclaration_Destroy(TParameterDeclaration* p)
{
  TDeclarator_Destroy(&p->Declarator);
  TDeclarationSpecifiers_Destroy(&p->Specifiers);
}


bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration* pAnyDeclaration)
{
  TDeclaration *  pDeclaration = TAnyDeclaration_As_TDeclaration(pAnyDeclaration);
  if (pDeclaration != NULL)
  {
    return TDeclaration_Is_StructOrUnionDeclaration(pDeclaration);
  }

  return false;
}

bool TAnyDeclaration_IsTypedef(TAnyDeclaration* pDeclaration)
{
  bool bResult = false;
  switch (pDeclaration->type)
  {
  case TDeclaration_ID:
  {
    TDeclaration* p = (TDeclaration*)pDeclaration;
    bResult = p->Specifiers.StorageSpecifiers.bIsTypedef;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
  return bResult;
}

int TAnyDeclaration_GetFileIndex(TAnyDeclaration* pDeclaration)
{
  int result = -1;
  switch (pDeclaration->type)
  {
  case TDeclaration_ID:
    result = ((TDeclaration*)pDeclaration)->FileIndex;
    break;
  case TStaticAssertDeclaration_ID:
    break;
  default:
    ASSERT(false);
    break;
  }
  return result;
}
void TAnyDeclaration_Destroy(TAnyDeclaration* pDeclaration)
{
  switch (pDeclaration->type)
  {
  case TDeclaration_ID:
    TDeclaration_Destroy((TDeclaration*)pDeclaration);
    break;
  default:
    ASSERT(false);
    break;
  }
}


void TDesignator_Destroy(TDesignator* p)
{
  TExpression_Delete(p->pExpression);
  String_Destroy(&p->Name);
}

void  TInitializerListType_Destroy(TInitializerListType* pTInitializerListType)
{
  TInitializerList_Destroy(&pTInitializerListType->InitializerList);
}

void TInitializer_Destroy(TInitializer* p)
{
  if (p->type == TInitializerListType_ID)
  {
    TInitializerListType_Destroy((TInitializerListType*)p);

  }
  else
  {
    TExpression_Destroy((TExpression*)p);
  }

}

void TInitializerListItem_Destroy(TInitializerListItem* p)
{
  List_Destroy(TDesignator, &p->DesignatorList);
  TInitializer_Delete(p->pInitializer);
}


Result DeclarationsMap_Add(DeclarationsMap* p, const char* name, TAnyDeclaration* pData)
{
  return MultiMap_Add(p, name, pData);
}

TDeclaration* DeclarationsMap_FindDeclaration(DeclarationsMap* p, const char* name)
{
  Bucket *  pBucket =
    MultiMap_FindBucket(p, name);
  if (pBucket)
  {
    for (size_t j = 0; j < pBucket->size; j++)
    {
      if (strcmp(pBucket->data[j]->key, name) == 0)
      {
        return TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);
      }
    }
  }
  return NULL;
}

TDeclaration* TProgram_FindDeclaration(TProgram* p, const char* name)
{
  return DeclarationsMap_FindDeclaration(&p->Symbols, name);
}

TDeclaration* TProgram_FindFunctionDeclaration(TProgram* p, const char* name)
{
  TDeclaration*  pDeclaration = NULL;


  Bucket *  pBucket =
    MultiMap_FindBucket(&p->Symbols, name);
  if (pBucket)
  {
    for (size_t j = 0; j < pBucket->size; j++)
    {
      if (strcmp(pBucket->data[j]->key, name) == 0)
      {
        TDeclaration*  pDeclaration0 =
          TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);

        if (pDeclaration0 != NULL /* &&
            pDeclaration0->pCompoundStatementOpt == NULL*/)
        {
          pDeclaration = pDeclaration0;
          break;
        }
      }
    }
  }
  return pDeclaration;
}


TDeclaration* TProgram_FindFunctionDefinition(TProgram* p, const char* name)
{
  TDeclaration*  pDeclaration = NULL;
  Bucket *  pBucket = MultiMap_FindBucket(&p->Symbols, name);
  if (pBucket)
  {
    for (size_t j = 0; j < pBucket->size; j++)
    {
      if (strcmp(pBucket->data[j]->key, name) == 0)
      {
        TDeclaration*  pDeclaration0 =
          TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);

        if (pDeclaration0 != NULL &&
          pDeclaration0->pCompoundStatementOpt != NULL)
        {
          pDeclaration = pDeclaration0;
          break;
        }
      }
    }
  }
  return pDeclaration;
}


//Retorna a declaracao final do tipo entrando em cada typedef. 
TDeclaration* TProgram_GetFinalTypeDeclaration(TProgram* p, const char* typeName)
{
  TDeclaration*  pDeclarationResult = NULL;
  for (;;)
  {
    Bucket *  pBucket =
      MultiMap_FindBucket(&p->Symbols, typeName);
    if (pBucket)
    {
      TDeclaration*  pDeclaration = NULL;
      for (size_t j = 0; j < pBucket->size; j++)
      {
        pDeclaration = NULL;
        if (strcmp(pBucket->data[j]->key, typeName) == 0)
        {
          pDeclaration = TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);
          if (pDeclaration != NULL &&
            pDeclaration->Specifiers.pTypeSpecifierOpt != NULL)
          {
            TSingleTypeSpecifier *  pSingleTypeSpecifier = TTypeSpecifier_As_TSingleTypeSpecifier(pDeclaration->Specifiers.pTypeSpecifierOpt);
            if (pSingleTypeSpecifier != NULL)
            {
              if (pSingleTypeSpecifier->bIsTypeDef)
              {
                typeName = pSingleTypeSpecifier->TypedefName;
                break;
              }
              else
              {
                //int etc..
                pDeclarationResult = pDeclaration;
                break;
              }
            }
            else
            {
              //enum or struct union
              pDeclarationResult = pDeclaration;
              break;
            }
          }//declaration
        }//key
      }//for
      if (pDeclarationResult != NULL)
      {
        break; //ok achou
      }

      if (pDeclaration == NULL)
      {
        break;
      }
    }
    else
    {
      break;
    }
  }//for
  return pDeclarationResult;
}

/*void TDeclarations_Init(TDeclarations* p)
{
  TDeclarations temp = TDECLARATIONS_INIT;
  *p = temp;
}*/

void TProgram_Destroy(TProgram * p)
{

  StrArray_Destroy(&p->MySourceDir);

  Map_Destroy(&p->EnumMap, NULL);
  ArrayT_Destroy(TAnyDeclaration, &p->Declarations);
  ArrayT_Destroy(TFile, &p->Files2);
  DeclarationsMap_Destroy(&p->Symbols);
  MacroMap_Destroy(&p->Defines);
}



///////////////////////////////////////////

static bool TPostfixExpressionCore_CodePrint2(TPostfixExpressionCore * p,
  int *pResult)
{

  int result = *pResult;

  if (p->pExpressionLeft)
  {
    int left;
    EvaluateConstantExpression(p->pExpressionLeft, &left);
  }

  //if (p->pInitializerList)
  {
    //falta imprimeir typename
    //TTypeName_Print*
    //b = TInitializerList_CodePrint(p->pInitializerList, b, fp);
  }

  switch (p->token)
  {
  case TK_FULL_STOP:
    //fprintf(fp, ".%s", p->Identifier);
    ASSERT(false);
    break;
  case TK_ARROW:
    //fprintf(fp, "->%s", p->Identifier);
    //b = true;
    ASSERT(false);
    break;

  case TK_LEFT_SQUARE_BRACKET:
  {
    int index;
    //fprintf(fp, "[");
    EvaluateConstantExpression(p->pExpressionRight, &index);
    //fprintf(fp, "]");
    ASSERT(false);
  }
  break;

  case TK_LEFT_PARENTHESIS:
  {
    EvaluateConstantExpression(p->pExpressionRight, &result);
  }
  break;

  case TK_PLUSPLUS:
    ASSERT(false);
    break;
  case TK_MINUSMINUS:
    ASSERT(false);
    break;
  }



  if (p->pNext)
  {
    int result2 = result;
    TPostfixExpressionCore_CodePrint2(p->pNext, &result2);
    result = result2;
  }

  return true;
}

//Criado para avaliacao do #if
//Tem que arrumar para fazer os casts do enum
bool EvaluateConstantExpression(TExpression *  p, int *pResult)
{
  int result = -987654321;

  if (p == NULL)
  {
    return false;
  }
  bool b = false;

  switch (p->type)
  {
    CASE(TBinaryExpression) :
    {
      TBinaryExpression* pBinaryExpression =
        (TBinaryExpression*)p;

      int left;
      b = EvaluateConstantExpression(pBinaryExpression->pExpressionLeft, &left);

      int right;
      b = EvaluateConstantExpression(pBinaryExpression->pExpressionRight, &right);

      switch (pBinaryExpression->token)
      {
      case TK_ASTERISK:
        result = (left * right);
        break;
      case TK_PLUS_SIGN:
        result = (left + right);
        break;
      case TK_HYPHEN_MINUS:
        result = (left - right);
        break;
      case TK_ANDAND:
        result = (left && right);
        break;
      case TK_OROR:
        result = (left || right);
        break;
      case TK_NOTEQUAL:
        result = (left != right);
        break;
      case TK_EQUALEQUAL:
        result = (left == right);
        break;
      case TK_GREATEREQUAL:
        result = (left >= right);
        break;
      case TK_LESSEQUAL:
        result = (left <= right);
        break;
      case TK_GREATER_THAN_SIGN:
        result = (left > right);
        break;
      case TK_LESS_THAN_SIGN:
        result = (left < right);
        break;
      case TK_AMPERSAND:
        result = (left & right);
        break;
      case TK_GREATERGREATER:
        result = (left >> right);
        break;
      case TK_LESSLESS:
        result = (left << right);
        break;
      case TK_VERTICAL_LINE:
        result = (left | right);
        break;
      default:
        //TODO ADD THE OPERADOR?
        ASSERT(false);
      }

      //if (pBinaryExpression->)
    }
    break;

    CASE(TTernaryExpression) :
    {
      int e1, e2, e3;
      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionLeft, &e1);

      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionMiddle, &e2);

      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionRight, &e3);
      ASSERT(false);
    }
    break;

    CASE(TPrimaryExpressionValue) :
    {
      TPrimaryExpressionValue* pPrimaryExpressionValue =
        (TPrimaryExpressionValue*)p;

      if (pPrimaryExpressionValue->pExpressionOpt != NULL)
      {
        b = EvaluateConstantExpression(pPrimaryExpressionValue->pExpressionOpt, &result);
      }
      else
      {
        switch (pPrimaryExpressionValue->token)
        {
        case TK_IDENTIFIER:
          result = 0; //para macro
          break;

        case TK_DECIMAL_INTEGER:
          result = atoi(pPrimaryExpressionValue->lexeme);
          break;

        case TK_HEX_INTEGER:
          result = strtol(pPrimaryExpressionValue->lexeme, NULL, 16);
          break;

        case TK_CHAR_LITERAL:
          if (pPrimaryExpressionValue->lexeme != NULL)
          {
            //vem com 'A'
            result = pPrimaryExpressionValue->lexeme[1];
          }
          else
          {
            result = 0;
          }
          break;
        default:
          ASSERT(0);
          break;
        }

      }
    }
    break;

    CASE(TPostfixExpressionCore) :
    {
      TPostfixExpressionCore* pPostfixExpressionCore =
        (TPostfixExpressionCore*)p;
      b = TPostfixExpressionCore_CodePrint2(pPostfixExpressionCore, &result);
      ASSERT(false);
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

          //b = TTypeQualifier_CodePrint2(&pTUnaryExpressionOperator->TypeName.qualifiers, false, fp);
          //b = TTypeSpecifier_CodePrint2(pTUnaryExpressionOperator->TypeName.pTypeSpecifier, b, fp);
          // b = TDeclarator_CodePrint(&pTUnaryExpressionOperator->TypeName.declarator, b, fp);


        }
        else
        {
          b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionLeft, &result);
        }
      }
      else
      {
        int localResult;
        b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionLeft, &localResult);
        switch (pTUnaryExpressionOperator->token)
        {
        case TK_EXCLAMATION_MARK:
          result = !localResult;
          break;
        default:
          ASSERT(false);
        }
      }


    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;


      //b = TTypeQualifier_CodePrint2(&pCastExpressionType->TypeName.qualifiers, false, fp);
      //b = TTypeSpecifier_CodePrint2(pCastExpressionType->TypeName.pTypeSpecifier, b, fp);
      //b = TDeclarator_CodePrint(&pCastExpressionType->TypeName.declarator, b, fp);


      EvaluateConstantExpression(pCastExpressionType->pExpression, &result);
      ASSERT(false);

    }
    break;

  default:
    ASSERT(false);
  }

  ASSERT(result != -987654321);
  *pResult = result;
  return b;
}

