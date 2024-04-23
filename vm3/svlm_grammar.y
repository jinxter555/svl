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

%type <std::shared_ptr<ExprAst>>  iexp



%%

start:
  lines
  ;

lines
  : %empty
  | lines line
  ;

line
  : EOL { std::cerr << "Read an empty line\n"; }
  | iexp EOL { 
    // $1->print(); 
    lang->current_context->add($1);
  }
  | error EOL { yyerrok; }
  ;

iexp
  : INT { $$ = std::make_shared<NumberExprAst>($1); }
  | iexp PLUS iexp {
    std::cout << "bin_op_expr:\n";
    $1->print(); 
    $3->print();
    $$ = std::make_shared<BinOpExprAst>($1, $3, BinOpcodeAST::INT_OP_INT, '+');
  }
  ;



%%

void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
