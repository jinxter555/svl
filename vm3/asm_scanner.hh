#pragma once
#undef yyFlexLexer
#define yyFlexLexer AsmFlexLexer
#include <FlexLexer.h>
#include "asm_scanner_internal.hh"