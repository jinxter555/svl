%{
#include <iostream>
#include <string>
#include <cmath>
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
%parse-param {SvlmLangContext* slc}


 
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


SvlmLang* svlm_lang;
std::vector<std::string> lvar_list;

}


%token YYEOF EOL COMMENT1 COMMENT2
%token MODULE DEF DO END AST_BREAK AST_RETURN AST_DEFAULT PRINT 
%token CASE FLOW WHILE REPEAT UNTIL DONE IS IF THEN ELSE WHEN WHERE
%token PAREN_L PAREN_R CUR_L CUR_R AT DOLLAR COLON COMMA SEMICOLON ARROW_L ARROW_R
%token SQBRK_L SQBRK_R
%token TRUE FALSE NIL
%token <std::string> IDENT_STR STR DQSTR
%token <int>  INT
%token <float>     FLT
 
%nterm EOS // end of statement
%nterm <std::vector<std::string>> param_list 
%nterm <std::string> param
//%nterm <ast_op> comparison_ops
%nterm comments

%nonassoc           ASSIGN
%left               AND OR 
%left               EQL NEQL GT LT GTEQ LTEQ 
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         NOT
%right              EXPONENT

%type <std::shared_ptr<ExprAst>>  exp exp_eval statement arg print_exp module function caller tuple comments literals  variable
%type <std::shared_ptr<ExprAst>>  case while_loop repeat_loop if_then_else 
%type <std::shared_ptr<ListExprAst>>  statement_list  arg_list case_match_list list
%type <std::shared_ptr<CaseMatchExprAst>>  case_match 
%start program_start


%%
program_start
  : statement_list  { auto astcode = slc->svlm_lang->ast_current_contexts.top(); astcode->add($1); }
  ;

comments
  : COMMENT1 {$$=nullptr;}
  ;

statement_list
  : statement_list EOS statement {
    if($1==nullptr) {std::cerr << "statement syntax error"; yyerrok; }
    if($1!=nullptr && $3!=nullptr) $1->add($3);
    $$ = $1;
  }
  | statement  {
    auto ast_current_context = std::make_shared<ListExprAst>(std::string("statement code here"));
    ast_current_context->add($1);
    $$ = ast_current_context;
  }
  | statement_list error EOS statement { yyerrok; }
  | %empty { $$ = std::make_shared<ListExprAst>(std::string("empty statement code")); }
  ;

statement
  : %empty {$$=nullptr;} // end of each statement
  | exp 
  | module
  | function
  | case
  | while_loop
  | if_then_else
  | repeat_loop
  | print_exp
  | comments {$$ = nullptr; }
  ;

//--------------------------------------------------- module decl
module
  : MODULE STR { 
    svlm_lang = slc->svlm_lang;
    slc->add_module_name($2); 
    $$ = std::make_shared<DeclExprAst>( std::make_shared<IdentExprAst>($2), DeclOpcodeAST::MODULE);
  }
  ;

//--------------------------------------------------- callee argument list
arg_list
  : arg_list COMMA arg {
    $1->add($3);
    $$ = $1;
  }
  | arg {
    auto ast_current_context = std::make_shared<ListExprAst>("argument block");
    ast_current_context->add($1);
    $$ = ast_current_context;
  }
  | %empty {$$ = std::make_shared<ListExprAst>("empty args");}
  ;

arg
  : exp_eval
  ;


//--------------------------------------------------- caller/callee 
caller
  : STR PAREN_L arg_list PAREN_R {
    std::shared_ptr<CallExprAst> caller = std::make_shared<CallExprAst>($1, $3); 
    $$ = caller;
  }


//--------------------------------------------------- exp eval
exp
  : exp_eval {$$ = $1; }
  | AST_RETURN { $$ = std::make_shared<ControlFlowExprAst>(ControlFlow::ast_return); }
  | AST_RETURN exp_eval { $$ = std::make_shared<ControlFlowExprAst>(ControlFlow::ast_return, $2); }
  | AST_BREAK { $$ = std::make_shared<ControlFlowExprAst>(ControlFlow::ast_break); }
  ;

