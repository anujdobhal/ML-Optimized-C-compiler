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
#include <stdlib.h>
#include <string.h>
#include "symbolTable.c"

#include <ctype.h>

// ---------------- AST NODE ----------------

typedef struct ASTNode
{
    char type[20];
    char value[50];

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *middle;
    struct ASTNode *next;

} ASTNode;

ASTNode* createNode(char *type,
                    char *value,
                    ASTNode *left,
                    ASTNode *right,
                    ASTNode *middle)
{
    ASTNode *node =
        (ASTNode*)malloc(sizeof(ASTNode));

    strcpy(node->type,type);

    if(value)
        strcpy(node->value,value);
    else
        strcpy(node->value,"");

    node->left = left;
    node->right = right;
    node->middle = middle;
    node->next = NULL;

    return node;
}

extern int yylineno;
extern FILE *yyin;
extern char *yytext;


int yylex();
int yyerror(char *s);
int printline();

// ----------- ICG (YOUR PART) -----------
int tempCount = 0;

char* newTemp() {
    char *temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}
int labelCount = 0;

char* newLabel()
{
    char *label = (char*)malloc(10);

    sprintf(label, "L%d", labelCount++);

    return label;
}

char tac[1000][100];


int tacIndex = 0;

void emit(char *str) {
    strcpy(tac[tacIndex++], str);
}

// ----------- existing variables -----------
int i=1,k=-1,l=-1;
int j=0;
char curfunc[100];
int stack[100];
int top=0;
int plist[100],flist[100];
int end[100];
int arr[10];
int ct=0,c=0,b;
int loop = 0;
int errc=0;
int type=0;
ASTNode *root = NULL;

