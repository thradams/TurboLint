#include "Scanner.h"
#include "Parser.h"
#include "Macro.h"

BasicScanner * Scanner_Top(Scanner * pScanner);;

PPTokenType TokenToPPToken(Tokens token)
{
  PPTokenType result = PPTokenType_Other;

  switch (token)
  {
  case TK_identifier:
    result = PPTokenType_Identifier;
    break;

  case TK_SPACES:
    result = PPTokenType_Spaces;
    break;

  case TK_HEX_INTEGER:
  case TK_DECIMAL_INTEGER:
  case TK_FLOAT_NUMBER:
    result = PPTokenType_Number;
    break;

  case TK_char_literal:
    result = PPTokenType_CharConstant;
    break;

  case TK_string_literal:
    result = PPTokenType_StringLiteral;
    break;

  case TK_ARROW:
  case TK_PLUSPLUS:
  case TK_MINUSMINUS:
  case TK_LESSLESS:
  case TK_GREATERGREATER:
  case TK_LESSEQUAL:
  case TK_GREATEREQUAL:
  case TK_EQUALEQUAL:
  case TK_NOTEQUAL:
  case TK_ANDAND:
  case TK_OROR:
  case TK_MULTIEQUAL:
  case TK_DIVEQUAL:
  case TK_PERCENT_EQUAL:
  case TK_PLUSEQUAL:
  case TK_MINUS_EQUAL:
  case TK_ANDEQUAL:
  case TK_CARETEQUAL:
  case TK_OREQUAL:
  case TK_NUMBERNUMBER:
  case TK_LESSCOLON:
  case TK_COLONGREATER:
  case TK_LESSPERCENT:
  case TK_PERCENTGREATER:
  case TK_PERCENTCOLON:
  case TK_DOTDOTDOT:
  case TK_GREATERGREATEREQUAL:
  case TK_LESSLESSEQUAL:
  case TK_PERCENTCOLONPERCENTCOLON:


  case TK_NUMBER_SIGN:
    result = PPTokenType_Punctuator;
    break;

  }

  return result;
}

TFile* TFile_Create()
{
  TFile* p = (TFile*)malloc(sizeof * p);

  if (p)
  {
    TFile temp = TFILE_INIT;
    *p = temp;
  }

  return p;
}

void TFile_Destroy(TFile* p)
{
  String_Destroy(&p->FullPath);
}

void TFile_Delete(TFile* p)
{
  if (p)
  {
    TFile_Destroy(p);
    free(p);
  }
}

void TFile_DeleteVoid(void* p)
{
  TFile_Delete((TFile*)p);
}

void TFileMap_Destroy(TFileMap* p)
{
  Map_Destroy(p, TFile_DeleteVoid);
}

Result TFileMap_Set(TFileMap* map, const char* key, TFile* pFile)
{
  //tem que ser case insensitive!
  ASSERT(IsFullPath(key));
  //converter
  //Ajusta o file index de acordo com a entrada dele no mapa
  pFile->FileIndex = map->Size;
  Result result = Map_Set(map, key, pFile);
  String_Set(&pFile->FullPath, key);
  return result;
}

TFile*  TFileMap_Find(TFileMap* map, const char* key)
{
  //tem que ser case insensitive!
  return (TFile*)Map_Find2(map, key);
}

Result TFileMap_DeleteItem(TFileMap* map, const char* key)
{
  return Map_DeleteItem(map, key, TFile_DeleteVoid);
}

typedef enum
{
  NONE, //inclui
  I1,//inclui
  I0,
  E0,
  E1,//inclui
} State;

bool IsIncludeState(State e)
{
  return e == NONE || e == I1 || e == E1;
}

State StateTop(Scanner* pScanner)
{
  if (pScanner->StackIfDef.size == 0)
    return NONE;

  return (State)ArrayInt_Top(&pScanner->StackIfDef);
}

void StatePush(Scanner* pScanner, State s)
{
  ArrayInt_Push(&pScanner->StackIfDef, s);
}

void StatePop(Scanner* pScanner)
{
  ArrayInt_Pop(&pScanner->StackIfDef);
}


void Scanner_GetError(Scanner* pScanner, StrBuilder* str)
{
  StrBuilder_Append(str, pScanner->DebugString.c_str);
  StrBuilder_Append(str, "\n");

  for (size_t i = 0; i < pScanner->stack.size; i++)
  {
    BasicScanner* p = (BasicScanner*)pScanner->stack.pItems[i];
    StrBuilder_Append(str, p->stream.NameOrFullPath);
    StrBuilder_Append(str, "(");
    StrBuilder_AppendInt(str, p->stream.currentLine);
    StrBuilder_Append(str, ")\n");
  }
}

void Scanner_SetError(Scanner* pScanner, const char* message)
{
  if (!pScanner->bError)
  {
    pScanner->bError = true;
    StrBuilder_Set(&pScanner->ErrorString,
      Scanner_Top(pScanner)->stream.NameOrFullPath);
    StrBuilder_Append(&pScanner->ErrorString, "(");
    StrBuilder_AppendInt(&pScanner->ErrorString, Scanner_Top(pScanner)->stream.currentLine);
    StrBuilder_Append(&pScanner->ErrorString, ")");
    StrBuilder_Append(&pScanner->ErrorString, message);
  }
}

void Scanner_PrintDebug(Scanner* pScanner)
{
  printf("\ndebug---\n");

  for (size_t i = 0; i < pScanner->stack.size; i++)
  {
    BasicScanner* p = (BasicScanner*)pScanner->stack.pItems[i];
    printf("stream %d %s\n", (int)i, p->stream.NameOrFullPath);
    printf("line, col = %d %d\n", p->stream.currentLine, p->stream.currentCol);
  }

  printf("---\n");
}

