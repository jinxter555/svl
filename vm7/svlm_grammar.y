%{
#include <iostream>
#include <string>
#include <cmath>
#include <tuple>
#include "lang.hh"
%}

%require "3.8.1"
%language "C++"
%defines "svlm_parser.hh"
%output "svlm_parser.cc"

%define api.parser.class {SvlmParser}
%define api.namespace {vslast}
%define api.value.type variant
%parse-param {SvlmScanner* scanner}
%parse-param {SvlmAst* slc}


 
%locations

%code requires { 
#include "ast.hh"
#include "svlm_ast.hh"

namespace vslast {
  class SvlmScanner;
}}

%code {
#include "svlm_scanner.hh"
#define yylex(x,y) scanner->lex(x,y)


}


%token YYEOF EOL COMMENT1 COMMENT2
%token MODULE DEF DO END AST_BREAK AST_RETURN AST_DEFAULT PRINT 
%token CASE FLOW WHILE REPEAT UNTIL DONE IS IF THEN ELSE WHEN WHERE
%token PAREN_L PAREN_R CUR_L CUR_R ARROW_L ARROW_R
%token SQBRK_L SQBRK_R
%token DOT AT DOLLAR COLON COMMA SEMICOLON
%token TRUE FALSE NIL
%token <std::string> IDENT_STR STR DQSTR
%token <s_integer>  INT
%token <s_float>     FLT
 
%nterm EOS // end of statement
%nterm <std::vector<std::string>> param_list 
%nterm <std::string> param
//%nterm <ast_op> comparison_ops
%nterm comments

%nonassoc           ASSIGN
%left               AND OR 
%left               EQL NEQL GT LT GTEQ LTEQ 
%left               PLUS MINUS
%left               MULTIPLY DIVIDE PERCENT
%precedence         UMINUS
%precedence         NOT
%right              EXPONENT

%type <unique_ptr<AstList>> statement_list
%type <unique_ptr<AstExpr>> module literals exp_eval statement

%start program_start

%%
program_start
  :  statement_list { slc->add_module(Operand("mname"));}
  ;

statement_list
  : statement_list EOS statement {
    if($1==nullptr) {std::cerr << "statement syntax error"; yyerrok; }
    if($1!=nullptr && $3!=nullptr) $1->add($3);
    $$ = $1;
  }
  | statement  {
    auto new_list = std::make_unique<AstList>();
    new_list->add(move($1));
    $$ = move(new_list);
  }

  | statement_list error EOS statement { yyerrok; }
  | %empty { $$ = std::make_unique<AstList>(); }
  ;

statement
  : %empty {$$=nullptr;} // end of each statement
  | exp_eval { $$ = move($1); }
  ;

exp_eval
  : literals  { $$ = move($1); }
  | exp_eval MULTIPLY exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::mul); }
  | exp_eval DIVIDE exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::div); }
  | exp_eval PLUS exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::plus); }
  | exp_eval MINUS exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::minus); }
  | exp_eval GT exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::gt); }
  | exp_eval LT exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::lt); }
  | exp_eval LTEQ exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::lteq); }
  | exp_eval GTEQ exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::gteq); }
  | exp_eval EQL exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::eql); }
  | exp_eval NEQL exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::neql); }
  | exp_eval AND exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::and_); }
  | exp_eval OR exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::or_); }
  | NOT exp_eval { $$ = make_unique<AstBinOp>(move($2), move($2), AstOpCode::not_); }
  ;



literals
  : INT { $$ = make_unique<Operand>($1); }
  | FLT { $$ = make_unique<Operand>($1); }
  | TRUE { $$ = make_unique<Operand>(true); }
  | FALSE { $$ = make_unique<Operand>(false); }
  //| COLON STR { $$ = std::make_unique<OperandExprAst>(Operand(Atom($2))); }
  | DQSTR { $$ = make_unique<Operand>($1); }
  ;




%%

//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
