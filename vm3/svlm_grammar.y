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


%token              MODULE DEF DO END
%token              EOL LPAREN RPAREN AT DOLLAR COLON SEMICOLON
%token <std::string> IDENT_STR STR
%token <int>  INT
%token <float>     FLT
 
%nterm <char>  math_bin_op
%nterm param_list param exp def_function
%nterm EOS // end of statement

%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT

%type <std::shared_ptr<ExprAst>>  iexp

%start program_start


%%
program_start
  : statement_list
  ;

statement_list
  : statement
  | statement_list statement
  ;

statement
  : exp
  // function def here def_function a() { statement_list }
  | def_module
  | def_function EOS
  ;

exp
  : EOS { std::cerr << "Read an empty line\n"; }
  | iexp EOS { 
    svlm_lang->ast_current_context->add($1);
    // $1->print(); //std::cout <<  "ieval: " << std::any_cast<int>($1->evaluate()) << "\n\n";
  }
  | error EOL { yyerrok; }
  ;

def_module
  : MODULE STR EOL { 
    svlm_lang = slc->svlm_lang;
    slc->add_module_name($2); 
    svlm_lang->ast_current_context->add( 
      std::make_shared<DeclExprAst>(
        std::make_shared<IdentExprAst>($2), 
        DeclOpcodeAST::MODULE)
    );
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
  : DEF STR LPAREN param_list RPAREN { 
    std::cout << "function: " << $2 << "\n";
    // std::make_shared<FuncExprAst>(std::string($2), param_list, nullptr); 
    if($2=="") std::cerr << "error empty function string!\n";
    slc->add_function_name($2);
    slc->add_function_args(param_list);
    param_list.clear();
  }
  ;

param_list
  : param 
  | param param_list 
  ;

param
  : STR { std::cout << "param: " << $1 << "\n"; 
    param_list.push_back(std::string($1));
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
