/*============================[[    beg-code    ]]============================*/
#include    "petal.h"


tACCESSOR   my;
tDEBUG      debug;
char        unit_answer [LEN_UNIT];



/*====================------------------------------------====================*/
/*===----                         helper functions                     ----===*/
/*====================------------------------------------====================*/
static void      o___HELPER__________________o (void) {;}

char*        /*--: return versioning information ---------[ leaf-- [ ------ ]-*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strlcpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strlcpy (t, "[cbang      ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (my.version, 100, "%s   %s : %s", t, PETAL_VER_NUM, PETAL_VER_TXT);
   return my.version;
}



/*====================------------------------------------====================*/
/*===----                        start-up functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char         /*--: wholesale urgents change --------------[ leaf   [ ------ ]-*/
PROG_urgsmass      (char a_set, char a_extra)
{
   /*---(overall)------------------------*/
   debug.tops     = a_set;
   debug.summ     = a_set;
   /*---(startup/shutdown)---------------*/
   debug.args     = a_set;
   debug.conf     = a_set;
   debug.prog     = a_set;
   /*---(file processing)----------------*/
   debug.inpt     = a_set;
   debug.inpt_mas = a_set;
   debug.outp     = a_set;
   debug.outp_mas = a_set;
   /*---(event handling)-----------------*/
   debug.loop     = a_set;
   debug.loop_mas = a_set;
   debug.user     = a_set;
   debug.apis     = a_set;
   debug.sign     = a_set;
   debug.scrp     = a_set;
   debug.hist     = a_set;
   /*---(program)------------------------*/
   debug.graf     = a_set;
   debug.data     = a_set;
   debug.envi     = a_set;
   debug.envi_mas = a_set;
   /*---(specific)-----------------------*/
   if (a_extra == 'y') {
      debug.recog    = a_set;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--: evaluate logger needs early -----------[ leaf   [ ------ ]-*/
PROG_logger        (int a_argc, char *a_argv[])
{
   /*---(locals)-------------------------*/
   int         i           = 0;             /* loop iterator -- arguments     */
   char       *a           = NULL;          /* current argument               */
   int         x_log       = '-';           /* logging flag                   */
   int         x_len       = 0;
   char        x_prog      [LEN_STR];
   /*---(default urgents)----------------*/
   debug.logger   = -1;
   PROG_urgsmass ('-', 'y');   /* turn everything off */
   /*---(save prog name)-----------------*/
   strlcpy (my.progname, a_argv [0], LEN_STR);
   strlcpy (x_prog     , a_argv [0], LEN_STR);
   x_len = strllen (x_prog, LEN_STR);
   /*---(test for debug version)---------*/
   if      (x_len > 6 && strstr (x_prog, "_debug") == NULL) {
      x_len -= 6;
      x_prog [x_len] = '\0';
   }
   /*---(test for unit testing)----------*/
   else if (x_len > 5 && strstr (x_prog, "_unit" ) == NULL) {
      ;;
   }
   /*---(test for normal version)--------*/
   else {
      return 0;
   }
   /*---(check for urgents)--------------*/
   for (i = 1; i < a_argc; ++i) {
      /*---(filter)----------------------*/
      a = a_argv[i];
      if (a[0] != '@')  continue;
      /*---(turn on debugging)-----------*/
      x_log          = 'y';
      debug.tops     = 'y';
      /*---(test for args)---------------*/
      if      (strncmp(a, "@a"           ,10) == 0)  debug.args  = 'y';
      else if (strncmp(a, "@@args"       ,10) == 0)  debug.args  = 'y';
      else if (strncmp(a, "@f"           ,10) == 0)  debug.args  = 'y';
      else if (strncmp(a, "@@full"       ,10) == 0)  debug.args  = 'y';
      else if (strncmp(a, "@k"           ,10) == 0)  debug.args  = 'y';
      else if (strncmp(a, "@@kitchen"    ,10) == 0)  debug.args  = 'y';
      /*---(next)------------------------*/
   }
   /*---(startup logging)----------------*/
   if (x_log == 'y')  debug.logger = yLOG_begin (x_prog, yLOG_SYSTEM, yLOG_NOISE);
   else               debug.logger = yLOG_begin (x_prog, yLOG_SYSTEM, yLOG_QUIET);
   /*---(log header)------------------*/
   DEBUG_TOPS   yLOG_info     ("petal"   , PROG_version   ());
   DEBUG_TOPS   yLOG_info     ("purpose" , "wicked cool pen based text input");
   DEBUG_TOPS   yLOG_info     ("ySTR"    , ySTR_version   ());
   DEBUG_TOPS   yLOG_info     ("yLOG"    , yLOG_version   ());
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: initialize variables --------------------------------------*/
PROG_init          (void)
{
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   stroke.max      = -1;
   stroke.zth      = -1;
   stroke.fst      = -1;
   stroke.snd      = -1;
   stroke.trd      = -1;
   stroke.fth      = -1;
   ndots        =   0;
   stroke.small     = NOR;
   strlcpy (my.win_title, "petal_writing", LEN_STR);
   strlcpy (my.face_bg  , "coolvetica"   , LEN_STR);
   strlcpy (my.face_sm  , "courier"      , LEN_STR);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--: evaluate command line urgents ---------[ leaf   [ ------ ]-*/
PROG_urgs          (int a_argc, char *a_argv[])
{
   /*---(locals)-------------------------*/
   int         rc          = 0;             /* generic return code            */
   int         i           = 0;             /* loop iterator -- arguments     */
   char       *a           = NULL;          /* current argument               */
   int         x_len       = 0;             /* argument length                */
   int         x_total     = 0;             /* total argument count           */
   int         x_urgs      = 0;             /* urgent count                   */
   /*---(default urgents)----------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(check for normal version)-------*/
   if (strcmp (a_argv[0], "themis"       ) == 0)  return 0;
   /*---(walk through urgents)-----------*/
   for (i = 1; i < a_argc; ++i) {
      /*---(prepare)---------------------*/
      a        = a_argv [i];
      x_len    = strllen (a, LEN_RECD);
      ++x_total;
      /*---(filter)----------------------*/
      if (a[0] != '@')  continue;
      ++x_urgs;
      DEBUG_ARGS  yLOG_info  ("urgent"    , a);
      /*---(overall)---------------------*/
      if      (strncmp(a, "@t"           ,10) == 0)  debug.tops = 'y';
      else if (strncmp(a, "@@tops"       ,10) == 0)  debug.tops = 'y';
      else if (strncmp(a, "@s"           ,10) == 0)  debug.tops = debug.summ  = 'y';
      else if (strncmp(a, "@@summ"       ,10) == 0)  debug.tops = debug.summ  = 'y';
      /*---(startup/shutdown)------------*/
      else if (strncmp(a, "@a"           ,10) == 0)  debug.tops = debug.args  = 'y';
      else if (strncmp(a, "@@args"       ,10) == 0)  debug.tops = debug.args  = 'y';
      else if (strncmp(a, "@c"           ,10) == 0)  debug.tops = debug.conf  = 'y';
      else if (strncmp(a, "@@conf"       ,10) == 0)  debug.tops = debug.conf  = 'y';
      else if (strncmp(a, "@p"           ,10) == 0)  debug.tops = debug.prog  = 'y';
      else if (strncmp(a, "@@prog"       ,10) == 0)  debug.tops = debug.prog  = 'y';
      /*---(file processing)-------------*/
      else if (strncmp(a, "@i"           ,10) == 0)  debug.tops = debug.inpt  = 'y';
      else if (strncmp(a, "@@inpt"       ,10) == 0)  debug.tops = debug.inpt  = 'y';
      else if (strncmp(a, "@I"           ,10) == 0)  debug.tops = debug.inpt  = debug.inpt_mas = 'y';
      else if (strncmp(a, "@@INPT"       ,10) == 0)  debug.tops = debug.inpt  = debug.inpt_mas = 'y';
      else if (strncmp(a, "@o"           ,10) == 0)  debug.tops = debug.outp  = 'y';
      else if (strncmp(a, "@@outp"       ,10) == 0)  debug.tops = debug.outp  = 'y';
      else if (strncmp(a, "@O"           ,10) == 0)  debug.tops = debug.outp  = debug.outp_mas = 'y';
      else if (strncmp(a, "@@OUTP"       ,10) == 0)  debug.tops = debug.outp  = debug.outp_mas = 'y';
      /*---(processing)------------------*/
      else if (strncmp(a, "@l"           ,10) == 0)  debug.tops = debug.loop  = 'y';
      else if (strncmp(a, "@@loop"       ,10) == 0)  debug.tops = debug.loop  = 'y';
      else if (strncmp(a, "@L"           ,10) == 0)  debug.tops = debug.loop  = debug.loop_mas =  'y';
      else if (strncmp(a, "@@LOOP"       ,10) == 0)  debug.tops = debug.loop  = debug.loop_mas =  'y';
      else if (strncmp(a, "@u"           ,10) == 0)  debug.tops = debug.user  = 'y';
      else if (strncmp(a, "@@user"       ,10) == 0)  debug.tops = debug.user  = 'y';
      else if (strncmp(a, "@z"           ,10) == 0)  debug.tops = debug.apis  = 'y';
      else if (strncmp(a, "@@apis"       ,10) == 0)  debug.tops = debug.apis  = 'y';
      else if (strncmp(a, "@x"           ,10) == 0)  debug.tops = debug.sign  = 'y';
      else if (strncmp(a, "@@sign"       ,10) == 0)  debug.tops = debug.sign  = 'y';
      else if (strncmp(a, "@b"           ,10) == 0)  debug.tops = debug.scrp  = 'y';
      else if (strncmp(a, "@@scrp"       ,10) == 0)  debug.tops = debug.scrp  = 'y';
      else if (strncmp(a, "@h"           ,10) == 0)  debug.tops = debug.hist  = 'y';
      else if (strncmp(a, "@@hist"       ,10) == 0)  debug.tops = debug.hist  = 'y';
      /*---(program)---------------------*/
      else if (strncmp(a, "@g"           ,10) == 0)  debug.tops = debug.graf  = 'y';
      else if (strncmp(a, "@@graf"       ,10) == 0)  debug.tops = debug.graf  = 'y';
      else if (strncmp(a, "@d"           ,10) == 0)  debug.tops = debug.data  = 'y';
      else if (strncmp(a, "@@data"       ,10) == 0)  debug.tops = debug.data  = 'y';
      else if (strncmp(a, "@e"           ,10) == 0)  debug.tops = debug.envi  = 'y';
      else if (strncmp(a, "@@envi"       ,10) == 0)  debug.tops = debug.envi  = 'y';
      else if (strncmp(a, "@E"           ,10) == 0)  debug.tops = debug.envi  = debug.envi_mas = 'y';
      else if (strncmp(a, "@@ENVI"       ,10) == 0)  debug.tops = debug.envi  = debug.envi_mas = 'y';
      /*---(complex)---------------------*/
      else if (strncmp(a, "@q"           ,10) == 0)  PROG_urgsmass ('n', 'n');
      else if (strncmp(a, "@@quiet"      ,10) == 0)  PROG_urgsmass ('n', 'n');
      else if (strncmp(a, "@f"           ,10) == 0)  PROG_urgsmass ('y', '-');
      else if (strncmp(a, "@@full"       ,10) == 0)  PROG_urgsmass ('y', '-');
      else if (strncmp(a, "@k"           ,10) == 0)  PROG_urgsmass ('y', 'y');
      else if (strncmp(a, "@@kitchen"    ,10) == 0)  PROG_urgsmass ('y', 'y');
      /*---(specific)--------------------*/
      else if (strncmp(a, "@@recog"      ,10) == 0)  debug.tops = debug.recog = 'y';
      /*---(unknown)--------------------*/
      else {
         DEBUG_ARGS  yLOG_note    ("urgent not understood");
      }
      /*---(done)-----------------------*/
   }
   /*---(display urgents)----------------*/
   DEBUG_ARGS   yLOG_note    ("summarization of urgent processing");
   DEBUG_ARGS   yLOG_value   ("entries"   , x_total);
   DEBUG_ARGS   yLOG_value   ("urgents"   , x_urgs);
   DEBUG_ARGS   yLOG_note    ("standard urgents");
   DEBUG_ARGS   yLOG_char    ("tops"      , debug.tops);
   DEBUG_ARGS   yLOG_char    ("summ"      , debug.summ);
   DEBUG_ARGS   yLOG_char    ("args"      , debug.args);
   DEBUG_ARGS   yLOG_char    ("conf"      , debug.conf);
   DEBUG_ARGS   yLOG_char    ("prog"      , debug.prog);
   DEBUG_ARGS   yLOG_char    ("inpt"      , debug.inpt);
   DEBUG_ARGS   yLOG_char    ("INPT"      , debug.inpt_mas);
   DEBUG_ARGS   yLOG_char    ("outp"      , debug.outp);
   DEBUG_ARGS   yLOG_char    ("OUTP"      , debug.outp_mas);
   DEBUG_ARGS   yLOG_char    ("loop"      , debug.loop);
   DEBUG_ARGS   yLOG_char    ("LOOP"      , debug.loop_mas);
   DEBUG_ARGS   yLOG_char    ("user"      , debug.user);
   DEBUG_ARGS   yLOG_char    ("apis"      , debug.apis);
   DEBUG_ARGS   yLOG_char    ("sign"      , debug.sign);
   DEBUG_ARGS   yLOG_char    ("scrp"      , debug.scrp);
   DEBUG_ARGS   yLOG_char    ("hist"      , debug.hist);
   DEBUG_ARGS   yLOG_char    ("graf"      , debug.graf);
   DEBUG_ARGS   yLOG_char    ("data"      , debug.data);
   DEBUG_ARGS   yLOG_char    ("envi"      , debug.envi);
   DEBUG_ARGS   yLOG_char    ("ENVI"      , debug.envi_mas);
   DEBUG_ARGS   yLOG_note    ("specialty urgents");
   DEBUG_ARGS   yLOG_char    ("recog"     , debug.recog);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}


/* PURPOSE : process the command line arguments                               */
char
PROG_args          (int argc, char *argv[])
{
   stroke.owner       =   'c';       /* start in Cheryl mode for hublin custom   */
   int    i       = 0;
   char *a = NULL;
   for (i= 1; i < argc; ++i) {
      a = argv[i];
      if      (strncmp(a, "-h"        ,  5) == 0)  stroke.help    = 1;
      else if (strncmp(a, "--letters" , 20) == 0) stroke.help     = 1;
      else if (strncmp(a, "--rob"     , 20) == 0) stroke.owner   = 'r';
      else if (strncmp(a, "--cheryl"  , 20) == 0) stroke.owner   = 'c';
      else if (strncmp(a, "--tiny"    , 20) == 0) stroke.small    = TNY;
      else if (strncmp(a, "--small"   , 20) == 0) stroke.small    = SML;
      else if (strncmp(a, "--med"     , 20) == 0) stroke.small    = MED;
      else if (strncmp(a, "--normal"  , 20) == 0) stroke.small    = NOR;
      else if (strncmp(a, "--large"   , 20) == 0) stroke.small    = LRG;
      else if (strncmp(a, "--huge"    , 20) == 0) stroke.small    = HUG;
      else if (strncmp(a, "--giant"   , 20) == 0) stroke.small    = GIA;
   }
   return 0;
}

/* PURPOSE : drive the program startup activities                             */
char
PROG_begin(void)
{
   DEBUG_TOPS   printf("\npetal writing v03 --------------------------------begin---\n\n");
   strcpy(stroke.text, " ");
   if      (stroke.small == TNY) SHAPE_tiny   ();
   else if (stroke.small == SML) SHAPE_small  ();
   else if (stroke.small == MED) SHAPE_medium ();
   else if (stroke.small == NOR) SHAPE_normal ();
   else if (stroke.small == LRG) SHAPE_large  ();
   else if (stroke.small == HUG) SHAPE_huge   ();
   else                          SHAPE_giant  ();
   yXINIT_start (my.win_title, shape.sz_width, shape.sz_height, 'n', debug.prog, 'n');
   touch_open    ();
   DRAW_init     ();
   displist_init ();
   font_load     ();
   DRAW_init     ();
   mouse_init    ();
   DEBUG_PROG   printf("PREP       :: end ---------------\n\n");
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        shutdown functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

/* PURPOSE : drive the program closure activities                             */
char
PROG_end(void)
{
   touch_close   ();
   displist_free ();
   yXINIT_end    ();
   DEBUG_TOPS   printf("\npetal writing v03 ----------------------------------end---\n\n");
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   helpers for unit testing                   ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char       /*----: set up program test file locations ------------------------*/
PROG_testfiles     (void)
{
   /*> snprintf (my.name_root   , LEN_STR, "%s"    , DIR_TEST);                           <* 
    *> snprintf (my.name_conf   , LEN_STR, "%s%s%s", DIR_TEST , DIR_ETC  , FILE_CONF );   <* 
    *> snprintf (my.name_full   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_FULL );   <* 
    *> snprintf (my.name_summ   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_SUMM );   <* 
    *> snprintf (my.name_warn   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_WARN );   <*/
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_testquiet     (void)
{
   char       *x_args [1]  = { "petal" };
   PROG_logger    (1, x_args);
   PROG_init      ();
   PROG_urgs      (1, x_args);
   PROG_args      (1, x_args);
   PROG_begin     ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_testloud      (void)
{
   char       *x_args [2]  = { "petal_unit", "@@kitchen"    };
   PROG_logger    (1, x_args);
   PROG_init      ();
   PROG_urgs      (2, x_args);
   PROG_args      (2, x_args);
   PROG_begin     ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_testend       (void)
{
   PROG_end       ();
   return 0;
}




/*============================[[ end-of-code ]]===============================*/
