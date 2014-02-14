/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 6 "parse.yy"

	#include <iostream>
	using namespace std;

	#include <stdio.h>
	#include <stdlib.h>
	#include <stddef.h>

	#include "AST.h"
	#include "Type.h"

	//this routine is in scan.ll
	int getCurrentSourceLineNumber();

	// type module is in main.cxx
	extern TypeModule* types;

	// dump variables are in main.cxx
	extern bool before;
	extern bool after;
	extern bool errors;

	void yyerror(const char*);
	extern int yyparse(void);
	extern int yylex(void);


/* Line 268 of yacc.c  */
#line 99 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INT = 259,
     INTEGER_LITERAL = 260,
     MAIN = 261,
     EQ_OP = 262,
     OUT = 263,
     IF = 264,
     ELSE = 265,
     WHILE = 266,
     RETURN = 267,
     BREAK = 268,
     CONTINUE = 269,
     NULL_LITERAL = 270,
     CLASS = 271,
     EXTENDS = 272,
     NEW = 273,
     FIELD_REF = 274,
     THIS = 275,
     SUPER = 276,
     DELETE = 277,
     BAD = 278
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define INT 259
#define INTEGER_LITERAL 260
#define MAIN 261
#define EQ_OP 262
#define OUT 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define NULL_LITERAL 270
#define CLASS 271
#define EXTENDS 272
#define NEW 273
#define FIELD_REF 274
#define THIS 275
#define SUPER 276
#define DELETE 277
#define BAD 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 33 "parse.yy"
 //types of semantic values
       int value;
       char* str;
       AST_Program* program;
       AST_MainFunction* mainFunction;
       AST_StatementList* statementList;
       AST_VarList* varList;
       AST_Statement* statement;
       AST_Declaration* declaration;
       AST_Block* block;
       AST_OutStatement* outStatement;
       AST_ExpressionStatement* expStatement;
       AST_WhileStatement* whileStatement;
       AST_ReturnStatement* returnStatement;
       AST_IfThenElseStatement* ifThenElseStatement;
       AST_BreakStatement* breakStatement;
       AST_ContinueStatement* continueStatement;
       AST_EmptyStatement* emptyStatement;
       AST_Expression* expression;
       AST_IntegerLiteral* intLiteral;
       Type* type;
       /*Phase 3*/
       AST_ClassList* classList;
       AST_ClassDeclaration* classDeclaration;
       AST_FieldAccess* fieldAccess;
       //AST_This* astThis;
       //AST_NullLiteral* nullLiteral;



