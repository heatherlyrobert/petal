/*=============================[[ beg-of-code ]]==============================*/ 



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     ""
#define     P_NICHE     ""
#define     P_SUBJECT   "artistic pen-based writing"
#define     P_PURPOSE   "provide beautiful and efficient pen-based text input"

#define     P_NAMESAKE  "khloris-nympha (flowering)"
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (less than 1,000 slocl)"
#define     P_DEPENDS   ""

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2009-05"

#define     P_VERMAJOR  "3.-- third major phase"
#define     P_VERMINOR  "3.0- ramped the beauty way up ;)"
#define     P_VERNUM    "3.0d"
#define     P_VERTXT    "ribbon showing with representative icons"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

#define     P_DEFINE    \
   "petal is a potentially fast on-screen text input system for when i am¦" \
   "working on a pen-based system, or using a pen-based application and¦" \
   "need to enter text as well (without slowing down).¦"


/*===[[ HEADER ]]=============================================================#

 *   focus         : (UI) user input
 *   niche         : (pe) pen-based writing
 *   application   : petal
 *   purpose       : provide efficient, effective pen-based written input
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : X, opengl, yFONT, yX11
 *   size          : small       (~2,000 slocL)
 * 
 *   author        : heatherly
 *   created       : 2009-05
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 *
 */
/*===[[ SUMMARY ]]=============================================================*

 *   petal is a fast on-screen text input system meant to greatly improve upon
 *   other pen-based methods in speed, sustainability, and elegance by fronting
 *   an entire set of short-cuts to the most common words in english.
 *
 */
/*---[[ PURPOSE ]]------------------------------------------------*

 *   petal is a alternative pen-based writing system that seeks to compete with,
 *   replace, and greatly improve upon existing onscreen keyboard systems when
 *   a physical keyboard is either not available or undesireable.  it is then
 *   expected to greatly excel onscreen other methods through the use of custom
 *   and advanced techniques that are unlikely to make it into mainstream
 *   programs or require several separate systems working in tandem.
 *
 *   building a custom input system, like petal, will allow us to build in
 *   things like keyboard short cuts that can not be built into keyboards or
 *   into keyboard mappers/drivers.  normally these have to be scripted into
 *   each individual application, require a entire desktop environment that
 *   allows special applications to intercept keys (specific to the DE), or we
 *   would need to hack the actual window manager.
 *
 *   petal is never expected to wholely replace any of the following techniques
 *   that we will also be aggressively investigating...
 *      - keyboard input
 *      - voice control and input
 *      - shorthand system
 *      - physical writing
 *      - etc
 *
 *   the idea behind the system is to build up the ability to desengage from
 *   keyboards on pen based systems and free up the space, fuss, and equipment
 *   overhead.  it also will work well in environments where privacy precludes
 *   voice input.  finally, it is in itself a very unintelligible system to the
 *   untrained and so its own layer of security
 *
 *   it is not yet known whether the petal writing system will significantly
 *   slow down input after a sufficent learning curve as the method is unproven.
 *   but, we do have strong suspiscions that it will reduce pressure on the
 *   hands and allow a much smaller input form-factor than needing a physical
 *   keyboard.  all-in-all, it is meant to compete favorably against onscreen
 *   keyboards, not the physical kind.
 *
 *   no matter what, its great for the brain, great for creativity, fun, and
 *   a solid programming project to learn from.
 *
 *   petal stands exactly a zero percent chance of being acceptable to anyone
 *   except us as its power comes from alternative techniques that require time
 *   and willpower to master.  rather than being a bad thing, this frees us up
 *   to drive petal as far as we can as we have both the time and willpower to
 *   invest.
 *
 *   petal will focus on...
 *      - having a small visual/window footprint
 *      - using strokes for character input rather than pecking/presses
 *      - all basic stokes are clean, distinct, and fluid; no direction changes
 *      - allowing stokes to be run together to increase potential speed
 *      - integrating hublin shortcuts to drive even more speed
 *      - having all characters that are available on colemak-arensito keyboard
 *      - placing the resulting characters in any window as if typed there
 *
 *   for learning purposes it will...
 *      - use opengl for all drawing (including solid aesthetics)
 *      - calculate positions for input rather than using widgets/buttons
 *      - attempt to draw onto a preprepared bitmap to increase efficiency
 *      - overall, learn more about xwindows and opengl
 *
 *   petal will not focus on...
 *      - spelling (there are other tools for that)
 *      - any other input method as a backup
 *
 *   there are many, stable, accepted, existing programs and utilities have
 *   been built by better programmers and are likely superior in speed, size,
 *   capability, and reliability; BUT, i would not have learned nearly as much
 *   using them, so i follow the adage..
 *
 */
