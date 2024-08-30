// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "svlm_grammar.y"

#include <iostream>
#include <string>
#include <cmath>
#include "lang.hh"

#line 48 "svlm_parser.cc"


#include "svlm_parser.hh"


// Unqualified %code blocks.
#line 31 "svlm_grammar.y"

#include "svlm_scanner.hh"
#include "svlm_lang.hh"
#define yylex(x,y) scanner->lex(x,y)


SvlmLang* svlm_lang;
std::vector<std::string> lvar_list;


#line 66 "svlm_parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "svlm_grammar.y"
namespace vslast {
#line 159 "svlm_parser.cc"

  /// Build a parser object.
  SvlmParser::SvlmParser (SvlmScanner* scanner_yyarg, SvlmLangContext* slc_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      slc (slc_yyarg)
  {}

  SvlmParser::~SvlmParser ()
  {}

  SvlmParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  SvlmParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_FLT: // FLT
        value.copy< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_match: // case_match
        value.copy< std::shared_ptr<CaseMatchExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
      case symbol_kind::S_if_then_else: // if_then_else
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
        value.copy< std::shared_ptr<ExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_case_match_list: // case_match_list
        value.copy< std::shared_ptr<ListExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_param: // param
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  SvlmParser::symbol_kind_type
  SvlmParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  SvlmParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  SvlmParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_FLT: // FLT
        value.move< float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_case_match: // case_match
        value.move< std::shared_ptr<CaseMatchExprAst> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
      case symbol_kind::S_if_then_else: // if_then_else
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
        value.move< std::shared_ptr<ExprAst> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_case_match_list: // case_match_list
        value.move< std::shared_ptr<ListExprAst> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_param: // param
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<std::string> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  SvlmParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  SvlmParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  SvlmParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  SvlmParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  SvlmParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  SvlmParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  SvlmParser::symbol_kind_type
  SvlmParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  SvlmParser::symbol_kind_type
  SvlmParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  SvlmParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  SvlmParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  SvlmParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  SvlmParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  SvlmParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  SvlmParser::symbol_kind_type
  SvlmParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  SvlmParser::stack_symbol_type::stack_symbol_type ()
  {}

  SvlmParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_FLT: // FLT
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_match: // case_match
        value.YY_MOVE_OR_COPY< std::shared_ptr<CaseMatchExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
      case symbol_kind::S_if_then_else: // if_then_else
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
        value.YY_MOVE_OR_COPY< std::shared_ptr<ExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_case_match_list: // case_match_list
        value.YY_MOVE_OR_COPY< std::shared_ptr<ListExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  SvlmParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_FLT: // FLT
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_match: // case_match
        value.move< std::shared_ptr<CaseMatchExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
      case symbol_kind::S_if_then_else: // if_then_else
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
        value.move< std::shared_ptr<ExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_case_match_list: // case_match_list
        value.move< std::shared_ptr<ListExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_param: // param
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  SvlmParser::stack_symbol_type&
  SvlmParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_FLT: // FLT
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_case_match: // case_match
        value.copy< std::shared_ptr<CaseMatchExprAst> > (that.value);
        break;

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
      case symbol_kind::S_if_then_else: // if_then_else
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
        value.copy< std::shared_ptr<ExprAst> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_case_match_list: // case_match_list
        value.copy< std::shared_ptr<ListExprAst> > (that.value);
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_param: // param
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  SvlmParser::stack_symbol_type&
  SvlmParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_FLT: // FLT
        value.move< float > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< int > (that.value);
        break;

      case symbol_kind::S_case_match: // case_match
        value.move< std::shared_ptr<CaseMatchExprAst> > (that.value);
        break;

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
      case symbol_kind::S_if_then_else: // if_then_else
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
        value.move< std::shared_ptr<ExprAst> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_case_match_list: // case_match_list
        value.move< std::shared_ptr<ListExprAst> > (that.value);
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_param: // param
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  SvlmParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  SvlmParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  SvlmParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  SvlmParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  SvlmParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SvlmParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SvlmParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SvlmParser::debug_level_type
  SvlmParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SvlmParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  SvlmParser::state_type
  SvlmParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  SvlmParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  SvlmParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SvlmParser::operator() ()
  {
    return parse ();
  }

  int
  SvlmParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_FLT: // FLT
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_case_match: // case_match
        yylhs.value.emplace< std::shared_ptr<CaseMatchExprAst> > ();
        break;

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
      case symbol_kind::S_if_then_else: // if_then_else
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
        yylhs.value.emplace< std::shared_ptr<ExprAst> > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_case_match_list: // case_match_list
        yylhs.value.emplace< std::shared_ptr<ListExprAst> > ();
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_param: // param
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program_start: statement_list
#line 76 "svlm_grammar.y"
                    { auto astcode = slc->svlm_lang->ast_current_contexts.top(); astcode->add(yystack_[0].value.as < std::shared_ptr<ListExprAst> > ()); }
#line 985 "svlm_parser.cc"
    break;

  case 3: // comments: COMMENT1
#line 80 "svlm_grammar.y"
             {yylhs.value.as < std::shared_ptr<ExprAst> > ()=nullptr;}
#line 991 "svlm_parser.cc"
    break;

  case 4: // statement_list: statement_list EOS statement
#line 84 "svlm_grammar.y"
                                 {
    if(yystack_[2].value.as < std::shared_ptr<ListExprAst> > ()==nullptr) {std::cerr << "statement syntax error"; yyerrok; }
    if(yystack_[2].value.as < std::shared_ptr<ListExprAst> > ()!=nullptr && yystack_[0].value.as < std::shared_ptr<ExprAst> > ()!=nullptr) yystack_[2].value.as < std::shared_ptr<ListExprAst> > ()->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = yystack_[2].value.as < std::shared_ptr<ListExprAst> > ();
  }
#line 1001 "svlm_parser.cc"
    break;

  case 5: // statement_list: statement
#line 89 "svlm_grammar.y"
               {
    auto ast_current_context = std::make_shared<ListExprAst>(std::string("statement code here"));
    ast_current_context->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = ast_current_context;
  }
#line 1011 "svlm_parser.cc"
    break;

  case 6: // statement_list: statement_list error EOS statement
#line 94 "svlm_grammar.y"
                                       { yyerrok; }
#line 1017 "svlm_parser.cc"
    break;

  case 7: // statement_list: %empty
#line 95 "svlm_grammar.y"
           { yylhs.value.as < std::shared_ptr<ListExprAst> > () = std::make_shared<ListExprAst>(std::string("empty statement code")); }
#line 1023 "svlm_parser.cc"
    break;

  case 8: // statement: %empty
#line 99 "svlm_grammar.y"
           {yylhs.value.as < std::shared_ptr<ExprAst> > ()=nullptr;}
#line 1029 "svlm_parser.cc"
    break;

  case 9: // statement: exp
#line 100 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1035 "svlm_parser.cc"
    break;

  case 10: // statement: module
#line 101 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1041 "svlm_parser.cc"
    break;

  case 11: // statement: function
#line 102 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1047 "svlm_parser.cc"
    break;

  case 12: // statement: case
#line 103 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1053 "svlm_parser.cc"
    break;

  case 13: // statement: while_loop
#line 104 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1059 "svlm_parser.cc"
    break;

  case 14: // statement: if_then_else
#line 105 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1065 "svlm_parser.cc"
    break;

  case 15: // statement: repeat_loop
#line 106 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1071 "svlm_parser.cc"
    break;

  case 16: // statement: print_exp
#line 107 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1077 "svlm_parser.cc"
    break;

  case 17: // statement: comments
#line 108 "svlm_grammar.y"
             {yylhs.value.as < std::shared_ptr<ExprAst> > () = nullptr; }
#line 1083 "svlm_parser.cc"
    break;

  case 18: // module: MODULE STR
#line 113 "svlm_grammar.y"
               { 
    svlm_lang = slc->svlm_lang;
    slc->add_module_name(yystack_[0].value.as < std::string > ()); 
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<DeclExprAst>( std::make_shared<IdentExprAst>(yystack_[0].value.as < std::string > ()), DeclOpcodeAST::MODULE);
  }
#line 1093 "svlm_parser.cc"
    break;

  case 19: // arg_list: arg_list COMMA arg
#line 122 "svlm_grammar.y"
                       {
    yystack_[2].value.as < std::shared_ptr<ListExprAst> > ()->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = yystack_[2].value.as < std::shared_ptr<ListExprAst> > ();
  }
#line 1102 "svlm_parser.cc"
    break;

  case 20: // arg_list: arg
#line 126 "svlm_grammar.y"
        {
    auto ast_current_context = std::make_shared<ListExprAst>("argument block");
    ast_current_context->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = ast_current_context;
  }
#line 1112 "svlm_parser.cc"
    break;

  case 21: // arg_list: %empty
#line 131 "svlm_grammar.y"
           {yylhs.value.as < std::shared_ptr<ListExprAst> > () = std::make_shared<ListExprAst>("empty args");}
#line 1118 "svlm_parser.cc"
    break;

  case 22: // arg: exp
#line 135 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1124 "svlm_parser.cc"
    break;

  case 23: // caller: STR PAREN_L arg_list PAREN_R
#line 141 "svlm_grammar.y"
                                 {
    std::shared_ptr<CallExprAst> caller = std::make_shared<CallExprAst>(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<ListExprAst> > ()); 
    yylhs.value.as < std::shared_ptr<ExprAst> > () = caller;
  }
#line 1133 "svlm_parser.cc"
    break;

  case 24: // exp: exp_eval
#line 149 "svlm_grammar.y"
             {yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1139 "svlm_parser.cc"
    break;

  case 25: // exp: AST_RETURN
#line 150 "svlm_grammar.y"
               { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<ControlFlowExprAst>(ControlFlow::ast_return); }
#line 1145 "svlm_parser.cc"
    break;

  case 26: // exp: AST_RETURN exp_eval
#line 151 "svlm_grammar.y"
                        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<ControlFlowExprAst>(ControlFlow::ast_return, yystack_[0].value.as < std::shared_ptr<ExprAst> > ()); }
#line 1151 "svlm_parser.cc"
    break;

  case 27: // exp: AST_BREAK
#line 152 "svlm_grammar.y"
              { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<ControlFlowExprAst>(ControlFlow::ast_break); }
#line 1157 "svlm_parser.cc"
    break;

  case 28: // print_exp: PRINT exp
#line 156 "svlm_grammar.y"
              { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<PrintExprAst>(yystack_[0].value.as < std::shared_ptr<ExprAst> > ()); }
#line 1163 "svlm_parser.cc"
    break;

  case 29: // print_exp: PRINT DQSTR
#line 157 "svlm_grammar.y"
                { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<PrintExprAst> (std::make_shared<IdentExprAst>(yystack_[0].value.as < std::string > ())); }
#line 1169 "svlm_parser.cc"
    break;

  case 30: // tuple: CUR_L arg_list CUR_R
#line 162 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<TupleExprAst>(yystack_[1].value.as < std::shared_ptr<ListExprAst> > ()); }
#line 1175 "svlm_parser.cc"
    break;

  case 31: // exp_eval: literals
#line 165 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1181 "svlm_parser.cc"
    break;

  case 32: // exp_eval: variable
#line 166 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1187 "svlm_parser.cc"
    break;

  case 33: // exp_eval: tuple
#line 167 "svlm_grammar.y"
          { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1193 "svlm_parser.cc"
    break;

  case 34: // exp_eval: PAREN_L exp_eval PAREN_R
#line 168 "svlm_grammar.y"
                                    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[1].value.as < std::shared_ptr<ExprAst> > (); }
#line 1199 "svlm_parser.cc"
    break;

  case 35: // exp_eval: caller
#line 169 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1205 "svlm_parser.cc"
    break;

  case 36: // exp_eval: exp_eval MULTIPLY exp_eval
#line 170 "svlm_grammar.y"
                               { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::mul); }
#line 1211 "svlm_parser.cc"
    break;

