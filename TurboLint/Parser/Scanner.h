
#pragma once

#include "..\Base\Array.h"
#include "BasicScanner.h"
#include "..\Base\Map.h"
#include "..\Base\List.h"
#include "Macro.h"


typedef struct
{
  String FullPath;
  String IncludePath;
  int FileIndex;
  bool PragmaOnce;
  bool bDirectInclude;
  bool bSystemLikeInclude;
} TFile;
#define TFILE_INIT {STRING_INIT, STRING_INIT, 0, false, false, false}
void TFile_Delete(TFile* p);

typedef Map TFileMap;

void TFileMap_Destroy(TFileMap* p);
Result TFileMap_Set(TFileMap *map, const char*key, TFile *data);
TFile*  TFileMap_Find(TFileMap* map, const char* key);
Result TFileMap_DeleteItem(TFileMap *map, const char* key);
void TFile_DeleteVoid(void* p);

typedef ArrayT(TFile) TFileArray;



typedef List(ScannerItem) TScannerItemList;
#define TSCANNERITEMLIST_INIT LIST_INIT
#define TScannerItemList_Destroy(p) List_Destroy(ScannerItem, (p))

typedef struct
{
  //Stack de basicscanner
  BasicScannerStack stack;

  //Mapa dos defines
  MacroMap  Defines2;

  //Stack usado para #if #else etc
  ArrayInt StackIfDef;

  //lista de arquivos marcados com pragma once
  TFileMap FilesIncluded;

  //Lista de diretorios de include
  StrArray IncludeDir;

  //Lista de diretorios considerados codigo do usuario
  StrArray MySourceDir;

  //string para debug
  StrBuilder DebugString;


  //String que mantem o erro
  StrBuilder ErrorString;

  //True indica error
  bool bError;

  //Imprime includes no console
  bool bPrintIncludes;

  //Quando true o scanner retorna tambem espacos
  bool bIncludeSpaces;


  TScannerItemList AcumulatedTokens;
  ///////////////////////////////////////////////////


  //string para debug
  //StrBuilder PreprocessorAndCommentsString;
  //TScannerItemList NodeClueList;
  bool bAmalgamationMode;

} Scanner;

void Scanner_SetError(Scanner* pScanner, const char* message);

//const char* Scanner_GetStreamName(Scanner* pScanner);
Result Scanner_InitString(Scanner* pScanner,
  const char* name,
  const char* text);

Result PushExpandedMacro(Scanner * pScanner, const char * defineName, const char * callString, const char * defineContent);

//const char* Scanner_TokenString(Scanner* pScanner);
//Tokens Scanner_Token(Scanner* pScanner);
//const char* Scanner_Lexeme(Scanner* pScanner);

bool Scanner_IsActiveGroup(Scanner* pScanner);

Result Scanner_Init(Scanner* pScanner);

typedef enum
{
  FileIncludeTypeQuoted,
  FileIncludeTypeIncludes,
  FileIncludeTypeFullPath,
} FileIncludeType;

void Scanner_IncludeFile(Scanner* pScanner,
  const char* fileName,
  FileIncludeType fileIncludeType);

void Scanner_IncludeFile_Version2(Scanner* pScanner,
  const char* includeFileName,
  FileIncludeType fileIncludeType);

void Scanner_Destroy(Scanner* pScanner);

//int Scanner_GetFileIndex(Scanner * pScanner);

int EvalExpression(const char* s, Scanner* pScanner);
void Scanner_PrintDebug(Scanner* pScanner);
void Scanner_GetError(Scanner* pScanner, StrBuilder* str);


void PrintPreprocessedToFile(const char* fileIn,
  const char* configFileName);


//NOVA INTERFACE

Tokens Scanner_CurrentToken(Scanner * pScanner);
int Scanner_CurrentLine(Scanner * pScanner);
int Scanner_CurrentFileIndex(Scanner * pScanner);
const char * Scanner_CurrentLexeme(Scanner * pScanner);

Tokens Scanner_LookAheadToken(Scanner * pScanner, int nLookAhead);
const char * Scanner_LookAheadLexeme(Scanner * pScanner, int nLookAhead);

void Scanner_Match(Scanner * pScanner);