print_exp
  : PRINT exp { $$ = std::make_shared<PrintExprAst>($2); }
  | PRINT DQSTR { $$ = std::make_shared<PrintExprAst> (std::make_shared<IdentExprAst>($2)); }
  ;

//--------------------------------------------------- exp var eval
tuple
  : CUR_L arg_list CUR_R { $$ = std::make_shared<TupleExprAst>($2); }

list
  : SQBRK_L arg_list SQBRK_R { $$ = $2; }

exp_eval
  : literals
  | variable
  | tuple { $$ = $1; }
  | PAREN_L exp_eval PAREN_R        { $$ = $2; }
  | caller
  | exp_eval MULTIPLY exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::mul); }
  | exp_eval DIVIDE exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::div); }
  | exp_eval PLUS exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::plus); }
  | exp_eval MINUS exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::minus); }
  | exp_eval GT exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::gt); }
  | exp_eval LT exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::lt); }
  | exp_eval LTEQ exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::lteq); }
  | exp_eval GTEQ exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::gteq); }
  | exp_eval EQL exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::eql); }
  | exp_eval NEQL exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::neql); }
  | exp_eval AND exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::and_); }
  | exp_eval OR exp_eval { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::or_); }
  | NOT exp_eval { $$ = std::make_shared<BinOpExprAst>($2, $2, ast_op::not_); }
  
  | DOLLAR STR ASSIGN exp_eval {           // global variable
    slc->add_mvar_name($2);               // add to context tree
    $$ = std::make_shared<BinOpExprAst>(
      std::make_shared<GvarExprAst>(std::string($2), nullptr, VarTypeEnum::scalar_t), 
      $4, ast_op::assign);
  }
  | DOLLAR STR ASSIGN list {           // global variable
    slc->add_mvar_name($2);               // add to context tree

    $$ = std::make_shared<BinOpExprAst>(
      std::make_shared<GvarExprAst>(std::string($2), nullptr, VarTypeEnum::list_t),
      $4, ast_op::assign);

  }

  | STR ASSIGN exp_eval { 
    lvar_list.push_back($1);
    $$ = std::make_shared<BinOpExprAst>(
      std::make_shared<LvarExprAst>(std::string($1)), 
      $3, ast_op::assign);
  }


  | tuple ASSIGN tuple {
    $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::assign);
  }
  | tuple ASSIGN variable {
    $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::assign);
  }
  ;

literals
  : INT { $$ = std::make_shared<OperandExprAst>(Operand($1)); }
  | FLT { $$ = std::make_shared<OperandExprAst>(Operand($1)); }
  | TRUE { $$ = std::make_shared<OperandExprAst>(Operand(true)); }
  | FALSE { $$ = std::make_shared<OperandExprAst>(Operand(false)); }
  | COLON STR { $$ = std::make_shared<OperandExprAst>(Operand(Atom($2))); }
  ;

variable
  : STR { $$ = std::make_shared<LvarExprAst>(std::string($1)); }
  | DOLLAR STR { $$ = std::make_shared<GvarExprAst>(std::string($2)); }
  ;



//--------------------------------------------------- def function 
function
  : DEF STR PAREN_L param_list PAREN_R DO statement_list END { 

    if(slc->interactive) slc->defining_func = true;
    std::shared_ptr<FuncExprAst> func_ptr = 
      std::make_shared<FuncExprAst>
        (std::string($2), $4, $7);  // this adds to ast tree notice param_list, not added in FuncExprAst
    slc->add_function_name($2);
    slc->add_function_params($4); // this adds to the universe context  tree notice param_list
    slc->add_function_lvars(lvar_list);
    slc->add_function_fbody(func_ptr);

    lvar_list.clear();
    $$ = func_ptr;
  }
  ;

