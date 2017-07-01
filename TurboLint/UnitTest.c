#include "UnitTest.h"
#include "Base\Stream.h"
#include "Parser\BasicScanner.h"
#include "Parser\Scanner.h"

#include <stdio.h>
#include <string.h>

static int error_count = 0;
static int sucess_count = 0;

#define TEST(condition) \
if (condition)\
{\
  sucess_count++;\
}\
else\
{\
  printf("LINE %d FAILED!\n", __LINE__); \
  error_count++;\
}


#define MATCH(scanner, TK) \
 TEST(Scanner_CurrentToken((scanner)) == TK&& \
      Scanner_IsActiveGroup((scanner)));\
 Scanner_Match((scanner));

#define MATCH_INACTIVE(scanner, TK) \
 TEST(Scanner_CurrentToken((scanner)) == TK && \
      !Scanner_IsActiveGroup((scanner)));\
 Scanner_Match((scanner));

#define  MATCH_INACTIVE2(scanner, TK, lexeme)\
TEST(Scanner_CurrentToken((scanner)) == TK &&\
     strcmp(Scanner_CurrentLexeme(scanner), lexeme) == 0 &&\
     !Scanner_IsActiveGroup((scanner)));\
Scanner_Match((scanner));

#define  MATCH2(scanner, TK, lexeme)\
TEST(Scanner_CurrentToken((scanner)) == TK &&\
     strcmp(Scanner_CurrentLexeme(scanner), lexeme) == 0 &&\
     Scanner_IsActiveGroup((scanner)));\
Scanner_Match((scanner));

void Test1()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test1.h", FileIncludeTypeQuoted);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)

        TEST(Scanner_LookAheadToken(&scanner2, 1) == TK_DECIMAL_INTEGER);
    TEST(Scanner_LookAheadToken(&scanner2, 1) == TK_DECIMAL_INTEGER);
    TEST(Scanner_LookAheadToken(&scanner2, 2) == TK_MACRO_EOF);
    TEST(Scanner_LookAheadToken(&scanner2, 3) == TK_BREAKLINE);
    TEST(Scanner_LookAheadToken(&scanner2, 4) == TK_EOF);
    TEST(Scanner_LookAheadToken(&scanner2, 5) == TK_EOF);
    TEST(Scanner_LookAheadToken(&scanner2, 6) == TK_EOF);

    MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)

        Scanner_Destroy(&scanner2);
}

void Test2()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test2.h", FileIncludeTypeQuoted);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)

        Scanner_Destroy(&scanner2);
}
void Test3()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test3.h", FileIncludeTypeQuoted);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_STRING_LITERAL)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)



        Scanner_Destroy(&scanner2);
}

void Test4()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test4.h", FileIncludeTypeQuoted);

    MATCH(&scanner2, TK_BOF)

        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_LEFT_PARENTHESIS)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_PLUS_SIGN)
        MATCH(&scanner2, TK_SPACES)
        MATCH2(&scanner2, TK_IDENTIFIER, "foo")
        MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)

        Scanner_Destroy(&scanner2);
}

void Test5()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test5.h", FileIncludeTypeQuoted);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH2(&scanner2, TK_STRING_LITERAL, "\"x ## y\"")
        MATCH(&scanner2, TK_MACRO_EOF)

        Scanner_Destroy(&scanner2);
}
void Test6()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test6.h", FileIncludeTypeQuoted);
    MATCH(&scanner2, TK_BOF)
        MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_IF)
        MATCH2(&scanner2, TK_IDENTIFIER, "A")
        MATCH(&scanner2, TK_SPACES)
        MATCH2(&scanner2, TK_IDENTIFIER, "B")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH_INACTIVE(&scanner2, TK_PRE_ELSE)

        //MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
        MATCH_INACTIVE(&scanner2, TK_IDENTIFIER, "B")
        MATCH_INACTIVE(&scanner2, TK_SPACES)
        MATCH_INACTIVE(&scanner2, TK_IDENTIFIER, "D")
        MATCH_INACTIVE(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_ENDIF)
        //MATCH(&scanner2, TK_BREAKLINE) //#endif

        MATCH2(&scanner2, TK_IDENTIFIER, "END")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)
        Scanner_Destroy(&scanner2);
    ///////////////////////////
}

