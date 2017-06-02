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


void Test()
{
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
  TEST(Scanner_Token(&scanner2) == TK_BOF);
  Scanner_NextVersion2(&scanner2);

  //Define
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);
  Scanner_NextVersion2(&scanner2);
  
  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_LEFT_PARENTHESIS);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_DECIMAL_INTEGER);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_SPACES);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_PLUS_SIGN);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_SPACES);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_IDENTIFIER);
  TEST(strcmp(Scanner_Lexeme(&scanner2), "foo") == 0);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_RIGHT_PARENTHESIS);
  Scanner_NextVersion2(&scanner2);

  TEST(Scanner_Token(&scanner2) == TK_BREAKLINE);
  Scanner_NextVersion2(&scanner2);

  Scanner_Destroy(&scanner2);
  //////////


}