static Result AddStandardMacro(Scanner* pScanner,
  const char* name,
  const char* value)
{
  Macro* pDefine1 = Macro_Create();
  String_Set(&pDefine1->Name, name);
  //TODO tipo do token
  TokenArray2_Push(&pDefine1->TokenSequence, PPToken_Create(value, PPTokenType_Other));
  pDefine1->FileIndex = 0;
  MacroMap2_SetAt(&pScanner->Defines2, name, pDefine1);
  return RESULT_OK;
}

static Result Scanner_InitCore(Scanner* pScanner)
{
  //TFileMap_init
  //pScanner->IncludeDir
  Map_Init(&pScanner->FilesIncluded, 100);
  MacroMap2_Init(&pScanner->Defines2);
  StrBuilder_Init(&pScanner->DebugString, 100);
  StrBuilder_Init(&pScanner->ErrorString, 100);
  //StrBuilder_Init(&pScanner->DebugString, 100);
  //StrBuilder_Init(&pScanner->ErrorString, 100);
  pScanner->bError = false;
  ArrayInt_Init(&pScanner->StackIfDef);
  pScanner->bPrintIncludes = false;

  pScanner->bIncludeSpaces = false;
  Array_Init(&pScanner->stack);

  StrArray_Init(&pScanner->IncludeDir);
  StrArray_Init(&pScanner->MySourceDir);

  //Indica que foi feita uma leitura especulativa
  pScanner->bHasLookAhead = false;
  //Valor lido na leitura especulativa
  ScannerItem_Init(&pScanner->LookAhead);
  //__FILE__ __LINE__ __DATE__ __STDC__  __STD_HOSTED__  __TIME__  __STD_VERSION__
  //
  AddStandardMacro(pScanner, "__LINE__", "0");
  AddStandardMacro(pScanner, "__FILE__", "\"__FILE__\"");
  AddStandardMacro(pScanner, "__DATE__", "\"__DATE__\"");
  AddStandardMacro(pScanner, "__TIME__", "\"__TIME__\"");
  AddStandardMacro(pScanner, "__STDC__", "1");
  //AddStandardMacro(pScanner, "__STD_HOSTED__", "1");
  return RESULT_OK;
}

Result Scanner_InitString(Scanner* pScanner,
  const char* name,
  const char* text)
{
  Scanner_InitCore(pScanner);

  BasicScanner* pNewScanner;
  Result result = BasicScanner_Create(&pNewScanner, name, text);
  Array_Push(&pScanner->stack, pNewScanner);
  return result;
}


static Result PushExpandedMacro(Scanner* pScanner,
  const char* defineName,
  const char* defineContent)
{
  BasicScanner* pNewScanner;
  Result result = BasicScanner_Create(&pNewScanner,
    defineName,
    defineContent);

  if (result == RESULT_OK)
  {
    pNewScanner->bMacroExpanded = true;
    BasicScanner_Next(pNewScanner);//inicia
    Array_Push(&pScanner->stack, pNewScanner);
  }

  return result;
}

bool Scanner_GetFullPath(Scanner* pScanner,
  const char* fileName,
  bool bQuotedForm,
  String* fullPathOut)
{
  bool bFullPathFound = false;

  //https://msdn.microsoft.com/en-us/library/36k2cdd4.aspx
  /*
  bQuotedForm
  The preprocessor searches for include files in this order:
  1) In the same directory as the file that contains the #include statement.
  2) In the directories of the currently opened include files, in the reverse order in which they were opened. The search begins in the directory of the parent include file and continues upward through the directories of any grandparent include files.
  3) Along the path that's specified by each /I compiler option.
  4)
  Along the paths that are specified by the INCLUDE environment variable.
  */
  if (bQuotedForm)
  {
    //String s = STRING_INIT;
    //GetFullPath(fileName, &s);
    //String_Destroy(&s);
    if (IsFullPath(fileName))
    {
      //Se ja vier com fullpath?? este caso esta cobrindo
      //mas deve ter uma maneira melhor de verificar se eh um fullpath ja
      bFullPathFound = true;
      String_Set(fullPathOut, fileName);
    }

    else
    {
      if (pScanner->stack.size > 0)
      {
        //tenta nos diretorios ja abertos
        StrBuilder path = STRBUILDER_INIT;

        for (int i = (int)pScanner->stack.size - 1; i >= 0; i--)
        {
          BasicScanner* p = (BasicScanner*)pScanner->stack.pItems[i];
          StrBuilder_Set(&path, p->stream.FullDir2);
          StrBuilder_Append(&path, fileName);
          bool bFileExists = FileExists(path.c_str);

          if (bFileExists)
          {
            GetFullPath(path.c_str, fullPathOut);
            //String_Set(fullPathOut, StrBuilder_Release(&path));
            bFullPathFound = true;
            break;
          }
        }

        StrBuilder_Destroy(&path);
      }

      else
      {
        //nao abriu nenhum, faz o full path do nome do arquivo
        String fullPath;
        String_Init(&fullPath, NULL);
        GetFullPath(fileName, &fullPath);
        bool bFileExists = FileExists(fullPath);

        if (bFileExists)
        {
          String_Swap(&fullPath, fullPathOut);
          bFullPathFound = true;
        }

        String_Destroy(&fullPath);
      }
    }
  }

  /*
  Angle-bracket form
  The preprocessor searches for include files in this order:
  1) Along the path that's specified by each /I compiler option.
  2) When compiling occurs on the command line, along the paths that are specified by the INCLUDE environment variable.
  */
  if (!bFullPathFound)
  {
    StrBuilder path = STRBUILDER_INIT;

    //StrBuilder_Init(&path, 200);
    for (size_t i = 0; i < pScanner->IncludeDir.size; i++)
    {
      const char* pItem = pScanner->IncludeDir.pItems[i];
      StrBuilder_Set(&path, pItem);
      StrBuilder_Append(&path, "\\");
      StrBuilder_Append(&path, fileName);
      bool bFileExists = FileExists(path.c_str);

      if (bFileExists)
      {
        String_Set(fullPathOut, StrBuilder_Release(&path));
        bFullPathFound = true;
        break;
      }
    }

    StrBuilder_Destroy(&path);
  }

  return bFullPathFound;
}


