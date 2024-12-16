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
#line 32 "svlm_grammar.y"

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
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_kv_pair_list: // kv_pair_list
      case symbol_kind::S_tuple: // tuple
        value.copy< astexpr_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< list_u_ptr > (YY_MOVE (that.value));
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
        value.copy< tuple<string, astexpr_u_ptr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_kv_pair_list: // kv_pair_list
      case symbol_kind::S_tuple: // tuple
        value.move< astexpr_u_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< list_u_ptr > (YY_MOVE (s.value));
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
        value.move< tuple<string, astexpr_u_ptr> > (YY_MOVE (s.value));
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
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_kv_pair_list: // kv_pair_list
      case symbol_kind::S_tuple: // tuple
        value.YY_MOVE_OR_COPY< astexpr_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.YY_MOVE_OR_COPY< list_u_ptr > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< tuple<string, astexpr_u_ptr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_kv_pair_list: // kv_pair_list
      case symbol_kind::S_tuple: // tuple
        value.move< astexpr_u_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< list_u_ptr > (YY_MOVE (that.value));
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
        value.move< tuple<string, astexpr_u_ptr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_kv_pair_list: // kv_pair_list
      case symbol_kind::S_tuple: // tuple
        value.copy< astexpr_u_ptr > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< list_u_ptr > (that.value);
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
        value.copy< tuple<string, astexpr_u_ptr> > (that.value);
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
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_kv_pair_list: // kv_pair_list
      case symbol_kind::S_tuple: // tuple
        value.move< astexpr_u_ptr > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< list_u_ptr > (that.value);
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
        value.move< tuple<string, astexpr_u_ptr> > (that.value);
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
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_list: // list
      case symbol_kind::S_map: // map
      case symbol_kind::S_kv_pair_list: // kv_pair_list
      case symbol_kind::S_tuple: // tuple
        yylhs.value.emplace< astexpr_u_ptr > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
        yylhs.value.emplace< list_u_ptr > ();
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
        yylhs.value.emplace< tuple<string, astexpr_u_ptr> > ();
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
#line 78 "svlm_grammar.y"
                    { 
    //cout << "program start:" << *$1 << "\n"; $1->print(); cout << "\n";
    svlm_lang->add_code(Operand("Prompt"), move(yystack_[0].value.as < list_u_ptr > ()));
    }
#line 957 "svlm_parser.cc"
    break;

  case 3: // statement_list: statement_list EOS statement
#line 85 "svlm_grammar.y"
                                 {
    if(yystack_[2].value.as < list_u_ptr > ()==nullptr) { yyerrok; }
    if(yystack_[2].value.as < list_u_ptr > ()!=nullptr && yystack_[0].value.as < astexpr_u_ptr > ()!=nullptr) { yystack_[2].value.as < list_u_ptr > ()->add(move(yystack_[0].value.as < astexpr_u_ptr > ())); }
    yylhs.value.as < list_u_ptr > () = move(yystack_[2].value.as < list_u_ptr > ());
  }
#line 967 "svlm_parser.cc"
    break;

  case 4: // statement_list: statement
#line 90 "svlm_grammar.y"
               {
    auto new_list = make_unique<AstList>();
    new_list->add(move(yystack_[0].value.as < astexpr_u_ptr > ()));
    yylhs.value.as < list_u_ptr > () = move(new_list);
  }
#line 977 "svlm_parser.cc"
    break;

  case 5: // statement_list: statement_list error EOS statement
#line 95 "svlm_grammar.y"
                                       { yyerrok; }
#line 983 "svlm_parser.cc"
    break;

  case 6: // statement_list: %empty
#line 96 "svlm_grammar.y"
           { yylhs.value.as < list_u_ptr > () = make_unique<AstList>(); }
#line 989 "svlm_parser.cc"
    break;

  case 7: // statement: %empty
#line 100 "svlm_grammar.y"
           {yylhs.value.as < astexpr_u_ptr > ()=nullptr;}
#line 995 "svlm_parser.cc"
    break;

  case 8: // statement: exp_eval
#line 101 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1001 "svlm_parser.cc"
    break;

  case 9: // statement: module
