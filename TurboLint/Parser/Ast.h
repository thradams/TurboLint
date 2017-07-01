#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "..\Base\Array.h"
#include "..\Base\List.h"
#include "..\Base\StringEx.h"
#include "Scanner.h"
#include "Macro.h"


#define CAST(FROM, TO) \
inline TO *  FROM##_As_##TO(FROM*  p)\
{\
if (p != NULL && p->type == TO##_ID)\
    return ( TO * )p;\
  return NULL;\
}\
inline FROM *  TO##_As_##FROM(TO*  p)\
{\
    return ( FROM * )p;\
}

#define CASTSAME(FROM, TO) \
inline TO * FROM##_As_##TO(FROM* p) { return p; }\
inline FROM * TO##_As_##FROM(TO* p) { return p; }


/*
   AST data structures
*/

typedef enum
{
	TypeNull,
	TDeclaration_ID,
	TStaticAssertDeclaration_ID,

	TSingleTypeSpecifier_ID,
	TEnumSpecifier_ID,
	TStructUnionSpecifier_ID,

	TStructDeclaration_ID,

	TCompoundStatement_ID,
	TExpressionStatement_ID,
	TSwitchStatement_ID,
	TLabeledStatement_ID,
	TForStatement_ID,
	TJumpStatement_ID,
	TAsmStatement_ID,
	TWhileStatement_ID,
	TDoStatement_ID,
	TIfStatement_ID,
	TReturnStatement_ID,
	TInitializerListType_ID,

	TPrimaryExpression_ID,
	TUnaryExpressionOperator_ID,
	TCastExpressionType_ID,
	TPrimaryExpressionValue_ID,
	TPostfixExpressionCore_ID,
	TBinaryExpression_ID,
	TTernaryExpression_ID
} Type;
#define CASE(T) case T##_ID


#define CREATETYPEOR(TYPE)\
  typedef TTypePointer TYPE ;\
  void TYPE##_Destroy(TYPE* p);\
inline void TYPE##_Delete(TYPE*  p)\
{\
  if (p)\
  {\
    TYPE##_Destroy(p);\
    free(p);\
  }\
}\
inline void TYPE##_DeleteVoid(void*  p)\
{\
  TYPE##_Delete((TYPE*)p);\
}


#define CREATETYPE(TYPE, INIT) inline TYPE*  TYPE##_Create()\
{\
  TYPE* p = (TYPE*)malloc(sizeof * p);\
  if (p)\
  {\
    TYPE temp_Moved = INIT;\
    *p =  temp_Moved;\
  }\
  else \
  {\
    _exit(EXIT_FAILURE); \
  }\
  return p;\
}\
void TYPE##_Destroy(TYPE* p);\
inline void TYPE##_Delete(TYPE*  p)\
{\
  if (p)\
  {\
    TYPE##_Destroy(p);\
    free(p);\
  }\
}\
inline void TYPE##_DeleteVoid(void*  p)\
{\
  TYPE##_Delete((TYPE*)p);\
}


typedef struct
{
    int FileIndex;
    int Line;
} TPosition;
#define TPOSITION_INIT {0,0}

typedef struct TTypePointer
{
  Type type;
  struct TTypePointer *pNext;
} TTypePointer;

typedef TTypePointer TExpression;

typedef struct
{
  TTypePointer Type;
  
  TExpression* pConstantExpression;
  TScannerItemList NodeClueList;

} TStaticAssertDeclaration;
#define TSTATIC_ASSERT_DECLARATION_INIT { {TStaticAssertDeclaration_ID} , NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TStaticAssertDeclaration, TSTATIC_ASSERT_DECLARATION_INIT)



typedef TTypePointer TStatement;
typedef TTypePointer TBlockItem;

CREATETYPEOR(TBlockItem)
CASTSAME(TBlockItem, TStatement)

typedef TTypePointer TAnyDeclaration;
CASTSAME(TBlockItem, TAnyDeclaration)
CREATETYPEOR(TAnyDeclaration)

typedef ArrayT(TBlockItem) TBlockItemList;

typedef struct
{
  TTypePointer Type;
  TBlockItemList BlockItemList;
  TScannerItemList NodeClueList;
} TCompoundStatement;

#define TCOMPOUNDSTATEMENT_INIT { {TCompoundStatement_ID}, ARRAYT_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TCompoundStatement, TCOMPOUNDSTATEMENT_INIT)

//////////////////



typedef struct
{
  TTypePointer Type;
  Tokens token;
  String lexeme;
  TExpression*  pExpressionOpt;  
  TScannerItemList NodeClueList;
} TPrimaryExpressionValue;

#define TPRIMARY_EXPRESSION_VALUE { {TPrimaryExpressionValue_ID}, TK_NONE, STRING_INIT, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TPrimaryExpressionValue, TPRIMARY_EXPRESSION_VALUE)


typedef  struct TInitializerListItem TInitializerListItem;
typedef List(TInitializerListItem) TInitializerList;

typedef struct TPostfixExpressionCoreTag
{
  TTypePointer Type;
  Tokens token;
  String lexeme;
  TExpression*  pExpressionLeft;
  TExpression*  pExpressionRight;
  
  //cast
  
  
  struct TPostfixExpressionCoreTag*  pNext;
  TInitializerList InitializerList;
  String Identifier;
  struct TParameterDeclaration* pTypeName; /*typename*/
  TScannerItemList NodeClueList;
} TPostfixExpressionCore;
#define TPOSTFIX_EXPRESSION_CORE { {TPostfixExpressionCore_ID}, TK_NONE, STRING_INIT, NULL, NULL, NULL, LIST_INIT, STRING_INIT, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TPostfixExpressionCore, TPOSTFIX_EXPRESSION_CORE)


typedef struct
{
  TTypePointer Type;
  Tokens token;
  TExpression*  pExpressionLeft;
  TExpression*  pExpressionRight;
  TPosition Position;
  TScannerItemList NodeClueList;

} TBinaryExpression;
#define TBINARYEXPRESSION_INIT { {TBinaryExpression_ID}, TK_NONE, NULL, NULL, TPOSITION_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TBinaryExpression, TBINARYEXPRESSION_INIT)

typedef struct
{
  TTypePointer Type;
  Tokens token;
  TExpression*  pExpressionLeft;
  TExpression*   pExpressionMiddle;
  TExpression*   pExpressionRight;
  TScannerItemList NodeClueList;
} TTernaryExpression;
#define TTERNARYEXPRESSION_INIT { {TTernaryExpression_ID}, TK_NONE, NULL, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TTernaryExpression, TTERNARYEXPRESSION_INIT)



CREATETYPEOR(TExpression)

typedef struct
{
	bool bIsConst;
	bool bIsRestrict;
	bool bIsVolatile;
	bool bIsAtomic;
	
	//type-qualifier-extensions 
	bool bIsOpt;
	bool bIsOwner;
	bool bIsDestructor;
	bool bIsMemDestructor;
	//
  TScannerItemList NodeClueList;
} TTypeQualifier;

#define TTYPE_QUALIFIER_INIT {false, false, false, false /*extensoes*/, false, false /**/, false, false, TSCANNERITEMLIST_INIT}

////////////////////////////

typedef struct
{
  TTypePointer Type;  
  TExpression *   pExpression;  
  TScannerItemList NodeClueList;
} TExpressionStatement;
#define TEXPRESSION_STATEMENT_INIT { {TExpressionStatement_ID}, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TExpressionStatement, TEXPRESSION_STATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  Tokens token;
  TExpression *  pExpression;
  TScannerItemList NodeClueList;
} TJumpStatement;