void Scanner_IncludeFile(Scanner* pScanner,
  const char* includeFileName,
  FileIncludeType fileIncludeType)
{
  bool bDirectInclude = false;

  String fullPath = STRING_INIT;
  String_Init(&fullPath, "");
  //Faz a procura nos diretorios como se tivesse adicinando o include
  //seguindo as mesmas regras. Caso o include seja possivel ele retorna o path completo
  //este path completo que eh usado para efeitos do pragma once.
  bool bHasFullPath = false;

  switch (fileIncludeType)
  {
  case FileIncludeTypeQuoted:
  case FileIncludeTypeIncludes:
    bHasFullPath = Scanner_GetFullPath(pScanner,
      includeFileName,
      fileIncludeType == FileIncludeTypeQuoted,
      &fullPath);
    break;

  case FileIncludeTypeFullPath:
    String_Set(&fullPath, includeFileName);
    bHasFullPath = true;
    break;
  };

  if (bHasFullPath)
  {
    //Se o arquivo esta sendo incluído de um arquivo
    //que é do usuário e este arquivo não é do usuário
    //então ele é marcado para ser incluído para fazer 
    //os includes lah do almagamations

    const char* fName = Scanner_GetStreamName(pScanner);

    for (int k = 0; k < pScanner->MySourceDir.size; k++)
    {
      if (fName && IsInPath(fName, pScanner->MySourceDir.pItems[k]))
      {
        if (!IsInPath(fullPath, pScanner->MySourceDir.pItems[k]))
        {
          bDirectInclude = true;
        }
      }
      if (bDirectInclude)
        break;
    }


    TFile*  pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);

    if (pFile != NULL && pFile->PragmaOnce)
    {
      //foi marcado como pragma once.. nao faz nada
    }
    else
    {
      if (pFile == NULL)
      {
        pFile = TFile_Create();
        pFile->bDirectInclude = bDirectInclude;
        TFileMap_Set(&pScanner->FilesIncluded, fullPath, pFile); //pfile Moved
      }

      BasicScanner* pNewScanner = NULL;
      Result result = BasicScanner_CreateFile(fullPath, &pNewScanner);

      if (result == RESULT_OK)
      {
        if (pScanner->bPrintIncludes)
        {
          printf("%s\n", fullPath);
        }

        if (pFile)
        {
          pNewScanner->FileIndex = pFile->FileIndex;
          BasicScanner_Next(pNewScanner);
          Array_Push(&pScanner->stack, pNewScanner);
        }

        else
        {
          Scanner_SetError(pScanner, "mem");
        }
      }

      else
      {
        ASSERT(false);
        Scanner_SetError(pScanner, "error in file '");
        StrBuilder_Append(&pScanner->ErrorString, fullPath);
        StrBuilder_Append(&pScanner->ErrorString, "'");
      }
    }
  }

  else
  {
    Scanner_SetError(pScanner, "file '");
    StrBuilder_Append(&pScanner->ErrorString, includeFileName);
    StrBuilder_Append(&pScanner->ErrorString, "' not found");
  }

  String_Destroy(&fullPath);
}

const char* Scanner_GetStreamName(Scanner* pScanner)
{
  BasicScanner* p = Scanner_Top(pScanner);
  return p ?  p->stream.NameOrFullPath : NULL;
}

Result Scanner_Init(Scanner* pScanner)
{
  return Scanner_InitCore(pScanner);
}

static void Delete_Scanner(void* pv)
{
  BasicScanner_Delete((BasicScanner*)pv);
}

void Scanner_Destroy(Scanner* pScanner)
{

  MacroMap2_Destroy(&pScanner->Defines2);
  StrBuilder_Destroy(&pScanner->DebugString);
  StrBuilder_Destroy(&pScanner->ErrorString);
  ArrayInt_Destroy(&pScanner->StackIfDef);
  Array_Destroy(&pScanner->stack, &Delete_Scanner);
  TFileMap_Destroy(&pScanner->FilesIncluded);
  StrArray_Destroy(&pScanner->IncludeDir);
  StrArray_Destroy(&pScanner->MySourceDir);
  //Valor lido na leitura especulativa
  ScannerItem_Destroy(&pScanner->LookAhead);
}

int Scanner_GetCurrentLine(Scanner* pScanner)
{
  ASSERT(!pScanner->bHasLookAhead);

  if (pScanner->bError)
  {
    return -1;
  }

  if (pScanner->stack.size == 0)
  {
    return -1;
  }

  int currentLine = -1;
  int fileIndex = -1;

  for (int i = (int)pScanner->stack.size - 1; i >= 0; i--)
  {
    BasicScanner* pBasicScanner = (BasicScanner*)pScanner->stack.pItems[i];
    fileIndex = pBasicScanner->FileIndex;

    if (fileIndex >= 0) //macro eh -1
    {
      currentLine = pBasicScanner->stream.currentLine;
      break;
    }
  }

  return currentLine;
}


int Scanner_GetFileIndex(Scanner* pScanner)
{
  if (pScanner->bError)
  {
    return -1;
  }

  if (pScanner->stack.size == 0)
  {
    return -1;
  }

  int fileIndex = -1;

  for (int i = (int)pScanner->stack.size - 1; i >= 0; i--)
  {
    BasicScanner* pBasicScanner = (BasicScanner*)pScanner->stack.pItems[i];
    fileIndex = pBasicScanner->FileIndex;

    if (fileIndex >= 0)
    {
      break;
    }
  }

  //ASSERT(fileIndex >= 0);
  return fileIndex;
}