#line 102 "svlm_grammar.y"
           { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1007 "svlm_parser.cc"
    break;

  case 10: // statement: function
#line 103 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1013 "svlm_parser.cc"
    break;

  case 11: // statement: print_exp
#line 104 "svlm_grammar.y"
              {yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1019 "svlm_parser.cc"
    break;

  case 12: // statement: comments
#line 105 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = nullptr; }
#line 1025 "svlm_parser.cc"
    break;

  case 13: // comments: COMMENT1
#line 109 "svlm_grammar.y"
              { yylhs.value.as < astexpr_u_ptr > ()=nullptr; }
#line 1031 "svlm_parser.cc"
    break;

  case 14: // module: MODULE STR DO statement_list END
#line 116 "svlm_grammar.y"
  {
    //cout << "module : " << $2 << "\n";
    svlm_lang->add_module(yystack_[3].value.as < string > (), move(yystack_[1].value.as < list_u_ptr > ()));
  }
#line 1040 "svlm_parser.cc"
    break;

  case 15: // function: DEF STR PAREN_L proto_list PAREN_R DO statement_list END
#line 124 "svlm_grammar.y"
                                                             {
    yylhs.value.as < astexpr_u_ptr > () = make_unique<AstFunc>(yystack_[6].value.as < string > (), move(yystack_[4].value.as < astexpr_u_ptr > ()), move(yystack_[1].value.as < list_u_ptr > ()));
  }
#line 1048 "svlm_parser.cc"
    break;

  case 16: // exp_eval: literals
#line 130 "svlm_grammar.y"
              { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1054 "svlm_parser.cc"
    break;

  case 17: // exp_eval: variable
#line 131 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1060 "svlm_parser.cc"
    break;

  case 18: // exp_eval: list
#line 132 "svlm_grammar.y"
         { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1066 "svlm_parser.cc"
    break;

  case 19: // exp_eval: map
#line 133 "svlm_grammar.y"
        { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1072 "svlm_parser.cc"
    break;

  case 20: // exp_eval: tuple
#line 134 "svlm_grammar.y"
          { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1078 "svlm_parser.cc"
    break;

  case 21: // exp_eval: caller
#line 135 "svlm_grammar.y"
           { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1084 "svlm_parser.cc"
    break;

  case 22: // exp_eval: exp_eval MULTIPLY exp_eval
#line 136 "svlm_grammar.y"
                               { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::mul); }
#line 1090 "svlm_parser.cc"
    break;

  case 23: // exp_eval: exp_eval DIVIDE exp_eval
#line 137 "svlm_grammar.y"
                             { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::div); }
#line 1096 "svlm_parser.cc"
    break;

  case 24: // exp_eval: exp_eval PLUS exp_eval
#line 138 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::plus); }
#line 1102 "svlm_parser.cc"
    break;

  case 25: // exp_eval: exp_eval MINUS exp_eval
#line 139 "svlm_grammar.y"
                            { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::minus); }
#line 1108 "svlm_parser.cc"
    break;

  case 26: // exp_eval: exp_eval GT exp_eval
#line 140 "svlm_grammar.y"
                         { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::gt); }
#line 1114 "svlm_parser.cc"
    break;

  case 27: // exp_eval: exp_eval LT exp_eval
#line 141 "svlm_grammar.y"
                         { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::lt); }
#line 1120 "svlm_parser.cc"
    break;

  case 28: // exp_eval: exp_eval LTEQ exp_eval
#line 142 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::lteq); }
#line 1126 "svlm_parser.cc"
    break;

  case 29: // exp_eval: exp_eval GTEQ exp_eval
#line 143 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::gteq); }
#line 1132 "svlm_parser.cc"
    break;

  case 30: // exp_eval: exp_eval EQL exp_eval
#line 144 "svlm_grammar.y"
                          { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::eql); }
#line 1138 "svlm_parser.cc"
    break;

  case 31: // exp_eval: exp_eval NEQL exp_eval
#line 145 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::neql); }
#line 1144 "svlm_parser.cc"
    break;

  case 32: // exp_eval: exp_eval AND exp_eval
#line 146 "svlm_grammar.y"
                          { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::and_); }
#line 1150 "svlm_parser.cc"
    break;

  case 33: // exp_eval: exp_eval OR exp_eval
#line 147 "svlm_grammar.y"
                         { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::or_); }
#line 1156 "svlm_parser.cc"
    break;

  case 34: // exp_eval: NOT exp_eval
#line 148 "svlm_grammar.y"
                 { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[0].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::not_); }
#line 1162 "svlm_parser.cc"
    break;

  case 35: // exp_eval: DOLLAR STR ASSIGN exp_eval