/* Line 293 of yacc.c  */
#line 212 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 224 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   226

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  154

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,     2,     2,     2,     2,     2,
      24,    25,    34,    32,    29,    33,    37,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
      30,    38,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    13,    17,    23,    25,
      28,    30,    34,    40,    44,    47,    50,    52,    54,    56,
      58,    62,    66,    69,    72,    74,    76,    78,    81,    84,
      88,    90,    92,    94,    96,    98,   100,   102,   104,   106,
     108,   110,   114,   117,   120,   122,   124,   130,   134,   138,
     141,   144,   147,   149,   153,   157,   160,   162,   164,   166,
     168,   172,   174,   176,   180,   182,   186,   190,   192,   196,
     200,   202,   206,   210,   212,   215,   218,   220,   223,   225,
     227,   229,   231,   233,   235,   237,   239,   243,   247,   250,
     252,   254,   256,   258,   260,   262,   264,   266,   268,   270
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    41,    -1,    42,    -1,    42,    44,    -1,
      44,    42,    -1,    44,    42,    44,    -1,     4,     6,    24,
      25,    43,    -1,    51,    -1,    45,    44,    -1,    45,    -1,
      16,    94,    46,    -1,    16,    94,    17,    93,    46,    -1,
      26,    47,    27,    -1,    26,    27,    -1,    48,    47,    -1,
      48,    -1,    49,    -1,    28,    -1,    50,    -1,    88,    56,
      28,    -1,    26,    52,    27,    -1,    26,    27,    -1,    53,
      52,    -1,    53,    -1,    54,    -1,    61,    -1,    55,    28,
      -1,    88,    56,    -1,    57,    29,    56,    -1,    57,    -1,
      94,    -1,    59,    -1,    67,    -1,    70,    -1,    62,    -1,
      63,    -1,    64,    -1,    68,    -1,    65,    -1,    66,    -1,
      26,    60,    27,    -1,    26,    27,    -1,    61,    60,    -1,
      61,    -1,    58,    -1,     9,    69,    58,    10,    58,    -1,
      11,    69,    58,    -1,    12,    72,    28,    -1,    12,    28,
      -1,    13,    28,    -1,    14,    28,    -1,    28,    -1,     8,
      72,    28,    -1,    24,    72,    25,    -1,    71,    28,    -1,
      74,    -1,    73,    -1,    74,    -1,    76,    -1,    75,    87,
      73,    -1,    94,    -1,    85,    -1,    76,     7,    77,    -1,
      77,    -1,    77,    30,    78,    -1,    77,    31,    78,    -1,
      78,    -1,    78,    32,    79,    -1,    78,    33,    79,    -1,
      79,    -1,    79,    34,    80,    -1,    79,    35,    80,    -1,
      80,    -1,    33,    80,    -1,    36,    80,    -1,    81,    -1,
      69,    81,    -1,    82,    -1,    94,    -1,    83,    -1,    69,
      -1,    20,    -1,    85,    -1,    84,    -1,    95,    -1,    18,
      93,    86,    -1,    82,    37,    94,    -1,    24,    25,    -1,
      38,    -1,    89,    -1,    92,    -1,    90,    -1,    91,    -1,
       4,    -1,    93,    -1,    94,    -1,     3,    -1,     5,    -1,
      15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   111,   111,   139,   143,   147,   151,   159,   167,   171,
     175,   182,   186,   193,   197,   201,   205,   212,   216,   220,
     227,   236,   238,   243,   247,   255,   256,   261,   266,   274,
     278,   287,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   305,   309,   317,   321,   328,   335,   346,   353,   357,
     364,   371,   379,   387,   397,   402,   410,   415,   420,   421,
     426,   434,   435,   440,   444,   449,   453,   457,   462,   466,
     470,   474,   478,   482,   486,   490,   494,   498,   502,   506,
     507,   511,   512,   513,   514,   515,   519,   526,   533,   537,
     541,   542,   546,   551,   555,   562,   569,   577,   585,   589
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "INT", "INTEGER_LITERAL",
  "MAIN", "EQ_OP", "OUT", "IF", "ELSE", "WHILE", "RETURN", "BREAK",
  "CONTINUE", "NULL_LITERAL", "CLASS", "EXTENDS", "NEW", "FIELD_REF",
  "THIS", "SUPER", "DELETE", "BAD", "'('", "')'", "'{'", "'}'", "';'",
  "','", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'!'", "'.'", "'='",
  "$accept", "Program", "CompilationUnit", "MainFunctionDeclaration",
  "MainFunctionBody", "ClassDeclarations", "ClassDeclaration", "ClassBody",
  "ClassBodyDeclarations", "ClassBodyDeclaration",
  "ClassMemberDeclaration", "FieldDeclaration", "MainBlock",
  "MainBlockStatements", "MainBlockStatement",
  "MainVariableDeclarationStatement", "MainVariableDeclaration",
  "VariableDeclarators", "VariableDeclarator", "Statement", "Block",
  "BlockStatements", "BlockStatement", "IfThenElseStatement",
  "WhileStatement", "ReturnStatement", "BreakStatement",
  "ContinueStatement", "EmptyStatement", "OutStatement", "ParenExpression",
  "ExpressionStatement", "StatementExpression", "Expression",
  "AssignmentExpression", "Assignment", "LeftHandSide",
  "EqualityExpression", "RelationalExpression", "AdditiveExpression",
  "MultiplicativeExpression", "UnaryExpression", "CastExpression",
  "Primary", "PrimaryNoNewArray", "ClassInstanceCreationExpression",
  "FieldAccess", "Arguments", "AssignmentOperator", "Type",
  "PrimitiveType", "NumericType", "IntegralType", "ReferenceType",
  "ClassType", "Identifier", "Literal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    40,    41,   123,   125,    59,    44,
      60,    62,    43,    45,    42,    47,    33,    46,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    41,    42,    43,    44,
      44,    45,    45,    46,    46,    47,    47,    48,    48,    49,
      50,    51,    51,    52,    52,    53,    53,    54,    55,    56,
      56,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    60,    61,    62,    63,    64,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    73,
      74,    75,    75,    76,    76,    77,    77,    77,    78,    78,
      78,    79,    79,    79,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    83,    83,    83,    84,    85,    86,    87,
      88,    88,    89,    90,    91,    92,    93,    94,    95,    95
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     3,     5,     1,     2,
       1,     3,     5,     3,     2,     2,     1,     1,     1,     1,
       3,     3,     2,     2,     1,     1,     1,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     1,     1,     5,     3,     3,     2,
       2,     2,     1,     3,     3,     2,     1,     1,     1,     1,
       3,     1,     1,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     3,     0,    10,     0,    97,
       0,     1,     4,     5,     9,     0,     0,     0,    11,     6,
       0,     0,    96,    94,    14,    18,     0,    16,    17,    19,
       0,    90,    92,    93,    91,    95,     0,     7,     8,    12,
      13,    15,     0,    30,    31,    98,     0,     0,     0,     0,
       0,     0,    99,     0,    82,     0,     0,    22,    52,     0,
      24,    25,     0,    45,    32,    26,    35,    36,    37,    39,
      40,    33,    38,    81,    34,     0,    56,     0,     0,    80,
      84,    83,     0,    61,    85,    20,     0,     0,     0,    81,
       0,    57,    58,    59,    64,    67,    70,    73,    76,    78,
      79,     0,     0,    49,     0,    50,    51,     0,     0,    42,
       0,    44,    21,    23,    27,    55,    89,     0,     0,    28,
      29,    74,    83,    79,    75,    77,    53,     0,     0,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    86,    54,
      41,    43,    60,    87,    63,    65,    66,    68,    69,    71,
      72,     0,    88,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    37,     6,     7,    18,    26,    27,
      28,    29,    38,    59,    60,    61,    62,    42,    43,    63,
      64,   110,    65,    66,    67,    68,    69,    70,    71,    72,
      89,    74,    75,    90,    91,    76,    77,    93,    94,    95,
      96,    97,    98,    99,    79,    80,    81,   138,   117,    30,
      31,    32,    33,    34,    35,   123,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -95
