%{
#include <iostream>
#include <string>
#include <cmath>
#include <FlexLexer.h>
%}
%require "3.7.4"
%language "C++"
%defines "Parser2.hpp"
%output "Parser2.cpp"

%define api.parser.class {Parser}
%define api.namespace {vslasm}
%define api.value.type variant
%parse-param {Scanner* scanner}
%parse-param {Assembler* assembler}

%code requires {
#include "assembler.h"
namespace vslasm {
  class Scanner;
}}

%code {
#include "Scanner2.hpp"
#define yylex(x) scanner->lex(x)
}

%token              EOL LPAREN RPAREN
%token <long long>  INT
%token <double>     FLT
%token <std::string>     STR
 
//%nterm <long long>  iexp
//%nterm <double>     fexp
 
%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT
 
%token COMMA REGISTER
%nterm <std::string>     opname

//  opcode REGISTER { std::cout << "R1: opcode: " << $1 <<  "\n"; }

%%

lines 
  : %empty
  | lines line
  ;

line: EOL
  | instruction
  | directive
  ;


instruction
  : opname REGISTER { 
    std::cout << "R1: opname: " << $1 <<  "\n"; 
    if(assembler->lookup_opcode($1) != Opcode::INVALID) {
      std::cout << "opname is valid!\n";
    } else {
      std::cout << "opname is not valid!!!!\n";
    }
    }
  | opname REGISTER COMMA REGISTER { std::cout << "R2: opcode: " << $1 <<  "\n"; }
  | opname REGISTER COMMA REGISTER COMMA REGISTER { std::cout << "R3: opcode: " << $1 <<  "\n"; }
  ;

opname: STR;

directive: EOL
  ;
%%

void vslasm::Parser::error(const std::string& msg) {
  std::cerr << msg << "\n";
}