  case 37: // exp_eval: exp_eval DIVIDE exp_eval
#line 171 "svlm_grammar.y"
                             { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::div); }
#line 1217 "svlm_parser.cc"
    break;

  case 38: // exp_eval: exp_eval PLUS exp_eval
#line 172 "svlm_grammar.y"
                           { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::plus); }
#line 1223 "svlm_parser.cc"
    break;

  case 39: // exp_eval: exp_eval MINUS exp_eval
#line 173 "svlm_grammar.y"
                            { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::minus); }
#line 1229 "svlm_parser.cc"
    break;

  case 40: // exp_eval: exp_eval GT exp_eval
#line 174 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::gt); }
#line 1235 "svlm_parser.cc"
    break;

  case 41: // exp_eval: exp_eval LT exp_eval
#line 175 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::lt); }
#line 1241 "svlm_parser.cc"
    break;

  case 42: // exp_eval: exp_eval LTEQ exp_eval
#line 176 "svlm_grammar.y"
                           { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::lteq); }
#line 1247 "svlm_parser.cc"
    break;

  case 43: // exp_eval: exp_eval GTEQ exp_eval
#line 177 "svlm_grammar.y"
                           { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::gteq); }
#line 1253 "svlm_parser.cc"
    break;

  case 44: // exp_eval: exp_eval EQL exp_eval
