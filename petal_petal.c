/*============================[[    beg-code    ]]============================*/
#include    "petal.h"

tSTROKE     stroke;

char      stroke_letter[MAXWORD];
int       stroke_index [MAXWORD];
ulong     stroke_keysym[MAXWORD];



tPETAL  g_petals [LEN_TERSE];
int     g_npetal     = 0;



/*> tDOTS       dots        [MAX_DOTS];                                               <* 
 *> int         ndot;                                                                 <* 
 *> int         s_tries     = 0;                                                      <* 
 *> int         s_lastx     = 0;                                                      <* 
 *> int         s_lasty     = 0;                                                      <*/

int last_ring  = -1;
int last_petal = -1;

char garbage = 0;



char
STROKE_begin_OLD   (int a_x, int a_y, int a_r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(header)-------------------------*/
   RPTG_RECOG   printf ("\nbegin stroke recognition\n");
   /*---(add dot)------------------------*/
   /*> rc = DOT_beg (a_x, a_y);                                                       <*/
   if (rc < 0) return -1;
   /*---(reset flags)---------------------------*/
   letter_init();
   /*---(get the focus window)----------------------------*/
   /*> g_focus = yXINIT_focus();                                                      <*/
   RPTG_RECOG   printf("   - focus window     = %ld¦", g_focus);
   /*---(determine direction)-------------------*/
   if (curr_r <= shape.r_center)  stroke.outward = TRUE;
   else                           stroke.outward = FALSE;
   RPTG_RECOG   printf("   - stroke.outward   = %s\n", (stroke.outward) ? "TRUE" : "FALSE");
   /*---(for strokes)---------------------------*/
   strncpy(stroke_letter, "", 20);
   int i;
   for (i = 0; i < MAXWORD; ++i) stroke_keysym[i] = stroke_index[i] = 0;
   for (i = 0; i < 40; ++i) s_next[i] = 0;
   /*> s_nstroke = 0;                                                                 <*/
   /*> DRAW_main();                                                                   <*/
   /*---(complete)------------------------------*/
   return 0;
}

