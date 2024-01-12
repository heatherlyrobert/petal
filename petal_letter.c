/*============================[[    beg-code    ]]============================*/
#include    "petal.h"

uint   states[10];
uint   locks [10];


char   g_lower    [MAX_LETTER];
char   g_upper    [MAX_LETTER];
char   g_greek    [MAX_LETTER];
char   g_arith    [MAX_LETTER];
char   g_logic    [MAX_LETTER];
char   g_boxdr    [MAX_LETTER];
char   g_macro    [MAX_LETTER];
char   g_punct    [MAX_LETTER];


/*
 *
 *   INNER is six (6) letters and space/backspace
 *
 *                   t
 *              a    Ï    n     
 *               Ï   ·   Ï      
 *                 · · ·            
 *            ¿ Ï····´····Ï ¾       
 *                 · · ·            
 *               Ï   ·   Ï     
 *              o    Ï    i    
 *                   e
 *
 *
 *                    
 *
 *                m     c
 *             v Ï··· ···Ï f      
 *              ·    ·    ·
 *          y ···         n·· r
 *          Ï        ·        Ï
 *         k·      · · ·      ·u    
 *           ··· ····Ï···· ···      
 *         j·      · · ·      ·p    
 *          Ï        ·        Ï
 *          w····         ··· l
 *             ·     ·     ·
 *             g Ï··· ···Ï d      
 *                s     h
 *
 *                           
 *
 *
 *                   Ï
 *
 *                m     c
 *         Ï   v Ï€€€‰€€€Ï f   Ï  
 *                  t     
 *          y€€ˆa    Ï    nˆ€€r€€€€‚
 *          Ï    Ï’  ·  —Ï    Ï    
 *         k      ·“’·—–       u   x
 *     Ï   ‡€€¿ Ï····Ï····Ï ¾€€†   Ï
 *         j       —–·“’       p   q
 *          Ï    Ï–  ·  “Ï    Ï    
 *          w€€‰o    Ï    i‰€€l€€€€…
 *                  e     
 *         Ï   g Ï€€€ˆ€€·Ï d   Ï  
 *               s     h  
 *                        
 *             „€€€z Ï b€€€…
 *
 */


char g_mapping [LEN_FULL] = {
   /*--- 0 ---------*/
   0              , 0              , 0              , 0              ,
   0              , 0              , 0              , 0              ,
   0              , 0              , 0              , 0              ,
   0              , 0              , 0              , 0              ,
   /*--- 1 ---------*/
   0              , 0              , 0              , 0              ,
   0              , 0              , 0              , 0              ,
   0              , 0              , 0              , 0              ,
   0              , 0              , 0              , 0              ,
   /*--- 2 ---------*/
   XK_space       , XK_exclam      , XK_quotedbl    , XK_numbersign  ,
   XK_dollar      , XK_percent     , XK_ampersand   , XK_apostrophe  ,
   XK_parenleft   , XK_parenright  , XK_asterisk    , XK_plus        ,
   XK_comma       , XK_minus       , XK_period      , XK_slash       ,
   /*--- 3 ---------*/
   XK_0           , XK_1           , XK_2           , XK_3           ,
   XK_4           , XK_5           , XK_6           , XK_7           ,
   XK_8           , XK_9           , XK_colon       , XK_semicolon   ,
   XK_less        , XK_equal       , XK_greater     , XK_question    ,
   /*--- 4 ---------*/
   XK_at          , XK_A           , XK_B           , XK_C           ,
   XK_D           , XK_E           , XK_F           , XK_G           ,
   XK_H           , XK_I           , XK_J           , XK_K           ,
   XK_L           , XK_M           , XK_N           , XK_O           ,
   /*--- 5 ---------*/
   XK_P           , XK_Q           , XK_R           , XK_S           ,
   XK_T           , XK_U           , XK_V           , XK_W           ,
   XK_X           , XK_Y           , XK_Z           , XK_bracketleft ,
   XK_backslash   , XK_bracketright, XK_asciicircum , XK_grave       ,
   /*--- 6 ---------*/
   XK_at          , XK_a           , XK_b           , XK_c           ,
   XK_d           , XK_e           , XK_f           , XK_g           ,
   XK_h           , XK_i           , XK_j           , XK_k           ,
   XK_l           , XK_m           , XK_n           , XK_o           ,
   /*--- 7 ---------*/
   XK_p           , XK_q           , XK_r           , XK_s           ,
   XK_t           , XK_u           , XK_v           , XK_w           ,
   XK_x           , XK_y           , XK_z           , XK_braceleft   ,
   XK_bar         , XK_braceright  , XK_asciitilde  , -1             ,
};

