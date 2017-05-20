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

typedef struct
{
  Type type;
} TTypePointer;

typedef TTypePointer TExpression;

typedef struct
{
  TTypePointer Type;
  
  TExpression* pConstantExpression;
} TStaticAssertDeclaration;
#define TSTATIC_ASSERT_DECLARATION_INIT { {TStaticAssertDeclaration_ID} , NULL}
CREATETYPE(TStaticAssertDeclaration, TSTATIC_ASSERT_DECLARATION_INIT)




typedef TTypePointer TStatement;
typedef TTypePointer TBlockItem;

CREATETYPEOR(TBlockItem)
CASTSAME(TBlockItem, TStatement)

typedef TTypePointer TAnyDeclaration;
CASTSAME(TBlockItem, TAnyDeclaration)
CREATETYPEOR(TAnyDeclaration)


typedef struct
{
  TBlockItem** pItems;
  size_t size;
  size_t capacity;
} TBlockItemList;

#define TBLOCKITEMLIST_INIT {NULL, 0, 0}
ARRAYOF(TBlockItemList, TBlockItem)




typedef struct
{
  TTypePointer Type;
  TBlockItemList BlockItemList;
} TCompoundStatement;

#define TCOMPOUNDSTATEMENT_INIT { {TCompoundStatement_ID}, TBLOCKITEMLIST_INIT}
CREATETYPE(TCompoundStatement, TCOMPOUNDSTATEMENT_INIT)

//////////////////



typedef struct
{
  TTypePointer Type;
  Tokens token;
  String lexeme;
  TExpression*  pExpressionOpt;
  String MacroExpansion;
} TPrimaryExpressionValue;

#define TPRIMARY_EXPRESSION_VALUE { {TPrimaryExpressionValue_ID}, TK_NONE, STRING_INIT, NULL, STRING_INIT}
CREATETYPE(TPrimaryExpressionValue, TPRIMARY_EXPRESSION_VALUE)

//struct TInitializerList_;
  
typedef struct TPostfixExpressionCoreTag
{
  TTypePointer Type;
  Tokens token;
  String lexeme;
  TExpression*  pExpressionLeft;
  TExpression*  pExpressionRight;
  
  //cast
  
  
  struct TPostfixExpressionCoreTag*  pNext;
  struct TInitializerList_ *  pInitializerList;
  String Identifier;
  struct TParameterDeclaration* pTypeName; /*typename*/
} TPostfixExpressionCore;
#define TPOSTFIX_EXPRESSION_CORE { {TPostfixExpressionCore_ID}, TK_NONE, STRING_INIT, NULL, NULL, NULL, NULL, STRING_INIT}
CREATETYPE(TPostfixExpressionCore, TPOSTFIX_EXPRESSION_CORE)


typedef struct
{
  TTypePointer Type;
  Tokens token;
  TExpression*  pExpressionLeft;
  TExpression*  pExpressionRight;
  TPosition Position;
} TBinaryExpression;
#define TBINARYEXPRESSION_INIT { {TBinaryExpression_ID}, TK_NONE, NULL, NULL, TPOSITION_INIT}
CREATETYPE(TBinaryExpression, TBINARYEXPRESSION_INIT)

typedef struct
{
  TTypePointer Type;
  Tokens token;
  TExpression*  pExpressionLeft;
  TExpression*   pExpressionMiddle;
  TExpression*   pExpressionRight;
} TTernaryExpression;
#define TTERNARYEXPRESSION_INIT { {TTernaryExpression_ID}, TK_NONE, NULL, NULL, NULL}
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

} TTypeQualifier;

#define TTYPE_QUALIFIER_INIT {false, false, false, false /*extensoes*/, false, false /**/, false, false}

//#define TDECLARATOR_INIT {STRING_INIT, TTYPE_QUALIFIER_INIT, TPOINTERLIST_INIT, NULL, NULL, NULL, NULL, TK_NONE, TPOSITION_INIT}




////////////////////////////

typedef struct
{
  TTypePointer Type;  
  TExpression *   pExpression;  
} TExpressionStatement;
#define TEXPRESSION_STATEMENT_INIT { {TExpressionStatement_ID}, NULL}
CREATETYPE(TExpressionStatement, TEXPRESSION_STATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  Tokens token;
  TExpression *  pExpression;
} TJumpStatement;

#define TJUMP_STATEMENT_INIT {{TJumpStatement_ID}, TK_NONE, NULL }
CREATETYPE(TJumpStatement, TJUMP_STATEMENT_INIT)


typedef struct
{
  TTypePointer Type;

} TAsmStatement;