#line 178 "svlm_grammar.y"
                          { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::eql); }
#line 1259 "svlm_parser.cc"
    break;

  case 45: // exp_eval: exp_eval NEQL exp_eval
#line 179 "svlm_grammar.y"
                           { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::neql); }
#line 1265 "svlm_parser.cc"
    break;

  case 46: // exp_eval: exp_eval AND exp_eval
#line 180 "svlm_grammar.y"
                          { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::and_); }
#line 1271 "svlm_parser.cc"
    break;

  case 47: // exp_eval: exp_eval OR exp_eval
#line 181 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::or_); }
#line 1277 "svlm_parser.cc"
    break;

  case 48: // exp_eval: NOT exp_eval
#line 182 "svlm_grammar.y"
                 { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[0].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::not_); }
#line 1283 "svlm_parser.cc"
    break;

  case 49: // exp_eval: DOLLAR STR ASSIGN exp_eval
#line 183 "svlm_grammar.y"
                               {           // global variable
    slc->add_mvar_name(yystack_[2].value.as < std::string > ());               // add to context tree
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(
      std::make_shared<GvarExprAst>(std::string(yystack_[2].value.as < std::string > ())), 
      yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::assign);
  }
#line 1294 "svlm_parser.cc"
    break;

  case 50: // exp_eval: STR ASSIGN exp_eval
