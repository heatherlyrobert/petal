/*============================[[    beg-code    ]]============================*/
#include    "petal.h"


static char  s_name  [LEN_TERSE] = "";



/*============================--------------------============================*/
/*===----                       program level                          ----===*/
/*============================--------------------============================*/
static void      o___PROGRAM____________o (void) {;}

char
CONF_init               (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   CONF_purge ();
   /*---(configuration)------------------*/
   rc = yPARSE_config (YPARSE_MANUAL, NULL, YPARSE_ONETIME, YPARSE_TRADITION, YPARSE_FILL);
   DEBUG_PROG   yLOG_value   ("yparse"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
CONF_purge              (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_LETTER; ++i) {
      g_lower [i] = g_upper [i] = g_greek [i] = g_arith [i] = '·';
      g_logic [i] = g_boxdr [i] = g_macro [i] = g_punct [i] = '·';
   }
   strcpy (g_lowers, "");
   strcpy (g_uppers, "");
   strcpy (g_greeks, "");
   strcpy (g_ariths, "");
   strcpy (g_logics, "");
   strcpy (g_boxdrs, "");
   strcpy (g_macros, "");
   strcpy (g_puncts, "");
   g_shown = g_lower;
   g_bases = g_lowers;
   return 0;
}



/*============================--------------------============================*/
/*===----                       detailed handlers                      ----===*/
/*============================--------------------============================*/
static void      o___DETAIL_____________o (void) {;}

char
CONF__default           (int n, uchar a_verb [LEN_TERSE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_name      [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_verb"     , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);
   --rce;  if (strcmp (a_verb, "DEFAULT") != 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read details)-------------------*/
   rc = yPARSE_scanf (a_verb, "T"  , x_name);
   DEBUG_CONF  yLOG_value   ("scanf"      , rc);
   if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("x_name"     , x_name);
   /*---(save)---------------------------*/
   ystrlcpy (s_name, x_name, LEN_TERSE);
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
CONF__load              (char a_dir [LEN_TERSE], char a_desc [LEN_TERSE], char a_seq, char a_field [LEN_LABEL], char a_bases [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   char        a           =   -1;
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL) {
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   l = strlen (a_dir);
   DEBUG_CONF  yLOG_value   ("l"         , l);
   --rce;  if (l != 2) {
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CONF  yLOG_value   ("a_seq"     , a_seq);
   --rce;  if (a_seq < 0 || a_seq > 5) {
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CONF  yLOG_point   ("a_field"   , a_field);
   --rce;  if (a_field == NULL) {
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   l = strlen (a_field);
   DEBUG_CONF  yLOG_value   ("l"         , l);
   --rce;  if (a_seq != 5 && l != 15) {
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(direction)----------------------*/
   switch (a_dir [0]) {
   case 'E' :
      if (a_dir [1] == 'E')  a = 0;
      break;
   case 'N' :
      switch (a_dir [1]) {
      case 'E' :  a = 1;  break;
      case 'N' :  a = 2;  break;
      case 'W' :  a = 3;  break;
      }
      break;
   case 'W' :
      if (a_dir [1] == 'W')  a = 4;
      break;
   case 'S' :
      switch (a_dir [1]) {
      case 'W' :  a = 5;  break;
      case 'S' :  a = 6;  break;
      case 'E' :  a = 7;  break;
      }
      break;
   }
   DEBUG_CONF  yLOG_value   ("a"         , a);
   --rce;  if (a < 0 || a > 7) {
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   n = a * 5 + a_seq;
   DEBUG_CONF  yLOG_value   ("n"         , n);
   /*---(load)---------------------------*/
   if (a_seq != 5) {
      g_lower [n] = (a_field [ 0] == ' ') ? '²' : a_field [ 0];
      g_upper [n] = (a_field [ 2] == ' ') ? '²' : a_field [ 2];
      g_greek [n] = (a_field [ 4] == ' ') ? '²' : a_field [ 4];
      g_arith [n] = (a_field [ 6] == ' ') ? '²' : a_field [ 6];
      g_logic [n] = (a_field [ 8] == ' ') ? '²' : a_field [ 8];
      g_boxdr [n] = (a_field [10] == ' ') ? '²' : a_field [10];
      g_macro [n] = (a_field [12] == ' ') ? '²' : a_field [12];
      g_punct [n] = (a_field [14] == ' ') ? '²' : a_field [14];
   } else if (a_seq == 5) {
      g_layer [a] = a_field [ 0];
      if (a_bases != NULL) {
         switch (a) {
         case 0 :  ystrlcpy (g_ariths, a_bases, LEN_TITLE);  break;
         case 1 :  ystrlcpy (g_puncts, a_bases, LEN_TITLE);  break;
         case 2 :  ystrlcpy (g_uppers, a_bases, LEN_TITLE);  break;
         case 3 :  ystrlcpy (g_boxdrs, a_bases, LEN_TITLE);  break;
         case 4 :  ystrlcpy (g_greeks, a_bases, LEN_TITLE);  break;
         case 5 :  ystrlcpy (g_macros, a_bases, LEN_TITLE);  break;
         case 6 :  ystrlcpy (g_lowers, a_bases, LEN_TITLE);  break;
         case 7 :  ystrlcpy (g_logics, a_bases, LEN_TITLE);  break;
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
CONF__mapping           (int n, uchar a_verb [LEN_TERSE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        x_name      [LEN_TERSE] = "";
   char        x_1st       [LEN_LABEL] = "";
   char        x_dir       [LEN_LABEL] = "";
   char        x_fast      [LEN_LABEL] = "";
   char        x_CW2nd     [LEN_LABEL] = "";
   char        x_CW3rd     [LEN_LABEL] = "";
   char        x_CCW2nd    [LEN_LABEL] = "";
   char        x_CCW3rd    [LEN_LABEL] = "";
   char        x_layers    [LEN_LABEL] = "";
   char        x_bases     [LEN_TITLE] = "";
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_verb"     , a_verb);
   --rce;  if (a_verb == NULL) {
      yURG_err ('f', "%4d, verb null", n);
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);
   --rce;  if (strcmp (a_verb, "MAP") != 0) {
      yURG_err ('f', "%4d, verb å%-8.8sæ incorrectly called MAP handler", n, a_verb);
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(field count)--------------------*/
   rc = yPARSE_ready (&c);
   DEBUG_INPT   yLOG_char    ("ready"     , rc);
   --rce;  if (rc != 'y') {
      yURG_err ('f', "%4d, verb å%-8.8sæ, yPARSE not ready", n, a_verb);
      DEBUG_INPT  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("fields"    , c);
   --rce; if (c < 1) {
      yURG_err ('f', "%4d, verb å%-8.8sæ, yPARSE no fields found", n, a_verb);
      DEBUG_INPT  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   --rce; if (c != 11) {
      yURG_err ('f', "%4d, verb å%-8.8sæ, yPARSE not using current eleven (11) field format", n, a_verb);
      DEBUG_INPT  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(read details)-------------------*/
   rc = yPARSE_scanf (a_verb, "TTTLLLLLL3"  , x_name, x_dir, x_fast, x_1st, x_CW2nd, x_CW3rd, x_CCW2nd, x_CCW3rd, x_layers, x_bases);
   DEBUG_CONF  yLOG_value   ("scanf"      , rc);
   if (rc < 0) {
      yURG_err ('f', "%4d, verb å%-8.8sæ, %d fields, yPARSE_scanf failed (%d)", n, a_verb, c, rc);
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("x_name"     , x_name);
   /*---(quick-out)----------------------*/
   if (strcmp (x_name, s_name) != 0) {
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(save)---------------------------*/
   printf ("%-10.10s  %-2.2s  å%-10.10sæ  å%-16.16sæ  å%-16.16sæ  å%-16.16sæ  å%-16.16sæ  å%-16.16sæ  å%-16.16sæ  å%sæ\n",
         x_name, x_dir, x_fast, x_1st,
         x_CW2nd , x_CW3rd ,
         x_CCW2nd, x_CCW3rd,
         x_layers, x_bases);
   rc = CONF__load (x_dir, "inner"    , 0, x_1st    , NULL);
   rc = CONF__load (x_dir, "outer·cw" , 1, x_CW2nd  , NULL);
   rc = CONF__load (x_dir, "edge·cw"  , 2, x_CW3rd  , NULL);
   rc = CONF__load (x_dir, "outer·ccw", 3, x_CCW2nd , NULL);
   rc = CONF__load (x_dir, "edge·ccw" , 4, x_CCW3rd , NULL);
   rc = CONF__load (x_dir, "layers"   , 5, x_layers , x_bases);
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*============================--------------------============================*/
/*===----                        pull driver                           ----===*/
/*============================--------------------============================*/
static void      o___DRIVER_____________o (void) {;}

char
CONF__handler           (int n, uchar a_verb [LEN_TERSE], char a_exist, void *a_handler)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(dispatch)-----------------------*/
   DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);
   switch (a_verb [0]) {
   case 'D' :  /* default map */
      rc = CONF__default (n, a_verb);
      break;
   case 'M' :  /* key mapping */
      rc = CONF__mapping (n, a_verb);
      break;
   case 'S' :  /* short-cuts  */
      break;
   }
   DEBUG_CONF  yLOG_value   ("handler"   , rc);
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
CONF_pull               (cchar a_file [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "reading configuration file...");
   /*---(purge the tables)---------------*/
   rc = yPARSE_reset_in ();
   DEBUG_CONF   yLOG_value   ("purge_in"  , rc);
   rc = CONF_purge ();
   DEBUG_CONF   yLOG_value   ("purge"     , rc);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_file"     , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_CONF  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_file"     , a_file);
   /*---(read all lines)-----------------*/
   rc = yPARSE_autoread (a_file, NULL, CONF__handler);
   DEBUG_CONF  yLOG_value   ("read"      , rc);
   /*---(close)--------------------------*/
   rc = yPARSE_close ();
   DEBUG_CONF   yLOG_value   ("close"     , rc);
   --rce; if (rc < 0) {
      yURG_err ('f', "yPARSE failed closing configuration file");
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(trouble)------------------------*/
   --rce;  if (rc <  0) {
      DEBUG_CONF  yLOG_note    ("no file found");
      DEBUG_CONF  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("å%sæ\n", g_bases);                                                    <*/
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*============================--------------------============================*/
/*===----                        unit testing                          ----===*/
/*============================--------------------============================*/
static void      o___UNITTEST___________o (void) {;}

char*
CONF__unit              (char *a_question, int a_num)
{
   int         i           =    0;
   uchar       c           =  '·';
   char        s           [LEN_TERSE] = "";
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   if      (strcmp (a_question, "loaded")         == 0) {
      if (a_num < 0 || a_num > 7) {
         sprintf (unit_answer, "CONF loaded  (%1d) : not recognized", a_num);
         return unit_answer;
      }
      switch (a_num) {
      case 0 : p = g_lower;  break;
      case 1 : p = g_upper;  break;
      case 2 : p = g_greek;  break;
      case 3 : p = g_arith;  break;
      case 4 : p = g_logic;  break;
      case 5 : p = g_boxdr;  break;
      case 6 : p = g_macro;  break;
      case 7 : p = g_punct;  break;
      }
      for (i = 0; i < MAX_LETTER; ++i) {
         c = p [i];
         if (c < 32 || c == 127)  strcpy (s, "¢ ");
         else                     sprintf (s, "%c ", c);
         ystrlcat (t, s, LEN_HUND);
      }
      ystrltrim (t, ySTR_BOTH, LEN_HUND);
      sprintf (unit_answer, "CONF loaded  (%1d) : å%sæ", a_num, t);
   }
   return unit_answer;
}


