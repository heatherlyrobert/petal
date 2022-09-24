/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



#define  HELP_ONLY    if (stroke.help > 0 && stroke.help < 10 && stroke.help != i + 1)   continue



/*============================--------------------============================*/
/*===----                        event loop                            ----===*/
/*============================--------------------============================*/
static void      o___LOOP____________________o (void) {;}

char
DRAW_main          (void)
{
   /*---(locals)----------------------------*/
   float       x_mid, x_cen;
   float       z;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(center)----------------------------*/
   x_mid  = shape.sz_nav + (shape.sz_height - shape.sz_nav) / 2.0;
   x_cen  = shape.sz_width / 2.0;
   z      =   20.0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(start)--------------------------*/
   long  x_start, x_stop;
   x_start = time_stamp();
   /*---(draw)---------------------------*/
   DRAW_back    ();
   glPushMatrix(); {
      glTranslatef (x_cen, x_mid,  z);
      DRAW_image   ();
      DRAW_labels  ();
      /*> DRAW_current();                                                                <*/
      /*> DRAW_locks();                                                                  <*/
      /*> DRAW_arrows();                                                                 <*/
   } glPopMatrix();
   DRAW_navigation ();
   /*> DRAW_context();                                                                <*/
   /*> DRAW_dots();                                                                   <*/
   /*---(timing)-------------------------*/
   x_stop  = time_stamp();
   DEBUG_GRAF   yLOG_llong   ("elapsed"   , x_stop - x_start);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_back          (void)
{
   /*---(locals)----------------------------*/
   float       x_top, x_rig;
   float       z;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(sizes)-----------------------------*/
   x_top  = shape.sz_height;
   x_rig  = shape.sz_width;
   z      = -20.0;
   /*---(bottom shaded area)----------------*/
   glColor4f  (0.7f, 0.7f, 0.7f, 1.0f);
   glBegin    (GL_POLYGON); {
      glVertex3f ( 0.0  , x_top, z);
      glVertex3f ( x_rig, x_top, z);
      glVertex3f ( x_rig, 0.0  , z);
      glVertex3f ( 0.0  , 0.0  , z);
   } glEnd();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_resize        (uint a_w, uint a_h)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("size"      , "%d, %d", a_w, a_h);
   if (a_h == 0) a_h = 1;
   /*> WIDTH   = a_w;                                                                 <* 
    *> HEIGHT  = a_h;                                                                 <*/
   glViewport(0,  0, a_w, a_h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float  x_lef   = shape.sz_centerx;
   float  x_rig   = shape.sz_centerx;
   float  x_top   = shape.sz_centery + shape.sz_ctl;
   float  x_bot   = shape.sz_centery + shape.sz_nav;
   glOrtho( -x_lef       ,  x_rig, -x_bot,  x_top, -100.0,  100.0);
   glMatrixMode(GL_MODELVIEW);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_dots          (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(locals)---------------------------*/
   int   i;
   /*---(leaves)---------------------------*/
   glPushMatrix();
   glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
   glLineWidth(shape.r_dots);
   glBegin(GL_LINE_STRIP);
   for (i = 0; i < ndot; i += 1) {
      glVertex3f( dots[i].relx, dots[i].rely,   4.00f);
   }
   glEnd();
   glLineWidth(0.8);
   glPopMatrix();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_image (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(locals)---------------------------*/
   int   i;
   /*---(leaves)---------------------------*/
   glPushMatrix();
   for (i = 0; i < 4; i += 1) {
      glRotatef( 90.0, 0.0f, 0.0f, 1.0f);
      glCallList(shape.dl_leaf);
   }
   glPopMatrix();
   /*---(the ring)-------------------------*/
   /*> glCallList(shape.dl_ring);                                                     <*/
   /*---(edge petals)----------------------*/
   glPushMatrix(); {
      glRotatef( 11.5, 0.0f, 0.0f, 1.0f);
      for (i = 0; i < 16; i += 1) {
         glRotatef( 22.5, 0.0f, 0.0f, 1.0f);
         glCallList(shape.dl_edge);
         /*> glPushMatrix(); {                                                           <* 
          *>    glRotatef( 11.2, 0.0f, 0.0f, 1.0f);                                      <* 
          *>    glTranslatef(shape.r_edge * 0.95, 0.0f, 0.0f);                           <* 
          *>    if (i % 2 == 0) {                                                        <* 
          *>       if ((i % 4) == 0)  glColor4f(0.0f, 0.0f, 0.6f, 0.3f);                 <* 
          *>       else               glColor4f(0.0f, 0.0f, 0.6f, 0.2f);                 <* 
          *>       glCallList(shape.dl_balls);                                           <* 
          *>    }                                                                        <* 
          *> } glPopMatrix();                                                            <*/
      }
   } glPopMatrix();
   /*---(edges circles)--------------------*/
   for (i = 0; i < 8; i += 1) {
      if (stroke.help > 0 && stroke.help < 10) {
         switch (stroke.help) {
         case 1 :
            if (i > 1 && i < 7)  continue;
            break;
         case 8 :
            if (i > 0 && i < 6)  continue;
            break;
         default :
            if (stroke.help < i || stroke.help > i + 2)  continue;
            break;
         }
      }
      glPushMatrix(); {
         glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
         glTranslatef (shape.r_edge * 0.95, 0.0f, 0.0f);
         if (stroke.color != 1)  glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
         else if ((i % 2) == 0)  glColor4f (0.0f, 0.0f, 0.8f, 0.2f);
         else                    glColor4f (0.0f, 0.0f, 0.8f, 0.3f);
         glCallList   (shape.dl_balls);
      } glPopMatrix();
   }
   /*---(the buffer)-----------------------*/
   glCallList(shape.dl_buffer);
   /*---(outer)----------------------------*/
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glPushMatrix(); {
         glRotatef    (45 - (i * 45), 0.0f, 0.0f, 1.0f);
         glCallList(shape.dl_outer);
      } glPopMatrix();
      if (stroke.help > 0 && stroke.help < 10) {
         switch (stroke.help) {
         case 1 :
            if (i > 0 && i < 7)  continue;
            break;
         case 8 :
            if (i < 6)           continue;
            break;
         default :
            if (stroke.help < i + 1 || stroke.help > i + 2)  continue;
            break;
         }
      }
      glPushMatrix(); {
         glRotatef    (45 - (i * 45), 0.0f, 0.0f, 1.0f);
         glRotatef    (22.5, 0.0f, 0.0f, 1.0f);
         /*> glTranslatef (shape.r_outer * 0.87, 0.0f, 0.0f);                         <*/
         glTranslatef (shape.r_outer * 0.85, 0.0f, 0.0f);
         if (stroke.color != 1)  glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
         else                    glColor4f (0.6f, 0.0f, 0.6f, 0.3f);
         glCallList(  shape.dl_balls);
      } glPopMatrix();
   }
   glPopMatrix();
   /*---(inner)----------------------------*/
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glPushMatrix(); {
         glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
         glColor4f    (0.7f, 0.7f, 0.7f, 1.0f);
         glCallList   (shape.dl_inner);
      } glPopMatrix();
      if (stroke.help > 0 && stroke.help < 10) {
         if (stroke.help != i + 1)  continue;
      }
      glPushMatrix(); {
         glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
         glTranslatef (shape.r_inner * 0.65, 0.0f, 0.0f);
         if (stroke.color != 1)  glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
         else                    glColor4f (0.6f, 0.0f, 0.3f, 0.3f);
         glCallList   (shape.dl_balls);
      } glPopMatrix();
   }
   glPopMatrix();
   /*---(center)---------------------------*/
   glCallList (shape.dl_center);
   glPushMatrix(); {
      glTranslatef(0.0f, 0.0f, 25.0f);
      if (stroke.color != 1)  glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
      else                    glColor4f (1.0f, 1.0f, 0.0f, 0.4f);
      glCallList (shape.dl_balls);
   } glPopMatrix();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_context (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (stroke.help != 1) {
      DEBUG_GRAF   yLOG_note    ("text is turned off");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (stroke.small   <= SML) {
      DEBUG_GRAF   yLOG_note    ("small mode, no fonts");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_GRAF   yLOG_note    ("using fonts");
#  ifdef   USE_FONTS
   /*> if (font == NULL || font_small == NULL) {                                      <* 
    *>    font_delete();                                                              <* 
    *>    font_load();                                                                <* 
    *> }                                                                              <*/
   glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
   /*---(verions number)--------------------*/
   /*> glRasterPos2f( shape.sz_centerx / 3.0,  shape.sz_centery - (shape.sz_bar * 1.5));          <* 
    *> ftglRenderFont(font_small, VERSION, FTGL_RENDER_ALL);                          <*/
   /*---(working text)----------------------*/
   /*> glRasterPos2f(  -95.0,   93.0);                                                <* 
    *> ftglRenderFont(font_small, stroke_letter, FTGL_RENDER_ALL);                    <*/
   /*---(current writing)-------------------*/
   /*> glRasterPos2f(  -95.0, -108.0);                                                <* 
    *> ftglRenderFont(font_small, "curr :: ", FTGL_RENDER_ALL);                       <* 
    *> glRasterPos2f(  -50.0, -108.0);                                                <* 
    *> ftglRenderFont(font_small, stroke.feedback, FTGL_RENDER_ALL);                     <*/
   /*---(current window)--------------------*/
   /*> glRasterPos2f(  -95.0, -116.0);                                                <* 
    *> ftglRenderFont(font_small, "focu :: ", FTGL_RENDER_ALL);                       <* 
    *> glRasterPos2f(  -50.0, -116.0);                                                <* 
    *> ftglRenderFont(font_small, FOCU_NAME, FTGL_RENDER_ALL);                        <*/
#  endif
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
DRAW_labels (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (stroke.help <  0) {
      DEBUG_GRAF   yLOG_note    ("text is turned off");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(current)--------------------------*/
   glPushMatrix();
   glTranslatef(  0,  0,   75.0);
   yFONT_print (my.txf_bg, my.size_big, YF_MIDCEN, stroke.text);
   glPopMatrix();
   /*---(locals)---------------------------*/
   char  letter[5];
   int   i;
   float r, d;
   float x, y;
   float rad = 0;
   float x_off = shape.r_center / 4.0;
   float y_off = shape.r_center / 5.0;
   glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
   /*---(check for label adjustments)------*/
   char *x_labels = g_letters;
   if      (states[MODE])  x_labels = g_punct;
   else if (states[SHIFT]) x_labels = g_upper;
   /*---(modes)----------------------------*/
   if (stroke.help < 10 || stroke.help == 13) {
      r = shape.r_edge * 1.10;
      for (i = 0; i < 8; i += 1) {
         HELP_ONLY;
         d = i * 45;
         rad = ((float) (d) / 360) * (2 * 3.1415927);
         x = (r * sin(rad));
         y = (r * cos(rad));
         glPushMatrix(); {
            snprintf(letter, 2, "%c", g_special[i]);
            glTranslatef(  x,  y,   75.0);
            yFONT_print (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
         } glPopMatrix();
      }
   }
   /*---(edges)----------------------------*/
   if (stroke.help < 10 || stroke.help == 12) {
      r = shape.r_edge * 1.02;
      for (i = 0; i < 8; i += 1) {
         HELP_ONLY;
         d = (i * 45) - 35;
         rad = ((float) (d) / 360) * (2 * 3.1415927);
         x = (r * sin(rad));
         y = (r * cos(rad));
         if (s_next[(i * 5) + 2] == 0) {
            glPushMatrix();
            snprintf(letter, 2, "%c", x_labels[(i * 5) + 2]);
            /*> printf("label %s @ x=%7.2f, y=%7.2f\n", letter, x, y);                   <*/
            glTranslatef(  x,  y,   75.0);
            yFONT_print (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
            glPopMatrix();
         }
      }
      for (i = 0; i < 8; i += 1) {
         HELP_ONLY;
         d = (i * 45) + 35;
         rad = ((float) (d) / 360) * (2 * 3.1415927);
         x = (r * sin(rad));
         y = (r * cos(rad));
         if (s_next[(i * 5) + 4] == 0) {
            glPushMatrix();
            snprintf(letter, 2, "%c", x_labels[(i * 5) + 4]);
            /*> printf("label %s @ x=%7.2f, y=%7.2f\n", letter, x, y);                   <*/
            glTranslatef(  x,  y,   75.0);
            yFONT_print (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
            glPopMatrix();
         }
      }
   }
   /*---(outer)----------------------------*/
   if (stroke.help < 10 || stroke.help == 11 || stroke.help == 14) {
      r = shape.r_outer  * 0.91;
      for (i = 0; i < 8; i += 1) {
         HELP_ONLY;
         d = (i * 45) - 12;
         rad = ((float) (d) / 360) * (2 * 3.1415927);
         x = (r * sin(rad));
         y = (r * cos(rad));
         if (s_next[(i * 5) + 1] == 0) {
            glPushMatrix();
            snprintf(letter, 2, "%c", x_labels[(i * 5) + 1]);
            /*> printf("label %s @ x=%7.2f, y=%7.2f\n", letter, x, y);                   <*/
            glTranslatef(  x,  y,   75.0);
            yFONT_print (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
            glPopMatrix();
         }
      }
      for (i = 0; i < 8; i += 1) {
         HELP_ONLY;
         d = (i * 45) + 12;
         rad = ((float) (d) / 360) * (2 * 3.1415927);
         x = (r * sin(rad));
         y = (r * cos(rad));
         if (s_next[(i * 5) + 3] == 0) {
            glPushMatrix();
            snprintf(letter, 2, "%c", x_labels[(i * 5) + 3]);
            /*> printf("label %s @ x=%7.2f, y=%7.2f\n", letter, x, y);                   <*/
            glTranslatef(  x,  y,   75.0);
            yFONT_print (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
            glPopMatrix();
         }
      }
   }
   /*---(inner)----------------------------*/
   if (stroke.help < 10 || stroke.help == 10 || stroke.help == 14) {
      r = shape.r_inner  * 0.90;
      for (i = 0; i < 8; i += 1) {
         HELP_ONLY;
         d = i * 45;
         rad = ((float) (d) / 360) * (2 * 3.1415927);
         x = (r * sin(rad));
         y = (r * cos(rad));
         if (s_next[(i * 5)] == 0) {
            glPushMatrix();
            snprintf     (letter, 2, "%c", x_labels[i * 5]);
            glTranslatef (  x,  y,   75.0);
            yFONT_print  (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
            glPopMatrix();
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_locks (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(locals)---------------------------*/
   float   x, y;
   float   z = -20.0;
   /*---(mode)-----------------------------*/
   if (states[MODE] != 0 || locks[MODE] != 0) {
      glPushMatrix();
      glLineWidth(0.8);
      x = - shape.sz_width  / 4;
      y = (shape.sz_height - shape.sz_bar * 2) / 4;
      glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
      if      (locks[MODE]    != 0) glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
      else if (states[MODE]   != 0) glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
      glTranslatef(  x,  y,  z);
      glCallList(shape.dl_box);
      glPopMatrix();
   }
   /*---(shift)----------------------------*/
   if (states[SHIFT] == 1 || locks[SHIFT] == 1) {
      glPushMatrix();
      glLineWidth(0.8);
      x = shape.sz_width  / 4;
      y = (shape.sz_height - shape.sz_bar * 2) / 4;
      glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
      if      (locks[SHIFT]   != 0) glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
      else if (states[SHIFT]  != 0) glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
      glTranslatef(  x,  y,  z);
      glCallList(shape.dl_box);
      glPopMatrix();
   }
   /*---(hublin)---------------------------*/
   if (states[HUBLIN] != 0 || locks[HUBLIN] != 0 || states[MYHUBLIN] != 0) {
      glPushMatrix();
      glLineWidth(0.8);
      x = shape.sz_width  / 4;
      y = - (shape.sz_height - shape.sz_bar * 2) / 4;
      glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
      if      (locks [HUBLIN]   != 0) glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
      else if (states[MYHUBLIN] != 0) glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
      else if (states[HUBLIN]   != 0) glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
      glTranslatef(  x,  y,  z);
      glCallList(shape.dl_box);
      glPopMatrix();
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_arrows (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (stroke.help != 1) {
      DEBUG_GRAF   yLOG_note    ("text is turned off");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(locals)---------------------------*/
   float   r1 = (shape.r_outer + shape.r_edge) / 2.0;
   float   z  = 20.0;
   /*---(up)-----*/
   glPushMatrix();
   glTranslatef(-r1, r1, z);
   glCallList(shape.dl_triangle);
   glPopMatrix();
   /*---(down)---*/
   glPushMatrix();
   glTranslatef( r1, r1, z);
   glRotatef(180.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_triangle);
   glPopMatrix();
   /*---(left)---*/
   glPushMatrix();
   glTranslatef(-r1,-r1, z);
   glRotatef( 90.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_triangle);
   glPopMatrix();
   /*---(right)--*/
   glPushMatrix();
   glTranslatef( r1,-r1, z);
   glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_triangle);
   glPopMatrix();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_current (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(locals)---------------------------*/
   int   r, d;
   int   x, y;
   float rad = 0;
   /*---(draw letter)----------------------*/
   glPushMatrix();
   d = 0;
   r = 0;
   DEBUG_GRAF   yLOG_complex ("using"     , "1=%02d, 2=%02d, 3=%02d", stroke.fst, stroke.snd, stroke.trd);
   glPushMatrix();
   glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
   glTranslatef( 0.0 , 0.0 , 15.00f);
   glCallList(shape.dl_touch);
   glPopMatrix();
   if      (stroke.fst >= 0) {
      glCallList(shape.dl_center);
      r = shape.r_inner * 0.80;
      d = stroke.fst * 45;
      rad = ((float) (d) / 360) * (2 * 3.1415927);
      x = (r * sin(rad));
      y = (r * cos(rad));
      glPushMatrix();
      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
      glTranslatef( x , y , 15.00f);
      glCallList(shape.dl_touch);
      glPopMatrix();
   }
   if (stroke.snd >= 0) {
      r = shape.r_outer * 0.87;
      d = (stroke.snd) * 45.0 + 22.5;
      rad = ((float) (d) / 360) * (2 * 3.1415927);
      x = (r * sin(rad));
      y = (r * cos(rad));
      glPushMatrix();
      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
      glTranslatef( x , y , 15.00f);
      glCallList(shape.dl_touch);
      glPopMatrix();
   }
   if (stroke.trd >= 0) {
      r = shape.r_edge * 0.95;
      d = (stroke.trd) * 45.0;
      rad = ((float) (d) / 360) * (2 * 3.1415927);
      x = (r * sin(rad));
      y = (r * cos(rad));
      glPushMatrix();
      glTranslatef( x , y , 15.00f);
      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
      glCallList(shape.dl_touch);
      glPopMatrix();
   }
   /*> if (stroke.fth >= 0) {                                                            <* 
    *>    r = (shape.r_edge  + shape.r_max) / 2;                                        <* 
    *>    d = (stroke.fth) * 90.0 + 45;                                                  <* 
    *>    rad = ((float) (d) / 360) * (2 * 3.1415927);                                <* 
    *>    x = (r * sin(rad));                                                         <* 
    *>    y = (r * cos(rad));                                                         <* 
    *>    glPushMatrix();                                                             <* 
    *>    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);                                          <* 
    *>    glTranslatef( x , y , 15.00f);                                              <* 
    *>    glCallList(shape.dl_touch);                                                       <* 
    *>    glPopMatrix();                                                              <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_navigation         (void)
{
   /*---(locals)----------------------------*/
   float       x_top, x_bot, x_mid;
   float       x_lef, x_rig, x_cen, x_inc;
   float       z;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(vertical)--------------------------*/
   x_top  = shape.sz_nav;
   x_bot  = 0;
   x_mid  = shape.sz_nav / 2.0;
   /*---(horizontal)------------------------*/
   x_lef  = 0;
   x_rig  = shape.sz_width;
   x_cen  = shape.sz_width / 2.0;
   x_inc  = shape.sz_width / 8.0;
   /*---(depth)-----------------------------*/
   z =   20.0;
   /*---(bottom shaded area)----------------*/
   glColor4f  (0.5f, 0.5f, 0.5f, 1.0f);
   glBegin    (GL_POLYGON); {
      glVertex3f ( x_lef, x_top, z);
      glVertex3f ( x_rig, x_top, z);
      glVertex3f ( x_rig, x_bot, z);
      glVertex3f ( x_lef, x_bot, z);
   } glEnd();
   /*---(move up)------------------------*/
   z += 5;
   /*---(prev workspace)-----------------*/
   glPushMatrix (); {
      glColor4f    (0.6f, 0.6f, 0.6f, 1.0f);
      glTranslatef (x_inc * ++n, x_mid,  z);
      glRotatef    (  90.0, 0.0f, 0.0f, 1.0f);
      glCallList   (shape.dl_arrow);
      glTranslatef (   0.0,  x_inc / 4.0,  0.0);
      glCallList   (shape.dl_arrow);
   } glPopMatrix ();
   /*---(prev window)--------------------*/
   glPushMatrix (); {
      glColor4f    (0.6f, 0.6f, 0.6f, 1.0f);
      glTranslatef (x_inc * ++n, x_mid,  z);
      glRotatef    (  90.0, 0.0f, 0.0f, 1.0f);
      glCallList   (shape.dl_arrow);
   } glPopMatrix ();
   /*---(hyper key)----------------------*/
   glPushMatrix (); {
      glColor4f    (0.6f, 0.6f, 0.6f, 1.0f);
      if (states[HYPER] != 0) glColor4f (1.0f, 1.0f, 0.0f, 0.7f);
      glTranslatef (x_inc * ++n, x_mid,  z);
      glRotatef    (   0.0, 0.0f, 0.0f, 1.0f);
      glCallList   (shape.dl_arrow);
   } glPopMatrix ();
   /*---(belly)--------------------------*/
   glPushMatrix (); {
      glColor4f    (0.6f, 0.6f, 0.6f, 1.0f);
      if (stroke.help == 1)       glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
      glTranslatef (x_inc * ++n, x_mid,  z);
      glCallList   (shape.dl_belly);
   } glPopMatrix ();
   /*---(super key)----------------------*/
   glPushMatrix (); {
      glColor4f    (0.6f, 0.6f, 0.6f, 1.0f);
      if (states[SUPER] != 0) glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
      glTranslatef (x_inc * ++n, x_mid,  z);
      glRotatef    ( -180.0, 0.0f, 0.0f, 1.0f);
      glCallList   (shape.dl_arrow);
   } glPopMatrix ();
   /*---(next window)--------------------*/
   glPushMatrix (); {
      glColor4f    (0.6f, 0.6f, 0.6f, 1.0f);
      glTranslatef (x_inc * ++n, x_mid,  z);
      glRotatef    ( -90.0, 0.0f, 0.0f, 1.0f);
      glCallList   (shape.dl_arrow);
   } glPopMatrix ();
   /*---(next workspace)-----------------*/
   glPushMatrix (); {
      glColor4f    (0.6f, 0.6f, 0.6f, 1.0f);
      glTranslatef (x_inc * ++n, x_mid,  z);
      glRotatef    ( -90.0, 0.0f, 0.0f, 1.0f);
      glCallList   (shape.dl_arrow);
      glTranslatef (   0.0, x_inc / 4.0,  0.0);
      glCallList   (shape.dl_arrow);
   } glPopMatrix ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

long
time_stamp()                      /* PURPOSE : timestamp in microseconds      */
{
   /* second
    * millisecond  ms  0.001 sec
    * microsecond  us  0.000001 sec
    * nanosecond   ns  0.000000001 sec
    * picosecond   ps  0.000000000001 sec
    */
   long             tint = 0;
   struct timeval   tv;
   gettimeofday(&tv, NULL);
   tint += (int) (tv.tv_sec * 1000);
   tint += (int) tv.tv_usec / 1000;
   return tint;

}



/*============================-----end-of-file----============================*/