#define TJUMP_STATEMENT_INIT {{TJumpStatement_ID}, TK_NONE, NULL, TSCANNERITEMLIST_INIT }
CREATETYPE(TJumpStatement, TJUMP_STATEMENT_INIT)


typedef struct
{
  TTypePointer Type;
  TScannerItemList NodeClueList;
} TAsmStatement;

#define TASM_STATEMENT_INIT {{TAsmStatement_ID} , TSCANNERITEMLIST_INIT}
CREATETYPE(TAsmStatement, TASM_STATEMENT_INIT)


typedef struct
{
  TTypePointer Type;
  TAnyDeclaration*  pInitDeclarationOpt;
  TExpression*  pExpression1;
  TExpression* pExpression2;
  TExpression*  pExpression3;
  TStatement*  pStatement;
  TScannerItemList NodeClueList;
} TForStatement;

#define TFORSTATEMENT_INIT {{TForStatement_ID}, NULL, NULL, NULL, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TForStatement, TFORSTATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  TExpression*  pExpression;
  TStatement*  pStatement;
  TScannerItemList NodeClueList;
} TWhileStatement;

#define TWHILESTATEMENT_INIT { {TWhileStatement_ID}, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TWhileStatement, TWHILESTATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  TExpression*   pExpression;
  TScannerItemList NodeClueList;
} TReturnStatement;

