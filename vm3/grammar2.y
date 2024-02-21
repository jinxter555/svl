%{
#include <iostream>
#include <string>
#include <cmath>
#include <FlexLexer.h>
%}
%require "3.7.4"
%language "C++"


%defines "Parser2.hh"
%output "Parser2.cpp"

%define api.parser.class {Parser}
%define api.namespace {vslasm}
%define api.value.type variant
%parse-param {Scanner* scanner}
%parse-param {Assembler* assembler}


%code requires {
#include "assembler.hh"
namespace vslasm {
  class Scanner;
}}

%code {
#include "Scanner2.hh"
#define yylex(x) scanner->lex(x)
instr_t asm_instr = {Opcode(0), 0,0,0};
}

%token              EOL LPAREN RPAREN 
%token <long int>  INT
%token <long double>     FLT
%token <std::string>     STR
 
//%nterm <long int>  iexp
//%nterm <double>     fexp
 
%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT
 
%token COMMA 
%token <long int> REGISTER
// %nterm <std::string>     opname
%nterm <Opcode>     opcode


%%

lines 
  : %empty
  | lines line
  ;

line: EOL { 
  //assembler->set_instruction(asm_instr);
  assembler->insert_instruction();
  }
  | instruction
 // | directive
  ;


instruction
  : opcode REGISTER { 
    asm_instr = {$1, $2, 0, 0};  
    assembler->set_instruction(asm_instr); 
  } 
  | opcode REGISTER COMMA REGISTER {
    asm_instr = {$1, $2, $4, 0};
    assembler->set_instruction(asm_instr); 
  }
  | opcode REGISTER COMMA REGISTER COMMA REGISTER {
    asm_instr = {$1, $2, $4, $6}; 
    assembler->set_instruction(asm_instr); 
  }
  | opcode INT { 
    asm_instr = {$1, $2, 0, 0}; 
    assembler->set_instruction(asm_instr); 
    std::cout << static_cast<int>($1) << " " << $2 << "\n"; 
  }
  | opcode REGISTER COMMA INT { 
    asm_instr = {$1, $2, $4, 0};
    assembler->set_instruction(asm_instr); 
    std::cout << static_cast<int>($1) << " " << $2 << " " << $4 << "\n"; 

  }
  | opcode REGISTER COMMA REGISTER COMMA INT { 
    asm_instr = {$1, $2, $4, $6}; 
    assembler->set_instruction(asm_instr); 
  }
  | opcode FLT { 
    reg_t operand1;
    operand1.f = $2;
    asm_instr = {$1, operand1}; 
    assembler->set_instruction(asm_instr); 

  }
  | opcode REGISTER COMMA FLT { 
    //asm_instr_f = {$1, $2, $4, 0};
    //assembler->set_instruction(asm_instr_f); 
  }
  | opcode REGISTER COMMA REGISTER COMMA FLT { 
    //asm_instr = {$1, $2, $4, $6}; 
    //assembler->set_instruction(asm_instr); 
  }
  ;

opcode:
  STR { $$ = assembler->lookup_opcode($1); };
  ;

%%
// directive: EOL ;

void vslasm::Parser::error(const std::string& msg) {
  std::cerr << msg << "\n";
}