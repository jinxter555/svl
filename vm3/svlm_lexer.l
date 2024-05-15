%{
#include "svlm_parser.hh"
#include "svlm_scanner.hh"
#define YY_DECL int vslast::SvlmScanner::lex(\
  vslast::SvlmParser::semantic_type *yylval,\
  vslast::SvlmParser::location_type *yylloc)
%}

%option c++ interactive noyylineno nodefault outfile="svlm_scanner.cpp" 
%option noyyfree noyyrealloc noyyalloc

dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)
integer         ({dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))
identifier      ([a-zA-Z][a-zA-Z0-9_]*)
blank           [ \t\r]           

%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}

%%
%{
  yylloc->step();
%}
"module"        return SvlmParser::token::MODULE;
"def"        return SvlmParser::token::DEF;
"do"        return SvlmParser::token::DO;
"end"        return SvlmParser::token::END;
{integer}   yylval->emplace<int>(strtoll(YYText(), nullptr, 10)); return SvlmParser::token::INT;
{float}     yylval->emplace<float>(strtod(YYText(), nullptr)); return SvlmParser::token::FLT;
{blank}     yylloc->step();
{identifier}      yylval->emplace<std::string>(std::string(YYText())); return SvlmParser::token::STR;
"+"             return SvlmParser::token::PLUS;
"-"             return SvlmParser::token::MINUS;
"*"             return SvlmParser::token::MULTIPLY;
"/"             return SvlmParser::token::DIVIDE;
"%"             return SvlmParser::token::MODULO;
"!"             return SvlmParser::token::FACTORIAL;
"^"             return SvlmParser::token::EXPONENT;
"("             return SvlmParser::token::LPAREN;
")"             return SvlmParser::token::RPAREN;
"="             return SvlmParser::token::ASSIGN;
"@"             return SvlmParser::token::AT;
"$"             return SvlmParser::token::DOLLAR;
","             return SvlmParser::token::COMMA;
":"             return SvlmParser::token::COLON;
";"             return SvlmParser::token::SEMICOLON;
\n  {
  yylloc->lines(yyleng); 
  yylloc->step(); 
  return SvlmParser::token::EOL;}
<<EOF>>         return SvlmParser::token::YYEOF;
.               /* no action on unmatched input */
%%

/*--- int yyFlexLexer::yylex() { throw std::runtime_error("Bad call to yyFlexLexer::yylex()"); } */

int SvlmFlexLexer::yywrap() { return 1; }

/*
int main() {
  vslast::AstScanner scanner{ std::cin, std::cerr };
  vslast::AstParser parser{ &scanner };
  std::cout.precision(10);
  parser.parse();
}
*/
