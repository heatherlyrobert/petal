/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



/*---(GLX Globals)---------------------------------*/
/*> XWindowAttributes      gwa;                                                       <*/



FILE   *f = NULL;


/*============================--------------------============================*/
/*===----                         layout tables                        ----===*/
/*============================--------------------============================*/

char g_letters[40] = {
   't' , 'm' , '[' , 'c' , '\"',   /* N    */
   'n' , 'f' , '_' , 'r' , 'x' ,   /* NE   */
   '>' , 'u' , '.' , 'p' , ',' ,   /* E    */
   'i' , 'l' , 'q' , 'd' , 'b' ,   /* SE   */
   'e' , 'h' , '\'', 's' , ']' ,   /* S    */
   'o' , 'g' , 'z' , 'w' , ')' ,   /* SW   */
   '<' , 'j' , ';' , 'k' , ':' ,   /* W    */
   'a' , 'y' , '(' , 'v' , '-' ,   /* NW   */
};
char g_upper[40] = {
   'T' , 'M' , '[' , 'C' , '~' ,   /* N    */
   'N' , 'F' , '_' , 'R' , 'X' ,   /* NE   */
   '>' , 'U' , '!' , 'P' , '?' ,   /* E    */
   'I' , 'L' , 'Q' , 'D' , 'B' ,   /* SE   */
   'E' , 'H' , '`' , 'S' , ']' ,   /* S    */
   'O' , 'G' , 'Z' , 'W' , ')' ,   /* SW   */
   '<' , 'J' , ';' , 'K' , ':' ,   /* W */
   'A' , 'Y' , '(' , 'V' , '-' ,   /* NW   */
};
int  g_akeysyms[40] = {
   XK_t         , XK_m           , XK_bracketleft, XK_c       , XK_quotedbl    ,
   XK_n         , XK_f           , XK_underscore , XK_r       , XK_x           ,
   XK_space     , XK_u           , XK_period     , XK_p       , XK_comma       ,
   XK_i         , XK_l           , XK_q          , XK_d       , XK_b           ,
   XK_e         , XK_h           , XK_apostrophe , XK_s       , XK_bracketright,
   XK_o         , XK_g           , XK_z          , XK_w       , XK_parenright  ,
   XK_BackSpace , XK_j           , XK_semicolon  , XK_k       , XK_colon       ,
   XK_a         , XK_y           , XK_parenleft  , XK_v       , XK_minus       ,
};
char g_punct[40] = {
   '0' , '|' , '[' , '2' , '\"',   /* N   % ^ | @ $ _ & # : \ */
   '=' , '3' , '_' , '4' , '$' ,   /* NE   |{}[]  & _<>$   */
   '>' , '5' , '.' , '6' , ',' ,   /* E   % ;/-0 :\ 1()= ^ */
   '+' , '7' , '@' , '8' , '^' ,   /* SE  @ 8642 +* 3579   */
   '1' , '9' , '\'', '#' , ']' ,   /* S    */
   '*' , '>' , '%' , '<' , ')' ,   /* SW   */
   '<' , '}' , ';' , '{' , ':' ,   /* W    */
   '/' , '\\', '(' , '&' , '-' ,   /* NW   */
};
int  g_akeysyms_punct[40] = {
   XK_0         , XK_bar         , XK_bracketleft, XK_2           , XK_quotedbl    ,
   XK_equal     , XK_3           , XK_underscore , XK_4           , XK_dollar      ,
   XK_space     , XK_5           , XK_period     , XK_6           , XK_comma       ,
   XK_plus      , XK_7           , XK_at         , XK_8           , XK_asciicircum ,
   XK_1         , XK_9           , XK_apostrophe , XK_numbersign  , XK_bracketright,
   XK_asterisk  , XK_greater     , XK_percent    , XK_less        , XK_parenright  ,
   XK_BackSpace , XK_braceright  , XK_semicolon  , XK_braceleft   , XK_colon       ,
   XK_slash     , XK_backslash   , XK_parenleft  , XK_ampersand   , XK_minus       ,
};
/*> int  g_akeysyms_punct[40] = {                                                         <* 
 *>    XK_minus     , XK_Mode_switch , XK_asciicircum, XK_Shift_L     , XK_underscore ,   <* 
 *>    XK_equal     , XK_plus        , XK_percent    , XK_asterisk    , XK_5          ,   <* 
 *>    XK_space     , XK_1           , XK_3          , XK_braceright  , XK_9          ,   <* 
 *>    XK_parenright, XK_bracketright, XK_7          , XK_greater     , XK_ampersand  ,   <* 
 *>    XK_minus     , 1000000        , XK_numbersign , XK_Return      , XK_bar        ,   <* 
 *>    XK_parenleft , XK_less        , XK_dollar     , XK_bracketleft , XK_6          ,   <* 
 *>    XK_BackSpace , XK_braceleft   , XK_8          , XK_0           , XK_2          ,   <* 
 *>    XK_slash     , XK_backslash   , XK_4          , XK_colon       , XK_at         ,   <* 
 *> };                                                                                    <*/

char g_special[10]          = { 'S', 'C', 'T', 'H', 'N', 'A', 'E', 'M', };
int  g_akeysyms_special[10] = {
   XK_Shift_L  , XK_Control_L, XK_Tab      , 1000000       ,
   XK_Return   , XK_Alt_L    , XK_Escape   , XK_Mode_switch,
};

char s_next[40];


