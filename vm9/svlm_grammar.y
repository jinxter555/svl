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
#include "operand.hh"
#include "operand_vars.hh"
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

%nterm <astnode_u_ptr> proto_list proto arg_list arg list map tuple repeat_loop while_loop 
%nterm <astnode_u_ptr> case case_match_list case_match if_then_else
%nterm <astnode_u_ptr> tuple_arg_list
%nterm <map_u_ptr>  kv_pair_list
%nterm <string> map_key
%type <tuple<string, astnode_u_ptr>> kv_pair 



%nonassoc           ASSIGN
%left               AND OR 
%left               EQL NEQL GT LT GTEQ LTEQ 
%left               PLUS MINUS
%left               MULTIPLY DIVIDE PERCENT
%precedence         UMINUS
%precedence         NOT
%right              EXPONENT

%type <list_u_ptr> statement_list 
%type <astnode_u_ptr> module function literals exp_eval variable statement print_exp caller comments 

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
    auto new_list = make_unique<AstList>();
    new_list->add(move($1));
    $$ = move(new_list);
  }
  | statement_list error EOS statement { yyerrok; }
  | %empty { $$ = make_unique<AstList>(); }
  ;

statement
  : %empty {$$=nullptr;} // end of each statement
  | exp_eval { $$ = move($1); }
  | module { $$ = move($1); }
  | function { $$ = move($1); }
  | print_exp {$$ = move($1); }
  | comments { $$ = nullptr; }
  | repeat_loop { $$ = move($1); }
  | while_loop { $$ = move($1); }
  | case { $$ = move($1); }
  | if_then_else { $$ = move($1); }
  ;

comments
  :  COMMENT1 { $$=nullptr; }
  ;



module 
  : MODULE STR DO statement_list END 
  {
    //cout << "Grammar!"; cout << "module : " << $2 << "\n"; cout << "statement list: " ; $4->print(); cout << "\n";
    svlm_lang->add_module($2, move($4));
  }
  ;

function 
  //: DEF STR PAREN_L PAREN_R DO statement_list END {
  : DEF STR PAREN_L proto_list PAREN_R DO statement_list END {
    //cout << "Grammar!"; cout << "func: " << $2 << "\n"; cout << "statement list: " ; $7->print(); cout << "\n";
    $$ = make_unique<AstFunc>($2, move($4), move($7));
  }
  ;

