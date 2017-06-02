#include "Scanner.h"

#include "..\Base\StrBuilder.h"
#include "..\Base\Stream.h"
#include <stdbool.h>
#include <stdlib.h>
#include "Parser.h"

wchar_t BasicScanner_Match(BasicScanner* scanner);

const char* TokenToString(Tokens tk)
{
    switch(tk)
    {
        case TK_NONE:
            return "None";
            
        case TK_BOF:
          return "Bof";
        case TK_EOF:
            return "Eof";
        case TK_LINE_COMMENT:
            return "LINE_COMMENT";
        case TK_COMMENT:
            return "COMMENT";
        case TK_STRING_LITERAL:
            return "LITERALSTR";
        case TK_IDENTIFIER:
            return "IDENTIFIER";
        case TK_SPACES:
            return "SPACES";
        case TK_DECIMAL_INTEGER:
            return "TK_DECIMAL_INTEGER";
        case TK_HEX_INTEGER:
            return "TK_HEX_INTEGER";
        case TK_FLOAT_NUMBER:
            return "TK_FLOAT_NUMBER";
        case TK_BREAKLINE:
            return "BREAKLINE";
        case TK_PREPROCESSOR:
            return "PREPROCESSOR";
        case CHARACTER_TABULATION:
            return "CHARACTER_TABULATION";
        case TK_EXCLAMATION_MARK:
            return "!";// = '!';
        case TK_QUOTATION_MARK:
            return "\"";//,// = '\"';
        case TK_NUMBER_SIGN:
            return "#";//,// = '#';
        case TK_DOLLAR_SIGN:
            return "$";//,// = '$';
        case TK_PERCENT_SIGN:
            return "%";//,// = '%';
        case TK_AMPERSAND:
            return "&";//,// = '&';
        case TK_APOSTROPHE:
            return "'";//,// = '\'';
        case TK_LEFT_PARENTHESIS:
            return "(";//,// = '(';
        case TK_RIGHT_PARENTHESIS:
            return ")";//,// = ')';
        case TK_ASTERISK:
            return "*";//,// = '*';
        case TK_PLUS_SIGN:
            return "+";//,// = '+';
        case TK_COMMA:
            return ",";//,// = ',';
        case TK_HYPHEN_MINUS:
            return "-";//,// = '-';
        case TK_FULL_STOP:
            return ".";//,// = '.';
        case TK_SOLIDUS:
            return "/";//,// = '/';
        case TK_COLON:
            return ":";//,// = ':';
        case TK_SEMICOLON:
            return ";";//,// = ';';
        case TK_LESS_THAN_SIGN:
            return "<";//,// = '<';
        case TK_EQUALS_SIGN:
            return "=";//,// = '=';
        case TK_GREATER_THAN_SIGN:
            return ">";//,// = '>';
        case TK_QUESTION_MARK:
            return "?";//,// = '\?';
        case TK_COMMERCIAL_AT:
            return "@";//,// = '@';
        case TK_LEFT_SQUARE_BRACKET:
            return "[";//,// = '[';
        case REVERSE_SOLIDUS:
            return "\\";//,// = '\\';
        case TK_RIGHT_SQUARE_BRACKET:
            return "]";//,// = ']';
        case TK_CIRCUMFLEX_ACCENT:
            return "^";// = '^';
        case TK_LOW_LINE:
            return "_";//,// = '_';
        case TK_GRAVE_ACCENT:
            return "`";//,// = '`';
        case TK_LEFT_CURLY_BRACKET:
            return "{";//,// = '{';
        case TK_VERTICAL_LINE:
            return "|";//,// = '|';
        case TK_RIGHT_CURLY_BRACKET:
            return "}";//,// = '}';

        case TK_TILDE:
          return "~";//,// = '~';
          break;
        case TK_AUTO:
            return "auto";
        case TK_BREAK:
            return "break";
        case TK_CASE:
            return "case";
        case TK_char:
            return "char";
        case TK_CONST:
            return "const";
        case TK_CONTINUE:
            return "continue";
        case TK_DEFAULT:
            return "default";
        case TK_DO:
            return "DO";
        case TK_DOUBLE:
            return "DOUBLE";
        case TK_ELSE:
            return "ELSE";
        case TK_ENUM:
            return "ENUM";
        case TK_EXTERN:
            return "EXTERN";
        case TK_FLOAT:
            return "FLOAT";
        case TK_FOR:
            return "FOR";
        case TK_GOTO:
            return "GOTO";
        case TK_IF:
            return "IF";
        case TK_INT:
            return "INT";
        case TK_LONG:
            return "LONG";
        case TK_REGISTER:
            return "REGISTER";
        case TK_RETURN:
            return "RETURN";
        case TK_SHORT:
            return "SHORT";
        case TK_SIGNED:
            return "SIGNED";
        case TK_SIZEOF:
            return "SIZEOF";
        case TK_STATIC:
            return "STATIC";
        case TK_STRUCT:
            return "STRUCT";
        case TK_SWITCH:
            return "SWITCH";
        case TK_TYPEDEF:
            return "TYPEDEF";
        case TK_UNION:
            return "UNION";
        case TK_UNSIGNED:
            return "UNSIGNED";
        case TK_VOID:
            return "VOID";
        case TK_VOLATILE:
            return "VOLATILE";
        case TK_WHILE:
            return "WHILE";
		case TK_ARROW:
			return "->";

		case TK_PLUSPLUS:
			return "++";

		case TK_MINUSMINUS:
			return "--";

		case TK_EQUALEQUAL:
			return "==";
		case TK_NOTEQUAL:
			return "!=";

		case TK_LESSLESS:
			return "<<";

		case TK_GREATERGREATER:
			return ">>";

			
				case TK_LESSEQUAL:
					return "<=";
				case TK_GREATEREQUAL:
					return ">=";

				case TK_ANDAND:
					return "&&";
				case TK_OROR:
					return "||";
				case TK_MULTIEQUAL:
					return "*=";
				case TK_DIVEQUAL:
					return "/=";
				case TK_PERCENT_EQUAL:
					return "/%=";
				case TK_PLUSEQUAL:
					return "+=";
				case TK_MINUS_EQUAL:
					return "-=";
				case TK_ANDEQUAL:
					return "!=";
				case TK_CARETEQUAL:
					return "^=";
				case TK_OREQUAL:
					return "|=";
				case TK_NUMBERNUMBER:
					return "##";
				case TK_LESSCOLON:
					return "<:";
				case TK_COLONGREATER:
					return ":>";
				case TK_LESSPERCENT:
					return "<%";
				case TK_PERCENTGREATER:
					return "%>";
				case TK_PERCENTCOLON:
					return "%:";
				case TK_DOTDOTDOT:
					return "...";
				case TK_GREATERGREATEREQUAL:
					return ">>=";
				case TK_LESSLESSEQUAL:
					return "<<=";
				case TK_PERCENTCOLONPERCENTCOLON:
					return "/%:/%:";

        default:
            ASSERT(false);
            break;
    }
    return "???";
}