int  key_index[30] = {      /* to allow lookup on hublin shortcuts            */
   XK_a, XK_b, XK_c, XK_d, XK_e, XK_f, XK_g, XK_h, XK_i, XK_j, XK_k, XK_l, XK_m,
   XK_n, XK_o, XK_p, XK_q, XK_r, XK_s, XK_t, XK_u, XK_v, XK_w, XK_x, XK_y, XK_z
};

/*============================--------------------============================*/
/*===----                       states and locks                       ----===*/
/*============================--------------------============================*/

enum tSTATES eSTATES;

const float  DEG2RAD = 3.1415927 / 180.0;


/*============================--------------------============================*/
/*===----                            globals                           ----===*/
/*============================--------------------============================*/


int       curr_x;
int       curr_y;
int       curr_r;
int       new_x;
int       new_y;
int       new_r;
int       init_x       = 675;
int       init_y       = 390;






/*============================--------------------============================*/
/*===----                          touchscreen                         ----===*/
/*============================--------------------============================*/
static void      o___TOUCH___________________o (void) {;}

llong
timestamp          (void)             /* PURPOSE : timestamp in milliseconds      */
{
   /* second
    * millisecond  ms  0.001 sec
    * microsecond  us  0.000001 sec
    * nanosecond   ns  0.000000001 sec
    * picosecond   ps  0.000000000001 sec
    */
   llong            tint = 0;
   struct timespec  tv;
   clock_gettime (CLOCK_MONOTONIC, &tv);
   tint += (llong) tv.tv_sec  * 1000;
   tint += (llong) tv.tv_nsec / 1000000;
   return tint;
}

char
touch_open         (void)
{
   /*---(open)---------------------------*/
   f = fopen ("/dev/input/event12", "r");
   if (f == NULL) {
      printf ("BLOODY CAN'T GET EVENT FILE OPEN\n");
      exit (-2);
   }
   /*---(complete)-----------------------*/
   return  0;
}

char             /* [------] read input event -------------------------------*/
touch_read         (void)
{
   /*> printf ("touch_read ()\n");                                                    <*/
   /*---(locals)-----------*-------------*/
   int         rc          = 0;
   int         filenum     = 0;
   int         flags       = 0;
   char        ch          = 0;
   uchar       x_ch        = 0;
   int         count       = 0;
   char   next   [100];
   char   output [200];
   char   ev_type  = 0;
   char   ev_code  = 0;
   int    ev_value = 0;
   float       x           = 0.0;
   float       y           = 0.0;
   /*---(set stdin to non-blocking)------*/
   filenum     = fileno (f);
   flags       = fcntl  (filenum, F_GETFL, 0);
   fcntl (filenum, F_SETFL, flags | O_NONBLOCK);
   /*---(test stdin for input)-------------*/
   ch = fgetc (f);
   if (ch == -1) {
      /*> printf ("   touch_read () nothing\n");                                      <*/
      fcntl  (filenum, F_SETFL, flags);
      return -1;
   }
   /*---(continue with input)--------------*/
   x_ch = ch;
   strcpy  (output, "");
   ++count;
   while (1) {
      /*> printf ("   touch_read ()  loop beginning\n");                              <*/
      sprintf (next  , "%02x ", x_ch);
      strcat  (output, next);
      if (count % 16 == 0)  strcat (output, "   ");
      if (count % 17 == 0)  ev_type = x_ch;
      if (count % 18 == 0) {
         ev_type += x_ch * 256;
         switch (ev_type) {
         case 0 : strcat (output, "SYN");           break;
         case 1 : strcat (output, "KEY");           break;
         case 2 : strcat (output, "REL");           break;
         case 3 : strcat (output, "ABS");           break;
         }
         strcat (output, "   ");
      }
      if (count % 19 == 0)  ev_code = x_ch;
      if (count % 20 == 0) {
         ev_code += x_ch * 256;
         if (ev_type == 3) {
            switch (ev_code) {
            case 0x00 : strcat (output, "ABS_X ");           break;
            case 0x01 : strcat (output, "ABS_Y ");           break;
            case 0x2f : strcat (output, "SLOT  ");           break;
            case 0x35 : strcat (output, "EPS_X ");           break;
            case 0x36 : strcat (output, "EPS_Y ");           break;
            case 0x39 : strcat (output, "ID    ");           break;
            default   : strcat (output, "---   ");           break;
            }
         } else {
            strcat (output, "      ");
         }
         strcat (output, "   ");
      }
      if (count % 21 == 0)  ev_value = x_ch;
      if (count > 21) {
         ev_value += x_ch * 256;
      }
      if (count % 24 == 0) {
         sprintf (next, " %10d", ev_value);
         strcat  (output, next);
         printf ("%s\n", output);
         strcpy (output, "");
         count = 0;
         /*> if (ev_type == 3 && ev_code == 0x2f)  {                                                <* 
          *>    slot = ev_value;                                                                    <* 
          *>    /+> if (slot > 9)  printf ("BBBBBBLLLLLLLLAAAAAAAAAAAMMMMMMMMMOOOOOOOO\n");   <+/   <* 
          *> }                                                                                      <*/
         if (ev_type == 3 && ev_code == 0x39)  {
            if (ev_value == 196095 || ev_value == -1) {
               end   = timestamp ();
               diff  = end - beg;
               rc = stroke_end (new_x, new_y, new_r);
            }
            else {
               on    = ev_value;
               beg   = timestamp ();
               ndots = 0;
            }
         }
         if (ev_type == 3 && ev_code == 0x35)  {
            x     = ((float) ev_value / 1800.0);
            new_x = (1366.0 * (1 - x));
            new_y = 0;
         }
         if (ev_type == 3 && ev_code == 0x36)  {
            y     = ((float) ev_value / 1800.0);
            new_y = (768.0 * y);
            new_r = sqrt((new_x * new_x) + (new_y * new_y));
            if (ndots == 0) rc = stroke_begin (new_x, new_y, new_r);
            else            rc = stroke_next  (new_x, new_y, new_r);
         }
         break;
      }
      ch = fgetc (f);
      /*> if (ch == -1) return -1;                                                    <*/
      x_ch = ch;
      ++count;
   }
   fcntl  (filenum, F_SETFL, flags);
   /*> printf ("%s\n", output);                                                       <*/
   /*---(complete)-------------------------*/
   return rc;
}