#define TRETURN_STATEMENT_INIT { {TReturnStatement_ID}, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TReturnStatement, TRETURN_STATEMENT_INIT)


typedef struct
{
  TTypePointer Type;
  TExpression *   pExpression;
  TStatement*   pStatement;
  TScannerItemList NodeClueList;
} TDoStatement;
#define TDOSTATEMENT_INIT {{TDoStatement_ID}, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TDoStatement, TDOSTATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  
  TStatement *   pStatementOpt;
  TExpression *   pExpression;
  String Identifier;
  Tokens token;
  TScannerItemList NodeClueList;
} TLabeledStatement;

#define TLABEDSTATEMENT_INIT {{TLabeledStatement_ID},  NULL, NULL, STRING_INIT, TK_NONE, TSCANNERITEMLIST_INIT}
CREATETYPE(TLabeledStatement, TLABEDSTATEMENT_INIT)


typedef struct
{
  TTypePointer Type;
  TExpression *   pConditionExpression;
  TStatement*   pExpression;
  TScannerItemList NodeClueList;
} TSwitchStatement;

#define TSWITCH_STATEMENT { {TSwitchStatement_ID}, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TSwitchStatement, TSWITCH_STATEMENT)


typedef struct
{
  TTypePointer Type;
  TExpression*    pConditionExpression;
  TStatement*   pStatement;
  TStatement*   pElseStatement;
  TScannerItemList NodeClueList;
} TIfStatement;
#define TIFSTATEMENT_INIT { {TIfStatement_ID}, NULL, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TIfStatement, TIFSTATEMENT_INIT)



CREATETYPEOR(TStatement)
CAST(TStatement, TCompoundStatement)
CAST(TStatement, TExpressionStatement)
CAST(TStatement, TLabeledStatement)
CAST(TStatement, TJumpStatement)
CAST(TStatement, TIfStatement)
CAST(TStatement, TDoStatement)
CAST(TStatement, TForStatement)
CAST(TStatement, TAsmStatement)
CAST(TStatement, TReturnStatement)
CAST(TStatement, TWhileStatement)
CAST(TStatement, TSwitchStatement)



typedef struct TPointer
{
  TTypeQualifier Qualifier;
  bool bPointer;
  struct TPointer* pNext;
  TScannerItemList NodeClueList;
} TPointer;
#define TPOINTER_INIT {TTYPE_QUALIFIER_INIT, false, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TPointer, TPOINTER_INIT)


typedef List(TPointer) TPointerList;
bool TPointerList_IsPointer(TPointerList* pPointerlist);

typedef struct
{
  bool bIsInline;
  bool bIsNoReturn;
  TScannerItemList NodeClueList;
} TFunctionSpecifier;


#define TFUNCTION_SPECIFIER_INIT {false, false, TSCANNERITEMLIST_INIT}

typedef struct
{
  bool bIsTypedef;
  bool bIsExtern;
  bool bIsStatic;
  bool bIsThread_local;
  bool bIsAuto;
  bool bIsRegister;
  TScannerItemList NodeClueList;
} TStorageSpecifier;
#define TSTORAGE_SPECIFIER_INIT {false, false, false, false, false, false, TSCANNERITEMLIST_INIT}


typedef struct
{
  String TypeName;
  //_Alignas(type - name)
  //  _Alignas(constant - expression)
} TAlignmentSpecifier;
#define TALIGNMENT_SPECIFIER { STRING_INIT }

void TAlignmentSpecifier_Destroy(TAlignmentSpecifier* p);



typedef struct TEnumerator
{
  String Name;  
  TExpression*   pExpression;
  struct TEnumerator *pNext;
  TScannerItemList NodeClueList;
} TEnumerator;

#define TENUMERATOR_INIT { STRING_INIT , NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TEnumerator, TENUMERATOR_INIT)

typedef List(TEnumerator) TEnumeratorList;


typedef struct
{
  TTypePointer Type;
  String Name;
  TEnumeratorList EnumeratorList;
  TScannerItemList NodeClueList;
} TEnumSpecifier;

#define ENUM_SPECIFIER_INIT { {TEnumSpecifier_ID}, STRING_INIT, LIST_INIT, LIST_INIT}
CREATETYPE(TEnumSpecifier, ENUM_SPECIFIER_INIT)