#line 149 "svlm_grammar.y"
                               { 
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[2].value.as < string > ()),
        move(yystack_[0].value.as < astexpr_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1174 "svlm_parser.cc"
    break;

  case 36: // exp_eval: DOLLAR DOTSTR ASSIGN exp_eval
#line 156 "svlm_grammar.y"
                                  { 
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[2].value.as < string > ()),
        move(yystack_[0].value.as < astexpr_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1186 "svlm_parser.cc"
    break;

  case 37: // exp_eval: DOLLAR STR SQBRK_L exp_eval SQBRK_R ASSIGN exp_eval
#line 164 "svlm_grammar.y"
                                                        {
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[5].value.as < string > (), move(yystack_[3].value.as < astexpr_u_ptr > ())),
        move(yystack_[0].value.as < astexpr_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1198 "svlm_parser.cc"
    break;

  case 38: // exp_eval: DOLLAR DOTSTR SQBRK_L exp_eval SQBRK_R ASSIGN exp_eval
#line 171 "svlm_grammar.y"
                                                           {
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[5].value.as < string > (), move(yystack_[3].value.as < astexpr_u_ptr > ())),
        move(yystack_[0].value.as < astexpr_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1210 "svlm_parser.cc"
    break;

  case 39: // exp_eval: STR ASSIGN exp_eval
#line 178 "svlm_grammar.y"
                        { 
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstLvar>(yystack_[2].value.as < string > ()),
        move(yystack_[0].value.as < astexpr_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1222 "svlm_parser.cc"
    break;

  case 40: // exp_eval: tuple ASSIGN tuple
#line 185 "svlm_grammar.y"
                       {
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstTuple>(move(yystack_[2].value.as < astexpr_u_ptr > ())),
        move(yystack_[0].value.as < astexpr_u_ptr > ()),
        AstOpCode::assign
      );
  }
#line 1234 "svlm_parser.cc"
    break;

  case 41: // literals: INT
#line 196 "svlm_grammar.y"
        { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < s_integer > ()); }
#line 1240 "svlm_parser.cc"
    break;

  case 42: // literals: FLT
#line 197 "svlm_grammar.y"
        { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < s_float > ()); }
#line 1246 "svlm_parser.cc"
    break;

  case 43: // literals: TRUE
#line 198 "svlm_grammar.y"
         { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(true); }
#line 1252 "svlm_parser.cc"
    break;

  case 44: // literals: FALSE
#line 199 "svlm_grammar.y"
          { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(false); }
#line 1258 "svlm_parser.cc"
    break;

  case 45: // literals: DQSTR
#line 201 "svlm_grammar.y"
          { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < string > ()); }
#line 1264 "svlm_parser.cc"
    break;

  case 46: // caller: DOTSTR PAREN_L arg_list PAREN_R
#line 205 "svlm_grammar.y"
                                    { yylhs.value.as < astexpr_u_ptr > ()= make_unique<AstCaller>(yystack_[3].value.as < string > (), move(yystack_[1].value.as < astexpr_u_ptr > ())); }
#line 1270 "svlm_parser.cc"
    break;

  case 47: // variable: DOLLAR STR
#line 210 "svlm_grammar.y"
               { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstMvar>(yystack_[0].value.as < string > ()); }
#line 1276 "svlm_parser.cc"
    break;

  case 48: // variable: DOLLAR DOTSTR
#line 211 "svlm_grammar.y"
                  { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstMvar>(yystack_[0].value.as < string > ()); }
#line 1282 "svlm_parser.cc"
    break;

  case 49: // variable: DOLLAR STR SQBRK_L exp_eval SQBRK_R
#line 212 "svlm_grammar.y"
                                        { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstMvar>(yystack_[3].value.as < string > (), move(yystack_[1].value.as < astexpr_u_ptr > ())); }
#line 1288 "svlm_parser.cc"
    break;

  case 50: // variable: DOLLAR DOTSTR SQBRK_L exp_eval SQBRK_R
#line 213 "svlm_grammar.y"
                                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstMvar>(yystack_[3].value.as < string > (), move(yystack_[1].value.as < astexpr_u_ptr > ())); }
#line 1294 "svlm_parser.cc"
    break;

  case 51: // variable: STR
#line 214 "svlm_grammar.y"
        { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstLvar>(yystack_[0].value.as < string > ()); }
#line 1300 "svlm_parser.cc"
    break;

  case 52: // print_exp: PRINT exp_eval
#line 222 "svlm_grammar.y"
                   { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstPrint>(move(yystack_[0].value.as < astexpr_u_ptr > ())); }
#line 1306 "svlm_parser.cc"
    break;

  case 53: // DOTSTR: STR
#line 227 "svlm_grammar.y"
    { yylhs.value.as < string > () = yystack_[0].value.as < string > (); }
#line 1312 "svlm_parser.cc"
    break;

  case 54: // DOTSTR: DOTSTR DOT STR
#line 228 "svlm_grammar.y"
                   { yylhs.value.as < string > () = yystack_[2].value.as < string > () + string(".")+ yystack_[0].value.as < string > (); }
#line 1318 "svlm_parser.cc"
    break;

  case 55: // proto_list: proto
#line 234 "svlm_grammar.y"
           { 
    auto pl = make_unique<AstList>();
    pl->add(move(yystack_[0].value.as < astexpr_u_ptr > ())); 
    yylhs.value.as < astexpr_u_ptr > () = move(pl);
  }
#line 1328 "svlm_parser.cc"
    break;

  case 56: // proto_list: proto_list COMMA proto
#line 239 "svlm_grammar.y"
                           { 
    yystack_[2].value.as < astexpr_u_ptr > ()->add(move(yystack_[0].value.as < astexpr_u_ptr > ()));
    yylhs.value.as < astexpr_u_ptr > () = move(yystack_[2].value.as < astexpr_u_ptr > ());
  }
#line 1337 "svlm_parser.cc"
    break;

  case 57: // proto_list: %empty
#line 243 "svlm_grammar.y"
           { 
    yylhs.value.as < astexpr_u_ptr > () = make_unique<AstList>();
  }
#line 1345 "svlm_parser.cc"
    break;

  case 58: // proto: STR
#line 249 "svlm_grammar.y"
        { //std::cout << "param: " << $1 << "\n"; 
    yylhs.value.as < astexpr_u_ptr > ()=make_unique<Operand>(yystack_[0].value.as < string > ());
  }
#line 1353 "svlm_parser.cc"
    break;

  case 59: // arg_list: arg_list COMMA arg
#line 255 "svlm_grammar.y"
                       {
    yystack_[2].value.as < astexpr_u_ptr > ()->add(move(yystack_[0].value.as < astexpr_u_ptr > ()));
    yylhs.value.as < astexpr_u_ptr > () = move(yystack_[2].value.as < astexpr_u_ptr > ());
  }
#line 1362 "svlm_parser.cc"
    break;

  case 60: // arg_list: arg
#line 259 "svlm_grammar.y"
        {
    auto al = make_unique<AstList>();
    al->add(move(yystack_[0].value.as < astexpr_u_ptr > ()));
    yylhs.value.as < astexpr_u_ptr > () = move(al);
  }
#line 1372 "svlm_parser.cc"
    break;

  case 61: // arg_list: %empty
#line 264 "svlm_grammar.y"
           {yylhs.value.as < astexpr_u_ptr > () = make_unique<AstList>();}
#line 1378 "svlm_parser.cc"
    break;

  case 62: // arg: exp_eval
#line 268 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 1384 "svlm_parser.cc"
    break;

  case 63: // list: SQBRK_L arg_list SQBRK_R
#line 273 "svlm_grammar.y"
                             { 
    yylhs.value.as < astexpr_u_ptr > () =  make_unique<Operand>( make_shared<Operand>( move(yystack_[1].value.as < astexpr_u_ptr > ()) )); 
    //$$ =  move($2); 
  }
#line 1393 "svlm_parser.cc"
    break;

  case 64: // map: PERCENT CUR_L kv_pair_list CUR_R
#line 281 "svlm_grammar.y"
                                     { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[1].value.as < astexpr_u_ptr > ()); }
