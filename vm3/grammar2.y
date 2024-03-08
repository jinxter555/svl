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


//---------------
#define call_param_d(x) \
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, x); \
    asm_instr = {Opcode(Opcode::LOAD_L), call_register, Reg::fp, vadr};   \
    assembler->set_instruction(asm_instr); \
    assembler->insert_instruction(); \
    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0}; \
    assembler->set_instruction(asm_instr); \
    assembler->insert_instruction();


// instr_t asm_instr = {Opcode(Opcode::NOOP), 0,0,0};
instr_t asm_instr = {Opcode(0), 0,0,0};
bool skipline=false;
s_int_t call_register=0;
}

%token EOL LPAREN RPAREN APP API MODULE MVAR FUNCTION LABEL LVAR LARG DOT  COMMA COLON URI
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
%nterm <std::string> call_params
%nterm <full_symbol_t> modfunstr funlvarstr uri_api //modvarstr modfunvarstr
%nterm <long int> call_register
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
  : MODULO CALL modfunstr 
    { assembler->super_opfun_set_instruction(Opcode::CALL, $3); }
  | MODULO CALL modfunstr call_register COMMA call_params 
    { assembler->super_opfun_set_instruction(Opcode::CALL, $3); } 
//| MODULO BRANCH labelstr {assembler->super_op_branch($2, $3); }
  | MODULO LVAR STR INT   {
    assembler->add_lvar_name($3); 
    asm_instr = {Opcode(Opcode::PUSH_C), $4, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
  | MODULO LVAR STR FLT  {
    reg_t operand2;
    operand2.f = $4;
    assembler->add_lvar_name($3); 
    asm_instr = {Opcode(Opcode::PUSH_C), operand2, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
  | MODULO LOAD_L REGISTER COMMA funlvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $5);
    asm_instr = {Opcode(Opcode::LOAD_L), $3, Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  | MODULO STORE_L REGISTER COMMA funlvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $5);
    asm_instr = {Opcode(Opcode::STORE_L), $3, Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  // MODULO INIT_GV_COUNT {} // global variable count for vmstack.resize
  /*
  | MODULO STR {
    std::cerr << "unknown super instruction!\n";
    asm_instr = {Opcode(Opcode::NOOP), 0, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
  */
  ;


// do not insert directives in to assembly::code[]
directive
  : MODULO MODULO URI uri_api { skipline=true;} 
  | MODULO MODULO MODULE  DOTSTR  {assembler->add_module_name($4); skipline=true; } 
  | MODULO MODULO MVAR STR {
    assembler->add_mvar_name($4);  
    skipline=true;
    }
  | MODULO MODULO FUNCTION STR    {assembler->add_function_name($4); skipline=true;}
  | MODULO MODULO LABEL STR       {
    assembler->add_label_name($4);
    std::cout << "adding label: " << $4 << "\n";
    skipline=true;}
  | MODULO MODULO LARG STR        {assembler->add_larg_name($4); skipline=true;}
  // array needs another instruction to resize vmstack
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
/*
// set module and var full symbol  return a symbol struct
/*
modvarstr
  : STR DOT STR { 
    $$.smodule = $1;
    $$.mvar = $3;
  }
  ;
  */

/*
call_params
  : funlvarstr { 
    std::cout << "cpara1: " <<  $1.lvar << "\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $1);
    asm_instr = {Opcode(Opcode::LOAD), call_register, Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();

    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();
    }
  | call_params COMMA funlvarstr { 
    std::cout << "cparaM: " <<  $3.lvar << "\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $3);
    asm_instr = {Opcode(Opcode::LOAD), call_register, Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();

    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();
    }
  ;
*/

call_params
  : funlvarstr { call_param_d($1); }
  | call_params COMMA funlvarstr { call_param_d($3); }
  ;

call_register
  : REGISTER { call_register = $1; std::cout << "call register: " << $1 << "\n";}
  ;

instruction
  : opcode { 
    //std::cout<< "meta-opname code " << static_cast<int>($1) << "\n"; 
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