#line 190 "svlm_grammar.y"
                        { 
    lvar_list.push_back(yystack_[2].value.as < std::string > ());
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(
      std::make_shared<LvarExprAst>(std::string(yystack_[2].value.as < std::string > ())), 
      yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::assign);
  }
#line 1305 "svlm_parser.cc"
    break;

  case 51: // exp_eval: tuple ASSIGN tuple
#line 196 "svlm_grammar.y"
                       {
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::assign);
  }
#line 1313 "svlm_parser.cc"
    break;

  case 52: // exp_eval: tuple ASSIGN variable
#line 199 "svlm_grammar.y"
                          {
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::assign);
  }
#line 1321 "svlm_parser.cc"
    break;

  case 53: // literals: INT
#line 205 "svlm_grammar.y"
        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<OperandExprAst>(Operand(yystack_[0].value.as < int > ())); }
#line 1327 "svlm_parser.cc"
    break;

  case 54: // literals: FLT
#line 206 "svlm_grammar.y"
        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<OperandExprAst>(Operand(yystack_[0].value.as < float > ())); }
#line 1333 "svlm_parser.cc"
    break;

  case 55: // literals: TRUE
#line 207 "svlm_grammar.y"
         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<OperandExprAst>(Operand(true)); }
#line 1339 "svlm_parser.cc"
    break;

  case 56: // literals: FALSE
#line 208 "svlm_grammar.y"
          { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<OperandExprAst>(Operand(false)); }
#line 1345 "svlm_parser.cc"
    break;

  case 57: // literals: COLON STR
#line 209 "svlm_grammar.y"
              { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<OperandExprAst>(Operand(Atom(yystack_[0].value.as < std::string > ()))); }
#line 1351 "svlm_parser.cc"
    break;

  case 58: // variable: STR
#line 213 "svlm_grammar.y"
        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<LvarExprAst>(std::string(yystack_[0].value.as < std::string > ())); }
#line 1357 "svlm_parser.cc"
    break;

  case 59: // variable: DOLLAR STR
#line 214 "svlm_grammar.y"
               { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<GvarExprAst>(std::string(yystack_[0].value.as < std::string > ())); }
#line 1363 "svlm_parser.cc"
    break;

  case 60: // function: DEF STR PAREN_L param_list PAREN_R DO statement_list END
#line 221 "svlm_grammar.y"
                                                             { 

    if(slc->interactive) slc->defining_func = true;
    std::shared_ptr<FuncExprAst> func_ptr = 
      std::make_shared<FuncExprAst>
        (std::string(yystack_[6].value.as < std::string > ()), yystack_[4].value.as < std::vector<std::string> > (), yystack_[1].value.as < std::shared_ptr<ListExprAst> > ());  // this adds to ast tree notice param_list, not added in FuncExprAst
    slc->add_function_name(yystack_[6].value.as < std::string > ());
    slc->add_function_params(yystack_[4].value.as < std::vector<std::string> > ()); // this adds to the universe context  tree notice param_list
    slc->add_function_lvars(lvar_list);
    slc->add_function_fbody(func_ptr);

    lvar_list.clear();
    yylhs.value.as < std::shared_ptr<ExprAst> > () = func_ptr;
  }
#line 1382 "svlm_parser.cc"
    break;

  case 61: // case: CASE exp_eval DO case_match_list END
#line 240 "svlm_grammar.y"
                                         {
    std::shared_ptr<CaseExprAst> case_ptr =
      std::make_shared<CaseExprAst>(yystack_[3].value.as < std::shared_ptr<ExprAst> > (), yystack_[1].value.as < std::shared_ptr<ListExprAst> > ());
    yylhs.value.as < std::shared_ptr<ExprAst> > () = case_ptr;
  }
#line 1392 "svlm_parser.cc"
    break;

  case 62: // case_match_list: %empty