char
touch_close        (void)
{
   int         rc           = 0;
   /*---(open)---------------------------*/
   rc = fclose (f);
   if (rc < 0) {
      printf ("BLOODY CAN'T CLOSE EVENT FILE\n");
      exit (-2);
   }
   /*---(complete)-----------------------*/
   return  0;
}


/*====================------------------------------------====================*/
/*===----                             fonts                            ----===*/
/*====================------------------------------------====================*/
static void      o___FONTS___________________o (void) {;}

char
font_load(void)
{
   my.txf_bg = yFONT_load (my.face_bg);
   if (my.txf_bg < 0) {
      fprintf(stderr, "Problem loading %s\n", my.face_bg);
      exit(1);
   }
   my.txf_sm = yFONT_load (my.face_sm);
   if (my.txf_sm < 0) {
      fprintf(stderr, "Problem loading %s\n", my.face_sm);
      exit(1);
   }
   return 0;
}

char
font_free (void)
{
   yFONT_free (my.txf_bg);
   yFONT_free (my.txf_sm);
   return 0;
}


/*============================--------------------============================*/
/*===----                      simple dot tracing                      ----===*/
/*============================--------------------============================*/
static void      o___DOTS____________________o (void) {;}
char garbage = 0;

char
dot_beg (int a_x, int a_y)
{
   DEBUG_USER    printf("RAW DOT ENTRY (begin)\n");
   ndots   = 0;
   /*> init_x  = a_x + 1;                                                             <* 
    *> init_y  = a_y + 1;                                                             <*/
   curr_x  = 0;
   curr_y  = 0;
   curr_r  = 0;
   DEBUG_USER    printf("   check %4d,  %4dx, %4dy\n", ndots, init_x, init_y);
   garbage = 0;
   char rc = dot_add (a_x, a_y);
   return rc;
}

char
dot_add (int a_x, int a_y)
{
   int       x  = a_x - init_x;
   int       y  = a_y - init_y;
   DEBUG_USER    printf("   check %4d,  %4dx, %4dy : ", ndots, a_x, a_y);
   if (garbage == 1)  {
      DEBUG_USER    printf("REJECTED, garbage on\n");
      return -1;
   }
   if (a_x == curr_x && a_y == curr_y) {
      DEBUG_USER    printf("REJECTED, duplicate\n");
      return -2;
   }
   if (ndots >= MAXDOTS) {
      DEBUG_USER    printf("REJECTED, too many dots (%d >= %d)\n", ndots, MAXDOTS);
      return -3;
   }
   x  -= curr_x;
   y  -= curr_y;
   float     r  = sqrt((x * x) + (y * y));
   /*> if (r < 3)            return -2;                                               <*/
   /*> if (ndots > 0 && r <  3.0) {                                                          <* 
    *>    DEBUG_USER    printf("REJECTED, garbage as too little moved (%4.1f > 15.0)\n", r);   <* 
    *>    return -4;                                                                         <* 
    *> }                                                                                     <*/
   if (r > 30.0) {
      DEBUG_USER    printf("REJECTED, garbage as too far moved (%4.1f > 30.0)\n", r);
      garbage = 1;
      return -4;
   }
   curr_x = dots[ndots].x  = a_x - init_x;
   curr_y = dots[ndots].y  = a_y - init_y;
   curr_r = sqrt((curr_x * curr_x) + (curr_y * curr_y));
   DEBUG_USER    printf(" %4dx, %4dy : ", curr_x, curr_y);
   DEBUG_USER    printf("accepted (%4.1f)\n", r);
   ++ndots;
   return 0;
}

char
dot_end (int a_x, int a_y)
{
   /*> if (a_x == curr_x && a_y == curr_y) return -1;                                 <*/
   /*> curr_x = 1000;                                                                 <* 
    *> curr_y = 1000;                                                                 <*/
   char rc = dot_add (a_x, a_y);
   DEBUG_USER    printf("   total dots = %d\n", ndots);
   DEBUG_USER    printf("RAW DOT ENTRY (end)\n");
   return rc;
}



/*============================--------------------============================*/
/*===----                        stroke handling                       ----===*/
/*============================--------------------============================*/
static void      o___STROKES_________________o (void) {;}

int last_ring  = -1;
int last_petal = -1;

char
stroke_begin (int a_x, int a_y, int a_r)
{
   DEBUG_INPT   printf("\n");
   DEBUG_INPT   printf("BEGIN STROKE : stroke_begin(%4dx, %4dy, %4dw)...\n", a_x, a_y, a_r);
   char rc = dot_beg (a_x, a_y);
   if (rc < 0) return -1;
   /*---(reset flags)---------------------------*/
   letter_init();
   /*---(get the focus window)----------------------------*/
   FOCU = yXINIT_focus();
   DEBUG_INPT   printf("   - focus window = %ld\n", FOCU);
   /*---(determine direction)-------------------*/
   if (curr_r <= shape.r_center)  stroke.outward = TRUE;
   else                       stroke.outward = FALSE;
   DEBUG_INPT   printf("   - stroke.outward   = %s\n", (stroke.outward) ? "TRUE" : "FALSE");
   /*---(for strokes)---------------------------*/
   strncpy(stroke_letter, "", 20);
   int i;
   for (i = 0; i < MAXWORD; ++i) stroke_keysym[i] = stroke_index[i] = 0;
   for (i = 0; i < 40; ++i) s_next[i] = 0;
   stroke_count = 0;
   DRAW_main();
   /*---(complete)------------------------------*/
   return 0;
}