Tokens Scanner_Token(Scanner* pScanner)
{
  if (pScanner->bError)
  {
    return TK_EOF;
  }

  if (pScanner->bHasLookAhead)
  {
    return pScanner->LookAhead.token;
  }

  if (pScanner->stack.size == 0)
  {
    return TK_EOF;
  }

  Tokens token = ((BasicScanner*)Array_Top(&pScanner->stack))->currentItem.token;

  return token;
}

const char* Scanner_Lexeme(Scanner* pScanner)
{
  if (pScanner->bHasLookAhead)
  {
    return pScanner->LookAhead.lexeme.c_str;
  }

  if (pScanner->stack.size == 0)
  {
    return "";
  }

  return ((BasicScanner*)Array_Top(&pScanner->stack))->currentItem.lexeme.c_str;
}

BasicScanner* Scanner_Top(Scanner* pScanner)
{
  if (pScanner->stack.size == 0)
  {
    return NULL;
  }

  return (BasicScanner*)Array_Top(&pScanner->stack);
}

int Scanner_Line(Scanner* pScanner)
{
  ASSERT(!pScanner->bHasLookAhead);
  return Scanner_Top(pScanner)->stream.currentLine;
}

int Scanner_Col(Scanner* pScanner)
{
  ASSERT(!pScanner->bHasLookAhead);
  return Scanner_Top(pScanner)->stream.currentCol;
}

void SkipSpaces(Scanner* pScanner)
{
  while (Scanner_Top(pScanner)->currentItem.token == TK_SPACES)
  {
    BasicScanner_Next(Scanner_Top(pScanner));
  }

  /*  
   #define A(x) M(x) 
   #define B A 
   B(10) 
  */
  //Arranca também o EOF se nao for o ultimo
  while (Scanner_Top(pScanner) != NULL && 
         Scanner_Top(pScanner)->currentItem.token == TK_EOF)
  {
    if (pScanner->stack.size > 1)
    {
      Array_Pop(&pScanner->stack, &Delete_Scanner);
    }
  }
}

static void Scanner_Match(Scanner* pScanner)
{
  BasicScanner_Next(Scanner_Top(pScanner));
  SkipSpaces(pScanner);
}

void IgnorePreProcessor(Scanner* pScanner)
{
  BasicScanner* pTop = Scanner_Top(pScanner);

  // ASSERT(pTop->currentItem.token != TK_BREAKLINE);
  while (pTop->currentItem.token != TK_EOF)
  {
    if (pTop->currentItem.token == TK_BREAKLINE)
    {
      //BasicScanner_Next(Scanner_Top(pScanner));
      break;
    }

    BasicScanner_Next(pTop);
  }
}

void GetDefineString(Scanner* pScanner, StrBuilder* strBuilder)
{
  for (;;)
  {
    Tokens token = Scanner_Top(pScanner)->currentItem.token;

    if (token == TK_EOF)
    {
      break;
    }

    if (token == TK_BREAKLINE)
    {
      //deixa o break line
      //BasicScanner_Next(Scanner_Top(pScanner));
      break;
    }

    if (token == TK_COMMENT ||
      token == TK_LINE_COMMENT)
    {
      //transforma em espaços
      StrBuilder_Append(strBuilder, " ");
    }

    else
    {
      StrBuilder_Append(strBuilder, BasicScanner_Lexeme(Scanner_Top(pScanner)));
    }

    BasicScanner_Next(Scanner_Top(pScanner));
  }
}

static Tokens GetToken(Scanner* pScanner)
{
  return Scanner_Top(pScanner)->currentItem.token;
}


Macro*  Scanner_FindPreprocessorItem2(Scanner* pScanner,
  const char* key)
{
  Macro* pMacro = MacroMap2_Find(&pScanner->Defines2, key);
  return pMacro;
}

bool Scanner_IsLexeme(Scanner* pScanner, const char* psz)
{
  return BasicScanner_IsLexeme(Scanner_Top(pScanner), psz);
}


int PreprocessorExpression(Parser* parser)
{
  //Faz o parser da expressão
  TExpression2* pExpression = NULL;
  ConstantExpression(parser, &pExpression);
  //..a partir da arvore da expressão
  //calcula o valor
  //TODO pegar error
  int r;
  EvaluateConstantExpression(pExpression, &r);
  TExpression2_Delete(pExpression);
  return r;
}


int EvalExpression(const char* s, Scanner* pScanner)
{
  MacroMap* pDefines = &pScanner->Defines2;
  //printf("%s = ", s);
  //TODO avaliador de expressoes para pre processador
  //https://gcc.gnu.org/onlinedocs/gcc-3.0.2/cpp_4.html#SEC38
  Parser parser;
  Parser_InitString(&parser, "eval expression", s);

  if (pDefines)
  {
    //usa o mapa de macros para o pre-processador
    MacroMap2_Swap(&parser.Scanner.Defines2, pDefines);
  }

  Scanner_Next(&parser.Scanner);
  int iRes = PreprocessorExpression(&parser);

  //printf(" %d\n", iRes);
  if (pDefines)
  {
    MacroMap2_Swap(&parser.Scanner.Defines2, pDefines);
  }

  if (parser.bError)
  {
    Scanner_SetError(pScanner, parser.ErrorMessage.c_str);
  }

  Parser_Destroy(&parser);
  return iRes;
}