static const yytype_int16 yypact[] =
{
      34,     4,    19,    29,   -95,    33,    48,    33,    31,   -95,
       7,   -95,   -95,    33,   -95,    54,    19,     9,   -95,   -95,
      60,    62,   -95,   -95,   -95,   -95,    69,    42,   -95,   -95,
      19,   -95,   -95,   -95,   -95,   -95,   124,   -95,   -95,   -95,
     -95,   -95,    70,    68,   -95,   -95,    87,    79,    79,    86,
      89,    96,   -95,    19,   -95,    87,   150,   -95,   -95,    81,
     176,   -95,    97,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,    98,   -95,    92,    94,   -95,
     -95,   102,    19,     6,   -95,   -95,    19,    87,    87,   151,
     106,   -95,   -95,   134,    36,    50,    40,   -95,   -95,    94,
     105,   198,   198,   -95,   117,   -95,   -95,   122,   132,   -95,
     120,   198,   -95,   -95,   -95,   -95,   -95,    87,    19,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,    87,    87,    87,
      87,    87,    87,    87,   157,   -95,   -95,   135,   -95,   -95,
     -95,   -95,   -95,   -95,    36,    50,    50,    40,    40,   -95,
     -95,   198,   -95,   -95
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -95,   -95,   -95,   166,   -95,    80,   -95,   152,   155,   -95,
     -95,   -95,   -95,   123,   -95,   -95,   -95,   -47,   -95,   -94,
     -95,    75,   -55,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -30,   -95,   -95,    -7,    76,   -44,   -95,   -95,    65,   -34,
     -18,   -56,   108,   -33,   -95,   -95,   -68,   -95,   -95,   -20,
     -95,   -95,   -95,   -95,   -12,    -2,   -95
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -97
static const yytype_int16 yytable[] =
{
      10,   111,    92,    78,    21,    92,    73,   134,   135,   -96,
       8,    92,     9,    23,    22,    22,    82,   101,   102,   122,
     122,   122,     9,    78,    16,    22,    73,    78,    44,    11,
      73,   121,   124,    17,    83,   119,    24,    25,     1,   120,
      82,   107,   104,   -79,   100,     9,    23,   100,   108,     2,
       2,    22,     1,   100,   100,    15,   111,   153,    83,   122,
     122,   122,   122,   122,   122,   122,   128,   129,    78,    78,
      25,    73,    73,    92,   132,   133,   149,   150,    78,    20,
      44,    73,   130,   131,    44,    12,    36,    14,    17,     9,
       9,    45,    45,    19,   145,   146,    40,    86,    85,   100,
     100,    52,    52,    55,    53,    53,    54,    54,   112,   100,
      55,    55,   147,   148,   103,   100,   143,   105,    78,    87,
      87,    73,    88,    88,   106,   114,   115,     9,    23,    45,
     116,   118,    46,    47,   126,    48,    49,    50,    51,    52,
     -62,   127,    53,   -61,    54,   136,   137,   140,    55,   100,
      56,    57,    58,     9,     9,    45,    45,   139,    46,    47,
     152,    48,    49,    50,    51,    52,    52,   151,    53,    53,
      54,    54,    13,    39,    55,    55,    56,   109,    58,     9,
      23,    45,    41,   113,    46,    47,   141,    48,    49,    50,
      51,    52,   144,   142,    53,     0,    54,   125,     0,     0,
      55,     9,    56,    45,    58,     0,    46,    47,     0,    48,
      49,    50,    51,    52,     0,     0,    53,     0,    54,     0,
       0,     0,    55,     0,    56,     0,    58
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-95))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    56,    46,    36,    16,    49,    36,   101,   102,     3,
       6,    55,     3,     4,    16,    17,    36,    47,    48,    87,
      88,    89,     3,    56,    17,    27,    56,    60,    30,     0,
      60,    87,    88,    26,    36,    82,    27,    28,     4,    86,
      60,    53,    49,    37,    46,     3,     4,    49,    55,    16,
      16,    53,     4,    55,    56,    24,   111,   151,    60,   127,
     128,   129,   130,   131,   132,   133,    30,    31,   101,   102,
      28,   101,   102,   117,    34,    35,   132,   133,   111,    25,
      82,   111,    32,    33,    86,     5,    26,     7,    26,     3,
       3,     5,     5,    13,   128,   129,    27,    29,    28,   101,
     102,    15,    15,    24,    18,    18,    20,    20,    27,   111,
      24,    24,   130,   131,    28,   117,   118,    28,   151,    33,
      33,   151,    36,    36,    28,    28,    28,     3,     4,     5,
      38,    37,     8,     9,    28,    11,    12,    13,    14,    15,
      38,     7,    18,    38,    20,    28,    24,    27,    24,   151,
      26,    27,    28,     3,     3,     5,     5,    25,     8,     9,
      25,    11,    12,    13,    14,    15,    15,    10,    18,    18,
      20,    20,     6,    21,    24,    24,    26,    27,    28,     3,
       4,     5,    27,    60,     8,     9,   111,    11,    12,    13,
      14,    15,   127,   117,    18,    -1,    20,    89,    -1,    -1,
      24,     3,    26,     5,    28,    -1,     8,     9,    -1,    11,
      12,    13,    14,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    -1,    24,    -1,    26,    -1,    28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    16,    40,    41,    42,    44,    45,     6,     3,
      94,     0,    44,    42,    44,    24,    17,    26,    46,    44,
      25,    93,    94,     4,    27,    28,    47,    48,    49,    50,
      88,    89,    90,    91,    92,    93,    26,    43,    51,    46,
      27,    47,    56,    57,    94,     5,     8,     9,    11,    12,
      13,    14,    15,    18,    20,    24,    26,    27,    28,    52,
      53,    54,    55,    58,    59,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    74,    75,    82,    83,
      84,    85,    88,    94,    95,    28,    29,    33,    36,    69,
      72,    73,    74,    76,    77,    78,    79,    80,    81,    82,
      94,    69,    69,    28,    72,    28,    28,    93,    72,    27,
      60,    61,    27,    52,    28,    28,    38,    87,    37,    56,
      56,    80,    85,    94,    80,    81,    28,     7,    30,    31,
      32,    33,    34,    35,    58,    58,    28,    24,    86,    25,
      27,    60,    73,    94,    77,    78,    78,    79,    79,    80,
      80,    10,    25,    58
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 112 "parse.yy"
    {
      (yyval.program) = (yyvsp[(1) - (1)].program);
      if( before ){
          cerr << endl;
          (yyval.program)->dump();
        }

        //do semantic analysis
        (yyval.program)->analyze();

        if( after ){
          cerr << endl;
          (yyval.program)->dump();
        }

        //generate code if no errors are present
        if( !errors ){
          (yyval.program)->encode();
        }else{
          cerr << "Errors detected in code; code generation aborted\n";
        }
        //cleanup the AST
        delete (yyval.program);
    }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 140 "parse.yy"
    {
        (yyval.program) = new AST_Program(NULL,(yyvsp[(1) - (1)].mainFunction),NULL);
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 144 "parse.yy"
    {
        (yyval.program) = new AST_Program(NULL,(yyvsp[(1) - (2)].mainFunction),(yyvsp[(2) - (2)].classList));
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 148 "parse.yy"
    {
        (yyval.program) = new AST_Program(NULL,(yyvsp[(2) - (2)].mainFunction),(yyvsp[(1) - (2)].classList));
    }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 152 "parse.yy"
    {
        (yyval.program) = new AST_Program((yyvsp[(1) - (3)].classList), (yyvsp[(2) - (3)].mainFunction), (yyvsp[(3) - (3)].classList));
    }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 160 "parse.yy"
    {
		(yyval.mainFunction) = new AST_MainFunction((yyvsp[(5) - (5)].statementList));//Use MainFunctionBody
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 167 "parse.yy"
    { (yyval.statementList) = (yyvsp[(1) - (1)].statementList); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 172 "parse.yy"
    {
        (yyval.classList) = new AST_ClassList((yyvsp[(1) - (2)].classDeclaration),(yyvsp[(2) - (2)].classList));
    }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 176 "parse.yy"
    {
        (yyval.classList) = new AST_ClassList((yyvsp[(1) - (1)].classDeclaration),NULL);
    }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 183 "parse.yy"
    {
      (yyval.classDeclaration) = new AST_ClassDeclaration((yyvsp[(2) - (3)].expression),NULL,(yyvsp[(3) - (3)].statementList));
    }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 187 "parse.yy"
    {
      (yyval.classDeclaration) = new AST_ClassDeclaration((yyvsp[(2) - (5)].expression),(yyvsp[(4) - (5)].expression),(yyvsp[(5) - (5)].statementList));
    }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 194 "parse.yy"
    {
        (yyval.statementList) = (yyvsp[(2) - (3)].statementList);
    }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 197 "parse.yy"
    {/*Do nothing*/}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 202 "parse.yy"
    {
        (yyval.statementList) = new AST_StatementList((yyvsp[(1) - (2)].declaration),(yyvsp[(2) - (2)].statementList));
    }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 206 "parse.yy"
    {
        (yyval.statementList) = new AST_StatementList((yyvsp[(1) - (1)].declaration),NULL);
    }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 213 "parse.yy"
    {
        (yyval.declaration) = (yyvsp[(1) - (1)].declaration);
    }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 216 "parse.yy"
    {/*Do nothing*/}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 221 "parse.yy"
    {
      (yyval.declaration) = (yyvsp[(1) - (1)].declaration);
    }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 228 "parse.yy"
    {
      (yyval.declaration) = new AST_Declaration((yyvsp[(1) - (3)].type),(yyvsp[(2) - (3)].varList));
    }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 236 "parse.yy"
    { (yyval.statementList) = (yyvsp[(2) - (3)].statementList); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 238 "parse.yy"
    { (yyval.statementList) = NULL; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 244 "parse.yy"
    {
		(yyval.statementList) = new AST_StatementList((yyvsp[(1) - (2)].statement),(yyvsp[(2) - (2)].statementList));
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 248 "parse.yy"
    {
		(yyval.statementList) = new AST_StatementList((yyvsp[(1) - (1)].statement),NULL);
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 255 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].statement); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 256 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].statement); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 261 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (2)].declaration); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 267 "parse.yy"
    {
		(yyval.declaration) = new AST_Declaration((yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].varList));
	}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 275 "parse.yy"
    {
		(yyval.varList) = new AST_VarList((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].varList));
	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 279 "parse.yy"
    {
		(yyval.varList) = new AST_VarList((yyvsp[(1) - (1)].expression),NULL);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 287 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 292 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].block); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 293 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].emptyStatement); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 294 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].expStatement); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 295 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].ifThenElseStatement); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 296 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].whileStatement); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 297 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].returnStatement); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 298 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].outStatement); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 299 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].breakStatement); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 300 "parse.yy"
    { (yyval.statement) = (yyvsp[(1) - (1)].continueStatement); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 306 "parse.yy"
    {
      (yyval.block) = new AST_Block((yyvsp[(2) - (3)].statementList));
    }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 310 "parse.yy"
    {
      (yyval.block) = new AST_Block(NULL); //
    }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 318 "parse.yy"
    {
    (yyval.statementList) = new AST_StatementList((yyvsp[(1) - (2)].statement),(yyvsp[(2) - (2)].statementList));
  }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 322 "parse.yy"
    {
    (yyval.statementList) = new AST_StatementList((yyvsp[(1) - (1)].statement),NULL);
  }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 329 "parse.yy"
    {
      (yyval.statement) = (yyvsp[(1) - (1)].statement);
    }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 336 "parse.yy"
    {
      (yyval.ifThenElseStatement) = new AST_IfThenElseStatement((yyvsp[(2) - (5)].expression),(yyvsp[(3) - (5)].statement),(yyvsp[(5) - (5)].statement));
    }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 347 "parse.yy"
    {
      (yyval.whileStatement) = new AST_WhileStatement((yyvsp[(2) - (3)].expression),(yyvsp[(3) - (3)].statement));
    }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 354 "parse.yy"
    {
      (yyval.returnStatement) = new AST_ReturnStatement((yyvsp[(2) - (3)].expression));
    }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 358 "parse.yy"
    {
      (yyval.returnStatement) = new AST_ReturnStatement(NULL);
    }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 365 "parse.yy"
    {
      (yyval.breakStatement) = new AST_BreakStatement();
    }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 372 "parse.yy"
    {
      (yyval.continueStatement) = new AST_ContinueStatement();
    }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 380 "parse.yy"
    {
      (yyval.emptyStatement) = new AST_EmptyStatement();
    }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 388 "parse.yy"
    {
    //Drops the 'OUT' keyword; could be done in Statement instead
		(yyval.outStatement) = new AST_OutStatement((yyvsp[(2) - (3)].expression));
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 397 "parse.yy"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 403 "parse.yy"
    {
		(yyval.expStatement) = new AST_ExpressionStatement((yyvsp[(1) - (2)].expression));
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 410 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 415 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression);	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 420 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression);	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 421 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 427 "parse.yy"
    {
		(yyval.expression) = new AST_Assignment((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 434 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression);	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 435 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 441 "parse.yy"
    {
		(yyval.expression) = new AST_EqualityExpression((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 444 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression);	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 450 "parse.yy"
    {
		(yyval.expression) = new AST_LessThan((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 454 "parse.yy"
    {
		(yyval.expression) = new AST_GreaterThan((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 457 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression);	}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 463 "parse.yy"
    {
		(yyval.expression) = new AST_Add((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 467 "parse.yy"
    {
		(yyval.expression) = new AST_Subtract((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 470 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 475 "parse.yy"
    {
		(yyval.expression) = new AST_Multiply((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 479 "parse.yy"
    {
		(yyval.expression) = new AST_Divide((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 482 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression);	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 487 "parse.yy"
    {
		(yyval.expression) = new AST_Negate((yyvsp[(2) - (2)].expression));
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 491 "parse.yy"
    {
		(yyval.expression) = new AST_LogicalNot((yyvsp[(2) - (2)].expression));
	}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 494 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression);	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 499 "parse.yy"
    {
        (yyval.expression) = (yyvsp[(1) - (2)].expression);
	}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 502 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 506 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 507 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 511 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 512 "parse.yy"
    { (yyval.expression) = new AST_This(); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 513 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 514 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 515 "parse.yy"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 520 "parse.yy"
    {
      (yyval.expression) = new AST_ClassCreationExp( (yyvsp[(2) - (3)].expression), (yyvsp[(3) - (3)].expression) );
    }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 527 "parse.yy"
    {
      (yyval.expression) = new AST_FieldAccess((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
    }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 533 "parse.yy"
    {/*Do nothing for Phase 3*/}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 537 "parse.yy"
    {/*Do nothing*/}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 541 "parse.yy"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 542 "parse.yy"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 546 "parse.yy"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 551 "parse.yy"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 556 "parse.yy"
    {
	    (yyval.type) = types->intType();
    }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 563 "parse.yy"
    {
        (yyval.type) = (yyvsp[(1) - (1)].expression);
    }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 570 "parse.yy"
    {
      (yyval.expression) = (yyvsp[(1) - (1)].expression);
    }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 578 "parse.yy"
    {
		(yyval.expression) = new AST_Variable((yyvsp[(1) - (1)].str));
	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 586 "parse.yy"
    {
		(yyval.expression) = new AST_IntegerLiteral((yyvsp[(1) - (1)].value));
	}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 590 "parse.yy"
    {
        (yyval.expression) = new AST_NullLiteral();
	}
    break;



/* Line 1806 of yacc.c  */
#line 2437 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 597 "parse.yy"


void yyerror(const char *s){
  cerr << getCurrentSourceLineNumber() << ": parse error" << endl;
}