#line 248 "svlm_grammar.y"
           {
    //std::cout << "empty case match list\n";
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = std::make_shared<ListExprAst>(std::string("empty case match list"));
  }
#line 1401 "svlm_parser.cc"
    break;

  case 63: // case_match_list: case_match
#line 252 "svlm_grammar.y"
               {
    //std::cout << "start case match list\n";
    auto ast_current_context = std::make_shared<ListExprAst>(std::string("case match list"));
    ast_current_context->add(yystack_[0].value.as < std::shared_ptr<CaseMatchExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = ast_current_context;
  }
#line 1412 "svlm_parser.cc"
    break;

  case 64: // case_match_list: case_match_list case_match
#line 258 "svlm_grammar.y"
                               {
    if(yystack_[0].value.as < std::shared_ptr<CaseMatchExprAst> > () !=nullptr)
      yystack_[1].value.as < std::shared_ptr<ListExprAst> > ()->add(yystack_[0].value.as < std::shared_ptr<CaseMatchExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = yystack_[1].value.as < std::shared_ptr<ListExprAst> > ();
  }
#line 1422 "svlm_parser.cc"
    break;

  case 65: // case_match_list: case_match_list EOS case_match
#line 263 "svlm_grammar.y"
                                   {
    if(yystack_[0].value.as < std::shared_ptr<CaseMatchExprAst> > () !=nullptr)
      yystack_[2].value.as < std::shared_ptr<ListExprAst> > ()->add(yystack_[0].value.as < std::shared_ptr<CaseMatchExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = yystack_[2].value.as < std::shared_ptr<ListExprAst> > ();
  }
#line 1432 "svlm_parser.cc"
    break;

  case 66: // case_match_list: case_match_list error EOS case_match
#line 268 "svlm_grammar.y"
                                         { yyerrok; }
#line 1438 "svlm_parser.cc"
    break;

  case 67: // case_match: IS literals ARROW_R statement_list
#line 273 "svlm_grammar.y"
                                     {
    //std::cout << "case match s->sl"; $1->print(); std::cout << "\n";
    yylhs.value.as < std::shared_ptr<CaseMatchExprAst> > () = std::make_shared<CaseMatchIsExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ListExprAst> > ());
  }
#line 1447 "svlm_parser.cc"
    break;

  case 68: // case_match: IS variable WHEN statement ARROW_R statement_list
#line 277 "svlm_grammar.y"
                                                      {
    yylhs.value.as < std::shared_ptr<CaseMatchExprAst> > () = std::make_shared<CaseMatchWhenExprAst>(yystack_[4].value.as < std::shared_ptr<ExprAst> > (), yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ListExprAst> > ());
  }
#line 1455 "svlm_parser.cc"
    break;

  case 69: // case_match: IS tuple ARROW_R statement_list
#line 280 "svlm_grammar.y"
                                    {
    yylhs.value.as < std::shared_ptr<CaseMatchExprAst> > () = std::make_shared<CaseMatchIsExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ListExprAst> > ());
  }
#line 1463 "svlm_parser.cc"
    break;

  case 70: // case_match: IS tuple WHEN statement ARROW_R statement_list
#line 283 "svlm_grammar.y"
                                                   {
    yylhs.value.as < std::shared_ptr<CaseMatchExprAst> > () = std::make_shared<CaseMatchWhenExprAst>(yystack_[4].value.as < std::shared_ptr<ExprAst> > (), yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ListExprAst> > ());
  }
#line 1471 "svlm_parser.cc"
    break;

  case 71: // case_match: ELSE ARROW_R statement_list
#line 286 "svlm_grammar.y"
                                {
    yylhs.value.as < std::shared_ptr<CaseMatchExprAst> > () = std::make_shared<CaseMatchElseExprAst>(yystack_[0].value.as < std::shared_ptr<ListExprAst> > ());
  }
#line 1479 "svlm_parser.cc"
    break;

  case 73: // if_then_else: IF exp_eval THEN statement_list END
#line 296 "svlm_grammar.y"
                                        {
    auto l = std::make_shared<ListExprAst>("if then end");
    auto y = std::make_shared<OperandExprAst>(Operand(true));
    l->add(std::make_shared<CaseMatchIsExprAst>(y, yystack_[1].value.as < std::shared_ptr<ListExprAst> > ()));
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<CaseExprAst>(yystack_[3].value.as < std::shared_ptr<ExprAst> > (), l);
  }
#line 1490 "svlm_parser.cc"
    break;

  case 74: // if_then_else: IF exp_eval THEN statement_list ELSE statement_list END
#line 302 "svlm_grammar.y"
                                                            {
    auto l = std::make_shared<ListExprAst>("if then else end");
    auto y = std::make_shared<OperandExprAst>(Operand(true));
    l->add(std::make_shared<CaseMatchIsExprAst>(y, yystack_[3].value.as < std::shared_ptr<ListExprAst> > ()));
    l->add(std::make_shared<CaseMatchElseExprAst>(yystack_[1].value.as < std::shared_ptr<ListExprAst> > ()));
    std::shared_ptr<CaseExprAst> case_ptr =
      std::make_shared<CaseExprAst>(yystack_[5].value.as < std::shared_ptr<ExprAst> > (), l);
    yylhs.value.as < std::shared_ptr<ExprAst> > () = case_ptr;
  }
#line 1504 "svlm_parser.cc"
    break;

  case 75: // while_loop: WHILE exp_eval DO statement_list END
#line 325 "svlm_grammar.y"
                                         {
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<WhileExprAst>(yystack_[3].value.as < std::shared_ptr<ExprAst> > (), yystack_[1].value.as < std::shared_ptr<ListExprAst> > ());
  }
#line 1512 "svlm_parser.cc"
    break;

  case 76: // repeat_loop: REPEAT statement_list UNTIL exp_eval DONE
#line 331 "svlm_grammar.y"
                                              {
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<RepeatExprAst>(yystack_[1].value.as < std::shared_ptr<ExprAst> > (), yystack_[3].value.as < std::shared_ptr<ListExprAst> > ());
  }
#line 1520 "svlm_parser.cc"
    break;

  case 77: // param_list: param
#line 341 "svlm_grammar.y"
           { 
    std::vector<std::string> pl;
    pl.push_back(yystack_[0].value.as < std::string > ()); 
    yylhs.value.as < std::vector<std::string> > () = pl;
  }
#line 1530 "svlm_parser.cc"
    break;

  case 78: // param_list: param_list COMMA param
#line 346 "svlm_grammar.y"
                           { 
    yystack_[2].value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < std::string > ());
    yylhs.value.as < std::vector<std::string> > () = yystack_[2].value.as < std::vector<std::string> > ();
  }
