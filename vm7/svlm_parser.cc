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
        value.copy< std::string > (YY_MOVE (that.value));
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
        value.move< std::string > (YY_MOVE (s.value));
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
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
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
        value.move< std::string > (YY_MOVE (that.value));
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
        value.copy< std::string > (that.value);
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
        value.move< std::string > (that.value);
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
        yylhs.value.emplace< std::string > ();
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
#line 73 "svlm_grammar.y"
                    { 
    //cout << "program start:" << *$1 << "\n"; $1->print(); cout << "\n";
    svlm_lang->add_code(Operand("Prompt"), move(yystack_[0].value.as < list_u_ptr > ()));
    }
#line 866 "svlm_parser.cc"
    break;

  case 3: // statement_list: statement_list EOS statement
#line 80 "svlm_grammar.y"
                                 {
    if(yystack_[2].value.as < list_u_ptr > ()==nullptr) { yyerrok; }
    if(yystack_[2].value.as < list_u_ptr > ()!=nullptr && yystack_[0].value.as < astexpr_u_ptr > ()!=nullptr) { yystack_[2].value.as < list_u_ptr > ()->add(move(yystack_[0].value.as < astexpr_u_ptr > ())); }
    yylhs.value.as < list_u_ptr > () = move(yystack_[2].value.as < list_u_ptr > ());
  }
#line 876 "svlm_parser.cc"
    break;

  case 4: // statement_list: statement
#line 85 "svlm_grammar.y"
               {
    auto new_list = std::make_unique<AstList>();
    new_list->add(move(yystack_[0].value.as < astexpr_u_ptr > ()));
    yylhs.value.as < list_u_ptr > () = move(new_list);
  }
#line 886 "svlm_parser.cc"
    break;

  case 5: // statement_list: statement_list error EOS statement
#line 90 "svlm_grammar.y"
                                       { yyerrok; }
#line 892 "svlm_parser.cc"
    break;

  case 6: // statement_list: %empty
#line 91 "svlm_grammar.y"
           { yylhs.value.as < list_u_ptr > () = std::make_unique<AstList>(); }
#line 898 "svlm_parser.cc"
    break;

  case 7: // statement: %empty
#line 95 "svlm_grammar.y"
           {yylhs.value.as < astexpr_u_ptr > ()=nullptr;}
#line 904 "svlm_parser.cc"
    break;

  case 8: // statement: exp_eval
#line 96 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 910 "svlm_parser.cc"
    break;

  case 9: // statement: module
#line 97 "svlm_grammar.y"
           { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 916 "svlm_parser.cc"
    break;

  case 10: // statement: function
#line 98 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 922 "svlm_parser.cc"
    break;

  case 11: // statement: print_exp
#line 99 "svlm_grammar.y"
              {yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 928 "svlm_parser.cc"
    break;

  case 12: // statement: comments
#line 100 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = nullptr; }
#line 934 "svlm_parser.cc"
    break;

  case 13: // comments: COMMENT1
#line 104 "svlm_grammar.y"
              { yylhs.value.as < astexpr_u_ptr > ()=nullptr; }
#line 940 "svlm_parser.cc"
    break;

  case 14: // module: MODULE STR DO statement_list END
#line 111 "svlm_grammar.y"
  {
    cout << "module : " << yystack_[3].value.as < std::string > () << "\n";
    svlm_lang->add_module(yystack_[3].value.as < std::string > (), move(yystack_[1].value.as < list_u_ptr > ()));
  }
#line 949 "svlm_parser.cc"
    break;

  case 15: // function: DEF STR PAREN_L PAREN_R DO statement_list END
#line 118 "svlm_grammar.y"
                                                  {
    yylhs.value.as < astexpr_u_ptr > () = make_unique<AstFunc>(yystack_[5].value.as < std::string > (), move(yystack_[1].value.as < list_u_ptr > ()));
  }
#line 957 "svlm_parser.cc"
    break;

  case 16: // exp_eval: literals
#line 126 "svlm_grammar.y"
              { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 963 "svlm_parser.cc"
    break;

  case 17: // exp_eval: variable
#line 127 "svlm_grammar.y"
             { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 969 "svlm_parser.cc"
    break;

  case 18: // exp_eval: caller
#line 128 "svlm_grammar.y"
           { yylhs.value.as < astexpr_u_ptr > () = move(yystack_[0].value.as < astexpr_u_ptr > ()); }
#line 975 "svlm_parser.cc"
    break;

  case 19: // exp_eval: exp_eval MULTIPLY exp_eval
#line 129 "svlm_grammar.y"
                               { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::mul); }
#line 981 "svlm_parser.cc"
    break;

  case 20: // exp_eval: exp_eval DIVIDE exp_eval
#line 130 "svlm_grammar.y"
                             { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::div); }
#line 987 "svlm_parser.cc"
    break;

  case 21: // exp_eval: exp_eval PLUS exp_eval
#line 131 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::plus); }
#line 993 "svlm_parser.cc"
    break;

  case 22: // exp_eval: exp_eval MINUS exp_eval
#line 132 "svlm_grammar.y"
                            { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::minus); }
#line 999 "svlm_parser.cc"
    break;

  case 23: // exp_eval: exp_eval GT exp_eval
#line 133 "svlm_grammar.y"
                         { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::gt); }