typedef struct
{
  TTypePointer Type;

  bool bIsVoid;
  bool bIsChar;
  bool bIsShort;
  bool bIsInt;
  int nLong; //long long
  bool bIsFloat;
  bool bIsDouble;
  bool bIsSigned;
  bool bIsUnsigned;
  bool bIsBool;
  bool bIsComplex;

  bool bIsTypeDef;
  String TypedefName;

  TScannerItemList NodeClueList;
} TSingleTypeSpecifier;

#define TBUILDINTYPE_SPECIFIER_INIT { {TSingleTypeSpecifier_ID}, false, false, false, false, 0, false, false , false, false, false, false, false, STRING_INIT, LIST_INIT}
CREATETYPE(TSingleTypeSpecifier, TBUILDINTYPE_SPECIFIER_INIT)

typedef TTypePointer TTypeSpecifier;

typedef struct
{
  TStorageSpecifier StorageSpecifiers;
  TTypeSpecifier*   pTypeSpecifierOpt;
  TTypeQualifier TypeQualifiers;
  TFunctionSpecifier FunctionSpecifiers;
  TAlignmentSpecifier AlignmentSpecifier;
  TScannerItemList NodeClueList;
} TDeclarationSpecifiers;
#define TDECLARATION_SPECIFIERS_INIT { TSTORAGE_SPECIFIER_INIT, NULL, TTYPE_QUALIFIER_INIT, TFUNCTION_SPECIFIER_INIT, TALIGNMENT_SPECIFIER, TSCANNERITEMLIST_INIT}


void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers);

struct TParameterDeclaration;
typedef struct TParameterDeclaration TParameterDeclaration;
typedef List(TParameterDeclaration) TParameterList;

typedef struct TDesignator
{
  String Name;
  TExpression *  pExpression;
  struct TDesignator *pNext;
  TScannerItemList NodeClueList;
} TDesignator;

#define TDESIGNATOR_INIT { STRING_INIT , NULL, NULL,TSCANNERITEMLIST_INIT}
CREATETYPE(TDesignator, TDESIGNATOR_INIT)
typedef List(TDesignator) TDesignatorList;


typedef TTypePointer TInitializer;

typedef struct TInitializerListItem
{
  TDesignatorList  DesignatorList;
  TInitializer* pInitializer;
  struct TInitializerListItem* pNext;
  TScannerItemList NodeClueList;
} TInitializerListItem;

#define TINITIALIZER_LIST_ITEM_INIT { LIST_INIT , NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TInitializerListItem, TINITIALIZER_LIST_ITEM_INIT)

#define TInitializerList_Destroy(p) List_Destroy(TInitializerListItem, p)

typedef struct
{
  TTypePointer Type;
  TInitializerList InitializerList;
  TScannerItemList NodeClueList1; //{
  TScannerItemList NodeClueList2; //}
} TInitializerListType;

#define TINITIALIZER_LIST_TYPE_INIT {{TInitializerListType_ID}, LIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TInitializerListType, TINITIALIZER_LIST_TYPE_INIT)


CREATETYPEOR(TInitializer)
CAST(TInitializer, TInitializerListType)
CASTSAME(TInitializer, TExpression)

struct TDirectDeclarator;

typedef struct TDeclarator
{
  TPointerList PointerList;
  struct TDirectDeclarator* pDirectDeclarator;
  TScannerItemList NodeClueList;
} TDeclarator;

#define TDECLARATOR_INIT {LIST_INIT, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TDeclarator, TDECLARATOR_INIT)

//typedef struct TAbstractDeclarator
//{
  //TPointerList PointerList;
  //struct TAbstractDeclarator* pDirectDeclarator;
//} TAbstractDeclarator;

//#define TDECLARATOR_INIT {TPOINTERLIST_INIT, NULL}
//CREATETYPE(TDeclarator, TDECLARATOR_INIT)


typedef enum TDirectDeclaratorType
{
  TDirectDeclaratorTypeNone,
  TDirectDeclaratorTypeIdentifier,
  TDirectDeclaratorTypeDeclarator,
  TDirectDeclaratorTypeFunction,
  TDirectDeclaratorTypeArray,

}TDirectDeclaratorType;

typedef struct TDirectDeclarator
{
  String Identifier; //identifier
  TDeclarator* pDeclarator; //(declarator)
  struct TDirectDeclarator* pDirectDeclarator; //
  TPosition Position;
  TParameterList  Parameters;
  TExpression*   pExpression;
  TDirectDeclaratorType Type; //para diferenciar pois null nao basta []
  TScannerItemList NodeClueList;
} TDirectDeclarator;