/*===((END DOC))==============================================================*/



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YPETAL
#define YPETAL loaded



/*===[[ CLIB HEADERS ]]=======================================================*/
#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>
#include    <string.h>
#include    <unistd.h>
#include    <ctype.h>
#include    <time.h>
#include    <sys/time.h>
#include    <fcntl.h>             /* clibc standard file control              */



/*===[[ HEATHERLY HEADERS ]]==================================================*/
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(vi-keys foundation)----------------*/
#include    <yMODE.h>             /* heatherly vikeys mode tracking           */
#include    <yKEYS.h>             /* heatherly vikeys key handling            */
#include    <yVIEW.h>             /* heatherly vikeys view management         */
/*---(vi-keys major)---------------------*/
#include    <yMAP.h>              /* heatherly vikeys location management     */
#include    <yCMD.h>              /* heatherly vikeys command processing      */
#include    <yMACRO.h>            /* heatherly vikeys macro processing        */
/*---(custom opengl)---------------------*/
#include    <yVIHUB.h> 
#include    <yVIOPENGL.h>    /* heatherly vikeys curses handler          */
#include    <yX11.h>         /* CUSTOM  heatherly xlib/glx setup/teardown     */
#include    <yFONT.h>        /* CUSTOM  heatherly texture-mapped fonts        */
#include    <yGLTEX.h>       /* CUSTOM  heatherly texture handling            */
#include    <yPARSE.h>
#include    <yCOLOR.h>



/*---(X11 standard)----------------------*/
#include   <X11/X.h>              /* X11    standard overall file             */
#include   <X11/Xlib.h>           /* X11    standard C API                    */
#include    <X11/extensions/shape.h>    /* shape extention -- funky windows    */
/*---(opengl standard)-------------------*/
#include   <GL/gl.h>              /* opengl standard primary header           */
#include   <GL/glx.h>             /* opengl standard X11 integration          */






#define   MAXWORD      50

typedef   unsigned int     uint;
typedef   unsigned char    uchar;
typedef   long long        llong;


typedef     struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(overall)--------------*/
   char        version     [LEN_FULL];  /* version reporting string            */
   char        progname    [LEN_FULL];  /* program name                        */
   char        win_title   [LEN_FULL];
   char        n_event     [LEN_FULL];
   FILE       *f_event;
   char        audit;
   /*---(tablet)---------------*/
   int         t_left;
   int         t_topp;
   int         t_wide;
   int         t_tall;
   int         t_x;
   int         t_y;
   /*---(screen)---------------*/
   int         s_left;
   int         s_topp;
   int         s_wide;
   int         s_tall;
   float       s_xratio;
   float       s_yratio;
   int         s_x;
   int         s_y;
   /*---(window)---------------*/
   int         w_left;
   int         w_topp;
   int         w_wide;
   int         w_tall;
   /*---(main·petal)-----------*/
   int         m_left;
   int         m_topp;
   int         m_wide;
   int         m_tall;
   char        m_align;
   char        m_valid;
   char        m_touch;
   int         m_x;
   int         m_y;
   int         m_r;
   /*---(opengl objects)-----------------*/
   uint        g_tex;                    /* task texture                      */
   uint        g_fbo;                    /* task fbo                          */
   uint        g_dep;                    /* task depth                        */
   int         g_wide;
   int         g_tall;
   /*---(fonts)----------------*/
   char        face_bg     [LEN_FULL];
   char        face_sm     [LEN_FULL];
   int         txf_bg;
   int         txf_sm;
   int         size_big;
   int         size_norm;
   /*---(files)-----------------*/
   char        name_event  [LEN_FULL];  /* name of event device                */
   FILE       *file_event;             /* pointer to event device             */
   /*---(flags)----------------*/
   char        rptg_events;            /* request to dump events to screen    */
   int         ev_major;               /* which ev_code to show               */
   int         ev_minor;               /* which ev_code to show               */
   char        rptg_dots;              /* request to dump dots to screen      */
   char        rptg_recog;             /* request to dump regcognition        */
   char        show_balls;
   char        save_png;
   char        mask;     
   char        guides;
   int         icons;
   /*---(arguments)-------------*/
   long        loop_msec;              /* wait time in milliseconds           */
   /*---(done)------------------*/
};
extern      tACCESSOR   my;

