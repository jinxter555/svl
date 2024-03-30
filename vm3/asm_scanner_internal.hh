#include "asm_parser.hh"
namespace vslasm {
class AsmScanner : public AsmFlexLexer {
public:
  AsmScanner(std::istream& arg_yyin, std::ostream& arg_yyout)
    : AsmFlexLexer(arg_yyin, arg_yyout) {}
  AsmScanner(std::istream* arg_yyin=nullptr, std::ostream* arg_yyout=nullptr)
    : AsmFlexLexer(arg_yyin, arg_yyout) {}
  int lex(AsmParser::semantic_type *yylval);
}; 
}