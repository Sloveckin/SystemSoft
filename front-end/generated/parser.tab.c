/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include <stdio.h>

#include "../include/ast/ast_node.h"
#include <assert.h>

int yylex();
void yyerror(struct AstNode**, char*);


#line 83 "generated/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_TYPE = 3,                   /* INT_TYPE  */
  YYSYMBOL_BOOL_TYPE = 4,                  /* BOOL_TYPE  */
  YYSYMBOL_BYTE_TYPE = 5,                  /* BYTE_TYPE  */
  YYSYMBOL_UINT_TYPE = 6,                  /* UINT_TYPE  */
  YYSYMBOL_LONG_TYPE = 7,                  /* LONG_TYPE  */
  YYSYMBOL_ULONG_TYPE = 8,                 /* ULONG_TYPE  */
  YYSYMBOL_CHAR_TYPE = 9,                  /* CHAR_TYPE  */
  YYSYMBOL_STRING_TYPE = 10,               /* STRING_TYPE  */
  YYSYMBOL_PLUS = 11,                      /* PLUS  */
  YYSYMBOL_MINUS = 12,                     /* MINUS  */
  YYSYMBOL_DIV = 13,                       /* DIV  */
  YYSYMBOL_MUL = 14,                       /* MUL  */
  YYSYMBOL_EQ = 15,                        /* EQ  */
  YYSYMBOL_NOT_EQ = 16,                    /* NOT_EQ  */
  YYSYMBOL_LESS = 17,                      /* LESS  */
  YYSYMBOL_MORE = 18,                      /* MORE  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_ASSIGMENT = 22,                 /* ASSIGMENT  */
  YYSYMBOL_AS = 23,                        /* AS  */
  YYSYMBOL_BR_OPEN = 24,                   /* BR_OPEN  */
  YYSYMBOL_BR_CLOSE = 25,                  /* BR_CLOSE  */
  YYSYMBOL_SEMICOLON = 26,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_DO = 28,                        /* DO  */
  YYSYMBOL_LOOP = 29,                      /* LOOP  */
  YYSYMBOL_WEND = 30,                      /* WEND  */
  YYSYMBOL_IF = 31,                        /* IF  */
  YYSYMBOL_THEN = 32,                      /* THEN  */
  YYSYMBOL_ELSE = 33,                      /* ELSE  */
  YYSYMBOL_END = 34,                       /* END  */
  YYSYMBOL_DIM = 35,                       /* DIM  */
  YYSYMBOL_FUNCTION = 36,                  /* FUNCTION  */
  YYSYMBOL_DEC = 37,                       /* DEC  */
  YYSYMBOL_BOOL = 38,                      /* BOOL  */
  YYSYMBOL_STR = 39,                       /* STR  */
  YYSYMBOL_HEX = 40,                       /* HEX  */
  YYSYMBOL_BITS = 41,                      /* BITS  */
  YYSYMBOL_IDENTIFIER = 42,                /* IDENTIFIER  */
  YYSYMBOL_BREAK = 43,                     /* BREAK  */
  YYSYMBOL_WHILE = 44,                     /* WHILE  */
  YYSYMBOL_UNTIL = 45,                     /* UNTIL  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_source = 47,                    /* source  */
  YYSYMBOL_statement = 48,                 /* statement  */
  YYSYMBOL_statement_list = 49,            /* statement_list  */
  YYSYMBOL_source_item = 50,               /* source_item  */
  YYSYMBOL_source_item_list = 51,          /* source_item_list  */
  YYSYMBOL_return_type_opt = 52,           /* return_type_opt  */
  YYSYMBOL_func_signature = 53,            /* func_signature  */
  YYSYMBOL_func_def = 54,                  /* func_def  */
  YYSYMBOL_arg_def_list = 55,              /* arg_def_list  */
  YYSYMBOL_type_ref = 56,                  /* type_ref  */
  YYSYMBOL_arg_def = 57,                   /* arg_def  */
  YYSYMBOL_custom = 58,                    /* custom  */
  YYSYMBOL_var = 59,                       /* var  */
  YYSYMBOL_identifier_list = 60,           /* identifier_list  */
  YYSYMBOL_builtin = 61,                   /* builtin  */
  YYSYMBOL_else_block_opt = 62,            /* else_block_opt  */
  YYSYMBOL_else_block = 63,                /* else_block  */
  YYSYMBOL_if = 64,                        /* if  */
  YYSYMBOL_while_or_until = 65,            /* while_or_until  */
  YYSYMBOL_do = 66,                        /* do  */
  YYSYMBOL_while = 67,                     /* while  */
  YYSYMBOL_binary = 68,                    /* binary  */
  YYSYMBOL_unary = 69,                     /* unary  */
  YYSYMBOL_assigment = 70,                 /* assigment  */
  YYSYMBOL_break = 71,                     /* break  */
  YYSYMBOL_expression = 72,                /* expression  */
  YYSYMBOL_braces = 73,                    /* braces  */
  YYSYMBOL_expr_list = 74,                 /* expr_list  */
  YYSYMBOL_call_or_indexer = 75,           /* call_or_indexer  */
  YYSYMBOL_expr = 76,                      /* expr  */
  YYSYMBOL_place = 77,                     /* place  */
  YYSYMBOL_literal = 78                    /* literal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   388

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   115,   115,   120,   121,   122,   123,   124,   125,   128,
     129,   130,   136,   142,   145,   146,   152,   158,   159,   160,
     163,   173,   182,   183,   184,   190,   196,   197,   200,   209,
     212,   221,   222,   228,   229,   230,   231,   232,   233,   234,
     235,   238,   239,   242,   250,   260,   261,   264,   274,   283,
     290,   297,   304,   311,   318,   325,   332,   339,   346,   355,
     361,   367,   375,   385,   388,   391,   394,   395,   396,   402,
     408,   417,   418,   419,   420,   421,   422,   423,   426,   429,
     430,   431,   432,   433
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT_TYPE",
  "BOOL_TYPE", "BYTE_TYPE", "UINT_TYPE", "LONG_TYPE", "ULONG_TYPE",
  "CHAR_TYPE", "STRING_TYPE", "PLUS", "MINUS", "DIV", "MUL", "EQ",
  "NOT_EQ", "LESS", "MORE", "OR", "AND", "NOT", "ASSIGMENT", "AS",
  "BR_OPEN", "BR_CLOSE", "SEMICOLON", "COMMA", "DO", "LOOP", "WEND", "IF",
  "THEN", "ELSE", "END", "DIM", "FUNCTION", "DEC", "BOOL", "STR", "HEX",
  "BITS", "IDENTIFIER", "BREAK", "WHILE", "UNTIL", "$accept", "source",
  "statement", "statement_list", "source_item", "source_item_list",
  "return_type_opt", "func_signature", "func_def", "arg_def_list",
  "type_ref", "arg_def", "custom", "var", "identifier_list", "builtin",
  "else_block_opt", "else_block", "if", "while_or_until", "do", "while",
  "binary", "unary", "assigment", "break", "expression", "braces",
  "expr_list", "call_or_indexer", "expr", "place", "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -26,   -14,    38,   -69,   -26,   -69,    18,   275,   -69,   -69,
       1,   283,   283,   283,   283,   275,   283,    16,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   283,   -69,   139,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   315,
     -69,   -69,    36,   -16,   -69,     5,     5,     5,   363,   173,
      59,   -69,   -15,   105,    24,   -69,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   -69,    27,
      39,     1,   -69,    -4,   275,    27,    19,   283,   283,   283,
     207,   -69,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,   -12,     5,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,    27,   -69,   -69,
     -69,   -69,   283,   241,   -69,   -69,   331,   347,   363,   -69,
     -69,   283,   -69,     5,   275,    29,   -69,     5,   275,    33,
     -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      14,     0,     0,    15,     2,    13,     0,     9,     1,    16,
      22,     0,     0,     0,     0,     9,     0,     0,    80,    79,
      81,    82,    83,    78,    63,     0,    11,     0,     3,     4,
       6,     5,    72,    73,    71,     7,     8,    74,    75,     0,
      76,    77,     0,     0,    24,    59,    60,    61,     0,     0,
       0,    31,     0,     9,     0,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    66,    64,     0,
      17,     0,    65,     0,     9,     0,     0,     0,     0,    66,
       0,    21,    49,    50,    52,    51,    53,    54,    56,    55,
      57,    58,    62,     0,    68,    33,    34,    35,    36,    37,
      38,    39,    40,    29,    28,    26,    27,     0,    20,    25,
      45,    46,     0,    41,    30,    32,    49,    50,    68,    48,
      70,     0,    19,    47,     9,     0,    42,    69,    43,     0,
      44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -23,    -9,    76,   -69,   -69,   -69,   -69,   -69,
     -68,    11,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -11,   -69,   -69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    26,    27,     3,     4,   108,     7,     5,    43,
     104,    44,   105,    28,    52,   106,   125,   126,    29,   112,
      30,    31,    32,    33,    34,    35,    36,    37,    93,    38,
      39,    40,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    46,    47,    48,    55,    50,    49,   114,    75,    70,
       1,    71,    76,   120,    53,   121,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    55,    66,     6,    67,
      95,    96,    97,    98,    99,   100,   101,   102,     8,   122,
     110,   111,    10,    42,    80,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    94,    55,    51,    69,
      81,   115,   107,   129,   130,   113,   116,   117,   118,   103,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       9,    66,   109,    67,     0,     0,     0,     0,     0,     0,
      55,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   123,     0,     0,     0,    55,     0,     0,     0,     0,
     127,     0,     0,     0,     0,   128,    77,    78,    58,    59,
      60,    61,    62,    63,    64,    65,    13,    66,     0,    79,
       0,     0,     0,    15,     0,     0,    16,     0,     0,     0,
      17,     0,    18,    19,    20,    21,    22,    23,    24,    25,
      11,    12,     0,     0,     0,     0,     0,     0,     0,     0,
      13,     0,     0,    14,     0,     0,     0,    15,     0,     0,
      16,     0,     0,    54,    17,     0,    18,    19,    20,    21,
      22,    23,    24,    25,    11,    12,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,     0,    14,     0,     0,
       0,    15,    73,     0,    16,     0,     0,     0,    17,     0,
      18,    19,    20,    21,    22,    23,    24,    25,    11,    12,
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
       0,    14,     0,     0,     0,    15,     0,   119,    16,     0,
       0,     0,    17,     0,    18,    19,    20,    21,    22,    23,
      24,    25,    11,    12,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,    14,     0,     0,     0,    15,
       0,     0,    16,     0,   124,     0,    17,     0,    18,    19,
      20,    21,    22,    23,    24,    25,    11,    12,     0,     0,
       0,     0,     0,     0,    11,    12,    13,     0,     0,    14,
       0,     0,     0,    15,    13,     0,    16,    14,     0,     0,
      17,     0,    18,    19,    20,    21,    22,    23,    24,    25,
      18,    19,    20,    21,    22,    23,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,     0,    66,     0,    67,
       0,    68,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     0,    66,     0,    67,     0,   -59,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,    66,
       0,    67,     0,   -60,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,     0,    66,     0,    67,    72
};

static const yytype_int16 yycheck[] =
{
      11,    12,    13,    14,    27,    16,    15,    75,    23,    25,
      36,    27,    27,    25,    25,    27,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    49,    22,    42,    24,
       3,     4,     5,     6,     7,     8,     9,    10,     0,   107,
      44,    45,    24,    42,    53,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    80,    42,    23,
      36,    42,    23,    34,    31,    74,    77,    78,    79,    42,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       4,    22,    71,    24,    -1,    -1,    -1,    -1,    -1,    -1,
     113,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   112,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,
     121,    -1,    -1,    -1,    -1,   124,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    -1,    -1,    28,    -1,    -1,    31,    -1,    -1,    -1,
      35,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,
      31,    -1,    -1,    34,    35,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,
      -1,    28,    29,    -1,    31,    -1,    -1,    -1,    35,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      -1,    24,    -1,    -1,    -1,    28,    -1,    30,    31,    -1,
      -1,    -1,    35,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    28,
      -1,    -1,    31,    -1,    33,    -1,    35,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    11,    12,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    21,    -1,    31,    24,    -1,    -1,
      35,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      37,    38,    39,    40,    41,    42,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    -1,    22,    -1,    24,
      -1,    26,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    22,    -1,    24,    -1,    26,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    22,
      -1,    24,    -1,    26,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    22,    -1,    24,    25
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,    47,    50,    51,    54,    42,    53,     0,    50,
      24,    11,    12,    21,    24,    28,    31,    35,    37,    38,
      39,    40,    41,    42,    43,    44,    48,    49,    59,    64,
      66,    67,    68,    69,    70,    71,    72,    73,    75,    76,
      77,    78,    42,    55,    57,    76,    76,    76,    76,    49,
      76,    42,    60,    76,    34,    48,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    22,    24,    26,    23,
      25,    27,    25,    29,    32,    23,    27,    11,    12,    24,
      49,    36,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    74,    76,     3,     4,     5,     6,     7,
       8,     9,    10,    42,    56,    58,    61,    23,    52,    57,
      44,    45,    65,    49,    56,    42,    76,    76,    76,    30,
      25,    27,    56,    76,    33,    62,    63,    76,    49,    34,
      31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    48,    48,    48,    49,
      49,    49,    49,    50,    51,    51,    51,    52,    52,    52,
      53,    54,    55,    55,    55,    55,    56,    56,    57,    58,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    62,    63,    64,    65,    65,    66,    67,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    69,
      69,    69,    70,    71,    72,    73,    74,    74,    74,    74,
      75,    76,    76,    76,    76,    76,    76,    76,    77,    78,
      78,    78,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       0,     1,     2,     1,     0,     1,     2,     0,     0,     2,
       5,     5,     0,     0,     1,     3,     1,     1,     3,     1,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     2,     7,     1,     1,     5,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     1,     2,     3,     0,     0,     1,     3,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (root, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct AstNode** root)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (root);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct AstNode** root)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, root);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, struct AstNode** root)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, root); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct AstNode** root)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (root);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_INT_TYPE: /* INT_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1401 "generated/parser.tab.c"
        break;

    case YYSYMBOL_BOOL_TYPE: /* BOOL_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1412 "generated/parser.tab.c"
        break;

    case YYSYMBOL_BYTE_TYPE: /* BYTE_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1423 "generated/parser.tab.c"
        break;

    case YYSYMBOL_UINT_TYPE: /* UINT_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1434 "generated/parser.tab.c"
        break;

    case YYSYMBOL_LONG_TYPE: /* LONG_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1445 "generated/parser.tab.c"
        break;

    case YYSYMBOL_ULONG_TYPE: /* ULONG_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1456 "generated/parser.tab.c"
        break;

    case YYSYMBOL_CHAR_TYPE: /* CHAR_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1467 "generated/parser.tab.c"
        break;

    case YYSYMBOL_STRING_TYPE: /* STRING_TYPE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1478 "generated/parser.tab.c"
        break;

    case YYSYMBOL_DEC: /* DEC  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1489 "generated/parser.tab.c"
        break;

    case YYSYMBOL_BOOL: /* BOOL  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1500 "generated/parser.tab.c"
        break;

    case YYSYMBOL_STR: /* STR  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1511 "generated/parser.tab.c"
        break;

    case YYSYMBOL_HEX: /* HEX  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1522 "generated/parser.tab.c"
        break;

    case YYSYMBOL_BITS: /* BITS  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1533 "generated/parser.tab.c"
        break;

    case YYSYMBOL_IDENTIFIER: /* IDENTIFIER  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1544 "generated/parser.tab.c"
        break;

    case YYSYMBOL_BREAK: /* BREAK  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1555 "generated/parser.tab.c"
        break;

    case YYSYMBOL_WHILE: /* WHILE  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1566 "generated/parser.tab.c"
        break;

    case YYSYMBOL_UNTIL: /* UNTIL  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1577 "generated/parser.tab.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1588 "generated/parser.tab.c"
        break;

    case YYSYMBOL_statement_list: /* statement_list  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1599 "generated/parser.tab.c"
        break;

    case YYSYMBOL_source_item: /* source_item  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1610 "generated/parser.tab.c"
        break;

    case YYSYMBOL_source_item_list: /* source_item_list  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1621 "generated/parser.tab.c"
        break;

    case YYSYMBOL_return_type_opt: /* return_type_opt  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1632 "generated/parser.tab.c"
        break;

    case YYSYMBOL_func_signature: /* func_signature  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1643 "generated/parser.tab.c"
        break;

    case YYSYMBOL_func_def: /* func_def  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1654 "generated/parser.tab.c"
        break;

    case YYSYMBOL_arg_def_list: /* arg_def_list  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1665 "generated/parser.tab.c"
        break;

    case YYSYMBOL_type_ref: /* type_ref  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1676 "generated/parser.tab.c"
        break;

    case YYSYMBOL_arg_def: /* arg_def  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1687 "generated/parser.tab.c"
        break;

    case YYSYMBOL_custom: /* custom  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1698 "generated/parser.tab.c"
        break;

    case YYSYMBOL_var: /* var  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1709 "generated/parser.tab.c"
        break;

    case YYSYMBOL_identifier_list: /* identifier_list  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1720 "generated/parser.tab.c"
        break;

    case YYSYMBOL_builtin: /* builtin  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1731 "generated/parser.tab.c"
        break;

    case YYSYMBOL_else_block_opt: /* else_block_opt  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1742 "generated/parser.tab.c"
        break;

    case YYSYMBOL_else_block: /* else_block  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1753 "generated/parser.tab.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1764 "generated/parser.tab.c"
        break;

    case YYSYMBOL_while_or_until: /* while_or_until  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1775 "generated/parser.tab.c"
        break;

    case YYSYMBOL_do: /* do  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1786 "generated/parser.tab.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1797 "generated/parser.tab.c"
        break;

    case YYSYMBOL_binary: /* binary  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1808 "generated/parser.tab.c"
        break;

    case YYSYMBOL_unary: /* unary  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1819 "generated/parser.tab.c"
        break;

    case YYSYMBOL_assigment: /* assigment  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1830 "generated/parser.tab.c"
        break;

    case YYSYMBOL_break: /* break  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1841 "generated/parser.tab.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1852 "generated/parser.tab.c"
        break;

    case YYSYMBOL_braces: /* braces  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1863 "generated/parser.tab.c"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1874 "generated/parser.tab.c"
        break;

    case YYSYMBOL_call_or_indexer: /* call_or_indexer  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1885 "generated/parser.tab.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1896 "generated/parser.tab.c"
        break;

    case YYSYMBOL_place: /* place  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1907 "generated/parser.tab.c"
        break;

    case YYSYMBOL_literal: /* literal  */
