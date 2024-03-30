%{
#include <iostream>
#include <string>
#include <cmath>

%}
 
%require "3.7.4"
%language "C++"
%defines "ast_parser.hh"
%output "ast_parser.cpp"


%define api.parser.class {AstParser}
%define api.namespace {vslast}
%define api.value.type variant
%parse-param {AstScanner* scanner}

%locations


%code requires { 
#include "ast.hh"
namespace vslast {
  class AstScanner;
}}

%code {
#include "ast_scanner.hh"
#define yylex(x,y) scanner->lex(x,y)

#include "ast.cpp"
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

//%nterm <int> iexp
//%type <NumberExpr<int>*>  iexp
%type <std::unique_ptr<NumberExpr<int>>>  iexp

%%
lines
  : %empty
  | lines line
  ;

line
  : EOL       { std::cerr << "Read an empty line\n"; }
  | iexp EOL       { std::cout << "iexp " << $1->evaluate() << "\n"; }
  // | iexp EOL       { std::cout << "iexp " << $1 << "\n"; }
 // | fexp EOL       { std::cout << "fexp\n"; }
  | error EOL { yyerrok; }
  ;

iexp
  // : INT { $$ = 456; Expr<int> *a = new NumberExpr<int>(123); }
  : INT { $$ = std::make_unique<NumberExpr<int>>($1); }
  ;
//fexp //: FLT { Expr<float> *a = new NumberExpr<float>(3.1415); } ;

%%

void vslast::AstParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