bool GetNewMacroCallString(Scanner* pScanner,
  Macro* pMacro,
  TokenArray* ppTokenArray)
{
  //StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));

  const char* lexeme = Scanner_Lexeme(pScanner);
  PPToken *ppToken = PPToken_Create(lexeme,
    TokenToPPToken(GetToken(pScanner)));
  TokenArray2_Push(ppTokenArray, ppToken);

  Scanner_Match(pScanner);
  //verificar se tem parametros
  int nArgsExpected = pMacro->FormalArguments.Size;// pMacro->bIsFunction;
  int nArgsFound = 0;

  //fazer uma lista com os parametros
  if (nArgsExpected > 0)
  {
    Tokens token = Scanner_Token(pScanner);

    if (token == TK_LEFT_PARENTHESIS)
    {
      PPToken *ppToken = PPToken_Create(Scanner_Lexeme(pScanner), TokenToPPToken(GetToken(pScanner)));
      TokenArray2_Push(ppTokenArray, ppToken);
      //StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
      BasicScanner_Next(Scanner_Top(pScanner));
      //comeca com 1
      nArgsFound = 1;
      int iInsideParentesis = 1;

      for (;;)
      {
        token = Scanner_Token(pScanner);

        if (token == TK_LEFT_PARENTHESIS)
        {
          //StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
          PPToken *ppToken = PPToken_Create(Scanner_Lexeme(pScanner), TokenToPPToken(GetToken(pScanner)));
          TokenArray2_Push(ppTokenArray, ppToken);
          BasicScanner_Next(Scanner_Top(pScanner));
          iInsideParentesis++;
        }

        else if (token == TK_RIGHT_PARENTHESIS)
        {
          if (iInsideParentesis == 1)
          {
            //StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
            PPToken *ppToken = PPToken_Create(Scanner_Lexeme(pScanner), TokenToPPToken(GetToken(pScanner)));
            TokenArray2_Push(ppTokenArray, ppToken);
            BasicScanner_Next(Scanner_Top(pScanner));
            break;
          }

          iInsideParentesis--;
          //StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
          PPToken *ppToken = PPToken_Create(Scanner_Lexeme(pScanner), TokenToPPToken(GetToken(pScanner)));
          TokenArray2_Push(ppTokenArray, ppToken);
          BasicScanner_Next(Scanner_Top(pScanner));
        }

        else if (token == TK_COMMA)
        {
          if (iInsideParentesis == 1)
          {
            nArgsFound++;
          }

          else
          {
            //continuar...
          }

          //StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
          PPToken *ppToken = PPToken_Create(Scanner_Lexeme(pScanner), TokenToPPToken(GetToken(pScanner)));
          TokenArray2_Push(ppTokenArray, ppToken);
          BasicScanner_Next(Scanner_Top(pScanner));
        }

        else
        {
          //StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
          PPToken *ppToken = PPToken_Create(Scanner_Lexeme(pScanner), TokenToPPToken(GetToken(pScanner)));
          TokenArray2_Push(ppTokenArray, ppToken);
          BasicScanner_Next(Scanner_Top(pScanner));
        }
      }
    }

    else
    {
      //oops
    }
  }
  else
  {
    //o nome eh a propria expansao
  }

  bool bIsMacro = true;

  if (nArgsExpected != nArgsFound)
  {
    if (nArgsFound == 0 && nArgsExpected > 0)
    {
      bIsMacro = false;
      //nao eh macro
      //no header do windows por ex, tem um min como membro
      //de struct e o mesmo min eh macro
      //tratar como nao sendo macro
      //JObj_PrintDebug(pMacro);
      //Scanner_PrintDebug(pScanner);
    }

    else
    {
      ASSERT(false);
      //JObj_PrintDebug(pMacro);
      Scanner_PrintDebug(pScanner);
    }
  }

  return bIsMacro;
  //return false;
}

typedef  enum
{
  PRETK_INCLUDE,
  PRETK_PRAGMA,
  PRETK_IF,
  PRETK_ELIF,
  PRETK_IFNDEF,
  PRETK_IFDEF,
  PRETK_ENDIF,
  PRETK_ELSE,
  PRETK_ERROR,
  PRETK_LINE,
  PRETK_UNDEF,
  PRETK_DEFINE,
  PRETK_NONE,
} PreTokens;

PreTokens FindPreToken(const char* lexeme)
{
  const char* s_PreTokens[] =
  {
    "include",
    "pragma",
    "if",
    "elif",
    "ifndef",
    "ifdef",
    "endif",
    "else",
    "error",
    "line",
    "undef",
    "define"
  };

  for (int i = 0; i < sizeof(s_PreTokens) / sizeof(s_PreTokens[0]); i++)
  {
    if (strcmp(lexeme, s_PreTokens[i]) == 0)
    {
      return (PreTokens)i;
    }
  }

  return PRETK_NONE;
}

void GetPPTokens(Scanner* pScanner, TokenArray* pptokens)
{
  //Corpo da macro
  while (GetToken(pScanner) != TK_BREAKLINE)
  {
    const char* lexeme = Scanner_Top(pScanner)->currentItem.lexeme.c_str;
    PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(GetToken(pScanner)));
    TokenArray2_Push(pptokens, ppToken);
    BasicScanner_Next(Scanner_Top(pScanner));
  }
}

