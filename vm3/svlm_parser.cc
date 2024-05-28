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

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_num: // exp_num
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
        value.copy< std::shared_ptr<ExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
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

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_num: // exp_num
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
        value.move< std::shared_ptr<ExprAst> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
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

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_num: // exp_num
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
        value.YY_MOVE_OR_COPY< std::shared_ptr<ExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
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

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_num: // exp_num
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
        value.move< std::shared_ptr<ExprAst> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
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

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_num: // exp_num
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
        value.copy< std::shared_ptr<ExprAst> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
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

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_num: // exp_num
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
        value.move< std::shared_ptr<ExprAst> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
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

      case symbol_kind::S_comments: // comments
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_module: // module
      case symbol_kind::S_arg: // arg
      case symbol_kind::S_caller: // caller
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_print_exp: // print_exp
      case symbol_kind::S_tuple: // tuple
      case symbol_kind::S_exp_num: // exp_num
      case symbol_kind::S_function: // function
      case symbol_kind::S_case: // case
        yylhs.value.emplace< std::shared_ptr<ExprAst> > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_arg_list: // arg_list
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
#line 72 "svlm_grammar.y"
                    { auto astcode = slc->svlm_lang->ast_current_contexts.top(); astcode->add(yystack_[0].value.as < std::shared_ptr<ListExprAst> > ()); }
#line 915 "svlm_parser.cc"
    break;

  case 3: // comments: COMMENT1
#line 76 "svlm_grammar.y"
             {yylhs.value.as < std::shared_ptr<ExprAst> > ()=nullptr;}
#line 921 "svlm_parser.cc"
    break;

  case 4: // statement_list: statement_list EOS statement
#line 80 "svlm_grammar.y"
                                 {
    if(yystack_[0].value.as < std::shared_ptr<ExprAst> > ()!=nullptr) yystack_[2].value.as < std::shared_ptr<ListExprAst> > ()->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = yystack_[2].value.as < std::shared_ptr<ListExprAst> > ();
  }
#line 930 "svlm_parser.cc"
    break;

  case 5: // statement_list: statement
#line 84 "svlm_grammar.y"
               {
    auto ast_current_context = std::make_shared<ListExprAst>(std::string("statement code here"));
    ast_current_context->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = ast_current_context;
  }
#line 940 "svlm_parser.cc"
    break;

  case 6: // statement_list: statement_list error EOS statement
#line 89 "svlm_grammar.y"
                                       { yyerrok; }
#line 946 "svlm_parser.cc"
    break;

  case 7: // statement_list: %empty
#line 90 "svlm_grammar.y"
           { yylhs.value.as < std::shared_ptr<ListExprAst> > () = std::make_shared<ListExprAst>(std::string("empty statement code")); }
#line 952 "svlm_parser.cc"
    break;

  case 8: // statement: %empty
#line 94 "svlm_grammar.y"
           {yylhs.value.as < std::shared_ptr<ExprAst> > ()=nullptr;}
#line 958 "svlm_parser.cc"
    break;

  case 9: // statement: exp
#line 95 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 964 "svlm_parser.cc"
    break;

  case 10: // statement: module
#line 96 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 970 "svlm_parser.cc"
    break;

  case 11: // statement: function
#line 97 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 976 "svlm_parser.cc"
    break;

  case 12: // statement: caller
#line 98 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 982 "svlm_parser.cc"
    break;

  case 13: // statement: case
#line 99 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 988 "svlm_parser.cc"
    break;

  case 14: // statement: print_exp
#line 100 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 994 "svlm_parser.cc"
    break;

  case 15: // statement: comments
#line 101 "svlm_grammar.y"
             {yylhs.value.as < std::shared_ptr<ExprAst> > () = nullptr; }
#line 1000 "svlm_parser.cc"
    break;

  case 16: // module: MODULE STR
#line 106 "svlm_grammar.y"
               { 
    svlm_lang = slc->svlm_lang;
    slc->add_module_name(yystack_[0].value.as < std::string > ()); 
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<DeclExprAst>( std::make_shared<IdentExprAst>(yystack_[0].value.as < std::string > ()), DeclOpcodeAST::MODULE);
  }
