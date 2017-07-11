


#include <stdio.h>

#include ".\Parser\AstPrint.h"
#include ".\Parser\Parser.h"
#include ".\TurboLint\CodePrint.h"
#include ".\TurboLint\TCLint2.h"
#include "..\TurboLint\Base\Path.h"
#include "UnitTest.h"

void Compile(const char* configFileName,
	const char* inputFileName,
	Options* options)
{
  TProgram program = TPROGRAM_INIT;


	printf("Parsing...\n");
	if (GetAST(inputFileName, configFileName, &program))
	{
		

		//TProgram_Analize(&program);

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

		//TProgram_PrintAstToFile(&program, outjs, inputFileName);

		strcat(fname, "_gen");
		MakePath(outjs, drive, dir, fname, ext);

        printf("Generating code for %s...\n", inputFileName);
		TProgram_PrintCodeToFile(&program, options, outjs, inputFileName);

		printf("Done!\n");
	}
	TProgram_Destroy(&program);
}


int main(int argc, char* argv[])
{
	printf("Turbo lint " __DATE__ "\n");


    //AllTests();

	if (argc < 2)
	{
		printf("TurboLint.exe configFile.txt file.c");
		return 1;
	}


	const char* configFileName = argv[1];
	const char* inputFileName = argv[2];

    if (argc > 2)
    {
        configFileName = argv[1];
        inputFileName = argv[2];
    }
    else
    {
        //nao tem config
        configFileName = NULL;
        inputFileName = argv[1];
    }

	
	bool bPrintPreprocessed = false;
	for (int i = 3; i < argc; i++)
	{
		const char * option = argv[i];
		if (strcmp(option, "-E") == 0)
		{
			bPrintPreprocessed = true;
		}
		else if (strcmp(option, "-F") == 0)
		{
		}		
	}

	if (bPrintPreprocessed)
	{
		PrintPreprocessedToFile(inputFileName, configFileName);
	}

	String inputFullPath = NULL;
	GetFullPath(inputFileName, &inputFullPath);
    
    Options options;
    options.bExpandMacros = false;
    options.bIncludeComments = true;

	Compile(configFileName, inputFullPath, &options);
	String_Destroy(&inputFullPath);

	return 0;
}