void ParsePreDefine(Scanner* pScanner)
{
  //objetivo eh montar a macro e colocar no mapa
  Macro* pNewMacro = Macro_Create();
  //const char* lexeme = Scanner_Top(pScanner)->currentItem.lexeme.c_str;
  //define MATCHED
  //Scanner_Match(pScanner);
  //nome da macro
  const char* lexeme = Scanner_Top(pScanner)->currentItem.lexeme.c_str;

  if (strcmp(lexeme, "__ANNOTATION") == 0)
  {
    String_Set(&pNewMacro->Name, lexeme);
  }

  else
    String_Set(&pNewMacro->Name, lexeme);


  //AQUI NAO PODE IGNORAR ESPACOS
  BasicScanner_Next(Scanner_Top(pScanner));

  //Parametros
  if (Scanner_Token(pScanner) == TK_LEFT_PARENTHESIS)
  {
    pNewMacro->bIsFunction = true;

    Scanner_Match(pScanner);

    for (;;)
    {
      Tokens token = Scanner_Token(pScanner);

      if (token == TK_RIGHT_PARENTHESIS)
      {
        Scanner_Match(pScanner);
        break;
      }

      if (token == TK_BREAKLINE ||
        token == TK_EOF)
      {
        //oopss
        break;
      }

      lexeme = BasicScanner_Lexeme(Scanner_Top(pScanner));
      PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(GetToken(pScanner)));
      TokenArray2_Push(&pNewMacro->FormalArguments, ppToken);
      //StrArray_Push(&pDefine->Args, lexeme);
      //JObj_PushString(pArgs, lexeme);
      Scanner_Match(pScanner);
      token = Scanner_Token(pScanner);

      if (token == TK_COMMA)
      {
        Scanner_Match(pScanner);
        //tem mais
      }
    }
  }

  GetPPTokens(pScanner, &pNewMacro->TokenSequence);

  MacroMap2_SetAt(&pScanner->Defines2, pNewMacro->Name, pNewMacro);

  //breakline ficou...
}


int EvalPre(Scanner* pScanner)
{
  //pega todos os tokens ate o final da linha expande e
  //avalia
  //usado no #if #elif etc.

  TokenArray pptokens = TOKENARRAY_INIT;
  GetPPTokens(pScanner, &pptokens);
  StrBuilder strBuilder = STRBUILDER_INIT;
  ExpandMacroToText(&pptokens,
    &pScanner->Defines2,
    false,
    true,
    NULL,
    &strBuilder);

  int iRes = EvalExpression(strBuilder.c_str, pScanner);

  StrBuilder_Destroy(&strBuilder);
  TokenArray2_Destroy(&pptokens);
  return iRes;
}