#line 20 "parser.y"
            { 
    if (((*yyvaluep).node)) {
        vector_free(&((*yyvaluep).node)->children);
        free(((*yyvaluep).node));
    }
}
#line 1918 "generated/parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (struct AstNode** root)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* source: source_item_list  */
#line 115 "parser.y"
                          { 
                            *root = (yyvsp[0].node); 
                        }
#line 2218 "generated/parser.tab.c"
    break;

  case 3: /* statement: var  */
#line 120 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2224 "generated/parser.tab.c"
    break;

  case 4: /* statement: if  */
#line 121 "parser.y"
               {(yyval.node) = (yyvsp[0].node); }
#line 2230 "generated/parser.tab.c"
    break;

  case 5: /* statement: while  */
#line 122 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2236 "generated/parser.tab.c"
    break;

  case 6: /* statement: do  */
#line 123 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2242 "generated/parser.tab.c"
    break;

  case 7: /* statement: break  */
#line 124 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2248 "generated/parser.tab.c"
    break;

  case 8: /* statement: expression  */
#line 125 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2254 "generated/parser.tab.c"
    break;

  case 10: /* statement_list: %empty  */
#line 129 "parser.y"
              { /* Empty statement list */ }
#line 2260 "generated/parser.tab.c"
    break;

  case 11: /* statement_list: statement  */
