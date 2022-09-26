/*============================[[    beg-code    ]]============================*/
#include    "petal.h"


tACCESSOR   my;
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
   snprintf (my.version, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return my.version;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT_________________o (void) {;}

/*> char         /+--: wholesale urgents change --------------[ leaf   [ ------ ]-+/   <* 
 *> PROG_urgsmass      (char a_set, char a_extra)                                      <* 
 *> {                                                                                  <* 
 *>    /+---(overall)------------------------+/                                        <* 
 *>    debug.tops     = a_set;                                                         <* 
 *>    debug.summ     = a_set;                                                         <* 
 *>    /+---(startup/shutdown)---------------+/                                        <* 
 *>    debug.args     = a_set;                                                         <* 
 *>    debug.conf     = a_set;                                                         <* 
 *>    debug.prog     = a_set;                                                         <* 
 *>    /+---(file processing)----------------+/                                        <* 
 *>    debug.inpt     = a_set;                                                         <* 
 *>    debug.inpt_mas = a_set;                                                         <* 
 *>    debug.outp     = a_set;                                                         <* 
 *>    debug.outp_mas = a_set;                                                         <* 
 *>    /+---(event handling)-----------------+/                                        <* 
 *>    debug.loop     = a_set;                                                         <* 
 *>    debug.loop_mas = a_set;                                                         <* 
 *>    debug.user     = a_set;                                                         <* 
 *>    debug.apis     = a_set;                                                         <* 
 *>    debug.sign     = a_set;                                                         <* 
 *>    debug.scrp     = a_set;                                                         <* 
 *>    debug.hist     = a_set;                                                         <* 
 *>    /+---(program)------------------------+/                                        <* 
 *>    debug.graf     = a_set;                                                         <* 
 *>    debug.data     = a_set;                                                         <* 
 *>    debug.envi     = a_set;                                                         <* 
 *>    debug.envi_mas = a_set;                                                         <* 
 *>    /+---(specific)-----------------------+/                                        <* 
 *>    if (a_extra == 'y') {                                                           <* 
 *>       debug.recog    = a_set;                                                      <* 
 *>       debug.touch    = a_set;                                                      <* 
 *>    }                                                                               <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char         /+--: evaluate logger needs early -----------[ leaf   [ ------ ]-+/   <* 
 *> PROG_logger        (int a_argc, char *a_argv[])                                    <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-------------------------+/                                        <* 
 *>    int         i           = 0;             /+ loop iterator -- arguments     +/   <* 
 *>    char       *a           = NULL;          /+ current argument               +/   <* 
 *>    int         x_log       = '-';           /+ logging flag                   +/   <* 
 *>    int         x_len       = 0;                                                    <* 
 *>    char        x_prog      [LEN_STR];                                              <* 
 *>    /+---(default urgents)----------------+/                                        <* 
 *>    debug.logger   = -1;                                                            <* 
 *>    PROG_urgsmass ('-', 'y');   /+ turn everything off +/                           <* 
 *>    /+---(save prog name)-----------------+/                                        <* 
 *>    strlcpy (my.progname, a_argv [0], LEN_STR);                                     <* 
 *>    strlcpy (x_prog     , a_argv [0], LEN_STR);                                     <* 
 *>    x_len = strllen (x_prog, LEN_STR);                                              <* 
 *>    /+---(test for debug version)---------+/                                        <* 
 *>    if      (x_len > 6 && strstr (x_prog, "_debug") == NULL) {                      <* 
 *>       x_len -= 6;                                                                  <* 
 *>       x_prog [x_len] = '\0';                                                       <* 
 *>    }                                                                               <* 
 *>    /+---(test for unit testing)----------+/                                        <* 
 *>    else if (x_len > 5 && strstr (x_prog, "_unit" ) == NULL) {                      <* 
 *>       ;;                                                                           <* 
 *>    }                                                                               <* 
 *>    /+---(test for normal version)--------+/                                        <* 
 *>    else {                                                                          <* 
 *>       return 0;                                                                    <* 
 *>    }                                                                               <* 
 *>    /+---(check for urgents)--------------+/                                        <* 
 *>    for (i = 1; i < a_argc; ++i) {                                                  <* 
 *>       /+---(filter)----------------------+/                                        <* 
 *>       a = a_argv[i];                                                               <* 
 *>       if (a[0] != '@')  continue;                                                  <* 
 *>       /+---(turn on debugging)-----------+/                                        <* 
 *>       x_log          = 'y';                                                        <* 
 *>       debug.tops     = 'y';                                                        <* 
 *>       /+---(test for args)---------------+/                                        <* 
 *>       if      (strncmp(a, "@a"           ,10) == 0)  debug.args  = 'y';            <* 
 *>       else if (strncmp(a, "@@args"       ,10) == 0)  debug.args  = 'y';            <* 
 *>       else if (strncmp(a, "@f"           ,10) == 0)  debug.args  = 'y';            <* 
 *>       else if (strncmp(a, "@@full"       ,10) == 0)  debug.args  = 'y';            <* 
 *>       else if (strncmp(a, "@k"           ,10) == 0)  debug.args  = 'y';            <* 
 *>       else if (strncmp(a, "@@kitchen"    ,10) == 0)  debug.args  = 'y';            <* 
 *>       /+---(next)------------------------+/                                        <* 
 *>    }                                                                               <* 
 *>    /+---(startup logging)----------------+/                                        <* 
 *>    if (x_log == 'y')  debug.logger = yLOGS_begin (x_prog, YLOG_SYS, YLOG_NOISE);   <* 
 *>    else               debug.logger = yLOGS_begin (x_prog, YLOG_SYS, YLOG_QUIET);   <* 
 *>    /+---(log header)------------------+/                                           <* 
 *>    DEBUG_TOPS   yLOG_info     ("petal"   , PROG_version   ());                     <* 
 *>    DEBUG_TOPS   yLOG_info     ("purpose" , "wicked cool pen based text input");    <* 
 *>    DEBUG_TOPS   yLOG_info     ("ySTR"    , ySTR_version   ());                     <* 
 *>    DEBUG_TOPS   yLOG_info     ("yLOG"    , yLOGS_version  ());                     <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char         /+--: evaluate command line urgents ---------[ leaf   [ ------ ]-+/                         <* 
 *> PROG_urgs          (int a_argc, char *a_argv[])                                                          <* 
 *> {                                                                                                        <* 
 *>    /+---(locals)-------------------------+/                                                              <* 
 *>    int         rc          = 0;             /+ generic return code            +/                         <* 
 *>    int         i           = 0;             /+ loop iterator -- arguments     +/                         <* 
 *>    char       *a           = NULL;          /+ current argument               +/                         <* 
 *>    int         x_len       = 0;             /+ argument length                +/                         <* 
 *>    int         x_total     = 0;             /+ total argument count           +/                         <* 
 *>    int         x_urgs      = 0;             /+ urgent count                   +/                         <* 
 *>    /+---(default urgents)----------------+/                                                              <* 
 *>    DEBUG_TOPS   yLOG_enter   (__FUNCTION__);                                                             <* 
 *>    /+---(check for normal version)-------+/                                                              <* 
 *>    if (strcmp (a_argv[0], "themis"       ) == 0)  return 0;                                              <* 
 *>    /+---(walk through urgents)-----------+/                                                              <* 
 *>    for (i = 1; i < a_argc; ++i) {                                                                        <* 
 *>       /+---(prepare)---------------------+/                                                              <* 
 *>       a        = a_argv [i];                                                                             <* 
 *>       x_len    = strllen (a, LEN_RECD);                                                                  <* 
 *>       ++x_total;                                                                                         <* 
 *>       /+---(filter)----------------------+/                                                              <* 
 *>       if (a[0] != '@')  continue;                                                                        <* 
 *>       ++x_urgs;                                                                                          <* 
 *>       DEBUG_ARGS  yLOG_info  ("urgent"    , a);                                                          <* 
 *>       /+---(overall)---------------------+/                                                              <* 
 *>       if      (strncmp(a, "@t"           ,10) == 0)  debug.tops = 'y';                                   <* 
 *>       else if (strncmp(a, "@@tops"       ,10) == 0)  debug.tops = 'y';                                   <* 
 *>       else if (strncmp(a, "@s"           ,10) == 0)  debug.tops = debug.summ  = 'y';                     <* 
 *>       else if (strncmp(a, "@@summ"       ,10) == 0)  debug.tops = debug.summ  = 'y';                     <* 
 *>       /+---(startup/shutdown)------------+/                                                              <* 
 *>       else if (strncmp(a, "@a"           ,10) == 0)  debug.tops = debug.args  = 'y';                     <* 
 *>       else if (strncmp(a, "@@args"       ,10) == 0)  debug.tops = debug.args  = 'y';                     <* 
 *>       else if (strncmp(a, "@c"           ,10) == 0)  debug.tops = debug.conf  = 'y';                     <* 
 *>       else if (strncmp(a, "@@conf"       ,10) == 0)  debug.tops = debug.conf  = 'y';                     <* 
 *>       else if (strncmp(a, "@p"           ,10) == 0)  debug.tops = debug.prog  = 'y';                     <* 
 *>       else if (strncmp(a, "@@prog"       ,10) == 0)  debug.tops = debug.prog  = 'y';                     <* 
 *>       /+---(file processing)-------------+/                                                              <* 
 *>       else if (strncmp(a, "@i"           ,10) == 0)  debug.tops = debug.inpt  = 'y';                     <* 
 *>       else if (strncmp(a, "@@inpt"       ,10) == 0)  debug.tops = debug.inpt  = 'y';                     <* 
 *>       else if (strncmp(a, "@I"           ,10) == 0)  debug.tops = debug.inpt  = debug.inpt_mas = 'y';    <* 
 *>       else if (strncmp(a, "@@INPT"       ,10) == 0)  debug.tops = debug.inpt  = debug.inpt_mas = 'y';    <* 
 *>       else if (strncmp(a, "@o"           ,10) == 0)  debug.tops = debug.outp  = 'y';                     <* 
 *>       else if (strncmp(a, "@@outp"       ,10) == 0)  debug.tops = debug.outp  = 'y';                     <* 
 *>       else if (strncmp(a, "@O"           ,10) == 0)  debug.tops = debug.outp  = debug.outp_mas = 'y';    <* 
 *>       else if (strncmp(a, "@@OUTP"       ,10) == 0)  debug.tops = debug.outp  = debug.outp_mas = 'y';    <* 
 *>       /+---(processing)------------------+/                                                              <* 
 *>       else if (strncmp(a, "@l"           ,10) == 0)  debug.tops = debug.loop  = 'y';                     <* 
 *>       else if (strncmp(a, "@@loop"       ,10) == 0)  debug.tops = debug.loop  = 'y';                     <* 
 *>       else if (strncmp(a, "@L"           ,10) == 0)  debug.tops = debug.loop  = debug.loop_mas =  'y';   <* 
 *>       else if (strncmp(a, "@@LOOP"       ,10) == 0)  debug.tops = debug.loop  = debug.loop_mas =  'y';   <* 
 *>       else if (strncmp(a, "@u"           ,10) == 0)  debug.tops = debug.user  = 'y';                     <* 
 *>       else if (strncmp(a, "@@user"       ,10) == 0)  debug.tops = debug.user  = 'y';                     <* 
 *>       else if (strncmp(a, "@z"           ,10) == 0)  debug.tops = debug.apis  = 'y';                     <* 
 *>       else if (strncmp(a, "@@apis"       ,10) == 0)  debug.tops = debug.apis  = 'y';                     <* 
 *>       else if (strncmp(a, "@x"           ,10) == 0)  debug.tops = debug.sign  = 'y';                     <* 
 *>       else if (strncmp(a, "@@sign"       ,10) == 0)  debug.tops = debug.sign  = 'y';                     <* 
 *>       else if (strncmp(a, "@b"           ,10) == 0)  debug.tops = debug.scrp  = 'y';                     <* 
 *>       else if (strncmp(a, "@@scrp"       ,10) == 0)  debug.tops = debug.scrp  = 'y';                     <* 
 *>       else if (strncmp(a, "@h"           ,10) == 0)  debug.tops = debug.hist  = 'y';                     <* 
 *>       else if (strncmp(a, "@@hist"       ,10) == 0)  debug.tops = debug.hist  = 'y';                     <* 
 *>       /+---(program)---------------------+/                                                              <* 
 *>       else if (strncmp(a, "@g"           ,10) == 0)  debug.tops = debug.graf  = 'y';                     <* 
 *>       else if (strncmp(a, "@@graf"       ,10) == 0)  debug.tops = debug.graf  = 'y';                     <* 
 *>       else if (strncmp(a, "@d"           ,10) == 0)  debug.tops = debug.data  = 'y';                     <* 
 *>       else if (strncmp(a, "@@data"       ,10) == 0)  debug.tops = debug.data  = 'y';                     <* 
 *>       else if (strncmp(a, "@e"           ,10) == 0)  debug.tops = debug.envi  = 'y';                     <* 
 *>       else if (strncmp(a, "@@envi"       ,10) == 0)  debug.tops = debug.envi  = 'y';                     <* 
 *>       else if (strncmp(a, "@E"           ,10) == 0)  debug.tops = debug.envi  = debug.envi_mas = 'y';    <* 
 *>       else if (strncmp(a, "@@ENVI"       ,10) == 0)  debug.tops = debug.envi  = debug.envi_mas = 'y';    <* 
 *>       /+---(complex)---------------------+/                                                              <* 
 *>       else if (strncmp(a, "@q"           ,10) == 0)  PROG_urgsmass ('n', 'n');                           <* 
 *>       else if (strncmp(a, "@@quiet"      ,10) == 0)  PROG_urgsmass ('n', 'n');                           <* 
 *>       else if (strncmp(a, "@f"           ,10) == 0)  PROG_urgsmass ('y', '-');                           <* 
 *>       else if (strncmp(a, "@@full"       ,10) == 0)  PROG_urgsmass ('y', '-');                           <* 
 *>       else if (strncmp(a, "@k"           ,10) == 0)  PROG_urgsmass ('y', 'y');                           <* 
 *>       else if (strncmp(a, "@@kitchen"    ,10) == 0)  PROG_urgsmass ('y', 'y');                           <* 
 *>       /+---(specific)--------------------+/                                                              <* 
 *>       else if (strncmp(a, "@@recog"      ,10) == 0)  debug.tops = debug.recog = 'y';                     <* 
 *>       else if (strncmp(a, "@@touch"      ,10) == 0)  debug.tops = debug.touch = 'y';                     <* 
 *>       /+---(unknown)--------------------+/                                                               <* 
 *>       else {                                                                                             <* 
 *>          DEBUG_ARGS  yLOG_note    ("urgent not understood");                                             <* 
 *>       }                                                                                                  <* 
 *>       /+---(done)-----------------------+/                                                               <* 
 *>    }                                                                                                     <* 
 *>    /+---(display urgents)----------------+/                                                              <* 
 *>    DEBUG_ARGS   yLOG_note    ("summarization of urgent processing");                                     <* 
 *>    DEBUG_ARGS   yLOG_value   ("entries"   , x_total);                                                    <* 
 *>    DEBUG_ARGS   yLOG_value   ("urgents"   , x_urgs);                                                     <* 
 *>    DEBUG_ARGS   yLOG_note    ("standard urgents");                                                       <* 
 *>    DEBUG_ARGS   yLOG_char    ("tops"      , debug.tops);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("summ"      , debug.summ);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("args"      , debug.args);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("conf"      , debug.conf);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("prog"      , debug.prog);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("inpt"      , debug.inpt);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("INPT"      , debug.inpt_mas);                                             <* 
 *>    DEBUG_ARGS   yLOG_char    ("outp"      , debug.outp);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("OUTP"      , debug.outp_mas);                                             <* 
 *>    DEBUG_ARGS   yLOG_char    ("loop"      , debug.loop);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("LOOP"      , debug.loop_mas);                                             <* 
 *>    DEBUG_ARGS   yLOG_char    ("user"      , debug.user);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("apis"      , debug.apis);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("sign"      , debug.sign);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("scrp"      , debug.scrp);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("hist"      , debug.hist);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("graf"      , debug.graf);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("data"      , debug.data);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("envi"      , debug.envi);                                                 <* 
 *>    DEBUG_ARGS   yLOG_char    ("ENVI"      , debug.envi_mas);                                             <* 
 *>    DEBUG_ARGS   yLOG_note    ("specialty urgents");                                                      <* 
 *>    DEBUG_ARGS   yLOG_char    ("touch"     , debug.touch);                                                <* 
 *>    DEBUG_ARGS   yLOG_char    ("recog"     , debug.recog);                                                <* 
 *>    /+---(complete)-----------------------+/                                                              <* 
 *>    DEBUG_TOPS   yLOG_exit    (__FUNCTION__);                                                             <* 
 *>    return 0;                                                                                             <* 
 *> }                                                                                                        <*/

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
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   stroke.help       = -1;
   stroke.color      = -1;
   stroke.max        = -1;
   stroke.zth        = -1;
   stroke.fst        = -1;
   stroke.snd        = -1;
   stroke.trd        = -1;
   stroke.fth        = -1;
   ndot              =   0;
   stroke.small      = NOR;
   strlcpy (my.win_title, "petal_writing", LEN_STR);
   strlcpy (my.face_bg  , "coolvetica"   , LEN_STR);
   strlcpy (my.face_sm  , "shrike"       , LEN_STR);
   /*> strlcpy (my.face_sm  , "courier"      , LEN_STR);                              <*/
   /*---(flags)--------------------------*/
   my.rptg_events    = '-';
   my.rptg_dots      = '-';
   my.rptg_recog     = '-';
   my.loop_msec      =   1;
   strlcpy (shape.r_seq , "", LEN_RECD);
   shape.r_len       =   0;
   shape.r_pos       =   0;
   strlcpy (shape.r_done, "", LEN_RECD);
   shape.r_done_show = 'y';
   shape.r_mode      = '-';
   shape.r_letter    = '\0';
   shape.r_state     = -1;
   shape.r_prog      = 0.0;
   shape.r_inc       = 0.0;
   /*---(file names)---------------------*/
   DEBUG_PROG   yLOG_note    ("file names");
   snprintf (my.name_event  , LEN_STR, "%s%s", DIR_INPUT, FILE_EVENT );
   my.file_event     = NULL;
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
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
      if      (strncmp(a, "--letters" , 20) == 0)  stroke.help     = 0;
      else if (strncmp(a, "--NN"      , 20) == 0)  stroke.help     = 1;
      else if (strncmp(a, "--NE"      , 20) == 0)  stroke.help     = 2;
      else if (strncmp(a, "--EE"      , 20) == 0)  stroke.help     = 3;
      else if (strncmp(a, "--SE"      , 20) == 0)  stroke.help     = 4;
      else if (strncmp(a, "--SS"      , 20) == 0)  stroke.help     = 5;
      else if (strncmp(a, "--SW"      , 20) == 0)  stroke.help     = 6;
      else if (strncmp(a, "--WW"      , 20) == 0)  stroke.help     = 7;
      else if (strncmp(a, "--NW"      , 20) == 0)  stroke.help     = 8;
      else if (strncmp(a, "--inner"   , 20) == 0)  stroke.help     = 10;
      else if (strncmp(a, "--outer"   , 20) == 0)  stroke.help     = 11;
      else if (strncmp(a, "--edge"    , 20) == 0)  stroke.help     = 12;
      else if (strncmp(a, "--mode"    , 20) == 0)  stroke.help     = 13;
      else if (strncmp(a, "--two"     , 20) == 0)  stroke.help     = 14;
      else if (strncmp(a, "--color"   , 20) == 0)  stroke.color    = 1;
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
   /*> yX11_start (my.win_title, shape.sz_width, shape.sz_height, 'n', debug.prog, 'n');   <*/
   /*---(initialize)---------------------*/
   TOUCH_open    ();
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
   rc = yVIOPENGL_init   (P_NAMESAKE, P_VERNUM, MODE_MAP, shape.sz_width, shape.sz_height);
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
   rc = yVIEW_full     (YVIEW_MAIN , YVIEW_FLAT , YVIEW_BOTLEF, 1.0, 0, DRAW_main);
   DEBUG_PROG   yLOG_value    ("yVIEW"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   yCMD_direct (":layout min");
   displist_init ();
   font_load     ();
   /*---(commands)-----------------------*/
   rc = yCMD_add (YCMD_M_CONFIG, "label"       , ""    , "s"    , DRAW_help            , "configure the help labels"                                   );
   DEBUG_PROG   yLOG_value   ("label"     , rc);
   rc = yCMD_add (YCMD_M_CONFIG, "pad"         , ""    , "s"    , DRAW_color           , "configure the help colors"                                   );
   DEBUG_PROG   yLOG_value   ("pad"       , rc);
   rc = yCMD_add (YCMD_M_CONFIG, "speed"       , ""    , "s"    , DRAW_speed           , "configure the help colors"                                   );
   DEBUG_PROG   yLOG_value   ("speed"     , rc);
   rc = yCMD_add (YCMD_M_CONFIG, "seq"         , ""    , "cs"   , DRAW_seq             , "configure the help colors"                                   );
   DEBUG_PROG   yLOG_value   ("seq"       , rc);
   rc = yCMD_add (YCMD_M_CONFIG, "size"        , ""    , "s"    , SHAPE_size           , "configure the help colors"                                   );
   DEBUG_PROG   yLOG_value   ("size"      , rc);
   rc = yCMD_add (YCMD_M_CONFIG, "done"        , ""    , "s"    , DRAW_done_show       , "configure showing completed text"                            );
   DEBUG_PROG   yLOG_value   ("done"      , rc);
   rc = yCMD_add (YCMD_M_CONFIG, "press"       , ""    , "s"    , DRAW_press           , "configure showing completed text"                            );
   DEBUG_PROG   yLOG_value   ("press"     , rc);
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
   displist_free ();
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
   /*> TOUCH_close   ();                                                              <*/
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
   /*> snprintf (my.name_root   , LEN_STR, "%s"    , DIR_TEST);                           <* 
    *> snprintf (my.name_conf   , LEN_STR, "%s%s%s", DIR_TEST , DIR_ETC  , FILE_CONF );   <* 
    *> snprintf (my.name_full   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_FULL );   <* 
    *> snprintf (my.name_summ   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_SUMM );   <* 
    *> snprintf (my.name_warn   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_WARN );   <*/
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
   char        x_carg      = 2;
   char       *x_args [2]  = { "petal_unit", "@@kitchen"    };
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