#define TASM_STATEMENT_INIT {{TAsmStatement_ID} }
CREATETYPE(TAsmStatement, TASM_STATEMENT_INIT)


typedef struct
{
  TTypePointer Type;
  TAnyDeclaration*  pInitDeclarationOpt;
  TExpression*  pExpression1;
  TExpression* pExpression2;
  TExpression*  pExpression3;
  TStatement*  pStatement;
} TForStatement;

#define TFORSTATEMENT_INIT {{TForStatement_ID}, NULL, NULL, NULL, NULL, NULL}
CREATETYPE(TForStatement, TFORSTATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  TExpression*  pExpression;
  TStatement*  pStatement;
} TWhileStatement;

#define TWHILESTATEMENT_INIT { {TWhileStatement_ID}, NULL, NULL}
CREATETYPE(TWhileStatement, TWHILESTATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  TExpression*   pExpression;
} TReturnStatement;

#define TRETURN_STATEMENT_INIT { {TReturnStatement_ID}, NULL}
CREATETYPE(TReturnStatement, TRETURN_STATEMENT_INIT)


typedef struct
{
  TTypePointer Type;
  TExpression *   pExpression;
  TStatement*   pStatement;
} TDoStatement;
#define TDOSTATEMENT_INIT {{TDoStatement_ID}, NULL, NULL}
CREATETYPE(TDoStatement, TDOSTATEMENT_INIT)

typedef struct
{
  TTypePointer Type;
  
  TStatement *   pStatementOpt;
  TExpression *   pExpression;
  String Identifier;
  Tokens token;
} TLabeledStatement;

#define TLABEDSTATEMENT_INIT {{TLabeledStatement_ID},  NULL, NULL, STRING_INIT, TK_NONE}
CREATETYPE(TLabeledStatement, TLABEDSTATEMENT_INIT)


typedef struct
{
  TTypePointer Type;
  TExpression *   pConditionExpression;
  TStatement*   pExpression;
} TSwitchStatement;

#define TSWITCH_STATEMENT { {TSwitchStatement_ID}, NULL, NULL}
CREATETYPE(TSwitchStatement, TSWITCH_STATEMENT)


typedef struct
{
  TTypePointer Type;
  TExpression*    pConditionExpression;
  TStatement*   pStatement;
  TStatement*   pElseStatement;
} TIfStatement;
#define TIFSTATEMENT_INIT { {TIfStatement_ID}, NULL, NULL, NULL}
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
} TPointer;
#define TPOINTER_INIT {TTYPE_QUALIFIER_INIT, false, NULL}
CREATETYPE(TPointer, TPOINTER_INIT)

typedef List(TPointer) TPointerList;
#define TPointerList_Destroy(p) List_Destroy(TPointer, (p))

typedef struct
{
  bool bIsInline;
  bool bIsNoReturn;
} TFunctionSpecifier;


#define TFUNCTION_SPECIFIER_INIT {false, false}

typedef struct
{
  bool bIsTypedef;
  bool bIsExtern;
  bool bIsStatic;
  bool bIsThread_local;
  bool bIsAuto;
  bool bIsRegister;
} TStorageSpecifier;
#define TSTORAGE_SPECIFIER_INIT {false, false, false, false, false, false}


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
} TEnumerator;

#define TENUMERATOR_INIT { STRING_INIT , NULL}
CREATETYPE(TEnumerator, TENUMERATOR_INIT)

typedef List(TEnumerator) TEnumeratorList;
#define TEnumeratorList_Destroy(p) List_Destroy(TEnumerator, p)
//typedef struct
//{
//  TEnumerator** pItems;
//  size_t size;
//  size_t capacity;
//} TEnumeratorList;
//#define ENUMERATOR_LIST_INIT {NULL, 0, 0}
//ARRAYOF(TEnumeratorList, TEnumerator)


typedef struct
{
  TTypePointer Type;
  String Name;
  TEnumeratorList EnumeratorList;
} TEnumSpecifier;

#define ENUM_SPECIFIER_INIT { {TEnumSpecifier_ID}, STRING_INIT, LIST_INIT}
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

  
} TSingleTypeSpecifier;

#define TBUILDINTYPE_SPECIFIER_INIT { {TSingleTypeSpecifier_ID}, false, false, false, false, 0, false, false , false, false, false, false, false, STRING_INIT}
CREATETYPE(TSingleTypeSpecifier, TBUILDINTYPE_SPECIFIER_INIT)

typedef TTypePointer TTypeSpecifier;