#line 1010 "svlm_parser.cc"
    break;

  case 17: // arg_list: arg_list COMMA arg
#line 115 "svlm_grammar.y"
                       {
    yystack_[2].value.as < std::shared_ptr<ListExprAst> > ()->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = yystack_[2].value.as < std::shared_ptr<ListExprAst> > ();
  }
#line 1019 "svlm_parser.cc"
    break;

  case 18: // arg_list: arg
#line 119 "svlm_grammar.y"
        {
    auto ast_current_context = std::make_shared<ListExprAst>("argument block");
    ast_current_context->add(yystack_[0].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ListExprAst> > () = ast_current_context;
  }
#line 1029 "svlm_parser.cc"
    break;

  case 19: // arg_list: %empty
#line 124 "svlm_grammar.y"
           {yylhs.value.as < std::shared_ptr<ListExprAst> > () = std::make_shared<ListExprAst>("empty args");}
#line 1035 "svlm_parser.cc"
    break;

  case 20: // arg: exp
#line 128 "svlm_grammar.y"
    { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1041 "svlm_parser.cc"
    break;

  case 21: // caller: STR PAREN_L arg_list PAREN_R
#line 134 "svlm_grammar.y"
                                 {
    std::shared_ptr<CallExprAst> caller = std::make_shared<CallExprAst>(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<ListExprAst> > ()); 
    yylhs.value.as < std::shared_ptr<ExprAst> > () = caller;
  }
#line 1050 "svlm_parser.cc"
    break;

  case 22: // exp: exp_num
#line 142 "svlm_grammar.y"
            {yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1056 "svlm_parser.cc"
    break;

  case 23: // exp: AST_RETURN
#line 143 "svlm_grammar.y"
               { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<DisContExprAst>(std::string("return")); }
#line 1062 "svlm_parser.cc"
    break;

  case 24: // print_exp: PRINT exp
#line 147 "svlm_grammar.y"
              { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<PrintExprAst>(yystack_[0].value.as < std::shared_ptr<ExprAst> > ()); }
#line 1068 "svlm_parser.cc"
    break;

  case 25: // print_exp: PRINT DQSTR
#line 148 "svlm_grammar.y"
                { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<PrintExprAst> (std::make_shared<IdentExprAst>(yystack_[0].value.as < std::string > ())); }
#line 1074 "svlm_parser.cc"
    break;

  case 26: // tuple: CUR_L arg_list CUR_R
#line 153 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<TupleExprAst>(yystack_[1].value.as < std::shared_ptr<ListExprAst> > ()); }
#line 1080 "svlm_parser.cc"
    break;

  case 27: // exp_num: INT
#line 156 "svlm_grammar.y"
        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<NumberExprAst>(Number(yystack_[0].value.as < int > ())); }
#line 1086 "svlm_parser.cc"
    break;

  case 28: // exp_num: FLT
#line 157 "svlm_grammar.y"
        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<NumberExprAst>(Number(yystack_[0].value.as < float > ())); }
#line 1092 "svlm_parser.cc"
    break;

  case 29: // exp_num: tuple
#line 158 "svlm_grammar.y"
          { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[0].value.as < std::shared_ptr<ExprAst> > (); }
#line 1098 "svlm_parser.cc"
    break;

  case 30: // exp_num: COLON STR
#line 159 "svlm_grammar.y"
              { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<AtomExprAst>(Atom(yystack_[0].value.as < std::string > ())); }
#line 1104 "svlm_parser.cc"
    break;

  case 31: // exp_num: exp_num MULTIPLY exp_num
#line 161 "svlm_grammar.y"
                             { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::mul); }
#line 1110 "svlm_parser.cc"
    break;

  case 32: // exp_num: exp_num DIVIDE exp_num
#line 162 "svlm_grammar.y"
                           { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::div); }
#line 1116 "svlm_parser.cc"
    break;

  case 33: // exp_num: exp_num PLUS exp_num
#line 163 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::plus); }
#line 1122 "svlm_parser.cc"
    break;

  case 34: // exp_num: exp_num MINUS exp_num
