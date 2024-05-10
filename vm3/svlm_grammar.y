%{
#include <iostream>
#include <string>
#include <cmath>
%}

%require "3.7.4"
%language "C++"
%defines "svlm_parser.hh"
%output "svlm_parser.cpp"

%define api.parser.class {SvlmParser}
%define api.namespace {vslast}
%define api.value.type variant
%parse-param {SvlmScanner* scanner}
%parse-param {SvlmLangContext* slc}


%locations

%code requires { 
#include "ast.hh"
#include "svlm_lang.hh"

namespace vslast {
  class SvlmScanner;
}}

%code {
#include "svlm_scanner.hh"
#include "svlm_lang.hh"
#define yylex(x,y) scanner->lex(x,y)

SvlmLang* svlm_lang;
std::vector<std::string> param_list;


}


%token YYEOF EOL 
%token              MODULE DEF DO END
%token              LPAREN RPAREN AT DOLLAR COLON SEMICOLON
%token <std::string> IDENT_STR STR
%token <int>  INT
%token <float>     FLT
 
%nterm <char>  math_bin_op
%nterm EOS // end of statement
%nterm <std::vector<std::string>> param_list 
%nterm <std::string> param

%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT

%type <std::shared_ptr<ExprAst>>  iexp exp statement def_module def_function
%type <std::shared_ptr<ListExprAst>>  statement_list 

%start program_start


%%
program_start
  : statement_list  {
    auto p = slc->svlm_lang->ast_current_contexts.top();
    p->add($1);
  }
  ;

statement_list
  : statement_list EOS statement {
    if($3 != nullptr) {
      slc->svlm_lang->ast_current_context->add($3);
    } else {std::cout << "reach end\n"; }
    $$ = slc->svlm_lang->ast_current_context;
  }
  | statement  {
    slc->svlm_lang->new_ast_l_cc(); // init new ast_current_context for the block
    if($1!=nullptr) 
      slc->svlm_lang->ast_current_context->add($1);
    $$ = slc->svlm_lang->ast_current_context;
  }
  ;

statement
  : {$$=nullptr;} // end of each statement
  | exp 
  | def_module
  | def_function
  ;

exp
  : iexp { $$=$1; }
  | error { yyerrok; }
  ;

def_module
  : MODULE STR { 
    svlm_lang = slc->svlm_lang;
    slc->add_module_name($2); 
    $$ = std::make_shared<DeclExprAst>( std::make_shared<IdentExprAst>($2), DeclOpcodeAST::MODULE);
  }
  ;


iexp
  : INT { $$ = std::make_shared<NumberExprAst>($1); }
  | iexp math_bin_op iexp { $$ = std::make_shared<BinOpExprAst>($1, $3, BinOpcodeAST::INT_OP_INT, $2); }
  | LPAREN iexp RPAREN        { $$ = $2; }
  | DOLLAR STR { $$ = std::make_shared<GvarExprAst>(std::string($2)); }
  | DOLLAR STR ASSIGN iexp { 
    slc->add_mvar_name($2);  // add to context tree
    $$ = std::make_shared<BinOpExprAst>(
      std::make_shared<GvarExprAst>(std::string($2)), 
      $4, BinOpcodeAST::ASSIGN_INT_G, '=');
  }
  ;

math_bin_op
  : PLUS      {$$ = '+';}
  | MINUS     {$$ = '-';}
  | MULTIPLY  {$$ = '*';}
  | DIVIDE    {$$ = '/';}
  ;

def_function
  : DEF STR LPAREN param_list RPAREN DO statement_list END { 
    // std::cout << "function: " << $2 << "\n";

    std::shared_ptr<FuncExprAst> func_ptr = std::make_shared<FuncExprAst>(std::string($2), param_list, $7); 
    if($2=="") std::cerr << "error empty function string!\n";
    slc->add_function_name($2);
    slc->add_function_args($4);
    std::cout << "in def fun print:\n";
    $7->print();

    param_list.clear();

    slc->svlm_lang->done_ast_l_cc(); // pop the statement_list code block
    slc->add_function_body(func_ptr);
    $$ = func_ptr;
  }
  ;

param_list
  : param  { param_list.push_back($1); }
  | param_list param { 
    param_list.push_back($2);
    $$ = param_list;
  }
  ;

param
  : STR { 
    std::cout << "param: " << $1 << "\n"; 
    $$=$1;
  }
  ;


EOS
  : SEMICOLON
  | EOL
  ;


%%

void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