#define     ICON_SET  "/usr/local/share/fonts/outline_icons.png"

#define     RPTG_DOTS           if (my.rptg_dots    == 'y')
#define     RPTG_EVENTS         if (my.rptg_events  == 'y')
#define     RPTG_RECOG          if (my.rptg_recog   == 'y')


/*---(directory names)--------------------------*/
#define     DIR_INPUT        "/dev/input/"

/*---(file names)-------------------------------*/
/*> #define     FILE_EVENT       "event16"                                            <*/
#define     FILE_EVENT       "event7"
#define     FILE_CONF        "/etc/petal.conf"


/*===[[ drawing semi-constants ]]=============================================*/
/* values are established in petal.c                                          */

extern const float  DEG2RAD;
extern const float  RAD2DEG;

typedef     struct cSTROKE tSTROKE;
struct cSTROKE {
   int             x;
   int             y;
   int             ring;
   int             petal;
   int             max;
   int             zth;
   int             fst;
   int             snd;
   int             trd;
   int             fth;
   int             ndx;
   char            text[5];
   char            owner;
   int             last_max;
   int             last_0th;
   int             last_1st;
   int             last_2nd;
   int             last_3rd;
   int             last_4th;
   /*---(flags)---------------------------*/
   int             fail;
   int             pass;
   int             done;
   char            help;
   char            help_txt  [LEN_LABEL];
   char            feedback[MAXWORD];
   int             backwards;
   char           *focus_name;
   char            name[100];
   int             startx;
   int             starty;
   char            outward;
   char            section;         /* which section of the screen is active */
   int             small;            /* half size format                      */
   int             channel;
   llong           beg;
   llong           end;
   llong           diff;
};
extern      tSTROKE     stroke;

extern      int       curr_x;
extern      int       curr_y;
extern      float     curr_r;


typedef     struct cPETAL  tPETAL;
struct cPETAL {
   int         x, y, r, d;
   char        n, p;
};

extern tPETAL  g_petals [LEN_TERSE];






#define         TNY   0
#define         SML   1
#define         MED   2
#define         NOR   3
#define         LRG   4
#define         HUG   5
#define         GIA   6
#define         HORZ_LL       1050
#define         HORZ_L        1075
#define         HORZ_R        1100
#define         HORZ_RR       1125


