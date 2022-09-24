/*=============================[[ beg-of-code ]]==============================*/ 



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     ""
#define     P_NICHE     ""
#define     P_SUBJECT   "artistic pen-based writing"
#define     P_PURPOSE   ""

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

#define     P_VERMAJOR  ""
#define     P_VERMINOR  ""
#define     P_VERNUM    "2.2a"
#define     P_VERTXT    "switched to new vikeys and draw working again"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/
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
#include    <yVIOPENGL.h>    /* heatherly vikeys curses handler          */
#include    <yX11.h>         /* CUSTOM  heatherly xlib/glx setup/teardown     */
#include    <yFONT.h>        /* CUSTOM  heatherly texture-mapped fonts        */
#include    <yGLTEX.h>       /* CUSTOM  heatherly texture handling            */


#include    <ySTR.h>              /* heatherly safer string handling          */
#include    <yLOG.h>              /* heatherly programming tracing/logging    */

/*===[[ HEATHERLY HEADERS ]]==================================================*/
#include    <yX11.h>              /* heatherly xlib/glx setup/teardown        */
#include    <yGOD.h>              /* heatherly opengl godview                 */
#include    <yFONT.h>             /* heatherly texture-mapped fonts           */
#include    <yHUBLIN.h>           /* heatherly hublin shortcut library        */


/*---(X11 standard)----------------------*/
#include   <X11/X.h>              /* X11    standard overall file             */
#include   <X11/Xlib.h>           /* X11    standard C API                    */
/*---(opengl standard)-------------------*/
#include   <GL/gl.h>              /* opengl standard primary header           */
#include   <GL/glx.h>             /* opengl standard X11 integration          */


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






/*---(rational limits)------------------------------------------*/
#define     LEN_NAME        20     /* max naming string                       */
#define     LEN_STR        200     /* max string                              */
#define     LEN_UNIT       200     /* max unit test return string             */
#define     LEN_RECD      2000     /* max record len                          */

#define   MAXWORD      50

typedef   unsigned char    uchar;
typedef   long long        llong;


typedef     struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(overall)--------------*/
   char        version     [LEN_STR];  /* version reporting string            */
   char        progname    [LEN_STR];  /* program name                        */
   char        win_title   [LEN_STR];
   /*---(fonts)----------------*/
   char        face_bg     [LEN_STR];
   char        face_sm     [LEN_STR];
   int         txf_bg;
   int         txf_sm;
   int         size_big;
   int         size_norm;
   /*---(files)-----------------*/
   char        name_event  [LEN_STR];  /* name of event device                */
   FILE       *file_event;             /* pointer to event device             */
   /*---(flags)----------------*/
   char        rptg_events;            /* request to dump events to screen    */
   char        rptg_dots;              /* request to dump dots to screen      */
   char        rptg_recog;             /* request to dump regcognition        */
   /*---(arguments)-------------*/
   long        loop_msec;              /* wait time in milliseconds           */
   /*---(done)------------------*/
};
extern      tACCESSOR   my;

#define     RPTG_DOTS           if (my.rptg_dots    == 'y')
#define     RPTG_EVENTS         if (my.rptg_events  == 'y')
#define     RPTG_RECOG          if (my.rptg_recog   == 'y')


/*---(directory names)--------------------------*/
#define     DIR_INPUT        "/dev/input/"

/*---(file names)-------------------------------*/
#define     FILE_EVENT       "event16"


/*===[[ drawing semi-constants ]]=============================================*/
/* values are established in petal.c                                          */

extern const float  DEG2RAD;

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
   int             help;
   int             color;
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
extern      int       init_x;
extern      int       init_y;

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
   float       r_button;
};
extern    tSHAPES       shape;

extern ulong  g_focus;

uint   states[10];
uint   locks[10];



