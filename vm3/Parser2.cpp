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
#line 1 "grammar2.y"

#include <iostream>
#include <string>
#include <cmath>
#include <FlexLexer.h>

#line 48 "Parser2.cpp"


#include "Parser2.hh"


// Unqualified %code blocks.
#line 27 "grammar2.y"

#include "Scanner2.hh"
#define yylex(x) scanner->lex(x)


int line=1, element_count = 0;
instr_t asm_instr = {Opcode(Opcode::NOOP), 0,0,0};
bool skipline=false;
bool element_init = false;
s_int_t call_register=0;

#line 67 "Parser2.cpp"


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

#line 15 "grammar2.y"
namespace vslasm {
#line 141 "Parser2.cpp"

  /// Build a parser object.
  Parser::Parser (Scanner* scanner_yyarg, Assembler* assembler_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      assembler (assembler_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_loadstore_l: // loadstore_l
      case symbol_kind::S_loadstore_g: // loadstore_g
      case symbol_kind::S_opcode: // opcode
        value.copy< Opcode > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_uri_api: // uri_api
      case symbol_kind::S_modfunstr: // modfunstr
      case symbol_kind::S_funlvarstr: // funlvarstr
      case symbol_kind::S_labelstr: // labelstr
      case symbol_kind::S_modvarstr: // modvarstr
        value.copy< full_symbol_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.copy< long double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
      case symbol_kind::S_REGISTER: // REGISTER
      case symbol_kind::S_call_register: // call_register
        value.copy< long int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_g: // array_g
      case symbol_kind::S_element_g: // element_g
      case symbol_kind::S_number: // number
        value.copy< reg_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
      case symbol_kind::S_VSLSTRING: // VSLSTRING
      case symbol_kind::S_DOTSTR: // DOTSTR
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_loadstore_l: // loadstore_l
      case symbol_kind::S_loadstore_g: // loadstore_g
      case symbol_kind::S_opcode: // opcode
        value.move< Opcode > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_uri_api: // uri_api
      case symbol_kind::S_modfunstr: // modfunstr
      case symbol_kind::S_funlvarstr: // funlvarstr
      case symbol_kind::S_labelstr: // labelstr
      case symbol_kind::S_modvarstr: // modvarstr
        value.move< full_symbol_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.move< long double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT: // INT
      case symbol_kind::S_REGISTER: // REGISTER
      case symbol_kind::S_call_register: // call_register
        value.move< long int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_g: // array_g
      case symbol_kind::S_element_g: // element_g
      case symbol_kind::S_number: // number
        value.move< reg_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STR: // STR
      case symbol_kind::S_VSLSTRING: // VSLSTRING
      case symbol_kind::S_DOTSTR: // DOTSTR
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_loadstore_l: // loadstore_l
      case symbol_kind::S_loadstore_g: // loadstore_g
      case symbol_kind::S_opcode: // opcode
        value.YY_MOVE_OR_COPY< Opcode > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_uri_api: // uri_api
      case symbol_kind::S_modfunstr: // modfunstr
      case symbol_kind::S_funlvarstr: // funlvarstr
      case symbol_kind::S_labelstr: // labelstr
      case symbol_kind::S_modvarstr: // modvarstr
        value.YY_MOVE_OR_COPY< full_symbol_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.YY_MOVE_OR_COPY< long double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
      case symbol_kind::S_REGISTER: // REGISTER
      case symbol_kind::S_call_register: // call_register
        value.YY_MOVE_OR_COPY< long int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_g: // array_g
      case symbol_kind::S_element_g: // element_g
      case symbol_kind::S_number: // number
        value.YY_MOVE_OR_COPY< reg_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
      case symbol_kind::S_VSLSTRING: // VSLSTRING
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

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_loadstore_l: // loadstore_l
      case symbol_kind::S_loadstore_g: // loadstore_g
      case symbol_kind::S_opcode: // opcode
        value.move< Opcode > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_uri_api: // uri_api
      case symbol_kind::S_modfunstr: // modfunstr
      case symbol_kind::S_funlvarstr: // funlvarstr
      case symbol_kind::S_labelstr: // labelstr
      case symbol_kind::S_modvarstr: // modvarstr
        value.move< full_symbol_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLT: // FLT
        value.move< long double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
      case symbol_kind::S_REGISTER: // REGISTER
      case symbol_kind::S_call_register: // call_register
        value.move< long int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_g: // array_g
      case symbol_kind::S_element_g: // element_g
      case symbol_kind::S_number: // number
        value.move< reg_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
      case symbol_kind::S_VSLSTRING: // VSLSTRING
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
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_loadstore_l: // loadstore_l
      case symbol_kind::S_loadstore_g: // loadstore_g
      case symbol_kind::S_opcode: // opcode
        value.copy< Opcode > (that.value);
        break;

      case symbol_kind::S_uri_api: // uri_api
      case symbol_kind::S_modfunstr: // modfunstr
      case symbol_kind::S_funlvarstr: // funlvarstr
      case symbol_kind::S_labelstr: // labelstr
      case symbol_kind::S_modvarstr: // modvarstr
        value.copy< full_symbol_t > (that.value);
        break;

      case symbol_kind::S_FLT: // FLT
        value.copy< long double > (that.value);
        break;

      case symbol_kind::S_INT: // INT
      case symbol_kind::S_REGISTER: // REGISTER
      case symbol_kind::S_call_register: // call_register
        value.copy< long int > (that.value);
        break;

      case symbol_kind::S_array_g: // array_g
      case symbol_kind::S_element_g: // element_g
      case symbol_kind::S_number: // number
        value.copy< reg_t > (that.value);
        break;

      case symbol_kind::S_STR: // STR
      case symbol_kind::S_VSLSTRING: // VSLSTRING
      case symbol_kind::S_DOTSTR: // DOTSTR
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_loadstore_l: // loadstore_l
      case symbol_kind::S_loadstore_g: // loadstore_g
      case symbol_kind::S_opcode: // opcode
        value.move< Opcode > (that.value);
        break;

      case symbol_kind::S_uri_api: // uri_api
      case symbol_kind::S_modfunstr: // modfunstr
      case symbol_kind::S_funlvarstr: // funlvarstr
      case symbol_kind::S_labelstr: // labelstr
      case symbol_kind::S_modvarstr: // modvarstr
        value.move< full_symbol_t > (that.value);
        break;

      case symbol_kind::S_FLT: // FLT
        value.move< long double > (that.value);
        break;

      case symbol_kind::S_INT: // INT
      case symbol_kind::S_REGISTER: // REGISTER
      case symbol_kind::S_call_register: // call_register
        value.move< long int > (that.value);
        break;

      case symbol_kind::S_array_g: // array_g
      case symbol_kind::S_element_g: // element_g
      case symbol_kind::S_number: // number
        value.move< reg_t > (that.value);
        break;

      case symbol_kind::S_STR: // STR
      case symbol_kind::S_VSLSTRING: // VSLSTRING
      case symbol_kind::S_DOTSTR: // DOTSTR
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

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
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
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
      case symbol_kind::S_loadstore_l: // loadstore_l
      case symbol_kind::S_loadstore_g: // loadstore_g
      case symbol_kind::S_opcode: // opcode
        yylhs.value.emplace< Opcode > ();
        break;

      case symbol_kind::S_uri_api: // uri_api
      case symbol_kind::S_modfunstr: // modfunstr
      case symbol_kind::S_funlvarstr: // funlvarstr
      case symbol_kind::S_labelstr: // labelstr
      case symbol_kind::S_modvarstr: // modvarstr
        yylhs.value.emplace< full_symbol_t > ();
        break;

      case symbol_kind::S_FLT: // FLT
        yylhs.value.emplace< long double > ();
        break;

      case symbol_kind::S_INT: // INT
      case symbol_kind::S_REGISTER: // REGISTER
      case symbol_kind::S_call_register: // call_register
        yylhs.value.emplace< long int > ();
        break;

      case symbol_kind::S_array_g: // array_g
      case symbol_kind::S_element_g: // element_g
      case symbol_kind::S_number: // number
        yylhs.value.emplace< reg_t > ();
        break;

      case symbol_kind::S_STR: // STR
      case symbol_kind::S_VSLSTRING: // VSLSTRING
      case symbol_kind::S_DOTSTR: // DOTSTR
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 4: // line: EOL
#line 72 "grammar2.y"
        {
    //
    // readline eats newline character. only file scanning will encounter newline char
    // also do not insert directives in to assembly::code[]
    // NOTE:  recursive parsing within a single line do not reach here 
    //        to have the instruction inserted. i.e. module array  [1 2 3 4]
    //
    if(!skipline) // skip assembly %% directives because it's not instruction
      assembler->insert_instruction();  // instruction inserted when parsing a file aka encountering a newline char
    skipline=false;
    line++;
    assembler->line_total_read++;
  }
#line 881 "Parser2.cpp"
    break;

  case 8: // line: COMMENT
#line 88 "grammar2.y"
            { assembler->line_total_read++; }
#line 887 "Parser2.cpp"
    break;

  case 9: // line: EMPTYLINE
#line 89 "grammar2.y"
              { assembler->line_total_read++; }
#line 893 "Parser2.cpp"
    break;

  case 14: // super_instructions: MODULO BRANCH opcode labelstr
#line 97 "grammar2.y"
                                  { 
    std::cout << static_cast<int>(yystack_[1].value.as < Opcode > ()) << "label:" << yystack_[0].value.as < full_symbol_t > ().label << "\n"; 
    s_int_t ladr = assembler->get_sym_addr(key_tok_t::label, yystack_[0].value.as < full_symbol_t > ());
    if(ladr==-1) { assembler->add_unresolved_sym(key_tok_t::label, yystack_[0].value.as < full_symbol_t > ()); }
    asm_instr = {yystack_[1].value.as < Opcode > (), ladr, 0, 0};  
    assembler->set_instruction(asm_instr); 
    }
#line 905 "Parser2.cpp"
    break;

  case 15: // function_call: MODULO CALL modfunstr
#line 108 "grammar2.y"
                          { 
    assembler->super_opfun_set_instruction(Opcode::CALL, yystack_[0].value.as < full_symbol_t > ()); 
    }
#line 913 "Parser2.cpp"
    break;

  case 16: // function_call: MODULO CALL modfunstr call_register param_list
#line 111 "grammar2.y"
                                                   { 
    assembler->super_opfun_set_instruction(Opcode::CALL, yystack_[2].value.as < full_symbol_t > ());
    }
#line 921 "Parser2.cpp"
    break;

  case 17: // var_array_g_decl: MODULO MVAR STR LSBRACKET array_g RSBRACKET
#line 117 "grammar2.y"
                                                 {
    assembler->add_mvar_name(yystack_[3].value.as < std::string > (), 0);  // add mvar name default add + 1,
    assembler->mvc += element_count;  // should add element_count instead
    // need to reset size here
    element_count=0; // reset for for next array
    skipline = true; // insert is done by array_g grammar
  }
#line 933 "Parser2.cpp"
    break;

  case 18: // var_array_g_decl: MODULO MVAR STR INT LSBRACKET RSBRACKET
#line 124 "grammar2.y"
                                             {
    assembler->add_mvar_name(yystack_[3].value.as < std::string > (), yystack_[2].value.as < long int > ());   // don't forget the offset INT
    asm_instr = {Opcode(Opcode::DATA_RESIZE), yystack_[2].value.as < long int > (), 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 943 "Parser2.cpp"
    break;

  case 19: // var_array_g_decl: MODULO MVAR STR INT LSBRACKET array_g RSBRACKET
#line 129 "grammar2.y"
                                                     {
    assembler->add_mvar_name(yystack_[4].value.as < std::string > (), 0);  // add mvar name default add + 1,
    assembler->mvc += element_count;  // should add element_count instead
    int remain_size = yystack_[3].value.as < long int > () - element_count;
    element_count=0; // reset for for next array
    if(remain_size > 0) {
      asm_instr = {Opcode(Opcode::DATA_RESIZE), remain_size, 0, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->mvc += remain_size; 
      skipline = false;
    } else {
      skipline = true; // insert is done by array_g grammar
    }
  }
#line 962 "Parser2.cpp"
    break;

  case 20: // var_decl: MODULO LVAR STR number
#line 146 "grammar2.y"
                             {
    assembler->add_lvar_name(yystack_[1].value.as < std::string > ()); 
    asm_instr = {Opcode(Opcode::PUSH_C), yystack_[0].value.as < reg_t > (), 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 972 "Parser2.cpp"
    break;

  case 21: // var_decl: MODULO MVAR STR
#line 151 "grammar2.y"
                    {
    assembler->add_mvar_name(yystack_[0].value.as < std::string > ());  
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 982 "Parser2.cpp"
    break;

  case 22: // var_decl: MODULO MVAR STR number
#line 156 "grammar2.y"
                           {
    assembler->add_mvar_name(yystack_[1].value.as < std::string > ());  
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, yystack_[0].value.as < reg_t > (), 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 992 "Parser2.cpp"
    break;

  case 23: // var_decl: MODULO MODULO MVAR STR VSLSTRING
#line 161 "grammar2.y"
                                     {
    int i;

    s_int_t l=yystack_[0].value.as < std::string > ().length();
    int mvs = l / sizeof(reg_t);
    int remain = l  % sizeof(reg_t);
    int offset = mvs; if(remain != 0) offset++;

    reg_t block, *bptr=(reg_t *)yystack_[0].value.as < std::string > ().c_str();

    assembler->add_mvar_name(yystack_[1].value.as < std::string > (), offset);  

    std::cout << "mvs: " << mvs << ":" << l  << " string " << yystack_[0].value.as < std::string > () <<  "\n";

    // add size of string first
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, l, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();  

    for(i=0; i<mvs; i++, bptr++) {
      block = *bptr;
      for(int j=0; j<sizeof(s_float_t); j++) std::cout << bptr->c[j]; std::cout << "\n";
      asm_instr = {Opcode(Opcode::DATA_ADD), -1, block, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();  
    }
    if(remain != 0) {
      block = *bptr;
      for(i=0; i<remain; i++) std::cout << block.c[i]; std::cout << "\n";
      for(i=remain; i<sizeof(s_float_t); i++) block.c[i] = 0; // zero all 
      asm_instr = {Opcode(Opcode::DATA_ADD), -1, block, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();  
    }

    skipline = true;
  }
#line 1034 "Parser2.cpp"
    break;

  case 24: // var_access: loadstore_l REGISTER COMMA funlvarstr
#line 201 "grammar2.y"
                                        {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, yystack_[0].value.as < full_symbol_t > ());
    asm_instr = {yystack_[3].value.as < Opcode > (), yystack_[2].value.as < long int > (), Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
  }
#line 1044 "Parser2.cpp"
    break;

  case 25: // var_access: loadstore_g REGISTER COMMA REGISTER COMMA modvarstr
#line 206 "grammar2.y"
                                                        {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, yystack_[0].value.as < full_symbol_t > ());
    asm_instr = {yystack_[5].value.as < Opcode > (), yystack_[4].value.as < long int > (), yystack_[2].value.as < long int > (), vadr};  
    assembler->set_instruction(asm_instr); 
  }
#line 1054 "Parser2.cpp"
    break;

  case 26: // loadstore_l: LOAD_L
#line 214 "grammar2.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::LOAD_L);  }
#line 1060 "Parser2.cpp"
    break;

  case 27: // loadstore_l: STORE_L
#line 215 "grammar2.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::STORE_L); }
#line 1066 "Parser2.cpp"
    break;

  case 28: // loadstore_g: LOAD_G
#line 219 "grammar2.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::LOAD_G);  }
#line 1072 "Parser2.cpp"
    break;

  case 29: // loadstore_g: STORE_G
#line 220 "grammar2.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::STORE_G); }
#line 1078 "Parser2.cpp"
    break;

  case 30: // directive: MODULO MODULO URI uri_api
#line 225 "grammar2.y"
                              { skipline=true;}
#line 1084 "Parser2.cpp"
    break;

  case 31: // directive: MODULO MODULO MODULE DOTSTR
#line 226 "grammar2.y"
                                  {assembler->add_module_name(yystack_[0].value.as < std::string > ()); skipline=true; }
#line 1090 "Parser2.cpp"
    break;

  case 32: // directive: MODULO MODULO FUNCTION STR
#line 227 "grammar2.y"
                                  {assembler->add_function_name(yystack_[0].value.as < std::string > ()); skipline=true;}
#line 1096 "Parser2.cpp"
    break;

  case 33: // directive: MODULO MODULO LABEL STR
#line 228 "grammar2.y"
                                  {assembler->add_label_name(yystack_[0].value.as < std::string > ()); skipline=true;}
#line 1102 "Parser2.cpp"
    break;

  case 34: // directive: MODULO MODULO LARG STR
#line 229 "grammar2.y"
                                  {assembler->add_larg_name(yystack_[0].value.as < std::string > ()); skipline=true;}
#line 1108 "Parser2.cpp"
    break;

  case 35: // uri_api: COLON COLON STR DOT STR
#line 233 "grammar2.y"
                            {
    assembler->add_app_name(yystack_[2].value.as < std::string > ());
    assembler->add_api_name(yystack_[0].value.as < std::string > ());
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    }
#line 1118 "Parser2.cpp"
    break;

  case 36: // DOTSTR: STR
#line 241 "grammar2.y"
    { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1124 "Parser2.cpp"
    break;

  case 37: // DOTSTR: DOTSTR DOT STR
#line 242 "grammar2.y"
                   { yylhs.value.as < std::string > () = yystack_[2].value.as < std::string > () + std::string(".")+ yystack_[0].value.as < std::string > (); }
#line 1130 "Parser2.cpp"
    break;

  case 38: // array_g: element_g
#line 247 "grammar2.y"
    { yylhs.value.as < reg_t > () = yystack_[0].value.as < reg_t > (); }
#line 1136 "Parser2.cpp"
    break;

  case 39: // array_g: array_g element_g
#line 248 "grammar2.y"
    { yylhs.value.as < reg_t > () = yystack_[1].value.as < reg_t > (); }
#line 1142 "Parser2.cpp"
    break;

  case 40: // element_g: number
#line 252 "grammar2.y"
           { 
    //std::cout << $1.i << " "; 
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, yystack_[0].value.as < reg_t > (), 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();
    element_count++;
  }
#line 1154 "Parser2.cpp"
    break;

  case 41: // number: FLT
#line 263 "grammar2.y"
        { yylhs.value.as < reg_t > ().f = yystack_[0].value.as < long double > (); }
#line 1160 "Parser2.cpp"
    break;

  case 42: // number: INT
#line 264 "grammar2.y"
        { yylhs.value.as < reg_t > ().i = yystack_[0].value.as < long int > (); }
#line 1166 "Parser2.cpp"
    break;

  case 43: // call_register: REGISTER
#line 269 "grammar2.y"
             { call_register = yystack_[0].value.as < long int > (); }
#line 1172 "Parser2.cpp"
    break;

  case 46: // param: funlvarstr
#line 279 "grammar2.y"
               {
    //std::cout << "funlvarstr\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, yystack_[0].value.as < full_symbol_t > ());
    asm_instr = {Opcode(Opcode::LOAD_L), call_register, Reg::fp, vadr};
    //std::cout << "vadr: " << vadr << "\n";
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0};
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
  }
#line 1188 "Parser2.cpp"
    break;

  case 47: // param: modvarstr
#line 290 "grammar2.y"
              {
    //std::cout << "modvarstr\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, yystack_[0].value.as < full_symbol_t > ());
    asm_instr = {Opcode(Opcode::LOAD_G), call_register, -1, vadr};
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0};
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
  }
#line 1203 "Parser2.cpp"
    break;

  case 48: // modfunstr: STR
#line 305 "grammar2.y"
        { 
    yylhs.value.as < full_symbol_t > ().smodule = assembler->get_current_context().smodule;
    yylhs.value.as < full_symbol_t > ().mfunction = yystack_[0].value.as < std::string > ();
    }
#line 1212 "Parser2.cpp"
    break;

  case 49: // modfunstr: DOTSTR COLON STR
#line 309 "grammar2.y"
                     { 
    yylhs.value.as < full_symbol_t > ().smodule = yystack_[2].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().mfunction = yystack_[0].value.as < std::string > ();
    }
#line 1221 "Parser2.cpp"
    break;

  case 50: // funlvarstr: STR
#line 316 "grammar2.y"
        { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    yylhs.value.as < full_symbol_t > ().smodule = assembler->get_current_context().smodule;
    yylhs.value.as < full_symbol_t > ().mfunction = assembler->get_current_context().mfunction;
    yylhs.value.as < full_symbol_t > ().lvar = yystack_[0].value.as < std::string > ();
    }
#line 1232 "Parser2.cpp"
    break;

  case 51: // labelstr: STR
#line 325 "grammar2.y"
        { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    yylhs.value.as < full_symbol_t > ().smodule = assembler->get_current_context().smodule;
    yylhs.value.as < full_symbol_t > ().mfunction = assembler->get_current_context().mfunction;
    yylhs.value.as < full_symbol_t > ().label = yystack_[0].value.as < std::string > ();
    }
#line 1243 "Parser2.cpp"
    break;

  case 52: // modvarstr: STR
#line 335 "grammar2.y"
        { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    yylhs.value.as < full_symbol_t > ().smodule = assembler->get_current_context().smodule;
    yylhs.value.as < full_symbol_t > ().mvar = yystack_[0].value.as < std::string > ();
    }
#line 1253 "Parser2.cpp"
    break;

  case 53: // modvarstr: STR COLON STR
#line 340 "grammar2.y"
                  { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    yylhs.value.as < full_symbol_t > ().smodule = yystack_[2].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().mvar = yystack_[0].value.as < std::string > ();
    }
#line 1263 "Parser2.cpp"
    break;

  case 54: // instruction: opcode
#line 348 "grammar2.y"
           { 
    asm_instr = {yystack_[0].value.as < Opcode > (), 0, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 1272 "Parser2.cpp"
    break;

  case 55: // instruction: opcode REGISTER
#line 352 "grammar2.y"
                    { 
    asm_instr = {yystack_[1].value.as < Opcode > (), yystack_[0].value.as < long int > (), 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 1281 "Parser2.cpp"
    break;

  case 56: // instruction: opcode REGISTER COMMA REGISTER
#line 356 "grammar2.y"
                                   {
    asm_instr = {yystack_[3].value.as < Opcode > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < long int > (), 0};
    assembler->set_instruction(asm_instr); 
  }
#line 1290 "Parser2.cpp"
    break;

  case 57: // instruction: opcode REGISTER COMMA REGISTER COMMA REGISTER
#line 360 "grammar2.y"
                                                  {
    asm_instr = {yystack_[5].value.as < Opcode > (), yystack_[4].value.as < long int > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < long int > ()}; 
    assembler->set_instruction(asm_instr); 
  }
#line 1299 "Parser2.cpp"
    break;

  case 58: // instruction: opcode number
#line 364 "grammar2.y"
                  { 
    asm_instr = {yystack_[1].value.as < Opcode > (), yystack_[0].value.as < reg_t > (), 0, 0}; 
    assembler->set_instruction(asm_instr); 
  }
#line 1308 "Parser2.cpp"
    break;

  case 59: // instruction: opcode REGISTER COMMA number
#line 368 "grammar2.y"
                                 { 
    asm_instr = {yystack_[3].value.as < Opcode > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < reg_t > (), 0};
    assembler->set_instruction(asm_instr); 
  }
#line 1317 "Parser2.cpp"
    break;

  case 60: // instruction: opcode REGISTER COMMA REGISTER COMMA number
#line 372 "grammar2.y"
                                                { 
    asm_instr = {yystack_[5].value.as < Opcode > (), yystack_[4].value.as < long int > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < reg_t > ()}; 
    assembler->set_instruction(asm_instr); 
  }
#line 1326 "Parser2.cpp"
    break;

  case 61: // opcode: STR
#line 379 "grammar2.y"
      { 
    yylhs.value.as < Opcode > () = assembler->lookup_opcode(yystack_[0].value.as < std::string > ()); }
#line 1333 "Parser2.cpp"
    break;


#line 1337 "Parser2.cpp"

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
        error (YY_MOVE (msg));
      }


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

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char Parser::yypact_ninf_ = -71;

  const signed char Parser::yytable_ninf_ = -37;

  const signed char
  Parser::yypact_[] =
  {
     -71,     1,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,    -4,   -71,   -71,   -71,   -71,   -71,   -71,   -17,     0,
     -71,   -71,    21,    11,    13,    24,    33,     6,    39,    46,
     -71,   -71,    47,   -71,   -15,   -18,    37,    41,    44,    38,
      42,    43,    45,    48,    49,    51,    50,    52,    23,   -18,
      54,   -71,   -71,   -71,   -71,    53,    55,   -71,    56,   -71,
      59,    57,   -71,   -71,   -71,    61,   -71,   -71,   -71,    63,
      68,   -71,     5,   -71,   -71,    17,   -71,   -71,    69,   -71,
      56,   -71,   -71,   -71,    60,    62,    28,   -71,   -71,   -71,
      19,    64,   -71,    73,    69,   -71,   -71,   -71,   -71,   -71,
      65,   -71
  };

  const signed char
  Parser::yydefact_[] =
  {
       2,     0,     1,     4,     8,     9,    61,    26,    27,    28,
      29,     0,     3,     7,    13,    12,    11,    10,     0,     0,
       6,     5,    54,     0,     0,     0,     0,     0,     0,     0,
      42,    41,    55,    58,    21,     0,     0,    48,     0,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    22,    20,    51,    14,     0,     0,    43,     0,    36,
      31,     0,    32,    33,    34,     0,    30,    50,    24,     0,
      56,    59,     0,    38,    40,     0,    37,    49,    50,    16,
      44,    46,    47,    23,     0,     0,     0,    17,    39,    18,
       0,     0,    45,     0,    52,    25,    57,    60,    19,    53,
       0,    35
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,    25,    -5,   -70,   -22,   -71,     9,   -71,   -71,
      58,   -71,     7,   -71,    70
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    66,    38,    72,    73,    74,    58,    79,    80,    39,
      81,    54,    82,    21,    22
  };

  const signed char
  Parser::yytable_[] =
  {
      33,     2,    88,    49,     3,    23,    30,    31,    24,    50,
      31,    28,    51,    52,    40,    41,    42,    43,    25,    44,
      88,     4,     5,    45,    87,    26,    71,     6,    29,    30,
      31,     7,     8,     9,    10,    27,    89,    34,    98,    35,
      11,    30,    31,    30,    31,    30,    31,    30,    31,    32,
       6,    70,    30,    31,    46,   -36,    96,   -36,    55,    37,
      56,    47,    48,    53,    97,    60,    57,    65,    59,    61,
      90,    62,    75,    55,    63,    64,    67,    84,    85,    76,
      69,    77,    78,    86,    83,    91,    93,   100,    94,    92,
      99,   101,    95,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,    68
  };

  const signed char
  Parser::yycheck_[] =
  {
      22,     0,    72,    18,     3,     9,    24,    25,    12,    24,
      25,    28,    34,    35,     8,     9,    10,    11,    22,    13,
      90,    20,    21,    17,    19,    29,    48,    26,    28,    24,
      25,    30,    31,    32,    33,    39,    19,    26,    19,    26,
      39,    24,    25,    24,    25,    24,    25,    24,    25,    28,
      26,    28,    24,    25,    15,    14,    28,    16,    14,    26,
      16,    15,    15,    26,    86,    40,    28,    16,    26,    26,
      75,    26,    18,    14,    26,    26,    26,    16,    15,    26,
      28,    26,    26,    15,    27,    16,    26,    14,    26,    80,
      26,    26,    85,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    44,     0,     3,    20,    21,    26,    30,    31,    32,
      33,    39,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    66,    67,     9,    12,    22,    29,    39,    28,    28,
      24,    25,    28,    58,    26,    26,    67,    26,    55,    62,
       8,     9,    10,    11,    13,    17,    15,    15,    15,    18,
      24,    58,    58,    26,    64,    14,    16,    28,    59,    26,
      55,    26,    26,    26,    26,    16,    54,    26,    63,    28,
      28,    58,    56,    57,    58,    18,    26,    26,    26,    60,
      61,    63,    65,    27,    16,    15,    15,    19,    57,    19,
      56,    16,    60,    26,    26,    65,    28,    58,    19,    26,
      14,    26
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    43,    44,    44,    45,    45,    45,    45,    45,    45,
      46,    46,    46,    46,    46,    47,    47,    48,    48,    48,
      49,    49,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    53,    53,    53,    54,    55,    55,    56,    56,
      57,    58,    58,    59,    60,    60,    61,    61,    62,    62,
      63,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    67
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     5,     6,     6,     7,
       4,     3,     4,     5,     4,     6,     1,     1,     1,     1,
       4,     4,     4,     4,     4,     5,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     2,     4,     6,     2,     4,
       6,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "EOL", "LPAREN",
  "RPAREN", "APP", "API", "MODULE", "MVAR", "FUNCTION", "LABEL", "LVAR",
  "LARG", "DOT", "COMMA", "COLON", "URI", "LSBRACKET", "RSBRACKET",
  "COMMENT", "EMPTYLINE", "BRANCH", "TEXT", "INT", "FLT", "STR",
  "VSLSTRING", "REGISTER", "CALL", "LOAD_L", "STORE_L", "LOAD_G",
  "STORE_G", "ASSIGN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO",
  "UMINUS", "FACTORIAL", "EXPONENT", "$accept", "lines", "line",
  "super_instructions", "function_call", "var_array_g_decl", "var_decl",
  "var_access", "loadstore_l", "loadstore_g", "directive", "uri_api",
  "DOTSTR", "array_g", "element_g", "number", "call_register",
  "param_list", "param", "modfunstr", "funlvarstr", "labelstr",
  "modvarstr", "instruction", "opcode", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,    67,    67,    68,    72,    85,    86,    87,    88,    89,
      93,    94,    95,    96,    97,   108,   111,   117,   124,   129,
     146,   151,   156,   161,   201,   206,   214,   215,   219,   220,
     225,   226,   227,   228,   229,   233,   241,   242,   247,   248,
     252,   263,   264,   269,   274,   275,   279,   290,   305,   309,
     316,   325,   335,   340,   348,   352,   356,   360,   364,   368,
     372,   379
  };

  void
  Parser::yy_stack_print_ () const
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
  Parser::yy_reduce_print_ (int yyrule) const
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

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    return static_cast<symbol_kind_type> (t);
  }

#line 15 "grammar2.y"
} // vslasm
#line 1721 "Parser2.cpp"

#line 383 "grammar2.y"

// directive: EOL ;

void vslasm::Parser::error(const std::string& msg) {
  std::cerr << msg + " on line: " << line << "\n";
}