/*---(display lists)---------------*/
typedef     struct cSHAPES  tSHAPES;
struct cSHAPES {
   /*---(displaylists)-------*/
   uint        dl_center;
   uint        dl_ring;
   uint        dl_inner;
   uint        dl_buffer;
   uint        dl_outer;
   uint        dl_edge;
   uint        dl_leaf;
   uint        dl_curr;
   uint        dl_box;
   uint        dl_triangle;
   uint        dl_arrow;
   uint        dl_belly;
   uint        dl_orient;
   uint        dl_balls;
   uint        dl_touch;
   uint        dl_touch2;
   uint        dl_back;
   /*---(sizing)-------------*/
   int         sz_height;
   int         sz_width;
   int         sz_centery;
   int         sz_centerx;
   int         sz_bar;
   int         sz_ctl;
   int         sz_nav;
   /*---(guides)-------------*/
   int         g_center;          /* center ring radius                  */
   int         g_ring;            /* inner petal foregiveness radius     */
   int         g_inner;           /* radius of inner petals              */
   int         g_outer;           /* radius of outer petals              */
   int         g_edge;            /* radius of final edge petals         */
   /*---(radius)-------------*/
   float       r_center;          /* center ring radius                  */
   float       r_ring;            /* inner petal foregiveness radius     */
   float       r_inner;           /* radius of inner petals              */
   float       r_buffer;          /* outer petal foregiveness radius     */
   float       r_outer;           /* radius of outer petals              */
   float       r_edge;            /* radius of final edge petals         */
   float       r_max;             /* radius of petal extent              */
   float       r_lines;           /* normal shape borders                */
   float       r_dots;            /* dot line width                      */
   float       r_curr;            /* circle radius for marking current   */
   char        r_eng  [LEN_RECD]; /* requested text to recreate          */
   char        r_seq  [LEN_RECD]; /* letter or series of letters         */
   short       r_len;             /* count of letters in seq             */
   short       r_pos;             /* current position in seq             */
   char        r_mode;            /* loop, cum, all same time, etc.      */
   char        r_letter;          /* current letter for drawing          */
   short       r_exec;            /* current letter position             */
   char        r_loc;             /* current letter index                */
   char        r_state;           /* current letter state                */
   char        r_done [LEN_RECD]; /* letters as entered                  */
   char        r_done_show;       /* show letter display or not          */
   char        r_debug;           /* show internal debugging info        */
   float       r_trace;           /* current stroke width                */
   float       r_prog;            /* progress in current stroke          */
   char        r_color; 
   char        r_color_txt;
   float       r_inc;             /* progress increment on stroke        */
   char        r_inc_txt;         /* progress increment on stroke        */
   float       r_button;
};
extern    tSHAPES       shape;

extern ulong  g_focus;

extern uint   states[10];
extern uint   locks [10];



/*---(dot trace)------------------*/
struct cDOTS_OLD {
   int         tries;         /* place in raw data stream                     */
   int         absx;          /* dots screen-absolute x-coordinate            */
   int         absy;          /* dots screen-absolute y-coordinate            */
   int         relx;          /* dots center-relative x-coordinate            */
   int         rely;          /* dots center-relative y-coordinate            */
   float       delta;         /* change from last point                       */
   float       radius;        /* distance from center                         */
};


#define     MAX_DOTS    1000
typedef     struct      cDOTS       tDOTS;
struct cDOTS {
   char        d_place;       /* beg, end, or normal                          */
   int         d_seq;         /* place in raw source data stream              */
   int         d_tx;          /* tablet x, y   for debug, testing, etc        */
   int         d_ty;
   int         d_sx;          /* screen x, y   for debug, testing, etc        */
   int         d_sy;
   int         d_wx;          /* window x, y, r                               */
   int         d_wy;
   int         d_wr;
   int         d_wd;          /* distance from last point                     */
};
extern      tDOTS       g_dots        [MAX_DOTS];
extern      int         g_ndot;



/*---(convienence typedefs)-------------------------------------*/
typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;

/*> typedef struct FILE      tFILE;                                                   <* 
 *> typedef struct stat      tSTAT;                                                   <* 
 *> typedef struct passwd    tPASSWD;                                                 <* 
 *> typedef struct group     tGROUP;                                                  <* 
 *> typedef struct rusage    tRUSAGE;                                                 <* 
 *> typedef struct tm        tTIME;                                                   <* 
 *> typedef struct dirent    tDIRENT;                                                 <*/
typedef struct timespec  tTSPEC;


extern int  key_index[30];
extern int last_ring;
extern int last_petal;

/*---(saved letters)---------------*/
extern char      stroke_letter[MAXWORD];
extern int       stroke_index [MAXWORD];
extern ulong     stroke_keysym[MAXWORD];
extern int       stroke_count;

extern char          unit_answer [LEN_RECD];

