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
intvar          ([[:upper:]])
fltvar          ([[:lower:]])
blank           [ \t\r]           

%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}

%%
%{
  yylloc->step();
%}
{integer}   yylval->emplace<long long>(strtoll(YYText(), nullptr, 10)); return SvlmParser::token::INT;
{float}     yylval->emplace<double>(strtod(YYText(), nullptr)); return SvlmParser::token::FLT;
{intvar}    yylval->emplace<char>(YYText()[0]); return SvlmParser::token::INTVAR;
{fltvar}    yylval->emplace<char>(YYText()[0]); return SvlmParser::token::FLTVAR;
{blank}     yylloc->step();
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