%option c++ yyclass="zu_scanner" outfile="zu_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{
/* $Id: zu_scanner.l,v 1.10 2016/04/14 09:29:09 ist179042 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "zu_scanner.h"
#include "zu_parser.tab.h"

// don't change this
#define yyerror LexerError
%}

SPACE [ \t]

DIG   0|[1-9][0-9]*
DIG_HEX [0-9A-aF-f]
NUM_HEX 0x{DIG_HEX}+
EXPONENT  [eE][-]?{DIG}+
REAL  {DIG}+[.]{DIG}+{EXPONENT}?

%x X_STRING X_COMMENT X_FLOAT X_SPECIAL_CHAR X_STRING_IGNORE X_COMMENT_IN_STRING
%%
                       { set_debug(1); }

"//".*$                 ; /* ignore comments */

">="                   return tGE;
"<="                   return tLE;
"=="                   return tEQ;
"!="                   return tNE;

"for"                  return tFOR;
            /*"if"                   return tIF;  not needed I'd say*/
            /* TO CARE IN YACC"!"                    return tPRINT; */
"!!"                   return tPRINTLN;
"@"                    return tREAD;
"begin"                return tBEGIN;
"end"                  return tEND;
"!!!"                  return tRETURN;
"><"                   return tBREAK;
"<>"                   return tCONTINUE;

[A-Za-z_][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tIDENTIFIER;


\"                     yy_push_state(X_STRING); yylval.s = new std::string("");   /* BUGGY XXX CHANGE THE STRING THINGS */
<X_STRING>\"{SPACE}*\" ;
<X_STRING>\"{SPACE}*"/*" yy_push_state(X_COMMENT_IN_STRING);
<X_STRING>\"           yy_pop_state(); return tSTRING;
<X_STRING>\\         *yylval.s += yytext +1 ; yy_push_state(X_SPECIAL_CHAR);
<X_SPECIAL_CHAR>\\    (*yylval.s).push_back('\\');
<X_SPECIAL_CHAR>"n"    (*yylval.s).push_back('\n');yy_pop_state();
<X_SPECIAL_CHAR>"t"    (*yylval.s).push_back('\t');yy_pop_state();
<X_SPECIAL_CHAR>"r"    (*yylval.s).push_back('\r');yy_pop_state();
<X_SPECIAL_CHAR>{DIG_HEX}{DIG_HEX} *yylval.s += yytext + 1;yy_pop_state();
<X_SPECIAL_CHAR>"0"    yy_push_state(X_STRING_IGNORE);
<X_STRING_IGNORE>\"    *yylval.s += yytext + 1;yy_pop_state();yy_pop_state(); return tSTRING;
<X_STRING>"/*"		   *yylval.s += yytext + 1;
<X_STRING>"//"         *yylval.s += yytext + 1;
<X_STRING>.            *yylval.s += yytext;
<X_STRING>\n           yyerror("newline in string");

 /* Comments after strings because if it is inside a string it doesnt count as a comment */

<X_COMMENT_IN_STRING>"*/"{SPACE}*\" yy_pop_state(); /* SOMETHING MISSING FIXME */
<X_COMMENT_IN_STRING>.|\n    ;

"/*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"*/"        yy_pop_state();
<X_COMMENT>"/*"        yy_push_state(X_COMMENT);
<X_COMMENT>\n          ; /* ignore comments */
<X_COMMENT>.           ; /* ignore comments */

{DIG}                 yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;  /* Integers base 10 */
{NUM_HEX}             yylval.i = strtol(yytext, nullptr, 16); return tINTEGER;  /* Integers base 16 */
{REAL}                yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;  /* Reals  */
[#-~()<>=+*/%;{}.\[\]!&]       return *yytext;

[ \t\n]+               ; /* ignore whitespace */

.                      yyerror("Unknown character yolo  "+ *yytext);

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int zu_scanner::yywrap() { return 1; }
