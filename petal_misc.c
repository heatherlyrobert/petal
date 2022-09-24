/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



/*---(GLX Globals)---------------------------------*/
/*> XWindowAttributes      gwa;                                                       <*/

ulong  g_focus = 0;


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
float     curr_r;
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
/*===----                        mouse handling                        ----===*/
/*============================--------------------============================*/
static void      o___MOUSE___________________o (void) {;}

void
mouse_init (void)            /* initialize mouse usage before program starts  */
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   stroke_count  = 0;
   strncpy(stroke_letter, "", 20);
   letter_init();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
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
   /*> yXINIT_focus();                                                                <*/
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
   /*> yXINIT_focus();                                                                <*/
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
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
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
   /*> for (i = 0; i < 40; ++i) s_next[i] = 0;                                        <* 
    *> if (stroke_count == 2 && states[HUBLIN]) {                                     <* 
    *>    hublin_next(g_letters, s_next, stroke_letter);                              <* 
    *>    DRAW_main();                                                                <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
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
   YX_SKEY.display     = YX_DISP;
   YX_SKEY.window      = g_focus;
   YX_SKEY.send_event  = 1;
   YX_SKEY.root        = YX_ROOT;
   YX_SKEY.subwindow   = None;
   YX_SKEY.time        = fake_timestamp();
   YX_SKEY.x           = 1;
   YX_SKEY.y           = 1;
   YX_SKEY.x_root      = 1;
   YX_SKEY.y_root      = 1;
   YX_SKEY.same_screen = 1;
   YX_SKEY.state       = 0;
   /*---(handle sendkey)----------------------------------*/
   if (g_focus != YX_ROOT || states[SUPER] != 0 || states[HYPER] != 0) {
      if (states[SUPER] != 0 || states[HYPER] != 0) {
         YX_SKEY.window      = YX_ROOT;
      }
      /*---(key)--------------*/
      YX_SKEY.time        = fake_timestamp();
      YX_SKEY.state       = 0;
      YX_SKEY.state       = states[SHIFT] | states[MODE] | states[CONTROL] | states[ALT] | states[HYPER] | states[SUPER];
      YX_SKEY.keycode     = XKeysymToKeycode(YX_DISP, a_keysym);
      DEBUG_OUTP   printf("   - sending a %ld/0x%lx keysym as a %u keycode\n", a_keysym, a_keysym, YX_SKEY.keycode);
      DEBUG_OUTP   printf("   - with modifiers %08x :: s=%04x, c=%04x, 1=%04x, 3=%04x, 4=%04x, 5=%04x\n", YX_SKEY.state, states[SHIFT], states[CONTROL], states[ALT], states[MODE], states[HYPER], states[SUPER]);
      /*---(keypress side)-----------------------------------*/
      YX_SKEY.time        = fake_timestamp();
      YX_SKEY.type        = KeyPress;
      XSendEvent(YX_DISP, YX_SKEY.window, 0, KeyPressMask, (XEvent *) &YX_SKEY);
      /*---(keyrelease side)---------------------------------*/
      YX_SKEY.time        = fake_timestamp();
      YX_SKEY.type        = KeyRelease;
      XSendEvent(YX_DISP, YX_SKEY.window, 0, KeyReleaseMask, (XEvent *) &YX_SKEY);
      /*---(sync it up)--------------------------------------*/
      XSync(YX_DISP, 1);
      XFlush(YX_DISP);
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
      if (ndot == 0) {
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : there are no dots", a_num);
      } else if (a_num < 0) {
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : can not be negative", a_num);
      } else if (a_num >= ndot) {
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : out of range %3d to %3d", a_num, 0, ndot - 1);
      } else
         snprintf(unit_answer, LEN_TEXT, "Dot Trace (%4d) : %4dx, %4dy, %4dc", a_num, dots[a_num].relx, dots[a_num].rely, ndot);
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
