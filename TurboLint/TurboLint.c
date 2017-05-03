


#include <stdio.h>

#include ".\Parser\AstPrint.h"
#include ".\Parser\Parser.h"
#include ".\TurboLint\CodePrint.h"
#include ".\TurboLint\TCLint2.h"


void RunLint(const char* configFileName,
             const char* filename)
{
    TProgram program = TPROGRAM_INIT;
    printf("Parsing...\n");
    if(GetAST(filename, configFileName, &program))
    {
        printf("Running Code Analysis...\n");

		
		TProgram_Analize(&program);

		TProgram_PrintAstToFile(&program,
			"C:\\Users\\kiki\\Source\\Repos\\TurboLint\\teste.json"  /*out*/);

        TProgram_PrintCodeToFile(&program,
          "C:\\Users\\kiki\\Source\\Repos\\TurboLint\\teste.c",  /*out*/
          "C:\\Users\\kiki\\Source\\Repos\\TurboLint\\");
		 
        printf("Complete\n");
    }
    TProgram_Destroy(&program);
 }


int main(int argc, char* argv[])
{
   printf("Turbo lint " __DATE__ "\n");

    if(argc < 2)
    {
        printf("TurboLint.exe configFile.txt [file.c]");
        return 1;
    }
    const char* configFileName = argv[1];
    const char* filename = NULL;
    if(argc > 2)
    {
        filename = argv[2];
    }
    if(argc >= 4)
    {
        printf("%s\n\n", argv[3]);
    }
    
    bool bPrintPreprocessed = false;
    for(int i = 3; i < argc; i++)
    {
        const char * option = argv[i];
        if(strcmp(option, "/E") == 0)
        {
            bPrintPreprocessed = true;
        }
        else if(strcmp(option, "/F") == 0)
        {
        }
    }
	
    if(bPrintPreprocessed)
    {
        PrintPreprocessedToFile(filename, configFileName, "pre.txt");
    }
      
    RunLint(configFileName, filename);
    return 0;
}

