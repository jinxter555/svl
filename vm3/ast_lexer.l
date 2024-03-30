%{
#include "ast_parser.hh"
#include "ast_scanner.hh"
#define YY_DECL int vslast::AstScanner::lex(\
  vslast::AstParser::semantic_type *yylval,\
  vslast::AstParser::location_type *yylloc)
%}

%option c++ interactive noyylineno nodefault outfile="ast_scanner.cpp" 
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
{integer}   yylval->emplace<long long>(strtoll(YYText(), nullptr, 10)); return AstParser::token::INT;
{float}     yylval->emplace<double>(strtod(YYText(), nullptr)); return AstParser::token::FLT;
{intvar}    yylval->emplace<char>(YYText()[0]); return AstParser::token::INTVAR;
{fltvar}    yylval->emplace<char>(YYText()[0]); return AstParser::token::FLTVAR;
{blank}     yylloc->step();
"+"             return AstParser::token::PLUS;
"-"             return AstParser::token::MINUS;
"*"             return AstParser::token::MULTIPLY;
"/"             return AstParser::token::DIVIDE;
"%"             return AstParser::token::MODULO;
"!"             return AstParser::token::FACTORIAL;
"^"             return AstParser::token::EXPONENT;
"("             return AstParser::token::LPAREN;
")"             return AstParser::token::RPAREN;
"="             return AstParser::token::ASSIGN;
\n  {
  yylloc->lines(yyleng); 
  yylloc->step(); 
  return AstParser::token::EOL;}
<<EOF>>         return AstParser::token::YYEOF;
.               /* no action on unmatched input */
%%

int yyFlexLexer::yylex() {
  throw std::runtime_error("Bad call to yyFlexLexer::yylex()");
}
int AstFlexLexer::yywrap() { return 1; }

/*
int main() {
  vslast::AstScanner scanner{ std::cin, std::cerr };
  vslast::AstParser parser{ &scanner };
  std::cout.precision(10);
  parser.parse();
}
*/