#line 164 "svlm_grammar.y"
                          { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::minus); }
#line 1128 "svlm_parser.cc"
    break;

  case 35: // exp_num: exp_num GT exp_num
#line 165 "svlm_grammar.y"
                       { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::gt); }
#line 1134 "svlm_parser.cc"
    break;

  case 36: // exp_num: exp_num LT exp_num
#line 166 "svlm_grammar.y"
                       { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::lt); }
#line 1140 "svlm_parser.cc"
    break;

  case 37: // exp_num: exp_num LTEQ exp_num
#line 167 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::lteq); }
#line 1146 "svlm_parser.cc"
    break;

  case 38: // exp_num: exp_num GTEQ exp_num
#line 168 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::gteq); }
#line 1152 "svlm_parser.cc"
    break;

  case 39: // exp_num: exp_num EQL exp_num
#line 169 "svlm_grammar.y"
                        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::eql); }
#line 1158 "svlm_parser.cc"
    break;

  case 40: // exp_num: exp_num NEQL exp_num
#line 170 "svlm_grammar.y"
                         { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::neql); }
#line 1164 "svlm_parser.cc"
    break;

  case 41: // exp_num: exp_num AND exp_num
#line 171 "svlm_grammar.y"
                        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::and_); }
#line 1170 "svlm_parser.cc"
    break;

  case 42: // exp_num: exp_num OR exp_num
#line 172 "svlm_grammar.y"
                       { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::or_); }
#line 1176 "svlm_parser.cc"
    break;

  case 43: // exp_num: NOT exp_num
#line 173 "svlm_grammar.y"
                { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[0].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::not_); }
#line 1182 "svlm_parser.cc"
    break;

  case 44: // exp_num: PAREN_L exp_num PAREN_R
#line 175 "svlm_grammar.y"
                                   { yylhs.value.as < std::shared_ptr<ExprAst> > () = yystack_[1].value.as < std::shared_ptr<ExprAst> > (); }
#line 1188 "svlm_parser.cc"
    break;

  case 45: // exp_num: DOLLAR STR
#line 176 "svlm_grammar.y"
               { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<GvarExprAst>(std::string(yystack_[0].value.as < std::string > ())); }
#line 1194 "svlm_parser.cc"
    break;

  case 46: // exp_num: DOLLAR STR ASSIGN exp_num
#line 177 "svlm_grammar.y"
                              {           // global variable
    slc->add_mvar_name(yystack_[2].value.as < std::string > ());               // add to context tree
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(
      std::make_shared<GvarExprAst>(std::string(yystack_[2].value.as < std::string > ())), 
      yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::assign);
  }
#line 1205 "svlm_parser.cc"
    break;

  case 47: // exp_num: STR
#line 184 "svlm_grammar.y"
        { yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<LvarExprAst>(std::string(yystack_[0].value.as < std::string > ())); }
#line 1211 "svlm_parser.cc"
    break;

  case 48: // exp_num: STR ASSIGN exp_num
#line 185 "svlm_grammar.y"
                       { 
    lvar_list.push_back(yystack_[2].value.as < std::string > ());
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(
      std::make_shared<LvarExprAst>(std::string(yystack_[2].value.as < std::string > ())), 
      yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::assign);
  }
#line 1222 "svlm_parser.cc"
    break;

  case 49: // exp_num: tuple ASSIGN tuple
#line 191 "svlm_grammar.y"
                       {
    yylhs.value.as < std::shared_ptr<ExprAst> > () = std::make_shared<BinOpExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > (), yystack_[0].value.as < std::shared_ptr<ExprAst> > (), ast_op::assign);
  }
#line 1230 "svlm_parser.cc"
    break;

  case 50: // function: DEF STR PAREN_L param_list PAREN_R DO statement_list END
#line 198 "svlm_grammar.y"
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
#line 1249 "svlm_parser.cc"
    break;

  case 51: // case: CASE statement DO END
#line 216 "svlm_grammar.y"
                          {
    std::shared_ptr<CaseExprAst> case_ptr =
      std::make_shared<CaseExprAst>(yystack_[2].value.as < std::shared_ptr<ExprAst> > ());
    yylhs.value.as < std::shared_ptr<ExprAst> > () = case_ptr;
  }