#line 170 "parser.tab.c"

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
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_NUM = 7,                        /* NUM  */
  YYSYMBOL_REAL = 8,                       /* REAL  */
  YYSYMBOL_STRING = 9,                     /* STRING  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_PREPROC = 13,                   /* PREPROC  */
  YYSYMBOL_LE = 14,                        /* LE  */
  YYSYMBOL_PRINT = 15,                     /* PRINT  */
  YYSYMBOL_FUNCTION = 16,                  /* FUNCTION  */
  YYSYMBOL_DO = 17,                        /* DO  */
  YYSYMBOL_ARRAY = 18,                     /* ARRAY  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_STRUCT = 20,                    /* STRUCT  */
  YYSYMBOL_STRUCT_VAR = 21,                /* STRUCT_VAR  */
  YYSYMBOL_FOR = 22,                       /* FOR  */
  YYSYMBOL_GE = 23,                        /* GE  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NE = 25,                        /* NE  */
  YYSYMBOL_INC = 26,                       /* INC  */
  YYSYMBOL_DEC = 27,                       /* DEC  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* '+'  */
  YYSYMBOL_30_ = 30,                       /* '-'  */
  YYSYMBOL_31_ = 31,                       /* '*'  */
  YYSYMBOL_32_ = 32,                       /* '/'  */
  YYSYMBOL_33_ = 33,                       /* '<'  */
  YYSYMBOL_34_ = 34,                       /* '>'  */
  YYSYMBOL_IFX = 35,                       /* IFX  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* ')'  */
  YYSYMBOL_38_ = 38,                       /* ','  */
  YYSYMBOL_39_ = 39,                       /* ';'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* '['  */
  YYSYMBOL_43_ = 43,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_start = 45,                     /* start  */
  YYSYMBOL_Function = 46,                  /* Function  */
  YYSYMBOL_Type = 47,                      /* Type  */
  YYSYMBOL_stmt = 48,                      /* stmt  */
  YYSYMBOL_CompoundStmt = 49,              /* CompoundStmt  */
  YYSYMBOL_stmtlist = 50,                  /* stmtlist  */
  YYSYMBOL_dowhile = 51,                   /* dowhile  */
  YYSYMBOL_if = 52,                        /* if  */
  YYSYMBOL_for = 53,                       /* for  */
  YYSYMBOL_while = 54,                     /* while  */
  YYSYMBOL_expr1 = 55,                     /* expr1  */
  YYSYMBOL_assignment1 = 56,               /* assignment1  */
  YYSYMBOL_paralist = 57,                  /* paralist  */
  YYSYMBOL_param = 58,                     /* param  */
  YYSYMBOL_assignment2 = 59,               /* assignment2  */
  YYSYMBOL_exp = 60,                       /* exp  */
  YYSYMBOL_consttype = 61,                 /* consttype  */
  YYSYMBOL_Declaration = 62                /* Declaration  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  139

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


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
      36,    37,    31,    29,    38,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
      33,    28,    34,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      25,    26,    27,    35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   124,   124,   144,   164,   184,   186,   190,   208,   209,
     210,   214,   219,   224,   229,   234,   239,   244,   249,   254,
     259,   264,   271,   279,   298,   304,   309,   316,   321,   328,
     341,   349,   354,   359,   364,   369,   374,   379,   392,   409,
     416,   420,   424,   437,   458,   483,   489,   490,   493,   505,
     515,   526,   543,   548,   553,   558,   563,   568,   574,   575,
     578,   611,   638,   671,   675,   679
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "VOID",
  "ID", "NUM", "REAL", "STRING", "WHILE", "IF", "RETURN", "PREPROC", "LE",
  "PRINT", "FUNCTION", "DO", "ARRAY", "ELSE", "STRUCT", "STRUCT_VAR",
  "FOR", "GE", "EQ", "NE", "INC", "DEC", "'='", "'+'", "'-'", "'*'", "'/'",
  "'<'", "'>'", "IFX", "'('", "')'", "','", "';'", "'{'", "'}'", "'['",
  "']'", "$accept", "start", "Function", "Type", "stmt", "CompoundStmt",
  "stmtlist", "dowhile", "if", "for", "while", "expr1", "assignment1",
  "paralist", "param", "assignment2", "exp", "consttype", "Declaration", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-46)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -46,   129,   -46,   -46,   -46,   -46,   -46,    19,   -46,   -46,
     -31,   -29,     3,   -46,    -9,    16,    23,    -4,   -46,   155,
     -46,    52,   -46,   -46,   -46,   -46,   -46,   -46,    24,   -46,
      34,   -46,     9,    73,    45,    45,    45,    51,    62,    88,
      97,     2,    45,   105,   -46,   196,   -46,    26,   -46,    45,
     150,    13,   -46,    95,   160,   -46,   -12,   -46,   -46,    36,
     -46,    79,   -46,   -46,    77,    81,    82,   155,    89,    50,
     -46,   -46,    28,    83,   -46,    28,   -46,    73,   -46,    13,
     190,   -46,    13,    13,    13,    13,   -46,    73,    45,    45,
      45,    45,    45,    45,    16,    16,    99,    45,   -46,   237,
      45,   104,    16,   102,    58,   194,   123,    74,    74,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   128,
     -46,    85,   109,   -11,   -46,   -46,   111,   -46,   -46,    16,
     118,   -46,    45,   -46,   -46,   -46,   127,    16,   -46
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     1,    65,     8,     9,    10,    42,    58,    59,
       0,     0,     0,     5,     0,     0,     0,     0,    21,     0,
       3,     0,     2,    20,    15,    12,    13,    14,     0,    40,
      45,     4,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    24,     0,    11,     0,    16,     0,
      42,     0,    38,    49,    45,    48,     0,    47,    39,     0,
      37,     0,    18,    17,     0,     0,     0,     0,     0,     0,
      22,    23,     0,     0,    61,     0,    41,     0,    51,     0,
       0,    57,     0,     0,     0,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,    50,    52,    53,    54,
      55,    46,    31,    32,    34,    33,    36,    35,    30,    27,
      19,     0,     0,     0,    60,     7,     0,    43,    56,     0,
       0,    63,     0,    62,    28,    26,     0,     0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -46,   -46,   170,     1,   -14,   106,   -46,   -46,   -46,
     -46,    -6,    -1,   107,    87,   -46,   -45,    -8,   175
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    20,    43,    44,    23,    45,    24,    25,    26,
      27,    59,    60,    56,    57,    29,    53,    30,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    40,    22,    88,    38,    35,    80,    36,    66,    37,
       8,     9,    89,    90,    91,    50,     8,     9,    28,    78,
       8,     9,    92,    93,    54,    86,    87,    39,   132,    41,
      61,    52,    42,    58,   105,     8,     9,   107,   108,   109,
     110,    68,    67,    81,    28,    51,    71,    32,    76,    79,
      88,     7,     8,     9,    72,    33,    19,    34,    47,    89,
      90,    91,    73,    48,   101,    74,    28,   103,    75,    92,
      93,    81,    49,    94,    81,    81,    81,    81,    72,    55,
     118,   119,   112,   113,   114,   115,   116,   117,   125,    74,
      62,   121,    75,    88,   123,   127,    87,    64,    28,    88,
      71,    63,    89,    90,    91,    84,    85,    65,    89,    90,
      91,    69,    92,    93,    96,   134,    95,    97,    92,    93,
     102,    98,   130,   138,    82,    83,    84,    85,   100,     2,
       3,   136,     4,     5,     6,     7,     8,     9,   120,    10,
      11,    12,    13,   124,    14,   126,    15,   129,   131,    16,
     133,    17,   -56,   -56,   -56,   -56,     3,   135,     4,     5,
       6,     7,     8,     9,   137,    10,    11,    12,    18,    19,
      14,    21,    15,    99,   111,    16,    31,    17,    32,   -51,
     -51,   -51,   -51,     0,   104,     0,    77,     0,    34,   -57,
     -57,   -57,   -57,     0,    18,    19,   -25,     3,    49,     4,
       5,     6,     7,     8,     9,     0,    10,    11,    12,     0,
       0,    14,     0,    15,     0,     0,    16,     0,    17,    82,
      83,    84,    85,    82,    83,    84,    85,   106,     0,     0,
       0,   128,     0,     0,     0,    18,    19,    70,     3,     0,
       4,     5,     6,     7,     8,     9,     0,    10,    11,    12,
       0,     0,    14,     0,    15,     0,     0,    16,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    19,   122
};

static const yytype_int16 yycheck[] =
{
       1,    15,     1,    14,    12,    36,    51,    36,     6,     6,
       7,     8,    23,    24,    25,     6,     7,     8,    19,     6,
       7,     8,    33,    34,    32,    37,    38,    36,    39,     6,
      36,    32,    36,    34,    79,     7,     8,    82,    83,    84,
      85,    42,    40,    51,    45,    36,    45,    28,    49,    36,
      14,     6,     7,     8,    28,    36,    40,    38,     6,    23,
      24,    25,    36,    39,    72,    39,    67,    75,    42,    33,
      34,    79,    38,    37,    82,    83,    84,    85,    28,     6,
      94,    95,    88,    89,    90,    91,    92,    93,   102,    39,
      39,    97,    42,    14,   100,    37,    38,     9,    99,    14,
      99,    39,    23,    24,    25,    31,    32,    10,    23,    24,
      25,     6,    33,    34,    37,   129,    37,    36,    33,    34,
      37,    39,    37,   137,    29,    30,    31,    32,    39,     0,
       1,   132,     3,     4,     5,     6,     7,     8,    39,    10,
      11,    12,    13,    39,    15,    43,    17,    19,    39,    20,
      39,    22,    29,    30,    31,    32,     1,    39,     3,     4,
       5,     6,     7,     8,    37,    10,    11,    12,    39,    40,
      15,     1,    17,    67,    87,    20,     1,    22,    28,    29,
      30,    31,    32,    -1,    77,    -1,    36,    -1,    38,    29,
      30,    31,    32,    -1,    39,    40,    41,     1,    38,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    -1,
      -1,    15,    -1,    17,    -1,    -1,    20,    -1,    22,    29,
      30,    31,    32,    29,    30,    31,    32,    37,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    39,    40,    41,     1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      -1,    -1,    15,    -1,    17,    -1,    -1,    20,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,     0,     1,     3,     4,     5,     6,     7,     8,
      10,    11,    12,    13,    15,    17,    20,    22,    39,    40,
      46,    47,    48,    49,    51,    52,    53,    54,    56,    59,
      61,    62,    28,    36,    38,    36,    36,     6,    61,    36,
      49,     6,    36,    47,    48,    50,    62,     6,    39,    38,
       6,    36,    56,    60,    61,     6,    57,    58,    56,    55,
      56,    55,    39,    39,     9,    10,     6,    40,    56,     6,
      41,    48,    28,    36,    39,    42,    56,    36,     6,    36,
      60,    61,    29,    30,    31,    32,    37,    38,    14,    23,
      24,    25,    33,    34,    37,    37,    37,    36,    39,    50,
      39,    61,    37,    61,    57,    60,    37,    60,    60,    60,
      60,    58,    55,    55,    55,    55,    55,    55,    49,    49,
      39,    55,    41,    55,    39,    49,    43,    37,    37,    19,
      37,    39,    39,    39,    49,    39,    56,    37,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    45,    45,    45,    45,    46,    47,    47,
      47,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    49,    50,    50,    50,    51,    52,    52,    53,
      54,    55,    55,    55,    55,    55,    55,    55,    56,    56,
      56,    56,    56,    56,    56,    56,    57,    57,    58,    59,
      59,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      62,    62,    62,    62,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     0,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     3,     5,
       1,     1,     3,     2,     1,     0,     7,     5,     7,     9,
       5,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     6,     4,     1,     3,     1,     1,     3,
       5,     1,     3,     3,     3,     3,     3,     1,     1,     1,
       5,     3,     6,     6,     4,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: start stmt  */