exp_eval
  : literals  { $$ = move($1); }
  | variable { $$ = move($1); }
  | list { $$ = move($1); }
  | map { $$ = move($1); }
  | tuple { $$ = move($1); }
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
  | tuple ASSIGN tuple {
      $$ = make_unique<AstBinOp>(
        move($1),
        move($3),
        AstOpCode::assign
      );
  }
  | tuple ASSIGN variable {
      $$ = make_unique<AstBinOp>(
        move($1),
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
  | NIL { $$ = make_unique<Operand>(nil); }
  //| COLON STR { $$ = std::make_unique<OperandExprAst>(Operand(Atom($2))); }
  | DQSTR { $$ = make_unique<Operand>($1); }
  ;
caller
//  : STR PAREN_L PAREN_R { $$= std::make_unique<AstCaller>($1); }
  : DOTSTR PAREN_L arg_list PAREN_R { 
    //cout << "in Grammar: caller!\n" ; $3->print(); cout << "\n";
    $$= make_unique<AstCaller>($1, move($3)); 
    }
  ;


variable
  : DOLLAR STR { $$ = make_unique<AstMvar>($2); }
  | DOLLAR DOTSTR { $$ = make_unique<AstMvar>($2); }
  | DOLLAR STR SQBRK_L exp_eval SQBRK_R { $$ = make_unique<AstMvar>($2, move($4)); }
  | DOLLAR DOTSTR SQBRK_L exp_eval SQBRK_R { $$ = make_unique<AstMvar>($2, move($4)); }

  | STR { $$ = make_unique<AstLvar>($1); }
//  | STR SQBRK_L exp_eval SQBRK_R { $$ = make_unique<AstLvar>($2, move($3)); }

  ;





print_exp
  : PRINT exp_eval { $$ = make_unique<AstPrint>(move($2)); }
  //| PRINT DQSTR { $$ = std::make_unique<AstPrint> (std::make_unique<AstPrint>($2)); }
  ;

DOTSTR
  : STR
  | DOTSTR DOT STR { $$ = $1 + string(".")+ $3; }
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
tuple_arg_list
  : tuple_arg_list COMMA arg {
    $1->add(move($3));
    $$ = move($1);
  }
  | arg {
    auto al = make_unique<Tuple>();
    al->add(move($1));
    $$ = move(al);
  }
  | %empty {$$ = make_unique<Tuple>();}
  ;

//---------------------------------------------------  
arg_list
  : arg_list COMMA arg {
    $1->add(move($3));
    $$ = move($1);
  }
  | arg {
    auto al = make_unique<AstList>();
    al->add(move($1));
    $$ = move(al);
  }
  | %empty {$$ = make_unique<AstList>();}
  ;

arg
  : exp_eval { $$ = move($1); }
  ;


//--------------------------------------------------- 
list 
  : SQBRK_L arg_list SQBRK_R { 
    $$ =  move($2); 
  } 
  ;

//--------------------------------------------------- 
map
  : PERCENT CUR_L kv_pair_list CUR_R { $$ = move($3); } ;

kv_pair_list
  : kv_pair_list COMMA kv_pair {
     $1->add(Operand(get<0>($3))._to_str(), move(get<1>($3)));
     $$ = move($1);
    //$$ = nullptr;
  }
  | kv_pair {
    auto map_vptr = make_unique<AstMap>();
    map_vptr->add( Operand(get<0>($1)) , move(get<1>($1)));
    $$ = move(map_vptr);
  }
  | %empty {$$ = make_unique<AstMap>();
  }
  ;

kv_pair : map_key COLON exp_eval { $$ = {$1, move($3)}; } ;
map_key : DQSTR | STR ;


//--------------------------------------------------- 
tuple
  //: CUR_L arg_list CUR_R {
  : CUR_L tuple_arg_list CUR_R {
    $$ = make_unique<AstTuple>(move($2));
    //$$ = make_unique<AstTuple>(make_unique<Tuple>(move($2)));
  }
  ;

//--------------------------------------------------- while loop 
while_loop
  : WHILE exp_eval DO statement_list END {
    $$ = make_unique<AstWhile>(move($2), move($4));
  }
  ;


//--------------------------------------------------- Repeat loop 

repeat_loop
  : REPEAT statement_list UNTIL exp_eval DONE {
    $$ = make_unique<AstRepeat>(move($4), move($2));
  }
  ;

//--------------------------------------------------- Case block 

case
  : CASE exp_eval DO case_match_list END {
    unique_ptr<AstCase> case_ptr = make_unique<AstCase>(move($2), move($4));
    $$ = move(case_ptr);
  }
  ;                                                                                                                                                               

case_match_list
  : %empty {
    $$ = make_unique<AstList>();
  }
  | case_match {
    auto  ml =   make_unique<AstList>();
    ml->add(move($1));
    $$ = move(ml);
  }
  | case_match_list case_match {
    if($2 != nullptr)
      $1->add(move($2));
    $$ = move($1);
  }
  | case_match_list EOS case_match {
    if($3 != nullptr)
      $1->add(move($3));
    $$ = move($1);
  }
  | case_match_list error EOS case_match { yyerrok; }

  ;

case_match
  : IS literals ARROW_R statement_list {
    $$ = make_unique<AstCaseMatchIs>(move($2), move($4));
  } 
  | IS variable WHEN statement ARROW_R statement_list {
    $$ = make_unique<AstCaseMatchWhen>(move($2), move($4), move($6));
  }
  | IS tuple ARROW_R statement_list {
    $$ = make_unique<AstCaseMatchIs>(move($2), move($4));
  } 
  | IS tuple WHEN statement ARROW_R statement_list {
    $$ = make_unique<AstCaseMatchWhen>(move($2), move($4), move($6));
  }
  | ELSE ARROW_R statement_list {
    $$ = make_unique<AstCaseMatchElse>(move($3));
  }
  ;

//--------------------------------------------------- if then else end
if_then_else
  :
  ;
if_then_else
  : IF exp_eval THEN statement_list END {
    auto l = make_unique<AstList>();
    auto y = make_unique<Operand>(true);
    l->add(make_unique<AstCaseMatchIs>(move(y), move($4)));
    $$ = make_unique<AstCase>(move($2), move(l));
  }
  ;
/*
  | IF exp_eval THEN statement_list ELSE statement_list END {
    auto l = make_unique<ListExprAst>("if then else end");
    auto y = make_unique<OperandExprAst>(Operand(true));
    l->add(std::make_unique<CaseMatchIsExprAst>(y, $4));
    l->add(std::make_unique <CaseMatchElseExprAst>($6));
    std::shared_ptr<CaseExprAst> case_ptr =
      std::make_shared<CaseExprAst>($2, l);
    $$ = case_ptr;
  }
  ;
*/




//--------------------------------------------------- EOS end of statement
EOS
  : SEMICOLON
  | EOL
  | COMMENT2
//  | YYEOF
  ;

%%

//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const string& msg) {
    cerr << "line "  << l << ": " << msg << '\n';
}