#define TDIRECTDECLARATOR_INIT { STRING_INIT, NULL  ,NULL, TPOSITION_INIT, LIST_INIT, NULL, TDirectDeclaratorTypeNone, TSCANNERITEMLIST_INIT}
CREATETYPE(TDirectDeclarator, TDIRECTDECLARATOR_INIT)


typedef struct TInitDeclarator
{
  TDeclarator* pDeclarator;
  TInitializer* pInitializer;
  struct TInitDeclarator * pNext;
  TScannerItemList NodeClueList;
} TInitDeclarator;

#define TINITDECLARATOR_INIT {NULL, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TInitDeclarator, TINITDECLARATOR_INIT)

typedef TInitDeclarator TStructDeclarator;
typedef List(TInitDeclarator) TInitDeclaratorList;

const char* TDeclarator_FindName(TDeclarator* p);
const char* TInitDeclarator_FindName(TInitDeclarator* p);


typedef TInitDeclaratorList TStructDeclaratorList;


typedef struct
{
  TTypePointer Type;//= {TStructDeclaration_ID}
  TTypeSpecifier*   pSpecifier;
  TTypeQualifier Qualifier;
  TStructDeclaratorList DeclaratorList;
  TScannerItemList NodeClueList;
} TStructDeclaration;
#define TSTRUCT_DECLARATION_BASE_INIT {{TStructDeclaration_ID}, NULL, TTYPE_QUALIFIER_INIT, LIST_INIT, TSCANNERITEMLIST_INIT}

CREATETYPE(TStructDeclaration, TSTRUCT_DECLARATION_BASE_INIT)

//Mudar o nome p TAnyStructDeclaration
CREATETYPEOR(TAnyStructDeclaration)
CAST(TAnyStructDeclaration, TStructDeclaration)
CAST(TAnyStructDeclaration, TStaticAssertDeclaration)

typedef ArrayT(TAnyStructDeclaration) TStructDeclarationList;

typedef struct
{
  TTypePointer Type;
  TStructDeclarationList StructDeclarationList;
  String Name;
  bool bIsStruct;
  TScannerItemList NodeClueList;
} TStructUnionSpecifier;
#define TSTRUCT_UNION_SPECIFIER_INIT { {TStructUnionSpecifier_ID}, ARRAYT_INIT, STRING_INIT , true , LIST_INIT}

CREATETYPE(TStructUnionSpecifier, TSTRUCT_UNION_SPECIFIER_INIT)


CREATETYPEOR(TTypeSpecifier)
CAST(TTypeSpecifier, TSingleTypeSpecifier)
CAST(TTypeSpecifier, TEnumSpecifier)
CAST(TTypeSpecifier, TStructUnionSpecifier)


typedef struct TTemplateParameter
{
  String Name;
  struct TTemplateParameter *pNext;
} TTemplateParameter;
#define TTEMPLATEPARAMETER_INIT { STRING_INIT , NULL}
CREATETYPE(TTemplateParameter, TTEMPLATEPARAMETER_INIT)
//TTemplateParameterList

typedef List(TTemplateParameter) TTemplateParameterList;

typedef struct
{
  TTypePointer Type;
  TDeclarationSpecifiers Specifiers;
  TInitDeclaratorList InitDeclaratorList;

  //se for funcao
  TCompoundStatement* pCompoundStatementOpt;

  TTemplateParameterList TemplateParameters;
  int FileIndex;
  int Line;

  TScannerItemList NodeClueList;
  
  
} TDeclaration;
#define TFUNCVARDECLARATION_INIT { {TDeclaration_ID}, TDECLARATION_SPECIFIERS_INIT, LIST_INIT, NULL, LIST_INIT, -1, -1, TSCANNERITEMLIST_INIT}
CREATETYPE(TDeclaration, TFUNCVARDECLARATION_INIT)

void TDeclaration_Destroy(TDeclaration* p);

bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration* p);
bool TDeclaration_Is_FunctionDeclaration(TDeclaration* p);
bool TDeclaration_Is_FunctionDefinition(TDeclaration* p);
const char* TDeclaration_GetFunctionThis(TDeclaration* p);
bool TDeclaration_Is_EnumDeclaration(TDeclaration* p);
TDeclarator* TDeclaration_FindDeclarator(TDeclaration* p, const char* name);



CAST(TAnyDeclaration, TStaticAssertDeclaration)
CAST(TAnyDeclaration, TDeclaration)

