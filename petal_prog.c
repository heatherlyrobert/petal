/*============================[[    beg-code    ]]============================*/
#include    "petal.h"


tACCESSOR   my;
char          unit_answer [LEN_RECD];



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
   snprintf (my.version, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return my.version;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__header            (void)
{
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter (__FUNCTION__);
   /*---(versioning)------------------*/
   DEBUG_PROG   yLOG_info     ("arachne" , PROG_version      ());
   DEBUG_PROG   yLOG_info     ("purpose" , P_PURPOSE);
   DEBUG_PROG   yLOG_info     ("namesake", P_NAMESAKE);
   DEBUG_PROG   yLOG_info     ("heritage", P_HERITAGE);
   DEBUG_PROG   yLOG_info     ("imagery" , P_IMAGERY);
   DEBUG_PROG   yLOG_note     ("custom core");
   DEBUG_PROG   yLOG_info     ("yURG"    , yURG_version      ());
   DEBUG_PROG   yLOG_info     ("yLOG"    , yLOGS_version     ());
   DEBUG_PROG   yLOG_info     ("ySTR"    , ySTR_version      ());
   DEBUG_PROG   yLOG_note     ("yvikeys foundation");
   DEBUG_PROG   yLOG_info     ("yMODE"   , yMODE_version     ());
   DEBUG_PROG   yLOG_info     ("yKEYS"   , yKEYS_version     ());
   /*> DEBUG_PROG   yLOG_info     ("yFILE"   , yFILE_version     ());                 <*/
   DEBUG_PROG   yLOG_info     ("yVIEW"   , yVIEW_version     ());
   DEBUG_PROG   yLOG_note     ("yvikeys major");
   DEBUG_PROG   yLOG_info     ("yMAP"    , yMAP_version      ());
   DEBUG_PROG   yLOG_info     ("yCMD"    , yCMD_version      ());
   DEBUG_PROG   yLOG_info     ("yMACRO"  , yMACRO_version    ());
   /*> DEBUG_PROG   yLOG_info     ("ySRC"    , ySRC_version      ());                 <*/
   /*> DEBUG_PROG   yLOG_info     ("yMARK"   , yMARK_version     ());                 <*/
   /*> DEBUG_PROG   yLOG_info     ("yGOD"    , yGOD_version      ());                 <*/
   DEBUG_PROG   yLOG_note     ("custom opengl");
   DEBUG_PROG   yLOG_info     ("yVIOP"   , yVIOPENGL_version ());
   DEBUG_PROG   yLOG_info     ("yX11"    , yX11_version      ());
   DEBUG_PROG   yLOG_info     ("yFONT"   , yFONT_version     ());
   DEBUG_PROG   yLOG_info     ("yGLTEX"  , yGLTEX_version    ());
   /*> DEBUG_PROG   yLOG_note     ("custom other");                                   <*/
   /*> DEBUG_PROG   yLOG_info     ("yVAR"    , yVAR_version      ());                 <*/
   /*> DEBUG_PROG   yLOG_info     ("yPARSE"  , yPARSE_version    ());                 <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = PROG__header ();
   DEBUG_PROG   yLOG_value    ("header"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return rc;
}






/*====================------------------------------------====================*/
/*===----                        start-up functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__init              (int argc, char *argv[])
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   TOUCH_init  ();
   PETAL_init  ();
   CONF_purge  ();
   my.boom           = '-';
   my.save_png       = '-';
   my.mask           = '-';
   my.audit          = '-';
   my.show_pguide    = '-';
   my.show_ribbon    = '-';
   my.show_pball     = '-';
   DRAW_help  ("-");
   /*> DRAW_color ("all");                                                            <*/
   stroke.max        = -1;
   stroke.zth        = -1;
   stroke.fst        = -1;
   stroke.snd        = -1;
   stroke.trd        = -1;
   stroke.fth        = -1;
   g_ndot            =   0;
   stroke.small      = NOR;
   strlcpy (my.win_title, "petal_writing", LEN_FULL);
   strlcpy (my.face_bg  , "coolvetica"   , LEN_FULL);
   /*> strlcpy (my.face_sm  , "courier"      , LEN_FULL);                              <*/
   strlcpy (my.face_sm  , "shrike"       , LEN_FULL);
   /*---(flags)--------------------------*/
   my.rptg_events    = '-';
   my.ev_major       = 0xee;
   my.ev_minor       = 0xee;
   my.rptg_dots      = '-';
   my.rptg_recog     = '-';
   my.loop_msec      =   1;
   strlcpy (shape.r_eng , "", LEN_RECD);
   strlcpy (shape.r_seq , "", LEN_RECD);
   shape.r_len       =   0;
   shape.r_pos       =   0;
   strlcpy (shape.r_done, "", LEN_RECD);
   shape.r_done_show = 'y';
   shape.r_mode      = '-';
   shape.r_letter    = '\0';
   shape.r_loc       = -1;
   shape.r_exec      =  0;
   shape.r_state     = -1;
   shape.r_debug     = '-';
   shape.r_prog      = 0.0;
   DRAW_speed ("-");
   /*---(file names)---------------------*/
   DEBUG_PROG   yLOG_note    ("file names");
   snprintf (my.n_event  , LEN_FULL, "%s%s", DIR_INPUT, FILE_EVENT );
   my.file_event     = NULL;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/* PURPOSE : process the command line arguments                               */
char
PROG__args              (int argc, char *argv[])
{
   stroke.owner       =   'c';       /* start in Cheryl mode for hublin custom   */
   int    i       = 0;
   char *a = NULL;
   for (i= 1; i < argc; ++i) {
      a = argv[i];
      if      (strncmp(a, "--letters" , 20) == 0)  DRAW_help ("all");
      else if (strncmp(a, "--NN"      , 20) == 0)  DRAW_help ("NN");
      else if (strncmp(a, "--NE"      , 20) == 0)  DRAW_help ("NE");
      else if (strncmp(a, "--EE"      , 20) == 0)  DRAW_help ("EE");
      else if (strncmp(a, "--SE"      , 20) == 0)  DRAW_help ("SE");
      else if (strncmp(a, "--SS"      , 20) == 0)  DRAW_help ("SS");
      else if (strncmp(a, "--SW"      , 20) == 0)  DRAW_help ("SW");
      else if (strncmp(a, "--WW"      , 20) == 0)  DRAW_help ("WW");
      else if (strncmp(a, "--NW"      , 20) == 0)  DRAW_help ("NW");
      else if (strncmp(a, "--inner"   , 20) == 0)  DRAW_help ("inner");
      else if (strncmp(a, "--outer"   , 20) == 0)  DRAW_help ("outer");
      else if (strncmp(a, "--edge"    , 20) == 0)  DRAW_help ("edge");
      else if (strncmp(a, "--mode"    , 20) == 0)  DRAW_help ("mode");
      else if (strncmp(a, "--two"     , 20) == 0)  DRAW_help ("two");
      else if (strncmp(a, "--tiny"    , 20) == 0)  stroke.small    = TNY;
      else if (strncmp(a, "--small"   , 20) == 0)  stroke.small    = SML;
      else if (strncmp(a, "--med"     , 20) == 0)  stroke.small    = MED;
      else if (strncmp(a, "--normal"  , 20) == 0)  stroke.small    = NOR;
      else if (strncmp(a, "--large"   , 20) == 0)  stroke.small    = LRG;
      else if (strncmp(a, "--huge"    , 20) == 0)  stroke.small    = HUG;
      else if (strncmp(a, "--giant"   , 20) == 0)  stroke.small    = GIA;
      else if (strncmp(a, "--events"  , 20) == 0)  my.rptg_events  = 'y';
      else if (strncmp(a, "--dots"    , 20) == 0)  my.rptg_dots    = 'y';
      else if (strncmp(a, "--recog"   , 20) == 0)  my.rptg_recog   = 'y';
      else if (strncmp(a, "--evall"   , 20) == 0)  { my.ev_major = 0xff; my.ev_minor = 0xff  ; }
      else if (strncmp(a, "--evx"     , 20) == 0)  { my.ev_major = 0x03; my.ev_minor = 0x00  ; }
      else if (strncmp(a, "--evy"     , 20) == 0)  { my.ev_major = 0x03; my.ev_minor = 0x01  ; }
      else if (strncmp(a, "--evhard"  , 20) == 0)  { my.ev_major = 0x03; my.ev_minor = 0x18  ; }
      else if (strncmp(a, "--evxtilt" , 20) == 0)  { my.ev_major = 0x03; my.ev_minor = 0x1a  ; }
      else if (strncmp(a, "--evytilt" , 20) == 0)  { my.ev_major = 0x03; my.ev_minor = 0x1b  ; }
      else if (strncmp(a, "--evhover" , 20) == 0)  { my.ev_major = 0x01; my.ev_minor = 0x0140; }
      else if (strncmp(a, "--evtouch" , 20) == 0)  { my.ev_major = 0x01; my.ev_minor = 0x014a; }
      else if (strncmp(a, "--evbutton", 20) == 0)  { my.ev_major = 0x04; my.ev_minor = 0xff  ; }
      else if (strncmp(a, "--pball"   , 20) == 0)  my.show_pball   = 'y';
      else if (strncmp(a, "--nopball" , 20) == 0)  my.show_pball   = '-';
      else if (strncmp(a, "--pngonly" , 20) == 0)  my.save_png     = 'y';
      else if (strncmp(a, "--pngalso" , 20) == 0)  my.save_png     = '+';
      else if (strncmp(a, "--mask"    , 20) == 0)  my.mask         = 'y';
      else if (strncmp(a, "--nomask"  , 20) == 0)  my.mask         = '-';
      else if (strncmp(a, "--pguide"  , 20) == 0)  my.show_pguide  = 'y';
      else if (strncmp(a, "--nopguide", 20) == 0)  my.show_pguide  = '-';
      else if (strncmp(a, "--ribbon"  , 20) == 0)  my.show_ribbon  = 'y';
      else if (strncmp(a, "--noribbon", 20) == 0)  my.show_ribbon  = '-';
      else if (strcmp (a, "--vcheck"      ) == 0)  my.audit        = 'y';
   }
   return 0;
}

/* PURPOSE : drive the program startup activities                             */
char
PROG__begin             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   strcpy (stroke.text, " ");
   /*---(set size)-----------------------*/
   if      (stroke.small == TNY) SHAPE_tiny   ();
   else if (stroke.small == SML) SHAPE_small  ();
   else if (stroke.small == MED) SHAPE_medium ();
   else if (stroke.small == NOR) SHAPE_normal ();
   else if (stroke.small == LRG) SHAPE_large  ();
   else if (stroke.small == HUG) SHAPE_huge   ();
   else                          SHAPE_giant  ();
   /*> yX11_start (my.win_title, my.w_wide, my.w_tall, 'n', debug.prog, 'n');   <*/
   if (my.audit == 'y') {
      yURG_msg_live ();
      yURG_err_live ();
   }
   /*---(initialize)---------------------*/
   TOUCH__open (my.n_event, 'r', &(my.f_event));
   mouse_init    ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program execution                     ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTION_______________o (void) {;}

char
PROG_dawn          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(yvicurses config)---------------*/
   DEBUG_PROG   yLOG_complex ("size"      , "%4dw %4dt", my.w_wide, my.w_tall);
   rc = yVIOPENGL_init   (P_NAMESAKE, P_VERNUM, MODE_MAP, my.w_wide, my.w_tall);
   DEBUG_PROG   yLOG_value    ("yVIOPENGL" , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   rc = yMAP_config       (YMAP_OFFICE, api_ymap_locator, api_ymap_addressor, api_ymap_sizer, api_ymap_entry, api_ymap_placer, api_ymap_done);
   DEBUG_PROG   yLOG_value    ("yMAP"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   rc = yVIEW_full     (YVIEW_MAIN , YVIEW_FLAT , YVIEW_MIDCEN, 1.0, 0, DRAW_main);
   DEBUG_PROG   yLOG_value    ("yVIEW"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   rc = yVIEW_full     (YVIEW_RIBBON, YVIEW_FLAT , YVIEW_TOPLEF, 1.0, 0, DRAW_ribbon);
   DEBUG_PROG   yLOG_value    ("yVIEW"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   rc = yVIEW_defsize  (YVIEW_RIBBON, 80, 0);
   yCMD_direct (":layout min");
   /*> yCMD_direct (":command show");                                                 <*/
   /*> yCMD_direct (":keys show");                                                    <*/
   if (my.show_ribbon == 'y')  yCMD_direct (":ribbon show");
   yCMD_direct (":float 5");
   yCMD_direct (":menus 1");
   yCMD_direct (":title    disable");
   yCMD_direct (":version  disable");
   yCMD_direct (":universe disable");
   yCMD_direct (":formula  disable");
   yCMD_direct (":nav      disable");
   yCMD_direct (":alt      disable");
   yCMD_direct (":progress disable");
   yCMD_direct (":command  disable");
   yCMD_direct (":keys     disable");
   yCMD_direct (":status   disable");
   yCMD_direct (":modes    disable");
   yCMD_direct (":history  disable");
   /*---(dawn)---------------------------*/
   rc = yVIOPENGL_dawn ();
   DEBUG_PROG   yLOG_value    ("dawn"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   displist_init ();
   font_load     ();
   /*---(commands)-----------------------*/
   rc = yCMD_add (YVIHUB_M_CONFIG, "label"       , ""    , "s"    , DRAW_help            , "configure the help labels"                                   );
   DEBUG_PROG   yLOG_value   ("label"     , rc);
   /*> rc = yCMD_add (YVIHUB_M_CONFIG, "pad"         , ""    , "s"    , DRAW_color           , "configure the help colors"                                   );   <*/
   /*> DEBUG_PROG   yLOG_value   ("pad"       , rc);                                  <*/
   rc = yCMD_add (YVIHUB_M_CONFIG, "speed"       , ""    , "s"    , DRAW_speed           , "configure the help colors"                                   );
   DEBUG_PROG   yLOG_value   ("speed"     , rc);
   rc = yCMD_add (YVIHUB_M_CONFIG, "seq"         , ""    , "cs"   , DRAW_seq             , "configure the help colors"                                   );
   DEBUG_PROG   yLOG_value   ("seq"       , rc);
   rc = yCMD_add (YVIHUB_M_CONFIG, "size"        , ""    , "s"    , SHAPE_size           , "configure the help colors"                                   );
   DEBUG_PROG   yLOG_value   ("size"      , rc);
   /*> rc = yCMD_add (YVIHUB_M_CONFIG, "done"        , ""    , "s"    , DRAW_done_show       , "configure showing completed text"                            );   <*/
   /*> DEBUG_PROG   yLOG_value   ("done"      , rc);                                  <*/
   rc = yCMD_add (YVIHUB_M_CONFIG, "press"       , ""    , "s"    , DRAW_press           , "configure showing completed text"                            );
   DEBUG_PROG   yLOG_value   ("press"     , rc);
   /*> rc = yCMD_add (YVIHUB_M_CONFIG, "debug"       , ""    , "s"    , DRAW_debug_set       , "configure showing completed text"                            );   <*/
   /*> DEBUG_PROG   yLOG_value   ("debug"     , rc);                                  <*/
   rc = yCMD_add (YVIHUB_M_CONFIG, "pguide"      , ""    , "s"    , SHAPE_pguide         , "configure petal guide rings"                                 );
   DEBUG_PROG   yLOG_value   ("pguide"    , rc);
   rc = yCMD_add (YVIHUB_M_CONFIG, "pball"       , ""    , "s"    , SHAPE_pball          , "configure petal balls"                                       );
   DEBUG_PROG   yLOG_value   ("pball"     , rc);
   rc = yCMD_add (YVIHUB_M_CONFIG, "pletter"     , ""    , "s"    , SHAPE_pletter        , "configure petal letters"                                     );
   DEBUG_PROG   yLOG_value   ("pletter"   , rc);
   /*---(yPARSE)-------------------------*/
   CONF_init   ();
   rc = CONF_pull (FILE_CONF);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_dusk          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(dusk)---------------------------*/
   rc = yVIOPENGL_dusk ();
   DEBUG_PROG   yLOG_value    ("dawn"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   displist_free ();
   yVIOPENGL_wrap ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char       /*----: drive the program closure activities ----------------------*/
PROG__end               (void)
{
   /*---(shutdown)--------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   TOUCH__close   (&(my.f_event));
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] drive the program closure activities ------------*/
PROG_shutdown           (void)
{
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_END);
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   PROG__end ();
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   helpers for unit testing                   ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char       /*----: set up program test file locations ------------------------*/
PROG_testfiles     (void)
{
   /*> snprintf (my.name_root   , LEN_FULL, "%s"    , DIR_TEST);                           <* 
    *> snprintf (my.name_conf   , LEN_FULL, "%s%s%s", DIR_TEST , DIR_ETC  , FILE_CONF );   <* 
    *> snprintf (my.name_full   , LEN_FULL, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_FULL );   <* 
    *> snprintf (my.name_summ   , LEN_FULL, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_SUMM );   <* 
    *> snprintf (my.name_warn   , LEN_FULL, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_WARN );   <*/
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_unit_quiet    (void)
{
   char        x_carg      = 1;
   char       *x_args [1]  = { "petal" };
   PROG_urgents   (x_carg, x_args);
   PROG_startup   (x_carg, x_args);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_unit_loud     (void)
{
   char        x_carg      = 3;
   char       *x_args [3]  = { "petal_unit", "@@kitchen"   , "@@touch"    };
   PROG_urgents   (x_carg, x_args);
   PROG_startup   (x_carg, x_args);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_unit_end      (void)
{
   PROG_shutdown ();
   return 0;
}




/*============================[[ end-of-code ]]===============================*/
