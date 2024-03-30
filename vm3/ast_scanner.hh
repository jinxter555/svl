#pragma once
#undef yyFlexLexer
#define yyFlexLexer AstFlexLexer
#include <FlexLexer.h>
#include "ast_scanner_internal.hh"