char
stroke_next (int a_x, int a_y, int a_r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*> RPTG_RECOG   printf("   - stroke_continue (%4dx, %4dy, %4dw)...\n", a_x, a_y, a_r);   <*/
   /*---(add dot)------------------------*/
   /*> rc = DOT_add (a_x, a_y, 'a');                                                  <*/
   if (rc < 0) return -1;
   /*---(check for wave offs)-------------------*/
   if (stroke.done   == 1) return 0;
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
   else                           x_ring  = 3;
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
         RPTG_RECOG    printf("   - ring=%2d outside touch spot\n", x_ring);
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
         RPTG_RECOG    printf("   - ring=%2d outside touch spot\n", x_ring);
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
   RPTG_RECOG    printf("   - ring=%2d, petal=%2d", x_ring, petal);
   if (x_ring > 7)  {
      RPTG_RECOG    printf("   buffer zone                   [ ignored ]\n");
      return -1;
   }
   /*---(cull duplicates)-----------------------*/
   if (x_ring == last_ring && petal == last_petal) {
      RPTG_RECOG    printf("   redundant                     [ ignored ]\n");
      return -1;
   }
   last_ring   = x_ring;
   last_petal  = petal;
   /*---(check for restart)---------------------*/
   if (x_ring == 0 && stroke.done == 0 && stroke.max >= 0) {
      RPTG_RECOG   printf("\n   - RESET in zth ring...\n");
      letter_interpret();
      letter_init();
      return 0;
   }
   /*---(cull redundant)------------------------*/
   if (x_ring == 0 && stroke.zth >= 0) {
      RPTG_RECOG    printf("   move in center only           [ ignored ]\n");
      return -1;
   }
   if (x_ring == 1 && stroke.max >= 1 &&  stroke.outward) {
      RPTG_RECOG    printf("   ring one (1) already locked   [ ignored ]\n");
      return -1;
   }
   if (x_ring == 1 && stroke.fst >= 0 && !stroke.outward)  return -1;
   if (x_ring == 2 && stroke.max >= 2 &&  stroke.outward) {
      RPTG_RECOG    printf("   ring two (2) already locked   [ ignored ]\n");
      return -1;
   }
   if (x_ring == 2 && stroke.snd >= 0 && !stroke.outward)  return -1;
   if (x_ring == 3 && stroke.trd >= 0) {
      RPTG_RECOG    printf("   ring three (3) already locked [ ignored ]\n");
      return -1;
   }
   RPTG_RECOG    printf("\n");
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



/*============================--------------------============================*/
/*===----                         program level                        ----===*/
/*============================--------------------============================*/
static void      o___PROGRAM____________o (void) {;}

char
PETAL__reset_one        (char i)
{
   g_petals [i].x = g_petals [i].y = g_petals [i].r = -1;
   g_petals [i].d = g_petals [i].n = g_petals [i].p = -1;
   return 0;
}

char
PETAL_reset             (void)
{
   int         i           =    0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < LEN_TERSE; ++i) {
      PETAL__reset_one (i);
   }
   g_npetal = 0;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PETAL_init              (void)
{
   return PETAL_reset ();
}



/*============================--------------------============================*/
/*===----                        main worker                           ----===*/
/*============================--------------------============================*/
static void      o___WORKER_____________o (void) {;}

char
PETAL__data             (int x, int y, int r, int *d, char *n, char *i, char *o)
{
   /*---(locals)-----------+-----+-----+-*/
   float        x_rads     =  0.0;
   int          x_deg      =   -1;
   char         x_ring     =   -1;
   char         x_inner    =   -1;
   char         x_outer    =   -1;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_complex ("args"      , "%4dx, %4dy, %4dr", x, y, r);
   /*---(default)------------------------*/
   if (d != NULL)  *d = -1;
   if (n != NULL)  *n = -1;
   if (i != NULL)  *i = -1;
   if (o != NULL)  *o = -1;
   /*---(assign angle)-------------------*/
   if ((x == 0 && y == 0) || r <= 1) {
      x_deg  = 0;
   } else {
      x_rads = atan2f (y, x);
      x_deg  = (x_rads * RAD2DEG);
   }
   /*---(handle limits)------------------*/
   if (x_deg < 0  )   x_deg += 360;
   if (x_deg > 360)   x_deg -= 360;
   DEBUG_DATA   yLOG_value   ("x_deg"     , x_deg);
   /*---(assign ring)--------------------*/
   DEBUG_DATA   yLOG_complex ("guides"    , "%4dr %4di %4do %4de", shape.g_ring, shape.g_inner, shape.g_outer, shape.g_edge);
   if      (r <=  shape.g_center)  x_ring  =  0;
   else if (r <=  shape.g_ring  )  x_ring  =  9;
   else if (r <=  shape.g_inner )  x_ring  =  1;
   else if (r <=  shape.g_outer )  x_ring  =  2;
   else if (r <=  shape.g_edge  )  x_ring  =  3;
   else                            x_ring  = 10;
   DEBUG_DATA   yLOG_value   ("x_ring"    , x_ring);
   /*---(inner petal)--------------------*/
   x_inner = (int) ((x_deg + 22.5) / 45);
   if (x_inner >  7)  x_inner -=  8;
   if (x_inner <  0)  x_inner +=  8;
   x_inner *= 2;
   DEBUG_DATA   yLOG_value   ("x_inner"   , x_inner);
   /*---(outer petal)--------------------*/
   x_outer = (int) ((x_deg      ) / 45);
   if (x_outer >  7)  x_outer -=  8;
   if (x_outer <  0)  x_outer +=  8;
   x_outer *= 2;
   ++x_outer;
   DEBUG_DATA   yLOG_value   ("x_outer"   , x_outer);
   /*---(save-back)----------------------*/
   if (d != NULL)  *d = x_deg;
   if (n != NULL)  *n = x_ring;
   if (i != NULL)  *i = x_inner;
   if (o != NULL)  *o = x_outer;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PETAL__check            (int x, int y, int r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   int         d;
   char        n, i, o;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(add dot)------------------------*/
   PETAL__data (x, y, r, &d, &n, &i, &o);
   DEBUG_DATA   yLOG_complex ("data"      , "%3dd, %2dn, %2di, %2do", d, n, i, o);
   /*---(quick-out)-----------------------------*/
   /*> if (n ==  9) {                                                                 <* 
    *>    DEBUG_DATA   yLOG_note    ("buffer area, nothing to do");                   <* 
    *>    DEBUG_DATA   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   if (n == 10) {
      DEBUG_DATA   yLOG_note    ("outside maximum area, nothing to do");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (g_petals [n].n >= 0) {
      DEBUG_DATA   yLOG_note    ("ring already assigned");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(always)--------------------------------*/
   g_petals [n].x = x;
   g_petals [n].y = y;
   g_petals [n].r = r;
   g_petals [n].n = n;
   g_petals [n].d = d;
   /*---(save-back)-----------------------------*/
   switch (n) {
   case 0  :  g_petals [n].p = 0;  break;
   case 1  :  g_petals [n].p = i;  break;
   case 2  :  g_petals [n].p = o;  break;
   case 3  :  g_petals [n].p = i;  break;
   case 9  :  g_petals [n].p = i;  break;
   }
   /*---(if 1, clear fast)----------------------*/
   if (n == 1) {
      DEBUG_DATA   yLOG_note    ("reset petal 9");
      PETAL__reset_one (9);
   }
   /*---(if 1 matches 3, clear 2)---------------*/
   if (n == 3) {
      DEBUG_DATA   yLOG_complex ("line"      , "%2d ? %2d", g_petals [1].p, g_petals [3].p);
      if (g_petals [1].p == g_petals [3].p) {
         DEBUG_DATA   yLOG_note    ("reset petal 2");
         PETAL__reset_one (2);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}



/*============================--------------------============================*/
/*===----                         simplifiers                          ----===*/
/*============================--------------------============================*/
static void      o___SIMPLIFIER_________o (void) {;}

char
PETAL_beg               (int x, int y, int r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   PETAL_reset ();
   rc = PETAL__check (x, y, r);
   /*> if (a_r <= shape.r_center)  stroke.outward = TRUE;                             <* 
    *> else                        stroke.outward = FALSE;                            <* 
    *> g_npetal = 0;                                                                  <*/
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
PETAL_add               (int x, int y, int r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   rc = PETAL__check (x, y, r);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
PETAL_end               (int x, int y, int r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   rc = PETAL__check (x, y, r);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return rc;
}






char
STROKE_begin       (int a_x, int a_y, int a_r)
{
   char        rc          = 0;
   PETAL_reset ();
   if (a_r <= shape.r_center)  stroke.outward = TRUE;
   else                        stroke.outward = FALSE;
   g_npetal = 0;
   return 0;
}

char
STROKE_end         (int a_x, int a_y, int a_r)
{
   /*> char rc = DOT_end (a_x, a_y);                                                  <*/
   char x_rc = 0;                               /* local return code          */
   char x_before[MAXWORD] = "";
   /*---(process immediately)-------------------*/
   if (stroke.done == 0)  letter_interpret();
   /*---(process the whole string)--------------*/
   RPTG_RECOG   printf("END STROKE   : STROKE_end(%4dx, %4dy, %4dw)...\n", a_x, a_y, a_r);
   /*---(handle hublin)-------------------------*/
   RPTG_RECOG   printf("BEGIN PROCESS\n");
   strncpy(x_before,     stroke_letter, MAXWORD);
   strncpy(stroke.feedback, stroke_letter, MAXWORD);
   /*> if (states[HUBLIN] || states[MYHUBLIN]) {                                                                                                                              <* 
    *>    RPTG_RECOG   printf("inside hublin area, <<%s>>, strlen = %d, HUB=%d, MYHUB=%d\n", stroke_letter, (int) strlen(stroke_letter), states[HUBLIN], states[MYHUBLIN]);   <* 
    *>    x_rc = -1;                                                                                                                                                          <* 
    *>    if      (states[HUBLIN]   && strcmp(stroke_letter, ">") == 0)  { x_rc = 0; strcpy (stroke_letter, "   "); }                                                         <* 
    *>    else if (states[MYHUBLIN] && strlen(stroke_letter) == 1) x_rc = hublin_mysingle (stroke.owner, stroke_letter, x_before);                                            <* 
    *>    else if (states[MYHUBLIN] && strlen(stroke_letter) == 2) x_rc = hublin_mydouble (stroke.owner, stroke_letter, x_before);                                            <* 
    *>    else if (states[HUBLIN]   && strlen(stroke_letter) == 1) x_rc = hublin_single   (stroke_letter, x_before);                                                          <* 
    *>    else if (states[HUBLIN]   && strlen(stroke_letter) == 2) x_rc = hublin_double   (stroke_letter, x_before);                                                          <* 
    *>    else if (states[HUBLIN]   && strlen(stroke_letter) == 3) x_rc = hublin_triple   (stroke_letter, x_before);                                                          <* 
    *>    /+> x_rc = hublin_find(stroke_letter, stroke_keysym);                           <+/                                                                                 <* 
    *>    if (x_rc == 0) {                                                                                                                                                    <* 
    *>       int  i, j;                                                                                                                                                       <* 
    *>       for (i = 0; i < MAXWORD; ++i) {                                                                                                                                  <* 
    *>          if (stroke_letter[i] == '\0') break;                                                                                                                          <* 
    *>          j = (stroke_letter[i] - 'a');                                                                                                                                 <* 
    *>          switch (stroke_letter[i]) {                                                                                                                                   <* 
    *>          /+> case ' '  : stroke_keysym[i] = XK_space;          break;              <*                                                                                  <* 
    *>           *> case '.'  : stroke_keysym[i] = XK_period;         break;              <*                                                                                  <* 
    *>           *> case '\n' : stroke_keysym[i] = XK_Return;         break;              <*                                                                                  <* 
    *>           *> case ','  : stroke_keysym[i] = XK_comma;          break;              <+/                                                                                 <* 
    *>          default   : stroke_keysym[i] = key_index[j];      break;                                                                                                      <* 
    *>          }                                                                                                                                                             <* 
    *>       }                                                                                                                                                                <* 
    *>       snprintf(stroke.feedback, MAXWORD, "%s (%s)", x_before, stroke_letter);                                                                                          <* 
    *>    }                                                                                                                                                                   <* 
    *> }                                                                                                                                                                      <*/
   RPTG_RECOG   printf("END PROCESS\n\n");
   /*---(handle sendkeys)-----------------------*/
   x_rc = key_send_all(stroke_letter, stroke_keysym);
   /*---(complete)------------------------------*/
   int i = 0;
   for (i = 0; i < 40; ++i) s_next[i] = 0;
   DRAW_main();
   return 0;
}



/*============================--------------------============================*/
/*===----                        unit testing                          ----===*/
/*============================--------------------============================*/
static void      o___UNITTEST___________o (void) {;}

char*
PETAL__unit             (char *a_question, int a_num)
{
   if      (strcmp (a_question, "single")         == 0) {
      if (a_num > -1 && a_num < 4 && g_petals [a_num].p >= 0) {
         sprintf (unit_answer, "PETAL single (%1d) : %4dx  %4dy    %4dr  %4dd    %2dn  %2dp", a_num,
               g_petals [a_num].x, g_petals [a_num].y,
               g_petals [a_num].r, g_petals [a_num].d,
               g_petals [a_num].n, g_petals [a_num].p);
      } else {
         sprintf (unit_answer, "PETAL single (%1d) :    ·x     ·y       ·r     ·d     ·n   ·p", a_num);
      }
   }
   return unit_answer;
}


/*============================[[ end-of-code ]]===============================*/