void ScannerItem_Init(ScannerItem* scannerItem)
{
    //scannerItem->lexeme = STRBUILDER_INIT;
    StrBuilder_Init(&scannerItem->lexeme, 100);
    scannerItem->token = TK_NONE;
}

void ScannerItem_Reset(ScannerItem* scannerItem)
{
    StrBuilder_Clear(&scannerItem->lexeme);
    scannerItem->token = TK_EOF;
}

void ScannerItem_Copy(ScannerItem* scannerItem, 
                      ScannerItem* other)
{
  scannerItem->token = other->token;
  StrBuilder_Set(&scannerItem->lexeme, other->lexeme.c_str);
}

void ScannerItem_Swap(ScannerItem* scannerItem,
                      ScannerItem* other)
{
    Tokens tk = other->token;
    other->token = scannerItem->token;
    scannerItem->token = tk;
    StrBuilder_Swap(&scannerItem->lexeme, &other->lexeme);
}

void ScannerItem_Destroy(ScannerItem* scannerItem)
{
    StrBuilder_Destroy(&scannerItem->lexeme);
}

Result BasicScanner_Init(BasicScanner* pBasicScanner,
                         const char* name,
                         const char* text)
{
    pBasicScanner->pPrevious = NULL;
    pBasicScanner->FileIndex = -1;
    pBasicScanner->bLineStart = true;
    pBasicScanner->bMacroExpanded = false;
    SStream_Init(&pBasicScanner->stream, name, text);
    ScannerItem_Init(&pBasicScanner->currentItem);
    pBasicScanner->currentItem.token = TK_BOF;
    return RESULT_OK;
}