typedef struct
{
  TStorageSpecifier StorageSpecifiers;
  TTypeSpecifier*   pTypeSpecifierOpt;
  TTypeQualifier TypeQualifiers;
  TFunctionSpecifier FunctionSpecifiers;
  TAlignmentSpecifier AlignmentSpecifier;

} TDeclarationSpecifiers;
#define TDECLARATION_SPECIFIERS_INIT { TSTORAGE_SPECIFIER_INIT, NULL, TTYPE_QUALIFIER_INIT, TFUNCTION_SPECIFIER_INIT, TALIGNMENT_SPECIFIER}


void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers);

struct ParameterList_T;



typedef struct TDesignator
{
  String Name;
  TExpression *  pExpression;
  struct TDesignator *pNext;
} TDesignator;

#define TDESIGNATOR_INIT { STRING_INIT , NULL}
CREATETYPE(TDesignator, TDESIGNATOR_INIT)
typedef List(TDesignator) TDesignatorList;
#define TDesignatorList_Destroy(p) List_Destroy(TDesignator, p)

typedef TTypePointer TInitializer;

typedef struct
{
  TDesignatorList  DesignatorList;
  TInitializer* pInitializer;
} TInitializerListItem;
#define TINITIALIZER_LIST_ITEM_INIT { LIST_INIT , NULL}
CREATETYPE(TInitializerListItem, TINITIALIZER_LIST_ITEM_INIT)

typedef struct TInitializerList_
{
  TInitializerListItem** pItems;
  size_t size;
  size_t capacity;
} TInitializerList;
#define TINITIALIZER_LIST_INIT {NULL,0,0}
ARRAYOF(TInitializerList, TInitializerListItem)

typedef struct
{
  TTypePointer Type;
  TInitializerList InitializerList;
  String MacroExpansion;
} TInitializerListType;

#define TINITIALIZER_LIST_TYPE_INIT {{TInitializerListType_ID}, TINITIALIZER_LIST_INIT, STRING_INIT}
CREATETYPE(TInitializerListType, TINITIALIZER_LIST_TYPE_INIT)



CREATETYPEOR(TInitializer)
CAST(TInitializer, TInitializerListType)
CASTSAME(TInitializer, TExpression)

struct TDirectDeclarator;

typedef struct TDeclarator_S
{
  TPointerList PointerList;
  struct TDirectDeclarator* pDirectDeclarator;
} TDeclarator;

#define TDECLARATOR_INIT {LIST_INIT, NULL}
CREATETYPE(TDeclarator, TDECLARATOR_INIT)

//typedef struct TAbstractDeclarator
//{
  //TPointerList PointerList;
  //struct TAbstractDeclarator* pDirectDeclarator;
//} TAbstractDeclarator;

//#define TDECLARATOR_INIT {TPOINTERLIST_INIT, NULL}
//CREATETYPE(TDeclarator, TDECLARATOR_INIT)


typedef struct TDirectDeclarator
{
  String Identifier; //identifier
  TDeclarator* pDeclarator; //(declarator)
  struct TDirectDeclarator* pDirectDeclarator; //
  TPosition Position;
  struct ParameterList_T*  pParametersOpt;
  TExpression*   pExpression;
  Tokens token; //para diferenciar pois null nao basta []
} TDirectDeclarator;

#define TDIRECTDECLARATOR_INIT { STRING_INIT, NULL  ,NULL, TPOSITION_INIT, NULL, NULL, TK_NONE}
CREATETYPE(TDirectDeclarator, TDIRECTDECLARATOR_INIT)




typedef struct TInitDeclarator
{
  TDeclarator* pDeclarator;
  TInitializer* pInitializer;
  struct TInitDeclarator * pInitDeclaratorNext;
} TInitDeclarator;

#define TINITDECLARATOR_INIT {NULL, NULL, NULL}
CREATETYPE(TInitDeclarator, TINITDECLARATOR_INIT)

typedef TInitDeclarator TStructDeclarator;

typedef struct TInitDeclaratorList
{
  TInitDeclarator* pInitDeclaratorHeap;
  TInitDeclarator* pInitDeclaratorTail;
} TInitDeclaratorList;

#define TINITDECLARATORLIST_INIT {NULL, NULL}

CREATETYPE(TInitDeclaratorList, TINITDECLARATORLIST_INIT)

void TInitDeclaratorList_Push(TInitDeclaratorList* p, TInitDeclarator* pItem);

#define FOR_EACH_INITDECLARATOR(var, list) \
 for (TInitDeclarator * var = (list).pInitDeclaratorHeap; \
      var != NULL;\
      var = var->pInitDeclaratorNext)



const char* TDeclarator_FindName(TDeclarator* p);
const char* TInitDeclarator_FindName(TInitDeclarator* p);