void Test7()
{
    //
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test7.h", FileIncludeTypeQuoted);
    MATCH(&scanner2, TK_BOF)
    //Test7.h
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_PRE_PRAGMA)
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_VOID)
    MATCH(&scanner2, TK_SPACES)
    MATCH(&scanner2, TK_IDENTIFIER)
    MATCH(&scanner2, TK_LEFT_PARENTHESIS)
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
    MATCH(&scanner2, TK_SEMICOLON)
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_EOF)
    //Test7.h
    Scanner_Destroy(&scanner2);
    ///////////////////////////

    Scanner_Init(&scanner2);
    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test7.c", FileIncludeTypeQuoted);
    MATCH(&scanner2, TK_BOF)
        
        MATCH(&scanner2, TK_PRE_INCLUDE)

        //Test7.h
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_PRAGMA)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_VOID)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_IDENTIFIER)
        MATCH(&scanner2, TK_LEFT_PARENTHESIS)
        MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
        MATCH(&scanner2, TK_SEMICOLON)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_FILE_EOF)
        //Test7.h

        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_VOID)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_IDENTIFIER)
        MATCH(&scanner2, TK_LEFT_PARENTHESIS)
        MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
        MATCH(&scanner2, TK_SEMICOLON)
        MATCH(&scanner2, TK_BREAKLINE)

        MATCH(&scanner2, TK_EOF)
        Scanner_Destroy(&scanner2);

}

void Test()
{
    printf("RUNNING TESTS ...\n");
    Test7();
    Test3();


    Test1();
    Test2();
    
    Test4();
    Test5();
    Test6();
    
    
    SStream stream;
    SStream_Init(&stream, "name", "123");
    TEST(stream.currentChar == '1');
    TEST(SStream_LookAhead(&stream) == '2');
    SStream_Next(&stream);
    TEST(stream.currentChar == '2');
    TEST(SStream_LookAhead(&stream) == '3');
    SStream_Next(&stream);

    TEST(stream.currentChar == '3');
    TEST(SStream_LookAhead(&stream) == '\0');

    SStream_Next(&stream);
    TEST(stream.currentChar == '\0');
    TEST(SStream_LookAhead(&stream) == '\0');

    SStream_Next(&stream);

    TEST(stream.currentChar == '\0');
    TEST(SStream_LookAhead(&stream) == '\0');


    BasicScanner scanner;

    BasicScanner_Init(&scanner, "name", "#if 1", BasicScannerType_Token);
    scanner.m_Token = TK_PRE_IF;
    
    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_PRE_IF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    
    BasicScanner_Destroy(&scanner);



    BasicScanner_Init(&scanner, "name", "123\r\n", BasicScannerType_File);
    
    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_DECIMAL_INTEGER));
    TEST(BasicScanner_MatchToken(&scanner, TK_BREAKLINE));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);

    BasicScanner_Init(&scanner, "name", "#pragma once\r\n", BasicScannerType_File);

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_PREPROCESSOR));
    TEST(BasicScanner_MatchToken(&scanner, TK_IDENTIFIER));
    TEST(BasicScanner_MatchToken(&scanner, TK_SPACES));
    TEST(BasicScanner_MatchToken(&scanner, TK_IDENTIFIER));
    TEST(BasicScanner_MatchToken(&scanner, TK_BREAKLINE));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);

    BasicScanner_Init(&scanner, "name", "//comment", BasicScannerType_File);
    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_LINE_COMMENT));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);

    BasicScanner_Init(&scanner, "name", "/*comment*/", BasicScannerType_File);

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_COMMENT));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));

    Scanner scanner2;
    Scanner_Init(&scanner2);
    TEST(Scanner_CurrentToken(&scanner2) == TK_EOF);

    Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test1.h", FileIncludeTypeQuoted);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)

        Scanner_Destroy(&scanner2);
    //////////////////////////////////////////////////////////////

    Test1();
    Test2();
    Test3();
    Test4();
    ///////////

   
    //////////

  
    ///////////////////////////



    if (error_count == 0)
    {
        printf("ALL TESTS OK\n");
    }
}
