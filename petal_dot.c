/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



tDOTS       g_dots        [MAX_DOTS];
int         g_ndot      = 0;

static int  s_tries     = 0;

static int  s_lastx     = 0;
static int  s_lasty     = 0;
static char s_lock      = '-';





/*============================--------------------============================*/
/*===----                        program level                         ----===*/
/*============================--------------------============================*/
static void      o___PROGRAM____________o (void) {;}

char
DOT__reset              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(clear dot structure)------------*/
   for (i = 0; i < MAX_DOTS; ++i) {
      g_dots [i].d_place = '·';
      g_dots [i].d_seq   = -1;
      g_dots [i].d_tx    = -6666;
      g_dots [i].d_ty    = -6666;
      g_dots [i].d_sx    = -6666;
      g_dots [i].d_sy    = -6666;
      g_dots [i].d_wx    = -6666;
      g_dots [i].d_wy    = -6666;
      g_dots [i].d_wr    = -6666;
      g_dots [i].d_wd    = -6666;
   }
   g_ndot  = 0;
   /*---(initialize globals)-------------*/
   s_tries = 0;
   s_lastx = 0;
   s_lasty = 0;
   s_lock  = '-';
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DOT_init                (void)
{
   return DOT__reset ();
}



/*============================--------------------============================*/
/*===----                        main workers                          ----===*/
/*============================--------------------============================*/
static void      o___WORKER_____________o (void) {;}

