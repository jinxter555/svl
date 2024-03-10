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

// instr_t asm_instr = {Opcode(Opcode::NOOP), 0,0,0};
instr_t asm_instr = {Opcode(0), 0,0,0};
bool skipline=false;
s_int_t call_register=0;
}

%token EOL LPAREN RPAREN APP API MODULE MVAR FUNCTION LABEL LVAR LARG DOT  COMMA COLON URI LSBRACKET RSBRACKET
%token <long int>  INT
%token <long double>     FLT
%token <std::string>     STR
%token <long int> REGISTER
%token CALL LOAD_L STORE_L LOAD_G STORE_G
 
//%nterm <long int>  iexp
//%nterm <double>     fexp
 
%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT
 
%nterm <std::string> DOTSTR
%nterm  param_list param
%nterm <full_symbol_t> uri_api modfunstr funlvarstr modvarstr // modfunvarstr
%nterm <long int> call_register
%nterm <Opcode>     opcode
%nterm <reg_t> array number element


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
  : MODULO CALL modfunstr 
    { assembler->super_opfun_set_instruction(Opcode::CALL, $3); }
//  | MODULO CALL modfunstr call_register COMMA call_params 
  | MODULO CALL modfunstr call_register param_list
    { assembler->super_opfun_set_instruction(Opcode::CALL, $3); } 
//| MODULO BRANCH labelstr {assembler->super_op_branch($2, $3); }
  | MODULO LVAR STR number   {
    assembler->add_lvar_name($3); 
    asm_instr = {Opcode(Opcode::PUSH_C), $4, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
  | MODULO MVAR STR {
    assembler->add_mvar_name($3);  
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
  | MODULO MVAR STR number {
    assembler->add_mvar_name($3);  
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, $4, 0};  
    assembler->set_instruction(asm_instr); 
  }
  | MODULO MVAR STR LSBRACKET array RSBRACKET  {
      std::cout << "m array def  " << "$6" << "\n";
    assembler->add_mvar_name($3);  
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, 0, 0};  
    assembler->set_instruction(asm_instr); 
  } 
  | MODULO MVAR STR INT LSBRACKET RSBRACKET  {
    std::cout << "m array def num element: " << $4 << "\n";
    assembler->add_mvar_name($3, $4);   // don't forget the offset INT
    asm_instr = {Opcode(Opcode::DATA_RESIZE), $4, 0, 0};  
    assembler->set_instruction(asm_instr); 
  } 
  | LOAD_L REGISTER COMMA funlvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $4);
    asm_instr = {Opcode(Opcode::LOAD_L), $2, Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  | STORE_L REGISTER COMMA funlvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $4);
    asm_instr = {Opcode(Opcode::STORE_L), $2, Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  | LOAD_G REGISTER COMMA REGISTER COMMA modvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, $6);
    asm_instr = {Opcode(Opcode::LOAD_G), $2, $4, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  | STORE_G REGISTER COMMA REGISTER COMMA modvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, $6);
    asm_instr = {Opcode(Opcode::STORE_G), $2, $4, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  ;


// do not insert directives in to assembly::code[]
directive
  : MODULO MODULO URI uri_api { skipline=true;} 
  | MODULO MODULO MODULE  DOTSTR  {assembler->add_module_name($4); skipline=true; } 
  | MODULO MODULO FUNCTION STR    {assembler->add_function_name($4); skipline=true;}
//| MODULO MODULO LABEL STR       { assembler->add_label_name($4); std::cout << "adding label: " << $4 << "\n"; skipline=true;}
  | MODULO MODULO LARG STR        {assembler->add_larg_name($4); skipline=true;}
  ;

uri_api
  : COLON COLON STR DOT STR {
    assembler->add_app_name($3);
    assembler->add_api_name($5);
    $$ = assembler->get_current_context();
    } //full symbol from another app api module
  ;

DOTSTR
  : STR
  | DOTSTR DOT STR { $$ = $1 + std::string(".")+ $3; }
  ;

//----------------------------------- array decl
array 
  : element 
  | array element 
  ;

element
  : number { std::cout << $1.i << " "; }
  ;

//--- number dec
number 
  : FLT { $$.f = $1; }
  | INT { $$.i = $1; }
  ;

//-----------------------------------
call_register
  : REGISTER { call_register = $1; }
  ;

//-----------------------------------
param_list
  : param
  | param param_list
  ;

param 
  : funlvarstr {
    //std::cout << "funlvarstr\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $1);
    asm_instr = {Opcode(Opcode::LOAD_L), call_register, Reg::fp, vadr};
    //std::cout << "vadr: " << vadr << "\n";
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0};
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
  }
  | modvarstr {
    //std::cout << "modvarstr\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, $1);
    asm_instr = {Opcode(Opcode::LOAD_G), call_register, -1, vadr};
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0};
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
  }
  ;


// set module and fun full symbol  return a symbol struct
modfunstr
  : STR { 
    $$.smodule = assembler->get_current_context().smodule;
    $$.mfunction = $1;
    }
  | DOTSTR COLON STR { 
    $$.smodule = $1;
    $$.mfunction = $3;
    }
  // COLON COLON DOTSTR COLON STR {} //full symbol from another app api module
  ;
funlvarstr
  : STR { 
    $$ = assembler->get_current_context();
    $$.smodule = assembler->get_current_context().smodule;
    $$.mfunction = assembler->get_current_context().mfunction;
    $$.lvar = $1;
    }
  ;
// set module and var full symbol  return a symbol struct
modvarstr
  : STR { 
    $$ = assembler->get_current_context();
    $$.smodule = assembler->get_current_context().smodule;
    $$.mvar = $1;
    }
  | STR COLON STR { 
    $$ = assembler->get_current_context();
    $$.smodule = $1;
    $$.mvar = $3;
    }
  ;

instruction
  : opcode { 
    asm_instr = {$1, 0, 0, 0};  
    assembler->set_instruction(asm_instr); 
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
  | opcode number { 
    asm_instr = {$1, $2, 0, 0}; 
    assembler->set_instruction(asm_instr); 
  }
  | opcode REGISTER COMMA number { 
    asm_instr = {$1, $2, $4, 0};
    assembler->set_instruction(asm_instr); 
  }
  | opcode REGISTER COMMA REGISTER COMMA number { 
    asm_instr = {$1, $2, $4, $6}; 
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