char
stroke_next (int a_x, int a_y, int a_r)
{
   /*> DEBUG_INPT   printf("   - stroke_continue (%4dx, %4dy, %4dw)...\n", a_x, a_y, a_r);   <*/
   char rc = dot_add (a_x, a_y);
   if (rc < 0) return -1;
   /*---(check for wave offs)-------------------*/
   if (stroke.done     == 1) return 0;
   if (stroke.fail   == 1) return 0;
   /*---(set up variables)----------------------*/
   int          x, y;
   int          r, d;
   float        rads;
   int          x_ring  = -1;
   int          petal = -1;
   float        pi    = 3.1415927;
   /*---(center the coordinates)----------------*/
   x  =  curr_x;
   y  = -curr_x;
   r  =  curr_r;
   /*---(convert to polar)----------------------*/
   rads  = atan2f(-curr_y, curr_x);
   d     = (int) ((rads /  (2 * pi)) * 360 + 90);
   if (d < 0) d += 360;
   /*---(identify the ring)---------------------*/
   if      (r <=  shape.r_center) x_ring  = 0;
   else if (r <=  shape.r_ring)   x_ring  = 9;
   else if (r <=  shape.r_inner)  x_ring  = 1;
   else if (r <=  shape.r_buffer) x_ring  = 8;
   else if (r <=  shape.r_outer)  x_ring  = 2;
   else                          x_ring  = 3;
   if (x_ring == 4 || x_ring == 8 || x_ring == 9) return 0;
   /*---(identify the petal)--------------------*/
   switch (x_ring) {
   case 0  : /* center           */
      petal  = 0;
      break;
   case  1  :
      /* eight (8) petals shifted sightly        */
      petal = (int) ((d + 22.5) / 45);
      if (petal >  7)  petal -=  8;
      if (petal <  0)  petal +=  8;
      break;
   case  2  :
      /* eight (8) petals divided by spaces      */
      petal = (d + 11.0) / 22.5;
      if (petal > 15)  petal -= 16;
      if (petal <  0)  petal += 16;
      if ((petal % 2) == 0) {
         DEBUG_INPT    printf("   - ring=%2d outside touch spot\n", x_ring);
         return 0;  /* throw out evens  */
      }
      petal = (petal - 1) / 2;
      break;
   case  3  : /* edge             */
      /* eight (8) petals shifted sightly        */
      petal = (d + 11.0) / 22.5;
      if (petal > 15)  petal -= 16;
      if (petal <  0)  petal += 16;
      if ((petal % 2) == 1) {
         DEBUG_INPT    printf("   - ring=%2d outside touch spot\n", x_ring);
         return 0;  /* throw out evens  */
      }
      petal /= 2;
      break;
   case 4  :
      /* four (4) leaves evenly placed           */
      petal = d / 90.0;
      if (petal >  3)  petal -=  4;
      if (petal <  0)  petal +=  4;
      break;
   default :
      petal = 0;
      break;
   }
   /*---(check for buffer zones)----------------*/
   DEBUG_INPT    printf("   - ring=%2d, petal=%2d", x_ring, petal);
   if (x_ring > 7)  {
      DEBUG_INPT    printf("   buffer zone                   [ ignored ]\n");
      return -1;
   }
   /*---(cull duplicates)-----------------------*/
   if (x_ring == last_ring && petal == last_petal) {
      DEBUG_INPT    printf("   redundant                     [ ignored ]\n");
      return -1;
   }
   last_ring   = x_ring;
   last_petal  = petal;
   /*---(check for restart)---------------------*/
   if (x_ring == 0 && stroke.done == 0 && stroke.max >= 0) {
      DEBUG_INPT   printf("\n   - RESET in zth ring...\n");
      letter_interpret();
      letter_init();
      return 0;
   }
   /*---(cull redundant)------------------------*/
   if (x_ring == 0 && stroke.zth >= 0) {
      DEBUG_INPT    printf("   move in center only           [ ignored ]\n");
      return -1;
   }
   if (x_ring == 1 && stroke.max >= 1 &&  stroke.outward) {
      DEBUG_INPT    printf("   ring one (1) already locked   [ ignored ]\n");
      return -1;
   }
   if (x_ring == 1 && stroke.fst >= 0 && !stroke.outward)  return -1;
   if (x_ring == 2 && stroke.max >= 2 &&  stroke.outward) {
      DEBUG_INPT    printf("   ring two (2) already locked   [ ignored ]\n");
      return -1;
   }
   if (x_ring == 2 && stroke.snd >= 0 && !stroke.outward)  return -1;
   if (x_ring == 3 && stroke.trd >= 0) {
      DEBUG_INPT    printf("   ring three (3) already locked [ ignored ]\n");
      return -1;
   }
   DEBUG_INPT    printf("\n");
   /*---(handle a hublin stroke)----------------*/
   if (!stroke.outward) {
      if (stroke.max < 0) {
         states[HUBLIN] = 1000000;
         stroke.max      = x_ring;
      }
   }
   /*---(update)--------------------------------*/
   letter_update(x_ring, petal);
   /*---(update globals)------------------------*/
   stroke.ring   = x_ring;
   stroke.petal  = petal;
   /*---(complete)------------------------------*/
   return 0;
}