#line 1005 "svlm_parser.cc"
    break;

  case 24: // exp_eval: exp_eval LT exp_eval
#line 134 "svlm_grammar.y"
                         { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::lt); }
#line 1011 "svlm_parser.cc"
    break;

  case 25: // exp_eval: exp_eval LTEQ exp_eval
#line 135 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::lteq); }
#line 1017 "svlm_parser.cc"
    break;

  case 26: // exp_eval: exp_eval GTEQ exp_eval
#line 136 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::gteq); }
#line 1023 "svlm_parser.cc"
    break;

  case 27: // exp_eval: exp_eval EQL exp_eval
#line 137 "svlm_grammar.y"
                          { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::eql); }
#line 1029 "svlm_parser.cc"
    break;

  case 28: // exp_eval: exp_eval NEQL exp_eval
#line 138 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::neql); }
#line 1035 "svlm_parser.cc"
    break;

  case 29: // exp_eval: exp_eval AND exp_eval
#line 139 "svlm_grammar.y"
                          { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::and_); }
#line 1041 "svlm_parser.cc"
    break;

  case 30: // exp_eval: exp_eval OR exp_eval
#line 140 "svlm_grammar.y"
                         { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[2].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::or_); }
#line 1047 "svlm_parser.cc"
    break;

  case 31: // exp_eval: NOT exp_eval
#line 141 "svlm_grammar.y"
                 { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(move(yystack_[0].value.as < astexpr_u_ptr > ()), move(yystack_[0].value.as < astexpr_u_ptr > ()), AstOpCode::not_); }
#line 1053 "svlm_parser.cc"
    break;

  case 32: // exp_eval: DOLLAR STR ASSIGN exp_eval
#line 142 "svlm_grammar.y"
                               { 
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstMvar>(yystack_[2].value.as < std::string > ()),
        move(yystack_[0].value.as < astexpr_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1065 "svlm_parser.cc"
    break;

  case 33: // exp_eval: STR ASSIGN exp_eval
#line 149 "svlm_grammar.y"
                        { 
      yylhs.value.as < astexpr_u_ptr > () = make_unique<AstBinOp>(
        make_unique<AstLvar>(yystack_[2].value.as < std::string > ()),
        move(yystack_[0].value.as < astexpr_u_ptr > ()), 
        AstOpCode::assign
      ); 
  }
#line 1077 "svlm_parser.cc"
    break;

  case 34: // literals: INT
#line 161 "svlm_grammar.y"
        { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < s_integer > ()); }
#line 1083 "svlm_parser.cc"
    break;

  case 35: // literals: FLT
#line 162 "svlm_grammar.y"
        { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < s_float > ()); }
#line 1089 "svlm_parser.cc"
    break;

  case 36: // literals: TRUE
#line 163 "svlm_grammar.y"
         { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(true); }
#line 1095 "svlm_parser.cc"
    break;

  case 37: // literals: FALSE
#line 164 "svlm_grammar.y"
          { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(false); }
#line 1101 "svlm_parser.cc"
    break;

  case 38: // literals: DQSTR
#line 166 "svlm_grammar.y"
          { yylhs.value.as < astexpr_u_ptr > () = make_unique<Operand>(yystack_[0].value.as < std::string > ()); }
#line 1107 "svlm_parser.cc"
    break;

  case 39: // caller: DOTSTR PAREN_L PAREN_R
#line 170 "svlm_grammar.y"
                           { yylhs.value.as < astexpr_u_ptr > ()= std::make_unique<AstCaller>(yystack_[2].value.as < std::string > ()); }
#line 1113 "svlm_parser.cc"
    break;

  case 40: // variable: DOLLAR STR
#line 175 "svlm_grammar.y"
               { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstMvar>(yystack_[0].value.as < std::string > ()); }
#line 1119 "svlm_parser.cc"
    break;

  case 41: // variable: STR
#line 176 "svlm_grammar.y"
        { yylhs.value.as < astexpr_u_ptr > () = make_unique<AstLvar>(yystack_[0].value.as < std::string > ()); }
#line 1125 "svlm_parser.cc"
    break;

  case 42: // print_exp: PRINT exp_eval
#line 183 "svlm_grammar.y"
                   { yylhs.value.as < astexpr_u_ptr > () = std::make_unique<AstPrint>(move(yystack_[0].value.as < astexpr_u_ptr > ())); }
