%{
#include <iostream>
#include <string>
#include <cmath>
%}

%require "3.7.4"
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

//SvlmLangContext slc; 
SvlmLang* svlm_lang;

}


%token              EOL LPAREN RPAREN AT MODULE DOLLAR COLON
%token <std::string> IDENT_STR
%token <int>  INT
%token <float>     FLT
 
%nterm <char>  math_bin_op

%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT

%type <std::shared_ptr<ExprAst>>  iexp


%%
start
  : lines
  ;

lines
  : %empty
  | lines line
  ;

line
  : EOL { std::cerr << "Read an empty line\n"; }
  | iexp EOL { 
    svlm_lang->ast_current_context->add($1);
    $1->print(); 
    //std::cout <<  "ieval: " << std::any_cast<int>($1->evaluate()) << "\n\n";
  }
  | MODULE IDENT_STR EOL { 
    svlm_lang = slc->svlm_lang;
    slc->add_module_name($2); 
    svlm_lang->ast_current_context->add( 
      std::make_shared<DeclExprAst>(
        std::make_shared<IdentExprAst>($2), 
        DeclOpcodeAST::MODULE)
    );
  }

  | error EOL { yyerrok; }
  ;

iexp
  : INT { $$ = std::make_shared<NumberExprAst>($1); }
  | iexp math_bin_op iexp { $$ = std::make_shared<BinOpExprAst>($1, $3, BinOpcodeAST::INT_OP_INT, $2); }
  | DOLLAR IDENT_STR { $$ = std::make_shared<GvarExprAst>(std::string($2)); }
  | DOLLAR IDENT_STR ASSIGN iexp { 
    slc->add_mvar_name($2);  // add to context tree
      $$ = std::make_shared<BinOpExprAst>(
      std::make_shared<GvarExprAst>(std::string($2)), 
      $4, 
      BinOpcodeAST::ASSIGN_INT_G, '='
      );
    // std::cout << "var " << $1 << " " << $3->evaluate();
    }

  /*
  | iexp PLUS     iexp { $$ = std::make_shared<BinOpExprAst>($1, $3, BinOpcodeAST::INT_OP_INT, '+'); }
  | iexp MINUS    iexp { $$ = std::make_shared<BinOpExprAst>($1, $3, BinOpcodeAST::INT_OP_INT, '-'); }
  | iexp MULTIPLY iexp { $$ = std::make_shared<BinOpExprAst>($1, $3, BinOpcodeAST::INT_OP_INT, '*'); }
  | iexp DIVIDE   iexp { $$ = std::make_shared<BinOpExprAst>($1, $3, BinOpcodeAST::INT_OP_INT, '/'); }
  */
  ;

math_bin_op
  : PLUS      {$$ = '+';}
  | MINUS     {$$ = '-';}
  | MULTIPLY  {$$ = '*';}
  | DIVIDE    {$$ = '/';}
  ;

%%

void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