char
stroke_end (int a_x, int a_y, int a_r)
{
   char rc = dot_end (a_x, a_y);
   char x_rc = 0;                               /* local return code          */
   char x_before[MAXWORD] = "";
   /*---(process immediately)-------------------*/
   if (stroke.done == 0)  letter_interpret();
   /*---(process the whole string)--------------*/
   DEBUG_INPT   printf("END STROKE   : stroke_end(%4dx, %4dy, %4dw)...\n", a_x, a_y, a_r);
   /*---(handle hublin)-------------------------*/
   DEBUG_RECOG  printf("BEGIN PROCESS\n");
   strncpy(x_before,     stroke_letter, MAXWORD);
   strncpy(stroke.feedback, stroke_letter, MAXWORD);
   if (states[HUBLIN] || states[MYHUBLIN]) {
      DEBUG_RECOG  printf("inside hublin area, strlen = %d, HUB=%d, MYHUB=%d\n", (int) strlen(stroke_letter), states[HUBLIN], states[MYHUBLIN]);
      x_rc = -1;
      if      (states[MYHUBLIN] && strlen(stroke_letter) == 1) x_rc = hublin_mysingle (stroke.owner, stroke_letter, x_before);
      else if (states[MYHUBLIN] && strlen(stroke_letter) == 2) x_rc = hublin_mydouble (stroke.owner, stroke_letter, x_before);
      else if (states[HUBLIN]   && strlen(stroke_letter) == 1) x_rc = hublin_single   (stroke_letter, x_before);
      else if (states[HUBLIN]   && strlen(stroke_letter) == 2) x_rc = hublin_double   (stroke_letter, x_before);
      else if (states[HUBLIN]   && strlen(stroke_letter) == 3) x_rc = hublin_triple   (stroke_letter, x_before);
      /*> x_rc = hublin_find(stroke_letter, stroke_keysym);                           <*/
      if (x_rc == 0) {
         int  i, j;
         for (i = 0; i < MAXWORD; ++i) {
            if (stroke_letter[i] == '\0') break;
            j = (stroke_letter[i] - 'a');
            switch (stroke_letter[i]) {
            case ' '  : stroke_keysym[i] = XK_space;          break;
            case '.'  : stroke_keysym[i] = XK_period;         break;
            case '\n' : stroke_keysym[i] = XK_Return;         break;
            case ','  : stroke_keysym[i] = XK_comma;          break;
            default   : stroke_keysym[i] = key_index[j];      break;
            }
         }
         snprintf(stroke.feedback, MAXWORD, "%s (%s)", x_before, stroke_letter);
      }
   }
   DEBUG_RECOG  printf("END PROCESS\n\n");
   /*---(handle sendkeys)-----------------------*/
   x_rc = key_send_all(stroke_letter, stroke_keysym);
   /*---(complete)------------------------------*/
   int i = 0;
   for (i = 0; i < 40; ++i) s_next[i] = 0;
   DRAW_main();
   stroke_count = 0;
   return 0;
}




/*============================--------------------============================*/
/*===----                        mouse handling                        ----===*/
/*============================--------------------============================*/
static void      o___MOUSE___________________o (void) {;}

void
mouse_init (void)            /* initialize mouse usage before program starts  */
{
   DEBUG_PROG    printf("mouse_init()\n");
   stroke_count  = 0;
   strncpy(stroke_letter, "", 20);
   letter_init();
   DEBUG_PROG   printf("   - done\n\n");
   return;
}

char
event_arrows(int a_x, int a_y)
{
   if (a_y > 0) {
      if (a_x < 0) key_send(XK_Up);
      else         key_send(XK_Down);
   } else {
      if (a_x < 0) key_send(XK_Left);
      else         key_send(XK_Right);
   }
   /*---(complete)------------------------------*/
   yXINIT_focus();
   DRAW_main();
   return 0;
}

char
event_navigation(int a_x)
{
   /*---(determine slot)------------------------*/
   int slot = (a_x + shape.sz_centerx) / (shape.sz_width / 7.0);
   if (slot < 0) slot = 0;
   if (slot > 6) slot = 6;
   DEBUG_INPT   printf("event_navigation(%dx) so slot %d\n", a_x, slot);
   /*---(act)-----------------------------------*/
   char  x_cmd[200] = "";
   switch (slot) {
   case 0 :
      DEBUG_INPT   printf("   - NAVBAR  : previous workspace\n");
      system("fluxbox-remote \"PrevWorkspace\"");
      break;
   case 1 :
      DEBUG_INPT   printf("   - NAVBAR  : previous window\n");
      system("fluxbox-remote \"PrevWindow\"");
      break;
   case 2 :
      DEBUG_INPT   printf("   - NAVBAR  : hyper key\n");
      if (states[HYPER] == 0)  states[HYPER] = Mod5Mask;
      else                     states[HYPER] = 0;
      break;
   case 3 :
      DEBUG_INPT   printf("   - NAVBAR  : help key\n");
      if (stroke.help == 0)        stroke.help   = 1;
      else                     stroke.help   = 0;
      break;
   case 4 :
      DEBUG_INPT   printf("   - NAVBAR  : super key\n");
      if (states[SUPER] == 0)  states[SUPER] = Mod4Mask;
      else                     states[SUPER] = 0;
      break;
   case 5 :
      DEBUG_INPT   printf("   - NAVBAR  : next window\n");
      system("fluxbox-remote \"NextWindow\"");
      break;
   case 6 :
      DEBUG_INPT   printf("   - NAVBAR  : next workspace\n");
      system("fluxbox-remote \"NextWorkspace\"");
      break;
   default:
      break;
   }
   /*---(complete)------------------------------*/
   yXINIT_focus();
   DRAW_main();
   return 0;
}




