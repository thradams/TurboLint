#include "Scanner.h"
#include "Parser.h"

BasicScanner * Scanner_Top(Scanner * pScanner);;

TMacro* TMacro_Create()
{
    TMacro* p = (TMacro*)malloc(sizeof * p);
    if(p)
    {
        TMacro temp = TMACRO_INIT;
        *p = _move temp;
    }
    return p;
}

void TMacro_Destroy(TMacro* p)
{
    String_Destroy(&p->Name);
    StrArray_Destroy(&p->Args);
    StrBuilder_Destroy(&p->Content);
}

void TMacro_Delete(TMacro* p)
{
    if(p)
    {
        TMacro_Destroy(p);
        free(p);
    }
}
void TMacro_DeleteVoid(void* p)
{
    TMacro_Delete((TMacro*)p);
}

void TMacroMap_Init(TMacroMap* p)
{
    Map_Init(p, 100);
}

void TMacroMap_Destroy(TMacroMap* p)
{
    Map_Destroy(p, TMacro_DeleteVoid);
}

Result TMacroMap_Set(TMacroMap* map, const char* key, TMacro* data)
{
    return Map_Set(map, key, data);
}

TMacro* TMacroMap_Find(TMacroMap* map, const char* key)
{
    return (TMacro*)Map_Find2(map, key);
}

Result TMacroMap_DeleteItem(TMacroMap* map, const char* key)
{
    return Map_DeleteItem(map, key, TMacro_DeleteVoid);
}
void TMacroMap_Swap(TMacroMap *a, TMacroMap *b)
{
    Map_Swap(a, b);
}
//

void TFileMap_Init(TMacroMap* p)
{
    Map_Init(p, 100);
}


TFile* TFile_Create()
{
    TFile* p = (TFile*)malloc(sizeof * p);
    if(p)
    {
        TFile temp = TFILE_INIT;
        *p = _move temp;
    }
    return p;
}

void TFile_Destroy(TFile* p)
{
    String_Destroy(&p->FullPath);
}

void TFile_Delete(TFile* p)
{
    if(p)
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

TFile* _opt TFileMap_Find(TFileMap* map, const char* key)
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
    if(pScanner->StackIfDef.size == 0)
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
    for(size_t i = 0; i < pScanner->stack.size; i++)
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
    if(!pScanner->bError)
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
    for(size_t i = 0; i < pScanner->stack.size; i++)
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
	TMacro* pDefine1 = TMacro_Create();
	String_Set(&pDefine1->Name, name);
	StrBuilder_Append(&pDefine1->Content, value);
	pDefine1->FileIndex = 0;
	TMacroMap_Set(&pScanner->Defines, name, pDefine1);
	return RESULT_OK;
}