bool TAnyDeclaration_IsTypedef(TAnyDeclaration* pDeclaration);
bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration* pDeclaration);
int TAnyDeclaration_GetFileIndex(TAnyDeclaration* pDeclaration);


typedef struct TParameterDeclaration
{
  TDeclarationSpecifiers Specifiers;
  TDeclarator Declarator;

  struct TParameterDeclaration* pNext;
  //Anotacoes in out opt geradas automaticamente?
  //para os parametros?
  //para o retorno opt?
  TScannerItemList NodeClueList;

} TParameterDeclaration;
#define TPARAMETER_DECLARATION_INIT { TDECLARATION_SPECIFIERS_INIT, TDECLARATOR_INIT, NULL, TSCANNERITEMLIST_INIT}
void TParameterDeclaration_Destroy(TParameterDeclaration* p);
void TParameterDeclaration_Swap(TParameterDeclaration* a, TParameterDeclaration* b);

CREATETYPE(TParameterDeclaration, TPARAMETER_DECLARATION_INIT)

typedef ArrayT(TAnyDeclaration) TDeclarations;


/////////
typedef MultiMap DeclarationsMap;
//Mapa de String - > TAnyDeclaration*
#define DECLARATIONSMAP_INIT MULTIMAP_INIT
Result DeclarationsMap_Init(DeclarationsMap* p, size_t nBuckets);
void DeclarationsMap_Destroy(DeclarationsMap* p);
TDeclaration* DeclarationsMap_FindDeclaration(DeclarationsMap* p, const char* name);
Result DeclarationsMap_Add(DeclarationsMap* p, const char* name, TAnyDeclaration* pData);


//Coleta o resultado do parser
typedef struct
{
  //declaracoes
  TDeclarations Declarations;

  //arquivos na qual declaracao tem indice
  TFileArray Files2;

  //Diretorios de codigo do usuario
  StrArray MySourceDir;

  //multimap dos simbolos
  DeclarationsMap Symbols;

  //Defines
  MacroMap Defines;

  Map EnumMap;

} TProgram;

#define TPROGRAM_INIT {ARRAYT_INIT, STRARRAY_INIT, STRARRAY_INIT, ARRAYT_INIT, MACROMAP_INIT, MAP_INIT}
void TProgram_Destroy(TProgram* p);
TDeclaration* TProgram_GetFinalTypeDeclaration(TProgram* p, const char* typeName);
TDeclaration* TProgram_FindDeclaration(TProgram* p, const char* name);


CAST(TBlockItem, TCompoundStatement)
CAST(TBlockItem, TExpressionStatement)
CAST(TBlockItem, TLabeledStatement)
CAST(TBlockItem, TJumpStatement)
CAST(TBlockItem, TIfStatement)
CAST(TBlockItem, TDoStatement)
CAST(TBlockItem, TForStatement)
CAST(TBlockItem, TAsmStatement)
CAST(TBlockItem, TReturnStatement)
CAST(TBlockItem, TWhileStatement)
CAST(TBlockItem, TSwitchStatement)

CAST(TBlockItem, TDeclaration)
CAST(TBlockItem, TStaticAssertDeclaration)



//Na verdade Typename nao precisa umas partes do
//TParameterDeclaration
//mas para simplificar vou usar o mesmo
typedef TParameterDeclaration TTypeName;
#define TTYPENAME_INIT TPARAMETER_DECLARATION_INIT


typedef struct
{
	TTypePointer Type;
	TExpression*   pExpression;
	TTypeName TypeName;
  TScannerItemList NodeClueList;
} TCastExpressionType;
#define TCAST_EXPRESSION_INIT { {TCastExpressionType_ID}, NULL , TTYPENAME_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TCastExpressionType, TCAST_EXPRESSION_INIT)




typedef struct
{
	TTypePointer Type;
	Tokens token;
	TExpression*   pExpressionLeft;
	TTypeName TypeName;
  TScannerItemList NodeClueList;
} TUnaryExpressionOperator;

#define TUNARY_EXPRESSION_OPERATOR_INIT { {TUnaryExpressionOperator_ID}, TK_NONE,  NULL, TTYPENAME_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TUnaryExpressionOperator, TUNARY_EXPRESSION_OPERATOR_INIT)


bool EvaluateConstantExpression(TExpression * p, int *pResult);


CAST(TExpression, TPrimaryExpressionValue)
CAST(TExpression, TBinaryExpression)
CAST(TExpression, TUnaryExpressionOperator)
CAST(TExpression, TPostfixExpressionCore)
CAST(TExpression, TCastExpressionType)

