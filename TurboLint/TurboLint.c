


#include <stdio.h>

#include ".\Parser\AstPrint.h"
#include ".\Parser\Parser.h"
#include ".\TurboLint\CodePrint.h"
#include ".\TurboLint\TCLint2.h"
#include "..\TurboLint\Base\Path.h"

void RunLint(const char* configFileName,
  const char* inputFileName)
{
  TProgram program = TPROGRAM_INIT;
  printf("Parsing...\n");
  if (GetAST(inputFileName, configFileName, &program))
  {
    printf("Running Code Analysis...\n");


    TProgram_Analize(&program);


    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    SplitPath(inputFileName, drive, dir, fname, ext); // C4996

    char outjs[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME + _MAX_EXT + 1];
    MakePath(outjs, drive, dir, fname, ".json");
 
    if (inputFileName != NULL && 
        program.MySourceDir.size == 1 &&
        strcmp(program.MySourceDir.pItems[0], inputFileName) == 0)
    {
      //nao passa o nome eh considera o dir
      inputFileName = NULL;
    }

    if (program.MySourceDir.size != 0)
    {
      //nao passa o nome eh considera o dir
      inputFileName = NULL;
    }
 

    TProgram_PrintAstToFile(&program, outjs, inputFileName);

    strcat(fname, "_gen");
    MakePath(outjs, drive, dir, fname, ext);

    TProgram_PrintCodeToFile(&program, outjs, inputFileName);

    printf("Complete\n");
  }
  TProgram_Destroy(&program);
}


int main(int argc, char* argv[])
{
  printf("Turbo lint " __DATE__ "\n");

  if (argc < 2)
  {
    printf("TurboLint.exe configFile.txt [file.c]");
    return 1;
  }
  const char* configFileName = argv[1];
  const char* filename = NULL;


  if (argc > 2)
  {

    filename = argv[2];

  }
  if (argc >= 4)
  {
    printf("%s\n\n", argv[3]);
  }

  bool bPrintPreprocessed = false;
  for (int i = 3; i < argc; i++)
  {
    const char * option = argv[i];
    if (strcmp(option, "/E") == 0)
    {
      bPrintPreprocessed = true;
    }
    else if (strcmp(option, "/F") == 0)
    {
    }
  }

  if (bPrintPreprocessed)
  {
    PrintPreprocessedToFile(filename, configFileName, "pre.txt");
  }
  String fullpath = NULL;
  GetFullPath(filename, &fullpath);
  RunLint(configFileName, fullpath);
  String_Destroy(&fullpath);
  return 0;
}