void Scanner_SkipCore(Scanner* pScanner)
{

  for (; ;)
  {
    if (pScanner->bError)
      break;

    Tokens token = Scanner_Token(pScanner);
    State state = StateTop(pScanner);

    if (token == TK_PREPROCESSOR)
    {
      Scanner_Match(pScanner);
      const char* lexeme = Scanner_Top(pScanner)->currentItem.lexeme.c_str;
      token = Scanner_Token(pScanner);
      PreTokens preToken = FindPreToken(lexeme);

      if (preToken == PRETK_INCLUDE)
      {
        if (!IsIncludeState(state))
        {
          Scanner_Match(pScanner);
          continue;
        }

        Scanner_Match(pScanner);

        if (GetToken(pScanner) == TK_string_literal)
        {
          String fileName;
          String_Init(&fileName, Scanner_Lexeme(pScanner) + 1);
          Scanner_Match(pScanner);
          fileName[strlen(fileName) - 1] = 0;
          IgnorePreProcessor(pScanner);
          //pode ou nao incluir depende do pragma once
          Scanner_IncludeFile(pScanner, fileName, FileIncludeTypeQuoted);
          String_Destroy(&fileName);
          //break;
        }

        else if (GetToken(pScanner) == TK_LESS_THAN_SIGN)
        {
          Scanner_Match(pScanner);
          StrBuilder path = STRBUILDER_INIT;

          //StrBuilder_Init(&path, 200);
          for (;;)
          {
            if (GetToken(pScanner) == TK_GREATER_THAN_SIGN)
            {
              Scanner_Match(pScanner);
              break;
            }

            if (GetToken(pScanner) == TK_BREAKLINE)
            {
              //oopps
              break;
            }

            StrBuilder_Append(&path, Scanner_Lexeme(pScanner));
            Scanner_Match(pScanner);
          }

          //pode ou nao incluir depende do pragma once
          Scanner_IncludeFile(pScanner, path.c_str, FileIncludeTypeIncludes);
          StrBuilder_Destroy(&path);
        }

        else
        {
          IgnorePreProcessor(pScanner);
        }

        //
        //break;
      }

      else if (preToken == PRETK_PRAGMA)
      {
        if (!IsIncludeState(state))
        {
          IgnorePreProcessor(pScanner);
          continue;
        }

        Scanner_Match(pScanner);

        if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "once"))
        {
          const char* fullPath = Scanner_Top(pScanner)->stream.NameOrFullPath;
          TFile* pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);

          if (pFile == NULL)
          {
            pFile = TFile_Create();
            pFile->PragmaOnce = true;
            TFileMap_Set(&pScanner->FilesIncluded, fullPath, pFile);
          }

          else
          {
            pFile->PragmaOnce = true;
          }
        }

        else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "dir"))
        {
          Scanner_Match(pScanner);
          String fileName;
          String_Init(&fileName, Scanner_Lexeme(pScanner) + 1);
          Scanner_Match(pScanner);
          fileName[strlen(fileName) - 1] = 0;
          StrArray_Push(&pScanner->IncludeDir, fileName);
          String_Destroy(&fileName);
        }

        else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "mydir"))
        {
          Scanner_Match(pScanner);
          String fileName;
          String_Init(&fileName, Scanner_Lexeme(pScanner) + 1);
          Scanner_Match(pScanner);
          fileName[strlen(fileName) - 1] = 0;
          StrArray_Push(&pScanner->MySourceDir, fileName);
          String_Destroy(&fileName);
        }

        else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "ignore"))
        {
          Scanner_Match(pScanner);
          String fileName;
          String_Init(&fileName, Scanner_Lexeme(pScanner) + 1);
          Scanner_Match(pScanner);
          fileName[strlen(fileName) - 1] = 0;
          TFile* pFile = TFile_Create();
          TFileMap_Set(&pScanner->FilesIncluded, fileName, pFile);
        }

        else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "push_macro"))
        {
          Scanner_Match(pScanner);
          Scanner_Match(pScanner); //(
          Scanner_Match(pScanner);  //""
          Scanner_Match(pScanner); //)
          //salva a macro em uma pilha
        }

        else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "pop_macro"))
        {
          Scanner_Match(pScanner);
          Scanner_Match(pScanner); //(
          Scanner_Match(pScanner);  //""
          Scanner_Match(pScanner); //)
          //#pragma push_macro("Y")
          //#pragma pop_macro("X")
        }

        IgnorePreProcessor(pScanner);
      }

      else if (preToken == PRETK_IF ||
        preToken == PRETK_IFDEF ||
        preToken == PRETK_IFNDEF)
      {
        Scanner_Match(pScanner);

        switch (state)
        {
        case NONE:
        case I1:
        case E1:
        {
          int iRes = 0;

          if (preToken == PRETK_IF)
          {
            iRes = EvalPre(pScanner);
          }

          else
          {
            bool bFound = Scanner_FindPreprocessorItem2(pScanner, lexeme) != NULL;

            if (preToken == PRETK_IFDEF)
            {
              iRes = bFound ? 1 : 0;
            }

            else //if (preToken == PRETK_IFNDEF)
            {
              iRes = !bFound ? 1 : 0;
            }
          }

          if (iRes != 0)
          {
            StatePush(pScanner, I1);
          }

          else
          {
            StatePush(pScanner, I0);
          }
        }
        break;

        case I0:
          StatePush(pScanner, I0);
          break;

        case E0:
          StatePush(pScanner, E0);
          break;
        }

        IgnorePreProcessor(pScanner);
      }

      else if (preToken == PRETK_ELIF)
      {
        Scanner_Match(pScanner);

        switch (state)
        {
        case NONE:
        case I1:
          pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = E0;
          break;

        case I0:
        {
          int iRes = EvalPre(pScanner);

          if (pScanner->StackIfDef.size >= 2)
          {
            if ((pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 2] == I1 ||
              pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 2] == E1))
            {
              if (iRes)
              {
                pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = I1;
              }
            }
          }

          else
          {
            if (iRes)
            {
              pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = I1;
            }
          }
        }
        break;

        case E0:
          break;

        case E1:
          ASSERT(0);
          break;
        }

        IgnorePreProcessor(pScanner);
      }

      else if (preToken == PRETK_ENDIF)
      {
        IgnorePreProcessor(pScanner);
        StatePop(pScanner);
      }

      else if (preToken == PRETK_ELSE)
      {
        IgnorePreProcessor(pScanner);

        switch (state)
        {
        case NONE:
          ASSERT(0);
          break;

        case I1:
          pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = E0;
          break;

        case I0:
          if (pScanner->StackIfDef.size >= 2)
          {
            if ((pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 2] == I1 ||
              pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 2] == E1))
            {
              pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = E1;
            }
          }

          else
          {
            pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = E1;
          }

          break;

        case E0:
          break;

        case E1:
          ASSERT(false);
          break;
        }
      }

      else if (preToken == PRETK_ERROR)
      {
        if (!IsIncludeState(state))
        {
          IgnorePreProcessor(pScanner);
          continue;
        }

        Scanner_Match(pScanner);
        StrBuilder str = STRBUILDER_INIT;
        //StrBuilder_Init(&str, 100);
        StrBuilder_Append(&str, ": #error : ");
        GetDefineString(pScanner, &str);
        Scanner_SetError(pScanner, str.c_str);
        StrBuilder_Destroy(&str);
        IgnorePreProcessor(pScanner);
      }

      else if (preToken == PRETK_LINE)
      {
        IgnorePreProcessor(pScanner);
      }

      else if (preToken == PRETK_UNDEF)
      {
        if (!IsIncludeState(state))
        {
          IgnorePreProcessor(pScanner);
          continue;
        }

        Scanner_Match(pScanner);
        lexeme = BasicScanner_Lexeme(Scanner_Top(pScanner));

        MacroMap2_RemoveKey(&pScanner->Defines2, lexeme);

        IgnorePreProcessor(pScanner);
      }

      else if (preToken == PRETK_DEFINE)
      {
        Scanner_Match(pScanner);

        if (!IsIncludeState(state))
        {
          IgnorePreProcessor(pScanner);
          break;
        }

        //se ja existe deletar
        ParsePreDefine(pScanner);
      }

      else
      {
        IgnorePreProcessor(pScanner);
      }

      //todos acabam com final de linha exceto o include
      if (preToken == PRETK_INCLUDE)
      {
        //continua
      }
      else
      {
        //ASSERT(Scanner_Top(pScanner)->currentItem.token == TK_BREAKLINE);
        if (pScanner->bIncludeSpaces)
        {
          //é para retornar a quebra de linha, entao sair
          break;
        }

        BasicScanner_Next(Scanner_Top(pScanner));
      }
    }

    else if (token == TK_identifier)
    {
      if (!IsIncludeState(state))
      {
        Scanner_Match(pScanner);
        continue;
      }

      BasicScanner* pBasicScanner = Scanner_Top(pScanner);
      const char* lexeme = BasicScanner_Lexeme(pBasicScanner);

      Macro* pMacro2 = Scanner_FindPreprocessorItem2(pScanner, lexeme);

      if (pMacro2 != NULL)
      {
        if (strcmp(pMacro2->Name, "__declspec") == 0)
        {
          pMacro2 = pMacro2;
        }
        StrBuilder strBuilder = STRBUILDER_INIT;
        TokenArray ppTokenArray = TOKENARRAY_INIT;

        //confirma realmente se eh p expandir
        bool bIsMacro = GetNewMacroCallString(pScanner,
          pMacro2,
          &ppTokenArray);

        if (bIsMacro)
        {
          ExpandMacroToText(&ppTokenArray,
            &pScanner->Defines2,
            false,
            false,
            NULL,
            &strBuilder);

          if (strBuilder.size == 0)
          {
            //esta com bug quando expande para nada 
            //so em algum casos
            //enquanto nao debugar melhor
            //este espaco resolve
            StrBuilder_Append(&strBuilder, " ");
          }


          PushExpandedMacro(pScanner,
            pMacro2->Name,
            strBuilder.c_str);

        }

        else
        {
          //ASSERT(false);
        }

        TokenArray2_Destroy(&ppTokenArray);
        StrBuilder_Destroy(&strBuilder);

        if (!bIsMacro)
        {
          break;
        }
      }
      else
      {

        //eh um identificador..sair
        break;

      }
      break;
    }
    else if (token == TK_EOF)
    {
      if (pScanner->stack.size == 1)
      {
        //Scanner_PrintDebug(pScanner);
        //acabou
        //bResult = false;
        break;
      }
      else if (pScanner->stack.size > 0)
      {
        Array_Pop(&pScanner->stack, &Delete_Scanner);
      }
    }

    else
    {
      if (!IsIncludeState(state))
      {
        BasicScanner_Next(Scanner_Top(pScanner));
      }

      else
      {
        break;
      }
    }
  }//for

}