#line 125 "parser.y"
{
    if((yyvsp[0].node) != NULL)
    {
        if(root == NULL)
        {
            root = (yyvsp[0].node);
        }
        else
        {
            ASTNode *temp = root;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = (yyvsp[0].node);
        }
    }
}
#line 1344 "parser.tab.c"
    break;

  case 3: /* start: start Function  */
#line 145 "parser.y"
{
    if((yyvsp[0].node) != NULL)
    {
        if(root == NULL)
        {
            root = (yyvsp[0].node);
        }
        else
        {
            ASTNode *temp = root;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = (yyvsp[0].node);
        }
    }
}
#line 1367 "parser.tab.c"
    break;

  case 4: /* start: start Declaration  */
#line 165 "parser.y"
{
    if((yyvsp[0].node) != NULL)
    {
        if(root == NULL)
        {
            root = (yyvsp[0].node);
        }
        else
        {
            ASTNode *temp = root;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = (yyvsp[0].node);
        }
    }
}
#line 1390 "parser.tab.c"
    break;

  case 7: /* Function: Type ID '(' ')' CompoundStmt  */
#line 191 "parser.y"
{

    ASTNode *funcNode =
        createNode("FUNCTION",(yyvsp[-3].str),(yyvsp[0].node),NULL,NULL);

    (yyval.node) = funcNode;

}
#line 1403 "parser.tab.c"
    break;

  case 11: /* stmt: Declaration  */
#line 215 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1411 "parser.tab.c"
    break;

  case 12: /* stmt: if  */
#line 220 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1419 "parser.tab.c"
    break;

  case 13: /* stmt: for  */
#line 225 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1427 "parser.tab.c"
    break;

  case 14: /* stmt: while  */
