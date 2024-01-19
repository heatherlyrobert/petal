/*============================[[    beg-code    ]]============================*/
#include    "petal.h"


static int  s_new_x     = 0;
static int  s_new_y     = 0;
static int  s_new_r     = 0;
static int  s_fileno    = 0;
static int  s_flags     = 0;

static int  s_line      = 0;
static int  s_rptg      = 0;
static int  s_last      = 0;


static struct {
   int         t_val;
   char        t_desc      [LEN_TERSE];
   int         t_seen;
} s_type [LEN_LABEL] = {
   {     0, "SYN   ", 0    },  
   {     1, "DEP   ", 0    },  
   {     2, "REL   ", 0    },  
   {     3, "ABS   ", 0    },  
   {     4, "BTN   ", 0    },  
   {    -1, ""      , 0    },  
};

static struct {
   int         c_type;
   int         c_val;
   char        c_desc      [LEN_TERSE];
   int         c_seen;
} s_code [LEN_DESC] = {
   /*---(syn)----------------------------*/
   {     0,     0  , "all     ", 0    },  
   /*---(abs)----------------------------*/
   {     3,  0x00  , "abs_x   ", 0    },  
   {     3,  0x01  , "abs_y   ", 0    },  
   {     3,  0x04  , "button  ", 0    },  
   {     3,  0x18  , "hardnes ", 0    },  
   {     3,  0x1a  , "tilt_x  ", 0    },  
   {     3,  0x1b  , "tilt_y  ", 0    },  
   {     3,  0x2f  , "slot    ", 0    },  
   {     3,  0x35  , "eps_X   ", 0    },  
   {     3,  0x36  , "eps_Y   ", 0    },  
   {     3,  0x39  , "id      ", 0    },  
   {     1,  0x0140, "hover   ", 0    },  
   {     1,  0x014a, "touch   ", 0    },  
   /*---(end)----------------------------*/
   {    -1,    -1  , ""        , 0    },  
   /*---(done)---------------------------*/
};


static char s_sync        = '-';

static int  s_xpos        = -6666;
static int  s_ypos        = -6666;

static int  s_xsav        = -6666;
static int  s_ysav        = -6666;