Result BasicScanner_InitFile(BasicScanner* pBasicScanner, const char* fileName)
{
    pBasicScanner->pPrevious = NULL;
    pBasicScanner->FileIndex = -1;
    Result result = SStream_InitFile(&pBasicScanner->stream, fileName);
    if(result == RESULT_OK)
    {
        pBasicScanner->bLineStart = true;
        pBasicScanner->bMacroExpanded = false;
        ScannerItem_Init(&pBasicScanner->currentItem);
        pBasicScanner->currentItem.token = TK_BOF;
    }
    return result;
}

Result BasicScanner_Create(BasicScanner** pp, const char* name, const char* text)
{
    Result result = RESULT_OUT_OF_MEM;
    BasicScanner* p = (BasicScanner*)malloc(sizeof(BasicScanner));
    if(p)
    {
        result = BasicScanner_Init(p, name, text);
        if(result == RESULT_OK)
        {
            *pp = p;
        }
        else
        {
            free(p);
        }
    }
    return result;
}

Result BasicScanner_CreateFile(const char* fileName, BasicScanner** pp)
{
    Result result = RESULT_OUT_OF_MEM;
    BasicScanner* p = (BasicScanner*)malloc(sizeof(BasicScanner));
    if(p)
    {
        result = BasicScanner_InitFile(p, fileName);
        if(result == RESULT_OK)
        {
            *pp = p;
        }
        else
        {
            free(p);
        }
    }
    return result;
}


void BasicScanner_Destroy(BasicScanner* pBasicScanner)
{
    SStream_Destroy(&pBasicScanner->stream);
    ScannerItem_Destroy(&pBasicScanner->currentItem);
}

void BasicScanner_Delete(BasicScanner* pBasicScanner)
{
  if (pBasicScanner != NULL)
  {
    BasicScanner_Destroy(pBasicScanner);
    free(pBasicScanner);
  }
}

struct TkPair
{
    const char* lexeme;
    Tokens token;
};

static struct TkPair singleoperators[] =
{
    //punctuator: one of

    {"[", TK_LEFT_SQUARE_BRACKET }, //0
    {"]",  TK_RIGHT_SQUARE_BRACKET},
    {"(", TK_LEFT_PARENTHESIS},
    {")", TK_RIGHT_PARENTHESIS},
    {"{", TK_LEFT_CURLY_BRACKET},
    {"}", TK_RIGHT_CURLY_BRACKET},
    {".", TK_FULL_STOP},
    {"&", TK_AMPERSAND},
    {"*", TK_ASTERISK},
    {"+", TK_PLUS_SIGN},
    {"-",  TK_HYPHEN_MINUS},
    {"~", TK_TILDE},
    {"!", TK_EXCLAMATION_MARK},
    {"%", TK_PERCENT_SIGN},
    {"<", TK_LESS_THAN_SIGN},
    {">", TK_GREATER_THAN_SIGN },
    {"^", TK_CIRCUMFLEX_ACCENT },
    {"|", TK_VERTICAL_LINE },
    {"?", TK_QUESTION_MARK},
    {":", TK_COLON },
    {";", TK_SEMICOLON },
    {"=", TK_EQUALS_SIGN},
    {",", TK_COMMA},
    { "$", TK_DOLLAR_SIGN},
    { "@", TK_COMMERCIAL_AT }
    //  {"...", TK_DOTDOTDOT},//50
    //  {"%:%:", TK_PERCENTCOLONPERCENTCOLON},
    //  {"<<=", TK_LESSLESSEQUAL},
    //{">>=", TK_GREATERGREATEREQUAL},
};