/*===[[ DEBUGGING SETUP ]]====================================================*/
/* this is my latest standard format, vars, and urgents                       */
/* v3.0b : added signal handling                                (2014-feb-01) */
/*> struct cDEBUG                                                                      <* 
 *> {                                                                                  <* 
 *>    /+---(handle)-------------------------+/                                        <* 
 *>    int         logger;                 /+ log file so that we don't close it  +/   <* 
 *>    /+---(overall)------------------------+/  /+ abcdefghi_kl__opq_stu__x__    +/   <* 
 *>    /+ f = full urgents turns on all standard urgents                          +/   <* 
 *>    /+ k = kitchen sink and turns everything, i mean everything on             +/   <* 
 *>    /+ q = quiet turns all urgents off including the log itself                +/   <* 
 *>    char        tops;                   /+ t) broad structure and context      +/   <* 
 *>    char        summ;                   /+ s) statistics and analytical output +/   <* 
 *>    /+---(startup/shutdown)---------------+/                                        <* 
 *>    char        args;                   /+ a) command line args and urgents    +/   <* 
 *>    char        conf;                   /+ c) configuration handling           +/   <* 
 *>    char        prog;                   /+ p) program setup and teardown       +/   <* 
 *>    /+---(file processing)----------------+/                                        <* 
 *>    char        inpt;                   /+ i) text/data file input             +/   <* 
 *>    char        inpt_mas;               /+ I) text/data file input   (mas/more)+/   <* 
 *>    char        outp;                   /+ o) text/data file output            +/   <* 
 *>    char        outp_mas;               /+ O) text/data file output  (mas/more)+/   <* 
 *>    /+---(event handling)-----------------+/                                        <* 
 *>    char        loop;                   /+ l) main program event loop          +/   <* 
 *>    char        loop_mas;               /+ L) main program event loop (mas/more+/   <* 
 *>    char        user;                   /+ u) user input and handling          +/   <* 
 *>    char        apis;                   /+ z) interprocess communication       +/   <* 
 *>    char        sign;                   /+ x) os signal handling               +/   <* 
 *>    char        scrp;                   /+ b) scripts and batch operations     +/   <* 
 *>    char        hist;                   /+ h) history, undo, redo              +/   <* 
 *>    /+---(program)------------------------+/                                        <* 
 *>    char        graf;                   /+ g) grahpics, drawing, and display   +/   <* 
 *>    char        data;                   /+ d) complex data structure handling  +/   <* 
 *>    char        envi;                   /+ e) environment/filesystem           +/   <* 
 *>    char        envi_mas;               /+ E) environment/filesystem (mas/more)+/   <* 
 *>    /+---(specific)-----------------------+/                                        <* 
 *>    char        touch;                  /+    raw touch input                  +/   <* 
 *>    char        recog;                  /+    stroke recognition               +/   <* 
 *> };                                                                                 <* 
 *> typedef     struct      cDEBUG      tDEBUG;                                        <* 
 *> extern      tDEBUG      debug;                                                     <*/

/*> #define     DEBUG_TOPS          if (debug.tops      == 'y')                       <* 
 *> #define     DEBUG_SUMM          if (debug.summ      == 'y')                       <* 
 *> #define     DEBUG_ARGS          if (debug.args      == 'y')                       <* 
 *> #define     DEBUG_CONF          if (debug.conf      == 'y')                       <* 
 *> #define     DEBUG_PROG          if (debug.prog      == 'y')                       <* 
 *> #define     DEBUG_INPT          if (debug.inpt      == 'y')                       <* 
 *> #define     DEBUG_INPTM         if (debug.inpt_mas  == 'y')                       <* 
 *> #define     DEBUG_OUTP          if (debug.outp      == 'y')                       <* 
 *> #define     DEBUG_OUTPM         if (debug.outp_mas  == 'y')                       <* 
 *> #define     DEBUG_LOOP          if (debug.loop      == 'y')                       <* 
 *> #define     DEBUG_LOOPM         if (debug.loop_mas  == 'y')                       <* 
 *> #define     DEBUG_USER          if (debug.user      == 'y')                       <* 
 *> #define     DEBUG_APIS          if (debug.apis      == 'y')                       <* 
 *> #define     DEBUG_SIGN          if (debug.sign      == 'y')                       <* 
 *> #define     DEBUG_SCRP          if (debug.scrp      == 'y')                       <* 
 *> #define     DEBUG_HIST          if (debug.hist      == 'y')                       <* 
 *> #define     DEBUG_GRAF          if (debug.graf      == 'y')                       <* 
 *> #define     DEBUG_DATA          if (debug.data      == 'y')                       <* 
 *> #define     DEBUG_ENVI          if (debug.envi      == 'y')                       <* 
 *> #define     DEBUG_ENVIM         if (debug.envi_mas  == 'y')                       <*/