#line 1131 "svlm_parser.cc"
    break;

  case 43: // DOTSTR: STR
#line 188 "svlm_grammar.y"
    { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1137 "svlm_parser.cc"
    break;

  case 44: // DOTSTR: DOTSTR DOT STR
#line 189 "svlm_grammar.y"
                   { yylhs.value.as < std::string > () = yystack_[2].value.as < std::string > () + std::string(".")+ yystack_[0].value.as < std::string > (); }
#line 1143 "svlm_parser.cc"
    break;


#line 1147 "svlm_parser.cc"

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









  const signed char SvlmParser::yypact_ninf_ = -51;

  const signed char SvlmParser::yytable_ninf_ = -44;

  const signed char
  SvlmParser::yypact_[] =
  {
      -4,   -51,   -40,   -25,   -29,    -5,   -51,   -51,    34,   -51,
     -51,   -51,   -29,    14,     5,   -51,   -51,   -51,   -51,    21,
     -51,   -51,   -51,   -51,    68,    37,    39,    21,    15,   -29,
     -51,   -51,    30,   -51,   -51,   -51,    -4,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,    40,
      55,    -4,    73,   -29,    21,    -4,   -51,    33,    33,    38,
      38,    38,    38,    38,    38,   -30,   -30,   -51,   -51,   -51,
     -51,    19,    58,    21,   -51,   -51,    -4,    22,   -51
  };

  const signed char
  SvlmParser::yydefact_[] =
  {
       6,    13,     0,     0,     0,     0,    36,    37,    41,    38,
      34,    35,     0,     0,     0,     4,    12,     9,    10,     8,
      16,    18,    17,    11,     0,     0,     0,    42,    40,     0,
      31,     1,     0,    46,    47,    45,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,    33,     7,     3,    29,    30,    27,
      28,    23,    24,    26,    25,    21,    22,    19,    20,    39,
      44,     0,     0,    32,     5,    14,     6,     0,    15
  };

  const signed char
  SvlmParser::yypgoto_[] =
  {
     -51,   -51,   -50,    28,   -51,   -51,   -51,     9,   -51,   -51,
     -51,   -51,   -51,    69
  };

  const signed char
  SvlmParser::yydefgoto_[] =
  {
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    36
  };

  const signed char
  SvlmParser::yytable_[] =
  {
       1,    71,     2,     3,    25,    -2,    32,     5,    33,     4,
      34,     6,     7,    27,    31,     8,     9,    10,    11,    26,
      32,    30,    33,    32,    34,    33,    77,    34,    75,    47,
      48,    78,     5,    33,    12,    34,     6,     7,    54,    28,
       8,     9,    10,    11,    35,    51,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    35,    12,
     -43,    35,    73,    53,    56,    52,    76,    69,   -43,    35,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    29,    74,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    45,    46,    47,    48,    70,
      72,    55,    50
  };

  const signed char
  SvlmParser::yycheck_[] =
  {
       4,    51,     6,     7,    44,     0,     1,    36,     3,    13,
       5,    40,    41,     4,     0,    44,    45,    46,    47,    44,
       1,    12,     3,     1,     5,     3,    76,     5,     9,    59,
      60,     9,    36,     3,    63,     5,    40,    41,    29,    44,
      44,    45,    46,    47,    39,     8,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    39,    63,
      26,    39,    53,    48,    36,    26,     8,    27,    34,    39,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    48,    55,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    26,    57,    58,    59,    60,    44,
      27,    32,    34
  };

  const signed char
  SvlmParser::yystos_[] =
  {
       0,     4,     6,     7,    13,    36,    40,    41,    44,    45,
      46,    47,    63,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    44,    44,    72,    44,    48,
      72,     0,     1,     3,     5,    39,    78,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    26,
      34,     8,    26,    48,    72,    78,    68,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    27,
      44,    67,    27,    72,    68,     9,     8,    67,     9
  };

  const signed char
  SvlmParser::yyr1_[] =
  {
       0,    65,    66,    67,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    69,    70,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    73,    73,    73,    74,
      75,    75,    76,    77,    77,    78,    78,    78
  };

  const signed char
  SvlmParser::yyr2_[] =
  {
       0,     2,     1,     3,     1,     4,     0,     0,     1,     1,
       1,     1,     1,     1,     5,     7,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     4,     3,     1,     1,     1,     1,     1,     3,
       2,     1,     2,     1,     3,     1,     1,     1
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
  "DOTSTR", "EOS", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  SvlmParser::yyrline_[] =
  {
       0,    73,    73,    80,    85,    90,    91,    95,    96,    97,
      98,    99,   100,   104,   110,   118,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   149,   161,   162,   163,   164,   166,   170,
     175,   176,   183,   188,   189,   194,   195,   196
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
#line 1565 "svlm_parser.cc"

#line 200 "svlm_grammar.y"


//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