static struct TkPair doubleoperators[] =
{
    { "->", TK_ARROW },//25
    { "++", TK_PLUSPLUS },
    { "--", TK_MINUSMINUS },
    { "<<", TK_LESSLESS },
    { ">>", TK_GREATERGREATER },
    { "<=", TK_LESSEQUAL },
    { ">=", TK_GREATEREQUAL },
    { "==", TK_EQUALEQUAL },
    { "!=", TK_NOTEQUAL },
    { "&&", TK_ANDAND },
    { "||", TK_OROR },
    { "*=", TK_MULTIEQUAL },
    { "/=", TK_DIVEQUAL },
    { "%=", TK_PERCENT_EQUAL },
    { "+=", TK_PLUSEQUAL },
    { "-=", TK_MINUS_EQUAL },
    { "&=", TK_ANDEQUAL },
    { "^=", TK_CARETEQUAL },
    { "|=", TK_OREQUAL },
    { "##", TK_NUMBERNUMBER },
    { "<:", TK_LESSCOLON },
    { ":>", TK_COLONGREATER },
    { "<%", TK_LESSPERCENT },
    { "%>", TK_PERCENTGREATER },
    { "%:", TK_PERCENTCOLON },

    { "...", TK_DOTDOTDOT },//50
    { "%:%:", TK_PERCENTCOLONPERCENTCOLON },
    { "<<=", TK_LESSLESSEQUAL },
    { ">>=", TK_GREATERGREATEREQUAL }
};

static struct TkPair keywords[] =
{
    //keywords
    { "auto", TK_AUTO },
    { "break", TK_BREAK },
    { "case", TK_CASE },
    { "char", TK_char },
    { "const", TK_CONST },
    { "continue", TK_CONTINUE },
    { "default", TK_DEFAULT },
    { "do", TK_DO },
    { "double", TK_DOUBLE },
    { "else", TK_ELSE },
    { "enum", TK_ENUM },
    { "extern", TK_EXTERN },
    { "float", TK_FLOAT },
    { "for", TK_FOR },
    { "goto", TK_GOTO },
    { "if", TK_IF },
    { "inline", TK_INLINE },
    { "int", TK_INT },
    { "long", TK_LONG },
    { "register", TK_REGISTER },
    { "restrict", TK_RESTRICT },
    { "return", TK_RETURN },
    { "short", TK_SHORT },
    { "signed", TK_SIGNED },
    { "sizeof", TK_SIZEOF },
    { "static", TK_STATIC },
    { "struct", TK_STRUCT },
    { "switch", TK_SWITCH },
    { "typedef", TK_TYPEDEF },
    { "union", TK_UNION },
    { "unsigned", TK_UNSIGNED },
    { "void", TK_VOID },
    { "volatile", TK_VOLATILE },
    { "while", TK_WHILE },
    { "_Alignas", TK__ALIGNAS },
    { "_Alignof", TK__ALINGOF },
    { "_Atomic", TK__ATOMIC },
    { "_Bool", TK__BOOL },
    { "_Complex", TK__COMPLEX },
    { "_Generic", TK__GENERIC },
    { "_Imaginary", TK__IMAGINARY },
    { "_Noreturn", TK__NORETURN },
    { "_Static_assert", TK__STATIC_ASSERT },
    { "_Thread_local", TK__THREAD_LOCAL },
    //
    { "__asm", TK__ASM }, //visual studio
    {"template", TK_TEMPLATE},
    {"class", TK_CLASS}

};