/*============================--------------------============================*/
/*===----                        letter handling                       ----===*/
/*============================--------------------============================*/
static void      o___LETTERS_________________o (void) {;}

char
letter_init()
{
   DEBUG_INPT    printf("   - letter_init()\n");
   /*---(reset flags)---------------------------*/
   stroke.done      = 0;
   stroke.pass      = 0;
   stroke.fail    = 0;
   stroke.backwards = 0;
   /*---(last letter)---------------------------*/
   stroke.last_max     = stroke.max;
   stroke.last_0th     = stroke.zth;
   stroke.last_1st     = stroke.fst;
   stroke.last_2nd     = stroke.snd;
   stroke.last_3rd     = stroke.trd;
   stroke.last_4th     = stroke.fth;
   /*---(current letter)------------------------*/
   stroke.outward   = TRUE;
   stroke.max      = -1;
   stroke.zth      = -1;
   stroke.fst      = -1;
   stroke.snd      = -1;
   stroke.trd      = -1;
   stroke.fth      = -1;
   strcpy(stroke.text, " ");
   /*---(saved)---------------------------------*/
   last_ring    = -1;
   last_petal   = -1;
   /*---(get next)------------------------------*/
   /*> printf("starting letter %d\n", stroke_count);                                  <*/
   int i;
   for (i = 0; i < 40; ++i) s_next[i] = 0;
   if (stroke_count == 2 && states[HUBLIN]) {
      hublin_next(g_letters, s_next, stroke_letter);
      DRAW_main();
   }
   /*---(complete)------------------------------*/
   return 0;
}

int
letter_update(int a_ring, int a_petal)
{
   DEBUG_INPT    printf("   - letter_update(%dr, %dp) with max at %d\n", a_ring, a_petal, stroke.max);
   /*---(look for backtracking)-----------------*/
   if (a_ring == 0 && stroke.max <= 0) {
      DEBUG_INPT   printf("   - ring zero noted\n");
      stroke.zth = 0;
      stroke.max = 0;
      return -1;
   }
   /*---(look for oddities)---------------------*/
   stroke.fail = 0;
   /*---(record path)---------------------------*/
   if (a_ring == 1) stroke.fst = a_petal;
   if (a_ring == 2) stroke.snd = a_petal;
   if (a_ring == 3) stroke.trd = a_petal;
   if (a_ring == 4) stroke.fth = a_petal;
   /*---(update max)----------------------------*/
   if (a_ring > stroke.max && a_ring < 8) stroke.max = a_ring;
   /*---(complete)------------------------------*/
   DEBUG_INPT   printf("   - now got a 0=%2d, 1=%2d, 2=%2d, 3=%2d, m=%2d\n", stroke.zth, stroke.fst, stroke.snd, stroke.trd, stroke.max);
   DRAW_main();
   return 0;
}