#line 130 "parser.y"
                            {
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_STATMENT_LIST);
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2271 "generated/parser.tab.c"
    break;

  case 12: /* statement_list: statement_list statement  */
#line 136 "parser.y"
                                        {
                                            vector_push(&(yyvsp[-1].node)->children, &(yyvsp[0].node));
                                            (yyval.node) = (yyvsp[-1].node);
                                        }
#line 2280 "generated/parser.tab.c"
    break;

  case 13: /* source_item: func_def  */
#line 142 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2286 "generated/parser.tab.c"
    break;

  case 15: /* source_item_list: source_item  */
#line 146 "parser.y"
                                {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_SOURCE_ITEM_LIST);
                                    vector_push(&node->children, &(yyvsp[0].node));
                                    (yyval.node) = node;
                                }
#line 2297 "generated/parser.tab.c"
    break;

  case 16: /* source_item_list: source_item_list source_item  */
#line 152 "parser.y"
                                                {
                                                    vector_push(&(yyvsp[-1].node)->children, &(yyvsp[0].node));
                                                    (yyval.node) = (yyvsp[-1].node);
                                                }
#line 2306 "generated/parser.tab.c"
    break;

  case 19: /* return_type_opt: AS type_ref  */
#line 160 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2312 "generated/parser.tab.c"
    break;

  case 20: /* func_signature: IDENTIFIER BR_OPEN arg_def_list BR_CLOSE return_type_opt  */