#line 230 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1435 "parser.tab.c"
    break;

  case 15: /* stmt: dowhile  */
#line 235 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1443 "parser.tab.c"
    break;

  case 16: /* stmt: assignment1 ';'  */
#line 240 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1451 "parser.tab.c"
    break;

  case 17: /* stmt: RETURN consttype ';'  */
#line 245 "parser.y"
{
    (yyval.node) = createNode("RETURN",(yyvsp[-1].str),NULL,NULL,NULL);
}
#line 1459 "parser.tab.c"
    break;

  case 18: /* stmt: RETURN ID ';'  */
#line 250 "parser.y"
{
    (yyval.node) = createNode("RETURN",(yyvsp[-1].str),NULL,NULL,NULL);
}
#line 1467 "parser.tab.c"
    break;

  case 19: /* stmt: PRINT '(' STRING ')' ';'  */
#line 255 "parser.y"
{
    (yyval.node) = createNode("PRINT",(yyvsp[-2].str),NULL,NULL,NULL);
}
#line 1475 "parser.tab.c"
    break;

  case 20: /* stmt: CompoundStmt  */
#line 260 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1483 "parser.tab.c"
    break;

  case 21: /* stmt: ';'  */
#line 265 "parser.y"
{
    (yyval.node) = NULL;
}
#line 1491 "parser.tab.c"
    break;

  case 22: /* CompoundStmt: '{' stmtlist '}'  */
#line 272 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1499 "parser.tab.c"
    break;

  case 23: /* stmtlist: stmtlist stmt  */
#line 280 "parser.y"
{
    if((yyvsp[-1].node) == NULL)
    {
        (yyval.node) = (yyvsp[0].node);
    }
    else
    {
        ASTNode *temp = (yyvsp[-1].node);

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = (yyvsp[0].node);

        (yyval.node) = (yyvsp[-1].node);
    }
}
#line 1521 "parser.tab.c"
    break;

  case 24: /* stmtlist: stmt  */
#line 299 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1529 "parser.tab.c"
    break;

  case 25: /* stmtlist: %empty  */
#line 304 "parser.y"
{
    (yyval.node) = NULL;
}
#line 1537 "parser.tab.c"
    break;

  case 26: /* dowhile: DO CompoundStmt WHILE '(' expr1 ')' ';'  */
#line 310 "parser.y"
{
    (yyval.node) = createNode("DOWHILE","dowhile",(yyvsp[-2].node),(yyvsp[-5].node),NULL);
}
#line 1545 "parser.tab.c"
    break;

  case 27: /* if: IF '(' expr1 ')' CompoundStmt  */
