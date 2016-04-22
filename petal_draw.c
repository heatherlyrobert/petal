/*============================[[    beg-code    ]]============================*/
#include    "petal.h"






/*============================--------------------============================*/
/*===----                        initialization                        ----===*/
/*============================--------------------============================*/
static void      o___SETUP___________________o (void) {;}

char
DRAW_init          (void)
{
   DEBUG_PROG    printf("DRAW_init()\n\n");
   /*---(clearing)-----------------------*/
   glClearColor  (0.7f, 0.7f, 0.7f, 1.0f);       /* nice medium green          */
   glClearDepth  (1.0f);
   /*---(basics)-------------------------*/
   glShadeModel  (GL_SMOOTH);
   glEnable      (GL_TEXTURE_2D);    /* NEW */
   glEnable      (GL_DEPTH_TEST);
   glDepthFunc   (GL_LEQUAL);
   /*---(blending)-----------------------*/
   glEnable      (GL_ALPHA_TEST);
   glAlphaFunc   (GL_GEQUAL, 0.0125);
   glEnable      (GL_BLEND);
   glBlendFunc   (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint        (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   /*---(polygon antialiasing)-----------*/
   glEnable      (GL_POLYGON_SMOOTH);
   glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
   glHint        (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   /*---(wrap)---------------------------*/
   glFlush();
   DRAW_resize   (shape.sz_width, shape.sz_height);
   return 0;
}



/*============================--------------------============================*/
/*===----                        event loop                            ----===*/
/*============================--------------------============================*/
static void      o___LOOP____________________o (void) {;}

char
DRAW_main          (void)
{
   DEBUG_GRAF    printf("DRAW_main()\n");
   /*---(start)----------------------------*/
   long  x_start, x_stop;
   x_start = time_stamp();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   /*---(draw)-----------------------------*/
   DRAW_image();
   DRAW_labels();
   DRAW_current();
   DRAW_locks();
   DRAW_arrows();
   DRAW_navigation();
   DRAW_context();
   /*> DRAW_dots();                                                                   <*/
   /*---(force the redraw)-----------------*/
   glXSwapBuffers(DISP, BASE);
   glFlush();
   /*---(complete)-------------------------*/
   x_stop  = time_stamp();
   DEBUG_GRAF    printf("   - done, drawing took %ld ms\n\n", x_stop - x_start);
   return 0;
}

char
DRAW_resize        (uint a_w, uint a_h)
{
   DEBUG_GRAF    printf("DRAW_resize(%dw, %dh)\n", a_w, a_h);
   if (a_h == 0) a_h = 1;
   WIDTH   = a_w;
   HEIGHT  = a_h;
   glViewport(0,  0, WIDTH, HEIGHT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float  x_lef   = shape.sz_centerx;
   float  x_rig   = shape.sz_centerx;
   float  x_top   = shape.sz_centery + shape.sz_ctl;
   float  x_bot   = shape.sz_centery + shape.sz_nav;
   glOrtho( -x_lef       ,  x_rig, -x_bot,  x_top, -100.0,  100.0);
   glMatrixMode(GL_MODELVIEW);
   return 0;
}

char
DRAW_dots          (void)
{
   DEBUG_GRAF    printf("   - DRAW_dots()         ");
   /*---(locals)---------------------------*/
   int   i;
   /*---(leaves)---------------------------*/
   glPushMatrix();
   glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
   glLineWidth(shape.r_dots);
   glBegin(GL_LINE_STRIP);
   for (i = 0; i < ndots; i += 1) {
      glVertex3f( dots[i].x, dots[i].y,   4.00f);
   }
   glEnd();
   glLineWidth(0.8);
   glPopMatrix();
   /*---(complete)-------------------------*/
   DEBUG_GRAF    printf(" : complete...\n");
   return 0;
}

char
DRAW_image (void)
{
   /*> glCallList(shape.dl_back);                                                           <*/
   DEBUG_GRAF    printf("   - DRAW_image()        ");
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
   glCallList(shape.dl_ring);
   /*---(edges)----------------------------*/
   glPushMatrix();
   glRotatef( 11.5, 0.0f, 0.0f, 1.0f);
   for (i = 0; i < 16; i += 1) {
      glRotatef( 22.5, 0.0f, 0.0f, 1.0f);
      glCallList(shape.dl_edge);
      glPushMatrix(); {
         glRotatef( 11.2, 0.0f, 0.0f, 1.0f);
         glTranslatef(shape.r_edge * 0.95, 0.0f, 0.0f);
         glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
         if (i % 2 == 0) glCallList(shape.dl_balls);
      } glPopMatrix();
   }
   glPopMatrix();
   /*---(the buffer)-----------------------*/
   glCallList(shape.dl_buffer);
   /*---(outer)----------------------------*/
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glRotatef( 45.0, 0.0f, 0.0f, 1.0f);
      glCallList(shape.dl_outer);
      glPushMatrix(); {
         glRotatef( 22.5, 0.0f, 0.0f, 1.0f);
         glTranslatef(shape.r_outer * 0.87, 0.0f, 0.0f);
         glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
         glCallList(shape.dl_balls);
      } glPopMatrix();
   }
   glPopMatrix();
   /*---(inner)----------------------------*/
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
      glCallList(shape.dl_inner);
      glPushMatrix(); {
         glTranslatef(shape.r_inner * 0.80, 0.0f, 0.0f);
         glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
         glCallList(shape.dl_balls);
      } glPopMatrix();
      glRotatef(-45.0, 0.0f, 0.0f, 1.0f);
   }
   glPopMatrix();
   /*---(center)---------------------------*/
   glCallList(shape.dl_center);
   /*---(complete)-------------------------*/
   DEBUG_GRAF    printf(" : complete...\n");
   return 0;
}

char
DRAW_context (void)
{
   DEBUG_GRAF    printf("   - DRAW_context()      ");
   if (stroke.help != 1) {
      DEBUG_GRAF    printf(" : text is not turned on...\n");
      return 0;
   }
   if (stroke.small   <= SML) {
      DEBUG_GRAF    printf(" : small mode...\n");
      return 0;
   }
   DEBUG_GRAF    printf(" : use fonts...\n");
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
   /*---(complete)-------------------------*/
   DEBUG_GRAF    printf("   - DRAW_context()       : complete\n");
   return 0;
}

char
DRAW_labels (void)
{
   /*---(current)--------------------------*/
   glPushMatrix();
   glTranslatef(  0,  0,   75.0);
   yFONT_print (my.txf_bg, my.size_big, YF_MIDCEN, stroke.text);
   glPopMatrix();
   /*---(check for others)-----------------*/
   DEBUG_GRAF    printf("   - DRAW_labels()       ");
   if (stroke.help != 1) {
      DEBUG_GRAF    printf(" : text is not turned on...\n");
      return 0;
   }
   /*---(locals)---------------------------*/
   char  letter[5];
   int   i;
   float r, d;
   float x, y;
   float rad = 0;
   float x_off = shape.r_center / 4.0;
   float y_off = shape.r_center / 5.0;
   glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
   /*---(check for label adjustments)------*/
   char *x_labels = g_letters;
   if      (states[MODE])  x_labels = g_punct;
   else if (states[SHIFT]) x_labels = g_upper;
   /*---(modes)----------------------------*/
   glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
   r = shape.r_edge + 10;
   for (i = 0; i < 8; i += 1) {
      d = i * 45;
      rad = ((float) (d) / 360) * (2 * 3.1415927);
      x = (r * sin(rad));
      y = (r * cos(rad));
      glPushMatrix();
      snprintf(letter, 2, "%c", g_special[i]);
      glTranslatef(  x,  y,   75.0);
      yFONT_print (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
      glPopMatrix();
   }
   /*---(edges)----------------------------*/
   r = shape.r_edge + 2;
   for (i = 0; i < 8; i += 1) {
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
   /*---(outer)----------------------------*/
   r = shape.r_buffer + 2;
   for (i = 0; i < 8; i += 1) {
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
   /*---(inner)----------------------------*/
   r = shape.r_center + 5;
   for (i = 0; i < 8; i += 1) {
      d = i * 45;
      rad = ((float) (d) / 360) * (2 * 3.1415927);
      x = (r * sin(rad));
      y = (r * cos(rad));
      if (s_next[(i * 5)] == 0) {
         glPushMatrix();
         snprintf(letter, 2, "%c", x_labels[i * 5]);
         glTranslatef(  x,  y,   75.0);
         yFONT_print (my.txf_sm, my.size_norm, YF_MIDCEN, letter);
         glPopMatrix();
      }
   }
   /*---(complete)-------------------------*/
   DEBUG_GRAF    printf("   - DRAW_labels()        : complete...\n");
   return 0;
}

char
DRAW_locks (void)
{
   DEBUG_GRAF    printf("   - DRAW_locks()        ");
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
   /*---(complete)-------------------------*/
   DEBUG_GRAF    printf(" : complete...\n");
   return 0;
}

char
DRAW_arrows (void)
{
   DEBUG_GRAF    printf("   - DRAW_arrows()       ");
   if (stroke.help != 1) {
      DEBUG_GRAF    printf(" : text is not turned on...\n");
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
   /*---(complete)-------------------------*/
   DEBUG_GRAF    printf(" : complete...\n");
   return 0;
}

char
DRAW_current (void)
{
   DEBUG_GRAF    printf("   - DRAW_current()      ");
   /*---(locals)---------------------------*/
   int   r, d;
   int   x, y;
   float rad = 0;
   /*---(draw letter)----------------------*/
   glPushMatrix();
   d = 0;
   r = 0;
   DEBUG_GRAF    printf(" : using 1=%02d, 2=%02d, 3=%02d", stroke.fst, stroke.snd, stroke.trd);
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
   /*---(complete)-------------------------*/
   DEBUG_GRAF    printf(" : complete...\n");
   return 0;
}

char
DRAW_navigation (void)
{
   DEBUG_GRAF    printf("   - DRAW_navigation()   ");
   /*---(locals)----------------------------*/
   float  x_top  = - shape.sz_centery;
   float  x_bot  = - shape.sz_centery - shape.sz_nav;
   float  x_lef  = shape.sz_centerx - shape.sz_width;
   float  x_rig  = shape.sz_width   - shape.sz_centerx;
   float  y_cen  = - shape.sz_centery - (shape.sz_nav / 2.0);
   float  x_inc  = shape.sz_centerx / 3.5;
   float  x_cen  = shape.sz_centerx - (x_inc / 2.0);
   float  z = -20.0;
   /*---(start)-----------------------------*/
   glPushMatrix();
   /*> glTranslatef( 0.0, x_bot - x_top ,  0.0);                                      <*/
   /*---(bottom shaded area)----------------*/
   glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
   glBegin(GL_POLYGON);
   glVertex3f( x_lef, x_top, z);
   glVertex3f( x_rig, x_top, z);
   glVertex3f( x_rig, x_bot, z);
   glVertex3f( x_lef, x_bot, z);
   glEnd();
   /*---(move to top point)-----------------*/
   /*> glTranslatef( 0.0, x_bot - x_top ,  0.0);                                      <*/
   /*---(fluxbox movement arrows)-----------*/
   /* prev workspace   */
   glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
   glPushMatrix();
   glTranslatef( -x_cen , y_cen ,  0.0);
   glRotatef(  90.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_arrow);
   glTranslatef(   0.0,  -(x_inc / 4.0) ,  0.0);
   glCallList(shape.dl_arrow);
   glPopMatrix();
   /* prev window      */
   glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
   glPushMatrix();
   glTranslatef( -x_cen + x_inc, y_cen ,  0.0);
   glRotatef(  90.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_arrow);
   glPopMatrix();
   /* hyper            */
   glPushMatrix();
   glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
   if (states[HYPER] != 0) glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
   glTranslatef( -x_inc , (y_cen * 0.995),  0.0);
   glRotatef(   0.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_arrow);
   glPopMatrix();
   /* belly            */
   glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
   if (stroke.help == 1)       glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
   glPushMatrix();
   glTranslatef(   0.0, y_cen,  0.0);
   glCallList(shape.dl_belly);
   glPopMatrix();
   /* super            */
   glPushMatrix();
   glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
   if (states[SUPER] != 0) glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
   glTranslatef(  x_inc,  (y_cen * 1.005),  0.0);
   glRotatef( -180.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_arrow);
   glPopMatrix();
   /* next window      */
   glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
   glPushMatrix();
   glTranslatef(  x_cen - x_inc, y_cen,  0.0);
   glRotatef( -90.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_arrow);
   glPopMatrix();
   /* next workspace   */
   glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
   glPushMatrix();
   glTranslatef( x_cen, y_cen,  0.0);
   glRotatef( -90.0, 0.0f, 0.0f, 1.0f);
   glCallList(shape.dl_arrow);
   glTranslatef(   0.0, -(x_inc / 4.0),  0.0);
   glCallList(shape.dl_arrow);
   glPopMatrix();
   /*---(complete)-------------------------*/
   glPopMatrix();
   DEBUG_GRAF    printf(" : complete...\n");
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
