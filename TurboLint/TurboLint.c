


#include <stdio.h>

#include ".\Parser\AstPrint.h"
#include ".\Parser\Parser.h"
#include ".\TurboLint\CodePrint.h"
#include ".\TurboLint\TCLint2.h"

void PrintASTToFile(const char* filename,
                    const char* configFileName,
                    const char* outFileName,
	                const char* userpath)
{
    TProgram program = TPROGRAM_INIT;
    GetAST(filename, configFileName, &program);
   // TProgram_PrintLocalsToFile(&program,
     //                          outFileName,
       //                        2);

	TProgram_PrintCodeToFile(&program,
		outFileName,
		2,
		userpath);

    TProgram_Destroy(&program);
}


void RunLint(const char* configFileName,
             const char* filename)
{
    TProgram program = TPROGRAM_INIT;
    printf("Parsing...\n");
    if(GetAST(filename, configFileName, &program))
    {
        printf("Running Code Analysis...\n");

		
		 TProgram_Analize(&program,
			1,
			"");

        //RunStaticAnalysis(&program);
        //RunStaticAnalysis2(&program);
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
	
    //if(bPrintPreprocessed)
    {
        PrintPreprocessedToFile(filename, configFileName, "pre.txt");
    }
    
    //PrintPreprocessedToFile(filename, configFileName, "pre.txt");
	//const char* userpath = "C:\\Users\\thiago\\TurboLint";
	//const char* userpath = "C:\\ThiagoDevel\\MobileServer\\MobileServer";
    //PrintASTToFile(filename, configFileName, "teste.cpp", userpath);

    //Aqui poderia ir uma lista de folders
    //que sera convertida array de indices..
    //de arquivos que estao naquele folder
    RunLint(configFileName, filename);
    return 0;
}

