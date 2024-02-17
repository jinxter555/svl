%{
#include "Parser2.hpp"
#include "Scanner2.hpp"
#define YY_DECL int vslasm::Scanner::lex(vslasm::Parser::semantic_type *yylval)
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
 
{integer}       yylval->emplace<long long>(strtoll(YYText(), nullptr, 10)); return Parser::token::INT;
{float}         yylval->emplace<double>(strtod(YYText(), nullptr)); return Parser::token::FLT;
{blank}         {}

{register}      { yylval->emplace<std::string>(std::string(YYText())); return Parser::token::REGISTER;
}
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
\n              return Parser::token::EOL;
<<EOF>>         return Parser::token::YYEOF;
.               /* no action on unmatched input */

%%