%{
// $Id: zu_parser.y,v 1.10 2016/04/14 17:18:23 ist179042 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	/* integer value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  zu::lvalue_node  *lvalue;
  basic_type *type;
  zu::function_call_node *fcall;

};

%token <i> tINTEGER
%token <s> tIDENTIFIER tSTRING
%token tIF tPRINT tREAD tBEGIN tEND tRETURN tBREAK tCONTINUE tPRINTLN tFOR

%nonassoc tIFX
%nonassoc tELSE

%right '='
%left tGE tLE tEQ tNE '>' '<'
%left '+' '-'
%left '*' '/' '%'
// FIXME '?'
%left '?'
// FIXME '?'
%nonassoc tUNARY

%type <node> stmt function intruction
%type <sequence> list opt_args declaration variables body declarations block intructions expressions iteration
%type <expression> expr variable
%type <lvalue> lval
%type <type> type
%type <fcall> fun_call

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file : declarations   { compiler->ast($1); }
     |                {compiler->ast(nullptr);}
 	 ;

declarations : declaration declarations { $$ = new cdk::sequence_node(LINE,$1,$2); }
             | declaration             { $$ = new cdk::sequence_node(LINE,$1); }
             ;

declaration : variable ';'        { $$ = new cdk::sequence_node(LINE,$1); }
			| function            { $$ = new cdk::sequence_node(LINE,$1); }
			;

function    : type tIDENTIFIER '!' '(' variables ')' '='  expr body { $$ = new zu::function_def_node(LINE,$2,$5,$1,$9,true,$8); }
            | type tIDENTIFIER '(' variables ')'                { /* FIXME */ }
            | type tIDENTIFIER '!' '('')' '=' expr  body {  $$ = new zu::function_def_node(LINE,$2,nullptr,$1,$8,true,$7); }
            | '!' tIDENTIFIER '!' '(' variables ')''=' expr  body { $$ = new zu::function_def_node(LINE,$2,$5,nullptr,$9,true,$8); } //FIXME: Need to add other function nodes
            | '!' tIDENTIFIER '(' variables ')'                { /* FIXME */ }
            | '!' tIDENTIFIER '!' '('')' '=' expr  body {  $$ = new zu::function_def_node(LINE,$2,nullptr,nullptr,$8,true,$7);  }
	      ;

body : block            {  $$ = $1 ;  }
      ;
      
block : '{' declarations intructions '}'      { $$ = new cdk::sequence_node(LINE,$2,$3);}
	  | '{' declarations '}'       { $$ = new cdk::sequence_node(LINE,$2); }
	  | '{' intructions '}'         { $$ = new cdk::sequence_node(LINE,$2); }
	  |  '{' '}'                   { $$ = new cdk::sequence_node(LINE,nullptr); }
	  ;

type : '#'           { $$ = new basic_type(4, basic_type::TYPE_INT);}
	 | '%'           { $$ = new basic_type(8, basic_type::TYPE_DOUBLE);}
     | '$'           { $$ = new basic_type(1, basic_type::TYPE_STRING);}
     | '<' type '>'  { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
     ;
     
list : stmt	     { $$ = new cdk::sequence_node(LINE, $1); }
	   | list stmt { $$ = new cdk::sequence_node(LINE, $2, $1); }
	   ;

stmt : expr ';'                         { $$ = new zu::evaluation_node(LINE, $1); }
     | tREAD ';'                   { $$ = new zu::read_node(LINE); }
     | '[' iteration ']'           { /* FIXME DO STUFF */}
    | condition ';'                      { /* TODO LEL */ }
     | tRETURN                 { $$ = new zu::return_node(LINE); } // XXX
     | tBREAK                      { $$ = new zu::break_node(LINE); } // XXX
     | tCONTINUE                      { $$ = new zu::continue_node(LINE); } // XXX
     ;

expr : tINTEGER                { $$ = new cdk::integer_node(LINE, $1); }
	   | tSTRING                 { $$ = new cdk::string_node(LINE, $1); }
     | '-' expr %prec tUNARY   { $$ = new cdk::neg_node(LINE, $2); }
     | expr '+' expr	         { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	         { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	         { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr	         { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr             { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	         { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	         { $$ = new cdk::eq_node(LINE, $1, $3); }
     | expr '&' expr             { /* TODO */ }
     | '(' expr ')'              { $$ = $2; }
     | lval                      { $$ = new zu::rvalue_node(LINE, $1); }  //FIXME
     | lval '=' expr             { $$ = new zu::assignment_node(LINE, $1, $3); }
     | fun_call                  { $$ = $1; }

     ;

expressions : expr ',' expressions   { /* TODO */ }
            ;
     
fun_call : tIDENTIFIER '(' opt_args ')'     { $$ = new zu::function_call_node(LINE,$1,$3); }
		 ;
		 
opt_args :                      { $$ = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
         | expr ',' opt_args    { $$ = new cdk::sequence_node(LINE,$1,$3); }
         | expr               { $$ = new cdk::sequence_node(LINE,$1); }
         ;

intructions : intruction intructions   { /* TODO */ }
             | intruction               { /* TODO */ }
            ;

intruction : expr ';'            {/* FIXME DO SOMETHING */ }
           | expr '!'           { /* FIXME DO SOMETHING ELSE */ }
           | expr tPRINTLN      { /* YEAH YOU GUESSED IT FIXME */ }
           | tBREAK               { /* OH WELL FIXME */ }
           | tCONTINUE               { /* TIRED OF FIXME XXX FROM NOW ON */ }
           | tRETURN              { /* OH YEAH BABY XXX IF U KNOW WUT I MEAN *WINK* */}
           | condition             { /* HMMM TODO FIXME */}
           | '[' iteration ']'             { $$ = new cdk::sequence_node(LINE,$2); }
           | block                   { /* YUP ITS TOURET FAULT LEL TODO */}
           ;

variables : variable ',' variables  { /* NUNO IS GAME FIXME AND FIXHIM */ }
          | variable               { /* FIXME FOLKS */ }
          ;

variable : type tIDENTIFIER '!' '=' expr { /* FIXME DO THINGS */ }
            | type tIDENTIFIER '?' '=' expr { /* FIXME DO MORE THINGS */ }
              | type tIDENTIFIER '=' expr {/* FIXME DO EVEN MORE THINGS */ }
                |type tIDENTIFIER '!'  { /* FIXME OMG PLZ NO THINGS */ }
                | type tIDENTIFIER '?' { /* FIXME DO MORE THINGS */ }
                  | type tIDENTIFIER  { /* FIXME MIGUEL TOURET IS GAY LEL */}
                   ;

iteration :  variables ';' expressions ';' expressions  intruction { /*  $$ = new zu::for_node(LINE, $1, $3, $5, $6 );  */ }
          |  expressions ';' expressions ';' expressions  intruction    { /* $$ = new zu::for_node(LINE, $1, $3, $5, $6 ); */ }
          ;

condition : '[' expr ']' '#' intruction       {/* TODO IF NODE HERE */}
          | '[' expr ']' '?' intruction       { /* TODO IF NODE HERE AS WELL */ }
          | '[' expr ']' '?' intruction ':' intruction { /* TODO  IF-ELSE NODE HERE */ }
          ;


lval :  tIDENTIFIER             {  /* $$ = new zu::lvalue_node(LINE, $1); */   }
	;

%%
