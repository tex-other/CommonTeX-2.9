
/*
 * @(#)tex.h 2.6 EPA
 *
 * Copyright 1987,1988 Pat J Monardo
 *
 * Redistribution of this file is permitted through
 * the specifications in the file COPYING.
 *
 * 
 */

#include    <stdio.h>
#include    <signal.h>
#include    <time.h>
/*#include 	<sys/time.h>*/

/*
 * constants in the outer block
 */

#define NUL                 '\0'
#define EOLN                '\n'
#define FALSE               0
#define TRUE                1
#define EMPTY               0


#define BUF_SIZE            500
#define DVI_BUF_SIZE        4096
#define ERROR_LINE          64
#define FILE_NAME_SIZE      104
#define FONT_BASE           0
#define FONT_MAX            150
#define FONT_MEM_SIZE       25000
#define HALF_BUF            2048
#define HALF_ERROR_LINE     32
#define HASH_SIZE           3000
#define HASH_PRIME          2551
#define HYPH_SIZE           307
#define MAX_IN_OPEN         15
#define MAX_PRINT_LINE      72
#define MAX_STRINGS         4400
#define NEST_SIZE           40
#define PARAM_SIZE          30
#define POOL_SIZE           20000
#define SAVE_SIZE           600
#define STACK_SIZE          200
#define STRING_VACANCIES    1000
#define TRIE_OP_HASH_SIZE   512
#define TRIE_SIZE           8000

#ifdef BIG
#define MEM_BOT             0
#define MEM_TOP             50000
#define TOK_BOT             0
#define TOK_TOP             30000
#ifdef INIT
#define MEM_MIN             MEM_BOT
#define MEM_MAX             MEM_TOP
#define TOK_MIN             TOK_BOT
#define TOK_MAX             TOK_TOP
#else
#define MEM_MIN             0
#define MEM_MAX             55000
#define TOK_MIN             0
#define TOK_MAX             55000
#endif
#define MIN_QUARTERWORD     0
#define MAX_QUARTERWORD     255
#define MIN_HALFWORD        0
#define MAX_HALFWORD        65535
#endif

#ifdef BIGG
#define MEM_BOT             0
#define MEM_TOP             250000
#define TOK_BOT             0
#define TOK_TOP             30000
#ifdef INIT
#define MEM_MIN             MEM_BOT
#define MEM_MAX             MEM_TOP
#define TOK_MIN             TOK_BOT
#define TOK_MAX             TOK_TOP
#else
#define MEM_MIN             0
#define MEM_MAX             524200
#define TOK_MIN             0
#define TOK_MAX             55000
#endif
#define MIN_QUARTERWORD     0
#define MAX_QUARTERWORD     255
#define MIN_HALFWORD        0
#define MAX_HALFWORD        655350
#endif

#if !defined(BIGG) && !defined(BIG)
#define MEM_BOT             0
#define MEM_TOP             30000
#define TOK_BOT             0
#define TOK_TOP             30000
#ifdef INIT
#define MEM_MIN             MEM_BOT
#define MEM_MAX             MEM_TOP
#define TOK_MIN             TOK_BOT
#define TOK_MAX             TOK_TOP
#else
#define MEM_MIN             0
#define MEM_MAX             35000
#define TOK_MIN             0
#define TOK_MAX             35000
#endif
#define MIN_QUARTERWORD     0
#define MAX_QUARTERWORD     255
#define MIN_HALFWORD        0
#define MAX_HALFWORD        65535
#endif

/*
 *  types in the outer block
 */

#define global      extern
#if defined(BIG) || defined(BIGG)
typedef unsigned char   qword;
typedef unsigned long   hword;
#else
typedef unsigned char   qword;
typedef unsigned short  hword;
#endif
typedef unsigned char   ascii;
typedef int             bool;
typedef unsigned char   byte;
typedef char *          chrs;
typedef int             fnt;
typedef unsigned char   gord;
typedef float           gratio;
typedef int             group;
typedef hword           ptr;
typedef long            scal;
typedef hword           str;
typedef hword           tok;
typedef long            val;
typedef FILE            *word_file;
typedef FILE            *alpha_file;            
typedef FILE            *byte_file;
typedef union { 
    struct { 
        hword   rh; 
        hword   lh; 
    } hh1; 
    struct { 
        hword   rh; 
        qword   b0; 
        qword   b1; 
    } hh2; 
} hh;
typedef struct { 
    qword   b0;
    qword   b1;
    qword   b2;
    qword   b3;
} qqqq;
typedef union { 
    hh      hh;  
    qqqq    qqqq;
    long    i;   
    gratio  gr;  
} mword;

/*
 *  variables in the outer block
 */

global  char        banner[];
global  int         ready_already;

/*
 *  functions in the outer block
 */

int     final_cleanup();
int     close_files_and_terminate();
int     initialize();
bool    decode_args();
int     handle_int();
int     call_edit();

/*
 * some common programming idioms
 */

#define sc                  i
#define incr(i)             ++(i)
#define decr(i)             --(i)
#define odd(i)              ((i) & 1)
#define abs(i)              ((i) >= 0 ? (i) : -(i))
#define round(x)            (long) ((x) > 0.0 ? ((x) + 0.5) : ((x) - 0.5))
#define negate(x)           (x) = -(x)
#define loop                while (1)
#include "cmds.h"
#include "char.h"
#include "str.h"
#include "io.h"
#include "print.h"
#include "error.h"
#include "heap.h"
#include "eq.h"
#include "hash.h"
#include "arith.h"