void Scanner_Skip(Scanner* pScanner)
{
  if (pScanner->bError)
  {
    return;
  }

  for (;;)
  {
    Scanner_SkipCore(pScanner);

    if (pScanner->bError)
      break;

    Tokens token = Scanner_Token(pScanner);

    if (token == TK_SPACES ||
      token == TK_BREAKLINE ||
      token == TK_COMMENT ||
      token == TK_LINE_COMMENT)
    {
      if (token == TK_BREAKLINE)
      {
        StrBuilder_Clear(&pScanner->DebugString);
      }

      if (pScanner->bIncludeSpaces)
      {
        break;
      }

      if (token != TK_BREAKLINE)
      {
        StrBuilder_Append(&pScanner->DebugString, " ");
        StrBuilder_Append(&pScanner->DebugString, Scanner_Lexeme(pScanner));
      }

      BasicScanner_Next(Scanner_Top(pScanner));
      continue;
    }

    else if (token == TK_EOF)
    {
      if (pScanner->stack.size == 1)
      {
        //acabou
        //bResult = false;
        break;
      }

      else if (pScanner->stack.size > 1)
      {
        Array_Pop(&pScanner->stack, &Delete_Scanner);
      }
    }

    break;
  }
}

void Scanner_Next(Scanner* pScanner)
{
  if (!pScanner->bError)
  {
    if (pScanner->bHasLookAhead)
    {
      ScannerItem_Reset(&pScanner->LookAhead);
      pScanner->bHasLookAhead = false;
      //Na verdade ja esta apontando para o proximo
      //so nao esta usando
      //agora vai usar
    }

    else
    {
      BasicScanner_Next(Scanner_Top(pScanner));
      Scanner_Skip(pScanner);
    }
  }
}


const char* Scanner_TokenString(Scanner* pScanner)
{
  return TokenToString(Scanner_Top(pScanner)->currentItem.token);
}
//


void PrintPreprocessedToFile(const char* fileIn,
  const char* configFileName,
  const char* fileNameOut)
{
  String fullFileNamePath = STRING_INIT;
  GetFullPath(fileIn, &fullFileNamePath);
  String configFullPath = STRING_INIT;
  GetFullPath(configFileName, &configFullPath);

  Scanner scanner;
  Scanner_Init(&scanner);
  scanner.bIncludeSpaces = true;
  Scanner_IncludeFile(&scanner, fullFileNamePath, FileIncludeTypeFullPath);
  Scanner_IncludeFile(&scanner, configFullPath, FileIncludeTypeFullPath);
  Scanner_Skip(&scanner);
  
  
  FILE* fp = fopen(fileNameOut, "w");

  while (Scanner_Token(&scanner) != TK_EOF)
  {
    BasicScanner* pBasicScanner = Scanner_Top(&scanner);
    Tokens token = pBasicScanner->currentItem.token;
    const char* lexeme = pBasicScanner->currentItem.lexeme.c_str;

    if (token == TK_BREAKLINE)
    {
      fprintf(fp, "%s", lexeme);
    }

    if (token == TK_LINE_COMMENT ||
      token == TK_COMMENT)
    {
      //fprintf(fp, "%s", lexeme);
    }
    else
    {
      fprintf(fp, "%s", lexeme);
    }

    Scanner_Next(&scanner);
  }

  fclose(fp);
  Scanner_Destroy(&scanner);
  String_Destroy(&fullFileNamePath);
  String_Destroy(&configFullPath);
}

void Scanner_GetScannerItemCopy(Scanner* pScanner, ScannerItem* scannerItem)
{
  if (pScanner->bHasLookAhead)
  {
    ScannerItem_Copy(scannerItem, &pScanner->LookAhead);
  }

  else
  {
    ScannerItem_Copy(scannerItem, &Scanner_Top(pScanner)->currentItem);
  }
}


ScannerItem* Scanner_GetLookAhead(Scanner* pScanner)
{
  if (!pScanner->bHasLookAhead)
  {
    //Fabricar o lookahead
    //copia o atual para o loakahead
    ASSERT(Scanner_Top(pScanner)->currentItem.token != TK_SPACES);
    ScannerItem_Copy(&pScanner->LookAhead,
      &Scanner_Top(pScanner)->currentItem);
    //Mover scanner p proximo
    BasicScanner_Next(Scanner_Top(pScanner));
    Scanner_Skip(pScanner);
    //So no fim para que o mover seja normal
    pScanner->bHasLookAhead = true;
    ASSERT(Scanner_Top(pScanner)->currentItem.token != TK_SPACES);
  }

  ASSERT(Scanner_Top(pScanner)->currentItem.token != TK_SPACES);
  return &Scanner_Top(pScanner)->currentItem;
}