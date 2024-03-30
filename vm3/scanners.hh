#pragma once

#undef yyFlexLexer
#define yyFlexLexer AstFlexLexer
#include <FlexLexer.h>
#include "ast_scanner_internal.hh"

#undef yyFlexLexer
#define yyFlexLexer AsmFlexLexer
#include <FlexLexer.h>
#include "asm_scanner_internal.hh"
