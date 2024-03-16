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


int line=1, element_count = 0;
instr_t asm_instr = {Opcode(Opcode::NOOP), 0,0,0};
bool skipline=false;
bool element_init = false;
s_int_t call_register=0;
}

%token EOL LPAREN RPAREN APP API MODULE MVAR FUNCTION LABEL LVAR LARG DOT  COMMA COLON URI LSBRACKET RSBRACKET COMMENT EMPTYLINE BRANCH TEXT
%token <long int>  INT
%token <long double>     FLT
%token <std::string>     STR VSLSTRING
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
%nterm <full_symbol_t> uri_api modfunstr funlvarstr modvarstr  labelstr // modfunvarstr
%nterm <long int> call_register
%nterm <Opcode>     opcode loadstore_l loadstore_g
%nterm <reg_t> array_g number element_g


%%

lines 
  : %empty
  | lines line
  ;

line
  : EOL {
    //
    // readline eats newline character. only file scanning will encounter newline char
    // also do not insert directives in to assembly::code[]
    // NOTE:  recursive parsing within a single line do not reach here 
    //        to have the instruction inserted. i.e. module array  [1 2 3 4]
    //
    if(!skipline) // skip assembly %% directives because it's not instruction
      assembler->insert_instruction();  // instruction inserted when parsing a file aka encountering a newline char
    skipline=false;
    line++;
    assembler->line_total_read++;
  }
  | instruction
  | directive
  | super_instructions
  | COMMENT { assembler->line_total_read++; }     // parser bugs out without this
  | EMPTYLINE { assembler->line_total_read++; }   // parser bugs out without this
  ;

super_instructions
  : var_access
  | var_decl
  | var_array_g_decl
  | function_call
  | MODULO BRANCH opcode labelstr { 
    std::cout << static_cast<int>($3) << "label:" << $4.label << "\n"; 
    s_int_t ladr = assembler->get_sym_addr(key_tok_t::label, $4);
    if(ladr==-1) { assembler->add_unresolved_sym(key_tok_t::label, $4); }
    asm_instr = {$3, ladr, 0, 0};  
    assembler->set_instruction(asm_instr); 
    }
  // | MODULO BRANCH STR { std::cout <<  ":" << $3 << "\n";  skipline = true; }
  ;
//-----------------------------------  function call declaration
function_call
  : MODULO CALL modfunstr { 
    assembler->super_opfun_set_instruction(Opcode::CALL, $3); 
    }
  | MODULO CALL modfunstr call_register param_list { 
    assembler->super_opfun_set_instruction(Opcode::CALL, $3);
    } 
  ;
//-----------------------------------  variable array declaration
var_array_g_decl 
  : MODULO MVAR STR LSBRACKET array_g RSBRACKET  {
    assembler->add_mvar_name($3, 0);  // add mvar name default add + 1,
    assembler->mvc += element_count;  // should add element_count instead
    // need to reset size here
    element_count=0; // reset for for next array
    skipline = true; // insert is done by array_g grammar
  } 
  | MODULO MVAR STR INT LSBRACKET RSBRACKET  {
    assembler->add_mvar_name($3, $4);   // don't forget the offset INT
    asm_instr = {Opcode(Opcode::DATA_RESIZE), $4, 0, 0};  
    assembler->set_instruction(asm_instr); 
  } 
  | MODULO MVAR STR INT LSBRACKET array_g RSBRACKET  {
    assembler->add_mvar_name($3, 0);  // add mvar name default add + 1,
    assembler->mvc += element_count;  // should add element_count instead
    int remain_size = $4 - element_count;
    element_count=0; // reset for for next array
    if(remain_size > 0) {
      asm_instr = {Opcode(Opcode::DATA_RESIZE), remain_size, 0, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->mvc += remain_size; 
      skipline = false;
    } else {
      skipline = true; // insert is done by array_g grammar
    }
  }
  ;
//-----------------------------------  variable declaration
var_decl
  : MODULO LVAR STR number   {
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
  | MODULO MODULO MVAR STR VSLSTRING {
    int i;

    s_int_t l=$5.length();
    int mvs = l / sizeof(reg_t);
    int remain = l  % sizeof(reg_t);
    int offset = mvs; if(remain != 0) offset++;

    reg_t block, *bptr=(reg_t *)$5.c_str();

    assembler->add_mvar_name($4, offset);  

    std::cout << "mvs: " << mvs << ":" << l  << " string " << $5 <<  "\n";

    // add size of string first
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, l, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();  

    for(i=0; i<mvs; i++, bptr++) {
      block = *bptr;
      for(int j=0; j<sizeof(s_float_t); j++) std::cout << bptr->c[j]; std::cout << "\n";
      asm_instr = {Opcode(Opcode::DATA_ADD), -1, block, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();  
    }
    if(remain != 0) {
      block = *bptr;
      for(i=0; i<remain; i++) std::cout << block.c[i]; std::cout << "\n";
      for(i=remain; i<sizeof(s_float_t); i++) block.c[i] = 0; // zero all 
      asm_instr = {Opcode(Opcode::DATA_ADD), -1, block, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();  
    }

    skipline = true;
  }
  ;
//-----------------------------------  variable acccess 
var_access:
  loadstore_l REGISTER COMMA funlvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, $4);
    asm_instr = {$1, $2, Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  | loadstore_g REGISTER COMMA REGISTER COMMA modvarstr {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, $6);
    asm_instr = {$1, $2, $4, vadr};  
    assembler->set_instruction(asm_instr); 
  }
  ;

loadstore_l
  : LOAD_L  {$$ = Opcode(Opcode::LOAD_L);  }
  | STORE_L {$$ = Opcode(Opcode::STORE_L); }
  ;

loadstore_g
  : LOAD_G  {$$ = Opcode(Opcode::LOAD_G);  }
  | STORE_G {$$ = Opcode(Opcode::STORE_G); }
  ;

// do not insert directives in to assembly::code[]
directive
  : MODULO MODULO URI uri_api { skipline=true;} 
  | MODULO MODULO MODULE  DOTSTR  {assembler->add_module_name($4); skipline=true; } 
  | MODULO MODULO FUNCTION STR    {assembler->add_function_name($4); skipline=true;}
  | MODULO MODULO LABEL STR       {assembler->add_label_name($4); skipline=true;}
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
array_g
  : element_g
  | array_g element_g
  ;

element_g
  : number { 
    //std::cout << $1.i << " "; 
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, $1, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();
    element_count++;
  }
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

//----------------------------------- for calling function
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
// label string for branching
labelstr
  : STR { 
    $$ = assembler->get_current_context();
    $$.smodule = assembler->get_current_context().smodule;
    $$.mfunction = assembler->get_current_context().mfunction;
    $$.label = $1;
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
  std::cerr << msg + " on line: " << line << "\n";
}