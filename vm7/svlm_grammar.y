%{
#include <iostream>
#include <string>
#include <cmath>
#include <tuple>
#include "lang.hh"
%}

%require "3.8.1"
%language "C++"
%defines "svlm_parser.hh"
%output "svlm_parser.cc"

%define api.parser.class {SvlmParser}
%define api.namespace {vslast}
%define api.value.type variant
%parse-param {SvlmScanner* scanner}
%parse-param {SvlmAst* svlm_lang}


 
%locations

%code requires { 
#include "ast.hh"
#include "svlm_ast.hh"

namespace vslast {
  class SvlmScanner;
}}

%code {
#include "svlm_scanner.hh"
#define yylex(x,y) scanner->lex(x,y)


}


%token YYEOF EOL COMMENT1 COMMENT2
%token MODULE DEF DO END AST_BREAK AST_RETURN AST_DEFAULT PRINT 
%token CASE FLOW WHILE REPEAT UNTIL DONE IS IF THEN ELSE WHEN WHERE
%token PAREN_L PAREN_R CUR_L CUR_R ARROW_L ARROW_R
%token SQBRK_L SQBRK_R
%token DOT AT DOLLAR COLON COMMA SEMICOLON
%token TRUE FALSE NIL
%token <string> IDENT_STR STR DQSTR
%token <s_integer>  INT
%token <s_float>     FLT
 
%nterm EOS // end of statement
%nterm <string> DOTSTR 
%nterm comments

%nterm <astexpr_u_ptr> proto_list proto arg_list arg list map
%nterm <astexpr_u_ptr>  kv_pair_list
%nterm <string> map_key
%type <std::tuple<string, astexpr_u_ptr>> kv_pair 



%nonassoc           ASSIGN
%left               AND OR 
%left               EQL NEQL GT LT GTEQ LTEQ 
%left               PLUS MINUS
%left               MULTIPLY DIVIDE PERCENT
%precedence         UMINUS
%precedence         NOT
%right              EXPONENT

%type <list_u_ptr> statement_list 
%type <astexpr_u_ptr> module function literals exp_eval variable statement print_exp caller comments

%start program_start

%%
program_start
  :  statement_list { 
    //cout << "program start:" << *$1 << "\n"; $1->print(); cout << "\n";
    svlm_lang->add_code(Operand("Prompt"), move($1));
    }
  ;

statement_list
  : statement_list EOS statement {
    if($1==nullptr) { yyerrok; }
    if($1!=nullptr && $3!=nullptr) { $1->add(move($3)); }
    $$ = move($1);
  }
  | statement  {
    auto new_list = std::make_unique<AstList>();
    new_list->add(move($1));
    $$ = move(new_list);
  }
  | statement_list error EOS statement { yyerrok; }
  | %empty { $$ = std::make_unique<AstList>(); }
  ;

statement
  : %empty {$$=nullptr;} // end of each statement
  | exp_eval { $$ = move($1); }
  | module { $$ = move($1); }
  | function { $$ = move($1); }
  | print_exp {$$ = move($1); }
  | comments { $$ = nullptr; }
  ;

comments
  :  COMMENT1 { $$=nullptr; }
  ;



module 
  : MODULE STR DO statement_list END 
  {
    //cout << "module : " << $2 << "\n";
    svlm_lang->add_module($2, move($4));
  }
  ;

function 
  //: DEF STR PAREN_L PAREN_R DO statement_list END {
  : DEF STR PAREN_L proto_list PAREN_R DO statement_list END {
    $$ = make_unique<AstFunc>($2, move($4), move($7));
  }
  ;

exp_eval
  : literals  { $$ = move($1); }
  | variable { $$ = move($1); }
  | list { $$ = move($1); }
  | map { $$ = move($1); }
  | caller { $$ = move($1); }
  | exp_eval MULTIPLY exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::mul); }
  | exp_eval DIVIDE exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::div); }
  | exp_eval PLUS exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::plus); }
  | exp_eval MINUS exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::minus); }
  | exp_eval GT exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::gt); }
  | exp_eval LT exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::lt); }
  | exp_eval LTEQ exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::lteq); }
  | exp_eval GTEQ exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::gteq); }
  | exp_eval EQL exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::eql); }
  | exp_eval NEQL exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::neql); }
  | exp_eval AND exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::and_); }
  | exp_eval OR exp_eval { $$ = make_unique<AstBinOp>(move($1), move($3), AstOpCode::or_); }
  | NOT exp_eval { $$ = make_unique<AstBinOp>(move($2), move($2), AstOpCode::not_); }
  | DOLLAR STR ASSIGN exp_eval { 
      $$ = make_unique<AstBinOp>(
        make_unique<AstMvar>($2),
        move($4), 
        AstOpCode::assign
      ); 
  }
  | DOLLAR DOTSTR ASSIGN exp_eval { 
      $$ = make_unique<AstBinOp>(
        make_unique<AstMvar>($2),
        move($4), 
        AstOpCode::assign
      ); 
  }

  | DOLLAR STR SQBRK_L exp_eval SQBRK_R ASSIGN exp_eval {
      $$ = make_unique<AstBinOp>(
        make_unique<AstMvar>($2, move($4)),
        move($7), 
        AstOpCode::assign
      ); 
  }
  | DOLLAR DOTSTR SQBRK_L exp_eval SQBRK_R ASSIGN exp_eval {
      $$ = make_unique<AstBinOp>(
        make_unique<AstMvar>($2, move($4)),
        move($7), 
        AstOpCode::assign
      ); 
  }




  | STR ASSIGN exp_eval { 
      $$ = make_unique<AstBinOp>(
        make_unique<AstLvar>($1),
        move($3), 
        AstOpCode::assign
      ); 
  }
  ;