#line 1259 "svlm_parser.cc"
    break;

  case 52: // param_list: param
#line 234 "svlm_grammar.y"
           { 
    std::vector<std::string> pl;
    pl.push_back(yystack_[0].value.as < std::string > ()); 
    yylhs.value.as < std::vector<std::string> > () = pl;
  }
#line 1269 "svlm_parser.cc"
    break;

  case 53: // param_list: param_list COMMA param
#line 239 "svlm_grammar.y"
                           { 
    yystack_[2].value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < std::string > ());
    yylhs.value.as < std::vector<std::string> > () = yystack_[2].value.as < std::vector<std::string> > ();
  }
#line 1278 "svlm_parser.cc"
    break;

  case 54: // param_list: %empty
#line 243 "svlm_grammar.y"
           { 
    std::vector<std::string> pl;
    yylhs.value.as < std::vector<std::string> > ()=pl;
  }
#line 1287 "svlm_parser.cc"
    break;

  case 55: // param: STR
#line 250 "svlm_grammar.y"
        { //std::cout << "param: " << $1 << "\n"; 
    yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > ();
  }
#line 1295 "svlm_parser.cc"
    break;


#line 1299 "svlm_parser.cc"

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









  const signed char SvlmParser::yypact_ninf_ = -20;

  const signed char SvlmParser::yytable_ninf_ = -3;

  const signed char
  SvlmParser::yypact_[] =
  {
      15,   -20,   -19,   -15,   -20,    52,    15,    90,    72,   -10,
      -5,   -11,   -20,   -20,    90,    24,   -20,     8,   -20,   -20,
     -20,   -20,   -20,     7,   105,   -20,   -20,   -20,    26,    31,
     -20,   -20,    38,    92,   -13,   -20,   -20,    37,   -20,    72,
      90,   -20,   -20,    11,   -20,   -20,   -20,    15,    53,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    44,    67,   -20,   -20,    72,    90,     3,   105,    15,
     -20,   -20,    34,    34,    34,    34,    34,    34,    34,    34,
       4,     4,   -20,   -20,   -20,    17,   -20,   -20,   -20,   105,
     -20,   -20,    73,    44,    15,   -20,    83,   -20
  };

  const signed char
  SvlmParser::yydefact_[] =
  {
       7,     3,     0,     0,    23,     0,     8,     0,    19,     0,
       0,    47,    27,    28,     0,     0,    15,     0,     5,    10,
      12,     9,    14,    29,    22,    11,    13,    16,     0,    47,
      25,    24,     0,     0,     0,    18,    20,    45,    30,    19,
       0,    43,     1,     0,    57,    58,    56,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,     0,    44,    26,     0,     0,     0,    48,     8,
       4,    49,    39,    40,    35,    36,    38,    37,    41,    42,
      33,    34,    31,    32,    55,     0,    52,    51,    17,    46,
      21,     6,     0,     0,     7,    53,     0,    50
  };

  const signed char
  SvlmParser::yypgoto_[] =
  {
     -20,   -20,   -20,    -1,    -6,   -20,    50,    18,   -20,    -4,
     -20,    46,    -2,   -20,   -20,   -20,     2,    55
  };

  const signed char
  SvlmParser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    34,    35,    20,    21,
      22,    23,    24,    25,    26,    85,    86,    47
  };

  const signed char
  SvlmParser::yytable_[] =
  {
      32,    31,    39,    64,    36,    33,    27,    65,    -2,    43,
      28,    44,    41,    45,    44,    37,    45,    90,    40,     1,
      38,     2,     3,    65,    42,     4,     5,     6,     7,    46,
       8,    92,    46,     9,    10,    36,    48,    93,    68,    61,
      11,    70,    12,    13,    59,    60,    62,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    14,
      40,    36,     4,    91,    89,     7,    66,     8,     8,    84,
       9,    10,    57,    58,    59,    60,    87,    29,    30,    12,
      13,    94,     4,    88,    43,     7,    44,     8,    45,    67,
       9,    10,    97,    96,    71,    95,    14,    29,    69,    12,
      13,     0,     0,     7,    46,     8,    63,     0,     9,    10,
       0,     0,     0,     0,     0,    29,    14,    12,    13,     0,
       0,     0,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    14,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60
  };

  const signed char
  SvlmParser::yycheck_[] =
  {
       6,     5,    13,    16,     8,     7,    25,    20,     0,     1,
      25,     3,    14,     5,     3,    25,     5,    14,    29,     4,
      25,     6,     7,    20,     0,    10,    11,    12,    13,    21,
      15,    14,    21,    18,    19,    39,    29,    20,    40,    13,
      25,    47,    27,    28,    40,    41,     8,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    44,
      29,    65,    10,    69,    66,    13,    29,    15,    15,    25,
      18,    19,    38,    39,    40,    41,     9,    25,    26,    27,
      28,     8,    10,    65,     1,    13,     3,    15,     5,    39,
      18,    19,     9,    94,    48,    93,    44,    25,    43,    27,
      28,    -1,    -1,    13,    21,    15,    14,    -1,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    44,    27,    28,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    44,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
  };

  const signed char
  SvlmParser::yystos_[] =
  {
       0,     4,     6,     7,    10,    11,    12,    13,    15,    18,
      19,    25,    27,    28,    44,    47,    48,    49,    50,    51,
      54,    55,    56,    57,    58,    59,    60,    25,    25,    25,
      26,    55,    50,    58,    52,    53,    55,    25,    25,    13,
      29,    58,     0,     1,     3,     5,    21,    63,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    13,     8,    14,    16,    20,    29,    52,    58,    63,
      50,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    25,    61,    62,     9,    53,    58,
      14,    50,    14,    20,     8,    62,    49,     9
  };

  const signed char
  SvlmParser::yyr1_[] =
  {
       0,    46,    47,    48,    49,    49,    49,    49,    50,    50,
      50,    50,    50,    50,    50,    50,    51,    52,    52,    52,
      53,    54,    55,    55,    56,    56,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    60,    61,    61,    61,    62,    63,    63,    63
  };

  const signed char
  SvlmParser::yyr2_[] =
  {
       0,     2,     1,     1,     3,     1,     4,     0,     0,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     0,
       1,     4,     1,     1,     2,     2,     3,     1,     1,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     2,     4,     1,     3,     3,
       8,     4,     1,     3,     0,     1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const SvlmParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "EOL", "COMMENT1",
  "COMMENT2", "MODULE", "DEF", "DO", "END", "AST_RETURN", "PRINT", "CASE",
  "PAREN_L", "PAREN_R", "CUR_L", "CUR_R", "AT", "DOLLAR", "COLON", "COMMA",
  "SEMICOLON", "ARROW_R", "ARROW_L", "IDENT_STR", "STR", "DQSTR", "INT",
  "FLT", "ASSIGN", "EQL", "NEQL", "GT", "LT", "GTEQ", "LTEQ", "AND", "OR",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "UMINUS", "NOT",
  "EXPONENT", "$accept", "program_start", "comments", "statement_list",
  "statement", "module", "arg_list", "arg", "caller", "exp", "print_exp",
  "tuple", "exp_num", "function", "case", "param_list", "param", "EOS", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  SvlmParser::yyrline_[] =
  {
       0,    72,    72,    76,    80,    84,    89,    90,    94,    95,
      96,    97,    98,    99,   100,   101,   106,   115,   119,   124,
     128,   134,   142,   143,   147,   148,   153,   156,   157,   158,
     159,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   175,   176,   177,   184,   185,   191,
     198,   216,   234,   239,   243,   250,   258,   259,   260
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
      45
    };
    // Last valid token kind.
    const int code_max = 300;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 14 "svlm_grammar.y"
} // vslast
#line 1730 "svlm_parser.cc"

#line 262 "svlm_grammar.y"


//--------------------------------------------------- EOS end of statement
void vslast::SvlmParser::error(const location_type& l, const std::string& msg) {
    std::cerr << "line "  << l << ": " << msg << '\n';
}