#line 163 "parser.y"
                                                                            {
                                                                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                                                                ast_node_init(node, AST_TYPE_FUNC_SIGNATURE);
                                                                                vector_push(&node->children, &(yyvsp[-4].node));
                                                                                vector_push(&node->children, &(yyvsp[-2].node));
                                                                                vector_push(&node->children, &(yyvsp[0].node));
                                                                                (yyval.node) = node;
                                                                            }
#line 2325 "generated/parser.tab.c"
    break;

  case 21: /* func_def: FUNCTION func_signature statement_list END FUNCTION  */
#line 173 "parser.y"
                                                                {
                                                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                                                    ast_node_init(node, AST_TYPE_FUNC_DEF);
                                                                    vector_push(&node->children, &(yyvsp[-3].node));
                                                                    vector_push(&node->children, &(yyvsp[-2].node));
                                                                    (yyval.node) = node;
                                                                }
#line 2337 "generated/parser.tab.c"
    break;

  case 24: /* arg_def_list: arg_def  */
#line 184 "parser.y"
                        {
                            struct AstNode* node = malloc(sizeof(struct AstNode));
                            ast_node_init(node, AST_TYPE_ARG_DEF_LIST);
                            vector_push(&node->children, &(yyvsp[0].node));
                            (yyval.node) = node;
                        }
