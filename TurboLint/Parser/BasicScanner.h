#pragma once
#include <stdbool.h>
#include "..\Base\StrBuilder.h"
#include "..\Base\Stream.h"
#include "..\Base\Result.h"
#include "..\Base\Array.h"

typedef enum
{
    TK_NONE,
    TK_EOF,
    TK_ENDMARK,
    TK_LINE_COMMENT,
    TK_COMMENT,
    TK_STRING_LITERAL,
    TK_IDENTIFIER,
    TK_SPACES,
    TK_DECIMAL_INTEGER,
    TK_HEX_INTEGER,
    TK_FLOAT_NUMBER,
    TK_MACROPLACEHOLDER,
    TK_BREAKLINE,
    CHAR1, // '/' ,
    CHARACTER_TABULATION,// = '\t';
    TK_PREPROCESSOR,
    TK_ERROR, //reservado para erro


    //
    TK_EXCLAMATION_MARK,// = '!';
    TK_QUOTATION_MARK,// = '\"';
    TK_NUMBER_SIGN,// = '#';

    TK_DOLLAR_SIGN,// = '$';
    TK_PERCENT_SIGN,// = '%';
    TK_AMPERSAND,// = '&';
    TK_APOSTROPHE,// = '\'';
    TK_LEFT_PARENTHESIS,// = '(';
    TK_RIGHT_PARENTHESIS,// = ')';
    TK_ASTERISK,// = '*';
    TK_PLUS_SIGN,// = '+';
    TK_COMMA,// = ',';
    TK_HYPHEN_MINUS,// = '-';
    TK_HYPHEN_MINUS_NEG,// = '-'; //nao retorna no basic string mas eh usado para saber se eh - unario
    TK_FULL_STOP,// = '.';
    TK_SOLIDUS,// = '/';

    TK_COLON,// = ':';
    TK_SEMICOLON,// = ';';
    TK_LESS_THAN_SIGN,// = '<';
    TK_EQUALS_SIGN,// = '=';
    TK_GREATER_THAN_SIGN,// = '>';
    TK_QUESTION_MARK,// = '\?';
    TK_COMMERCIAL_AT,// = '@';

    TK_LEFT_SQUARE_BRACKET,// = '[';
    REVERSE_SOLIDUS,// = '\\';
    TK_RIGHT_SQUARE_BRACKET,// = ']';
    TK_CIRCUMFLEX_ACCENT,// = '^';
    TK_LOW_LINE,// = '_';
    TK_GRAVE_ACCENT,// = '`';

    TK_LEFT_CURLY_BRACKET,// = '{';
    TK_VERTICAL_LINE,// = '|';
    TK_RIGHT_CURLY_BRACKET,// = '}';
    TK_TILDE, // ~

    ////////////////////////////////////////
    TK_ARROW,
    TK_PLUSPLUS,
    TK_MINUSMINUS,
    TK_LESSLESS,
    TK_GREATERGREATER,
    TK_LESSEQUAL,
    TK_GREATEREQUAL,
    TK_EQUALEQUAL,
    TK_NOTEQUAL,
    TK_ANDAND,
    TK_OROR,
    TK_MULTIEQUAL,
    TK_DIVEQUAL,
    TK_PERCENT_EQUAL,
    TK_PLUSEQUAL,
    TK_MINUS_EQUAL,
    TK_ANDEQUAL,
    TK_CARETEQUAL,
    TK_OREQUAL,
    TK_NUMBERNUMBER,
    TK_LESSCOLON,
    TK_COLONGREATER,
    TK_LESSPERCENT,
    TK_PERCENTGREATER,
    TK_PERCENTCOLON,
    TK_DOTDOTDOT,
    TK_GREATERGREATEREQUAL,
    TK_LESSLESSEQUAL,
    TK_PERCENTCOLONPERCENTCOLON,

    TK_CHAR_LITERAL,

    TK_AUTO,
    TK_BREAK,
    TK_CASE,
    TK_char,
    TK_CONST,
    TK_CONTINUE,
    TK_DEFAULT,
    TK_DO,
    TK_DOUBLE,
    TK_ELSE,
    TK_ENUM,
    TK_EXTERN,
    TK_FLOAT,
    TK_FOR,
    TK_GOTO,
    TK_IF,
    TK_INT,
    TK_LONG,
    TK_REGISTER,
    TK_RETURN,
    TK_SHORT,
    TK_SIGNED,
    TK_SIZEOF,
    TK_STATIC,
    TK_STRUCT,
    TK_SWITCH,
    TK_TYPEDEF,
    TK_UNION,
    TK_UNSIGNED,
    TK_VOID,
    TK_VOLATILE,
    TK_WHILE,
    TK__THREAD_LOCAL,
    TK__BOOL,
    TK__COMPLEX,
    TK__ATOMIC,
    TK_RESTRICT,
    TK__STATIC_ASSERT,
    TK_INLINE,
    TK__NORETURN,
    TK__ALIGNAS,
    TK__GENERIC,
    TK__IMAGINARY,
    TK__ALINGOF,

    ///
    TK__ASM, //visual c++
} Tokens;