void BasicScanner_Next(BasicScanner* scanner)
{
    //bool bLineStart = scanner->bLineStart;
    //scanner->bLineStart = false;
    wchar_t ch = '\0';
    ScannerItem_Reset(&scanner->currentItem);
    ch = scanner->stream.currentChar;
    wchar_t ch1 = SStream_LookAhead(&scanner->stream);
    if(ch == '.' && ch1 == '.')
    {
        BasicScanner_Match(scanner);
        ch = BasicScanner_Match(scanner);
        if(ch != '.')
        {
            scanner->currentItem.token = TK_ERROR;
        }
        BasicScanner_Match(scanner);
        scanner->currentItem.token = TK_DOTDOTDOT;
        return;
    }
    //procura por puncturares com 2 caracteres
    for(size_t i = 0; i < sizeof(doubleoperators) / sizeof(doubleoperators[0]); i++)
    {
        if(doubleoperators[i].lexeme[0] == ch &&
                doubleoperators[i].lexeme[1] == ch1)
        {
            scanner->currentItem.token = doubleoperators[i].token;
            BasicScanner_Match(scanner);
            BasicScanner_Match(scanner);
            scanner->bLineStart = false;
            return;
        }
    }
    //procura por puncturtorscom 1 caracteres
    for(size_t i = 0; i < sizeof(singleoperators) / sizeof(singleoperators[0]); i++)
    {
        if(singleoperators[i].lexeme[0] == ch)
        {
            scanner->currentItem.token = singleoperators[i].token;
            BasicScanner_Match(scanner);
            scanner->bLineStart = false;
            return;
        }
    }
    //U'
    //u
    //L
    //Devido ao L' tem que vir antes do identificador
    //literal string
    if(ch == L'"' ||
            (ch == L'L' && ch1 == L'"'))
    {
        if(ch == 'L')
        {
            ch = BasicScanner_Match(scanner); //L
        }
        scanner->currentItem.token = TK_STRING_LITERAL;
        ch = BasicScanner_Match(scanner);
        for(;;)
        {
            if(ch == '\"')
            {
                ch = BasicScanner_Match(scanner);
                break;
            }
            else if(ch == '\\')
            {
                //escape
                ch = BasicScanner_Match(scanner);
                ch = BasicScanner_Match(scanner);
            }
            else
            {
                ch = BasicScanner_Match(scanner);
            }
        }
        scanner->bLineStart = false;
        return;
    }
    //Devido ao L' tem que vir antes do identificador
    //literal
    if(ch == L'\'' ||
            (ch == L'L' && ch1 == L'\''))
    {
        if(ch == 'L')
        {
            ch = BasicScanner_Match(scanner); //L
        }
        scanner->currentItem.token = TK_CHAR_LITERAL;
        ch = BasicScanner_Match(scanner); //'
        if(ch == '\\')
        {
            //escape
            ch = BasicScanner_Match(scanner); //
            ch = BasicScanner_Match(scanner); //caractere
        }
        else
        {
            ch = BasicScanner_Match(scanner);//caractere
        }
        ch = BasicScanner_Match(scanner);//'
        scanner->bLineStart = false;
        return;
    }
    //Identificador
    if((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            ch == '_')
    {
        scanner->currentItem.token = TK_IDENTIFIER;
        ch = BasicScanner_Match(scanner);
        while((ch >= 'a' && ch <= 'z') ||
                (ch >= 'A' && ch <= 'Z') ||
                (ch >= '0' && ch <= '9') ||
                ch == '_')
        {
            ch = BasicScanner_Match(scanner);
        }
        //vê se é keywords e corrige o token
        for(size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        {
            if(BasicScanner_IsLexeme(scanner, keywords[i].lexeme))
            {
                scanner->currentItem.token = keywords[i].token;
                //StrBuilder_Append(&scanner->currentItem.lexeme, keywords[i].lexeme);
                //SStream_Next(&scanner->stream);
                break;
            }
        }
        scanner->bLineStart = false;
        return;
    }
    if(ch == '0' && (ch1 == 'x' || ch1 == 'X'))
    {
        ch = BasicScanner_Match(scanner);
        ch = BasicScanner_Match(scanner);
        scanner->currentItem.token = TK_HEX_INTEGER;
        while((ch >= '0' && ch <= '9') ||
                (ch >= 'A' && ch <= 'F') ||
                (ch >= 'a' && ch <= 'f'))
        {
            ch = BasicScanner_Match(scanner);
        }
        if(ch == 'L')
        {
            //sufixos! por enquanto so ignoro
            //1L
            ch = BasicScanner_Match(scanner);
        }
        return;
    }
    //numero
    if(ch >= '0' && ch <= '9')
    {
        scanner->currentItem.token = TK_DECIMAL_INTEGER;
        ch = BasicScanner_Match(scanner);
        while((ch >= '0' && ch <= '9'))
        {
            ch = BasicScanner_Match(scanner);
        }
        
        //integer-suffix:
        //ULL L LL U
        bool bHasIntegerSuffix = false;
        while (ch == 'l' || ch == 'L' || ch == 'u' || ch == 'U')
        {
          ch = BasicScanner_Match(scanner);
          bHasIntegerSuffix = true;
        }
        
        if(bHasIntegerSuffix)
        {
          //ver se faz sentido?
        }
        else
        {
            if(ch == '.')
            {
                ch = BasicScanner_Match(scanner);
                scanner->currentItem.token = TK_FLOAT_NUMBER;
                while((ch >= '0' && ch <= '9'))
                {
                    ch = BasicScanner_Match(scanner);
                }
            }
            if(scanner->stream.currentChar == 'e' ||
                    scanner->stream.currentChar == 'E')
            {
                ch = BasicScanner_Match(scanner);
                if(ch == '-' ||
                        ch == '+')
                {
                    BasicScanner_Match(scanner);
                }
                while((ch >= '0' && ch <= '9'))
                {
                    ch = BasicScanner_Match(scanner);
                }
            }
        }
        scanner->bLineStart = false;
        return;
    }
    //quebra de linha
    if(ch == '\n' || ch == L'\r')
    {
        scanner->currentItem.token = TK_BREAKLINE;
        if(ch == L'\r' && ch1 == L'\n')
        {
            //so coloca \n
            SStream_Next(&scanner->stream);
            ch = scanner->stream.currentChar;
            ch = BasicScanner_Match(scanner);
        }
        else
        {
            ch = BasicScanner_Match(scanner);
            StrBuilder_Clear(&scanner->currentItem.lexeme);
            //normaliza para windows?
            StrBuilder_Append(&scanner->currentItem.lexeme, "\r\n");
        }
        scanner->bLineStart = true;
        return;
    }
    if(ch == '\0')
    {
        scanner->currentItem.token = TK_EOF;
        scanner->bLineStart = false;
        return;
    }
    if(ch == '\f')
    {
        scanner->currentItem.token = TK_SPACES;
        BasicScanner_Match(scanner);
        return;
    }
    //espacos
    if(ch == ' ' || ch == '\t')
    {
        scanner->currentItem.token = TK_SPACES;
        ch = BasicScanner_Match(scanner);
        while(ch == ' ' || ch == '\t')
        {
            ch = BasicScanner_Match(scanner);
        }
        //continua com scanner->bLineStart
        return;
    }
    if(ch < 32)
    {
        scanner->currentItem.token = TK_SPACES;
    }
    //
    if(scanner->stream.currentChar == '#')
    {
        ch = BasicScanner_Match(scanner);
        if(scanner->bLineStart)
        {
            scanner->currentItem.token = TK_PREPROCESSOR;
        }
        else
        {
            scanner->currentItem.token = TK_NUMBER_SIGN;
        }
        return;
    }
    //comentario de linha
    if(ch == '/')
    {
        if(ch1 == '/')
        {
            scanner->currentItem.token = TK_LINE_COMMENT;
            ch = BasicScanner_Match(scanner);
            ch = BasicScanner_Match(scanner);
            while(ch != '\r' &&
                    ch != '\n' &&
                    ch != '\0')
            {
                ch = BasicScanner_Match(scanner);
            }
        }
        else if(ch1 == '*')
        {
            scanner->currentItem.token = TK_COMMENT;
            ch = BasicScanner_Match(scanner);
            ch = BasicScanner_Match(scanner);
            for(;;)
            {
                if(ch == '*')
                {
                    ch = BasicScanner_Match(scanner);
                    if(ch == '/')
                    {
                        ch = BasicScanner_Match(scanner);
                        break;
                    }
                }
                else if(ch == L'\r')
                {
                    //so coloca \n
                    SStream_Next(&scanner->stream);
                    ch = scanner->stream.currentChar;
                    if(ch == L'\n')
                    {
                        ch = BasicScanner_Match(scanner);
                    }
                    else
                    {
                    }
                }
                else if(ch == L'\n')
                {
                    ch = BasicScanner_Match(scanner);
                }
                else
                {
                    ch = BasicScanner_Match(scanner);
                }
            }
            //scanner->bLineStart = true;
            return;
        }
        else
        {
            scanner->currentItem.token = TK_SOLIDUS;
            ch = BasicScanner_Match(scanner);
        }
        return;
    }
    //junta linha
    if(ch == L'\\' &&
            (ch1 == L'\n' || ch1 == L'\r'))
    {
      //1) Whenever backslash appears at the end of 
      //a line(immediately followed by the newline character), both 
      //backslash and newline are deleted,
      //combining two physical source lines into one logical 
      //source line.This is a single - pass operation; 
      //a line ending in two backslashes followed by an empty 
      //line does not combine three lines into one.
      //If a universal character name(\uXXX) is formed in this 
      //phase, the behavior is undefined.

      SStream_Next(&scanner->stream);
      ch = scanner->stream.currentChar;
        if(ch == L'\r')
        {
          SStream_Next(&scanner->stream);
          ch = scanner->stream.currentChar;
            if(ch == L'\n')
            {
              SStream_Next(&scanner->stream);
              ch = scanner->stream.currentChar;
            }
        }
        else if(ch == L'\n')
        {
          SStream_Next(&scanner->stream);
          ch = scanner->stream.currentChar;
        }
        ////acho que o padrao manda sumir...
        ///vou colocar espaco por enquanto
        //vai ser ignorado
        //scanner->currentItem.token = TK_SPACES;
        //StrBuilder_Clear(&scanner->currentItem.lexeme);
        //StrBuilder_AppendChar(&scanner->currentItem.lexeme, L' ');
        
        scanner->bLineStart = false;
        BasicScanner_Next(scanner);
        
        return;
    }
    if(ch == 2)  //peguei um
    {
        ch = BasicScanner_Match(scanner);
        scanner->currentItem.token = TK_MACROPLACEHOLDER;
        scanner->bLineStart = false;
        return;
    }
    if(ch == '\\')
    {
        ch = BasicScanner_Match(scanner);
        scanner->currentItem.token = REVERSE_SOLIDUS;
        return;
    }
    ASSERT(false);
}


Tokens BasicScanner_Token(BasicScanner* scanner)
{
    return scanner->currentItem.token;
}

const char* BasicScanner_Lexeme(BasicScanner* scanner)
{
    return scanner->currentItem.lexeme.c_str;
}

bool BasicScanner_IsLexeme(BasicScanner* scanner, const char* psz)
{
    return strcmp(BasicScanner_Lexeme(scanner), psz) == 0;
}

wchar_t BasicScanner_Match(BasicScanner* scanner)
{
    StrBuilder_AppendWChar(&scanner->currentItem.lexeme,
                           scanner->stream.currentChar);
    SStream_Next(&scanner->stream);
    return scanner->stream.currentChar;
}

//////////////////////////////////////////////



void BasicScannerStack_Init(BasicScannerStack* stack)
{
  *stack = NULL;
}

void BasicScannerStack_Push(BasicScannerStack* stack, BasicScanner* pItem)
{
  if (*stack == NULL)
  {
    *stack = pItem;
  }
  else
  {
    pItem->pPrevious = *stack;
    *stack = pItem;
  }
}

BasicScanner* BasicScannerStack_PopGet(BasicScannerStack* stack)
{
  BasicScanner* pItem = NULL;
  if (*stack != NULL)
  {
    pItem = *stack;
    *stack = pItem->pPrevious;
  }
  return pItem;
}

void BasicScannerStack_PopIfNotLast(BasicScannerStack* stack)
{
  ASSERT(*stack != NULL);
  if ((*stack)->pPrevious != NULL)
  {
    BasicScanner_Delete(BasicScannerStack_PopGet(stack));
  }
}

void BasicScannerStack_Pop(BasicScannerStack* stack)
{
  BasicScanner_Delete(BasicScannerStack_PopGet(stack));
}

void BasicScannerStack_Destroy(BasicScannerStack* stack)
{
  BasicScanner* pItem = *stack;
  while (pItem)
  {
    BasicScanner* p = pItem;
    pItem = pItem->pPrevious;
    BasicScanner_Delete(p);
  }
}
