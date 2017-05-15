
#pragma once

#include "..\Base\Array.h"
#include "BasicScanner.h"
#include "..\Base\Map.h"
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

typedef Map TFileMap;

void TFileMap_Destroy(TFileMap* p);
Result TFileMap_Set(TFileMap *map, const char*key, TFile *data);
TFile*  TFileMap_Find(TFileMap* map, const char* key);
Result TFileMap_DeleteItem(TFileMap *map, const char* key);
void TFile_DeleteVoid(void* p);

typedef struct
{
	TFile** pItems;
	size_t size;
	size_t capacity;
} TFileArray;
#define TFILE_ARRAY_INIT {NULL, 0 , 0}
ARRAYOF(TFileArray, TFile)

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

    ///////////////////////////////////////////////////
    //Indica que foi feita uma leitura especulativa
    bool bHasLookAhead;

    //Valor lido na leitura especulativa
    ScannerItem LookAhead;
    //BasicScanner* pLookAheadPreviousScanner;

    ///////////////////////////////////////////////////


    //string para debug
    StrBuilder PreprocessorAndCommentsString;

    bool bAmalgamationMode;

} Scanner;

void Scanner_SetError(Scanner* pScanner, const char* message);

const char* Scanner_GetStreamName(Scanner* pScanner);
Result Scanner_InitString(Scanner* pScanner,
                          const char* name,
                          const char* text);

const char* Scanner_TokenString(Scanner* pScanner);
Tokens Scanner_Token(Scanner* pScanner);
const char* Scanner_Lexeme(Scanner* pScanner);

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

const char * Scanner_GetApparentStreamName(Scanner * pScanner);

void Scanner_Destroy(Scanner* pScanner);
int Scanner_GetCurrentLine(Scanner * pScanner);
int Scanner_GetFileIndex(Scanner * pScanner);

Tokens Scanner_Token(Scanner * pScanner);
const char * Scanner_Lexeme(Scanner * pScanner);

int Scanner_Line(Scanner* scanner);
int Scanner_Col(Scanner* scanner);
void Scanner_Next(Scanner* pScanner);
void Scanner_Skip(Scanner* pScanner);

int EvalExpression(const char* s, Scanner* pScanner);
void Scanner_PrintDebug(Scanner* pScanner);
void Scanner_GetError(Scanner* pScanner, StrBuilder* str);


void PrintPreprocessedToFile(const char* fileIn,
  const char* configFileName);

void Scanner_GetScannerItemCopy(Scanner* pScanner,
                                ScannerItem* scannerItem);



bool Scanner_GetApparentMacroOnTop(Scanner * pScanner);

ScannerItem* Scanner_GetLookAhead(Scanner* pScanner);