char
DOT__add                (char a_tst, char a_func [LEN_LABEL], int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr, char a_place)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x           =    0;
   int         y           =    0;
   float       r           =  0.0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (a_func);
   /*---(check lock)---------------------*/
   --rce;  if (s_lock == 'y') {
      DEBUG_DATA   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(update tries)-------------------*/
   ++s_tries;
   DEBUG_DATA   yLOG_value   ("s_tries"   , s_tries);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_value   ("g_ndot"    , g_ndot);
   --rce;  if (g_ndot >= MAX_DOTS) {
      DEBUG_DATA   yLOG_exitr   (a_func, rce);
      return rce;
   }
   --rce;  if (g_ndot == 0 && a_place != 'b') {
      DEBUG_DATA   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x   = a_wx - s_lastx;
   y   = a_wy - s_lasty;
   if (x == 0 && y == 0)  r = 0;
   else                   r   = sqrt ((x * x) + (y * y));
   DEBUG_DATA   yLOG_complex ("rel pos"   , "%4d#, %4dx, %4dy, %4.0fr", s_tries, x, y, r);
   /*---(quick-out)----------------------*/
   if (g_ndot > 0 && r <  1.0 && a_place != 'e') {
      DEBUG_DATA   yLOG_note    ("too close to previous point");
      DEBUG_DATA   yLOG_exit    (a_func);
      return 0;
   }
   --rce;  if (a_tst != 'y' && g_ndot > 0 && r > 10.0) {
      DEBUG_DATA   yLOG_note    ("too far from previous point (FATAL)");
      DEBUG_DATA   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(save-dot)-----------------------*/
   g_dots [g_ndot].d_place = a_place;
   g_dots [g_ndot].d_seq   = s_tries - 1;
   g_dots [g_ndot].d_tx    = a_tx;
   g_dots [g_ndot].d_ty    = a_ty;
   g_dots [g_ndot].d_sx    = a_sx;
   g_dots [g_ndot].d_sy    = a_sy;
   g_dots [g_ndot].d_wx    = a_wx;
   g_dots [g_ndot].d_wy    = a_wy;
   g_dots [g_ndot].d_wr    = a_wr;
   g_dots [g_ndot].d_wd    = r;
   ++g_ndot;
   /*---(save-last)----------------------*/
   s_lastx = a_wx;
   s_lasty = a_wy;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (a_func);
   return 1;
}



/*============================--------------------============================*/
/*===----                         simplifiers                          ----===*/
/*============================--------------------============================*/
static void      o___SIMPLIFIER_________o (void) {;}

char
DOT_beg                 (int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr)
{
   DOT__reset ();
   return DOT__add ('-', __FUNCTION__, a_tx, a_ty, a_sx, a_sy, a_wx, a_wy, a_wr, 'b');
}

char
DOT_add                 (int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr)
{
   return DOT__add ('-', __FUNCTION__, a_tx, a_ty, a_sx, a_sy, a_wx, a_wy,  a_wr, '´');
}

char
DOT_end                 (int a_tx, int a_ty, int a_sx, int a_sy, int a_wx, int a_wy, int a_wr)
{
   return DOT__add ('-', __FUNCTION__, a_tx, a_ty, a_sx, a_sy, a_wx, a_wy,  a_wr, 'e');
}



/*============================--------------------============================*/
/*===----                        unit testing                          ----===*/
/*============================--------------------============================*/
static void      o___UNITTEST___________o (void) {;}

char
DOT_force_point         (int x, int y)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   0;
   int         sx          =   0;
   int         sy          =   0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_complex ("args"      , "%4dx %4dy", x, y);
   /*---(set xpos)-----------------------*/
   DEBUG_DATA   yLOG_value   ("w_align"   , my.w_align);
   switch (my.w_align) {
   case YGLTEX_TOPLEF : case YGLTEX_MIDLEF : case YGLTEX_BOTLEF :
      DEBUG_DATA   yLOG_note    ("handle lefts");
      sx = my.w_left + x;
      break;
   case YGLTEX_TOPCEN : case YGLTEX_MIDCEN : case YGLTEX_BOTCEN :
      DEBUG_DATA   yLOG_note    ("handle centers");
      sx = (my.w_left + (my.w_wide / 2.0)) + x;
      break;
   case YGLTEX_TOPRIG : case YGLTEX_MIDRIG : case YGLTEX_BOTRIG :
      DEBUG_DATA   yLOG_note    ("handle rights");
      sx = (my.w_left + my.w_wide) + x;
      break;
   }
   DEBUG_DATA   yLOG_value   ("sx"        , sx);
   /*---(set ypos)-----------------------*/
   switch (my.w_align) {
   case YGLTEX_TOPLEF : case YGLTEX_TOPCEN : case YGLTEX_TOPRIG :
      DEBUG_DATA   yLOG_note    ("handle tops");
      sy = my.w_topp - y;
      break;
   case YGLTEX_MIDLEF : case YGLTEX_MIDCEN : case YGLTEX_MIDRIG :
      DEBUG_DATA   yLOG_note    ("handle middles");
      sy = (my.w_topp + (my.w_tall / 2.0)) - y;
      break;
   case YGLTEX_BOTLEF : case YGLTEX_BOTCEN : case YGLTEX_BOTRIG :
      DEBUG_DATA   yLOG_note    ("handle bottoms");
      sy = (my.w_topp + my.w_tall) - y;
      break;
   }
   DEBUG_DATA   yLOG_value   ("sy"        , sy);
   /*---(reverse the point)--------------*/
   rc = TOUCH_point (((float) sx) / my.s_xratio, ((float) sy) / my.s_yratio);
   DEBUG_DATA   yLOG_value   ("point"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
DOT_force_beg           (int a_wx, int a_wy)
{
   char        rc          =    0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DOT__reset ();
   rc = DOT_force_point (a_wx, a_wy);
   if (rc >= 0)  rc = DOT__add ('y', __FUNCTION__, my.t_x, my.t_y, my.s_x, my.s_y, my.w_x, my.w_y, my.w_r, 'b');
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
DOT_force_add           (int a_wx, int a_wy)
{
   char        rc          =    0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   rc = DOT_force_point (a_wx, a_wy);
   if (rc >= 0)  rc = DOT__add ('y', __FUNCTION__, my.t_x, my.t_y, my.s_x, my.s_y, my.w_x, my.w_y, my.w_r, '´');
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
DOT_force_end           (int a_wx, int a_wy)
{
   char        rc          =    0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   rc = DOT_force_point (a_wx, a_wy);
   if (rc >= 0)  rc = DOT__add ('y', __FUNCTION__, my.t_x, my.t_y, my.s_x, my.s_y, my.w_x, my.w_y, my.w_r, 'e');
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return rc;
}

char*
DOT__unit               (char *a_question, int a_num)
{
   if      (strcmp (a_question, "point" )         == 0) {
      if (a_num < g_ndot)  sprintf (unit_answer, "DOT point  (%3d) : %3d %c   %5dx  %5dy   %5dx  %5dy   %5dx  %5dy  %5dr  %5dd",
            a_num, g_dots [a_num].d_seq, g_dots [a_num].d_place,
            g_dots [a_num].d_tx, g_dots [a_num].d_ty,
            g_dots [a_num].d_sx, g_dots [a_num].d_sy,
            g_dots [a_num].d_wx, g_dots [a_num].d_wy, g_dots [a_num].d_wr, g_dots [a_num].d_wd);
      else                 sprintf (unit_answer, "DOT point  (%3d) :   · ·       ·x      ·y       ·x      ·y       ·x      ·y      ·r      ·d", a_num);
   }
   else if (strcmp (a_question, "reverse")        == 0) {
      sprintf (unit_answer, "DOT reverse      :   ·   %5dx  %5dy   %5dx  %5dy   %5dx  %5dy  %5dr      ·d",
            my.t_x, my.t_y, my.s_x, my.s_y, my.w_x, my.w_y, my.w_r);
   }
   return unit_answer;
}