/*> #define     DEBUG_TOUCH         if (debug.touch     == 'y')                       <*/
/*> #define     DEBUG_RECOG         if (debug.recog     == 'y')                       <*/


#define   MAX_LETTER   40


extern char   g_lower    [MAX_LETTER];
extern char   g_upper    [MAX_LETTER];
extern char   g_greek    [MAX_LETTER];
extern char   g_arith    [MAX_LETTER];
extern char   g_logic    [MAX_LETTER];
extern char   g_boxdr    [MAX_LETTER];
extern char   g_macro    [MAX_LETTER];
extern char   g_punct    [MAX_LETTER];

extern char   g_fasts    [LEN_TERSE];
extern char   g_layer    [LEN_TERSE];

extern char   g_lowers   [LEN_TITLE];
extern char   g_uppers   [LEN_TITLE];
extern char   g_greeks   [LEN_TITLE];
extern char   g_ariths   [LEN_TITLE];
extern char   g_logics   [LEN_TITLE];
extern char   g_boxdrs   [LEN_TITLE];
extern char   g_macros   [LEN_TITLE];
extern char   g_puncts   [LEN_TITLE];

extern char  *g_shown;
extern char  *g_bases;
extern char  *g_letters;

extern char g_special[10];
extern int  g_akeysyms[40];
extern int  g_akeysyms_punct[40];
extern int  g_akeysyms_special[10];
extern char s_next[40];

#define  UNSET     -1
#define  FALSE      0
#define  TRUE       1


extern enum tSTATES {SHIFT = 0, MODE, CONTROL, ALT, HYPER, SUPER, HUBLIN, MYHUBLIN} eSTATES;

/*============================--------------------============================*/
/*===----                           prototypes                         ----===*/
/*============================--------------------============================*/




/*===[[ PROG ]]===============================================================*/
/*---(program)--------------*/
char*       PROG_version            (void);
/*---(preinit)---------------------------*/
char        PROG__header            (void);
char        PROG_urgents            (int a_argc, char *a_argv []);
/*---(startup)---------------------------*/
char        PROG__init              (int a_argc, char *a_argv []);
char        PROG__args              (int a_argc, char *a_argv []);
char        PROG__begin             (void);
char        PROG_startup            (int argc, char *argv[]);
/*---(execution)-------------------------*/
char        PROG_dawn               (void);
char        PROG_dusk               (void);
/*---(shutdown)--------------------------*/
char        PROG__end               (void);
char        PROG_shutdown           (void);
/*---(unittest)------------*/
char        PROG_testfiles          (void);
char        PROG_unit_quiet         (void);
char        PROG_unit_loud          (void);
char        PROG_unit_end           (void);
/*---(done)----------------*/

char        PROG_event              (void);


/*> char       DRAW_done_show           (char *a_flag);                               <*/
/*> char       DRAW_debug_set           (char *a_flag);                               <*/
char       DRAW_help                (char *a_help);
/*> char       DRAW_color               (char *a_help);                               <*/
char       DRAW_speed               (char *a_speed);
char       DRAW_press               (char *a_state);
char       DRAW_seq                 (char a_mode, char *a_seq);
char       DRAW_debug               (void);
char       DRAW_ribbon             (void);
char       DRAW_main              (void);
char       draw_delete       (void);
char       DRAW_back          (void);
char       DRAW__guides            (int r, int z);
char       DRAW__petals            (int n, int z);
char       DRAW_image        (void);
char       DRAW_labels       (void);
char       DRAW_context      (void);
char       DRAW_current      (void);
char       DRAW_locks        (void);
char       DRAW_arrows       (void);
char       DRAW_navigation   (void);
char       draw_controls     (void);
char       DRAW_dots         (void);
long        time_stamp         (void);

