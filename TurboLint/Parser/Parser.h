
#pragma once

#include "Scanner.h"
#include "..\Base\StrBuilder.h"
#include "Ast.h"
#include "Scanner.h"
#include "..\Base\Map.h"

#define SYMBOL_BUCKETS_SIZE 1000


typedef struct
{
  //indica presenca de erro no parser
  bool bError;

  //mensagem de erro
  StrBuilder ErrorMessage;

  //scanner ja pré-processado
  Scanner Scanner;

  //struct, union, or enum;
  //typedef estao no mesmo mapa mas da p achar
  //a diferenca se preciso
  DeclarationsMap  Symbols;

  Map EnumMap;

} Parser;

Result Parser_InitFile(Parser* parser, const char* fileName);

Result Parser_InitString(Parser* parser,
                         const char* name,
                         const char* text,
                         bool bExpressionMode);

void Parser_Destroy(Parser* parser);


const char* GetCompletationMessage(Parser* parser);


bool GetAST(const char * filename,
            const char * configFileName,
            TProgram* pProgram);

Result MatchAndGet(Parser* parser, ScannerItem* scannerItem);
Tokens MatchToken(Parser* parser, Tokens tk);
void ConstantExpression(Parser* ctx, TExpression2** ppExpression);