#line 1539 "svlm_parser.cc"
    break;

  case 79: // param_list: %empty
#line 350 "svlm_grammar.y"
           { 
    std::vector<std::string> pl;
    yylhs.value.as < std::vector<std::string> > ()=pl;
  }
#line 1548 "svlm_parser.cc"
    break;

  case 80: // param: STR
#line 357 "svlm_grammar.y"
        { //std::cout << "param: " << $1 << "\n"; 
    yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > ();
  }
#line 1556 "svlm_parser.cc"
    break;


#line 1560 "svlm_parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  SvlmParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  SvlmParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char SvlmParser::yypact_ninf_ = -104;

  const signed char SvlmParser::yytable_ninf_ = -72;

  const short
  SvlmParser::yypact_[] =
  {
      88,  -104,   -37,   -32,  -104,   206,     1,   206,   206,    88,
     206,   206,   123,   -27,   -10,  -104,  -104,     4,  -104,  -104,
     206,    41,  -104,    21,  -104,  -104,  -104,  -104,  -104,    13,
     336,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    20,
     336,  -104,  -104,   122,   138,    49,   174,   324,    27,  -104,
    -104,    14,  -104,   123,   206,  -104,  -104,     2,  -104,  -104,
    -104,    88,    69,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,    44,    43,    88,   206,    88,
    -104,  -104,   123,   206,     7,   336,    88,  -104,    55,  -104,
    -104,  -104,   149,   149,    81,    81,    81,    81,    81,    81,
      32,    32,  -104,  -104,  -104,    24,  -104,   309,    29,   250,
    -104,   322,   161,   299,  -104,   336,  -104,  -104,  -104,    82,
      44,   -16,    67,    83,    88,     2,  -104,  -104,    43,  -104,
    -104,  -104,    88,    88,  -104,    88,    88,    88,    88,   251,
      43,  -104,   323,   333,    70,   260,   286,    72,  -104,  -104,
    -104,    88,    88,   287,   296
  };

  const signed char
  SvlmParser::yydefact_[] =
  {
       7,     3,     0,     0,    27,    25,     0,     0,     0,     7,
       0,     0,    21,     0,     0,    55,    56,    58,    53,    54,
       0,     0,    17,     0,     5,    10,    35,     9,    16,    33,
      24,    31,    32,    11,    12,    14,    13,    15,    18,     0,
      26,    29,    28,     0,     0,     0,     0,     0,     0,    20,
      22,    59,    57,    21,     0,    48,     1,     0,    82,    83,
      81,     8,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    62,     7,     0,     7,
      34,    30,     0,     0,     0,    50,     8,     4,     0,    58,
      51,    52,    46,    47,    44,    45,    40,    41,    43,    42,
      38,    39,    36,    37,    80,     0,    77,     0,     0,     0,
      63,     0,     0,     0,    19,    49,    23,     6,    59,     0,
       0,     0,     0,     0,     7,     0,    61,    64,     0,    75,
      76,    73,     7,     7,    78,     8,     7,     7,     8,     0,
       0,    65,     0,     0,     0,     0,     0,     0,    66,    74,
      60,     7,     7,     0,     0
  };

  const signed char
  SvlmParser::yypgoto_[] =
  {
    -104,  -104,  -104,    -9,   -51,  -104,    58,    30,  -104,    11,
    -104,   -60,     8,     6,   -59,  -104,  -104,  -104,  -103,  -104,
    -104,  -104,  -104,    -3,   -56
  };

  const signed char
  SvlmParser::yydefgoto_[] =
  {
       0,    21,    22,    23,    24,    25,    48,    49,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   109,   110,    35,
      36,    37,   105,   106,    61
  };

  const short
  SvlmParser::yytable_[] =
  {
      45,    86,    90,    91,    38,    58,   127,    59,   135,    39,
      87,     4,     5,    40,    51,    43,    44,    42,    46,    47,
     136,    -2,    57,    50,    58,   141,    59,    11,    55,    12,
      53,    52,    13,    14,   116,   117,    60,   148,    15,    16,
      82,    56,    17,    41,    18,    19,    75,   121,   123,    54,
      57,   119,    58,   128,    59,    60,    81,   120,    62,    83,
      82,    20,    85,   107,    50,   124,   108,    78,   111,   140,
     113,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    60,   144,   104,   112,   147,    73,    74,
     133,   115,     1,    50,     2,     3,   118,    12,     4,     5,
      88,     6,     7,   137,     8,     9,   151,   138,   152,    10,
      89,    84,   114,   122,    11,   139,    12,   134,     0,    13,
      14,     0,     0,   142,   143,    15,    16,   145,   146,    17,
      76,    18,    19,     4,     5,    71,    72,    73,    74,     0,
       0,     0,   153,   154,     0,     0,    77,     0,    20,    11,
       0,    12,     0,     0,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,    17,     0,    18,    19,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     130,     0,     0,    20,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    79,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    11,     0,    12,     0,     0,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,    17,     0,    18,
      19,   125,    57,    58,    58,    59,    59,     0,     0,   126,
     -71,    57,     0,    58,     0,    59,    20,     0,     0,   -69,
     107,   -71,     0,   108,   -71,     0,     0,     0,     0,     0,
     -69,     0,     0,   -69,    60,    60,     0,    57,    57,    58,
      58,    59,    59,     0,    60,   -67,   -70,    57,     0,    58,
      57,    59,    58,     0,    59,   -68,   -67,   -70,   131,   -67,
     -70,     0,     0,     0,     0,     0,   -68,     0,     0,   -68,
      60,    60,   132,    57,    57,    58,    58,    59,    59,     0,
      60,   129,   149,    60,    57,     0,    58,    12,    59,     0,
      88,    14,   150,     0,     0,     0,    15,    16,     0,     0,
      89,    80,    18,    19,     0,     0,    60,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74
  };

  const short
  SvlmParser::yycheck_[] =
  {
       9,    57,    62,    62,    41,     3,   109,     5,    24,    41,
      61,    10,    11,     5,    41,     7,     8,     6,    10,    11,
      36,     0,     1,    12,     3,   128,     5,    26,    20,    28,
      26,    41,    31,    32,    27,    86,    34,   140,    37,    38,
      33,     0,    41,    42,    43,    44,    26,   107,   107,    45,
       1,    27,     3,   109,     5,    34,    29,    33,    45,    45,
      33,    60,    54,    20,    53,    36,    23,    18,    77,   125,
      79,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    34,   135,    41,    78,   138,    56,    57,
       8,    83,     4,    82,     6,     7,    41,    28,    10,    11,
      31,    13,    14,    36,    16,    17,    36,    24,    36,    21,
      41,    53,    82,   107,    26,   124,    28,   120,    -1,    31,
      32,    -1,    -1,   132,   133,    37,    38,   136,   137,    41,
       8,    43,    44,    10,    11,    54,    55,    56,    57,    -1,
      -1,    -1,   151,   152,    -1,    -1,     8,    -1,    60,    26,
      -1,    28,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      37,    38,    -1,    -1,    41,    -1,    43,    44,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      19,    -1,    -1,    60,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    22,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    26,    -1,    28,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    37,    38,    -1,    -1,    41,    -1,    43,
      44,     1,     1,     3,     3,     5,     5,    -1,    -1,     9,
       9,     1,    -1,     3,    -1,     5,    60,    -1,    -1,     9,
      20,    20,    -1,    23,    23,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    23,    34,    34,    -1,     1,     1,     3,
       3,     5,     5,    -1,    34,     9,     9,     1,    -1,     3,
       1,     5,     3,    -1,     5,     9,    20,    20,     9,    23,
      23,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    23,
      34,    34,    23,     1,     1,     3,     3,     5,     5,    -1,
      34,     9,     9,    34,     1,    -1,     3,    28,     5,    -1,
      31,    32,     9,    -1,    -1,    -1,    37,    38,    -1,    -1,
      41,    27,    43,    44,    -1,    -1,    34,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57
  };

  const signed char
  SvlmParser::yystos_[] =
  {
       0,     4,     6,     7,    10,    11,    13,    14,    16,    17,
      21,    26,    28,    31,    32,    37,    38,    41,    43,    44,
      60,    63,    64,    65,    66,    67,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    81,    82,    83,    41,    41,
      74,    42,    71,    74,    74,    65,    74,    74,    68,    69,
      71,    41,    41,    26,    45,    74,     0,     1,     3,     5,
      34,    86,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    26,     8,     8,    18,    22,
      27,    29,    33,    45,    68,    74,    86,    66,    31,    41,
      73,    76,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    41,    84,    85,    20,    23,    79,
      80,    65,    74,    65,    69,    74,    27,    66,    41,    27,
      33,    73,    75,    76,    36,     1,     9,    80,    86,     9,
      19,     9,    23,     8,    85,    24,    36,    36,    24,    65,
      86,    80,    65,    65,    66,    65,    65,    66,    80,     9,
       9,    36,    36,    65,    65
  };

  const signed char
  SvlmParser::yyr1_[] =
  {
       0,    62,    63,    64,    65,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    68,
      68,    68,    69,    70,    71,    71,    71,    71,    72,    72,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    75,    75,    75,    75,    75,    76,    76,
      77,    78,    79,    79,    79,    79,    79,    80,    80,    80,
      80,    80,    81,    81,    81,    82,    83,    84,    84,    84,
      85,    86,    86,    86
  };

  const signed char
  SvlmParser::yyr2_[] =
  {
       0,     2,     1,     1,     3,     1,     4,     0,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     0,     1,     4,     1,     1,     2,     1,     2,     2,
       3,     1,     1,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     4,
       3,     3,     3,     1,     1,     1,     1,     2,     1,     2,
       8,     5,     0,     1,     2,     3,     4,     4,     6,     4,
       6,     3,     0,     5,     7,     5,     5,     1,     3,     0,
       1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const SvlmParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "EOL", "COMMENT1",
  "COMMENT2", "MODULE", "DEF", "DO", "END", "AST_BREAK", "AST_RETURN",
  "AST_DEFAULT", "PRINT", "CASE", "FLOW", "WHILE", "REPEAT", "UNTIL",
  "DONE", "IS", "IF", "THEN", "ELSE", "WHEN", "WHERE", "PAREN_L",
  "PAREN_R", "CUR_L", "CUR_R", "AT", "DOLLAR", "COLON", "COMMA",
  "SEMICOLON", "ARROW_L", "ARROW_R", "TRUE", "FALSE", "NIL", "IDENT_STR",
  "STR", "DQSTR", "INT", "FLT", "ASSIGN", "AND", "OR", "EQL", "NEQL", "GT",
  "LT", "GTEQ", "LTEQ", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO",
  "UMINUS", "NOT", "EXPONENT", "$accept", "program_start", "comments",
  "statement_list", "statement", "module", "arg_list", "arg", "caller",
  "exp", "print_exp", "tuple", "exp_eval", "literals", "variable",
  "function", "case", "case_match_list", "case_match", "if_then_else",
  "while_loop", "repeat_loop", "param_list", "param", "EOS", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  SvlmParser::yyrline_[] =
  {
       0,    76,    76,    80,    84,    89,    94,    95,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   113,   122,
     126,   131,   135,   141,   149,   150,   151,   152,   156,   157,
     162,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     190,   196,   199,   205,   206,   207,   208,   209,   213,   214,
     221,   240,   248,   252,   258,   263,   268,   273,   277,   280,
     283,   286,   293,   296,   302,   325,   331,   341,   346,   350,
     357,   365,   366,   367
  };

  void
  SvlmParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  SvlmParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  SvlmParser::symbol_kind_type
  SvlmParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
    };
    // Last valid token kind.
    const int code_max = 316;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 14 "svlm_grammar.y"
} // vslast
#line 2075 "svlm_parser.cc"

#line 369 "svlm_grammar.y"


//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