#line 1399 "svlm_parser.cc"
    break;

  case 65: // kv_pair_list: kv_pair_list COMMA kv_pair
#line 284 "svlm_grammar.y"
                               {
    yystack_[2].value.as < astexpr_u_ptr > ()->add(Operand(get<0>(yystack_[0].value.as < tuple<string, astexpr_u_ptr> > ())), move(get<1>(yystack_[0].value.as < tuple<string, astexpr_u_ptr> > ())));
    yylhs.value.as < astexpr_u_ptr > () = move(yystack_[2].value.as < astexpr_u_ptr > ());
  }
#line 1408 "svlm_parser.cc"
    break;

  case 66: // kv_pair_list: kv_pair
#line 288 "svlm_grammar.y"
            {
    auto map_vptr = make_unique<AstMap>();
    map_vptr->add( Operand(get<0>(yystack_[0].value.as < tuple<string, astexpr_u_ptr> > ())) , move(get<1>(yystack_[0].value.as < tuple<string, astexpr_u_ptr> > ())));
    yylhs.value.as < astexpr_u_ptr > () = move(map_vptr);
  }
#line 1418 "svlm_parser.cc"
    break;

  case 67: // kv_pair_list: %empty
#line 293 "svlm_grammar.y"
           {yylhs.value.as < astexpr_u_ptr > () = make_unique<AstMap>();
  }