typedef TInitDeclaratorList TStructDeclaratorList;
#define TSTRUCT_DECLARATOR_LIST_INIT TINITDECLARATORLIST_INIT
void TStructDeclaratorList_Push(TStructDeclaratorList* p, TInitDeclarator* pItem);

typedef struct
{
  TTypePointer Type;//= {TStructDeclaration_ID}
  TTypeSpecifier*   pSpecifier;
  TTypeQualifier Qualifier;
  TStructDeclaratorList DeclaratorList;

} TStructDeclaration;
#define TSTRUCT_DECLARATION_BASE_INIT {{TStructDeclaration_ID}, NULL, TTYPE_QUALIFIER_INIT, TSTRUCT_DECLARATOR_LIST_INIT}

CREATETYPE(TStructDeclaration, TSTRUCT_DECLARATION_BASE_INIT)

//Mudar o nome p TAnyStructDeclaration
CREATETYPEOR(TAnyStructDeclaration)
CAST(TAnyStructDeclaration, TStructDeclaration)
CAST(TAnyStructDeclaration, TStaticAssertDeclaration)

typedef struct
{
  TAnyStructDeclaration** pItems;
  size_t size;
  size_t capacity;
} TStructDeclarationList;
#define TSTRUCT_DECLARATION_LIST_INIT {NULL,0,0}

ARRAYOF(TStructDeclarationList, TAnyStructDeclaration)

typedef struct
{
  TTypePointer Type;
  TStructDeclarationList StructDeclarationList;
  String Name;
  bool bIsStruct;

} TStructUnionSpecifier;
#define TSTRUCT_UNION_SPECIFIER_INIT { {TStructUnionSpecifier_ID}, TSTRUCT_DECLARATION_LIST_INIT, STRING_INIT , true }

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

  StrBuilder PreprocessorAndCommentsString;

} TDeclaration;
#define TFUNCVARDECLARATION_INIT { {TDeclaration_ID}, TDECLARATION_SPECIFIERS_INIT, TINITDECLARATORLIST_INIT, NULL, LIST_INIT, -1, -1, STRBUILDER_INIT}
CREATETYPE(TDeclaration, TFUNCVARDECLARATION_INIT)
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

  //Anotacoes in out opt geradas automaticamente?
  //para os parametros?
  //para o retorno opt?
} TParameterDeclaration;
#define TPARAMETER_DECLARATION_INIT { TDECLARATION_SPECIFIERS_INIT, TDECLARATOR_INIT}
void TParameterDeclaration_Destroy(TParameterDeclaration* p);
void TParameterDeclaration_Swap(TParameterDeclaration* a, TParameterDeclaration* b);

CREATETYPE(TParameterDeclaration, TPARAMETER_DECLARATION_INIT)


typedef struct ParameterList_T
{
  TParameterDeclaration** pItems;
  size_t size;
  size_t capacity;
} TParameterList;
#define TPARAMETER_LIST_INIT {NULL, 0 , 0}
ARRAYOF(TParameterList, TParameterDeclaration)

typedef struct
{
  TAnyDeclaration** pItems;
  size_t size;
  size_t capacity;
} TDeclarations;
#define TDECLARATIONS_INIT {NULL, 0 , 0}
ARRAYOF(TDeclarations, TAnyDeclaration)
void TDeclarations_Init(TDeclarations* p);
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

#define TPROGRAM_INIT {TDECLARATIONS_INIT, STRARRAY_INIT, STRARRAY_INIT, DECLARATIONSMAP_INIT, MACROMAP_INIT, MAP_INIT}
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
} TCastExpressionType;
#define TCAST_EXPRESSION_INIT { {TCastExpressionType_ID}, NULL , TTYPENAME_INIT}
CREATETYPE(TCastExpressionType, TCAST_EXPRESSION_INIT)




typedef struct
{
	TTypePointer Type;
	Tokens token;
	TExpression*   pExpressionLeft;
	TTypeName TypeName;
} TUnaryExpressionOperator;

#define TUNARY_EXPRESSION_OPERATOR_INIT { {TUnaryExpressionOperator_ID}, TK_NONE,  NULL, TTYPENAME_INIT}
CREATETYPE(TUnaryExpressionOperator, TUNARY_EXPRESSION_OPERATOR_INIT)


bool EvaluateConstantExpression(TExpression * p, int *pResult);


CAST(TExpression, TPrimaryExpressionValue)
CAST(TExpression, TBinaryExpression)
CAST(TExpression, TUnaryExpressionOperator)
CAST(TExpression, TPostfixExpressionCore)
CAST(TExpression, TCastExpressionType)