static Result Scanner_InitCore(Scanner* pScanner)
{
  


    TMacroMap_Init(&pScanner->Defines);
     
	StrBuilder_Init(&pScanner->DebugString, 100);
	StrBuilder_Init(&pScanner->ErrorString, 100);

    //StrBuilder_Init(&pScanner->DebugString, 100);
    //StrBuilder_Init(&pScanner->ErrorString, 100);
    pScanner->bError = false;
    ArrayInt_Init(&pScanner->StackIfDef);
    pScanner->bPrintIncludes = false;
    pScanner->bExpressionMode = false;
    pScanner->bIncludeSpaces = false;
    Array_Init(&pScanner->stack);
    TFileMap_Init(&pScanner->FilesIncluded);
    StrArray_Init(&pScanner->IncludeDir);

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
                          const char* text,
                          bool bExpressionMode)
{
    Scanner_InitCore(pScanner);
    pScanner->bExpressionMode = bExpressionMode;
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
    if(result == RESULT_OK)
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
    if(bQuotedForm)
    {
        //String s = STRING_INIT;
        //GetFullPath(fileName, &s);
        //String_Destroy(&s);
        if(IsFullPath(fileName))
        {
            //Se ja vier com fullpath?? este caso esta cobrindo
            //mas deve ter uma maneira melhor de verificar se eh um fullpath ja
            bFullPathFound = true;
            String_Set(fullPathOut, fileName);
        }
        else
        {
            if(pScanner->stack.size > 0)
            {
                //tenta nos diretorios ja abertos
                StrBuilder path = STRBUILDER_INIT;
                for(int i = (int)pScanner->stack.size - 1; i >= 0; i--)
                {
                    BasicScanner* p = (BasicScanner*)pScanner->stack.pItems[i];
                    StrBuilder_Set(&path, p->stream.FullDir2);
                    StrBuilder_Append(&path, fileName);
                    bool bFileExists = FileExists(path.c_str);
                    if(bFileExists)
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
                if(bFileExists)
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
    if(!bFullPathFound)
    {
        StrBuilder path = STRBUILDER_INIT;
        //StrBuilder_Init(&path, 200);
        for(size_t i = 0; i < pScanner->IncludeDir.size; i++)
        {
            const char* pItem = pScanner->IncludeDir.pItems[i];
            StrBuilder_Set(&path, pItem);
            StrBuilder_Append(&path, "\\");
            StrBuilder_Append(&path, fileName);
            bool bFileExists = FileExists(path.c_str);
            if(bFileExists)
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
    String fullPath = STRING_INIT;
    String_Init(&fullPath, "");
    //Faz a procura nos diretorios como se tivesse adicinando o include
    //seguindo as mesmas regras. Caso o include seja possivel ele retorna o path completo
    //este path completo que eh usado para efeitos do pragma once.
    bool bHasFullPath = false;
    switch(fileIncludeType)
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
    if(bHasFullPath)
    {
        TFile* _opt pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);
        if(pFile != NULL && pFile->PragmaOnce)
        {
            //foi marcado como pragma once.. nao faz nada
        }
        else
        {
            if(pFile == NULL)
            {
                pFile = TFile_Create();
				
				
				pFile->FileLevel = pScanner->stack.size + 1;

                TFileMap_Set(&pScanner->FilesIncluded, fullPath, pFile); //pfile Moved
            }
            BasicScanner* pNewScanner = NULL;
            Result result = BasicScanner_CreateFile(fullPath, &pNewScanner);
            if(result == RESULT_OK)
            {
                if(pScanner->bPrintIncludes)
                {
                    printf("%s\n", fullPath);
                }
                if(pFile)
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
    return Scanner_Top(pScanner)->stream.NameOrFullPath;
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
    TMacroMap_Destroy(&pScanner->Defines);
    StrBuilder_Destroy(&pScanner->DebugString);
    StrBuilder_Destroy(&pScanner->ErrorString);
    ArrayInt_Destroy(&pScanner->StackIfDef);
    Array_Destroy(&pScanner->stack, &Delete_Scanner);
    TFileMap_Destroy(&pScanner->FilesIncluded);
    StrArray_Destroy(&pScanner->IncludeDir);

    //Valor lido na leitura especulativa
    ScannerItem_Destroy(&pScanner->LookAhead);
}

int Scanner_GetCurrentLine(Scanner* pScanner)
{
    ASSERT(!pScanner->bHasLookAhead);

    if(pScanner->bError)
    {
        return -1;
    }
    if(pScanner->stack.size == 0)
    {
        return -1;
    }
    int currentLine = -1;
    int fileIndex = -1;
    for(int i = (int)pScanner->stack.size - 1; i >= 0; i--)
    {
        BasicScanner* pBasicScanner = (BasicScanner*)pScanner->stack.pItems[i];
        fileIndex = pBasicScanner->FileIndex;
        if(fileIndex >= 0)  //macro eh -1
        {
            currentLine = pBasicScanner->stream.currentLine;
            break;
        }
    }
    return currentLine;
}


int Scanner_GetFileIndex(Scanner* pScanner)
{
    if(pScanner->bError)
    {
        return -1;
    }
    if(pScanner->stack.size == 0)
    {
        return -1;
    }
    int fileIndex = -1;
    for(int i = (int)pScanner->stack.size - 1; i >= 0; i--)
    {
        BasicScanner* pBasicScanner = (BasicScanner*)pScanner->stack.pItems[i];
        fileIndex = pBasicScanner->FileIndex;
        if(fileIndex >= 0)
        {
            break;
        }
    }
    //ASSERT(fileIndex >= 0);
    return fileIndex;
}

Tokens Scanner_Token(Scanner* pScanner)
{

    if(pScanner->bError)
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
      return ((BasicScanner*)Array_Top(&pScanner->stack))->currentItem.token;
        
}

const char* Scanner_Lexeme(Scanner* pScanner)
{
  if (pScanner->bHasLookAhead)
  {
    return pScanner->LookAhead.lexeme.c_str;
  }

    if(pScanner->stack.size == 0)
    {
        return "";
    }
    return ((BasicScanner*)Array_Top(&pScanner->stack))->currentItem.lexeme.c_str;
}

BasicScanner* Scanner_Top(Scanner* pScanner)
{
    
    if(pScanner->stack.size == 0)
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
    while(Scanner_Top(pScanner)->currentItem.token == TK_SPACES)
    {
        BasicScanner_Next(Scanner_Top(pScanner));
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
    while(pTop->currentItem.token != TK_EOF)
    {
        if(pTop->currentItem.token == TK_BREAKLINE)
        {
            //BasicScanner_Next(Scanner_Top(pScanner));
            break;
        }
        BasicScanner_Next(pTop);
    }
}

void GetDefineString(Scanner* pScanner, StrBuilder* strBuilder)
{
    for(;;)
    {
        Tokens token = Scanner_Top(pScanner)->currentItem.token;
        if(token == TK_EOF)
        {
            break;
        }
        if(token == TK_BREAKLINE)
        {
            //deixa o break line
            //BasicScanner_Next(Scanner_Top(pScanner));
            break;
        }
        if(token == TK_COMMENT ||
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

TMacro* _opt Scanner_FindPreprocessorItem(Scanner* pScanner,
                                     const char* key)
{
    TMacro* pMacro = TMacroMap_Find(&pScanner->Defines, key);
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
    TMacroMap* pDefines = &pScanner->Defines;

	//printf("%s = ", s);

    //TODO avaliador de expressoes para pre processador
    //https://gcc.gnu.org/onlinedocs/gcc-3.0.2/cpp_4.html#SEC38
    
    Parser parser;
    Parser_InitString(&parser, "eval expression", s, true);
    
    if(pDefines)
    {
        //usa o mapa de macros para o pre-processador
        Map_Swap(&parser.Scanner.Defines, pDefines);
    }

    Scanner_Next(&parser.Scanner);
    
	
    int iRes = PreprocessorExpression(&parser);


	//printf(" %d\n", iRes);

    if (pDefines)
    {
        Map_Swap(&parser.Scanner.Defines, pDefines);
    }

    if(parser.bError)
    {
        Scanner_SetError(pScanner, parser.ErrorMessage.c_str);
    }

    Parser_Destroy(&parser);
    return iRes;
}


int GetMacroArgumentCount(TMacro* pMacro)
{
    return (int)pMacro->Args.size;
}

const char* GetMacroContent(TMacro* pMacro)
{
    return pMacro->Content.c_str;
}

const char* GetMacroName(TMacro* pMacro)
{
    return pMacro->Name;
}

bool MacroExpandCore(Scanner* pScanner,
                     const char* strInput,
                     StrBuilder* strBuilderResult,
                     StrMap* pReplacementListOpt,
                     StrSet* pAlreadyExpandList,
                     bool bExpressionMode);

//Pega todos os paramtros da chamada da macro e ja expande 100% cada um
static int CollectMacroExpansionArgs(Scanner* pScanner,
                                     BasicScanner* scanner,
                                     StrMap* pNamedArguments,
                                     StrArray* pArgs,
                                     StrMap* pReplacementListOpt,
                                     StrSet* pAlreadyExpandList,
                                     bool bExpressionMode)
{
    //ta  contando errado
    int nArgsFound = 0;
    StrBuilder strBuilderArgument;// = STRBUILDER_INIT;
    StrBuilder_Init(&strBuilderArgument, 100);
    Tokens token = scanner->currentItem.token;
    if(token == TK_LEFT_PARENTHESIS)
    {
        BasicScanner_Next(scanner);
        //comeca com 1
        nArgsFound = 1;
        int iInsideParentesis = 1;
        for(;;)
        {
            token = scanner->currentItem.token;
            if(token == TK_EOF)
            {
                break;
            }
            if(token == TK_LEFT_PARENTHESIS)
            {
                StrBuilder_Append(&strBuilderArgument, scanner->currentItem.lexeme.c_str);
                BasicScanner_Next(scanner);
                iInsideParentesis++;
            }
            else if(token == TK_RIGHT_PARENTHESIS)
            {
                if(iInsideParentesis == 1)
                {
                    //vou expandir isso completamente
                    StrBuilder strBuilderResultLocal;// = STRBUILDER_INIT;
                    StrBuilder_Init(&strBuilderResultLocal, 100);
                    MacroExpandCore(pScanner,
                                    strBuilderArgument.c_str,
                                    &strBuilderResultLocal,
                                    pReplacementListOpt,
                                    pAlreadyExpandList,
                                    bExpressionMode);
                    const char* name = "???";
                    if(pArgs->size > 0)
                    {
                        name = pArgs->pItems[nArgsFound - 1];
                    }
                    else
                    {
                        nArgsFound = 0;
                        // ASSERT(false);
                    }
                    StrMap_Set(pNamedArguments,
                               name,
                               strBuilderResultLocal.c_str);
                    //isso vai virar agumento
                    StrBuilder_Destroy(&strBuilderResultLocal);
                    StrBuilder_Clear(&strBuilderArgument);
                    BasicScanner_Next(scanner);
                    break;
                }
                iInsideParentesis--;
                StrBuilder_Append(&strBuilderArgument, scanner->currentItem.lexeme.c_str);
                BasicScanner_Next(scanner);
            }
            else if(token == TK_COMMA)
            {
                if(iInsideParentesis == 1)
                {
                    //vou expandir isso completamente
                    StrBuilder strBuilderResultLocal;// = STRBUILDER_INIT;
                    StrBuilder_Init(&strBuilderResultLocal, 100);
                    MacroExpandCore(pScanner,
                                    strBuilderArgument.c_str,
                                    &strBuilderResultLocal,
                                    pReplacementListOpt,
                                    pAlreadyExpandList,
                                    bExpressionMode);
                    const char* name = pArgs->pItems[nArgsFound - 1];
                    StrMap_Set(pNamedArguments,
                               name,
                               strBuilderResultLocal.c_str);
                    //isso vai virar agumento
                    StrBuilder_Destroy(&strBuilderResultLocal);
                    StrBuilder_Clear(&strBuilderArgument);
                    nArgsFound++;
                }
                else
                {
                    //continuar...
                    StrBuilder_Append(&strBuilderArgument, scanner->currentItem.lexeme.c_str);
                }
                BasicScanner_Next(scanner);
            }
            else
            {
                StrBuilder_Append(&strBuilderArgument, scanner->currentItem.lexeme.c_str);
                BasicScanner_Next(scanner);
            }
        }
    }
    else
    {
        //oops
    }
    StrBuilder_Destroy(&strBuilderArgument);
    return nArgsFound;
}

static void MacroAppend(StrBuilder* strBuilder,
                        const char* pString,
                        bool bInsertSpace)
{
    if(bInsertSpace)
    {
        if(strBuilder->size != 0 &&
                strBuilder->c_str[strBuilder->size - 1] != ' ')
        {
            StrBuilder_Append(strBuilder, " ");
        }
    }
    else
    {
        //vou colocar um cara invisivel aqui
        char ch[] = { 2, 0 };
        StrBuilder_Append(strBuilder, ch);
    }
    StrBuilder_Append(strBuilder, pString);
}

bool MacroExpandCore(Scanner* pScanner,
                     const char* strInput,
                     StrBuilder* strBuilderResult,
                     StrMap* _opt pReplacementListOpt,
                     StrSet* pAlreadyExpandList,
                     bool bExpressionMode)
{
    StrBuilder inputBuilder;// = STRBUILDER_INIT;
    StrBuilder_Init(&inputBuilder, 100);
    StrBuilder_Append(&inputBuilder, strInput);
    bool bSomeMacroExpanded = false;
    int i = 0;
    for(i = 0; i < 100; i++)
    {
        if(i > 90)
        {
        }
        StrBuilder_Clear(strBuilderResult); //out
        BasicScanner scanner;
        BasicScanner_Init(&scanner, "", inputBuilder.c_str); //colocar em um array?
        BasicScanner_NextNoSpaces(&scanner);
        bSomeMacroExpanded = false;
        bool bInsertSpace = true;
        for(;;)
        {
            Tokens token = scanner.currentItem.token;
            if(token == TK_EOF)
            {
                break;
            }
            const char* lexeme = scanner.currentItem.lexeme.c_str;
            //# pode sair como pre
            if(token == TK_NUMBER_SIGN ||
                    token == TK_PREPROCESSOR)
            {
                BasicScanner_NextNoSpaces(&scanner);
                lexeme = scanner.currentItem.lexeme.c_str;
                const char* pReplaceString = NULL;
                if(pReplacementListOpt != NULL)
                {
                    pReplaceString = StrMap_Find2(pReplacementListOpt, lexeme);
                }
                if(pReplaceString)
                {
                    BasicScanner_NextNoSpaces(&scanner);
                    //forma string
                    StrBuilder_Append(strBuilderResult, "\"");
                    //TODO formar string
                    const char* pArgumentCallString = pReplaceString;
                    StrBuilder_Append(strBuilderResult, pArgumentCallString);
                    StrBuilder_Append(strBuilderResult, "\"");
                }
                else
                {
                    //normal
                    MacroAppend(strBuilderResult, "#", bInsertSpace);
                }
                bInsertSpace = true;
            }
            else if(token == TK_NUMBERNUMBER)
            {
                bInsertSpace = false;
                BasicScanner_NextNoSpaces(&scanner);
            }
            else if(token == TK_MACROPLACEHOLDER)
            {
                bInsertSpace = false;
                BasicScanner_NextNoSpaces(&scanner);
            }
            else
            {
                if(bExpressionMode &&
                        token == TK_identifier &&
                        strcmp(lexeme, "defined") == 0)
                {
                    BasicScanner_NextNoSpaces(&scanner);
                    token = scanner.currentItem.token;
                    if(token == TK_LEFT_PARENTHESIS)
                    {
                        BasicScanner_NextNoSpaces(&scanner); //(
                        lexeme = scanner.currentItem.lexeme.c_str;
                        if(Scanner_FindPreprocessorItem(pScanner, lexeme) != NULL)
                        {
                            StrBuilder_Append(strBuilderResult, "1");
                        }
                        else
                        {
                            StrBuilder_Append(strBuilderResult, "0");
                        }
                        BasicScanner_NextNoSpaces(&scanner); //defined_arg
                        BasicScanner_NextNoSpaces(&scanner); //)
                    }
                    else if(token == TK_identifier)
                    {
                        lexeme = scanner.currentItem.lexeme.c_str;
                        if(Scanner_FindPreprocessorItem(pScanner, lexeme) != NULL)
                        {
                            StrBuilder_Append(strBuilderResult, "1");
                        }
                        else
                        {
                            StrBuilder_Append(strBuilderResult, "0");
                        }
                        BasicScanner_NextNoSpaces(&scanner); //defined_arg
                    }
                }
                else
                {
                    StrBuilder macroName;// = STRBUILDER_INIT;
                    StrBuilder_Init(&macroName, 100);
                    StrBuilder_Append(&macroName, lexeme);
                    int nArgsExpected = -1;// GetMacroArgumentCount(pMacroReplace);
                    //  TMacro* pArgs = NULL; // JObj_Find(pMacroReplace, "args");
                    TMacro* pMacroReplace = NULL;
                    const char* pReplaceString = NULL;
                    if(pReplacementListOpt != NULL)
                    {
                        pReplaceString = StrMap_Find2(pReplacementListOpt, lexeme);
                    }
                    if(pReplaceString)
                    {
                        //se o proximo do array eh ##
                        //vai ficar sem espaco
                        const char* pArgumentCallString = pReplaceString;
                        MacroAppend(strBuilderResult,
                                    pArgumentCallString,
                                    bInsertSpace);
                        BasicScanner_NextNoSpaces(&scanner);
                        pMacroReplace = NULL;
                    }
                    else
                    {
                        bool bHasKey = StrSet_HasKey(pAlreadyExpandList, lexeme);
                        if(!bHasKey)
                        {
                            pMacroReplace = Scanner_FindPreprocessorItem(pScanner, lexeme);
                            if(pMacroReplace)
                            {
                                nArgsExpected = GetMacroArgumentCount(pMacroReplace);
                                //pArgs = JObj_Find(pMacroReplace, "args");
                            }
                        }
                        else
                        {
                            MacroAppend(strBuilderResult,
                                        lexeme,
                                        bInsertSpace);
                            BasicScanner_NextNoSpaces(&scanner);
                            pMacroReplace = NULL;
                        }
                        if(pMacroReplace)
                        {
                            //vou colocar numa lista de ja trocadas
                            BasicScanner_NextNoSpaces(&scanner);
                            //int nArgsFound = 0;
                            bSomeMacroExpanded = true;
                            //vou separar em numero de argumento e expandir cada um
                            //pMacroReplace
                            StrMap namedArguments;
                            StrMap_Init(&namedArguments, 10);
                            //JObj_CreateObject(&pNamedArguments, DEFAULT_OBJECT_BUCKETS);
                            //arranca a lista de chamada de cada argumento
                            //100% expandido
                            int iArgsFound = CollectMacroExpansionArgs(pScanner,
                                             &scanner,
                                             &namedArguments,
                                             &pMacroReplace->Args,
                                             pReplacementListOpt, //usa a mesma lista
                                             pAlreadyExpandList,
                                             bExpressionMode);
                            if(nArgsExpected != -1 &&
                                    iArgsFound != nArgsExpected)
                            {
                                if(iArgsFound == 0 && nArgsExpected > 0)
                                {
                                    /*
                                    #define X(a) a
                                    #define F(a) a
                                    F(X); //X;
                                    */
                                    bSomeMacroExpanded = false;
                                    MacroAppend(strBuilderResult,
                                                macroName.c_str,
                                                bInsertSpace);
                                    BasicScanner_NextNoSpaces(&scanner);
                                }
                                else
                                {
                                    ASSERT(false);
                                    //                  JObj_PrintDebug(pMacroReplace);
                                    Scanner_PrintDebug(pScanner);
                                }
                            }
                            else
                            {
                                //usa a lista expandida para fazer a chamada
                                //como sendo os parametros a serem substituidos
                                //JObj_PrintDebug(pNamedArguments);
                                const char* content = GetMacroContent(pMacroReplace);
                                StrBuilder strBuilderResultLocal;// = STRBUILDER_INIT;
                                StrBuilder_Init(&strBuilderResultLocal, 100);
                                if(StrSet_HasKey(pAlreadyExpandList, GetMacroName(pMacroReplace)))
                                {
                                }
                                else
                                {
                                    StrSet_SetKey(pAlreadyExpandList, GetMacroName(pMacroReplace));
                                }
                                MacroExpandCore(pScanner,
                                                content,
                                                &strBuilderResultLocal,
                                                &namedArguments,
                                                pAlreadyExpandList,
                                                bExpressionMode);
                                //PODE USAR DE NOVO
                                StrSet_DeleteKey(pAlreadyExpandList, GetMacroName(pMacroReplace));
                                MacroAppend(strBuilderResult,
                                            strBuilderResultLocal.c_str,
                                            bInsertSpace);
                                StrBuilder_Destroy(&strBuilderResultLocal);
                                StrMap_Destroy(&namedArguments);
                            }
                        }
                        else
                        {
                            //nao eh macro
                            MacroAppend(strBuilderResult,
                                        scanner.currentItem.lexeme.c_str,
                                        bInsertSpace);
                            BasicScanner_NextNoSpaces(&scanner);
                        }
                    }
                    bInsertSpace = true;
                    StrBuilder_Destroy(&macroName);
                } //not expression mode
            }
        }
        //terminou de expandir
        if(bSomeMacroExpanded)
        {
            //se tem mais.. o result vira input novamente
            StrBuilder_Swap(strBuilderResult, &inputBuilder);
        }
        BasicScanner_Destroy(&scanner);
        if(!bSomeMacroExpanded)
        {
            break;
        }
    }
    if(i >= 100)
    {
        ///macros recursivas
        /*

        #define _In_function_class_(x)  _In_function_class_(#x)
        #define _Called_from_function_class_(x) _In_function_class_(x)



        #define __PRIMOP(a,b)

        __PRIMOP(int, _In_function_class_(__In_impl_ char*);)

        #define _In_function_class_(x)  _In_function_class_(#x)
        #define _Called_from_function_class_(x) _In_function_class_(x)
        */
        StrBuilder_Clear(strBuilderResult);
        //Scanner_PrintDebug(pScanner);
        //ASSERT(false);
    }
    //Scanner_PrintDebug(pScanner);
    StrBuilder_Clear(&inputBuilder);
    for(size_t j = 0; j < strBuilderResult->size; j++)
    {
        char ch = strBuilderResult->c_str[j];
        if(ch != 2)
        {
            StrBuilder_AppendChar(&inputBuilder, strBuilderResult->c_str[j]);
        }
        else
        {
            ch = 0;
        }
    }
    StrBuilder_Swap(&inputBuilder, strBuilderResult);
    StrBuilder_Destroy(&inputBuilder);
    return bSomeMacroExpanded;
}


//Arranca do prscanenr os tokens que sao a chamada da macro
//Pode nao ser macro se for verificado que nao tem parametros
static bool GetMacroCallString(Scanner* pScanner,
                               TMacro* pMacro,
                               StrBuilder* strBuilderResult)
{
    StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
    //StrBuilder macroName;
    //StrBuilder_Init(&macroName, 100);
    //StrBuilder_Append(&macroName, lexeme);
    //identificador com nome da macro
    //BasicScanner_Next(Scanner_Top(pScanner));
    //Pode ter espaço na hora de chamar a macro
    Scanner_Match(pScanner);
    //verificar se tem parametros
    int nArgsExpected = GetMacroArgumentCount(pMacro);
    int nArgsFound = 0;
    //fazer uma lista com os parametros
    if(nArgsExpected > 0)
    {
        Tokens token = Scanner_Token(pScanner);
        if(token == TK_LEFT_PARENTHESIS)
        {
            StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
            BasicScanner_Next(Scanner_Top(pScanner));
            //comeca com 1
            nArgsFound = 1;
            int iInsideParentesis = 1;
            for(;;)
            {
                token = Scanner_Token(pScanner);
                if(token == TK_LEFT_PARENTHESIS)
                {
                    StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
                    BasicScanner_Next(Scanner_Top(pScanner));
                    iInsideParentesis++;
                }
                else if(token == TK_RIGHT_PARENTHESIS)
                {
                    if(iInsideParentesis == 1)
                    {
                        StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
                        BasicScanner_Next(Scanner_Top(pScanner));
                        break;
                    }
                    iInsideParentesis--;
                    StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
                    BasicScanner_Next(Scanner_Top(pScanner));
                }
                else if(token == TK_COMMA)
                {
                    if(iInsideParentesis == 1)
                    {
                        nArgsFound++;
                    }
                    else
                    {
                        //continuar...
                    }
                    StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
                    BasicScanner_Next(Scanner_Top(pScanner));
                }
                else
                {
                    StrBuilder_Append(strBuilderResult, Scanner_Lexeme(pScanner));
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
    if(nArgsExpected != nArgsFound)
    {
        if(nArgsFound == 0 && nArgsExpected > 0)
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
    for(int i = 0; i < sizeof(s_PreTokens) / sizeof(s_PreTokens[0]); i++)
    {
        if(strcmp(lexeme, s_PreTokens[i]) == 0)
        {
            return (PreTokens)i;
        }
    }
    return PRETK_NONE;
}


void Scanner_SkipCore(Scanner* pScanner)
{
    StrSet alreadyExpandList;
    StrSet_Init(&alreadyExpandList, 100);
    for(; ;)
    {
        if(pScanner->bError)
            break;
        Tokens token = Scanner_Token(pScanner);
        State state = StateTop(pScanner);
        if(token == TK_PREPROCESSOR)
        {
            Scanner_Match(pScanner);
            const char* lexeme = Scanner_Top(pScanner)->currentItem.lexeme.c_str;
            token = Scanner_Token(pScanner);
            PreTokens preToken = FindPreToken(lexeme);
            if(preToken == PRETK_INCLUDE)
            {
                if(!IsIncludeState(state))
                {
                    Scanner_Match(pScanner);
                    continue;
                }
                Scanner_Match(pScanner);
                if(GetToken(pScanner) == TK_string_literal)
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
                else if(GetToken(pScanner) == TK_LESS_THAN_SIGN)
                {
                    Scanner_Match(pScanner);
                    StrBuilder path = STRBUILDER_INIT;
                    //StrBuilder_Init(&path, 200);
                    for(;;)
                    {
                        if(GetToken(pScanner) == TK_GREATER_THAN_SIGN)
                        {
                            Scanner_Match(pScanner);
                            break;
                        }
                        if(GetToken(pScanner) == TK_BREAKLINE)
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
            else if(preToken == PRETK_PRAGMA)
            {
                if(!IsIncludeState(state))
                {
                    IgnorePreProcessor(pScanner);
                    continue;
                }
                Scanner_Match(pScanner);
                if(BasicScanner_IsLexeme(Scanner_Top(pScanner), "once"))
                {
                    const char* fullPath = Scanner_Top(pScanner)->stream.NameOrFullPath;
                    TFile* pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);
                    if(pFile == NULL)
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
                else if(BasicScanner_IsLexeme(Scanner_Top(pScanner), "dir"))
                {
                    Scanner_Match(pScanner);
                    String fileName;
                    String_Init(&fileName, Scanner_Lexeme(pScanner) + 1);
                    Scanner_Match(pScanner);
                    fileName[strlen(fileName) - 1] = 0;
                    StrArray_Push(&pScanner->IncludeDir, fileName);
                    String_Destroy(&fileName);
                }
                else if(BasicScanner_IsLexeme(Scanner_Top(pScanner), "ignore"))
                {
                    Scanner_Match(pScanner);
                    String fileName;
                    String_Init(&fileName, Scanner_Lexeme(pScanner) + 1);
                    Scanner_Match(pScanner);
                    fileName[strlen(fileName) - 1] = 0;
                    TFile* pFile = TFile_Create();
                    TFileMap_Set(&pScanner->FilesIncluded, fileName, pFile);
                }
                else if(BasicScanner_IsLexeme(Scanner_Top(pScanner), "push_macro"))
                {
                    Scanner_Match(pScanner);
                    Scanner_Match(pScanner); //(
                    Scanner_Match(pScanner);  //""
                    Scanner_Match(pScanner); //)
                    //salva a macro em uma pilha
                }
                else if(BasicScanner_IsLexeme(Scanner_Top(pScanner), "pop_macro"))
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
            else if(preToken == PRETK_IF ||
                    preToken == PRETK_IFDEF ||
                    preToken == PRETK_IFNDEF)
            {
                Scanner_Match(pScanner);
                switch(state)
                {
                    case NONE:
                    case I1:
                    case E1:
                    {
                        int iRes = 0;
                        if(preToken == PRETK_IF)
                        {
                            StrBuilder strMacroCall = STRBUILDER_INIT;
                            //StrBuilder_Init(&strMacroCall, 100);
                            GetDefineString(pScanner, &strMacroCall);
                            StrBuilder strBuilderResult = STRBUILDER_INIT;
                            //StrBuilder_Init(&strBuilderResult, 100);
                            MacroExpandCore(pScanner,
                                            strMacroCall.c_str,
                                            &strBuilderResult,
                                            NULL,
                                            &alreadyExpandList,
                                            true);
                            iRes = EvalExpression(strBuilderResult.c_str, pScanner);
                            StrBuilder_Destroy(&strMacroCall);
                            StrBuilder_Destroy(&strBuilderResult);
                        }
                        else
                        {
                            bool bFound = Scanner_FindPreprocessorItem(pScanner, lexeme) != NULL;
                            if(preToken == PRETK_IFDEF)
                            {
                                iRes = bFound ? 1 : 0;
                            }
                            else //if (preToken == PRETK_IFNDEF)
                            {
                                iRes = !bFound ? 1 : 0;
                            }
                        }
                        if(iRes != 0)
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
            else if(preToken == PRETK_ELIF)
            {
                Scanner_Match(pScanner);
                switch(state)
                {
                    case NONE:
                    case I1:
                        pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = E0;
                        break;
                    case I0:
                    {
                        int iRes = 0;
                        StrBuilder strMacroCall = STRBUILDER_INIT;
                        //StrBuilder_Init(&strMacroCall, 100);
                        GetDefineString(pScanner, &strMacroCall);
                        StrBuilder strBuilderResult = STRBUILDER_INIT;
                        //StrBuilder_Init(&strBuilderResult, 100);
                        MacroExpandCore(pScanner,
                                        strMacroCall.c_str,
                                        &strBuilderResult,
                                        NULL,
                                        &alreadyExpandList,
                                        true);
                        iRes = EvalExpression(strBuilderResult.c_str, pScanner);
                        StrBuilder_Destroy(&strMacroCall);
                        StrBuilder_Destroy(&strBuilderResult);
                        if(pScanner->StackIfDef.size >= 2)
                        {
                            if((pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 2] == I1 ||
                                    pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 2] == E1))
                            {
                                if(iRes)
                                {
                                    pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = I1;
                                }
                            }
                        }
                        else
                        {
                            if(iRes)
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
            else if(preToken == PRETK_ENDIF)
            {
                IgnorePreProcessor(pScanner);
                StatePop(pScanner);
            }
            else if(preToken == PRETK_ELSE)
            {
                IgnorePreProcessor(pScanner);
                switch(state)
                {
                    case NONE:
                        ASSERT(0);
                        break;
                    case I1:
                        pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 1] = E0;
                        break;
                    case I0:
                        if(pScanner->StackIfDef.size >= 2)
                        {
                            if((pScanner->StackIfDef.pItems[pScanner->StackIfDef.size - 2] == I1 ||
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
            else if(preToken == PRETK_ERROR)
            {
                if(!IsIncludeState(state))
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
            else if(preToken == PRETK_LINE)
            {
                IgnorePreProcessor(pScanner);
            }
            else if(preToken == PRETK_UNDEF)
            {
                if(!IsIncludeState(state))
                {
                    IgnorePreProcessor(pScanner);
                    continue;
                }
                Scanner_Match(pScanner);
                lexeme = BasicScanner_Lexeme(Scanner_Top(pScanner));
                if(strcmp(lexeme, "__ANNOTATION") == 0)
                {
                    TMacroMap_DeleteItem(&pScanner->Defines, lexeme);
                }
                else
                {
                    TMacroMap_DeleteItem(&pScanner->Defines, lexeme);
                }
                IgnorePreProcessor(pScanner);
            }
            else if(preToken == PRETK_DEFINE)
            {
                Scanner_Match(pScanner);
                if(!IsIncludeState(state))
                {
                    IgnorePreProcessor(pScanner);
                    break;
                }
                lexeme = BasicScanner_Lexeme(Scanner_Top(pScanner));
                TMacro* pDefine = Scanner_FindPreprocessorItem(pScanner, lexeme);
                //TMacro* pArgs = NULL;
                if(pDefine != NULL)
                {
                    //warning!
                    //ja foi definido  - fontes da MS
                    /*
                    #define __inout_ecount_z_opt(size)                               _SAL1_Source_(__inout_ecount_z_opt, (size), __inout_ecount_opt(size) __pre __nullterminated __post __nullterminated)
                    #define __inout_ecount_z_opt(size)                               _SAL1_Source_(__inout_ecount_z_opt, (size), __inout_ecount_opt(size) __pre __nullterminated __post __nullterminated)
                    */
                    //ASSERT(false);
                    //Scanner_PrintDebug(pScanner);
                    //JObj_DeleteKey(pScanner->Defines2, lexeme);
                    TMacroMap_DeleteItem(&pScanner->Defines, lexeme);
                    // ASSERT(JObj_Find(pScanner->Defines, lexeme) == NULL);
                    pDefine = TMacro_Create();
                    String_Set(&pDefine->Name, lexeme);
                    pDefine->FileIndex = Scanner_GetFileIndex(pScanner);
                    TMacroMap_Set(&pScanner->Defines, lexeme, pDefine);
                    //pDefine = JObj_SetNewObject(pScanner->Defines2, lexeme);
                    //JObj_SetString(pDefine, "name", lexeme);
                    //pArgs = JObj_SetNewArray(pDefine, "args");
                }
                else
                {
                    pDefine = TMacro_Create();
                    pDefine->FileIndex = Scanner_GetFileIndex(pScanner);
                    String_Set(&pDefine->Name, lexeme);
                    TMacroMap_Set(&pScanner->Defines, lexeme, pDefine);
                }
                //Scanner_Match(pScanner);
                BasicScanner_Next(Scanner_Top(pScanner));
                //AQUI NAO PODE IGNORAR ESPACOS!
                //SE ESTA GRUADO EH MACRO COM PARAMETROS
                /*
                #define X 1
                #define A(a, b) a X  b X
                A(1, 2)
                VERSUS
                #define X 1
                #define A (a, b) a X  b X
                A(1, 2)
                */
                //SkipSpaces(pScanner);
                //verificar se tem parametros
                if(Scanner_Token(pScanner) == TK_LEFT_PARENTHESIS)
                {
                    Scanner_Match(pScanner);
                    for(;;)
                    {
                        token = Scanner_Token(pScanner);
                        if(token == TK_RIGHT_PARENTHESIS)
                        {
                            Scanner_Match(pScanner);
                            break;
                        }
                        if(token == TK_BREAKLINE ||
                                token == TK_EOF)
                        {
                            //oopss
                            break;
                        }
                        lexeme = BasicScanner_Lexeme(Scanner_Top(pScanner));
                        StrArray_Push(&pDefine->Args, lexeme);
                        //JObj_PushString(pArgs, lexeme);
                        Scanner_Match(pScanner);
                        token = Scanner_Token(pScanner);
                        if(token == TK_COMMA)
                        {
                            Scanner_Match(pScanner);
                            //tem mais
                        }
                    }
                }
                StrBuilder strBuilder = STRBUILDER_INIT;
                //StrBuilder_Init(&strBuilder, 100);
                GetDefineString(pScanner, &strBuilder);
                //JObj_SetString(pDefine, "content", strBuilder.c_str);
                StrBuilder_Swap(&pDefine->Content, &strBuilder);
                StrBuilder_Destroy(&strBuilder);
            }
            else
            {
                IgnorePreProcessor(pScanner);
            }
            //todos acabam com final de linha exceto o include
            if(preToken == PRETK_INCLUDE)
            {
                //continua
            }
            else
            {
                //ASSERT(Scanner_Top(pScanner)->currentItem.token == TK_BREAKLINE);
                if(pScanner->bIncludeSpaces)
                {
                    //é para retornar a quebra de linha, entao sair
                    break;
                }
                BasicScanner_Next(Scanner_Top(pScanner));
            }
        }
        else if(token == TK_identifier)
        {
            if(!IsIncludeState(state))
            {
                Scanner_Match(pScanner);
                continue;
            }
            BasicScanner* pBasicScanner = Scanner_Top(pScanner);
            TMacro* pMacro = NULL;
            if(pBasicScanner->bMacroExpanded)
            {
                //
                //
                //
                ///////////////////#define X(B) (X , B)
                // X(1)
                ///depois que expande ele fica marcado para nao expandar mais
            }
            else
            {
                const char* lexeme = BasicScanner_Lexeme(pBasicScanner);
                //pMacro = Scanner_FindPreprocessorItem(pScanner, lexeme);
                //testar se ja foi expandida
                bool bHasKey = StrSet_HasKey(&alreadyExpandList, lexeme);
                if(!bHasKey)
                {
                    pMacro = Scanner_FindPreprocessorItem(pScanner, lexeme);
                }
                else
                {
                    //Evita recursao infinita
                    pMacro = NULL;
                    //MacroAppend(strBuilderResult,
                    //  pArgumentCallString,
                    //bInsertSpace);
                    //BasicScanner_NextNoSpaces(&scanner);
                    //pMacro = NULL;
                    //nao eh macro
                    //MacroAppend(&strBuilderResult,
                    //  lexeme,
                    //true);
                    //BasicScanner_NextNoSpaces(&scanner);
                }
            }
            if(pMacro != NULL)
            {
                //JObj_SetInt(pAlreadyExpandList, lexeme, 1);
                //faz uma string que representa a chamada da macro
                StrBuilder strMacroCall = STRBUILDER_INIT;
                //StrBuilder_Init(&strMacroCall, 100);
                bool bIsMacro = GetMacroCallString(pScanner, pMacro, &strMacroCall);
                if(bIsMacro)
                {
                    StrBuilder strBuilderResult;// = STRBUILDER_INIT;
                    StrBuilder_Init(&strBuilderResult, 100);
                    
                    bool bExpressionMode =
                        pScanner->bExpressionMode;
                    //expanda a chamda da macro
                    MacroExpandCore(pScanner,
                                    strMacroCall.c_str,
                                    &strBuilderResult,
                                    NULL,
                                    &alreadyExpandList,
                                    bExpressionMode);
                    //      JObj_SetInt(pAlreadyExpandList, GetMacroName(pMacro), 1);
                    //o retorno esta expandido e agora vira um stream.
                    //////////////////////////
                    /*
                      Para resolver o seguinte:
                      #define _CRT_MEMCPY_S_INLINE static __inline
                      _CRT_MEMCPY_S_INLINE int()
                      {
                      }
                      estava expandindo para staticint()
                    */
                    StrBuilder_Append(&strBuilderResult, " ");
                    ////////////////////
                    //os valores ja expandidos nao serao mais expandidos
                    //neste stream - vai ter que manter a lista
                    //uo um flag de nao expandir mais nada aqui
                    PushExpandedMacro(pScanner,
                                      GetMacroName(pMacro),
                                      strBuilderResult.c_str);
                    StrBuilder_Destroy(&strBuilderResult);
                    StrBuilder_Destroy(&strMacroCall);
                }
                else
                {
                    PushExpandedMacro(pScanner,
                                      GetMacroName(pMacro),
                                      strMacroCall.c_str);
                }
                continue;
            }
            else
            {
                if(!IsIncludeState(state))
                {
                }
                else
                {
                    //eh um identificador..sair
                    break;
                }
            }
            break;
        }
        else if(token == TK_EOF)
        {
            if(pScanner->stack.size == 1)
            {
                //Scanner_PrintDebug(pScanner);
                //acabou
                //bResult = false;
                break;
            }
            else if(pScanner->stack.size > 0)
            {
                Array_Pop(&pScanner->stack, &Delete_Scanner);
            }
        }
        else
        {
            if(!IsIncludeState(state))
            {
                BasicScanner_Next(Scanner_Top(pScanner));
            }
            else
            {
                break;
            }
        }
    }//for
    StrSet_Destroy(&alreadyExpandList);
    //const char* lexeme = BasicScanner_Lexeme(Scanner_Top(pScanner));
    //if (strcmp(lexeme, "_USE_DECLSPECS_FOR_SAL") == 0)
    //{
    //  Scanner_PrintDebug(pScanner);
    //        ASSERT(false);
    //  }
}

void Scanner_Skip(Scanner* pScanner)
{
    if(pScanner->bError)
    {
        return;
    }
    for(;;)
    {
        Scanner_SkipCore(pScanner);
        if(pScanner->bError)
            break;
        Tokens token = Scanner_Token(pScanner);
        if(token == TK_SPACES ||
                token == TK_BREAKLINE ||
                token == TK_COMMENT ||
                token == TK_LINE_COMMENT)
        {
            if(token == TK_BREAKLINE)
            {
                StrBuilder_Clear(&pScanner->DebugString);
            }
            if(pScanner->bIncludeSpaces)
            {
                break;
            }
            if(token != TK_BREAKLINE)
            {
                StrBuilder_Append(&pScanner->DebugString, " ");
                StrBuilder_Append(&pScanner->DebugString, Scanner_Lexeme(pScanner));
            }
            BasicScanner_Next(Scanner_Top(pScanner));
            continue;
        }
        else if(token == TK_EOF)
        {
            if(pScanner->stack.size == 1)
            {
                //acabou
                //bResult = false;
                break;
            }
            else if(pScanner->stack.size > 1)
            {
                Array_Pop(&pScanner->stack, &Delete_Scanner);
            }
        }
        break;
    }
}

void Scanner_Next(Scanner* pScanner)
{
    if(!pScanner->bError)
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
    FILE* fp = fopen(fileNameOut, "w");
    while(Scanner_Token(&scanner) != TK_EOF)
    {
        BasicScanner* pBasicScanner = Scanner_Top(&scanner);
        Tokens token = pBasicScanner->currentItem.token;
        const char* lexeme = pBasicScanner->currentItem.lexeme.c_str;
        if(token == TK_BREAKLINE)
        {
            fprintf(fp, "%s", lexeme);
        }
        if(token == TK_LINE_COMMENT ||
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
    //  JObj_PrintToFile(scanner.Defines2, "defines.json");
    //  JObj_PrintToFile(scanner.IncludedWithPragmaOnce2, "once.json");
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