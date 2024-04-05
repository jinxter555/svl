%{
#include "asm_parser.hh"
#include "asm_scanner.hh"
#define YY_DECL int vslasm::AsmScanner::lex(vslasm::AsmParser::semantic_type *yylval)
%}

%option c++ interactive noyywrap noyylineno nodefault outfile="asm_scanner.cpp"

dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)
integer         ({dseq}|-{dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))
identifier      ([a-zA-Z][a-zA-Z0-9_]*)
blank           ([ \t\r])
register        ([rR]{integer})





%%

{integer}        { yylval->emplace<long int>(strtoll(YYText(), nullptr, 10)); return AsmParser::token::INT;}
{float}         yylval->emplace<long double>(strtod(YYText(), nullptr)); return AsmParser::token::FLT;
{blank}         {}
{register}      { 
  std::string reg = YYText(); reg[0] = '0';
  yylval->emplace<long int>(strtoll(reg.c_str(), nullptr, 10)); 
  return AsmParser::token::REGISTER; 
}
"fp" { // frame pointer register
  yylval->emplace<long int>(Reg::fp); 
  return AsmParser::token::REGISTER; 
}
"uri"    return AsmParser::token::URI;
"app"    return AsmParser::token::APP;
"api"    return AsmParser::token::API;
"module"    return AsmParser::token::MODULE;
"text"    return AsmParser::token::TEXT;
"mvar"    return AsmParser::token::MVAR;
"function"    return AsmParser::token::FUNCTION;
"label"    return AsmParser::token::LABEL;
"lvar"    return AsmParser::token::LVAR;
"larg"    return AsmParser::token::LARG; // local argument
"call"    return AsmParser::token::CALL;
"branch"    return AsmParser::token::BRANCH;
"%store_l"       return AsmParser::token::STORE_L;
"%load_l"        return AsmParser::token::LOAD_L;
"%store_g"       return AsmParser::token::STORE_G;
"%load_g"        return AsmParser::token::LOAD_G;
"mov_mf_adr"        return AsmParser::token::MOV_MF_ADR;
"mov_mv_adr"        return AsmParser::token::MOV_MV_ADR;
"mov_l_adr"        return AsmParser::token::MOV_L_ADR;
\"(\\(.|\n)|[^\\"\n])*\"    yylval->emplace<std::string>(std::string(YYText())); return AsmParser::token::VSLSTRING;
{identifier}      yylval->emplace<std::string>(std::string(YYText())); return AsmParser::token::STR;
"@"             return AsmParser::token::AT;
"+"             return AsmParser::token::PLUS;
"-"             return AsmParser::token::MINUS;
"*"             return AsmParser::token::MULTIPLY;
"/"             return AsmParser::token::DIVIDE;
"%"             return AsmParser::token::MODULO;
"!"             return AsmParser::token::FACTORIAL;
"^"             return AsmParser::token::EXPONENT;
"("             return AsmParser::token::LPAREN;
")"             return AsmParser::token::RPAREN;
"["             return AsmParser::token::LSBRACKET;
"]"             return AsmParser::token::RSBRACKET;
"="             return AsmParser::token::ASSIGN;
","             return AsmParser::token::COMMA;
"."             return AsmParser::token::DOT;
":"             return AsmParser::token::COLON;
^#.*\n          return AsmParser::token::COMMENT1; // ignore comment
#.*\n          return AsmParser::token::COMMENT2; // ignore comment
^[ \t\r]*\n   return AsmParser::token::EMPTYLINE; // ignore empty line
\n              return AsmParser::token::EOL;
<<EOF>>         return AsmParser::token::YYEOF;
.               /* no action on unmatched input */

%%


int AsmFlexLexer::yywrap() { return 1; }
