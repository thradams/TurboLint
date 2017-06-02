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
 TEST(Scanner_Token((scanner)) == TK&& \
      Scanner_IsActiveGroup((scanner)));\
 Scanner_NextVersion2((scanner));

#define MATCH_INACTIVE(scanner, TK) \
 TEST(Scanner_Token((scanner)) == TK && \
      !Scanner_IsActiveGroup((scanner)));\
 Scanner_NextVersion2((scanner));

#define  MATCH_INACTIVE2(scanner, TK, lexeme)\
TEST(Scanner_Token((scanner)) == TK &&\
     strcmp(Scanner_Lexeme(scanner), lexeme) == 0 &&\
     !Scanner_IsActiveGroup((scanner)));\
Scanner_NextVersion2((scanner));

#define  MATCH2(scanner, TK, lexeme)\
TEST(Scanner_Token((scanner)) == TK &&\
     strcmp(Scanner_Lexeme(scanner), lexeme) == 0 &&\
     Scanner_IsActiveGroup((scanner)));\
Scanner_NextVersion2((scanner));

void Test()
{
  printf("RUNNING TESTS ...\n");

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
  BasicScanner_Init(&scanner, "name", "123\r\n");
  TEST(scanner.currentItem.token == TK_BOF);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_DECIMAL_INTEGER);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_BREAKLINE);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_EOF);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_EOF);


  BasicScanner_Destroy(&scanner);
  BasicScanner_Init(&scanner, "name", "#pragma once\r\n");
  TEST(scanner.currentItem.token == TK_BOF);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_PREPROCESSOR);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_IDENTIFIER);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_SPACES);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_IDENTIFIER);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_BREAKLINE);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_EOF);

  BasicScanner_Destroy(&scanner);
  BasicScanner_Init(&scanner, "name", "//comment");

  TEST(scanner.currentItem.token == TK_BOF);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_LINE_COMMENT);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_EOF);


  BasicScanner_Destroy(&scanner);
  BasicScanner_Init(&scanner, "name", "/*comment*/");
  TEST(scanner.currentItem.token == TK_BOF);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_COMMENT);
  BasicScanner_Next(&scanner);
  TEST(scanner.currentItem.token == TK_EOF);


  Scanner scanner2;
  Scanner_Init(&scanner2);
  TEST(Scanner_Token(&scanner2) == TK_EOF);

  Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test1.h", FileIncludeTypeQuoted);
  TEST(Scanner_Token(&scanner2) == TK_BOF);
  Scanner_NextVersion2(&scanner2);

  //Este break line veio de um #define A
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);

  //Este 1 vem da expansão de A
  Scanner_NextVersion2(&scanner2);
  TEST(Scanner_Token(&scanner2) == TK_DECIMAL_INTEGER);

  Scanner_NextVersion2(&scanner2);
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);

  Scanner_NextVersion2(&scanner2);
  TEST(Scanner_Token(&scanner2) == TK_EOF);


  Scanner_Destroy(&scanner2);
  //////////////////////////////////////////////////////////////

  Scanner_Init(&scanner2);
  Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test2.h", FileIncludeTypeQuoted);

  TEST(Scanner_Token(&scanner2) == TK_BOF);
  Scanner_NextVersion2(&scanner2);

  //Este break line veio de um #define A
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);

  //Este 1 vem da expansão de A
  Scanner_NextVersion2(&scanner2);
  TEST(Scanner_Token(&scanner2) == TK_DECIMAL_INTEGER);

  Scanner_NextVersion2(&scanner2);
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);

  Scanner_NextVersion2(&scanner2);
  TEST(Scanner_Token(&scanner2) == TK_EOF);
  Scanner_Destroy(&scanner2);
  //////////////////////////////////////////////////////////////
  Scanner_Init(&scanner2);
  Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test3.h", FileIncludeTypeQuoted);

  TEST(Scanner_Token(&scanner2) == TK_BOF);
  Scanner_NextVersion2(&scanner2);


  //#define A  1   2 
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);
  Scanner_NextVersion2(&scanner2);

  //1
  TEST(Scanner_Token(&scanner2) == TK_DECIMAL_INTEGER);
  TEST(strcmp(Scanner_Lexeme(&scanner2), "1") == 0);
  Scanner_NextVersion2(&scanner2);
  //
  TEST(Scanner_Token(&scanner2) == TK_SPACES);
  Scanner_NextVersion2(&scanner2);
  //2
  TEST(Scanner_Token(&scanner2) == TK_DECIMAL_INTEGER);
  TEST(strcmp(Scanner_Lexeme(&scanner2), "2") == 0);
  Scanner_NextVersion2(&scanner2);
  //
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);
  Scanner_NextVersion2(&scanner2);
  //
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);
  Scanner_NextVersion2(&scanner2);
  //
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);
  Scanner_NextVersion2(&scanner2);

  //"1 2"
  TEST(Scanner_Token(&scanner2) == TK_STRING_LITERAL);
  TEST(strcmp(Scanner_Lexeme(&scanner2), "\"1 2\"") == 0);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);

  Scanner_Destroy(&scanner2);
  ///////////

  Scanner_Init(&scanner2);
  Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test4.h", FileIncludeTypeQuoted);

  MATCH(&scanner2, TK_BOF)

    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_LEFT_PARENTHESIS)
    MATCH(&scanner2, TK_DECIMAL_INTEGER)
    MATCH(&scanner2, TK_SPACES)
    MATCH(&scanner2, TK_PLUS_SIGN)
    MATCH(&scanner2, TK_SPACES)
    MATCH2(&scanner2, TK_IDENTIFIER, "foo")
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
    MATCH(&scanner2, TK_BREAKLINE)

    Scanner_Destroy(&scanner2);
  //////////

  Scanner_Init(&scanner2);
  Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test5.h", FileIncludeTypeQuoted);

  MATCH(&scanner2, TK_BOF)
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH2(&scanner2, TK_STRING_LITERAL, "\"x ## y\"")

    Scanner_Destroy(&scanner2);
  ///////////////////////////

  Scanner_Init(&scanner2);
  Scanner_IncludeFile_Version2(&scanner2, ".\\Test\\Test6.h", FileIncludeTypeQuoted);
  MATCH(&scanner2, TK_BOF)
  MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN")
  MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_BREAKLINE)
  MATCH2(&scanner2, TK_IDENTIFIER, "A")
  MATCH(&scanner2, TK_SPACES)    
  MATCH2(&scanner2, TK_IDENTIFIER, "B")
  MATCH(&scanner2, TK_BREAKLINE)
    
    MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
    MATCH_INACTIVE(&scanner2, TK_IDENTIFIER, "B")
    MATCH_INACTIVE(&scanner2, TK_SPACES)
    MATCH_INACTIVE(&scanner2, TK_IDENTIFIER, "D")
    MATCH_INACTIVE(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_BREAKLINE) //#endif

    MATCH2(&scanner2, TK_IDENTIFIER, "END")
    MATCH(&scanner2, TK_BREAKLINE)
    MATCH(&scanner2, TK_EOF)
    Scanner_Destroy(&scanner2);
  ///////////////////////////

  if (error_count == 0)
  {
    printf("ALL TESTS OK\n");
  }
}