char
TOUCH_reset             (void)
{
   DEBUG_TOUCH  yLOG_enter   (__FUNCTION__);
   my.t_x      = my.t_y    = -6666;
   my.s_x      = my.s_y    = -6666;
   my.m_x      = my.m_y    = my.m_r    = -6666;
   my.m_n      =  -1;
   my.m_valid  = '·';
   my.m_button = -1;
   DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TOUCH_init              (void)
{
   DEBUG_TOUCH  yLOG_enter   (__FUNCTION__);
   my.t_left = my.t_topp = my.t_wide = my.t_tall = -6666;
   my.s_left = my.s_topp = my.s_wide = my.s_tall = -6666;
   my.w_left = my.w_topp = my.w_wide = my.w_tall = -6666;
   my.m_align = YGLTEX_MIDCEN;
   my.s_xratio = my.s_yratio = 0.00;
   my.m_touch  = '·';
   TOUCH_reset ();
   DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> open touch device event file ----------[ leaf   [ ------ ]-*/
TOUCH__open             (char a_name [LEN_FULL], char a_dir, FILE **f)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        a           [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_TOUCH  yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_TOUCH  yLOG_point   ("*f"        , *f);
   --rce;  if (*f != NULL) {
      DEBUG_TOUCH  yLOG_note    ("file already open");
      DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(access)-------------------------*/
   DEBUG_TOUCH  yLOG_char    ("a_dir"     , a_dir);
   --rce;  switch (a_dir) {
   case 'r' :  strcpy (a, "rt");   break;
   case 'w' :  strcpy (a, "wt");   break;
   case 'a' :  strcpy (a, "at");   break;
   default  :
               DEBUG_TOUCH  yLOG_note    ("illegal access code");
               DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
               return rce;
   }
   DEBUG_TOUCH  yLOG_info    ("a"         , a);
   /*---(open)---------------------------*/
   DEBUG_TOUCH  yLOG_info    ("name"      , a_name);
   *f = fopen (a_name, a);
   DEBUG_TOUCH  yLOG_point   ("*f"        , *f);
   --rce;  if (*f == NULL) {
      DEBUG_TOUCH  yLOG_note    ("could not be opennen");
      DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_TOUCH  yLOG_note    ("succesfully opened");
   /*---(complete)-----------------------*/
   DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
   return  0;
}

char
TOUCH__close       (FILE **f)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc           = 0;
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_TOUCH  yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_TOUCH  yLOG_point   ("*f"        , *f);
   --rce;  if (*f == NULL) {
      DEBUG_TOUCH  yLOG_note    ("file already closed");
      DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   rc = fclose (*f);
   DEBUG_TOUCH  yLOG_value   ("fclose"    , rc);
   if (rc < 0) {
      DEBUG_TOUCH  yLOG_note    ("file cound not be closed");
      DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground-pointer)-----------------*/
   *f = NULL;
   DEBUG_TOUCH  yLOG_point   ("*f"        , *f);
   /*---(complete)-----------------------*/
   DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
   return  0;
}

char         /*--> open touch device event file ----------[ leaf   [ ------ ]-*/
TOUCH__normal      (void)
{
   fcntl  (s_fileno, F_SETFL, s_flags);
   return 0;
}

char         /*--> open touch device event file ----------[ leaf   [ ------ ]-*/
TOUCH__check       (void)
{
   /*---(locals)-----------*-------------*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;
   int         x_flags     = 0;
   int         x_ch        = 0;
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_fileno    = 0;
   s_flags     = 0;
   /*---(set to non-blocking)------------*/
   DEBUG_TOUCH  yLOG_snote   ("non-blocking");
   s_fileno    = fileno (my.f_event);
   s_flags     = fcntl  (s_fileno, F_GETFL, 0);
   fcntl (s_fileno, F_SETFL, s_flags | O_NONBLOCK);
   /*---(test for input)-----------------*/
   x_ch = fgetc (my.f_event);
   DEBUG_TOUCH  yLOG_sint    (x_ch);
   --rce;  if (x_ch < 0) {
      DEBUG_TOUCH  yLOG_snote   ("nothing in queue");
      TOUCH__normal ();
      DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   /*---(put the char back)--------------*/
   rc = ungetc (x_ch, my.f_event);
   --rce;  if (rc != x_ch) {
      DEBUG_TOUCH  yLOG_snote   ("could not unget");
      TOUCH__normal ();
      DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   DEBUG_TOUCH  yLOG_snote   ("ready to read");
   /*---(complete)-----------------------*/
   DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
   return  0;
}

char
TOUCH__event_type       (int a_evtype, char *r_track, char r_desc [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_senter  (__FUNCTION__);
   DEBUG_TOUCH  yLOG_sint    (a_evtype);
   /*---(defaults)-----------------------*/
   if (r_track != NULL)  *r_track = '·';
   if (r_desc  != NULL)  strcpy (r_desc , "");
   /*---(defense)------------------------*/
   --rce;  if (a_evtype < 0) {
      DEBUG_TOUCH  yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(locate)-------------------------*/
   --rce;  for (i = 0; i < LEN_LABEL; ++i) {
      /*---(filter)----------------------*/
      if (s_type [i].t_val < 0)          break;
      if (s_type [i].t_val != a_evtype)  continue;
      /*---(handle)----------------------*/
      DEBUG_TOUCH  yLOG_snote   ("FOUND");
      DEBUG_TOUCH  yLOG_snote   (s_type [i].t_desc);
      ++(s_type [i].t_seen);
      if (r_desc != NULL)  strcpy (r_desc, s_type [i].t_desc);
      /*---(track)--------------------------*/
      if (my.ev_major == 0xff || my.ev_major == a_evtype) {
         if (r_track != NULL) {
            DEBUG_TOUCH  yLOG_snote   ("tracking");
            *r_track = 'y';
         }
      } else {
         DEBUG_TOUCH  yLOG_snote   ("silent");
      }
      /*---(sync)---------------------------*/
      if (a_evtype == 0) {
         /*> printf ("SYNC NOW\n");                                                   <*/
         s_sync = 'y';
      }
      /*---(complete)--------------------*/
      DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
      return 1;
   }
   /*---(handle trouble)-----------------*/
   DEBUG_TOUCH  yLOG_snote   ("not found");
   if (r_desc != NULL)  strcpy (r_desc, "-?-   ");
   /*---(track)--------------------------*/
   if (my.ev_major == 0xff) {
      if (r_track != NULL) {
         DEBUG_TOUCH  yLOG_snote   ("tracking");
         *r_track = 'y';
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
   return  0;
}

char
TOUCH__event_code       (int a_evtype, int a_evcode, char *b_track, char r_desc [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_senter  (__FUNCTION__);
   DEBUG_TOUCH  yLOG_sint    (a_evtype);
   DEBUG_TOUCH  yLOG_sint    (a_evcode);
   /*---(defaults)-----------------------*/
   if (r_desc  != NULL)  strcpy (r_desc , "");
   /*---(defense)------------------------*/
   --rce;  if (a_evcode < 0) {
      DEBUG_TOUCH  yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(locate)-------------------------*/
   --rce;  for (i = 0; i < LEN_LABEL; ++i) {
      /*---(filter)----------------------*/
      if (s_code [i].c_val  < 0)          break;
      if (s_code [i].c_type != a_evtype)  continue;
      if (s_code [i].c_val  != a_evcode)  continue;
      /*---(handle)----------------------*/
      DEBUG_TOUCH  yLOG_snote   ("FOUND");
      DEBUG_TOUCH  yLOG_snote   (s_code [i].c_desc);
      ++(s_code [i].c_seen);
      if (r_desc != NULL)  strcpy (r_desc, s_code [i].c_desc);
      /*---(track)--------------------------*/
      if (my.ev_minor == 0xff || my.ev_minor == a_evcode) {
         if (b_track != NULL) {
            if (*b_track == 'y') {
               DEBUG_TOUCH  yLOG_snote   ("tracking");
            } else {
               DEBUG_TOUCH  yLOG_snote   ("major not tracking");
            }
         }
      } else {
         DEBUG_TOUCH  yLOG_snote   ("silent");
         if (b_track != NULL)  *b_track = '·';
      }
      /*---(complete)--------------------*/
      DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
      return 1;
   }
   /*---(handle trouble)-----------------*/
   DEBUG_TOUCH  yLOG_snote   ("not found");
   if (r_desc != NULL)  strcpy (r_desc, "--?--   ");
   /*---(track)--------------------------*/
   if (my.ev_minor == 0xff) {
      if (b_track != NULL) {
         if (*b_track == 'y') {
            DEBUG_TOUCH  yLOG_snote   ("tracking");
         } else {
            DEBUG_TOUCH  yLOG_snote   ("major not tracking");
         }
      } else {
         DEBUG_TOUCH  yLOG_snote   ("silent");
         if (b_track != NULL)  *b_track = '·';
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
   return  0;
}

char
TOUCH__single           (FILE *f, int *r_type, int *r_code, int *r_value, char *r_track, char r_out [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         ch          =    0;
   uchar       x_ch        =    0;
   int         c           =    0;
   char        t           [LEN_LABEL] = "";
   char        x_out       [LEN_FULL]  = "";
   int         x_type      =    0;
   int         x_code      =    0;
   int         x_value     =    0;
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_enter   (__FUNCTION__);
   /*---(one record)---------------------*/
   while (1) {
      /*---(get and format character)----*/
      ++c;
      ch = fgetc (f);
      x_ch = ch;
      sprintf (t, "%02x ", x_ch);
      strcat  (x_out, t);
      /*---(timestamps)------------------*/
      if (c ==  8)   { strcat (x_out, "  ");               continue; }
      if (c == 16)   { strcat (x_out, "  ");               continue; }
      if (c <  17)                                         continue;
      /*---(event types)-----------------*/
      if (c == 17)   { x_type   = x_ch;                    continue; }
      if (c == 18) {
         x_type += x_ch * 256;
         TOUCH__event_type (x_type, r_track, t);
         strcat (x_out, t);                                continue;
      }
      /*---(event codes)-----------------*/
      if (c == 19)   { x_code   = x_ch;                    continue; }
      if (c == 20) {
         x_code += x_ch * 256;
         TOUCH__event_code (x_type, x_code, r_track, t);
         strcat (x_out, t);                                continue;
      }
      /*---(event value)-----------------*/
      if (c == 21)   { x_value  = x_ch;                    continue; }
      if (c == 22)   { x_value += x_ch *  256;             continue; }
      if (c == 23)   { x_value += x_ch * (256 * 256);      continue; }
      if (c == 24)   { x_value += x_ch * (256 * 256 * 256);          }
      /*---(wrap-up)---------------------*/
      sprintf (t, "%10d", x_value);
      strcat  (x_out, t);
      break;
   }
   /*---(report)-------------------------*/
   DEBUG_TOUCH  yLOG_info    ("x_out"     , x_out);
   /*---(global)-------------------------*/
   if (x_type == 0x03 && x_code == 0x00)  s_xpos = x_value;
   if (x_type == 0x03 && x_code == 0x01)  s_ypos = x_value;
   if (x_type == 0x01) {
      if (x_code == 0x0140 && x_value == 0)  my.m_touch = '·';
      if (x_code == 0x0140 && x_value == 1)  my.m_touch = 'h';
      if (x_code == 0x014a && x_value == 0)  my.m_touch = 'h';
      if (x_code == 0x014a && x_value == 1)  my.m_touch = 'T';
      /*> printf ("handled %4x with %4x result %c\n", x_code, x_value, my.m_touch);   <*/
   }
   /*---(save-back)----------------------*/
   if (r_type  != NULL)  *r_type   = x_type;
   if (r_code  != NULL)  *r_code   = x_code;
   if (r_value != NULL)  *r_value  = x_value;
   if (r_out   != NULL)  ystrlcpy (r_out, x_out, LEN_FULL);
   /*---(complete)-----------------------*/
   DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
   return  0;
}


char             /* [------] read input event -------------------------------*/
TOUCH_read         (void)
{
   /*---(locals)-----------*-------------*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;
   int         ch          = 0;
   uchar       x_ch        = 0;
   uchar       x_button    = 0;
   int         x_count     = 0;
   char   next   [100];
   char   output [200];
   int    ev_type  = 0;
   int    ev_code  = 0;
   int    ev_value = 0;
   char        x_track     =  '·';
   float       x           = 0.0;
   float       y           = 0.0;
   char        t           [LEN_DESC]  = "    ·x      ·y      ·w      ·t";
   char        s           [LEN_DESC]  = "    ·x      ·y";
   char        r           [LEN_DESC]  = "       ··         ··";
   char        x_ready     = '-';
   /*---(quick-out)----------------------*/
   rc = TOUCH__check  ();
   if (rc < 0)  return 0;
   else         x_ready = 'y';
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_enter   (__FUNCTION__);
   /*---(headers and line breaks)--------*/
   if (s_line == 0 || (s_rptg != s_last && (s_rptg % 25) == 0)) {
      RPTG_EVENTS  printf ("\n-- -- -- -- -- -- -- --   -- -- -- -- -- -- -- --   -- -- typ   -- -- code-   -- -- -- -- value-----\n");
   }
   if (s_line == 0 || (s_rptg != s_last && (s_rptg %  5) == 0)) {
      RPTG_EVENTS  printf ("\n");
   }
   ++s_line;
   s_last = s_rptg;
   /*---(prepare)------------------------*/
   x_count = 0;
   /*> strcpy  (output, "");                                                          <*/
   while (x_ready == 'y') {
      rc = TOUCH__single (my.f_event, &ev_type, &ev_code, &ev_value, &x_track, output);
      DEBUG_TOUCH  yLOG_complex ("single"    , "%3d %3d %6d, %c, %-20.20s", ev_type, ev_code, ev_value, x_track, output);
      if (x_track == 'y')  printf ("%s\n", output);
      if (ev_type == 0x01) {
         if (ev_code == 0x014a) {
            switch (ev_value) {
            case 1 :
               rc = TOUCH_point (s_xpos, s_ypos);
               rc = DOT_beg     (my.t_x, my.t_y, my.s_x, my.s_y, my.m_x, my.m_y, my.m_r);
               rc = PETAL_beg   (my.m_x, my.m_y, my.m_r);
               break;
            case 0 :
               rc = TOUCH_point (s_xpos, s_ypos);
               rc = DOT_end     (my.t_x, my.t_y, my.s_x, my.s_y, my.m_x, my.m_y, my.m_r);
               rc = PETAL_end   (my.m_x, my.m_y, my.m_r);
               rc = LETTER_by_stroke (g_petals [9].p, g_petals [1].p, g_petals [2].p, g_petals [3].p);
               break;
            }
         }
      }
      else if (s_sync  == 'y') {
         rc = TOUCH_point  (s_xpos, s_ypos);
         if (my.m_touch == 'T') {
            rc = DOT_add     (my.t_x, my.t_y, my.s_x, my.s_y, my.m_x, my.m_y, my.m_r);
            rc = PETAL_add   (my.m_x, my.m_y, my.m_r);
         }
         s_xsav = s_xpos;
         s_ysav = s_ypos;
         s_sync = '-';
      }
      x_ready = '-';
      rc = TOUCH__check  ();
      if (rc >= 0) x_ready = 'y';
   }


   DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
   return 0;



   /*---(finger touch)----------------*/
   if (ev_type == 3 && ev_code == 0x39 && ev_value >= 0)  {
      stroke.channel = ev_value;
      stroke.beg     = timestamp ();
      g_ndot = 0;
   }
   /*---(finger lift)-----------------*/
   if (ev_type == 3 && ev_code == 0x39 && ev_value <  0)  {
      stroke.end   = timestamp ();
      stroke.diff  = stroke.end - stroke.beg;
      rc = STROKE_end (s_new_x, s_new_y, s_new_r);
   }
   /*---(x-value)---------------------*/
   if (ev_type == 3 && ev_code == 0x35)  {
      x     = ((float) ev_value / 1800.0);
      s_new_x = (1366.0 * (1 - x));
      s_new_y = 0;
   }
   /*---(y-value)---------------------*/
   if (ev_type == 3 && ev_code == 0x36)  {
      y     = ((float) ev_value / 1800.0);
      s_new_y = (768.0 * y);
      s_new_r = sqrt((s_new_x * s_new_x) + (s_new_y * s_new_y));
      if (g_ndot == 0) rc = STROKE_begin (s_new_x, s_new_y, s_new_r);
      else             rc = stroke_next  (s_new_x, s_new_y, s_new_r);
   }

   TOUCH__normal ();
   /*---(complete)-------------------------*/
   return rc;
}

char
TOUCH__ribbon           (int a_wx, int a_wy)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   short       x_left, x_wide, x_righ;
   short       x_bott, x_tall, x_topp;
   int         wr          =    0;
   static char x_touch     =  '·';
   static char x_button    =  '·';
   int         x, y;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_complex ("args"      , "%5dx, %5dy", a_wx, a_wy);
   /*---(get ribbon coords)--------------*/
   yVIEW_curses (YVIEW_RIBBON, x_name, NULL, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   x_topp = x_bott - x_tall;
   x_righ = x_left + x_wide;
   DEBUG_GRAF   yLOG_complex (x_name, "%4dl  %4dr  %4dx  %4db  %4dt  %4dy", x_left, x_righ, x_wide, x_bott, x_topp, x_tall);
   /*---(check boundaries)---------------*/
   --rce;  if (a_wx < x_left || a_wx > x_righ) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_wy < x_topp || a_wy > x_bott) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update touch)-------------------*/
   DEBUG_DATA   yLOG_char    ("m_touch"   , my.m_touch);
   if (my.m_touch == 'T')   my.m_touch = 'R';
   if (my.m_touch == 'h')   my.m_touch = 'r';
   DEBUG_DATA   yLOG_char    ("m_touch"   , my.m_touch);
   /*---(save values)--------------------*/
   wr = sqrt ((a_wx * a_wx) + (a_wy * a_wy));
   my.m_x      = a_wx;
   my.m_y      = a_wy;
   my.m_r      = wr;
   my.m_valid  = 'y';
   /*> x           = ((a_wx - x_left) / 40) * 16;                                     <*/
   /*> y           = (-a_wy - 10) / 40;                                               <*/
   /*> my.m_button = x + y;                                                           <*/
   /*> DEBUG_DATA   yLOG_complex ("button"    , "%02x %02x %02x", x, y, my.m_touch);   <*/
   /*---(button action)------------------*/
   /*> DEBUG_DATA   yLOG_complex ("touching"  , "%c %c %d", x_touch, my.m_touch, my.m_button);   <*/
   rc = yVIOPENGL_ribbon_act (my.m_valid, my.m_touch, a_wx, a_wy);
   /*> if (x_touch == 'R' && my.m_touch == 'r') {                                               <* 
    *>    DEBUG_DATA   yLOG_note    ("touch released");                                         <* 
    *>    /+> switch (my.m_button) {                                                      <*    <* 
    *>     *> case 0x00 :                                                                 <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("previous workspace");                        <*    <* 
    *>     *>    system("fluxbox-remote \"PrevWorkspace\"");                              <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> case 0x10 :                                                                 <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("next workspace");                            <*    <* 
    *>     *>    system("fluxbox-remote \"NextWorkspace\"");                              <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> case 0x01 :                                                                 <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("previous window");                           <*    <* 
    *>     *>    system("fluxbox-remote \"PrevWindow (workspace=[current])\"");           <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> case 0x11 :                                                                 <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("next window");                               <*    <* 
    *>     *>    system("fluxbox-remote \"NextWindow (workspace=[current])\"");           <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> case 0x03 :                                                                 <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("toggle letter help");                        <*    <* 
    *>     *>    if (stroke.help == 0) stroke.help = -1; else stroke.help = 0;            <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> case 0x13 :                                                                 <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("toggle balls");                              <*    <* 
    *>     *>    if (my.show_pball == 'y')  SHAPE_pball ("hide");                         <*    <* 
    *>     *>    else                       SHAPE_pball ("show");                         <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> case 0x16 :                                                                 <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("exit");                                      <*    <* 
    *>     *>    yCMD_direct (":qa");                                                     <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> default:                                                                    <*    <* 
    *>     *>    DEBUG_DATA   yLOG_note    ("?. unknown button");                         <*    <* 
    *>     *>    break;                                                                   <*    <* 
    *>     *> }                                                                           <+/   <* 
    *>    TOUCH_reset ();                                                                       <* 
    *>    DOT_reset   ();                                                                       <* 
    *>    PETAL_reset ();                                                                       <* 
    *> }                                                                                        <*/
   if (rc == 1) {
      TOUCH_reset ();
      DOT_reset   ();
      PETAL_reset ();
   }
   /*---(save local)---------------------*/
   x_touch  = my.m_touch;
   x_button = my.m_button;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 2;
}

char
TOUCH_point             (int x, int y)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         wx          = -6666;
   int         wy          = -6666;
   int         wr          = -6666;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_complex ("args"      , "%5dx, %5dy", x, y);
   /*---(reset)--------------------------*/
   TOUCH_reset ();
   /*---(defense)------------------------*/
   --rce;  if (my.t_wide == -6666) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (my.s_wide == -6666) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (my.w_wide == -6666) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save tablet)--------------------*/
   my.t_x  = x;
   my.t_y  = y;
   DEBUG_DATA   yLOG_complex ("tablet"    , "%5dx, %5dy", my.t_x, my.t_y);
   /*---(save screen)--------------------*/
   my.s_x  = (x - my.s_left) * my.s_xratio;
   my.s_y  = (y - my.s_topp) * my.s_yratio;
   DEBUG_DATA   yLOG_complex ("screen"    , "%5dx, %5dy", my.s_x, my.s_y);
   /*---(set xpos)-----------------------*/
   DEBUG_DATA   yLOG_value   ("m_align"   , my.m_align);
   if        (my.s_x < my.w_left) {
      DEBUG_DATA   yLOG_note    ("too far left");
   } else if (my.s_x > my.w_left + my.w_wide) {
      DEBUG_DATA   yLOG_note    ("too far right, check ribbon");
      wx = my.s_x - my.w_left;
      wy = my.w_topp - my.s_y;
      rc = TOUCH__ribbon (wx, wy);
      if (rc == 2) {
         DEBUG_DATA   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   } else {
      DEBUG_DATA   yLOG_note    ("in x-range");
      switch (my.m_align) {
      case YGLTEX_TOPLEF : case YGLTEX_MIDLEF : case YGLTEX_BOTLEF :
         DEBUG_DATA   yLOG_note    ("handle lefts");
         wx = my.s_x - my.w_left;
         break;
      case YGLTEX_TOPCEN : case YGLTEX_MIDCEN : case YGLTEX_BOTCEN :
         DEBUG_DATA   yLOG_note    ("handle centers");
         wx = my.s_x - (my.w_left + (my.w_wide / 2.0));
         break;
      case YGLTEX_TOPRIG : case YGLTEX_MIDRIG : case YGLTEX_BOTRIG :
         DEBUG_DATA   yLOG_note    ("handle rights");
         wx = my.s_x - (my.w_left + my.w_wide);
         break;
      }
   }
   DEBUG_DATA   yLOG_value   ("wx"        , wx);
   /*---(set ypos)-----------------------*/
   if        (my.s_y < my.w_topp) {
      DEBUG_DATA   yLOG_note    ("too far up");
   } else if (my.s_y > my.w_topp + my.w_tall) {
      DEBUG_DATA   yLOG_note    ("too far down");
   } else {
      DEBUG_DATA   yLOG_note    ("in y-range");
      switch (my.m_align) {
      case YGLTEX_TOPLEF : case YGLTEX_TOPCEN : case YGLTEX_TOPRIG :
         DEBUG_DATA   yLOG_note    ("handle tops");
         wy = my.w_topp - my.s_y;
         break;
      case YGLTEX_MIDLEF : case YGLTEX_MIDCEN : case YGLTEX_MIDRIG :
         DEBUG_DATA   yLOG_note    ("handle middles");
         wy = (my.w_topp + (my.w_tall / 2.0)) - my.s_y ;
         break;
      case YGLTEX_BOTLEF : case YGLTEX_BOTCEN : case YGLTEX_BOTRIG :
         DEBUG_DATA   yLOG_note    ("handle bottoms");
         wy = (my.w_topp + my.w_tall) - my.s_y;
         break;
      }
   }
   DEBUG_DATA   yLOG_value   ("wy"        , wy);
   /*---(radius)-------------------------*/
   if      (wx == -6666)      ;
   else if (wy == -6666)      ;
   else {
      wr = sqrt ((wx * wx) + (wy * wy));
   }
   DEBUG_DATA   yLOG_value   ("wr"        , wr);
   DEBUG_DATA   yLOG_value   ("r_edge"    , shape.r_edge);
   DEBUG_DATA   yLOG_value   ("r_max"     , shape.r_max);
   /*---(save back)----------------------*/
   if      (wx == -6666)                ;
   else if (wy == -6666)                ;
   else if (wr >  shape.r_edge * 1.10)  ;
   else {
      DEBUG_DATA   yLOG_note    ("x, y, and r in range");
      DEBUG_DATA   yLOG_note    ("HIT");
      my.m_x     = wx;
      my.m_y     = wy;
      my.m_r     = wr;
      my.m_valid = 'y';
      DEBUG_DATA   yLOG_complex ("window"    , "%5dx, %5dy, %5dr", my.m_x, my.m_y, my.m_r);
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_note    ("MISS");
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*============================--------------------============================*/
/*===----                         unit testing                         ----===*/
/*============================--------------------============================*/
static void      o___UNITTEST________________o (void) {;}

char
TOUCH_force_data        (char a_name [LEN_FULL], int a_type, int a_code, int a_value)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        i           =    0;
   char        x_data      [LEN_DESC]  = "";
   uchar       c           =    0;
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   rc = TOUCH__open (a_name, 'a', &f);
   DEBUG_TOUCH  yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(null data))---------------------*/
   for (i = 0; i < LEN_DESC; ++i)   x_data [i] = '\0';
   /*---(write type)---------------------*/
   c  = a_type  % 256; 
   a_type  = (a_type  - c) / 256;
   x_data [16] = c;
   c  = a_type  % 256; 
   a_type  = (a_type  - c) / 256;
   x_data [17] = c;
   /*---(write code)---------------------*/
   c  = a_code  % 256; 
   a_code  = (a_code  - c) / 256;
   x_data [18] = c;
   c  = a_code  % 256; 
   a_code  = (a_code  - c) / 256;
   x_data [19] = c;
   /*---(write code)---------------------*/
   c  = a_value % 256; 
   a_value = (a_value - c) / 256;
   x_data [20] = c;
   c  = a_value % 256; 
   a_value = (a_value - c) / 256;
   x_data [21] = c;
   c  = a_value % 256; 
   a_value = (a_value - c) / 256;
   x_data [22] = c;
   c  = a_value % 256; 
   a_value = (a_value - c) / 256;
   x_data [23] = c;
   /*---(write data)---------------------*/
   for (i = 0; i < 24; ++i) {
      fputc (x_data [i], f);
   }
   /*---(flush buffer)-------------------*/
   fflush (f);
   /*---(close file)---------------------*/
   rc = TOUCH__close (&f);
   DEBUG_TOUCH  yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_TOUCH  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TOUCH_force_tablet      (int a_left, int a_topp, int a_wide, int a_tall)
{
   my.t_left   = a_left;
   my.t_topp   = a_topp;
   my.t_wide   = a_wide;
   my.t_tall   = a_tall;
   return 0;
}

char
TOUCH_force_screen      (int a_left, int a_topp, int a_wide, int a_tall)
{
   char        rce         =  -10;
   --rce;  if (my.t_wide == -6666)  return rce;
   my.s_left   = a_left;
   my.s_topp   = a_topp;
   my.s_wide   = a_wide;
   my.s_tall   = a_tall;
   my.s_xratio = (float) my.s_wide / (float) my.t_wide;
   my.s_yratio = (float) my.s_tall / (float) my.t_tall;
   return 0;
}

char
TOUCH_force_window      (int a_left, int a_topp, int a_wide, int a_tall, char a_align)
{
   char        rce         =  -10;
   --rce;  if (my.s_wide == -6666)  return rce;
   my.w_left   = a_left;
   my.w_topp   = a_topp;
   my.w_wide   = a_wide;
   my.w_tall   = a_tall;
   my.m_align  = a_align;
   return 0;
}

/*> char                                                                              <* 
 *> TOUCH_set_window        (int a_x, int a_y, int *r_x, int *r_x)                    <* 
 *> {                                                                                 <* 
 *> }                                                                                 <*/

char*
TOUCH__unit             (char *a_question, int a_num)
{
   char        t           [LEN_DESC]  = "    ·x      ·y      ·w      ·t";
   char        s           [LEN_DESC]  = "    ·x      ·y";
   char        r           [LEN_DESC]  = "       ··         ··";
   if        (strcmp (a_question, "tablet")         == 0) {
      if (my.t_wide != -6666 && my.t_tall != -6666)  sprintf (t, "%5dx  %5dy  %5dw  %5dt", my.t_left, my.t_topp, my.t_wide, my.t_tall);
      if (my.t_x    != -6666 && my.t_y    != -6666)  sprintf (s, "%5dx  %5dy", my.t_x, my.t_y);
      snprintf(unit_answer, LEN_RECD, "TOUCH tablet     : %s    %s     ·  %s", t, r, s);
   } else if (strcmp (a_question, "screen")         == 0) {
      if (my.s_wide != -6666 && my.s_tall != -6666)  sprintf (t, "%5dx  %5dy  %5dw  %5dt", my.s_left, my.s_topp, my.s_wide, my.s_tall);
      if (my.s_wide != -6666 && my.s_tall != -6666)  sprintf (r, "%8.6fx  %8.6fy", my.s_xratio, my.s_yratio);
      if (my.s_x    != -6666 && my.s_y    != -6666)  sprintf (s, "%5dx  %5dy", my.s_x, my.s_y);
      snprintf(unit_answer, LEN_RECD, "TOUCH screen     : %s    %s     ·  %s", t, r, s);
   } else if (strcmp (a_question, "window")         == 0) {
      if (my.w_wide != -6666 && my.w_tall != -6666)  sprintf (t, "%5dx  %5dy  %5dw  %5dt", my.w_left, my.w_topp, my.w_wide, my.w_tall);
      if (my.m_x    != -6666 && my.m_y    != -6666)  sprintf (s, "%5dx  %5dy", my.m_x, my.m_y);
      snprintf(unit_answer, LEN_RECD, "TOUCH window     : %s    %s    %2d  %s", t, r, my.m_align, s);
   }
   return unit_answer;
}



/*============================[[ end-of-code ]]===============================*/
