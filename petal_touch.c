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
   {     0,     0, "all     ", 0    },  
   /*---(abs)----------------------------*/
   {     3,  0x00, "abs_x   ", 0    },  
   {     3,  0x01, "abs_y   ", 0    },  
   {     3,  0x04, "button  ", 0    },  
   {     3,  0x18, "hardnes ", 0    },  
   {     3,  0x1a, "tilt_x  ", 0    },  
   {     3,  0x1b, "tilt_y  ", 0    },  
   {     3,  0x2f, "slot    ", 0    },  
   {     3,  0x35, "eps_X   ", 0    },  
   {     3,  0x36, "eps_Y   ", 0    },  
   {     3,  0x39, "id      ", 0    },  
   /*---(end)----------------------------*/
   {    -1,    -1, ""        , 0    },  
   /*---(done)---------------------------*/
};

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
TOUCH_normal       (void)
{
   fcntl  (s_fileno, F_SETFL, s_flags);
   return 0;
}

char         /*--> open touch device event file ----------[ leaf   [ ------ ]-*/
TOUCH_check        (void)
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
      TOUCH_normal ();
      DEBUG_TOUCH  yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   /*---(put the char back)--------------*/
   rc = ungetc (x_ch, my.f_event);
   --rce;  if (rc != x_ch) {
      DEBUG_TOUCH  yLOG_snote   ("could not unget");
      TOUCH_normal ();
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
   char        t           [LEN_LABEL] = "";
   char        x_track     =  '·';
   float       x           = 0.0;
   float       y           = 0.0;
   /*---(header)-------------------------*/
   DEBUG_TOUCH  yLOG_enter   (__FUNCTION__);
   /*---(check)--------------------------*/
   rc = TOUCH_check  ();
   --rce;  if (rc < 0) {
      DEBUG_TOUCH  yLOG_exit    (__FUNCTION__);
      return rce;
   }
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
   rc = TOUCH__single (my.f_event, &ev_type, &ev_code, &ev_value, &x_track, output);
   /*> while (1) {                                                                                        <* 
    *>    /+---(get and format character)----+/                                                           <* 
    *>    ++x_count;                                                                                      <* 
    *>    ch = fgetc (my.file_event);                                                                     <* 
    *>    x_ch = ch;                                                                                      <* 
    *>    sprintf (next  , "%02x ", x_ch);                                                                <* 
    *>    strcat  (output, next);                                                                         <* 
    *>    /+---(check for columns breaks)----+/                                                           <* 
    *>    if (x_count ==  8)   { strcat (output, "  ");        continue; }                                <* 
    *>    if (x_count == 16)   { strcat (output, "  ");        continue; }                                <* 
    *>    /+---(filter certain columns)------+/                                                           <* 
    *>    if (x_count <  17)                                   continue;                                  <* 
    *>    /+---(event types)-----------------+/                                                           <* 
    *>    if (x_count == 17)   { ev_type   = x_ch;             continue; }                                <* 
    *>    if (x_count == 18) {                                                                            <* 
    *>       ev_type += x_ch * 256;                                                                       <* 
    *>       TOUCH__event_type (ev_type, &x_track, t);                                                    <* 
    *>       strcat (output, t);                                                                          <* 
    *>       continue;                                                                                    <* 
    *>    }                                                                                               <* 
    *>    /+---(event codes)-----------------+/                                                           <* 
    *>    if (x_count == 19)   { ev_code   = x_ch;             continue; }                                <* 
    *>    if (x_count == 20) {                                                                            <* 
    *>       ev_code += x_ch * 256;                                                                       <* 
    *>       TOUCH__event_code (ev_type, ev_code, &x_track, t);                                           <* 
    *>       strcat (output, t);                                                                          <* 
    *>       continue;                                                                                    <* 
    *>    }                                                                                               <* 
    *>    /+---(event value)-----------------+/                                                           <* 
    *>    if (x_count == 21)   { x_button = ev_value  = x_ch;      continue; }                            <* 
    *>    if (x_count == 22)   { ev_value += x_ch * 256;           continue; }                            <* 
    *>    if (x_count == 23)   { ev_value += x_ch * (256 * 256);   continue; }                            <* 
    *>    /+---(last value)------------------+/                                                           <* 
    *>    if (x_count == 24) {                                                                            <* 
    *>       /+---(format value)-------------+/                                                           <* 
    *>       ev_value += x_ch * (256 * 256 * 256);                                                        <* 
    *>       if (ev_type == 0x04 && ev_code == 0x04)  sprintf (next, "%10d  %02x", ev_value, x_button);   <* 
    *>       else                                     sprintf (next, "%10d", ev_value);                   <* 
    *>       /+---(print final line)---------+/                                                           <* 
    *>       strcat  (output, next);                                                                      <* 
    *>       if (my.ev_major == 0x04 && (ev_type == 0x00 || ev_type == 0x01 || ev_type == 0x04)) {        <* 
    *>          RPTG_EVENTS  printf ("%s\n", output);                                                     <* 
    *>          ++s_rptg;                                                                                 <* 
    *>       }                                                                                            <* 
    *>       else if (my.ev_major == ev_type && (my.ev_minor == 0xff || my.ev_minor == ev_code)) {        <* 
    *>          RPTG_EVENTS  printf ("%s\n", output);                                                     <* 
    *>          ++s_rptg;                                                                                 <* 
    *>       }                                                                                            <* 
    *>       else if (my.ev_major == 0xff) {                                                              <* 
    *>          RPTG_EVENTS  printf ("%s\n", output);                                                     <* 
    *>          ++s_rptg;                                                                                 <* 
    *>       }                                                                                            <* 
    *>       /+---(reset values)-------------+/                                                           <* 
    *>       strcpy (output, "");                                                                         <* 
    *>       x_count = 0;                                                                                 <* 
    *>    }                                                                                               <* 
    *>    /+---(finger touch)----------------+/                                                           <* 
    *>    if (ev_type == 3 && ev_code == 0x39 && ev_value >= 0)  {                                        <* 
    *>       stroke.channel = ev_value;                                                                   <* 
    *>       stroke.beg     = timestamp ();                                                               <* 
    *>       ndot = 0;                                                                                    <* 
    *>    }                                                                                               <* 
    *>    /+---(finger lift)-----------------+/                                                           <* 
    *>    if (ev_type == 3 && ev_code == 0x39 && ev_value <  0)  {                                        <* 
    *>       stroke.end   = timestamp ();                                                                 <* 
    *>       stroke.diff  = stroke.end - stroke.beg;                                                      <* 
    *>       rc = STROKE_end (s_new_x, s_new_y, s_new_r);                                                 <* 
    *>    }                                                                                               <* 
    *>    /+---(x-value)---------------------+/                                                           <* 
    *>    if (ev_type == 3 && ev_code == 0x35)  {                                                         <* 
    *>       x     = ((float) ev_value / 1800.0);                                                         <* 
    *>       s_new_x = (1366.0 * (1 - x));                                                                <* 
    *>       s_new_y = 0;                                                                                 <* 
    *>    }                                                                                               <* 
    *>    /+---(y-value)---------------------+/                                                           <* 
    *>    if (ev_type == 3 && ev_code == 0x36)  {                                                         <* 
    *>       y     = ((float) ev_value / 1800.0);                                                         <* 
    *>       s_new_y = (768.0 * y);                                                                       <* 
    *>       s_new_r = sqrt((s_new_x * s_new_x) + (s_new_y * s_new_y));                                   <* 
    *>       if (ndot == 0) rc = STROKE_begin (s_new_x, s_new_y, s_new_r);                                <* 
    *>       else           rc = stroke_next  (s_new_x, s_new_y, s_new_r);                                <* 
    *>    }                                                                                               <* 
    *>    /+---(done)------------------------+/                                                           <* 
    *>    break;                                                                                          <* 
    *> }                                                                                                  <*/

   if (my.ev_major == 0x04 && (ev_type == 0x00 || ev_type == 0x01 || ev_type == 0x04)) {
      RPTG_EVENTS  printf ("%s\n", output);
      ++s_rptg;
   }
   else if (my.ev_major == ev_type && (my.ev_minor == 0xff || my.ev_minor == ev_code)) {
      RPTG_EVENTS  printf ("%s\n", output);
      ++s_rptg;
   }
   else if (my.ev_major == 0xff) {
      RPTG_EVENTS  printf ("%s\n", output);
      ++s_rptg;
   }

   /*---(finger touch)----------------*/
   if (ev_type == 3 && ev_code == 0x39 && ev_value >= 0)  {
      stroke.channel = ev_value;
      stroke.beg     = timestamp ();
      ndot = 0;
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
      if (ndot == 0) rc = STROKE_begin (s_new_x, s_new_y, s_new_r);
      else           rc = stroke_next  (s_new_x, s_new_y, s_new_r);
   }

   TOUCH_normal ();
   /*---(complete)-------------------------*/
   return rc;
}

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

/*============================[[ end-of-code ]]===============================*/