#line 317 "parser.y"
{
    (yyval.node) = createNode("IF","if",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1553 "parser.tab.c"
    break;

  case 28: /* if: IF '(' expr1 ')' CompoundStmt ELSE CompoundStmt  */
#line 322 "parser.y"
{
    (yyval.node) = createNode("IFELSE","ifelse",(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1561 "parser.tab.c"
    break;

  case 29: /* for: FOR '(' assignment1 ';' expr1 ';' assignment1 ')' CompoundStmt  */
#line 330 "parser.y"
{
    ASTNode *forNode =
        createNode("FOR","for",(yyvsp[-6].node),(yyvsp[-4].node),(yyvsp[-2].node));

    forNode->next = (yyvsp[0].node);

    (yyval.node) = forNode;
}
#line 1574 "parser.tab.c"
    break;

  case 30: /* while: WHILE '(' expr1 ')' CompoundStmt  */
#line 342 "parser.y"
{
    (yyval.node) = createNode("WHILE","while",(yyvsp[-2].node),(yyvsp[0].node),NULL);

    
}
#line 1584 "parser.tab.c"
    break;

  case 31: /* expr1: expr1 LE expr1  */
#line 350 "parser.y"
{
    (yyval.node) = createNode("LE","<=",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1592 "parser.tab.c"
    break;

  case 32: /* expr1: expr1 GE expr1  */
#line 355 "parser.y"
{
    (yyval.node) = createNode("GE",">=",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1600 "parser.tab.c"
    break;

  case 33: /* expr1: expr1 NE expr1  */
#line 360 "parser.y"
{
    (yyval.node) = createNode("NE","!=",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1608 "parser.tab.c"
    break;

  case 34: /* expr1: expr1 EQ expr1  */
#line 365 "parser.y"
{
    (yyval.node) = createNode("EQ","==",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1616 "parser.tab.c"
    break;

  case 35: /* expr1: expr1 '>' expr1  */
#line 370 "parser.y"
{
    (yyval.node) = createNode("GT",">",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1624 "parser.tab.c"
    break;

  case 36: /* expr1: expr1 '<' expr1  */
#line 375 "parser.y"
{
    (yyval.node) = createNode("LT","<",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1632 "parser.tab.c"
    break;

  case 37: /* expr1: assignment1  */
#line 380 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1640 "parser.tab.c"
    break;

  case 38: /* assignment1: ID '=' assignment1  */
#line 393 "parser.y"
{
    ASTNode *idNode =
        createNode("ID",(yyvsp[-2].str),NULL,NULL,NULL);

    (yyval.node) = createNode("ASSIGN","=",idNode,(yyvsp[0].node),NULL);

    int sct = returnscope((yyvsp[-2].str), stack[top-1]);
    int type = returntype((yyvsp[-2].str), sct);

    if(type == 273)
    {
        printf("\nError : Type Mismatch : Line %d\n", printline());
        errc++;
    }
}
#line 1660 "parser.tab.c"
    break;

  case 39: /* assignment1: ID ',' assignment1  */
#line 410 "parser.y"
        {
		if(lookup((yyvsp[-2].str))) {
			printf("\nUndeclared Variable %s : Line %d\n",(yyvsp[-2].str),printline()); errc++;
        }
        (yyval.node) = createNode("COMMA", ",", createNode("ID", (yyvsp[-2].str), NULL, NULL, NULL), (yyvsp[0].node), NULL);
	}
#line 1671 "parser.tab.c"
    break;

  case 40: /* assignment1: assignment2  */
#line 417 "parser.y"
    {
     (yyval.node) = (yyvsp[0].node);
    }
#line 1679 "parser.tab.c"
    break;

  case 41: /* assignment1: consttype ',' assignment1  */
#line 421 "parser.y"
    {
        (yyval.node) = createNode("COMMA", ",", createNode("NUM", (yyvsp[-2].str), NULL, NULL, NULL), (yyvsp[0].node), NULL);
    }
#line 1687 "parser.tab.c"
    break;

  case 42: /* assignment1: ID  */
#line 425 "parser.y"
{
   if(lookup((yyvsp[0].str)))
   {
      printf("\nUndeclared Variable %s : Line %d\n",
             (yyvsp[0].str),
             printline());

      errc++;
   }

   (yyval.node) = createNode("ID",(yyvsp[0].str),NULL,NULL,NULL);
}
#line 1704 "parser.tab.c"
    break;

  case 43: /* assignment1: ID '=' ID '(' paralist ')'  */
#line 438 "parser.y"
        {
                int sct=returnscope((yyvsp[-5].str),stack[top-1]);
		int type=returntype((yyvsp[-5].str),sct);
                //printf("%s",$3);
                int rtype;
                rtype=returntypef((yyvsp[-3].str)); int ch=0;
                //printf("%d",rtype);
		if(rtype!=type)
			{ printf("\nError : Type Mismatch : Line %d\n",printline()); errc++;}
		if(!lookup((yyvsp[-5].str)))
		{
		  for(j=0;j<=l;j++)
                  {ch = ch+checkp((yyvsp[-3].str),flist[j],j);}
                  if(ch>0) { printf("\nError : Parameter Type Mistake or Function undeclared : Line %d\n",printline()); errc++;}
                  l=-1;
		}
        ASTNode *idNode = createNode("ID", (yyvsp[-5].str), NULL, NULL, NULL);
        ASTNode *callNode = createNode("CALL", (yyvsp[-3].str), NULL, NULL, NULL);
        (yyval.node) = createNode("ASSIGN", "=", idNode, callNode, NULL);
	}
#line 1729 "parser.tab.c"
    break;

  case 44: /* assignment1: ID '(' paralist ')'  */
#line 459 "parser.y"
        {
                int sct=returnscope((yyvsp[-3].str),stack[top-1]);
		int type=returntype((yyvsp[-3].str),sct); int ch=0;
		if(!lookup((yyvsp[-3].str)))
		{
		  for(j=0;j<=l;j++)
                  {ch = ch+checkp((yyvsp[-3].str),flist[j],j);}
                  if(ch>0) { printf("\nError : Parameter Type Mistake or Required Function undeclared : Line %d\n",printline()); errc++;}
                  l=-1;
		}
                else {printf("\nUndeclared Function %s : Line %d\n",(yyvsp[-3].str),printline());errc++;}
        (yyval.node) = createNode("CALL", (yyvsp[-3].str), NULL, NULL, NULL);
	}
#line 1747 "parser.tab.c"
    break;

  case 45: /* assignment1: consttype  */
#line 484 "parser.y"
    {
        (yyval.node) = createNode("NUM", (yyvsp[0].str), NULL, NULL, NULL);
    }
#line 1755 "parser.tab.c"
    break;

  case 48: /* param: ID  */
#line 494 "parser.y"
        {
                if(lookup((yyvsp[0].str)))
	        	{printf("\nUndeclared Variable %s : Line %d\n",(yyvsp[0].str),printline());errc++;}
                else
                {
                	int sct=returnscope((yyvsp[0].str),stack[top-1]);
                	flist[++l]=returntype((yyvsp[0].str),sct);
                }
	}
#line 1769 "parser.tab.c"
    break;

  case 49: /* assignment2: ID '=' exp  */
#line 506 "parser.y"
{
    ASTNode *idNode =
        createNode("ID",(yyvsp[-2].str),NULL,NULL,NULL);

    (yyval.node) = createNode("ASSIGN","=",idNode,(yyvsp[0].node),NULL);

    c=0;
}
#line 1782 "parser.tab.c"
    break;

  case 50: /* assignment2: ID '=' '(' exp ')'  */
#line 516 "parser.y"
{
    ASTNode *idNode =
        createNode("ID",(yyvsp[-4].str),NULL,NULL,NULL);

    (yyval.node) = createNode("ASSIGN","=",idNode,(yyvsp[-1].node),NULL);

    c=0;
}
#line 1795 "parser.tab.c"
    break;

  case 51: /* exp: ID  */
#line 527 "parser.y"
{
    if(c==0)
    {
        c=1;
        int sct=returnscope((yyvsp[0].str),stack[top-1]);
        b=returntype((yyvsp[0].str),sct);
    }
    else
	{
    int sct1=returnscope((yyvsp[0].str),stack[top-1]);
    // temporarily skip strict type checking
	}

    (yyval.node) = createNode("ID",(yyvsp[0].str),NULL,NULL,NULL);
}
#line 1815 "parser.tab.c"
    break;

  case 52: /* exp: exp '+' exp  */
#line 544 "parser.y"
{
    (yyval.node) = createNode("ADD","+",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1823 "parser.tab.c"
    break;

  case 53: /* exp: exp '-' exp  */
#line 549 "parser.y"
{
    (yyval.node) = createNode("SUB","-",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1831 "parser.tab.c"
    break;

  case 54: /* exp: exp '*' exp  */
#line 554 "parser.y"
{
    (yyval.node) = createNode("MUL","*",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1839 "parser.tab.c"
    break;

  case 55: /* exp: exp '/' exp  */
#line 559 "parser.y"
{
    (yyval.node) = createNode("DIV","/",(yyvsp[-2].node),(yyvsp[0].node),NULL);
}
#line 1847 "parser.tab.c"
    break;

  case 56: /* exp: '(' exp ')'  */
#line 564 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1855 "parser.tab.c"
    break;

  case 57: /* exp: consttype  */
#line 569 "parser.y"
{
    (yyval.node) = createNode("NUM",(yyvsp[0].str),NULL,NULL,NULL);
}
#line 1863 "parser.tab.c"
    break;

  case 60: /* Declaration: Type ID '=' consttype ';'  */
#line 579 "parser.y"
        {
		if( (!(strspn((yyvsp[-1].str),"0123456789")==strlen((yyvsp[-1].str)))) && (yyvsp[-4].ival)==258)
			{printf("\nError : Type Mismatch : Line %d\n",printline());errc++;}
                else if ((yyvsp[-4].ival)==273)  {printf("\nError : Type Mismatch : Line %d\n",printline());errc++;}
		if(!lookup((yyvsp[-3].str)))
		{
			int currscope=stack[top-1];
			int previous_scope=returnscope((yyvsp[-3].str),currscope);
			if(currscope==previous_scope)
				{printf("\nError : Redeclaration of %s : Line %d\n",(yyvsp[-3].str),printline());errc++;}
			else
			{
				insert_dup((yyvsp[-3].str),(yyvsp[-4].ival),currscope);
				check_scope_update((yyvsp[-3].str),(yyvsp[-1].str),stack[top-1]);
			}
		}
		else
		{
			int scope=stack[top-1];
			insert((yyvsp[-3].str),(yyvsp[-4].ival));
			insertscope((yyvsp[-3].str),scope);
			check_scope_update((yyvsp[-3].str),(yyvsp[-1].str),stack[top-1]);
		}
            ASTNode *idNode =
            createNode("ID",(yyvsp[-3].str),NULL,NULL,NULL);

        ASTNode *valueNode =
            createNode("NUM",(yyvsp[-1].str),NULL,NULL,NULL);

        (yyval.node) = createNode("DECL","=",idNode,valueNode,NULL);
	}
#line 1899 "parser.tab.c"
    break;

  case 61: /* Declaration: Type ID ';'  */
#line 612 "parser.y"
        {
        	if(!lookup((yyvsp[-1].str)))
		{
			int currscope=stack[top-1];
			int previous_scope=returnscope((yyvsp[-1].str),currscope);
			if(currscope==previous_scope)
				{printf("\nError : Redeclaration of %s : Line %d\n",(yyvsp[-1].str),printline());errc++;}
			else
			{
				insert_dup((yyvsp[-1].str),(yyvsp[-2].ival),currscope);
				//check_scope_update($2,$4,stack[top-1]);
			}
		}
		else
		{
			int scope=stack[top-1];
			//printf("%d",type);
			insert((yyvsp[-1].str),(yyvsp[-2].ival));
			insertscope((yyvsp[-1].str),scope);
			//check_scope_update($2,$4,stack[top-1]);
		}
        ASTNode *idNode =
        createNode("ID",(yyvsp[-1].str),NULL,NULL,NULL);

        (yyval.node) = createNode("DECL",(yyvsp[-1].str),idNode,NULL,NULL);
	}
#line 1930 "parser.tab.c"
    break;

  case 62: /* Declaration: Type ID '[' consttype ']' ';'  */
#line 638 "parser.y"
                                        {
                       int itype;
                       if(!(strspn((yyvsp[-2].str),"0123456789")==strlen((yyvsp[-2].str)))) { itype=259; } else itype = 258;
                       if(itype!=258)
                       { printf("\nError : Array index must be of type int : Line %d\n",printline());errc++;}
                       if(atoi((yyvsp[-2].str))<=0)
                       { printf("\nError : Array index must be of type int > 0 : Line %d\n",printline());errc++;}
                       if(!lookup((yyvsp[-4].str)))
		       {
			int currscope=stack[top-1];
			int previous_scope=returnscope((yyvsp[-4].str),currscope);
			if(currscope==previous_scope)
				{printf("\nError : Redeclaration of %s : Line %d\n",(yyvsp[-4].str),printline());errc++;}
			else
			{

				insert_dup((yyvsp[-4].str),ARRAY,currscope);
                                insert_by_scope((yyvsp[-4].str),(yyvsp[-5].ival),currscope);	//to insert type to the correct identifier in case of multiple entries of the identifier by using scope
                                if (itype==258) {insert_index((yyvsp[-4].str), atoi((yyvsp[-2].str)));}
			}
		      }
		      else
		      {
			int scope=stack[top-1];
                        insert((yyvsp[-4].str),ARRAY);
			insert((yyvsp[-4].str),(yyvsp[-5].ival));
			insertscope((yyvsp[-4].str),scope);
                        if (itype==258) {insert_index((yyvsp[-4].str), atoi((yyvsp[-2].str)));}
		      }
        ASTNode *idNode = createNode("ID", (yyvsp[-4].str), NULL, NULL, NULL);
        ASTNode *sizeNode = createNode("NUM", (yyvsp[-2].str), NULL, NULL, NULL);
        (yyval.node) = createNode("DECL_ARRAY", (yyvsp[-4].str), idNode, sizeNode, NULL);
		    }
#line 1968 "parser.tab.c"
    break;

  case 63: /* Declaration: STRUCT ID '{' stmtlist '}' ';'  */
#line 671 "parser.y"
                                         {
						insert((yyvsp[-4].str),STRUCT);
                        (yyval.node) = createNode("STRUCT_DECL", (yyvsp[-4].str), (yyvsp[-2].node), NULL, NULL);
						}
#line 1977 "parser.tab.c"
    break;

  case 64: /* Declaration: STRUCT ID ID ';'  */
#line 675 "parser.y"
                           {
				insert((yyvsp[-1].str),STRUCT_VAR);
                (yyval.node) = createNode("STRUCT_VAR_DECL", (yyvsp[-1].str), createNode("ID", (yyvsp[-2].str), NULL, NULL, NULL), NULL, NULL);
				}
#line 1986 "parser.tab.c"
    break;


#line 1990 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 684 "parser.y"


#include<ctype.h>

void printAST(ASTNode *node, int level)
{
    ASTNode *curr = node;
    while(curr != NULL)
    {
        for(int i = 0; i < level; i++)
            printf("  ");

        printf("%s", curr->type);
        if(curr->value && strlen(curr->value) > 0)
            printf(" (%s)", curr->value);
        printf("\n");

        if(curr->left)
            printAST(curr->left, level + 1);
        if(curr->middle)
            printAST(curr->middle, level + 1);
        if(curr->right)
            printAST(curr->right, level + 1);

        curr = curr->next;
    }
}

char* generateTAC(ASTNode *node)
{
    if(node == NULL)
        return "";
	ASTNode *curr = node;

while(curr != NULL)
{
    // ---------- FUNCTION ----------
    if(strcmp(curr->type,"FUNCTION")==0)
    {
        emit("");

        char label[100];

        sprintf(label,"\nFUNC %s:",curr->value);

        emit(label);

        generateTAC(curr->left);

        curr = curr->next;
        continue;
    }

    // ---------- NUMBER ----------
    if(strcmp(curr->type,"NUM")==0)
    {
        return curr->value;
    }

    // ---------- ID ----------
    if(strcmp(curr->type,"ID")==0)
    {
        return  curr->value;;
    }

    // ---------- ADD ----------
    if(strcmp(curr->type,"ADD")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s + %s",
                temp,left,right);

        emit(code);

        return temp;
    }

    // ---------- SUB ----------
    if(strcmp(curr->type,"SUB")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s - %s",
                temp,left,right);

        emit(code);

        return temp;
    }

    // ---------- MUL ----------
    if(strcmp(curr->type,"MUL")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s * %s",
                temp,left,right);

        emit(code);

        return temp;
    }

    // ---------- DIV ----------
    if(strcmp(curr->type,"DIV")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s / %s",
                temp,left,right);

        emit(code);

        return temp;
    }
	// ---------- RELATIONAL ----------
	if(
    	strcmp(curr->type,"LT")==0 ||
    	strcmp(curr->type,"GT")==0 ||
    	strcmp(curr->type,"LE")==0 ||
    	strcmp(curr->type,"GE")==0 ||
    	strcmp(curr->type,"EQ")==0 ||
    	strcmp(curr->type,"NE")==0
	)
	{
    char *left = generateTAC(curr->left);

    char *right = generateTAC(curr->right);

    char *temp = newTemp();

    char code[100];

    sprintf(code,
        "%s = %s %s %s",
        temp,
        left,
       	curr->value ,
        right);

    emit(code);

    return temp;
	}
    // ---------- ASSIGN ----------
    if(strcmp(curr->type,"ASSIGN")==0)
    {
        char *rhs = generateTAC(curr->right);

        char code[100];

        sprintf(code,"%s = %s",
                curr->left->value,
                rhs);

        emit(code);

        curr = curr->next;
        continue;
    }
    // ---------- CALL ----------
    if(strcmp(curr->type,"CALL")==0)
    {
        char *temp = newTemp();
        char code[100];
        sprintf(code,"%s = call %s", temp, curr->value);
        emit(code);
        return temp;
    }
    // ---------- COMMA ----------
    if(strcmp(curr->type,"COMMA")==0)
    {
        generateTAC(curr->left);
        return generateTAC(curr->right);
    }
    // ---------- DECL ----------
    if(strcmp(curr->type,"DECL")==0)
    {
        if(curr->right != NULL)
        {
            char code[100];

            sprintf(code,
                "%s = %s",
                curr->left->value,
                curr->right->value);

            emit(code);
        }

        curr = curr->next;
        continue;
    }
    // ---------- WHILE ----------
    if(strcmp(curr->type,"WHILE")==0)
    {
        char *start = newLabel();

        char *end = newLabel();

        char code[100];

        sprintf(code,"%s:",start);
        emit(code);

        char *cond =
            generateTAC(curr->left);

        sprintf(code,
            "ifFalse %s goto %s",
            cond,end);

        emit(code);

        generateTAC(curr->right);

        sprintf(code,"goto %s",start);
        emit(code);

        sprintf(code,"%s:",end);
        emit(code);
        curr = curr->next;
        continue;
    }
        // ---------- IF ----------
    if(strcmp(curr->type,"IF")==0)
    {
        char *end = newLabel();

        char code[100];

        char *cond =
            generateTAC(curr->left);

        sprintf(code,
                "ifFalse %s goto %s",
                cond,end);

        emit(code);

        generateTAC(curr->right);

        sprintf(code,"%s:",end);

        emit(code);
        curr = curr->next;
        continue;    }
        // ---------- IF ELSE ----------
    if(strcmp(curr->type,"IFELSE")==0)
    {
        char *elseLabel = newLabel();

        char *endLabel = newLabel();

        char code[100];

        char *cond =
            generateTAC(curr->left);

        sprintf(code,
                "ifFalse %s goto %s",
                cond,elseLabel);

        emit(code);

        generateTAC(curr->right);

        sprintf(code,
                "goto %s",
                endLabel);

        emit(code);

        sprintf(code,"%s:",elseLabel);

        emit(code);

        generateTAC(curr->middle);

        sprintf(code,"%s:",endLabel);

        emit(code);
        curr = curr->next;
        continue;
    }
    // ---------- FOR ----------
    if(strcmp(curr->type,"FOR")==0)
    {
        char *start = newLabel();

        char *end = newLabel();

        char code[100];

        // INIT
        generateTAC(curr->left);

        sprintf(code,"%s:",start);
        emit(code);

        // CONDITION
        char *cond =
         generateTAC(curr->right);

        sprintf(code,
            "ifFalse %s goto %s",
            cond,end);

        emit(code);

        // BODY
        generateTAC(curr->next);

        // UPDATE
        generateTAC(curr->middle);

        sprintf(code,"goto %s",start);

        emit(code);

        sprintf(code,"%s:",end);

        emit(code);
        curr = curr->next;
        continue;
    }
        // ---------- RETURN ----------
    if(strcmp(curr->type,"RETURN")==0)
    {
        char code[100];

        sprintf(code,
                "return %s",
                curr->value);

        emit(code);
        curr = curr->next;
        continue;
    }
        // ---------- PRINT ----------
    if(strcmp(curr->type,"PRINT")==0)
    {
        char code[100];

        sprintf(code,
                "print %s",
                curr->value);

        emit(code);
        curr = curr->next;
        continue;
    }
    curr = curr->next;
    }

    return "";
}
int main(int argc, char *argv[])

{
    yyin = fopen(argv[1], "r");

    if(!yyparse() && errc<=0)
    {
        printf("\nParsing Completed\n");
        display();
        
        printf("\nAbstract Syntax Tree (AST):\n");
        printAST(root, 0);

		generateTAC(root);
        // ----------- PRINT TAC -----------
        printf("\nThree Address Code:\n");
        for(int i=0;i<tacIndex;i++) {
            printf("%s\n", tac[i]);
        }

        // ----------- SAVE TAC TO FILE -----------
        FILE *fp = fopen("tac.txt", "w");
        if(fp == NULL) {
            printf("Error opening file!\n");
            return 1;
        }

        for(int i=0;i<tacIndex;i++) {
            fprintf(fp, "%s\n", tac[i]);
        }

        fclose(fp);

        printf("\nTAC saved to tac.txt\n");
    }
    else
    {
        printf("\nParsing Failed\n");
        display();
    }

    fclose(yyin);
    return 0;
}


int yyerror(char *s)
{
    printf("\nLine %d : %s %s\n",yylineno,s,yytext);
	return 0;
}

int printline()
{
	return yylineno;
}
void push()
{
	stack[top]=i;
	i++;
	top++;
	return;
}
void pop()
{
	top--;
	end[stack[top]]=1;
	stack[top]=0;
	return;
}