#line 2348 "generated/parser.tab.c"
    break;

  case 25: /* arg_def_list: arg_def_list COMMA arg_def  */
#line 190 "parser.y"
                                          {
                                        vector_push(&(yyvsp[-2].node)->children, &(yyvsp[0].node));
                                        (yyval.node) = (yyvsp[-2].node);
                                    }
#line 2357 "generated/parser.tab.c"
    break;

  case 26: /* type_ref: custom  */
#line 196 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2363 "generated/parser.tab.c"
    break;

  case 27: /* type_ref: builtin  */
#line 197 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2369 "generated/parser.tab.c"
    break;

  case 28: /* arg_def: IDENTIFIER AS type_ref  */
#line 200 "parser.y"
                                {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_ARG_DEF);
                                    vector_push(&node->children, &(yyvsp[-2].node));
                                    vector_push(&node->children, &(yyvsp[0].node));
                                    (yyval.node) = node;
                                }
#line 2381 "generated/parser.tab.c"
    break;

  case 29: /* custom: IDENTIFIER  */
#line 209 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2387 "generated/parser.tab.c"
    break;

  case 30: /* var: DIM identifier_list AS type_ref  */
#line 212 "parser.y"
                                        {
                                            struct AstNode* node = malloc(sizeof(struct AstNode));
                                            ast_node_init(node, AST_TYPE_VAR);
                                            vector_push(&node->children, &(yyvsp[-2].node));
                                            vector_push(&node->children, &(yyvsp[0].node));
                                            (yyval.node) = node;
                                        }
