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
#include <tuple>
#include "lang.hh"

#line 49 "svlm_parser.cc"


#include "svlm_parser.hh"


// Unqualified %code blocks.
#line 36 "svlm_grammar.y"

#include "svlm_scanner.hh"
#define yylex(x,y) scanner->lex(x,y)



#line 63 "svlm_parser.cc"


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

#line 15 "svlm_grammar.y"
namespace vslast {
#line 156 "svlm_parser.cc"

  /// Build a parser object.
  SvlmParser::SvlmParser (SvlmScanner* scanner_yyarg, SvlmAst* svlm_lang_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      svlm_lang (svlm_lang_yyarg)
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
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_comments: // comments
      case symbol_kind::S_module: // module
      case symbol_kind::S_function: // function
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_proto_list: // proto_list
      case symbol_kind::S_proto: // proto
      case symbol_kind::S_tuple_arg_list: // tuple_arg_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
      case symbol_kind::S_case: // case
      case symbol_kind::S_case_match_list: // case_match_list
      case symbol_kind::S_case_match: // case_match
      case symbol_kind::S_if_then_else: // if_then_else
        value.copy< astnode_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< list_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kv_pair_list: // kv_pair_list
        value.copy< map_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.copy< s_float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.copy< s_integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_DOTSTR: // DOTSTR
      case symbol_kind::S_map_key: // map_key
        value.copy< string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kv_pair: // kv_pair
        value.copy< tuple<string, astnode_u_ptr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_comments: // comments
      case symbol_kind::S_module: // module
      case symbol_kind::S_function: // function
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_proto_list: // proto_list
      case symbol_kind::S_proto: // proto
      case symbol_kind::S_tuple_arg_list: // tuple_arg_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
      case symbol_kind::S_case: // case
      case symbol_kind::S_case_match_list: // case_match_list
      case symbol_kind::S_case_match: // case_match
      case symbol_kind::S_if_then_else: // if_then_else
        value.move< astnode_u_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< list_u_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_kv_pair_list: // kv_pair_list
        value.move< map_u_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.move< s_float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< s_integer > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_DOTSTR: // DOTSTR
      case symbol_kind::S_map_key: // map_key
        value.move< string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_kv_pair: // kv_pair
        value.move< tuple<string, astnode_u_ptr> > (YY_MOVE (s.value));
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
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_comments: // comments
      case symbol_kind::S_module: // module
      case symbol_kind::S_function: // function
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_proto_list: // proto_list
      case symbol_kind::S_proto: // proto
      case symbol_kind::S_tuple_arg_list: // tuple_arg_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
      case symbol_kind::S_case: // case
      case symbol_kind::S_case_match_list: // case_match_list
      case symbol_kind::S_case_match: // case_match
      case symbol_kind::S_if_then_else: // if_then_else
        value.YY_MOVE_OR_COPY< astnode_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.YY_MOVE_OR_COPY< list_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kv_pair_list: // kv_pair_list
        value.YY_MOVE_OR_COPY< map_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.YY_MOVE_OR_COPY< s_float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< s_integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_DOTSTR: // DOTSTR
      case symbol_kind::S_map_key: // map_key
        value.YY_MOVE_OR_COPY< string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kv_pair: // kv_pair
        value.YY_MOVE_OR_COPY< tuple<string, astnode_u_ptr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_comments: // comments
      case symbol_kind::S_module: // module
      case symbol_kind::S_function: // function
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_proto_list: // proto_list
      case symbol_kind::S_proto: // proto
      case symbol_kind::S_tuple_arg_list: // tuple_arg_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
      case symbol_kind::S_case: // case
      case symbol_kind::S_case_match_list: // case_match_list
      case symbol_kind::S_case_match: // case_match
      case symbol_kind::S_if_then_else: // if_then_else
        value.move< astnode_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< list_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kv_pair_list: // kv_pair_list
        value.move< map_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.move< s_float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< s_integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_DOTSTR: // DOTSTR
      case symbol_kind::S_map_key: // map_key
        value.move< string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kv_pair: // kv_pair
        value.move< tuple<string, astnode_u_ptr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_comments: // comments
      case symbol_kind::S_module: // module
      case symbol_kind::S_function: // function
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_proto_list: // proto_list
      case symbol_kind::S_proto: // proto
      case symbol_kind::S_tuple_arg_list: // tuple_arg_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
      case symbol_kind::S_case: // case
      case symbol_kind::S_case_match_list: // case_match_list
      case symbol_kind::S_case_match: // case_match
      case symbol_kind::S_if_then_else: // if_then_else
        value.copy< astnode_u_ptr > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< list_u_ptr > (that.value);
        break;

      case symbol_kind::S_kv_pair_list: // kv_pair_list
        value.copy< map_u_ptr > (that.value);
        break;

      case symbol_kind::S_FLT: // FLT
        value.copy< s_float > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< s_integer > (that.value);
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_DOTSTR: // DOTSTR
      case symbol_kind::S_map_key: // map_key
        value.copy< string > (that.value);
        break;

      case symbol_kind::S_kv_pair: // kv_pair
        value.copy< tuple<string, astnode_u_ptr> > (that.value);
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
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_comments: // comments
      case symbol_kind::S_module: // module
      case symbol_kind::S_function: // function
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_proto_list: // proto_list
      case symbol_kind::S_proto: // proto
      case symbol_kind::S_tuple_arg_list: // tuple_arg_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
      case symbol_kind::S_case: // case
      case symbol_kind::S_case_match_list: // case_match_list
      case symbol_kind::S_case_match: // case_match
      case symbol_kind::S_if_then_else: // if_then_else
        value.move< astnode_u_ptr > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< list_u_ptr > (that.value);
        break;

      case symbol_kind::S_kv_pair_list: // kv_pair_list
        value.move< map_u_ptr > (that.value);
        break;

      case symbol_kind::S_FLT: // FLT
        value.move< s_float > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< s_integer > (that.value);
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_DOTSTR: // DOTSTR
      case symbol_kind::S_map_key: // map_key
        value.move< string > (that.value);
        break;

      case symbol_kind::S_kv_pair: // kv_pair
        value.move< tuple<string, astnode_u_ptr> > (that.value);
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
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_comments: // comments
      case symbol_kind::S_module: // module
      case symbol_kind::S_function: // function
      case symbol_kind::S_exp_eval: // exp_eval
      case symbol_kind::S_literals: // literals
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_proto_list: // proto_list
      case symbol_kind::S_proto: // proto
      case symbol_kind::S_tuple_arg_list: // tuple_arg_list
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_while_loop: // while_loop
      case symbol_kind::S_repeat_loop: // repeat_loop
      case symbol_kind::S_case: // case
      case symbol_kind::S_case_match_list: // case_match_list
      case symbol_kind::S_case_match: // case_match
      case symbol_kind::S_if_then_else: // if_then_else
        yylhs.value.emplace< astnode_u_ptr > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
        yylhs.value.emplace< list_u_ptr > ();
        break;

      case symbol_kind::S_kv_pair_list: // kv_pair_list
        yylhs.value.emplace< map_u_ptr > ();
        break;

      case symbol_kind::S_FLT: // FLT
        yylhs.value.emplace< s_float > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< s_integer > ();
        break;

      case symbol_kind::S_IDENT_STR: // IDENT_STR
      case symbol_kind::S_STR: // STR
      case symbol_kind::S_DQSTR: // DQSTR
      case symbol_kind::S_DOTSTR: // DOTSTR
      case symbol_kind::S_map_key: // map_key
        yylhs.value.emplace< string > ();
        break;

      case symbol_kind::S_kv_pair: // kv_pair
        yylhs.value.emplace< tuple<string, astnode_u_ptr> > ();
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
#line 84 "svlm_grammar.y"
                    { 
    //cout << "program start:" << *$1 << "\n"; $1->print(); cout << "\n";
    svlm_lang->add_code(Operand("Prompt"), move(yystack_[0].value.as < list_u_ptr > ()));
  }
#line 1027 "svlm_parser.cc"
    break;

  case 3: // statement_list: statement_list EOS statement
#line 91 "svlm_grammar.y"
                                 {
    if(yystack_[2].value.as < list_u_ptr > ()==nullptr) { yyerrok; }
    if(yystack_[2].value.as < list_u_ptr > ()!=nullptr && yystack_[0].value.as < astnode_u_ptr > ()!=nullptr) { yystack_[2].value.as < list_u_ptr > ()->add(move(yystack_[0].value.as < astnode_u_ptr > ())); }
    yylhs.value.as < list_u_ptr > () = move(yystack_[2].value.as < list_u_ptr > ());
  }
#line 1037 "svlm_parser.cc"
    break;

  case 4: // statement_list: statement
#line 96 "svlm_grammar.y"
               {
    auto new_list = make_unique<AstList>();
    new_list->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < list_u_ptr > () = move(new_list);
  }
#line 1047 "svlm_parser.cc"
    break;

  case 5: // statement_list: statement_list error EOS statement
#line 101 "svlm_grammar.y"
                                       { yyerrok; }
#line 1053 "svlm_parser.cc"
    break;

  case 6: // statement_list: %empty
#line 102 "svlm_grammar.y"
           { yylhs.value.as < list_u_ptr > () = make_unique<AstList>(); }
#line 1059 "svlm_parser.cc"
    break;

  case 7: // statement: %empty
#line 106 "svlm_grammar.y"
           {yylhs.value.as < astnode_u_ptr > ()=nullptr;}
#line 1065 "svlm_parser.cc"
    break;

  case 8: // statement: exp_eval
#line 107 "svlm_grammar.y"
             { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1071 "svlm_parser.cc"
    break;

  case 9: // statement: module
#line 108 "svlm_grammar.y"
           { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1077 "svlm_parser.cc"
    break;

  case 10: // statement: function
#line 109 "svlm_grammar.y"
             { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1083 "svlm_parser.cc"
    break;

  case 11: // statement: print_exp
#line 110 "svlm_grammar.y"
              {yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1089 "svlm_parser.cc"
    break;

  case 12: // statement: comments
#line 111 "svlm_grammar.y"
             { yylhs.value.as < astnode_u_ptr > () = nullptr; }
#line 1095 "svlm_parser.cc"
    break;

  case 13: // statement: repeat_loop
#line 112 "svlm_grammar.y"
                { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1101 "svlm_parser.cc"
    break;

  case 14: // statement: while_loop
#line 113 "svlm_grammar.y"
               { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1107 "svlm_parser.cc"
    break;

  case 15: // statement: case
#line 114 "svlm_grammar.y"
         { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1113 "svlm_parser.cc"
    break;

  case 16: // statement: if_then_else
#line 115 "svlm_grammar.y"
                 { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1119 "svlm_parser.cc"
    break;

  case 17: // statement: AST_RETURN
#line 116 "svlm_grammar.y"
               { yylhs.value.as < astnode_u_ptr > () = std::make_unique<AstFlow>(ControlFlow::ast_return); }
#line 1125 "svlm_parser.cc"
    break;

  case 18: // statement: AST_RETURN exp_eval
#line 117 "svlm_grammar.y"
                        { yylhs.value.as < astnode_u_ptr > () = std::make_unique<AstFlow>(ControlFlow::ast_return_val, move(yystack_[0].value.as < astnode_u_ptr > ())); }
#line 1131 "svlm_parser.cc"
    break;

  case 19: // comments: COMMENT1
#line 121 "svlm_grammar.y"
              { yylhs.value.as < astnode_u_ptr > ()=nullptr; }
#line 1137 "svlm_parser.cc"
    break;

  case 20: // module: MODULE STR DO statement_list END
#line 128 "svlm_grammar.y"
  {
    //cout << "Grammar!"; cout << "module : " << $2 << "\n"; cout << "statement list: " ; $4->print(); cout << "\n";
    svlm_lang->add_module(yystack_[3].value.as < string > (), move(yystack_[1].value.as < list_u_ptr > ()));
  }
#line 1146 "svlm_parser.cc"
    break;

  case 21: // function: DEF STR PAREN_L proto_list PAREN_R DO statement_list END
#line 136 "svlm_grammar.y"
                                                             {
    //cout << "Grammar!"; cout << "func: " << $2 << "\n"; cout << "statement list: " ; $7->print(); cout << "\n";
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstFunc>(yystack_[6].value.as < string > (), move(yystack_[4].value.as < astnode_u_ptr > ()), move(yystack_[1].value.as < list_u_ptr > ()));
  }
#line 1155 "svlm_parser.cc"
    break;

  case 22: // exp_eval: literals
#line 143 "svlm_grammar.y"
              { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1161 "svlm_parser.cc"
    break;

  case 23: // exp_eval: variable
#line 144 "svlm_grammar.y"
             { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1167 "svlm_parser.cc"
    break;

  case 24: // exp_eval: list
#line 145 "svlm_grammar.y"
         { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1173 "svlm_parser.cc"
    break;

  case 25: // exp_eval: map
#line 146 "svlm_grammar.y"
        { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1179 "svlm_parser.cc"
    break;

  case 26: // exp_eval: tuple
#line 147 "svlm_grammar.y"
          { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1185 "svlm_parser.cc"
    break;

  case 27: // exp_eval: caller
#line 148 "svlm_grammar.y"
           { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1191 "svlm_parser.cc"
    break;

  case 28: // exp_eval: exp_eval MULTIPLY exp_eval
#line 149 "svlm_grammar.y"
                               { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::mul); }
#line 1197 "svlm_parser.cc"
    break;

  case 29: // exp_eval: exp_eval DIVIDE exp_eval
#line 150 "svlm_grammar.y"
                             { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::div); }
#line 1203 "svlm_parser.cc"
    break;

  case 30: // exp_eval: exp_eval PLUS exp_eval
#line 151 "svlm_grammar.y"
                           { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::plus); }
#line 1209 "svlm_parser.cc"
    break;

  case 31: // exp_eval: exp_eval MINUS exp_eval
#line 152 "svlm_grammar.y"
                            { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::minus); }
#line 1215 "svlm_parser.cc"
    break;

  case 32: // exp_eval: exp_eval GT exp_eval
#line 153 "svlm_grammar.y"
                         { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::gt); }
#line 1221 "svlm_parser.cc"
    break;

  case 33: // exp_eval: exp_eval LT exp_eval
#line 154 "svlm_grammar.y"
                         { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::lt); }
#line 1227 "svlm_parser.cc"
    break;

  case 34: // exp_eval: exp_eval LTEQ exp_eval
#line 155 "svlm_grammar.y"
                           { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::lteq); }
#line 1233 "svlm_parser.cc"
    break;

  case 35: // exp_eval: exp_eval GTEQ exp_eval
#line 156 "svlm_grammar.y"
                           { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::gteq); }
#line 1239 "svlm_parser.cc"
    break;

  case 36: // exp_eval: exp_eval EQL exp_eval
#line 157 "svlm_grammar.y"
                          { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::eql); }
#line 1245 "svlm_parser.cc"
    break;

  case 37: // exp_eval: exp_eval NEQL exp_eval
#line 158 "svlm_grammar.y"
                           { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::neql); }
#line 1251 "svlm_parser.cc"
    break;

  case 38: // exp_eval: exp_eval AND exp_eval
#line 159 "svlm_grammar.y"
                          { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::and_); }
#line 1257 "svlm_parser.cc"
    break;

  case 39: // exp_eval: exp_eval OR exp_eval
#line 160 "svlm_grammar.y"
                         { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::or_); }
#line 1263 "svlm_parser.cc"
    break;

  case 40: // exp_eval: NOT exp_eval
#line 161 "svlm_grammar.y"
                 { yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(move(yystack_[0].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < astnode_u_ptr > ()), AstOpCode::not_); }
#line 1269 "svlm_parser.cc"
    break;

  case 41: // exp_eval: DOLLAR STR ASSIGN exp_eval
#line 162 "svlm_grammar.y"
                               { 
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[2].value.as < string > ()),
        move(yystack_[0].value.as < astnode_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1281 "svlm_parser.cc"
    break;

  case 42: // exp_eval: DOLLAR DOTSTR ASSIGN exp_eval
#line 169 "svlm_grammar.y"
                                  { 
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[2].value.as < string > ()),
        move(yystack_[0].value.as < astnode_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1293 "svlm_parser.cc"
    break;

  case 43: // exp_eval: DOLLAR STR SQBRK_L exp_eval SQBRK_R ASSIGN exp_eval
#line 177 "svlm_grammar.y"
                                                        {
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[5].value.as < string > (), move(yystack_[3].value.as < astnode_u_ptr > ())),
        move(yystack_[0].value.as < astnode_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1305 "svlm_parser.cc"
    break;

  case 44: // exp_eval: DOLLAR DOTSTR SQBRK_L exp_eval SQBRK_R ASSIGN exp_eval
#line 184 "svlm_grammar.y"
                                                           {
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[5].value.as < string > (), move(yystack_[3].value.as < astnode_u_ptr > ())),
        move(yystack_[0].value.as < astnode_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1317 "svlm_parser.cc"
    break;

  case 45: // exp_eval: STR SQBRK_L exp_eval SQBRK_R ASSIGN exp_eval
#line 192 "svlm_grammar.y"
                                                 {
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstLvar>(yystack_[5].value.as < string > (), move(yystack_[3].value.as < astnode_u_ptr > ())),
        move(yystack_[0].value.as < astnode_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1329 "svlm_parser.cc"
    break;

  case 46: // exp_eval: STR ASSIGN exp_eval
#line 200 "svlm_grammar.y"
                        { 
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstLvar>(yystack_[2].value.as < string > ()),
        move(yystack_[0].value.as < astnode_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1341 "svlm_parser.cc"
    break;

  case 47: // exp_eval: tuple ASSIGN tuple
#line 207 "svlm_grammar.y"
                       {
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        move(yystack_[2].value.as < astnode_u_ptr > ()),
        move(yystack_[0].value.as < astnode_u_ptr > ()),
        AstOpCode::assign
      );
  }
#line 1353 "svlm_parser.cc"
    break;

  case 48: // exp_eval: tuple ASSIGN variable
#line 214 "svlm_grammar.y"
                          {
      yylhs.value.as < astnode_u_ptr > () = make_unique<AstBinOp>(
        move(yystack_[2].value.as < astnode_u_ptr > ()),
        move(yystack_[0].value.as < astnode_u_ptr > ()),
        AstOpCode::assign
      );
  }
#line 1365 "svlm_parser.cc"
    break;

  case 49: // literals: INT
#line 225 "svlm_grammar.y"
        { yylhs.value.as < astnode_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < s_integer > ()); }
#line 1371 "svlm_parser.cc"
    break;

  case 50: // literals: FLT
#line 226 "svlm_grammar.y"
        { yylhs.value.as < astnode_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < s_float > ()); }
#line 1377 "svlm_parser.cc"
    break;

  case 51: // literals: TRUE
#line 227 "svlm_grammar.y"
         { yylhs.value.as < astnode_u_ptr > () = make_unique<Operand>(true); }
#line 1383 "svlm_parser.cc"
    break;

  case 52: // literals: FALSE
#line 228 "svlm_grammar.y"
          { yylhs.value.as < astnode_u_ptr > () = make_unique<Operand>(false); }
#line 1389 "svlm_parser.cc"
    break;

  case 53: // literals: NIL
#line 229 "svlm_grammar.y"
        { yylhs.value.as < astnode_u_ptr > () = make_unique<Operand>(nil); }
#line 1395 "svlm_parser.cc"
    break;

  case 54: // literals: DQSTR
#line 231 "svlm_grammar.y"
          { yylhs.value.as < astnode_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < string > ()); }
#line 1401 "svlm_parser.cc"
    break;

  case 55: // caller: DOTSTR PAREN_L arg_list PAREN_R
#line 235 "svlm_grammar.y"
                                    { 
    //cout << "in Grammar: caller!\n" ; $3->print(); cout << "\n";
    yylhs.value.as < astnode_u_ptr > ()= make_unique<AstCaller>(yystack_[3].value.as < string > (), move(yystack_[1].value.as < astnode_u_ptr > ())); 
    }
#line 1410 "svlm_parser.cc"
    break;

  case 56: // variable: DOLLAR STR
#line 243 "svlm_grammar.y"
               { yylhs.value.as < astnode_u_ptr > () = make_unique<AstMvar>(yystack_[0].value.as < string > ()); }
#line 1416 "svlm_parser.cc"
    break;

  case 57: // variable: DOLLAR DOTSTR
#line 244 "svlm_grammar.y"
                  { yylhs.value.as < astnode_u_ptr > () = make_unique<AstMvar>(yystack_[0].value.as < string > ()); }
#line 1422 "svlm_parser.cc"
    break;

  case 58: // variable: DOLLAR STR SQBRK_L exp_eval SQBRK_R
#line 245 "svlm_grammar.y"
                                        { yylhs.value.as < astnode_u_ptr > () = make_unique<AstMvar>(yystack_[3].value.as < string > (), move(yystack_[1].value.as < astnode_u_ptr > ())); }
#line 1428 "svlm_parser.cc"
    break;

  case 59: // variable: DOLLAR DOTSTR SQBRK_L exp_eval SQBRK_R
#line 246 "svlm_grammar.y"
                                           { yylhs.value.as < astnode_u_ptr > () = make_unique<AstMvar>(yystack_[3].value.as < string > (), move(yystack_[1].value.as < astnode_u_ptr > ())); }
#line 1434 "svlm_parser.cc"
    break;

  case 60: // variable: STR
#line 248 "svlm_grammar.y"
        { yylhs.value.as < astnode_u_ptr > () = make_unique<AstLvar>(yystack_[0].value.as < string > ()); }
#line 1440 "svlm_parser.cc"
    break;

  case 61: // variable: STR SQBRK_L exp_eval SQBRK_R
#line 249 "svlm_grammar.y"
                                 { yylhs.value.as < astnode_u_ptr > () = make_unique<AstLvar>(move(yystack_[3].value.as < string > ()), move(yystack_[1].value.as < astnode_u_ptr > ())); }
#line 1446 "svlm_parser.cc"
    break;

  case 62: // print_exp: PRINT exp_eval
#line 258 "svlm_grammar.y"
                   { yylhs.value.as < astnode_u_ptr > () = make_unique<AstPrint>(move(yystack_[0].value.as < astnode_u_ptr > ())); }
#line 1452 "svlm_parser.cc"
    break;

  case 63: // DOTSTR: STR
#line 263 "svlm_grammar.y"
    { yylhs.value.as < string > () = yystack_[0].value.as < string > (); }
#line 1458 "svlm_parser.cc"
    break;

  case 64: // DOTSTR: DOTSTR DOT STR
#line 264 "svlm_grammar.y"
                   { yylhs.value.as < string > () = yystack_[2].value.as < string > () + string(".")+ yystack_[0].value.as < string > (); }
#line 1464 "svlm_parser.cc"
    break;

  case 65: // proto_list: proto
#line 270 "svlm_grammar.y"
           { 
    auto pl = make_unique<AstList>();
    pl->add(move(yystack_[0].value.as < astnode_u_ptr > ())); 
    yylhs.value.as < astnode_u_ptr > () = move(pl);
  }
#line 1474 "svlm_parser.cc"
    break;

  case 66: // proto_list: proto_list COMMA proto
#line 275 "svlm_grammar.y"
                           { 
    yystack_[2].value.as < astnode_u_ptr > ()->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(yystack_[2].value.as < astnode_u_ptr > ());
  }
#line 1483 "svlm_parser.cc"
    break;

  case 67: // proto_list: %empty
#line 279 "svlm_grammar.y"
           { 
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstList>();
  }
#line 1491 "svlm_parser.cc"
    break;

  case 68: // proto: STR
#line 285 "svlm_grammar.y"
        { //std::cout << "param: " << $1 << "\n"; 
    yylhs.value.as < astnode_u_ptr > ()=make_unique<Operand>(yystack_[0].value.as < string > ());
  }
#line 1499 "svlm_parser.cc"
    break;

  case 69: // tuple_arg_list: tuple_arg_list COMMA arg
#line 291 "svlm_grammar.y"
                             {
    yystack_[2].value.as < astnode_u_ptr > ()->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(yystack_[2].value.as < astnode_u_ptr > ());
  }
#line 1508 "svlm_parser.cc"
    break;

  case 70: // tuple_arg_list: arg
#line 295 "svlm_grammar.y"
        {
    auto al = make_unique<Tuple>();
    al->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(al);
  }
#line 1518 "svlm_parser.cc"
    break;

  case 71: // tuple_arg_list: %empty
#line 300 "svlm_grammar.y"
           {yylhs.value.as < astnode_u_ptr > () = make_unique<Tuple>();}
#line 1524 "svlm_parser.cc"
    break;

  case 72: // arg_list: arg_list COMMA arg
#line 305 "svlm_grammar.y"
                       {
    yystack_[2].value.as < astnode_u_ptr > ()->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(yystack_[2].value.as < astnode_u_ptr > ());
  }
#line 1533 "svlm_parser.cc"
    break;

  case 73: // arg_list: arg
#line 309 "svlm_grammar.y"
        {
    auto al = make_unique<AstList>();
    al->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(al);
  }
#line 1543 "svlm_parser.cc"
    break;

  case 74: // arg_list: %empty
#line 314 "svlm_grammar.y"
           {yylhs.value.as < astnode_u_ptr > () = make_unique<AstList>();}
#line 1549 "svlm_parser.cc"
    break;

  case 75: // arg: exp_eval
#line 318 "svlm_grammar.y"
             { yylhs.value.as < astnode_u_ptr > () = move(yystack_[0].value.as < astnode_u_ptr > ()); }
#line 1555 "svlm_parser.cc"
    break;

  case 76: // list: SQBRK_L arg_list SQBRK_R
#line 324 "svlm_grammar.y"
                             { 
    yylhs.value.as < astnode_u_ptr > () =  move(yystack_[1].value.as < astnode_u_ptr > ()); 
  }
#line 1563 "svlm_parser.cc"
    break;

  case 77: // map: PERCENT CUR_L kv_pair_list CUR_R
#line 331 "svlm_grammar.y"
                                     { yylhs.value.as < astnode_u_ptr > () = move(yystack_[1].value.as < map_u_ptr > ()); }
#line 1569 "svlm_parser.cc"
    break;

  case 78: // kv_pair_list: kv_pair_list COMMA kv_pair
#line 334 "svlm_grammar.y"
                               {
     yystack_[2].value.as < map_u_ptr > ()->add(Operand(get<0>(yystack_[0].value.as < tuple<string, astnode_u_ptr> > ()))._to_str(), move(get<1>(yystack_[0].value.as < tuple<string, astnode_u_ptr> > ())));
     yylhs.value.as < map_u_ptr > () = move(yystack_[2].value.as < map_u_ptr > ());
    //$$ = nullptr;
  }
#line 1579 "svlm_parser.cc"
    break;

  case 79: // kv_pair_list: kv_pair
#line 339 "svlm_grammar.y"
            {
    auto map_vptr = make_unique<AstMap>();
    map_vptr->add( Operand(get<0>(yystack_[0].value.as < tuple<string, astnode_u_ptr> > ())) , move(get<1>(yystack_[0].value.as < tuple<string, astnode_u_ptr> > ())));
    yylhs.value.as < map_u_ptr > () = move(map_vptr);
  }
#line 1589 "svlm_parser.cc"
    break;

  case 80: // kv_pair_list: %empty
#line 344 "svlm_grammar.y"
           {yylhs.value.as < map_u_ptr > () = make_unique<AstMap>();
  }
#line 1596 "svlm_parser.cc"
    break;

  case 81: // kv_pair: map_key COLON exp_eval
#line 348 "svlm_grammar.y"
                                 { yylhs.value.as < tuple<string, astnode_u_ptr> > () = {yystack_[2].value.as < string > (), move(yystack_[0].value.as < astnode_u_ptr > ())}; }
#line 1602 "svlm_parser.cc"
    break;

  case 82: // map_key: DQSTR
#line 349 "svlm_grammar.y"
          { yylhs.value.as < string > () = yystack_[0].value.as < string > (); }
#line 1608 "svlm_parser.cc"
    break;

  case 83: // map_key: STR
#line 349 "svlm_grammar.y"
                  { yylhs.value.as < string > () = yystack_[0].value.as < string > (); }
#line 1614 "svlm_parser.cc"
    break;

  case 84: // tuple: CUR_L tuple_arg_list CUR_R
#line 355 "svlm_grammar.y"
                               {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstTuple>(move(yystack_[1].value.as < astnode_u_ptr > ()));
    //$$ = make_unique<AstTuple>(make_unique<Tuple>(move($2)));
  }
#line 1623 "svlm_parser.cc"
    break;

  case 85: // while_loop: WHILE exp_eval DO statement_list END
#line 363 "svlm_grammar.y"
                                         {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstWhile>(move(yystack_[3].value.as < astnode_u_ptr > ()), move(yystack_[1].value.as < list_u_ptr > ()));
  }
#line 1631 "svlm_parser.cc"
    break;

  case 86: // repeat_loop: REPEAT statement_list UNTIL exp_eval DONE
#line 372 "svlm_grammar.y"
                                              {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstRepeat>(move(yystack_[1].value.as < astnode_u_ptr > ()), move(yystack_[3].value.as < list_u_ptr > ()));
  }
#line 1639 "svlm_parser.cc"
    break;

  case 87: // case: CASE exp_eval DO case_match_list END
#line 380 "svlm_grammar.y"
                                         {
    unique_ptr<AstCase> case_ptr = make_unique<AstCase>(move(yystack_[3].value.as < astnode_u_ptr > ()), move(yystack_[1].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(case_ptr);
  }
#line 1648 "svlm_parser.cc"
    break;

  case 88: // case_match_list: %empty
#line 387 "svlm_grammar.y"
           {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstList>();
  }
#line 1656 "svlm_parser.cc"
    break;

  case 89: // case_match_list: case_match
#line 390 "svlm_grammar.y"
               {
    auto  ml =   make_unique<AstList>();
    ml->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(ml);
  }
#line 1666 "svlm_parser.cc"
    break;

  case 90: // case_match_list: case_match_list case_match
#line 395 "svlm_grammar.y"
                               {
    if(yystack_[0].value.as < astnode_u_ptr > () != nullptr)
      yystack_[1].value.as < astnode_u_ptr > ()->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(yystack_[1].value.as < astnode_u_ptr > ());
  }
#line 1676 "svlm_parser.cc"
    break;

  case 91: // case_match_list: case_match_list EOS case_match
#line 400 "svlm_grammar.y"
                                   {
    if(yystack_[0].value.as < astnode_u_ptr > () != nullptr)
      yystack_[2].value.as < astnode_u_ptr > ()->add(move(yystack_[0].value.as < astnode_u_ptr > ()));
    yylhs.value.as < astnode_u_ptr > () = move(yystack_[2].value.as < astnode_u_ptr > ());
  }
#line 1686 "svlm_parser.cc"
    break;

  case 92: // case_match_list: case_match_list error EOS case_match
#line 405 "svlm_grammar.y"
                                         { yyerrok; }
#line 1692 "svlm_parser.cc"
    break;

  case 93: // case_match: IS literals ARROW_R statement_list
#line 410 "svlm_grammar.y"
                                       {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstCaseMatchIs>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < list_u_ptr > ()));
  }
#line 1700 "svlm_parser.cc"
    break;

  case 94: // case_match: IS variable WHEN statement ARROW_R statement_list
#line 413 "svlm_grammar.y"
                                                      {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstCaseMatchWhen>(move(yystack_[4].value.as < astnode_u_ptr > ()), move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < list_u_ptr > ()));
  }
#line 1708 "svlm_parser.cc"
    break;

  case 95: // case_match: IS tuple ARROW_R statement_list
#line 416 "svlm_grammar.y"
                                    {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstCaseMatchIs>(move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < list_u_ptr > ()));
  }
#line 1716 "svlm_parser.cc"
    break;

  case 96: // case_match: IS tuple WHEN statement ARROW_R statement_list
#line 419 "svlm_grammar.y"
                                                   {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstCaseMatchWhen>(move(yystack_[4].value.as < astnode_u_ptr > ()), move(yystack_[2].value.as < astnode_u_ptr > ()), move(yystack_[0].value.as < list_u_ptr > ()));
  }
#line 1724 "svlm_parser.cc"
    break;

  case 97: // case_match: ELSE ARROW_R statement_list
#line 422 "svlm_grammar.y"
                                {
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstCaseMatchElse>(move(yystack_[0].value.as < list_u_ptr > ()));
  }
#line 1732 "svlm_parser.cc"
    break;

  case 98: // if_then_else: IF exp_eval THEN statement_list END
#line 429 "svlm_grammar.y"
                                        {
    auto l = make_unique<AstList>();
    auto y = make_unique<Operand>(true);
    l->add(make_unique<AstCaseMatchIs>(move(y), move(yystack_[1].value.as < list_u_ptr > ())));
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstCase>(move(yystack_[3].value.as < astnode_u_ptr > ()), move(l));
  }
#line 1743 "svlm_parser.cc"
    break;

  case 99: // if_then_else: IF exp_eval THEN statement_list ELSE statement_list END
#line 435 "svlm_grammar.y"
                                                            {
    auto l = make_unique<AstList>();
    auto y = make_unique<Operand>(true);
    l->add(make_unique<AstCaseMatchIs>(move(y), move(yystack_[3].value.as < list_u_ptr > ())));
    l->add(make_unique<AstCaseMatchElse>(move(yystack_[1].value.as < list_u_ptr > ())));
    yylhs.value.as < astnode_u_ptr > () = make_unique<AstCase>(move(yystack_[5].value.as < astnode_u_ptr > ()), move(l));
  }
#line 1755 "svlm_parser.cc"
    break;


#line 1759 "svlm_parser.cc"

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









  const signed char SvlmParser::yypact_ninf_ = -65;

  const signed char SvlmParser::yytable_ninf_ = -98;

  const short
  SvlmParser::yypact_[] =
  {
     192,   -65,    52,   100,   285,   285,   285,   285,   192,   285,
     285,   285,   108,   -65,   -65,   -65,   135,   -65,   -65,   -65,
     -19,   285,   153,    36,   -65,   -65,   -65,   -65,   191,   -65,
     -65,   -65,   -65,     9,   -65,   -65,   122,   -65,   -65,   -65,
     -65,   149,   151,   191,   191,    -5,     7,   161,   207,   191,
     -22,   -65,   109,   -65,   -21,   154,   285,   285,    74,   -65,
     -65,   119,   -65,   -65,   -65,   192,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   140,
     183,   192,   146,    77,   192,   285,   192,   -65,   285,   -65,
     285,   285,   285,   285,   285,   301,   191,   -65,   -65,    39,
     -65,   160,   192,   -65,   400,   400,   -27,   -27,   -27,   -27,
     -27,   -27,    89,    89,   -65,   -65,   -17,   -65,   157,   180,
     -65,   -65,   111,   -65,     2,   -65,   403,   186,   136,   -65,
     112,    76,     3,   -65,   -65,   314,   191,   329,   191,   167,
     -65,    74,   285,   -65,   -65,   106,   139,   285,   -65,   217,
     146,   190,   202,    78,   192,   119,   -65,   -65,    77,   -65,
     -65,   -65,   192,   182,   187,   285,   -65,   191,   285,   285,
     342,   192,   -65,   192,   192,   192,   192,   184,    77,   -65,
     171,   285,   285,   191,   357,   370,   -65,   213,   267,   200,
     223,   268,   -65,   -65,   191,   191,   -65,   -65,   -65,   192,
     192,   277,   300
  };

  const signed char
  SvlmParser::yydefact_[] =
  {
       6,    19,     0,     0,    17,     0,     0,     0,     6,     0,
      71,    74,     0,    51,    52,    53,    60,    54,    49,    50,
       0,     0,     0,     0,     4,    12,     9,    10,     8,    22,
      27,    23,    11,     0,    24,    25,    26,    14,    13,    15,
      16,     0,     0,    18,    62,     0,     0,     0,     0,    75,
       0,    70,     0,    73,    56,    57,     0,     0,    80,    40,
       1,     0,   101,   102,   100,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    74,     0,
       0,     6,    67,    88,     6,     0,     6,    84,     0,    76,
       0,     0,     0,     0,     0,     0,    46,    83,    82,     0,
      79,     0,     7,     3,    38,    39,    36,    37,    32,    33,
      35,    34,    30,    31,    28,    29,     0,    64,     0,    60,
      48,    47,     0,    68,     0,    65,     0,     0,     0,    89,
       0,     0,     0,    69,    72,     0,    41,     0,    42,    61,
      77,     0,     0,     5,    55,    56,    57,     0,    20,     0,
       0,     0,     0,     0,     6,     0,    87,    90,     0,    85,
      86,    98,     6,    58,    59,     0,    78,    81,     0,     0,
       0,     6,    66,     6,     7,     7,     6,     0,     0,    91,
       0,     0,     0,    45,     0,     0,    61,     0,     0,     0,
       0,     0,    92,    99,    43,    44,    58,    59,    21,     6,
       6,     0,     0
  };

  const short
  SvlmParser::yypgoto_[] =
  {
     -65,   -65,    -8,   -64,   -65,   -65,   -65,    13,   148,   -65,
     -55,   -65,   -10,   -65,   125,   -65,   201,     4,   -65,   -65,
     -65,   142,   -65,   -52,   -65,   -65,   -65,   -65,   -35,   -65,
     -56
  };

  const unsigned char
  SvlmParser::yydefgoto_[] =
  {
       0,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,   124,   125,    50,    52,    53,    34,    35,
      99,   100,   101,    36,    37,    38,    39,   128,   129,    40,
      65
  };

  const short
  SvlmParser::yytable_[] =
  {
      47,   103,    55,    83,    61,   102,    62,    87,    63,    58,
     144,    91,   161,   -63,    51,    84,    88,    43,    44,    45,
      46,    90,    48,    49,    49,   120,   162,    92,   121,   149,
      74,    75,    76,    77,    59,    78,    -2,    61,   143,    62,
     150,    63,    64,    79,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,   140,    95,
      96,   152,   158,   122,   153,    64,   130,   141,   132,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    49,   133,   157,   134,   160,    41,   126,   131,   178,
     127,    49,   175,    49,   135,   136,   137,   138,   146,   176,
     189,   190,    61,    61,    62,    62,    63,    63,    97,    98,
     148,   159,    62,   179,    63,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,   155,   168,    62,
     -63,    63,    89,   192,    42,   156,   177,    90,    76,    77,
      64,    64,    54,    60,   180,   167,   126,    81,    64,   127,
     170,   -63,    61,   187,    62,   188,    63,    56,   191,   -63,
      80,   169,    61,    79,    62,    64,    63,    82,   183,    85,
     193,   184,   185,    57,   117,    61,    93,    62,    79,    63,
     123,   201,   202,   -97,   194,   195,     1,   142,     2,     3,
      64,   145,    94,     4,   -97,     5,     6,   -97,     7,     8,
      64,    10,   147,     9,    61,   165,    62,   154,    63,   118,
      10,   173,   198,    64,    11,   171,   174,   119,    12,    86,
     181,   199,    13,    14,    15,   182,    16,    17,    18,    19,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    64,    20,   200,    21,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    61,    61,
      62,    62,    63,    63,   151,   172,   -93,   -95,    61,   116,
      62,     0,    63,   166,     0,     0,   -94,   -93,   -95,     0,
     -93,   -95,     0,     0,     0,     0,     0,   -94,     0,     0,
     -94,    61,     0,    62,     0,    63,    64,    64,     0,   -96,
       0,     0,     0,    10,     0,     0,    64,    11,     0,     0,
     -96,    12,     0,   -96,     0,    13,    14,    15,     0,    16,
      17,    18,    19,     0,   139,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,    20,   163,    21,     0,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,   164,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   186,     0,     0,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
     196,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,   197,     0,     0,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,     0,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    10,     0,     0,     0,     0,     0,     0,     0,   118,
       0,     0,     0,    13,    14,    15,     0,   119,    17,    18,
      19,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77
  };

  const short
  SvlmParser::yycheck_[] =
  {
       8,    65,    12,     8,     1,    61,     3,    29,     5,    28,
      27,    32,     9,    34,    10,     8,    38,     4,     5,     6,
       7,    38,     9,    10,    11,    80,    23,    48,    80,    27,
      57,    58,    59,    60,    21,    26,     0,     1,   102,     3,
      38,     5,    39,    34,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    29,    56,
      57,   126,   128,    81,   126,    39,    84,    38,    86,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    88,   128,    90,    19,    44,    20,    85,   155,
      23,    88,    24,    90,    91,    92,    93,    94,   118,    31,
     174,   175,     1,     1,     3,     3,     5,     5,    44,    45,
       9,     9,     3,   158,     5,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     1,    32,     3,
      34,     5,    33,   178,    44,     9,   154,    38,    59,    60,
      39,    39,    44,     0,   162,   142,    20,     8,    39,    23,
     147,    26,     1,   171,     3,   173,     5,    32,   176,    34,
      48,    32,     1,    34,     3,    39,     5,    26,   165,    18,
       9,   168,   169,    48,    44,     1,    32,     3,    34,     5,
      44,   199,   200,     9,   181,   182,     4,    37,     6,     7,
      39,    44,    48,    11,    20,    13,    14,    23,    16,    17,
      39,    28,    32,    21,     1,    48,     3,    31,     5,    36,
      28,    31,     9,    39,    32,     8,    24,    44,    36,    22,
      48,    31,    40,    41,    42,    48,    44,    45,    46,    47,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    39,    61,    31,    63,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     1,     1,
       3,     3,     5,     5,   126,   150,     9,     9,     1,    78,
       3,    -1,     5,   141,    -1,    -1,     9,    20,    20,    -1,
      23,    23,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      23,     1,    -1,     3,    -1,     5,    39,    39,    -1,     9,
      -1,    -1,    -1,    28,    -1,    -1,    39,    32,    -1,    -1,
      20,    36,    -1,    23,    -1,    40,    41,    42,    -1,    44,
      45,    46,    47,    -1,    33,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    33,    63,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    33,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    33,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      33,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    33,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,    41,    42,    -1,    44,    45,    46,
      47,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60
  };

  const signed char
  SvlmParser::yystos_[] =
  {
       0,     4,     6,     7,    11,    13,    14,    16,    17,    21,
      28,    32,    36,    40,    41,    42,    44,    45,    46,    47,
      61,    63,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    83,    84,    88,    89,    90,    91,
      94,    44,    44,    72,    72,    72,    72,    67,    72,    72,
      80,    82,    81,    82,    44,    77,    32,    48,    28,    72,
       0,     1,     3,     5,    39,    95,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    26,    34,
      48,     8,    26,     8,     8,    18,    22,    29,    38,    33,
      38,    32,    48,    32,    48,    72,    72,    44,    45,    85,
      86,    87,    95,    68,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    81,    44,    36,    44,
      75,    88,    67,    44,    78,    79,    20,    23,    92,    93,
      67,    72,    67,    82,    82,    72,    72,    72,    72,    33,
      29,    38,    37,    68,    27,    44,    77,    32,     9,    27,
      38,    73,    75,    88,    31,     1,     9,    93,    95,     9,
      19,     9,    23,    33,    33,    48,    86,    72,    32,    32,
      72,     8,    79,    31,    24,    24,    31,    67,    95,    93,
      67,    48,    48,    72,    72,    72,    33,    67,    67,    68,
      68,    67,    93,     9,    72,    72,    33,    33,     9,    31,
      31,    67,    67
  };

  const signed char
  SvlmParser::yyr1_[] =
  {
       0,    65,    66,    67,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    69,
      70,    71,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    73,
      73,    73,    73,    73,    73,    74,    75,    75,    75,    75,
      75,    75,    76,    77,    77,    78,    78,    78,    79,    80,
      80,    80,    81,    81,    81,    82,    83,    84,    85,    85,
      85,    86,    87,    87,    88,    89,    90,    91,    92,    92,
      92,    92,    92,    93,    93,    93,    93,    93,    94,    94,
      95,    95,    95
  };

  const signed char
  SvlmParser::yyr2_[] =
  {
       0,     2,     1,     3,     1,     4,     0,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       5,     8,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     4,     4,     7,     7,     6,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     4,     2,     2,     5,     5,
       1,     4,     2,     1,     3,     1,     3,     0,     1,     3,
       1,     0,     3,     1,     0,     1,     3,     4,     3,     1,
       0,     3,     1,     1,     3,     5,     5,     5,     0,     1,
       2,     3,     4,     4,     6,     4,     6,     3,     5,     7,
       1,     1,     1
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
  "PAREN_R", "CUR_L", "CUR_R", "ARROW_L", "ARROW_R", "SQBRK_L", "SQBRK_R",
  "DOT", "AT", "DOLLAR", "COLON", "COMMA", "SEMICOLON", "TRUE", "FALSE",
  "NIL", "IDENT_STR", "STR", "DQSTR", "INT", "FLT", "ASSIGN", "AND", "OR",
  "EQL", "NEQL", "GT", "LT", "GTEQ", "LTEQ", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "PERCENT", "UMINUS", "NOT", "EXPONENT", "$accept",
  "program_start", "statement_list", "statement", "comments", "module",
  "function", "exp_eval", "literals", "caller", "variable", "print_exp",
  "DOTSTR", "proto_list", "proto", "tuple_arg_list", "arg_list", "arg",
  "list", "map", "kv_pair_list", "kv_pair", "map_key", "tuple",
  "while_loop", "repeat_loop", "case", "case_match_list", "case_match",
  "if_then_else", "EOS", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  SvlmParser::yyrline_[] =
  {
       0,    84,    84,    91,    96,   101,   102,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   121,
     127,   136,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   169,   177,   184,   192,   200,   207,   214,   225,
     226,   227,   228,   229,   231,   235,   243,   244,   245,   246,
     248,   249,   258,   263,   264,   270,   275,   279,   285,   291,
     295,   300,   305,   309,   314,   318,   324,   331,   334,   339,
     344,   348,   349,   349,   355,   363,   372,   380,   387,   390,
     395,   400,   405,   410,   413,   416,   419,   422,   429,   435,
     447,   448,   449
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
    };
    // Last valid token kind.
    const int code_max = 319;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 15 "svlm_grammar.y"
} // vslast
#line 2313 "svlm_parser.cc"

#line 453 "svlm_grammar.y"


//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const string& msg) {
    cerr << "line "  << l << ": " << msg << '\n';
}
