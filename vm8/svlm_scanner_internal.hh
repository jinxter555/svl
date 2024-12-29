#include "svlm_parser.hh"
namespace vslast {
class SvlmScanner : public SvlmFlexLexer {
public:
  SvlmScanner(std::istream& arg_yyin, std::ostream& arg_yyout)
    : SvlmFlexLexer(arg_yyin, arg_yyout) {}
  SvlmScanner(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr)
    : SvlmFlexLexer(arg_yyin, arg_yyout) {}
  int lex(SvlmParser::semantic_type *yylval, SvlmParser::location_type *yylloc); 
};
}