char       font_load            (void);
char       font_free            (void);
char       displist_init        (void);
char       displist_free        (void);
char       DRAW_resize          (uint, uint);
void       mouse_init           (void);

/*===[[ petal_shape.c ]]============================================================*/ 
/*---rc---- ---name---------------- ---args----------------------------------------*/
char        SHAPE_guides       (char a_option [LEN_LABEL]);
char        SHAPE_base         (char a_func [LEN_LABEL], float a_ratio);
char        SHAPE_tiny         (void);
char        SHAPE_small        (void);
char        SHAPE_medium       (void);
char        SHAPE_normal       (void);
char        SHAPE_large        (void);
char        SHAPE_huge         (void);
char        SHAPE_giant        (void);
char        SHAPE_size              (char *a_size);

/*===[[ petal_touch.c ]]============================================================*/ 
/*---rc---- ---name---------------- ---args----------------------------------------*/
char        TOUCH_reset             (void);
char        TOUCH_init              (void);
char        TOUCH__open             (char a_name [LEN_FULL], char a_dir, FILE **f);
char        TOUCH__close            (FILE **f);
char        TOUCH__normal           (void);
char        TOUCH__check            (void);
char        TOUCH__event_type       (int a_evtype, char *r_track, char r_desc [LEN_TERSE]);
char        TOUCH__event_code       (int a_evtype, int a_evcode, char *b_track, char r_desc [LEN_TERSE]);
char        TOUCH__single           (FILE *f, int *r_type, int *r_code, int *r_value, char *r_track, char a_out [LEN_FULL]);
char        TOUCH_read         (void);
char        TOUCH_close        (void);
/*---(unittest)-------------*/
char        TOUCH_force_data        (char a_name [LEN_FULL], int a_type, int a_code, int a_value);
char        TOUCH_force_tablet      (int a_left, int a_topp, int a_wide, int a_tall);
char        TOUCH_force_screen      (int a_left, int a_topp, int a_wide, int a_tall);
char        TOUCH_force_window      (int a_left, int a_topp, int a_wide, int a_tall, char a_align);
char        TOUCH_point             (int x, int y);
char*       TOUCH__unit             (char *a_question, int a_num);
/*---(done)-----------------*/



/*===[[ PETAL_PETAL.C ]]======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(program)--------------*/
char        PETAL_reset             (void);
char        PETAL_init              (void);
/*---(worker)---------------*/
char        PETAL__data             (int x, int y, int r, int *d, char *n, char *i, char *o);
char        PETAL__check            (int x, int y, int r);
/*---(simplifier)-----------*/
char        PETAL_beg               (int x, int y, int r);
char        PETAL_add               (int x, int y, int r);
char        PETAL_end               (int x, int y, int r);

/*---(unitetest)------------*/
char*       PETAL__unit             (char *a_question, int a_num);
/*---(done)-----------------*/


char        STROKE_begin      (int, int, int);
char        stroke_next       (int, int, int);
char        STROKE_end        (int, int, int);
/*---(done)-----------------*/



char       letter_init       (void);
int        letter_update     (int, int);
void       letter_interpret  (void);
char       event_navigation  (int);
char       event_arrows      (int, int);

char       hublin_find       (char* a_letters, ulong a_keysyms[]);

char       key_send_all      (char* a_letters, ulong a_keysyms[]);
void       key_send          (ulong a_keysym);

char*      unit_accessor     (char *a_question, int a_num);