#line 1425 "svlm_parser.cc"
    break;

  case 68: // kv_pair: map_key COLON exp_eval
#line 297 "svlm_grammar.y"
                                 { yylhs.value.as < tuple<string, astexpr_u_ptr> > () = {yystack_[2].value.as < string > (), move(yystack_[0].value.as < astexpr_u_ptr > ())}; }
#line 1431 "svlm_parser.cc"
    break;

  case 69: // map_key: DQSTR
#line 298 "svlm_grammar.y"
          { yylhs.value.as < string > () = yystack_[0].value.as < string > (); }
#line 1437 "svlm_parser.cc"
    break;

  case 70: // map_key: STR
#line 298 "svlm_grammar.y"
                  { yylhs.value.as < string > () = yystack_[0].value.as < string > (); }
#line 1443 "svlm_parser.cc"
    break;

  case 71: // tuple: CUR_L arg_list CUR_R
#line 303 "svlm_grammar.y"
                         {
    //$$ = make_unique<AstTuple>(move($2));
    yylhs.value.as < astexpr_u_ptr > () = make_unique<Tuple>(move(yystack_[1].value.as < astexpr_u_ptr > ()));
  }
#line 1452 "svlm_parser.cc"
    break;


#line 1456 "svlm_parser.cc"

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









  const signed char SvlmParser::yypact_ninf_ = -59;

  const signed char SvlmParser::yytable_ninf_ = -54;

  const signed char
  SvlmParser::yypact_[] =
  {
      65,   -59,   -30,   -25,    89,    89,    89,   -23,   -59,   -59,
     -14,   -59,   -59,   -59,    11,    89,    70,     4,   -59,   -59,
     -59,   -59,    30,   -59,   -59,   -59,   -59,    68,   -59,   -59,
      44,    88,    72,    30,    30,    62,   -59,     2,   -19,   -16,
      89,    -7,   -59,   -59,     5,   -59,   -59,   -59,    65,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    55,    79,    65,    64,   -59,    89,   -59,    89,
      89,    89,    89,    30,   -59,   -59,    66,   -59,    76,    65,
     -59,    87,    87,    17,    17,    17,    17,    17,    17,   -18,
     -18,   -59,   -59,   -10,   -59,   -59,    21,   -59,    35,   -59,
     -59,   104,    30,   116,    30,   -59,    -7,    89,   -59,   -59,
     -59,   106,    64,    71,    74,   -59,    30,    65,   -59,    89,
      89,    22,    30,    30,   -59
  };

  const signed char
  SvlmParser::yydefact_[] =
  {
       6,    13,     0,     0,     0,    61,    61,     0,    43,    44,
      51,    45,    41,    42,     0,     0,     0,     0,     4,    12,
       9,    10,     8,    16,    21,    17,    11,     0,    18,    19,
      20,     0,     0,    52,    62,     0,    60,     0,    47,    48,
       0,    67,    34,     1,     0,    73,    74,    72,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     6,    57,    71,     0,    63,     0,
       0,     0,     0,    39,    70,    69,     0,    66,     0,     7,
       3,    32,    33,    30,    31,    26,    27,    29,    28,    24,
      25,    22,    23,     0,    54,    40,     0,    58,     0,    55,
      59,     0,    35,     0,    36,    64,     0,     0,     5,    46,
      14,     0,     0,    49,    50,    65,    68,     6,    56,     0,
       0,     0,    37,    38,    15
  };

  const signed char
  SvlmParser::yypgoto_[] =
  {
     -59,   -59,   -58,   -15,   -59,   -59,   -59,    -4,   -59,   -59,
     -59,   -59,   111,   -59,     8,    -3,    56,   -59,   -59,   -59,
      18,   -59,    69,    83
  };

  const signed char
  SvlmParser::yydefgoto_[] =
  {
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    98,    99,    35,    36,    28,    29,    76,
      77,    78,    30,    48
  };

  const signed char
  SvlmParser::yytable_[] =
  {
      33,    34,    34,    37,    -2,    44,    96,    45,    45,    46,
      46,    42,   -53,    69,    31,   -53,    71,   109,    62,    32,
     -53,    38,    44,    44,    45,    45,    46,    46,    67,    70,
     110,   124,    72,    80,    40,    68,    73,    74,    75,    41,
      67,    59,    60,    47,    47,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    34,    93,   121,
      47,    47,   111,    34,   108,   101,   102,   103,   104,     1,
      43,     2,     3,   112,    57,    58,    59,    60,     4,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    66,    63,     5,    61,   105,    64,     6,    65,    94,
      67,     7,    62,   116,   106,     8,     9,     5,    97,    10,
      11,    12,    13,   107,   117,   122,   123,     5,    39,   119,
     118,     6,   120,   100,   115,     7,    14,    79,    15,     8,
       9,     0,    95,    10,    11,    12,    13,   113,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,   114,
      14,     0,    15,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60
  };

  const signed char
  SvlmParser::yycheck_[] =
  {
       4,     5,     6,     6,     0,     1,    64,     3,     3,     5,
       5,    15,    26,    32,    44,    34,    32,    27,    34,    44,
      34,    44,     1,     1,     3,     3,     5,     5,    38,    48,
       9,     9,    48,    48,    48,    33,    40,    44,    45,    28,
      38,    59,    60,    39,    39,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    61,   117,
      39,    39,    27,    67,    79,    69,    70,    71,    72,     4,
       0,     6,     7,    38,    57,    58,    59,    60,    13,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    29,    48,    28,    26,    29,     8,    32,    26,    44,
      38,    36,    34,   107,    38,    40,    41,    28,    44,    44,
      45,    46,    47,    37,     8,   119,   120,    28,     7,    48,
     112,    32,    48,    67,   106,    36,    61,    44,    63,    40,
      41,    -1,    63,    44,    45,    46,    47,    33,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    33,
      61,    -1,    63,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60
  };

  const signed char
  SvlmParser::yystos_[] =
  {
       0,     4,     6,     7,    13,    28,    32,    36,    40,    41,
      44,    45,    46,    47,    61,    63,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    82,    83,
      87,    44,    44,    72,    72,    80,    81,    80,    44,    77,
      48,    28,    72,     0,     1,     3,     5,    39,    88,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    26,    34,    48,     8,    26,    29,    38,    33,    32,
      48,    32,    48,    72,    44,    45,    84,    85,    86,    88,
      68,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    80,    44,    87,    67,    44,    78,    79,
      81,    72,    72,    72,    72,    29,    38,    37,    68,    27,
       9,    27,    38,    33,    33,    85,    72,     8,    79,    48,
      48,    67,    72,    72,     9
  };

  const signed char
  SvlmParser::yyr1_[] =
  {
       0,    65,    66,    67,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    69,    70,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    73,    73,    73,    73,    74,    75,    75,    75,
      75,    75,    76,    77,    77,    78,    78,    78,    79,    80,
      80,    80,    81,    82,    83,    84,    84,    84,    85,    86,
      86,    87,    88,    88,    88
  };

  const signed char
  SvlmParser::yyr2_[] =
  {
       0,     2,     1,     3,     1,     4,     0,     0,     1,     1,
       1,     1,     1,     1,     5,     8,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     4,     4,     7,     7,     3,
       3,     1,     1,     1,     1,     1,     4,     2,     2,     5,
       5,     1,     2,     1,     3,     1,     3,     0,     1,     3,
       1,     0,     1,     3,     4,     3,     1,     0,     3,     1,
       1,     3,     1,     1,     1
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
  "DOTSTR", "proto_list", "proto", "arg_list", "arg", "list", "map",
  "kv_pair_list", "kv_pair", "map_key", "tuple", "EOS", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  SvlmParser::yyrline_[] =
  {
       0,    78,    78,    85,    90,    95,    96,   100,   101,   102,
     103,   104,   105,   109,   115,   124,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   156,   164,   171,   178,
     185,   196,   197,   198,   199,   201,   205,   210,   211,   212,
     213,   214,   222,   227,   228,   234,   239,   243,   249,   255,
     259,   264,   268,   273,   281,   284,   288,   293,   297,   298,
     298,   303,   311,   312,   313
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
#line 1915 "svlm_parser.cc"

#line 317 "svlm_grammar.y"


//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const string& msg) {
    cerr << "line "  << l << ": " << msg << '\n';
}
