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
    TK_EndMark,
    TK_LINE_COMMENT,
    TK_COMMENT,
    TK_string_literal,
    TK_identifier,
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

    TK_char_literal,

    TK_auto,
    TK_BREAK,
    TK_case,
    TK_char,
    TK_const,
    TK_CONTINUE,
    TK_DEFAULT,
    TK_DO,
    TK_double,
    TK_ELSE,
    TK_enum,
    TK_extern,
    TK_float,
    TK_FOR,
    TK_GOTO,
    TK_IF,
    TK_int,
    TK_long,
    TK_register,
    TK_RETURN,
    TK_short,
    TK_signed,
    TK_SIZEOF,
    TK_static,
    TK_struct,
    TK_SWITCH,
    TK_typedef,
    TK_union,
    TK_unsigned,
    TK_void,
    TK_volatile,
    TK_WHILE,
    TK__Thread_local,
    TK__Bool,
    TK__Complex,
    TK__Atomic,
    TK_restrict,
    TK__Static_assert,
    TK_inline,
    TK__Noreturn,
    TK__Alignas,
    TK__Generic,
    TK__Imaginary,
    TK__Alignof,

    ///
    TK__Asm, //visual c++
} Tokens;

//APELIDOS PARA TOKENS
//type-qualifier-extensions
#define TK_OPT_QUALIFIER   TK_QUESTION_MARK
#define TK_OWN_QUALIFIER   TK_CIRCUMFLEX_ACCENT
#define TK_DTOR_QUALIFIER  TK_PERCENT_SIGN
#define TK_MDTOR_QUALIFIER TK_VERTICAL_LINE

//_move
#define TK_MOVE TK_ANDAND


__inline bool IsNumber(Tokens token)
{
    return token == TK_DECIMAL_INTEGER ||
           token == TK_FLOAT_NUMBER ||
           token == TK_HEX_INTEGER ||
           token == TK_char_literal;
}

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

typedef struct ScannerT
{
    SStream stream;
    ScannerItem currentItem;

    //true antes do 1 token de cada linha
    bool bLineStart;
    bool bMacroExpanded;
    int FileIndex;
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

typedef struct
{
    ScannerItem* strings;
    size_t size;
    size_t capacity;
} ScannerItemStack;
#define SCANNER_ITEM_STATCK_INIT {NULL , 0 , 0}

Result ScannerItemStack_Init(ScannerItemStack* st);
void   ScannerItemStack_Destroy(ScannerItemStack* st);
Result ScannerItemStack_PushMove(ScannerItemStack* st, ScannerItem* item);
void   ScannerItemStack_PopMove(ScannerItemStack* st, ScannerItem* item);
void   ScannerItemStack_Pop(ScannerItemStack* st);
Result ScannerItemStack_PopPushTo(ScannerItemStack* st, ScannerItemStack* other);
bool   ScannerItemStack_IsEmpty(ScannerItemStack* st);
Tokens ScannerItemStack_TopToken(ScannerItemStack* st);
void   ScannerItemStack_Print(ScannerItemStack* st);
void ScannerItemStack_Swap(ScannerItemStack* p1, ScannerItemStack* p2);
