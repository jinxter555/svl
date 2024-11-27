%{
#include "svlm_parser.hh"
#include "svlm_scanner.hh"
#include "my_helpers.hh"
#define YY_DECL int vslast::SvlmScanner::lex(\
  vslast::SvlmParser::semantic_type *yylval,\
  vslast::SvlmParser::location_type *yylloc)
%}

%option c++ interactive noyylineno nodefault outfile="svlm_scanner.cc" 


dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)
integer         ({dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))
identifier      ([a-zA-Z][a-zA-Z0-9_]*)
blank           [ \t\r]           
dqstring        \"([^"\\]|\\[^\n\\])*\"  


%{
#define YY_USER_ACTION yylloc->columns(yyleng);
std::string raw_to_escaped_string(const std::string& raw_string);
//%option noyyfree noyyrealloc noyyalloc
%}

%%
%{
  yylloc->step();
%}
"module"        return SvlmParser::token::MODULE;
"def"        return SvlmParser::token::DEF;
"do"        return SvlmParser::token::DO;
"done"        return SvlmParser::token::DONE;
"end"        return SvlmParser::token::END;
"flow"        return SvlmParser::token::FLOW;
"case"        return SvlmParser::token::CASE;
"when"        return SvlmParser::token::WHEN;
"where"        return SvlmParser::token::WHERE;
"is"        return SvlmParser::token::IS;
"if"        return SvlmParser::token::IF;
"then"        return SvlmParser::token::THEN;
"else"        return SvlmParser::token::ELSE;
"while"        return SvlmParser::token::WHILE;
"repeat"        return SvlmParser::token::REPEAT;
"until"        return SvlmParser::token::UNTIL;
"return"        return SvlmParser::token::AST_RETURN;
"break"        return SvlmParser::token::AST_BREAK;
"default"        return SvlmParser::token::AST_DEFAULT;
"print"        return SvlmParser::token::PRINT;
"not"        return SvlmParser::token::NOT;
"true"        return SvlmParser::token::TRUE;
"false"        return SvlmParser::token::FALSE;
{integer}   yylval->emplace<s_integer>(strtoll(YYText(), nullptr, 10)); return SvlmParser::token::INT;
{float}     yylval->emplace<s_float>(strtod(YYText(), nullptr)); return SvlmParser::token::FLT;
{blank}     yylloc->step();
{identifier}      yylval->emplace<std::string>(std::string(YYText())); return SvlmParser::token::STR;

"=="             return SvlmParser::token::EQL;
"!="             return SvlmParser::token::NEQL;
">="             return SvlmParser::token::GTEQ;
"<="             return SvlmParser::token::LTEQ;
"->"             return SvlmParser::token::ARROW_R;
"<-"             return SvlmParser::token::ARROW_L;
"&&"             return SvlmParser::token::AND;
"||"             return SvlmParser::token::OR;

"<"             return SvlmParser::token::LT;
">"             return SvlmParser::token::GT;
"+"             return SvlmParser::token::PLUS;
"-"             return SvlmParser::token::MINUS;
"*"             return SvlmParser::token::MULTIPLY;
"/"             return SvlmParser::token::DIVIDE;
"!"             return SvlmParser::token::NOT;
"^"             return SvlmParser::token::EXPONENT;
"("             return SvlmParser::token::PAREN_L;
")"             return SvlmParser::token::PAREN_R;
"{"             return SvlmParser::token::CUR_L;
"}"             return SvlmParser::token::CUR_R;
"["             return SvlmParser::token::SQBRK_L;
"]"             return SvlmParser::token::SQBRK_R;
"@"             return SvlmParser::token::AT;
"$"             return SvlmParser::token::DOLLAR;
"."             return SvlmParser::token::DOT;
","             return SvlmParser::token::COMMA;
":"             return SvlmParser::token::COLON;
";"             return SvlmParser::token::SEMICOLON;
"="             return SvlmParser::token::ASSIGN;
"%"             return SvlmParser::token::PERCENT;

{dqstring}        { 
  std::string result = raw_to_escaped_string(YYText()); 
  result.erase(0, 1); result.erase(result.size() - 1);
  yylval->emplace<std::string>(result);
  return SvlmParser::token::DQSTR;
  }



\n  {
  yylloc->lines(yyleng); 
  yylloc->step(); 
  return SvlmParser::token::EOL;}

^#.*          {
//  yylloc->lines(yyleng); 
  yylloc->step(); 
  return SvlmParser::token::COMMENT1; // ignore comment
}

#.*          {
 // yylloc->lines(yyleng); 
  yylloc->step(); 
  return SvlmParser::token::COMMENT2; // ignore comment
}



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