void
letter_interpret()
{
   DEBUG_INPT    printf("   - letter_interpret() ");
   char    letter = ' ';
   ulong   keysym;
   if (stroke.done   == 1) return;
   stroke.ndx  = 0;
   strcpy(stroke.text, " ");
   /*---(look for nulls)------------------------------*/
   if (stroke.max <  1) {
      DEBUG_INPT   printf("nothing so ignore\n");
      return;
   }
   /*> if (stroke.max <  1) {                                                            <* 
    *>    stroke.max =  1;                                                               <* 
    *>    stroke.zth =  0;                                                               <* 
    *>    stroke.fst =  2;                                                               <* 
    *>    stroke.snd = -1;                                                               <* 
    *>    stroke.trd = -1;                                                               <* 
    *>    stroke.fth = -1;                                                               <* 
    *> }                                                                              <*/
   if (stroke.max == 0) {
      if (states[HUBLIN] != 0) {
         return;
      } else {
         stroke.max =  3;
         stroke.zth =  0;
         stroke.fst =  7;
         stroke.snd = -1;
         stroke.trd =  7;
         stroke.fth = -1;
         /*> DEBUG_INPT   printf("max at 0 so it means repeat last letter\n");        <*/
         /*> stroke.max = stroke.last_max;                                            <* 
          *> stroke.zth = stroke.last_0th;                                            <* 
          *> stroke.fst = stroke.last_1st;                                            <* 
          *> stroke.snd = stroke.last_2nd;                                            <* 
          *> stroke.trd = stroke.last_3rd;                                            <* 
          *> stroke.fth = stroke.last_4th;                                            <*/
      }
   }
   /*---(test for rejected)---------------------------*/
   if (stroke.fail == 1) {
      DEBUG_INPT   printf("REJECT %d, %d, %d\n", stroke.fst, stroke.snd, stroke.trd);
      return;
   }
   /*---(special keys)-----------------------------*/
   if (stroke.max >= 3 && stroke.fst == stroke.trd)  {
      letter = g_special[stroke.trd];
      keysym = g_akeysyms_special[stroke.trd];
      if (keysym == 1000000) {
         if (states[HUBLIN] != 0) {
            if (locks[HUBLIN]  != 0) locks[HUBLIN] = states[HUBLIN]  = 0;
            else                     locks[HUBLIN] = states[HUBLIN]  = 1000000;
         } else {
            states[HUBLIN]  = 1000000;
         }
      } else if (states[HUBLIN] == 0) {
         key_send(keysym);
      }
      sprintf(stroke.text, "%c", letter);
      DRAW_main();
      return;
   }
   /*> if (stroke.zth < 0) {                                                             <* 
    *>    DEBUG_INPT   printf(", SET MY CUSTOM HUBLIN\n");                                 <* 
    *>    states[MYHUBLIN]  = 1000000;                                                <* 
    *>    states[HUBLIN]    = 0;                                                      <* 
    *>    return;                                                                     <* 
    *> }                                                                              <*/
   /*---(figure out index)-------------------------*/
   stroke.ndx = stroke.fst * 5;
   if (stroke.snd >= 0) {
      ++stroke.ndx;
      if ((int) (stroke.snd) == stroke.fst) stroke.ndx += 2;
   }
   if (stroke.trd >= 0) ++stroke.ndx;
   /*---(print the index audit)--------------------*/
   DEBUG_INPT   printf(" id'd %d, %d, %d so %d", stroke.fst, stroke.snd, stroke.trd, stroke.ndx);
   /*---(test for out of bounds)-------------------*/
   if (stroke.ndx < 0 || stroke.ndx > 39) {
      if (stroke.zth < 0) {
         DEBUG_INPT   printf(", SET MY CUSTOM HUBLIN\n");
         states[MYHUBLIN]  = 1000000;
         states[HUBLIN]    = 0;
         return;
      }
      stroke.fail = 1;
      DEBUG_INPT   printf(", WEIRD INDEX, REJECT\n");
      return;
   }
   letter = g_letters[stroke.ndx];
   if (states[MODE] != 0) letter = g_punct[stroke.ndx];
   /*---(test for a bad translation)------------*/
   if (letter == 0) {
      stroke.fail = 1;
      DEBUG_INPT   printf(", not assigned\n");
      return;
   }
   stroke.pass   = 1;
   keysym = g_akeysyms[stroke.ndx];
   if (states[MODE] != 0) keysym = g_akeysyms_punct[stroke.ndx];
   DEBUG_INPT   printf(", makes it a \"%c\" = %lx", letter, keysym);
   /*> uint  temp_mode = states[MODE];                                                <* 
    *> uint  temp_lock = locks [MODE];                                                <*/
   if (  letter == '#'  ||
         letter == '.'  || letter == ','  ||
         letter == '\"' || letter == '\'') {
      locks[MODE] = states[MODE] = 0;
   }
   if (  letter == ':'  || letter == ';'  ||
         letter == '('  || letter == ')'  ||
         letter == '-'  || letter == '_'  ||
         letter == '['  || letter == ']')
      states[MODE]   = 0x2000;
   if (keysym > 0 && keysym < 1000000) {
      DEBUG_INPT   printf(", so recording\n");
      if (states[MYHUBLIN]) letter = toupper(letter);
      stroke_letter[stroke_count]     = letter;
      stroke_letter[stroke_count + 1] = '\0';
      stroke_keysym[stroke_count]     = keysym;
      stroke_index [stroke_count]     = stroke.ndx;
      ++stroke_count;
      DEBUG_RECOG  printf("   - stroke adds \"%c\" so <<%s>> and %d long\n", letter, stroke_letter, stroke_count);
      sprintf(stroke.text, "%c", letter);
      DRAW_main();
   } else {
      DEBUG_INPT   printf(", NOT SENT\n");
   }
   /*> states[MODE] = temp_mode;                                                      <* 
    *> locks [MODE] = temp_lock;                                                      <*/
   return;
}




/*============================--------------------============================*/
/*===----                          key sending                         ----===*/
/*============================--------------------============================*/
static void      o___KEYS____________________o (void) {;}

Time
fake_timestamp()
{
   int              tint;
   struct timeval   tv;
   gettimeofday(&tv, NULL);
   tint = (int) tv.tv_sec * 1000;
   tint = tint / 1000 * 1000;
   tint = tint + tv.tv_usec / 1000;
   return (Time) tint;

}

int wordkeys = 0;

char
key_send_all(char *a_letters, ulong a_keysyms[])
{
   int i = 0;          /* letter iterator                                     */
   if (strlen(a_letters) > 0) DEBUG_OUTP   printf("\nBEGIN SENDKEYS...\n");
   /*> printf("strlen(%2d) <<%s>>\n", strlen(a_letters), a_letters);                  <*/
   if (strlen(a_letters) == 1 && wordkeys > 0 && states[HUBLIN] && a_letters[0] == (char) 0xAB) {
      for (i = 0; i < wordkeys; ++i) key_send(XK_BackSpace);
      wordkeys = 0;
   } else {
      for (i = 0; i < MAXWORD; ++i) {
         if (a_letters[i] == '\0') break;
         DEBUG_OUTP   printf("   - stroke letter %02d is %c\n", i, a_letters[i]);
         key_send(a_keysyms[i]);
      }
      wordkeys = strlen(a_letters);
   }
   if (strlen(a_letters) > 0) DEBUG_OUTP   printf("END SENDKEYS...\n");
   return 0;
}