#line 2399 "generated/parser.tab.c"
    break;

  case 31: /* identifier_list: IDENTIFIER  */
#line 221 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2405 "generated/parser.tab.c"
    break;

  case 32: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 222 "parser.y"
                                                  {
                                                vector_push(&(yyvsp[-2].node)->children, &(yyvsp[0].node));
                                                (yyval.node) = (yyvsp[-2].node);
                                            }
#line 2414 "generated/parser.tab.c"
    break;

  case 33: /* builtin: INT_TYPE  */
#line 228 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2420 "generated/parser.tab.c"
    break;

  case 34: /* builtin: BOOL_TYPE  */
#line 229 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2426 "generated/parser.tab.c"
    break;

  case 35: /* builtin: BYTE_TYPE  */
#line 230 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2432 "generated/parser.tab.c"
    break;

  case 36: /* builtin: UINT_TYPE  */
#line 231 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2438 "generated/parser.tab.c"
    break;

  case 37: /* builtin: LONG_TYPE  */
#line 232 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2444 "generated/parser.tab.c"
    break;

  case 38: /* builtin: ULONG_TYPE  */
#line 233 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2450 "generated/parser.tab.c"
    break;

  case 39: /* builtin: CHAR_TYPE  */
#line 234 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2456 "generated/parser.tab.c"
    break;

  case 40: /* builtin: STRING_TYPE  */
#line 235 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2462 "generated/parser.tab.c"
    break;

  case 41: /* else_block_opt: %empty  */
#line 238 "parser.y"
                { (yyval.node) = NULL; }