//APELIDOS PARA TOKENS
//type-qualifier-extensions
#define TK_OPT_QUALIFIER   TK_QUESTION_MARK
#define TK_OWN_QUALIFIER   TK_CIRCUMFLEX_ACCENT
#define TK_DTOR_QUALIFIER  TK_PERCENT_SIGN
#define TK_MDTOR_QUALIFIER TK_VERTICAL_LINE

//
#define TK_MOVE TK_ANDAND

typedef struct
{
    StrBuilder lexeme;
    Tokens token;
} ScannerItem;


const char* TokenToString(Tokens tk);

void ScannerItem_Init(ScannerItem* scannerItem);
void ScannerItem_Reset(ScannerItem* scannerItem);
void ScannerItem_Swap(ScannerItem* scannerItem, ScannerItem* other);
void ScannerItem_Destroy(ScannerItem* scannerItem);
void ScannerItem_Copy(ScannerItem* scannerItem, ScannerItem* other);

typedef struct BasicScanner
{
    SStream stream;
    ScannerItem currentItem;

    //true antes do 1 token de cada linha
    bool bLineStart;
    bool bMacroExpanded;
    int FileIndex;
    struct BasicScanner* pPrevious;

} BasicScanner;

Result      BasicScanner_Create(BasicScanner** pp, const char* name, const char* text);
const char* BasicScanner_Lexeme(BasicScanner* scanner);
bool        BasicScanner_IsLexeme(BasicScanner* scanner, const char* psz);
void        BasicScanner_Next(BasicScanner* scanner);
void        BasicScanner_NextNoSpaces(BasicScanner* scanner);
Result      BasicScanner_InitFile(BasicScanner* pScanner, const char* fileName);
Result      BasicScanner_CreateFile(const char* fileName, BasicScanner** pp);
void        BasicScanner_Delete(BasicScanner* pScanner);

Result BasicScanner_Init(BasicScanner* pScanner,
                         const char* name,
                         const char* text);
void BasicScanner_Destroy(BasicScanner* pScanner);



typedef BasicScanner* BasicScannerStack;
#define ITEM_STACK_INIT NULL
void BasicScannerStack_Init(BasicScannerStack* stack);
void BasicScannerStack_Push(BasicScannerStack* stack, BasicScanner* pItem);
BasicScanner* BasicScannerStack_PopGet(BasicScannerStack* stack);
void BasicScannerStack_Pop(BasicScannerStack* stack);
void BasicScannerStack_PopIfNotLast(BasicScannerStack* stack);
void BasicScannerStack_Destroy(BasicScannerStack* stack);

#define ForEachBasicScanner(pItem, stack)\
    for (BasicScanner* pItem = stack;\
      pItem;\
      pItem = pItem->pPrevious)