void
key_send           (ulong a_keysym)
{
   DEBUG_OUTP    printf("   - key_send(%ld keysym)\n", a_keysym);
   /*---(check the modifiers)-----------------------------*/
   switch (a_keysym) {
   case XK_Shift_L     : 
      if (states[HUBLIN] != 0) return;
      if (states[SHIFT] != 0) {
         if (locks[SHIFT]  != 0) locks[SHIFT] = states[SHIFT]  = 0;
         else                    locks[SHIFT] = states[SHIFT]  = ShiftMask;  
      } else {
         states[SHIFT]  = ShiftMask;
      }
      DEBUG_OUTP   printf("   - MODIFIER Shift\n");
      return;
   case XK_Mode_switch :
      if (states[HUBLIN] != 0) return;
      if (states[MODE] != 0) {
         if (locks[MODE]  != 0)  locks[MODE] = states[MODE]  = 0;
         else                    locks[MODE] = states[MODE]  = 0x2000;
      } else {
         states[MODE]   = 0x2000;
      }
      DEBUG_OUTP   printf("   - MODIFIER Mode\n");
      return;
   case XK_Control_L   :
      if (states[HUBLIN] != 0) return;
      states[CONTROL] = ControlMask;
      DEBUG_OUTP   printf("   - MODIFIER Control\n");
      return;
   case XK_Alt_L       :
      if (states[HUBLIN] != 0) return;
      states[ALT]     = Mod1Mask;
      DEBUG_OUTP   printf("   - MODIFIER Alt\n");
      return;
   }
   /*---(set the basic xsendevent fields)-----------------*/
   SKEY.display     = DISP;
   SKEY.window      = FOCU;
   SKEY.send_event  = 1;
   SKEY.root        = ROOT;
   SKEY.subwindow   = None;
   SKEY.time        = fake_timestamp();
   SKEY.x           = 1;
   SKEY.y           = 1;
   SKEY.x_root      = 1;
   SKEY.y_root      = 1;
   SKEY.same_screen = 1;
   SKEY.state       = 0;
   /*---(handle sendkey)----------------------------------*/
   if (FOCU != ROOT || states[SUPER] != 0 || states[HYPER] != 0) {
      if (states[SUPER] != 0 || states[HYPER] != 0) {
         SKEY.window      = ROOT;
      }
      /*---(key)--------------*/
      SKEY.time        = fake_timestamp();
      SKEY.state       = 0;
      SKEY.state       = states[SHIFT] | states[MODE] | states[CONTROL] | states[ALT] | states[HYPER] | states[SUPER];
      SKEY.keycode     = XKeysymToKeycode(DISP, a_keysym);
      DEBUG_OUTP   printf("   - sending a %ld/0x%lx keysym as a %u keycode\n", a_keysym, a_keysym, SKEY.keycode);
      DEBUG_OUTP   printf("   - with modifiers %08x :: s=%04x, c=%04x, 1=%04x, 3=%04x, 4=%04x, 5=%04x\n", SKEY.state, states[SHIFT], states[CONTROL], states[ALT], states[MODE], states[HYPER], states[SUPER]);
      /*---(keypress side)-----------------------------------*/
      SKEY.time        = fake_timestamp();
      SKEY.type        = KeyPress;
      XSendEvent(DISP, SKEY.window, 0, KeyPressMask, (XEvent *) &SKEY);
      /*---(keyrelease side)---------------------------------*/
      SKEY.time        = fake_timestamp();
      SKEY.type        = KeyRelease;
      XSendEvent(DISP, SKEY.window, 0, KeyReleaseMask, (XEvent *) &SKEY);
      /*---(sync it up)--------------------------------------*/
      XSync(DISP, 1);
      XFlush(DISP);
      if (states[SUPER] != 0 || states[HYPER] != 0) {
         ;
         /*> letter_init();                                                          <*/
      }
   }
   /*---(remove states)-----------------------------------*/
   if (locks[MODE]   == 0) states[MODE]     = 0;
   if (locks[SHIFT]  == 0) states[SHIFT]    = 0;
   if (locks[HUBLIN] == 0) states[HUBLIN]   = 0;
   states[MYHUBLIN] = 0;
   states[CONTROL] = states[ALT] = states[HYPER] = states[SUPER] = 0;
   /*---(complete)----------------------------------------*/
   return;
}




/*============================--------------------============================*/
/*===----                         unit testing                         ----===*/
/*============================--------------------============================*/
static void      o___UNIT_TEST_______________o (void) {;}

#define       LEN_TEXT  2000
char          unit_answer [ LEN_TEXT ];

char*
unit_accessor(char *a_question, int a_num)
{
   if        (strcmp(a_question, "dot")         == 0) {
      if (ndots == 0) {
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : there are no dots", a_num);
      } else if (a_num < 0) {
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : can not be negative", a_num);
      } else if (a_num >= ndots) {
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : out of range %3d to %3d", a_num, 0, ndots - 1);
      } else
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : %4dx, %4dy, %4dc", a_num, dots[a_num].x, dots[a_num].y, ndots);
   } else if (strcmp(a_question, "current")     == 0) {
      if (stroke.outward) {
         snprintf(unit_answer, LEN_TEXT, "Current   (fore) : 0=%2d, 1=%2d, 2=%2d, 3=%2d, m=%2d", stroke.zth, stroke.fst, stroke.snd, stroke.trd, stroke.max);
      } else {
         snprintf(unit_answer, LEN_TEXT, "Current   (back) : 0=%2d, 1=%2d, 2=%2d, 3=%2d, m=%2d", stroke.zth, stroke.fst, stroke.snd, stroke.trd, stroke.max);
      }
   } else if (strcmp(a_question, "status")      == 0) {
      snprintf(unit_answer, LEN_TEXT, "Letter Status    : done=%d, accept=%d, fail=%d", stroke.done, stroke.pass, stroke.fail);
   }
   return unit_answer;
}



/*============================================================================*
 *=======                         END OF SOURCE                        =======*
 *============================================================================*/
