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
%define api.token.raw
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
bool skipline=false;
}

%token              EOL LPAREN RPAREN APP API MODULE MVAR FUNCTION LABEL LVAR DOT  COMMA
%token <long int>  INT
%token <long double>     FLT
%token <std::string>     STR
%token <long int> REGISTER
%token  CALL
 
//%nterm <long int>  iexp
//%nterm <double>     fexp
 
%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT
 
%nterm <std::string> DOTSTR
%nterm <full_symbol_t> modfunstr //modvarstr modfunvarstr
%nterm <Opcode>     opcode


%%

lines 
  : %empty
  | lines line
  ;

line
  : EOL {
    // readline eats newline character. only file scanning will encounter newline char
    // also do not insert directives in to assembly::code[]
    if(!skipline) // skip assembly %% directives because it's not instruction
      assembler->insert_instruction();  // instruction inserted when parsing a file aka encountering a newline char
    skipline=false;
  }
  | instruction
  | directive
  | super_instruction
  ;

super_instruction
  : MODULO CALL modfunstr {
    // std::cout << "call modfunstr:'" << $3.sfunction << "'\n";
    assembler->super_opfun_set_instruction(Opcode::CALL, $3); 
    // skipline=true;
    }
//| MODULO BRANCH labelstr {assembler->super_op_branch($2, $3); }
  ;

// do not insert directives in to assembly::code[]
directive
  : MODULO MODULO MODULE  DOTSTR  {assembler->add_module_name($4); skipline=true; } // have to skip insert_instruction 
  | MODULO MODULO FUNCTION STR    {assembler->add_function_name($4); skipline=true;}
  | MODULO MODULO LABEL STR       {assembler->add_label_name($4); skipline=true;}
  | MODULO MODULO LVAR  STR        {assembler->add_lvar_name($4); skipline=true;}
  //| MODULO opcode dotstr {std::cout<< "meta-opname code " << static_cast<int>($2) << $3 << "\n"; skipline=true;}
  ;


DOTSTR
  : STR
  | DOTSTR DOT STR { $$ = $1 + std::string(".")+ $3; }
  ;

// set module and fun full symbol  return a symbol struct
modfunstr
  : STR { 
    $$.smodule = assembler->get_current_context().smodule;
    $$.sfunction = $1;
    }
  | DOTSTR DOT STR { 
    $$.smodule = $1;
    $$.sfunction = $3;
    }
  ;
// set module and var full symbol  return a symbol struct
/*
modvarstr
  : STR DOT STR { 
    $$.smodule = $1;
    $$.mvar = $3;
  }
  ;
  */

instruction
  : opcode { 
    asm_instr = {$1, 0, 0, 0};  
    assembler->set_instruction(asm_instr); 
    std::cout<< "meta-opname code " << static_cast<int>($1) << "\n"; 
    //skipline = true;
  }
  | opcode REGISTER { 
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
  }
  | opcode REGISTER COMMA INT { 
    asm_instr = {$1, $2, $4, 0};
    assembler->set_instruction(asm_instr); 

  }
  | opcode REGISTER COMMA REGISTER COMMA INT { 
    asm_instr = {$1, $2, $4, $6}; 
    assembler->set_instruction(asm_instr); 
  }
  //
  // special init for float due to limitation of union
  | opcode FLT { 
    reg_t operand1;
    operand1.f = $2;
    asm_instr = {$1, operand1}; 
    assembler->set_instruction(asm_instr); 

  }
  | opcode REGISTER COMMA FLT { 
    reg_t operand2;
    operand2.f = $4;
    asm_instr = {$1, $2, operand2}; 
    assembler->set_instruction(asm_instr); 
  }
  | opcode REGISTER COMMA REGISTER COMMA FLT { 
    reg_t operand3;
    operand3.f = $6;
    asm_instr = {$1, $2, $4, operand3}; 
    assembler->set_instruction(asm_instr); 
  }
  ;

opcode:
  STR { 
    $$ = assembler->lookup_opcode($1); };
  ;

%%
// directive: EOL ;

void vslasm::Parser::error(const std::string& msg) {
  std::cerr << msg << "\n";
}