//--------------------------------------------------- CASE statement list
case
  // : case exp_eval DO case_match_list END {
  : CASE exp_eval DO case_match_list END {
    std::shared_ptr<CaseExprAst> case_ptr =
      std::make_shared<CaseExprAst>($2, $4);
    $$ = case_ptr;
  }
  ;

case_match_list
  : %empty {
    //std::cout << "empty case match list\n";
    $$ = std::make_shared<ListExprAst>(std::string("empty case match list"));
  }
  | case_match {
    //std::cout << "start case match list\n";
    auto ast_current_context = std::make_shared<ListExprAst>(std::string("case match list"));
    ast_current_context->add($1);
    $$ = ast_current_context;
  }
  | case_match_list case_match {
    if($2 !=nullptr)
      $1->add($2);
    $$ = $1;
  }
  | case_match_list EOS case_match {
    if($3 !=nullptr)
      $1->add($3);
    $$ = $1;
  }
  | case_match_list error EOS case_match { yyerrok; }
  ;

case_match
  : 
  IS literals ARROW_R statement_list {
    //std::cout << "case match s->sl"; $1->print(); std::cout << "\n";
    $$ = std::make_shared<CaseMatchIsExprAst>($2, $4);
  } 
  | IS variable WHEN statement ARROW_R statement_list {
    $$ = std::make_shared<CaseMatchWhenExprAst>($2, $4, $6);
  }
  | IS tuple ARROW_R statement_list {
    $$ = std::make_shared<CaseMatchIsExprAst>($2, $4);
  }
  | IS tuple WHEN statement ARROW_R statement_list {
    $$ = std::make_shared<CaseMatchWhenExprAst>($2, $4, $6);
  }
  | ELSE ARROW_R statement_list {
    $$ = std::make_shared<CaseMatchElseExprAst>($3);
  }
  ;

//--------------------------------------------------- if then else end
if_then_else
  :
  ;
if_then_else
  : IF exp_eval THEN statement_list END {
    auto l = std::make_shared<ListExprAst>("if then end");
    auto y = std::make_shared<OperandExprAst>(Operand(true));
    l->add(std::make_shared<CaseMatchIsExprAst>(y, $4));
    $$ = std::make_shared<CaseExprAst>($2, l);
  }
  | IF exp_eval THEN statement_list ELSE statement_list END {
    auto l = std::make_shared<ListExprAst>("if then else end");
    auto y = std::make_shared<OperandExprAst>(Operand(true));
    l->add(std::make_shared<CaseMatchIsExprAst>(y, $4));
    l->add(std::make_shared<CaseMatchElseExprAst>($6));
    std::shared_ptr<CaseExprAst> case_ptr =
      std::make_shared<CaseExprAst>($2, l);
    $$ = case_ptr;
  }
  ;

//--------------------------------------------------- if then else end
/*
comparison_ops
  : EQL   { $$ = ast_op::eql; }
  | NEQL  {$$ = ast_op::neql; }
  | LT    {$$ = ast_op::lt;   }
  | GT    {$$ = ast_op::gt;   }
  | LTEQ  {$$ = ast_op::lteq; }
  | GTEQ  {$$ = ast_op::gteq; }
  ;
*/

//--------------------------------------------------- while loop 
while_loop
  : WHILE exp_eval DO statement_list END {
    $$ = std::make_shared<WhileExprAst>($2, $4);
  }
  ;

repeat_loop
  : REPEAT statement_list UNTIL exp_eval DONE {
    $$ = std::make_shared<RepeatExprAst>($4, $2);
  }
  ;




//--------------------------------------------------- param list
param_list
  : param  { 
    std::vector<std::string> pl;
    pl.push_back($1); 
    $$ = pl;
  }
  | param_list COMMA param { 
    $1.push_back($3);
    $$ = $1;
  }
  | %empty { 
    std::vector<std::string> pl;
    $$=pl;
  } 
  ;

param
  : STR { //std::cout << "param: " << $1 << "\n"; 
    $$=$1;
  }
  ;

//--------------------------------------------------- EOS end of statement

EOS
  : SEMICOLON
  | EOL
  | COMMENT2
  ;
%%

//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
