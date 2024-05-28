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
#line 1 "asm_grammar.y"

#include <iostream>
#include <string>
#include <cmath>

#line 47 "asm_parser.cc"


#include "asm_parser.hh"


// Unqualified %code blocks.
#line 26 "asm_grammar.y"

#include "asm_scanner.hh"
#define yylex(x) asm_scanner->lex(x)


int line=0, element_count = 0;
instr_t asm_instr = {Opcode(Opcode::NOOP), 0,0,0};
bool skipline=false;
bool element_init = false;
s_int_t call_register=0;
bool array_init = true;

#line 67 "asm_parser.cc"


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

#line 14 "asm_grammar.y"
namespace vslasm {
#line 141 "asm_parser.cc"

  /// Build a parser object.
  AsmParser::AsmParser (AsmScanner* asm_scanner_yyarg, Assembler* assembler_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      asm_scanner (asm_scanner_yyarg),
      assembler (assembler_yyarg)
  {}

  AsmParser::~AsmParser ()
  {}

  AsmParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  AsmParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
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
  AsmParser::symbol_kind_type
  AsmParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  AsmParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  AsmParser::basic_symbol<Base>::move (basic_symbol& s)
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
  AsmParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  AsmParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  AsmParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  AsmParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  AsmParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  AsmParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  AsmParser::symbol_kind_type
  AsmParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  AsmParser::symbol_kind_type
  AsmParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  AsmParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  AsmParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  AsmParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  AsmParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  AsmParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  AsmParser::symbol_kind_type
  AsmParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  AsmParser::stack_symbol_type::stack_symbol_type ()
  {}

  AsmParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
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

  AsmParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
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
  AsmParser::stack_symbol_type&
  AsmParser::stack_symbol_type::operator= (const stack_symbol_type& that)
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

  AsmParser::stack_symbol_type&
  AsmParser::stack_symbol_type::operator= (stack_symbol_type& that)
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
  AsmParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  AsmParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  AsmParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  AsmParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  AsmParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  AsmParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  AsmParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  AsmParser::debug_level_type
  AsmParser::debug_level () const
  {
    return yydebug_;
  }

  void
  AsmParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  AsmParser::state_type
  AsmParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  AsmParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  AsmParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  AsmParser::operator() ()
  {
    return parse ();
  }

  int
  AsmParser::parse ()
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
#line 73 "asm_grammar.y"
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
#line 881 "asm_parser.cc"
    break;

  case 9: // line: EMPTYLINE
#line 90 "asm_grammar.y"
              { assembler->line_total_read++;  line++;}
#line 887 "asm_parser.cc"
    break;

  case 15: // comments: COMMENT1
#line 105 "asm_grammar.y"
             { assembler->line_total_read++; line++; }
#line 893 "asm_parser.cc"
    break;

  case 16: // comments: COMMENT2
#line 106 "asm_grammar.y"
             {  // this comment is at the end of the instruction 
    if(!skipline) // skip assembly %% directives because it's not instruction
      assembler->insert_instruction();  // instruction inserted when parsing a file aka encountering a newline char
    skipline=false;
    assembler->line_total_read++; line++; 
    }
#line 904 "asm_parser.cc"
    break;

  case 17: // move_address: MODULO MOV_MV_ADR REGISTER COMMA modvarstr
#line 115 "asm_grammar.y"
                                               {
    //std::cout << "moving mf" << $3 << " " << $5.mfunction << "\n";
    //std::cout << "moving mv" << $3 << " " << $5.mvar << "\n";
    //std::cout << "type " << $3 << " " << static_cast<int>($5.type) << "\n";
    key_tok_t kkt_type = yystack_[0].value.as < full_symbol_t > ().type;
    s_int_t madr = assembler->get_sym_addr(kkt_type, yystack_[0].value.as < full_symbol_t > ());
    if(madr==-1) { assembler->add_unresolved_sym(kkt_type, yystack_[0].value.as < full_symbol_t > (), 1); }
    asm_instr = {Opcode(Opcode::MOV), yystack_[2].value.as < long int > (), madr, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 919 "asm_parser.cc"
    break;

  case 18: // branch_call: MODULO BRANCH opcode labelstr
#line 128 "asm_grammar.y"
                                  { 
    // std::cout << static_cast<int>($3) << "label:" << $4.label << "\n"; 
    s_int_t ladr = assembler->get_sym_addr(key_tok_t::label, yystack_[0].value.as < full_symbol_t > ());
    if(ladr==-1) { assembler->add_unresolved_sym(key_tok_t::label, yystack_[0].value.as < full_symbol_t > ()); }
    asm_instr = {yystack_[1].value.as < Opcode > (), ladr, 0, 0};  
    assembler->set_instruction(asm_instr); 
    }
#line 931 "asm_parser.cc"
    break;

  case 19: // function_call: MODULO CALL modfunstr
#line 139 "asm_grammar.y"
                          { 
    assembler->super_opfun_set_instruction(Opcode::CALL, yystack_[0].value.as < full_symbol_t > ()); 
    }
#line 939 "asm_parser.cc"
    break;

  case 20: // function_call: MODULO CALL modfunstr call_register param_list
#line 142 "asm_grammar.y"
                                                   { 
    assembler->super_opfun_set_instruction(Opcode::CALL, yystack_[2].value.as < full_symbol_t > ());
    }
#line 947 "asm_parser.cc"
    break;

  case 25: // var_decl_l: MODULO LVAR STR number
#line 157 "asm_grammar.y"
                             {
    assembler->add_lvar_name(yystack_[1].value.as < std::string > ()); 
    asm_instr = {Opcode(Opcode::PUSH_C), yystack_[0].value.as < reg_t > (), 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 957 "asm_parser.cc"
    break;

  case 26: // var_array_l_decl: MODULO LVAR STR INT LSBRACKET RSBRACKET
#line 165 "asm_grammar.y"
                                             {
    asm_instr = {Opcode(Opcode::PUSH_C), yystack_[2].value.as < long int > (), 0, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();  

    assembler->add_lvar_name(yystack_[3].value.as < std::string > (), yystack_[2].value.as < long int > ()+1);   // don't forget the offset INT to include size
    asm_instr = {Opcode(Opcode::STACK_RESIZE), yystack_[2].value.as < long int > (), 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 971 "asm_parser.cc"
    break;

  case 27: // var_decl_m: MODULO MVAR STR
#line 179 "asm_grammar.y"
                    {
    assembler->add_mvar_name(yystack_[0].value.as < std::string > ());  
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 981 "asm_parser.cc"
    break;

  case 28: // var_decl_m: MODULO MVAR STR number
#line 184 "asm_grammar.y"
                           {
    assembler->add_mvar_name(yystack_[1].value.as < std::string > ());  
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, yystack_[0].value.as < reg_t > (), 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 991 "asm_parser.cc"
    break;

  case 29: // var_decl_m: MODULO MVAR STR VSLSTRING
#line 189 "asm_grammar.y"
                              {
    int i;

    s_int_t l=yystack_[0].value.as < std::string > ().length();
    int mvs = l / sizeof(reg_t);
    int remain = l  % sizeof(reg_t);
    int offset = mvs; if(remain != 0) offset++;

    reg_t block, *bptr=(reg_t *)yystack_[0].value.as < std::string > ().c_str();

    // std::cout << "mvs: " << mvs <<  " offset: " << offset << " length" << l  << " string " << $4 <<  "\n";

    assembler->add_mvar_name(yystack_[1].value.as < std::string > (), offset+2);   // add size of array and string + 2 
    // add size of array first
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, offset, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();  
    // add size of string second
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, l, 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();  

    for(i=0; i<mvs; i++, bptr++) {
      block = *bptr;
      //for(int j=0; j<sizeof(s_float_t); j++) std::cout << bptr->c[j]; std::cout << "\n";
      asm_instr = {Opcode(Opcode::DATA_ADD), -1, block, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();  
    }
    if(remain != 0) {
      block = *bptr;
      //for(i=1; i<remain; i++) std::cout << block.c[i]; std::cout << "\n";
      for(i=remain; i<sizeof(s_float_t); i++) block.c[i] = 0; // zero all 
      asm_instr = {Opcode(Opcode::DATA_ADD), -1, block, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();  
    }

    skipline = true;
  }
#line 1036 "asm_parser.cc"
    break;

  case 30: // var_array_g_decl: MODULO MVAR STR INT LSBRACKET array_g RSBRACKET
#line 233 "asm_grammar.y"
                                                     {
  // : var_m_decl LSBRACKET array_g RSBRACKET  {
    int madr = assembler->add_mvar_name(yystack_[4].value.as < std::string > (), 1);  // add mvar name default add + 1,

    reg_t ec; ec.i = element_count;
    if(yystack_[3].value.as < long int > () > element_count) ec.i = yystack_[3].value.as < long int > ();

    assembler->mvc += element_count;  // should add element_count instead
    assembler->set_dataseg_adr_value(madr, ec);

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
    array_init = true;
  }
#line 1063 "asm_parser.cc"
    break;

  case 31: // var_access: loadstore_l REGISTER COMMA funlvarstr
#line 259 "asm_grammar.y"
                                        {
    //std::cout << "lvar: " << $4.lvar << "\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::lvar, yystack_[0].value.as < full_symbol_t > ());
    asm_instr = {yystack_[3].value.as < Opcode > (), yystack_[2].value.as < long int > (), Reg::fp, vadr};  
    assembler->set_instruction(asm_instr); 
  }
#line 1074 "asm_parser.cc"
    break;

  case 32: // var_access: loadstore_g REGISTER COMMA REGISTER COMMA modvarstr
#line 265 "asm_grammar.y"
                                                        {
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, yystack_[0].value.as < full_symbol_t > ());
    asm_instr = {yystack_[5].value.as < Opcode > (), yystack_[4].value.as < long int > (), yystack_[2].value.as < long int > (), vadr};  
    assembler->set_instruction(asm_instr); 
  }
#line 1084 "asm_parser.cc"
    break;

  case 33: // loadstore_l: LOAD_L
#line 273 "asm_grammar.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::LOAD_L);  }
#line 1090 "asm_parser.cc"
    break;

  case 34: // loadstore_l: STORE_L
#line 274 "asm_grammar.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::STORE_L); }
#line 1096 "asm_parser.cc"
    break;

  case 35: // loadstore_g: LOAD_G
#line 278 "asm_grammar.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::LOAD_G);  }
#line 1102 "asm_parser.cc"
    break;

  case 36: // loadstore_g: STORE_G
#line 279 "asm_grammar.y"
            {yylhs.value.as < Opcode > () = Opcode(Opcode::STORE_G); }
#line 1108 "asm_parser.cc"
    break;

  case 37: // directive: MODULO MODULO URI uri_api
#line 284 "asm_grammar.y"
                              { skipline=true;}
#line 1114 "asm_parser.cc"
    break;

  case 38: // directive: MODULO MODULO MODULE DOTSTR
#line 285 "asm_grammar.y"
                                  {assembler->add_module_name(yystack_[0].value.as < std::string > ()); skipline=true; }
#line 1120 "asm_parser.cc"
    break;

  case 39: // directive: MODULO MODULO FUNCTION STR
#line 286 "asm_grammar.y"
                                  {assembler->add_function_name(yystack_[0].value.as < std::string > ()); skipline=true;}
#line 1126 "asm_parser.cc"
    break;

  case 40: // directive: MODULO MODULO LABEL STR
#line 287 "asm_grammar.y"
                                  {assembler->add_label_name(yystack_[0].value.as < std::string > ()); skipline=true;}
#line 1132 "asm_parser.cc"
    break;

  case 41: // directive: MODULO MODULO LARG STR
#line 288 "asm_grammar.y"
                                  {assembler->add_larg_name(yystack_[0].value.as < std::string > ()); skipline=true;}
#line 1138 "asm_parser.cc"
    break;

  case 42: // uri_api: COLON COLON STR DOT STR
#line 292 "asm_grammar.y"
                            {
    assembler->add_app_name(yystack_[2].value.as < std::string > ());
    assembler->add_api_name(yystack_[0].value.as < std::string > ());
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    }
#line 1148 "asm_parser.cc"
    break;

  case 43: // DOTSTR: STR
#line 300 "asm_grammar.y"
    { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1154 "asm_parser.cc"
    break;

  case 44: // DOTSTR: DOTSTR DOT STR
#line 301 "asm_grammar.y"
                   { yylhs.value.as < std::string > () = yystack_[2].value.as < std::string > () + std::string(".")+ yystack_[0].value.as < std::string > (); }
#line 1160 "asm_parser.cc"
    break;

  case 45: // array_g: %empty
#line 306 "asm_grammar.y"
           {
    if(array_init) { // set up size of array at initialization
       asm_instr = {Opcode(Opcode::DATA_ADD), -1, -1, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();
      array_init = false;
    }
  }
#line 1173 "asm_parser.cc"
    break;

  case 46: // array_g: element_g
#line 314 "asm_grammar.y"
    { yylhs.value.as < reg_t > () = yystack_[0].value.as < reg_t > (); }
#line 1179 "asm_parser.cc"
    break;

  case 47: // array_g: array_g element_g
#line 315 "asm_grammar.y"
    { yylhs.value.as < reg_t > () = yystack_[1].value.as < reg_t > (); }
#line 1185 "asm_parser.cc"
    break;

  case 48: // element_g: number
#line 319 "asm_grammar.y"
           { 
    if(array_init) { // set up size of array at initialization
       asm_instr = {Opcode(Opcode::DATA_ADD), -1, -1, 0};  
      assembler->set_instruction(asm_instr); 
      assembler->insert_instruction();
      array_init = false;
    }
    asm_instr = {Opcode(Opcode::DATA_ADD), -1, yystack_[0].value.as < reg_t > (), 0};  
    assembler->set_instruction(asm_instr); 
    assembler->insert_instruction();
    element_count++;
  }
#line 1202 "asm_parser.cc"
    break;

  case 49: // number: FLT
#line 335 "asm_grammar.y"
        { yylhs.value.as < reg_t > ().f = yystack_[0].value.as < long double > (); }
#line 1208 "asm_parser.cc"
    break;

  case 50: // number: INT
#line 336 "asm_grammar.y"
        { yylhs.value.as < reg_t > ().i = yystack_[0].value.as < long int > (); }
#line 1214 "asm_parser.cc"
    break;

  case 51: // call_register: REGISTER
#line 341 "asm_grammar.y"
             { call_register = yystack_[0].value.as < long int > (); }
#line 1220 "asm_parser.cc"
    break;

  case 54: // param: funlvarstr
#line 351 "asm_grammar.y"
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
#line 1236 "asm_parser.cc"
    break;

  case 55: // param: modvarstr
#line 362 "asm_grammar.y"
              {
    //std::cout << "modvarstr\n";
    s_int_t vadr = assembler->get_sym_addr(key_tok_t::mvar, yystack_[0].value.as < full_symbol_t > ());
    if(vadr==-1) { assembler->add_unresolved_sym(key_tok_t::mvar, yystack_[0].value.as < full_symbol_t > ()); } // if symbol is not found
    asm_instr = {Opcode(Opcode::LOAD_G), call_register, -1, vadr}; // load from data seg into register
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
    asm_instr = {Opcode(Opcode::PUSH_R), call_register, 0, 0};     // pushed register to stack to be used as arg
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();
  }
#line 1252 "asm_parser.cc"
    break;

  case 56: // param: REGISTER
#line 373 "asm_grammar.y"
             {
    asm_instr = {Opcode(Opcode::PUSH_R), yystack_[0].value.as < long int > (), 0, 0};
    assembler->set_instruction(asm_instr);
    assembler->insert_instruction();

  }
#line 1263 "asm_parser.cc"
    break;

  case 57: // modfunstr: STR
#line 384 "asm_grammar.y"
        { 
    yylhs.value.as < full_symbol_t > ().smodule = assembler->get_current_context().smodule;
    yylhs.value.as < full_symbol_t > ().mfunction = yystack_[0].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().type = key_tok_t::mfunction;
    }
#line 1273 "asm_parser.cc"
    break;

  case 58: // modfunstr: DOTSTR COLON STR
#line 389 "asm_grammar.y"
                     { 
    yylhs.value.as < full_symbol_t > ().smodule = yystack_[2].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().mfunction = yystack_[0].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().type = key_tok_t::mfunction;
    }
#line 1283 "asm_parser.cc"
    break;

  case 59: // funlvarstr: STR
#line 397 "asm_grammar.y"
        { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    //$$.smodule = assembler->get_current_context().smodule;
    //$$.mfunction = assembler->get_current_context().mfunction;
    yylhs.value.as < full_symbol_t > ().type = key_tok_t::lvar;
    yylhs.value.as < full_symbol_t > ().lvar = yystack_[0].value.as < std::string > ();
    }
#line 1295 "asm_parser.cc"
    break;

  case 60: // labelstr: STR
#line 407 "asm_grammar.y"
        { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    //$$.smodule = assembler->get_current_context().smodule;
    //$$.mfunction = assembler->get_current_context().mfunction;
    yylhs.value.as < full_symbol_t > ().label = yystack_[0].value.as < std::string > ();
    }
#line 1306 "asm_parser.cc"
    break;

  case 61: // modvarstr: AT STR
#line 417 "asm_grammar.y"
           { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    //$$.smodule = assembler->get_current_context().smodule;
    yylhs.value.as < full_symbol_t > ().mvar = yystack_[0].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().type = key_tok_t::mvar;
    }
#line 1317 "asm_parser.cc"
    break;

  case 62: // modvarstr: STR COLON STR
#line 423 "asm_grammar.y"
                  { 
    yylhs.value.as < full_symbol_t > () = assembler->get_current_context();
    yylhs.value.as < full_symbol_t > ().smodule = yystack_[2].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().mvar = yystack_[0].value.as < std::string > ();
    yylhs.value.as < full_symbol_t > ().type = key_tok_t::mvar;
    }
#line 1328 "asm_parser.cc"
    break;

  case 63: // instruction: opcode
#line 432 "asm_grammar.y"
           { 
    asm_instr = {yystack_[0].value.as < Opcode > (), 0, 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 1337 "asm_parser.cc"
    break;

  case 64: // instruction: opcode REGISTER
#line 436 "asm_grammar.y"
                    { 
    asm_instr = {yystack_[1].value.as < Opcode > (), yystack_[0].value.as < long int > (), 0, 0};  
    assembler->set_instruction(asm_instr); 
  }
#line 1346 "asm_parser.cc"
    break;

  case 65: // instruction: opcode REGISTER COMMA REGISTER
#line 440 "asm_grammar.y"
                                   {
    asm_instr = {yystack_[3].value.as < Opcode > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < long int > (), 0};
    assembler->set_instruction(asm_instr); 
  }
#line 1355 "asm_parser.cc"
    break;

  case 66: // instruction: opcode REGISTER COMMA REGISTER COMMA REGISTER
#line 444 "asm_grammar.y"
                                                  {
    asm_instr = {yystack_[5].value.as < Opcode > (), yystack_[4].value.as < long int > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < long int > ()}; 
    assembler->set_instruction(asm_instr); 
  }
#line 1364 "asm_parser.cc"
    break;

  case 67: // instruction: opcode number
#line 448 "asm_grammar.y"
                  { 
    asm_instr = {yystack_[1].value.as < Opcode > (), yystack_[0].value.as < reg_t > (), 0, 0}; 
    assembler->set_instruction(asm_instr); 
  }
#line 1373 "asm_parser.cc"
    break;

  case 68: // instruction: opcode REGISTER COMMA number
#line 452 "asm_grammar.y"
                                 { 
    asm_instr = {yystack_[3].value.as < Opcode > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < reg_t > (), 0};
    assembler->set_instruction(asm_instr); 
  }
#line 1382 "asm_parser.cc"
    break;

  case 69: // instruction: opcode REGISTER COMMA REGISTER COMMA number
#line 456 "asm_grammar.y"
                                                { 
    asm_instr = {yystack_[5].value.as < Opcode > (), yystack_[4].value.as < long int > (), yystack_[2].value.as < long int > (), yystack_[0].value.as < reg_t > ()}; 
    assembler->set_instruction(asm_instr); 
  }
#line 1391 "asm_parser.cc"
    break;

  case 70: // opcode: STR
#line 463 "asm_grammar.y"
      { 
    yylhs.value.as < Opcode > () = assembler->lookup_opcode(yystack_[0].value.as < std::string > ()); }
#line 1398 "asm_parser.cc"
    break;


#line 1402 "asm_parser.cc"

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
  AsmParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  AsmParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char AsmParser::yypact_ninf_ = -62;

  const signed char AsmParser::yytable_ninf_ = -44;

  const signed char
  AsmParser::yypact_[] =
  {
     -62,     1,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,     7,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -13,    -7,   -62,   -62,    -5,
       0,     4,    13,    14,    21,    -2,    49,    50,   -62,   -62,
      51,   -62,    27,    31,    37,    54,    -4,    26,    38,    39,
      41,    42,    43,    59,    45,    44,    20,    11,   -62,   -62,
      60,   -62,   -62,   -62,   -26,    48,    52,   -62,    15,   -62,
      66,   -62,   -62,   -62,    65,   -62,   -62,   -62,    67,    69,
     -62,    33,    68,    55,    72,   -62,   -62,   -62,    72,   -62,
     -62,    15,   -62,   -62,    58,   -26,    25,   -12,   -62,   -62,
     -62,   -62,    61,   -62,    71,   -62,   -62,   -62,   -62,   -62,
     -62,    62,   -62
  };

  const signed char
  AsmParser::yydefact_[] =
  {
       2,     0,     1,     4,    15,    16,     9,    70,    33,    34,
      35,    36,     0,     3,     8,     5,    14,    13,    12,    11,
      21,    24,    22,    23,    10,     0,     0,     7,     6,    63,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    49,
      64,    67,    27,     0,     0,     0,    57,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    29,    28,
      50,    25,    60,    18,     0,     0,     0,    51,     0,    43,
      38,    39,    40,    41,     0,    37,    59,    31,     0,    65,
      68,    45,     0,     0,     0,    17,    44,    58,    59,    56,
      20,    52,    54,    55,     0,     0,     0,     0,    46,    48,
      26,    61,     0,    53,     0,    32,    66,    69,    30,    47,
      62,     0,    42
  };

  const signed char
  AsmParser::yypgoto_[] =
  {
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,    46,   -62,
      -6,   -29,   -62,    -1,   -62,   -62,    40,   -62,   -61,   -62,
      64
  };

  const signed char
  AsmParser::yydefgoto_[] =
  {
       0,     1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    75,    47,    97,
      98,    99,    68,    90,    91,    48,    92,    63,    93,    28,
      29
  };

  const signed char
  AsmParser::yytable_[] =
  {
      41,     2,    83,    85,     3,    84,    49,   108,    50,    51,
     -43,    52,   -43,    59,    61,    53,    30,    38,    39,    31,
      36,     4,     5,     6,    38,    39,    37,    80,    40,    81,
      32,    42,     7,    33,   105,    43,     8,     9,    10,    11,
      65,    34,    66,    83,     7,    12,    88,    45,    89,    38,
      39,    35,    46,    79,    38,    39,    57,    39,   106,    58,
      60,    39,    38,    39,    54,    55,    56,   107,    62,    64,
      69,    67,    71,    72,    73,    74,    76,    78,    82,    86,
      65,    94,    95,    87,    96,   111,   101,   100,   102,   104,
     103,   109,   110,   112,    77,    70,    44
  };

  const signed char
  AsmParser::yycheck_[] =
  {
      29,     0,    28,    64,     3,    31,     8,    19,    10,    11,
      14,    13,    16,    42,    43,    17,     9,    29,    30,    12,
      33,    20,    21,    22,    29,    30,    33,    56,    33,    18,
      23,    31,    31,    26,    95,    31,    35,    36,    37,    38,
      14,    34,    16,    28,    31,    44,    31,    33,    33,    29,
      30,    44,    31,    33,    29,    30,    29,    30,    33,    32,
      29,    30,    29,    30,    15,    15,    15,    96,    31,    15,
      31,    33,    31,    31,    31,    16,    31,    33,    18,    31,
      14,    16,    15,    31,    15,    14,    31,    19,    16,    31,
      91,    97,    31,    31,    54,    49,    32
  };

  const signed char
  AsmParser::yystos_[] =
  {
       0,    49,     0,     3,    20,    21,    22,    31,    35,    36,
      37,    38,    44,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    77,    78,
       9,    12,    23,    26,    34,    44,    33,    33,    29,    30,
      33,    69,    31,    31,    78,    33,    31,    66,    73,     8,
      10,    11,    13,    17,    15,    15,    15,    29,    32,    69,
      29,    69,    31,    75,    15,    14,    16,    33,    70,    31,
      66,    31,    31,    31,    16,    65,    31,    74,    33,    33,
      69,    18,    18,    28,    31,    76,    31,    31,    31,    33,
      71,    72,    74,    76,    16,    15,    15,    67,    68,    69,
      19,    31,    16,    71,    31,    76,    33,    69,    19,    68,
      31,    14,    31
  };

  const signed char
  AsmParser::yyr1_[] =
  {
       0,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    51,    51,    52,    52,    53,    54,    55,
      55,    56,    56,    56,    56,    57,    58,    59,    59,    59,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    65,    66,    66,    67,    67,    67,    68,    69,
      69,    70,    71,    71,    72,    72,    72,    73,    73,    74,
      75,    76,    76,    77,    77,    77,    77,    77,    77,    77,
      78
  };

  const signed char
  AsmParser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     4,     3,
       5,     1,     1,     1,     1,     4,     6,     3,     4,     4,
       7,     4,     6,     1,     1,     1,     1,     4,     4,     4,
       4,     4,     5,     1,     3,     0,     1,     2,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     3,     1,
       1,     2,     3,     1,     2,     4,     6,     2,     4,     6,
       1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const AsmParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "EOL", "LPAREN",
  "RPAREN", "APP", "API", "MODULE", "MVAR", "FUNCTION", "LABEL", "LVAR",
  "LARG", "DOT", "COMMA", "COLON", "URI", "LSBRACKET", "RSBRACKET",
  "COMMENT1", "COMMENT2", "EMPTYLINE", "BRANCH", "TEXT", "MOV_MF_ADR",
  "MOV_MV_ADR", "MOV_L_ADR", "AT", "INT", "FLT", "STR", "VSLSTRING",
  "REGISTER", "CALL", "LOAD_L", "STORE_L", "LOAD_G", "STORE_G", "ASSIGN",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "UMINUS", "FACTORIAL",
  "EXPONENT", "$accept", "lines", "line", "super_instructions", "comments",
  "move_address", "branch_call", "function_call", "var_decl", "var_decl_l",
  "var_array_l_decl", "var_decl_m", "var_array_g_decl", "var_access",
  "loadstore_l", "loadstore_g", "directive", "uri_api", "DOTSTR",
  "array_g", "element_g", "number", "call_register", "param_list", "param",
  "modfunstr", "funlvarstr", "labelstr", "modvarstr", "instruction",
  "opcode", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  AsmParser::yyrline_[] =
  {
       0,    68,    68,    69,    73,    86,    87,    88,    89,    90,
      97,    98,    99,   100,   101,   105,   106,   115,   128,   139,
     142,   149,   150,   151,   152,   157,   165,   179,   184,   189,
     233,   259,   265,   273,   274,   278,   279,   284,   285,   286,
     287,   288,   292,   300,   301,   306,   314,   315,   319,   335,
     336,   341,   346,   347,   351,   362,   373,   384,   389,   397,
     407,   417,   423,   432,   436,   440,   444,   448,   452,   456,
     463
  };

  void
  AsmParser::yy_stack_print_ () const
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
  AsmParser::yy_reduce_print_ (int yyrule) const
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

  AsmParser::symbol_kind_type
  AsmParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    return static_cast<symbol_kind_type> (t);
  }

#line 14 "asm_grammar.y"
} // vslasm
#line 1794 "asm_parser.cc"

#line 467 "asm_grammar.y"

// directive: EOL ;

void vslasm::AsmParser::error(const std::string& msg) {
  std::cerr << msg + " on line: " << line << "\n";
}
