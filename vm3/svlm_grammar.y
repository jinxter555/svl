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
%token              MODULE DEF DO END AST_RETURN PRINT
%token              LPAREN RPAREN AT DOLLAR COLON COMMA SEMICOLON
%token <std::string> IDENT_STR STR DQSTR
%token <int>  INT
%token <float>     FLT
 
%nterm <ast_op>  math_bin_op
%nterm EOS // end of statement
%nterm <std::vector<std::string>> param_list 
%nterm <std::string> param
%nterm comments

%nonassoc           ASSIGN
%left               EQL GT LT GTEQ LTEQ
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT

%type <std::shared_ptr<ExprAst>>  exp exp_num statement arg print_exp def_module def_function def_caller comments 
%type <std::shared_ptr<ListExprAst>>  statement_list  arg_list

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
  | def_module
  | def_function
  | def_caller
  | print_exp
  | comments {$$ = nullptr; }
  ;

//--------------------------------------------------- module decl
def_module
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
def_caller
  : STR LPAREN arg_list RPAREN {
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
exp_num
  : INT { $$ = std::make_shared<NumberExprAst>(Number($1)); }
  | FLT { $$ = std::make_shared<NumberExprAst>(Number($1)); }
  | COLON STR { $$ = std::make_shared<AtomExprAst>($2); }
  | exp_num math_bin_op exp_num { $$ = std::make_shared<BinOpExprAst>($1, $3, $2); }
  | LPAREN exp_num RPAREN        { $$ = $2; }

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
  ;

math_bin_op
  : PLUS      {$$ = ast_op::plus;}
  | MINUS     {$$ = ast_op::minus;}
  | MULTIPLY  {$$ = ast_op::mul;}
  | DIVIDE    {$$ = ast_op::div;}
  | GT    {$$ = ast_op::gt;}
  | LT    {$$ = ast_op::lt;}
  | GTEQ    {$$ = ast_op::gteq;}
  | LTEQ    {$$ = ast_op::lteq;}
  | EQL    {$$ = ast_op::eql;}
  ;

//--------------------------------------------------- def function 
def_function
  : DEF STR LPAREN param_list RPAREN DO statement_list END { 

    if(slc->interactive) slc->defining_func = true;
    std::shared_ptr<FuncExprAst> func_ptr = 
      std::make_shared<FuncExprAst>
        (std::string($2), $4, $7); 
    slc->add_function_name($2);
    slc->add_function_params($4);
    slc->add_function_lvars(lvar_list);
    slc->add_function_fbody(func_ptr);

    lvar_list.clear();
    $$ = func_ptr;
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
