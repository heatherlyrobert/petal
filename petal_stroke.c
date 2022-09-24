/*============================[[    beg-code    ]]============================*/
#include    "petal.h"

tSTROKE     stroke;

tDOTS       dots        [MAX_DOTS];
int         ndot;
int         s_tries     = 0;
int         s_lastx     = 0;
int         s_lasty     = 0;

int last_ring  = -1;
int last_petal = -1;

/*============================--------------------============================*/
/*===----                      simple dot tracing                      ----===*/
/*============================--------------------============================*/
static void      o___DOTS____________________o (void) {;}
char garbage = 0;

char         /*--> prepare for dot capture ---------------[ leaf   [ ------ ]-*/
DOT_beg (int a_x, int a_y)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   RPTG_DOTS    printf ("\nbegin raw dot capture\n");
   /*---(clear dot structure)------------*/
   for (i = 0; i < MAX_DOTS; ++i) {
      dots [i].tries  = 0;
      dots [i].absx   = 0;
      dots [i].absy   = 0;
      dots [i].relx   = 0;
      dots [i].rely   = 0;
      dots [i].delta  = 0;
      dots [i].radius = 0;
   }
   ndot    = 0;
   /*---(initialize globals)-------------*/
   s_tries = 0;
   s_lastx = 0;
   s_lasty = 0;
   /*> init_x  = a_x + 1;                                                             <* 
    *> init_y  = a_y + 1;                                                             <*/
   curr_x  = 0;
   curr_y  = 0;
   curr_r  = 0;
   s_lastx = 0;
   s_lasty = 0;
   garbage = 0;
   /*---(add the first dot)--------------*/
   char rc = DOT_add (a_x, a_y, 'b');
   /*---(complete)-----------------------*/
   return rc;
}

char
DOT_add (int a_x, int a_y, char a_place)
{
   /*---(locals)-----------+-----------+-*/
   int         x           = 0;
   int         y           = 0;
   float       r           = 0.0f;
   /*---(headers and line breaks)--------*/
   if ((s_tries % 15) == 0) {
      RPTG_DOTS    printf ("\ntry-  absx  absy  relx  rely  movx  movy  movr  radii  ---evaluation------------ --#--\n");
   }
   if ((s_tries %  3) == 0) {
      RPTG_DOTS    printf ("\n");
   }
   ++s_tries;
   /*---(print values)-------------------*/
   x   = a_x;
   y   = a_y;
   RPTG_DOTS    printf ("%4d  %4d  %4d  ", s_tries, x, y);
   dots [ndot].tries  = s_tries;
   dots [ndot].absx   = x;
   dots [ndot].absy   = y;
   /*---(filter)-------------------------*/
   if (garbage == 1)  {
      RPTG_DOTS    printf ("----  ----  ----  ----  ----  -----  rejected, garbage on         --\n");
      return -1;
   }
   if (ndot >= MAX_DOTS) {
      RPTG_DOTS    printf ("----  ----  ----  ----  ----  -----  rejected, too many dots      --\n");
      return -3;
   }
   /*---(calculate relatives)------------*/
   x  -= init_x;
   y  -= init_y;
   RPTG_DOTS    printf ("%4d  %4d  ", x, y);
   dots [ndot].relx = x;
   dots [ndot].rely = y;
   x  -= s_lastx;
   y  -= s_lasty;
   r   = sqrt((x * x) + (y * y));
   RPTG_DOTS    printf ("%4d  %4d  %4.1f  ", x, y, r);
   /*---(filter)-------------------------*/
   if (ndot > 0 && r <  3.0 && a_place != 'e') {
      RPTG_DOTS    printf ("-----  rejected, too close          --\n");
      return -4;
   }
   if (r > 30.0 && ndot > 0) {
      RPTG_DOTS    printf ("-----  rejected, moved too far      --\n");
      garbage = 1;
      return -5;
   }
   dots [ndot].delta = r;
   /*---(save old values)----------------*/
   s_lastx = dots [ndot].relx;
   s_lasty = dots [ndot].rely;
   curr_x = a_x - init_x;
   curr_y = a_y - init_y;
   /*---(calculate distance)-------------*/
   curr_r = sqrt((curr_x * curr_x) + (curr_y * curr_y));
   dots [ndot].radius = curr_r;
   /*---(accept)-------------------------*/
   if (a_place == 'e') {
      RPTG_DOTS    printf ("%5.1f  accepted, last dot        %5d\n", curr_r, ndot);
   } else {
      RPTG_DOTS    printf ("%5.1f  accepted                  %5d\n", curr_r, ndot);
   }
   ++ndot;
   /*---(complete)-----------------------*/
   return 0;
}

char
DOT_end (int a_x, int a_y)
{
   /*> if (a_x == curr_x && a_y == curr_y) return -1;                                 <*/
   /*> curr_x = 1000;                                                                 <* 
    *> curr_y = 1000;                                                                 <*/
   char rc = DOT_add (a_x, a_y, 'e');
   RPTG_DOTS    printf ("done for this stroke\n");
   return rc;
}



/*============================--------------------============================*/
/*===----                        stroke handling                       ----===*/
/*============================--------------------============================*/
static void      o___STROKES_________________o (void) {;}


char
STROKE_begin       (int a_x, int a_y, int a_r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(header)-------------------------*/
   RPTG_RECOG   printf ("\nbegin stroke recognition\n");
   /*---(add dot)------------------------*/
   rc = DOT_beg (a_x, a_y);
   if (rc < 0) return -1;
   /*---(reset flags)---------------------------*/
   letter_init();
   /*---(get the focus window)----------------------------*/
   /*> g_focus = yXINIT_focus();                                                      <*/
   RPTG_RECOG   printf("   - focus window     = %ld¦", g_focus);
   /*---(determine direction)-------------------*/
   if (curr_r <= shape.r_center)  stroke.outward = TRUE;
   else                       stroke.outward = FALSE;
   RPTG_RECOG   printf("   - stroke.outward   = %s\n", (stroke.outward) ? "TRUE" : "FALSE");
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
stroke_petal       (float a_r)
{
}

char
stroke_next (int a_x, int a_y, int a_r)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*> RPTG_RECOG   printf("   - stroke_continue (%4dx, %4dy, %4dw)...\n", a_x, a_y, a_r);   <*/
   /*---(add dot)------------------------*/
   rc = DOT_add (a_x, a_y, 'a');
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

char
STROKE_end         (int a_x, int a_y, int a_r)
{
   char rc = DOT_end (a_x, a_y);
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
   stroke_count = 0;
   return 0;
}


/*============================[[ end-of-code ]]===============================*/
