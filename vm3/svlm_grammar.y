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
%parse-param {SvlmLang* lang}

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
}


%token              EOL LPAREN RPAREN
%token <long long>  INT
%token <double>     FLT
%token <char>       INTVAR FLTVAR
 
%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT

%type <std::shared_ptr<NumberExprAst>>  iexp



%%

start:
  lines
  ;

lines
  : %empty
  | lines line
  ;

line
  : EOL { 
      //std::shared_ptr<ExprAst> current_context = lang->current_contexts.top(); 
      std::cerr << "Read an empty line\n"; 
    }
  // | iexp EOL       { std::cout << "iexp " << std::any_cast<long long>($1->evaluate()) << "\n"; }
  | iexp EOL       { 
    //std::cout << "iexp " << std::any_cast<int>($1->evaluate()) << "\n"; 
    $1->print();
    if(lang->current_context == nullptr) {
      std::cout << "current context is null!\n";

    }
    //lang->current_context->add($1);
  }
// | iexp EOL       { std::cout << "iexp " << $1 << "\n"; }
// | iexp EOL       { std::cout << "iexp " << $1 << "\n"; }
 // | fexp EOL       { std::cout << "fexp\n"; }
  | error EOL { yyerrok; }
  ;

iexp
  : INT { $$ = std::make_shared<NumberExprAst>((int)$1); }
  ;


//fexp //: FLT { Expr<float> *a = new NumberExpr<float>(3.1415); } ;

%%

void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