#line 2468 "generated/parser.tab.c"
    break;

  case 42: /* else_block_opt: else_block  */
#line 239 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2474 "generated/parser.tab.c"
    break;

  case 43: /* else_block: ELSE statement_list  */
#line 242 "parser.y"
                                {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_ELSE_BLOCK);
                                    vector_push(&node->children, &(yyvsp[0].node));
                                    (yyval.node) = node;
                                }
#line 2485 "generated/parser.tab.c"
    break;

  case 44: /* if: IF expr THEN statement_list else_block_opt END IF  */
#line 250 "parser.y"
                                                       {
                                            struct AstNode* node = malloc(sizeof(struct AstNode));
                                            ast_node_init(node, AST_TYPE_IF_BLOCK);
                                            vector_push(&node->children, &(yyvsp[-5].node));
                                            vector_push(&node->children, &(yyvsp[-3].node));
                                            vector_push(&node->children, &(yyvsp[-2].node));
                                            (yyval.node) = node;
                                        }
#line 2498 "generated/parser.tab.c"
    break;

  case 45: /* while_or_until: WHILE  */
#line 260 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2504 "generated/parser.tab.c"
    break;

  case 46: /* while_or_until: UNTIL  */
#line 261 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2510 "generated/parser.tab.c"
    break;

  case 47: /* do: DO statement_list LOOP while_or_until expr  */
#line 264 "parser.y"
                                                {
                                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                                    ast_node_init(node, AST_TYPE_DO);
                                                    vector_push(&node->children, &(yyvsp[-3].node));
                                                    vector_push(&node->children, &(yyvsp[-1].node));
                                                    vector_push(&node->children, &(yyvsp[0].node));
                                                    (yyval.node) = node;
                                                }
#line 2523 "generated/parser.tab.c"
    break;

  case 48: /* while: WHILE expr statement_list WEND  */
#line 274 "parser.y"
                                        {
                                            struct AstNode* node = malloc(sizeof(struct AstNode));
                                            ast_node_init(node, AST_TYPE_WHILE_CYCLE);
                                            vector_push(&node->children, &(yyvsp[-2].node));
                                            vector_push(&node->children, &(yyvsp[-1].node));
                                            ast_node_destructor(&(yyvsp[-3].node));
                                            (yyval.node) = node;
                                        }
#line 2536 "generated/parser.tab.c"
    break;

  case 49: /* binary: expr PLUS expr  */
#line 283 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_PLUS);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2548 "generated/parser.tab.c"
    break;

  case 50: /* binary: expr MINUS expr  */
#line 290 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_MINUS);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2560 "generated/parser.tab.c"
    break;

  case 51: /* binary: expr MUL expr  */
#line 297 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_MUL);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2572 "generated/parser.tab.c"
    break;

  case 52: /* binary: expr DIV expr  */
#line 304 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_DIV);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2584 "generated/parser.tab.c"
    break;

  case 53: /* binary: expr EQ expr  */
#line 311 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_EQ);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2596 "generated/parser.tab.c"
    break;

  case 54: /* binary: expr NOT_EQ expr  */
#line 318 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_NOT_EQ);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2608 "generated/parser.tab.c"
    break;

  case 55: /* binary: expr MORE expr  */
#line 325 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_MORE);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2620 "generated/parser.tab.c"
    break;

  case 56: /* binary: expr LESS expr  */
#line 332 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_LESS);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2632 "generated/parser.tab.c"
    break;

  case 57: /* binary: expr OR expr  */
#line 339 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_OR);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2644 "generated/parser.tab.c"
    break;

  case 58: /* binary: expr AND expr  */
#line 346 "parser.y"
                            { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_AND);
                                vector_push(&node->children, &(yyvsp[-2].node));
                                vector_push(&node->children, &(yyvsp[0].node));
                                (yyval.node) = node;
                            }
#line 2656 "generated/parser.tab.c"
    break;

  case 59: /* unary: PLUS expr  */
#line 355 "parser.y"
                    {
                        struct AstNode* node = malloc(sizeof(struct AstNode));
                        ast_node_init(node, AST_TYPE_UNARY_PLUS);
                        vector_push(&node->children, &(yyvsp[0].node));
                        (yyval.node) = node;
                    }
#line 2667 "generated/parser.tab.c"
    break;

  case 60: /* unary: MINUS expr  */