literals
  : INT { $$ = make_unique<Operand>($1); }
  | FLT { $$ = make_unique<Operand>($1); }
  | TRUE { $$ = make_unique<Operand>(true); }
  | FALSE { $$ = make_unique<Operand>(false); }
  //| COLON STR { $$ = std::make_unique<OperandExprAst>(Operand(Atom($2))); }
  | DQSTR { $$ = make_unique<Operand>($1); }
  ;
caller
//  : STR PAREN_L PAREN_R { $$= std::make_unique<AstCaller>($1); }
  : DOTSTR PAREN_L arg_list PAREN_R { $$= std::make_unique<AstCaller>($1, move($3)); }
  ;


variable
  : DOLLAR STR { $$ = make_unique<AstMvar>($2); }
  | DOLLAR DOTSTR { $$ = make_unique<AstMvar>($2); }
  | DOLLAR STR SQBRK_L exp_eval SQBRK_R { $$ = make_unique<AstMvar>($2, move($4)); }
  | DOLLAR DOTSTR SQBRK_L exp_eval SQBRK_R { $$ = make_unique<AstMvar>($2, move($4)); }
  | STR { $$ = make_unique<AstLvar>($1); }
  ;





print_exp
  : PRINT exp_eval { $$ = std::make_unique<AstPrint>(move($2)); }
  //| PRINT DQSTR { $$ = std::make_unique<AstPrint> (std::make_unique<AstPrint>($2)); }
  ;

DOTSTR
  : STR
  | DOTSTR DOT STR { $$ = $1 + std::string(".")+ $3; }
  ;


//--------------------------------------------------- 
proto_list
  : proto  { 
    auto pl = make_unique<AstList>();
    pl->add(move($1)); 
    $$ = move(pl);
  }
  | proto_list COMMA proto { 
    $1->add(move($3));
    $$ = move($1);
  }
  | %empty { 
    $$ = make_unique<AstList>();
  } 
  ;

proto
  : STR { //std::cout << "param: " << $1 << "\n"; 
    $$=make_unique<Operand>($1);
  }
  ;
//--------------------------------------------------- 
arg_list
  : arg_list COMMA arg {
    $1->add(move($3));
    $$ = move($1);
  }
  | arg {
    auto al = std::make_unique<AstList>();
    al->add(move($1));
    $$ = move(al);
  }
  | %empty {$$ = std::make_unique<AstList>();}
  ;

arg
  : exp_eval { $$ = move($1); }
  ;

//--------------------------------------------------- 
list 
  : SQBRK_L arg_list SQBRK_R { 
    $$ =  make_unique<Operand>( make_shared<Operand>( move($2) )); 
    //$$ =  move($2); 
  } 
  ;

//--------------------------------------------------- 
map
  : PERCENT CUR_L kv_pair_list CUR_R { $$ = move($3); } ;

kv_pair_list
  : kv_pair_list COMMA kv_pair {
    $1->add(Operand(std::get<0>($3)), move(std::get<1>($3)));
    $$ = move($1);
  }
  | kv_pair {
    auto map_vptr = std::make_unique<AstMap>();
    map_vptr->add( Operand(get<0>($1)) , move(get<1>($1)));
    $$ = move(map_vptr);
  }
  | %empty {$$ = std::make_unique<AstMap>();
  }
  ;

kv_pair : map_key COLON exp_eval { $$ = {$1, move($3)}; } ;
map_key : DQSTR | STR ;

//--------------------------------------------------- EOS end of statement
EOS
  : SEMICOLON
  | EOL
  | COMMENT2
//  | YYEOF
  ;

%%

//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
