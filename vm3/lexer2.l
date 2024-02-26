%{
#include "Parser2.hh"
#include "Scanner2.hh"
#define YY_DECL int vslasm::Scanner::lex(vslasm::Parser::semantic_type *yylval)
//#define YY_DECL int vslasm::Scanner::lex(Parser::semantic_type *yylval,  Parser::location_type* loc)
%}

%option c++ interactive noyywrap noyylineno nodefault outfile="Scanner2.cpp"

dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)
integer         ({dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))
identifier      ([a-zA-Z][a-zA-Z0-9_]*)
blank           ([ \t\r])
register        ([rR]{integer})


%%

{integer}        { yylval->emplace<long int>(strtoll(YYText(), nullptr, 10)); return Parser::token::INT;}
{float}         yylval->emplace<long double>(strtod(YYText(), nullptr)); return Parser::token::FLT;
{blank}         {}
{register}      { 
  std::string reg = YYText(); reg[0] = '0';
  yylval->emplace<long int>(strtoll(reg.c_str(), nullptr, 10)); 
  return Parser::token::REGISTER; 
}
"app"    return Parser::token::APP;
"api"    return Parser::token::API;
"module"    return Parser::token::MODULE;
"mvar"    return Parser::token::MVAR;
"function"    return Parser::token::FUNCTION;
"label"    return Parser::token::LABEL;
"lvar"    return Parser::token::LVAR;
"call"    return Parser::token::CALL;
{identifier}    yylval->emplace<std::string>(std::string(YYText())); return Parser::token::STR;
"+"             return Parser::token::PLUS;
"-"             return Parser::token::MINUS;
"*"             return Parser::token::MULTIPLY;
"/"             return Parser::token::DIVIDE;
"%"             return Parser::token::MODULO;
"!"             return Parser::token::FACTORIAL;
"^"             return Parser::token::EXPONENT;
"("             return Parser::token::LPAREN;
")"             return Parser::token::RPAREN;
"="             return Parser::token::ASSIGN;
","             return Parser::token::COMMA;
"."             return Parser::token::DOT;
":"             return Parser::token::COLON;
^#.*\n              {} // comments
^[ \t\r]*\n              {} // ignore empty lines
\n              return Parser::token::EOL;
<<EOF>>         return Parser::token::YYEOF;
.               /* no action on unmatched input */

%%