char g_letters_OLD  [40] = {
   't' , 'm' , '[' , 'c' , '\"',   /* N    */
   'n' , 'f' , '_' , 'r' , 'x' ,   /* NE   */
   '¼' , 'u' , '.' , 'p' , ',' ,   /* E    */
   'i' , 'l' , 'q' , 'd' , 'b' ,   /* SE   */
   'e' , 'h' , '\'', 's' , ']' ,   /* S    */
   'o' , 'g' , 'z' , 'w' , ')' ,   /* SW   */
   '½' , 'j' , ';' , 'k' , ':' ,   /* W    */
   'a' , 'y' , '(' , 'v' , '-' ,   /* NW   */
};

char g_letters_NEW [40] = {
   'e' , 'g' , '\\', 'f' , '/' ,   /* N  Ï */
   'a' , 'd' , 'b' , 'c' , 'v' ,   /* NE Ï */
   '¼' , ',' , ';' , '.' , ':' ,   /* E  Ï */
   't' , 's' , 'u' , 'r' , '_' ,   /* SE Ï */
   'o' , 'q' , '"' , 'p' , '\'',   /* S  Ï */
   'n' , 'm' , '´' , 'l' , '´' ,   /* SW Ï */
   '½' , 'y' , 'z' , 'w' , 'x' ,   /* W  Ï */
   'i' , 'k' , 'j' , 'h' , '´' ,   /* NW Ï */
};

char g_letters_LATE [40] = {
   'e' , 'g' , '´' , 'f' , '´' ,   /* N  Ï */
   'a' , 'd' , 'b' , 'c' , '´' ,   /* NE Ï */
   '¼' , 'u' , '´' , 'v' , '´' ,   /* E  Ï */
   't' , 's' , '´' , 'r' , '´' ,   /* SE Ï */
   'o' , 'q' , '´' , 'p' , '´' ,   /* S  Ï */
   'n' , 'm' , '´' , 'l' , '´' ,   /* SW Ï */
   '½' , 'y' , 'z' , 'w' , 'x' ,   /* W  Ï */
   'i' , 'k' , 'j' , 'h' , '´' ,   /* NW Ï */
};

char g_letters_EASY [40] = {
   'g' , 'i' , '´' , 'h' , '´' ,   /* N  Ï */
   'd' , 'f' , '´' , 'e' , '´' ,   /* NE Ï */
   'a' , 'c' , '´' , 'b' , '´' ,   /* E  Ï */
   'v' , 'y' , 'z' , 'w' , 'x' ,   /* SE Ï */
   's' , 'u' , '´' , 't' , '´' ,   /* S  Ï */
   'p' , 'r' , '´' , 'q' , '´' ,   /* SW Ï */
   'm' , 'o' , '´' , 'n' , '´' ,   /* W  Ï */
   'j' , 'l' , '´' , 'k' , '´' ,   /* NW Ï */
};

char g_letters_CONF [40];

char *g_letters = g_letters_CONF;

char g_upper [40] = {
   'T' , 'M' , '[' , 'C' , '~' ,   /* N    */
   'N' , 'F' , '_' , 'R' , 'X' ,   /* NE   */
   '·' , 'U' , '!' , 'P' , '?' ,   /* E    */
   'I' , 'L' , 'Q' , 'D' , 'B' ,   /* SE   */
   'E' , 'H' , '`' , 'S' , ']' ,   /* S    */
   'O' , 'G' , 'Z' , 'W' , ')' ,   /* SW   */
   '¿' , 'J' , ';' , 'K' , ':' ,   /* W */
   'A' , 'Y' , '(' , 'V' , '-' ,   /* NW   */
};


