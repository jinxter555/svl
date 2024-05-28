%{
#include <iostream>
#include <string>
#include <cmath>
#include "lang.hh"
%}

%require "3.8.1"
%language "C++"
%defines "svlm_parser.hh"
%output "svlm_parser.cpp"

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
%token              MODULE DEF DO END AST_RETURN PRINT CASE
%token              PAREN_L PAREN_R CUR_L CUR_R AT DOLLAR COLON COMMA SEMICOLON ARROW_R ARROW_L
%token <std::string> IDENT_STR STR DQSTR
%token <int>  INT
%token <float>     FLT
 
%nterm EOS // end of statement
%nterm <std::vector<std::string>> param_list 
%nterm <std::string> param
%nterm comments

%nonassoc           ASSIGN
%left               EQL NEQL GT LT GTEQ LTEQ AND OR 
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         NOT
%right              EXPONENT

%type <std::shared_ptr<ExprAst>>  exp exp_num statement arg print_exp module function caller tuple comments  case
%type <std::shared_ptr<ListExprAst>>  statement_list  arg_list
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
    if($3!=nullptr) $1->add($3);
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
  | caller
  | case
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
  : exp
  ;


//--------------------------------------------------- caller/callee 
caller
  : STR PAREN_L arg_list PAREN_R {
    std::shared_ptr<CallExprAst> caller = std::make_shared<CallExprAst>($1, $3); 
    $$ = caller;
  }


//--------------------------------------------------- exp eval
exp
  : exp_num {$$ = $1; }
  | AST_RETURN { $$ = std::make_shared<DisContExprAst>(std::string("return")); }
  ;

print_exp
  : PRINT exp { $$ = std::make_shared<PrintExprAst>($2); }
  | PRINT DQSTR { $$ = std::make_shared<PrintExprAst> (std::make_shared<IdentExprAst>($2)); }
  ;

//--------------------------------------------------- exp var eval
tuple
  : CUR_L arg_list CUR_R { $$ = std::make_shared<TupleExprAst>($2); }

exp_num
  : INT { $$ = std::make_shared<NumberExprAst>(Number($1)); }
  | FLT { $$ = std::make_shared<NumberExprAst>(Number($1)); }
  | tuple { $$ = $1; }
  | COLON STR { $$ = std::make_shared<AtomExprAst>(Atom($2)); }

  | exp_num MULTIPLY exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::mul); }
  | exp_num DIVIDE exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::div); }
  | exp_num PLUS exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::plus); }
  | exp_num MINUS exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::minus); }
  | exp_num GT exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::gt); }
  | exp_num LT exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::lt); }
  | exp_num LTEQ exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::lteq); }
  | exp_num GTEQ exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::gteq); }
  | exp_num EQL exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::eql); }
  | exp_num NEQL exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::neql); }
  | exp_num AND exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::and_); }
  | exp_num OR exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::or_); }
  | NOT exp_num { $$ = std::make_shared<BinOpExprAst>($2, $2, ast_op::not_); }

  | PAREN_L exp_num PAREN_R        { $$ = $2; }
  | DOLLAR STR { $$ = std::make_shared<GvarExprAst>(std::string($2)); }
  | DOLLAR STR ASSIGN exp_num {           // global variable
    slc->add_mvar_name($2);               // add to context tree
    $$ = std::make_shared<BinOpExprAst>(
      std::make_shared<GvarExprAst>(std::string($2)), 
      $4, ast_op::assign);
  }

  | STR { $$ = std::make_shared<LvarExprAst>(std::string($1)); }
  | STR ASSIGN exp_num { 
    lvar_list.push_back($1);
    $$ = std::make_shared<BinOpExprAst>(
      std::make_shared<LvarExprAst>(std::string($1)), 
      $3, ast_op::assign);
  }
  | tuple ASSIGN tuple {
    $$ = std::make_shared<BinOpExprAst>($1, $3, ast_op::assign);
  }
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

//--------------------------------------------------- case statement list
case
  : CASE statement DO END {
    std::shared_ptr<CaseExprAst> case_ptr =
      std::make_shared<CaseExprAst>($2);
    $$ = case_ptr;
  }
  ;

case_match
  : statement ARROW_R statement_list {

  } 
  | %empty {
    $$ = std::make_shared<CaseMatchExprAst>(nullptr, ast_op::eql );

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