/*===[[ petal_ymap.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(label)----------------*/
char        api_ymap_locator        (char a_strict, char *a_label, ushort *u, ushort *x, ushort *y, ushort *z);
char        api_ymap_addressor      (char a_strict, char *a_label, ushort u, ushort x, ushort y, ushort z);
/*---(load)-----------------*/
char        api_ymap_sizer          (char a_axis, ushort *n, ushort *a, ushort *b, ushort *c, ushort *e, ushort *m, ushort *x);
char        api_ymap_entry          (char a_axis, ushort a_pos, short *r_ref, uchar *r_wide, uchar *r_used);
/*---(update)---------------*/
char        api_ymap_placer         (char a_axis, ushort b, ushort c, ushort e);
char        api_ymap_done           (void);
/*---(done)-----------------*/



char        LETTER_by_index         (char n);
char        LETTER_by_stroke        (char f, char i, char o, char e);
char        LETTER_to_stroke        (char a_all, char c, char *m, char *i, char *o, char *e);
char        LETTER_by_mode          (char n);



/*===[[ PETAL_ARTSY.C ]]======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(program)--------------*/
char        ARTSY_resize            (void);
char        ARTSY_init              (void);
char        ARTSY_clear             (void);
/*---(leaves)---------------*/
char        ARTSY__bezier           (char a_type, float r1, float r2, float r3, float d1, float d2, float z, float a_cut);
char        ARTSY__inner            (float a_radius, float a_depth, uint *b_dlist);
char        ARTSY__outer            (float a_radius, float a_depth, uint *b_dlist);
char        ARTSY__edge             (float a_radius, float a_depth, uint *b_dlist);
/*---(shapes)---------------*/
char        ARTSY__center           (float a_radius, float a_depth, uint *b_dlist);
char        ARTSY__ball             (float a_radius, float a_depth, uint *b_dlist);
char        ARTSY__fast             (float a_radius, float a_depth, uint *b_dlist);
char        ARTSY__ring             (float a_radius, float a_depth, uint *b_dlist);
/*---(texture)--------------*/
char        ARTSY__start            (void);
char        ARTSY__finish           (void);
char        ARTSY__draw_fasts       (void);
char        ARTSY__draw_inners      (void);
char        ARTSY__draw_outers      (void);
char        ARTSY__draw_edges       (void);
char        ARTSY_draw              (void);
/*---(drawing)--------------*/
char        ARTSY_draw              (void);
char        ARTSY_show              (float a_wtop, float a_wlef, float a_wbot, float a_wrig);
char        ARTSY_mask              (char a_force, char a_ribbon, char a_float, char a_menu, char a_alt);
/*---(done)-----------------*/



/*===[[ PETAL_DOT.C ]]========================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(program)--------------*/
char        DOT_reset               (void);
char        DOT_init                (void);
/*---(worker)---------------*/
char        DOT__add                (char a_tst, char a_func [LEN_LABEL], int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr, char a_place);
/*---(simplifier)-----------*/
char        DOT_beg                 (int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr);
char        DOT_add                 (int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr);
char        DOT_end                 (int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr);
/*---(unittest)-------------*/
char        DOT_force_point         (int x, int y);
char        DOT_force_beg           (int a_wx, int a_wy);
char        DOT_force_add           (int a_wx, int a_wy);
char        DOT_force_end           (int a_wx, int a_wy);
char*       DOT__unit               (char *a_question, int a_num);
/*---(done)-----------------*/


/*===[[ PETAL_CONF.C ]]=======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(program)--------------*/
char        CONF_purge              (void);
char        CONF_init               (void);
/*---(parse)----------------*/
char        CONF__default           (int n, uchar a_verb [LEN_TERSE]);
char        CONF__load              (char a_dir [LEN_TERSE], char a_desc [LEN_TERSE], char a_seq, char a_field [LEN_LABEL], char a_bases [LEN_TITLE]);
char        CONF__mapping           (int n, uchar a_verb [LEN_TERSE]);
char        CONF__handler           (int n, uchar a_verb [LEN_TERSE], char a_exist, void *a_handler);
char        CONF_pull               (cchar a_file [LEN_PATH]);
/*---(unittest)-------------*/
char*       CONF__unit              (char *a_question, int a_num);
/*---(done)-----------------*/


#endif