/*---(dot trace)------------------*/
struct cDOTS {
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
extern      tDOTS       dots        [MAX_DOTS];
extern      int         ndot;

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
char      stroke_letter[MAXWORD];
int       stroke_index [MAXWORD];
ulong     stroke_keysym[MAXWORD];
int       stroke_count;


/*===[[ DEBUGGING SETUP ]]====================================================*/
/* this is my latest standard format, vars, and urgents                       */
/* v3.0b : added signal handling                                (2014-feb-01) */
struct cDEBUG
{
   /*---(handle)-------------------------*/
   int         logger;                 /* log file so that we don't close it  */
   /*---(overall)------------------------*/  /* abcdefghi_kl__opq_stu__x__    */
   /* f = full urgents turns on all standard urgents                          */
   /* k = kitchen sink and turns everything, i mean everything on             */
   /* q = quiet turns all urgents off including the log itself                */
   char        tops;                   /* t) broad structure and context      */
   char        summ;                   /* s) statistics and analytical output */
   /*---(startup/shutdown)---------------*/
   char        args;                   /* a) command line args and urgents    */
   char        conf;                   /* c) configuration handling           */
   char        prog;                   /* p) program setup and teardown       */
   /*---(file processing)----------------*/
   char        inpt;                   /* i) text/data file input             */
   char        inpt_mas;               /* I) text/data file input   (mas/more)*/
   char        outp;                   /* o) text/data file output            */
   char        outp_mas;               /* O) text/data file output  (mas/more)*/
   /*---(event handling)-----------------*/
   char        loop;                   /* l) main program event loop          */
   char        loop_mas;               /* L) main program event loop (mas/more*/
   char        user;                   /* u) user input and handling          */
   char        apis;                   /* z) interprocess communication       */
   char        sign;                   /* x) os signal handling               */
   char        scrp;                   /* b) scripts and batch operations     */
   char        hist;                   /* h) history, undo, redo              */
   /*---(program)------------------------*/
   char        graf;                   /* g) grahpics, drawing, and display   */
   char        data;                   /* d) complex data structure handling  */
   char        envi;                   /* e) environment/filesystem           */
   char        envi_mas;               /* E) environment/filesystem (mas/more)*/
   /*---(specific)-----------------------*/
   char        touch;                  /*    raw touch input                  */
   char        recog;                  /*    stroke recognition               */
};
typedef     struct      cDEBUG      tDEBUG;
extern      tDEBUG      debug;

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

#define     DEBUG_TOUCH         if (debug.touch     == 'y')
#define     DEBUG_RECOG         if (debug.recog     == 'y')




extern char g_letters[40];
extern char g_upper[40];
extern char g_punct[40];
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

/*===[[ MAIN ]]===============================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        main                    (int a_argc, char *a_argv []);

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
char        PROG_testquiet          (void);
char        PROG_testloud           (void);
char        PROG_testend            (void);
/*---(done)----------------*/

char        PROG_event              (void);


char       DRAW_main         (void);
char       draw_delete       (void);
char       DRAW_back          (void);
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
/*---rc---- ---name----------- ---args----------------------------------------*/
char        SHAPE_base         (float a_ratio);
char        SHAPE_tiny         (void);
char        SHAPE_small        (void);
char        SHAPE_medium       (void);
char        SHAPE_normal       (void);
char        SHAPE_large        (void);
char        SHAPE_huge         (void);
char        SHAPE_giant        (void);

/*===[[ petal_touch.c ]]============================================================*/ 
/*---rc---- ---name----------- ---args----------------------------------------*/
char        TOUCH_open         (void);
char        TOUCH_normal       (void);
char        TOUCH_check        (void);
char        TOUCH_read         (void);
char        TOUCH_close        (void);

/*===[[ petal_stroke.c ]]===========================================================*/ 
/*---rc---- ---name----------- ---args----------------------------------------*/
char        DOT_beg            (int, int);
char        DOT_add            (int, int, char);
char        DOT_end            (int, int);


char       STROKE_begin      (int, int, int);
char       stroke_next       (int, int, int);
char       STROKE_end        (int, int, int);



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



#endif