int  g_akeysyms_OLD [40] = {
   XK_t         , XK_m           , XK_bracketleft, XK_c       , XK_quotedbl    ,
   XK_n         , XK_f           , XK_underscore , XK_r       , XK_x           ,
   XK_space     , XK_u           , XK_period     , XK_p       , XK_comma       ,
   XK_i         , XK_l           , XK_q          , XK_d       , XK_b           ,
   XK_e         , XK_h           , XK_apostrophe , XK_s       , XK_bracketright,
   XK_o         , XK_g           , XK_z          , XK_w       , XK_parenright  ,
   XK_BackSpace , XK_j           , XK_semicolon  , XK_k       , XK_colon       ,
   XK_a         , XK_y           , XK_parenleft  , XK_v       , XK_minus       ,
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

/*> char g_punct[40] = {                                                              <* 
 *>    '0' , '|' , '[' , '2' , '\"',   /+ N   % ^ | @ $ _ & # : \ +/                  <* 
 *>    '=' , '3' , '_' , '4' , '$' ,   /+ NE   |{}[]  & _<>$   +/                     <* 
 *>    '·' , '5' , '.' , '6' , ',' ,   /+ E   % ;/-0 :\ 1()= ^ +/                     <* 
 *>    '+' , '7' , '@' , '8' , '^' ,   /+ SE  @ 8642 +* 3579   +/                     <* 
 *>    '1' , '9' , '\'', '#' , ']' ,   /+ S    +/                                     <* 
 *>    '*' , '>' , '%' , '<' , ')' ,   /+ SW   +/                                     <* 
 *>    '¿' , '}' , ';' , '{' , ':' ,   /+ W    +/                                     <* 
 *>    '/' , '\\', '(' , '&' , '-' ,   /+ NW   +/                                     <* 
 *> };                                                                                <*/
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

char g_special[10]          = { 'S', 'M', 'T', 'H', '¦', 'A', '¥', 'C', };
int  g_akeysyms_special[10] = {
   XK_Shift_L  , XK_Mode_switch, XK_Tab      , 1000000       ,
   XK_Return   , XK_Alt_L      , XK_Escape   , XK_Control_L  ,
};

char s_next[40];


int  key_index[30] = {      /* to allow lookup on hublin shortcuts            */
   XK_a, XK_b, XK_c, XK_d, XK_e, XK_f, XK_g, XK_h, XK_i, XK_j, XK_k, XK_l, XK_m,
   XK_n, XK_o, XK_p, XK_q, XK_r, XK_s, XK_t, XK_u, XK_v, XK_w, XK_x, XK_y, XK_z
};



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
letter_update           (int a_ring, int a_petal)
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

char
LETTER_by_index         (char n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        c           =  '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_svalue  ("n", n);
   --rce;  if (n < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (n >= 40) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(return)-------------------------*/
   c = g_letters [n];
   if (states [MODE]  != 0) c = g_punct [n];
   if (states [SHIFT] != 0) c = g_upper [n];
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return c;
}

char
LETTER_by_stroke        (char i, char o, char e)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =  ' ';
   char        o2          =    o;
   char        x_left      =  '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(inner)--------------------------*/
   DEBUG_GRAF   yLOG_svalue  ("i", i);
   --rce;  if (i < 0 || i > 7) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   n = i * 5;
   DEBUG_GRAF   yLOG_sint    (n);
   /*---(outer)--------------------------*/
   DEBUG_GRAF   yLOG_svalue  ("o", o);
   --rce;  if (o < 0) {
      if (e >= 0) {
         DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return n;
   }
   --rce;  if (o > 7) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (o < i - 1) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   o2 = o;
   if (i == 0 && o == 7)  o2 = i;
   --rce;  if (o2 > i) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (o >= 0) {
      if (o != i) { n += 1; x_left = 'y'; }
      else        { n += 3; x_left = '-'; }
   }
   DEBUG_GRAF   yLOG_sint    (n);
   /*---(edge)---------------------------*/
   --rce;  if (e < 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return n;
   }
   --rce;  if (e > 7) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_left == 'y' && e != i - 1) {
      if (i == 0) {
         if (e != 7) {
            DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
      } else {
         DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (x_left == '-' && e != i + 1) {
      if (i == 7) {
         if (e != 0) {
            DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
      } else {
         DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   ++n;
   DEBUG_GRAF   yLOG_sint    (n);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return n;
}

char
LETTER_to_stroke        (char a_all, char c, char *m, char *i, char *o, char *e)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         j           =    0;
   int         n           =   -1;          /* full index                     */
   char        xn          =   -1;          /* remaining outer/edge index     */
   char        xi          =   -1;          /* inner stroke                   */
   char        xo          =   -1;          /* outer stroke                   */
   char        xe          =   -1;          /* edge stroke                    */
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(initialize)---------------------*/
   if (m != NULL)  *m = -1;
   if (i != NULL)  *i = -1;
   if (o != NULL)  *o = -1;
   if (e != NULL)  *e = -1;
   /*---(special)------------------------*/
   if (c == '¶')    c = '"';
   /*---(find in letters)----------------*/
   for (j = 0; j < 40; ++j) {
      if (g_letters [j] == c) {
         DEBUG_GRAF   yLOG_snote   ("normal");
         n  = j;
         if (m != NULL)  *m = -1;
         break;
      }
      if (a_all == 'y' && g_upper   [j] == c) {
         DEBUG_GRAF   yLOG_snote   ("shift");
         n  = j;
         if (m != NULL)  *m = SHIFT;
         break;
      }
      if (a_all == 'y' && g_punct   [j] == c) {
         DEBUG_GRAF   yLOG_snote   ("mode");
         n  = j;
         if (m != NULL)  *m = MODE;
         break;
      }
      if (a_all == '-' && j < 10 && g_special [j] == c) {
         DEBUG_GRAF   yLOG_snote   ("special");
         n  = j;
         if (m != NULL)  *m = 20;
         break;
      }
   }
   DEBUG_GRAF   yLOG_svalue  ("n", n);
   --rce;  if (n < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(specials)-----------------------*/
   if (*m == 20) {
      if (i != NULL)  *i = n;
      if (e != NULL)  *i = n;
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return n;
   }
   /*---(set inner)----------------------*/
   xn  = n;
   xi  = n / 5;
   xn  = n % 5;
   DEBUG_GRAF   yLOG_svalue  ("i", xi);
   /*---(set outer)----------------------*/
   DEBUG_GRAF   yLOG_sint    (xn);
   switch (xn) {
   case 0 :
      xo = -1;
      break;
   case 1 : case 2 :
      if (xi == 0) xo = 7;
      else         xo = xi - 1;
      break;
   case 3 : case 4 :
      xo = xi;
      break;
   }
   DEBUG_GRAF   yLOG_svalue  ("o", xo);
   /*---(set outer)----------------------*/
   switch (xn) {
   case 0 : case 1 : case 3 :
      xe = -1;
      break;
   case 2 :
      xe = xo;
      break;
   case 4 :
      if (xi == 7) xe = 0;
      else         xe = xo + 1;
      break;
   }
   DEBUG_GRAF   yLOG_svalue  ("e", xe);
   /*---(save back)----------------------*/
   shape.r_loc = n;
   if (i != NULL)  *i = xi;
   if (o != NULL)  *o = xo;
   if (e != NULL)  *e = xe;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
LETTER_by_mode          (char n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        c           =  '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_svalue  ("n", n);
   --rce;  if (n < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (n >= 8) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(return)-------------------------*/
   c = g_special [n];
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return c;
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
      /*> stroke_letter[stroke_count]     = letter;                                   <*/
      /*> stroke_letter[stroke_count + 1] = '\0';                                     <*/
      /*> stroke_keysym[stroke_count]     = keysym;                                   <*/
      /*> stroke_index [stroke_count]     = stroke.ndx;                               <*/
      /*> ++stroke_count;                                                             <*/
      /*> DEBUG_INPT  printf("   - stroke adds \"%c\" so <<%s>> and %d long\n", letter, stroke_letter, stroke_count);   <*/
      /*> sprintf (stroke.text, "%c", letter);                                        <*/
      DRAW_main();
   } else {
      DEBUG_INPT   printf(", NOT SENT\n");
   }
   /*> states[MODE] = temp_mode;                                                      <* 
    *> locks [MODE] = temp_lock;                                                      <*/
   return;
}