#line 361 "parser.y"
                    {
                        struct AstNode* node = malloc(sizeof(struct AstNode));
                        ast_node_init(node, AST_TYPE_UNARY_MINUS);
                        vector_push(&node->children, &(yyvsp[0].node));
                        (yyval.node) = node;
                    }
#line 2678 "generated/parser.tab.c"
    break;

  case 61: /* unary: NOT expr  */
#line 367 "parser.y"
                    {
                        struct AstNode* node = malloc(sizeof(struct AstNode));
                        ast_node_init(node, AST_TYPE_NOT);
                        vector_push(&node->children, &(yyvsp[0].node));
                        (yyval.node) = node;
                    }
#line 2689 "generated/parser.tab.c"
    break;

  case 62: /* assigment: expr ASSIGMENT expr  */
#line 376 "parser.y"
                                {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_ASSIGMENT);
                                    vector_push(&node->children, &(yyvsp[-2].node));
                                    vector_push(&node->children, &(yyvsp[0].node));
                                    (yyval.node) = node;
                                }
#line 2701 "generated/parser.tab.c"
    break;

  case 63: /* break: BREAK  */
#line 385 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2707 "generated/parser.tab.c"
    break;

  case 64: /* expression: expr SEMICOLON  */
#line 388 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 2713 "generated/parser.tab.c"
    break;

  case 65: /* braces: BR_OPEN expr BR_CLOSE  */
#line 391 "parser.y"
                              { (yyval.node) = (yyvsp[-1].node); }
#line 2719 "generated/parser.tab.c"
    break;

  case 68: /* expr_list: expr  */
#line 396 "parser.y"
                {
                    struct AstNode* node = malloc(sizeof(struct AstNode));
                    ast_node_init(node, AST_TYPE_EXPR_LIST);
                    vector_push(&node->children, &(yyvsp[0].node));
                    (yyval.node) = node;
                }
#line 2730 "generated/parser.tab.c"
    break;

  case 69: /* expr_list: expr_list COMMA expr  */
#line 402 "parser.y"
                                    {
                                        vector_push(&(yyvsp[-2].node)->children, &(yyvsp[0].node));
                                        (yyval.node) = (yyvsp[-2].node);
                                    }
#line 2739 "generated/parser.tab.c"
    break;

  case 70: /* call_or_indexer: expr BR_OPEN expr_list BR_CLOSE  */
#line 408 "parser.y"
                                                    {
                                                        struct AstNode* node = malloc(sizeof(struct AstNode));
                                                        ast_node_init(node, AST_TYPE_CALL_OR_INDEXER);
                                                        vector_push(&node->children, &(yyvsp[-3].node));
                                                        vector_push(&node->children, &(yyvsp[-1].node));
                                                        (yyval.node) = node;
                                                    }
#line 2751 "generated/parser.tab.c"
    break;

  case 71: /* expr: assigment  */
#line 417 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2757 "generated/parser.tab.c"
    break;

  case 72: /* expr: binary  */
#line 418 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2763 "generated/parser.tab.c"
    break;

  case 73: /* expr: unary  */
#line 419 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2769 "generated/parser.tab.c"
    break;

  case 74: /* expr: braces  */
#line 420 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2775 "generated/parser.tab.c"
    break;

  case 75: /* expr: call_or_indexer  */
#line 421 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2781 "generated/parser.tab.c"
    break;

  case 76: /* expr: place  */
#line 422 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2787 "generated/parser.tab.c"
    break;

  case 77: /* expr: literal  */
#line 423 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2793 "generated/parser.tab.c"
    break;

  case 78: /* place: IDENTIFIER  */
#line 426 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2799 "generated/parser.tab.c"
    break;

  case 79: /* literal: BOOL  */
#line 429 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2805 "generated/parser.tab.c"
    break;

  case 80: /* literal: DEC  */
#line 430 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2811 "generated/parser.tab.c"
    break;

  case 81: /* literal: STR  */
#line 431 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2817 "generated/parser.tab.c"
    break;

  case 82: /* literal: HEX  */
#line 432 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2823 "generated/parser.tab.c"
    break;

  case 83: /* literal: BITS  */
#line 433 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2829 "generated/parser.tab.c"
    break;


#line 2833 "generated/parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (root, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, root);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, root);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (root, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, root);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 436 "parser.y"


void yyerror(struct AstNode** node, char* error)
{
    printf("Error = %s\n", error);
}
