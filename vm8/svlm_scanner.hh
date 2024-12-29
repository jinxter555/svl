#pragma once
#undef yyFlexLexer
#define yyFlexLexer SvlmFlexLexer
#include <FlexLexer.h>
#include "svlm_scanner_internal.hh"
