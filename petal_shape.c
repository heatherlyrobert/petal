/*============================[[    beg-code    ]]============================*/
#include    "petal.h"


tSHAPES       shape;




/*===[[ prototypes ]]===============================================*/
char       displist_center     (void);
char       SHAPE_ring          (void);
char       displist_inner      (void);
char       SHAPE_buffer        (void);
char       displist_outer      (void);
char       displist_edge       (void);
char       displist_leaf       (void);

char       displist_curr       (void);
char       displist_box        (void);
char       displist_triangle   (void);
char       displist_arrow      (void);
char       displist_belly      (void);
char       displist_orient     (void);
char       displist_balls      (void);

char       displist_touch      (void);
char       displist_touch2     (void);
char       displist_back       (void);



/*============================--------------------============================*/
/*===----                        general sizing                        ----===*/
/*============================--------------------============================*/
static void      o___SIZING__________________o (void) {;}

char       /*---: establish the size -----------------s-----------------------*/
SHAPE_base         (float a_ratio)
{
   /*---(base sizes)---------------------*/
   shape.sz_centery    = 100.0 * a_ratio;
   shape.sz_centerx    = 100.0 * a_ratio;
   shape.sz_bar        =  20.0 * a_ratio;
   /*---(calc sizes)---------------------*/
   shape.sz_ctl        =     0;
   /*> shape.sz_nav        =   shape.sz_bar;                                          <*/
   shape.sz_nav        =     0;
   my.w_tall           =  (shape.sz_centery * 2) + shape.sz_ctl + shape.sz_nav;
   my.w_wide           =  (shape.sz_centerx * 2);
   /*---(image sizes)--------------------*/
   shape.r_center      =  25.0 * a_ratio;
   shape.r_ring        =  28.0 * a_ratio;
   shape.r_inner       =  50.0 * a_ratio;
   shape.r_buffer      =  57.0 * a_ratio;
   shape.r_outer       =  75.0 * a_ratio;
   shape.r_edge        =  85.0 * a_ratio;
   shape.r_max         = 100.0 * a_ratio;
   /*---(drawing sizes)------------------*/
   shape.r_lines       =   0.8 * a_ratio;
   shape.r_dots        =   5.0 * a_ratio;
   shape.r_curr        =   7.0 * a_ratio;
   shape.r_trace       =   2.5 * a_ratio;
   /*---(fonts)--------------------------*/
   my.size_big         =  32.0 * a_ratio;
   my.size_norm        =   8.0 * a_ratio;   /* was 10 for courier */
   /*---(display lists)------------------*/
   displist_free();
   displist_init();
   /*---(complete)-----------------------*/
   return 0;
}

char SHAPE_giant         (void) { stroke.small = GIA; SHAPE_base (2.00); return 0; }
char SHAPE_huge          (void) { stroke.small = HUG; SHAPE_base (1.50); return 0; }
char SHAPE_large         (void) { stroke.small = LRG; SHAPE_base (1.25); return 0; }
char SHAPE_normal        (void) { stroke.small = NOR; SHAPE_base (1.00); return 0; }
char SHAPE_medium        (void) { stroke.small = MED; SHAPE_base (0.85); return 0; }
char SHAPE_small         (void) { stroke.small = SML; SHAPE_base (0.70); return 0; }
char SHAPE_tiny          (void) { stroke.small = TNY; SHAPE_base (0.60); return 0; }

char
SHAPE_size              (char *a_size)
{
   switch (a_size [0]) {
   case 'g' :  SHAPE_giant  ();    break;
   case 'h' :  SHAPE_huge   ();    break;
   case 'l' :  SHAPE_large  ();    break;
   case 'n' :  SHAPE_normal ();    break;
   case 'm' :  SHAPE_medium ();    break;
   case 's' :  SHAPE_small  ();    break;
   case 't' :  SHAPE_tiny   ();    break;
   default  :  SHAPE_normal ();    break;
   }
   yVIEW_resize (my.w_wide, my.w_tall, 0);
   return 0;
}



/*============================--------------------============================*/
/*===----                      display list setup                      ----===*/
/*============================--------------------============================*/

char
displist_init(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   shape.r_button = (shape.sz_bar / 2.5);
   /*--(petals)---------------------------*/
   ARTSY__center (shape.r_center, 20.0, &(shape.dl_center));
   /*> displist_center     ();                                                        <*/
   SHAPE_ring          ();
   ARTSY__inner  (shape.r_inner , 15.0, &(shape.dl_inner));
   /*> displist_inner      ();                                                        <*/
   SHAPE_buffer        ();
   ARTSY__outer  (shape.r_outer , 10.0, &(shape.dl_outer));
   /*> displist_outer      ();                                                        <*/
   ARTSY__edge   (shape.r_edge  ,  5.0, &(shape.dl_edge));
   /*> displist_edge       ();                                                        <*/
   displist_leaf       ();
   /*--(current)--------------------------*/
   displist_curr       ();
   displist_box        ();
   ARTSY__ball   (shape.r_center / 5.0, 50.0, &(shape.dl_balls));
   /*> displist_balls      ();                                                        <*/
   displist_touch      ();
   displist_touch2     ();
   displist_back       ();
   /*--(navigation)-----------------------*/
   displist_triangle   ();
   displist_arrow      ();
   displist_belly      ();
   displist_orient     ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_free (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   glDeleteLists (shape.dl_center,  1);
   glDeleteLists (shape.dl_ring ,   1);
   glDeleteLists (shape.dl_inner,   1);
   glDeleteLists (shape.dl_buffer,  1);
   glDeleteLists (shape.dl_outer,   1);
   glDeleteLists (shape.dl_edge,    1);
   glDeleteLists (shape.dl_leaf,    1);
   glDeleteLists (shape.dl_curr,    1);
   glDeleteLists (shape.dl_box,     1);
   glDeleteLists (shape.dl_balls,   1);
   glDeleteLists (shape.dl_touch,   1);
   glDeleteLists (shape.dl_touch2,  1);
   glDeleteLists (shape.dl_back,    1);
   glDeleteLists (shape.dl_triangle,1);
   glDeleteLists (shape.dl_arrow,   1);
   glDeleteLists (shape.dl_belly,   1);
   glDeleteLists (shape.dl_orient,  1);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_curr(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_curr = glGenLists(1);
   glNewList(shape.dl_curr, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r  = shape.r_curr;
   float   z  = 5.00;
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON);
   glColor4f(1.0f, 0.5f, 0.0f, 0.2f);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   =  r * cos(rad);
      y   =  r * sin(rad);
      glVertex3f( x, y, z);
   }
   glEnd();
   /*---(outline)---------------------------*/
   glBegin(GL_LINE_STRIP);
   glLineWidth(shape.r_lines);
   glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   =  r * cos(rad);
      y   =  r * sin(rad);
      glVertex3f( x, y, z + 1);
   }
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                            petals                            ----===*/
/*====================------------------------------------====================*/
static void      o___PETALS__________________o (void) {;}

char
displist_center(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_center = glGenLists(1);
   glNewList(shape.dl_center, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r  = shape.r_center;
   float   z  =  20.00;
   /*---(interior)--------------------------*/
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
   glBegin(GL_POLYGON); {
      for (d = 0; d <= 360; d += 10) {
         rad = d * DEG2RAD;
         x   = r * cos(rad);
         y   = r * sin(rad);
         glVertex3f ( x, y, z);
      }
   } glEnd();
   /*---(inside star)-----------------------*/
   glLineWidth (shape.r_lines);
   glColor4f   (0.0f, 0.5f, 0.0f, 0.5f);
   glBegin (GL_LINE_STRIP); {
      for (d = 0; d <= 360; d += 15) {
         rad = d * DEG2RAD;
         x   = r * cos(rad) * (((((int) d) % 45) == 0) ? 0.6f : 0.4f);
         y   = r * sin(rad) * (((((int) d) % 45) == 0) ? 0.6f : 0.4f);
         glVertex3f ( x, y, z + 2);
      }
   } glEnd();
   /*---(outline)---------------------------*/
   glBegin(GL_LINE_STRIP); {
      for (d = 0; d < 360; d += 2) {
         rad = d * DEG2RAD;
         x   = r * cos(rad);
         y   = r * sin(rad);
         glVertex3f ( x, y, z + 2);
      }
   } glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_inner     (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_inner = glGenLists(1);
   glNewList(shape.dl_inner, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r  = shape.r_inner;
   float   z  = -15.00;
   /*---(interior)--------------------------*/
   glColor4f   (1.0f, 1.0f, 0.0f, 0.2f);
   glBegin (GL_POLYGON); {
      glVertex3f ( 0.0, 0.0, z);
      for (d = -22; d < 22; d+=6) {
         rad = d * DEG2RAD;
         x   = r * cos(rad);
         y   = r * sin(rad);
         glVertex3f ( x, y, z);
      }
      glVertex3f ( 0.0, 0.0, z);
   } glEnd ();
   /*---(outline)---------------------------*/
   glLineWidth (shape.r_lines);
   glColor4f   (0.0f, 0.5f, 0.0f, 0.5f);
   glBegin (GL_LINE_STRIP); {
      glVertex3f ( 0.0, 0.0, z + 5);
      for (d = -22; d < 22; d+=6) {
         rad = d * DEG2RAD;
         x   = r * cos(rad);
         y   = r * sin(rad);
         glVertex3f ( x, y, z + 5);
      }
      glVertex3f ( 0.0, 0.0, z + 5);
   } glEnd ();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_outer(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_outer = glGenLists(1);
   glNewList(shape.dl_outer, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   z = -25.0;
   /*---(interior)--------------------------*/
   glColor4f   (0.0f, 1.0f, 0.0f, 0.2f);
   glBegin (GL_POLYGON); {
      glVertex3f ( 0.0, 0.0, z);
      for (d = 1; d <  44; d+=6) {
         rad = d * DEG2RAD;
         x   = shape.r_outer * cos(rad);
         y   = shape.r_outer * sin(rad);
         glVertex3f ( x, y, z);
      }
      glVertex3f ( 0.0, 0.0, z);
   } glEnd ();
   /*---(begin)-----------------------------*/
   glLineWidth (shape.r_lines);
   glColor4f   (0.0f, 0.5f, 0.0f, 0.5f);
   glBegin (GL_LINE_STRIP); {
      glVertex3f ( 0.0, 0.0, z + 1);
      for (d = 1; d <  44; d+=6) {
         rad = d * DEG2RAD;
         x   = shape.r_outer * cos(rad);
         y   = shape.r_outer * sin(rad);
         glVertex3f ( x, y, z);
      }
      glVertex3f ( 0.0, 0.0, z + 1);
   } glEnd ();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   /*---(complete)--------------------------*/
   return 0;
}

char
displist_edge           (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_edge = glGenLists(1);
   glNewList(shape.dl_edge, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   x, y;
   float   rad;
   float   r1 = shape.r_outer;
   float   r2 = (shape.r_outer * 0.35) + (shape.r_edge * 0.65);
   float   r3 = shape.r_edge;
   float   z  = -30.00;
   glLineWidth (shape.r_lines);
   glColor4f   (0.0f, 0.5f, 0.0f, 0.5f);
   glBegin (GL_LINE_STRIP); {
      /*---(start line)------------------*/
      d   = 12.0;
      rad = d  * DEG2RAD;
      x   = r1 * cos(rad);
      y   = r1 * sin(rad);
      glVertex3f( x, y, z);
      x   = r3 * cos(rad);
      y   = r3 * sin(rad);
      glVertex3f( x, y, z);
      /*---(point)-----------------------*/
      d   = 22.0;
      rad = d  * DEG2RAD;
      x   = r2 * cos(rad);
      y   = r2 * sin(rad);
      glVertex3f( x, y, z);
      /*---(end line)--------------------*/
      d   = 31.5;
      rad = d  * DEG2RAD;
      x   = r3 * cos(rad);
      y   = r3 * sin(rad);
      glVertex3f( x, y, z);
      x   = r1 * cos(rad);
      y   = r1 * sin(rad);
      glVertex3f( x, y, z);
      /*---(end)-------------------------*/
   } glEnd();
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
SHAPE_ring         (void)
{
   /*---(locals)-----------+-----------+-*/
   float       d;
   float       rad;
   float       x, y;
   float       z           = -33.00;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(prepare)---------------------------*/
   shape.dl_ring = glGenLists(1);
   glNewList (shape.dl_ring, GL_COMPILE);
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON);
   glColor4f(0.4f, 0.4f, 0.4f, 0.3f);
   for (d = 0; d <= 360; d += 15) {
      rad = d * DEG2RAD;
      x   = shape.r_ring * cos(rad);
      y   = shape.r_ring * sin(rad);
      glVertex3f( x, y, z);
   }
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
SHAPE_buffer       (void)
{
   /*---(locals)----------------------------*/
   int     d;
   float   rad;
   float   x, y;
   float   r1 = shape.r_buffer;
   float   r2 = (shape.r_inner * 0.25) + (shape.r_buffer * 0.75);
   float   z  = -30.00;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_buffer = glGenLists(1);
   glNewList (shape.dl_buffer, GL_COMPILE);
   /*---(exterior)--------------------------*/
   glBegin(GL_LINE_STRIP);
   glLineWidth(shape.r_lines);
   glColor4f(0.4f, 0.4f, 0.4f, 0.4f);
   for (d = 0; d <= 360; d +=  5) {
      rad = d * DEG2RAD;
      if ((int) d % 45 == 0) {
         x   = r1 * cos (rad) * 1.05;
         y   = r1 * sin (rad) * 1.05;
      } else {
         x   = r1 * cos(rad);
         y   = r1 * sin(rad);
      }
      glVertex3f( x, y, z);
   }
   glEnd();
   /*---(exterior)--------------------------*/
   glBegin(GL_LINE_STRIP);
   glLineWidth(shape.r_lines);
   glColor4f(0.4f, 0.4f, 0.4f, 0.4f);
   for (d = 0; d <= 360; d +=  5) {
      rad = d * DEG2RAD;
      if ((int) d % 45 == 0) {
         x   = r1 * cos(rad) * 1.07;
         y   = r1 * sin(rad) * 1.07;
      } else {
         x   = r1 * cos(rad) * 1.02;
         y   = r1 * sin(rad) * 1.02;
      }
      glVertex3f( x, y, z);
      /*> x   = r2 * cos(rad);                                                        <* 
       *> y   = r2 * sin(rad);                                                        <* 
       *> glVertex3f( x, y, z);                                                       <*/
   }
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_leaf           (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_leaf   = glGenLists(1);
   glNewList(shape.dl_leaf, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   r1 = shape.r_center / 2.0;
   float   r2 = shape.r_center / 4.0;
   float   r3 = shape.r_inner;
   float   r4 = shape.r_edge;
   float   r5 = shape.r_edge + r2;
   float   z  = -40.00;
   /*---(interior)--------------------------*/
   glColor4f   (1.0f, 1.0f, 1.0f, 1.0f);
   glBegin (GL_POLYGON); {
      glVertex3f  ( r1, r1, z);
      glVertex3f  ( r2, r3, z);
      glVertex3f  ( r1, r5, z);
      glVertex3f  ( r3, r4, z);
      glVertex3f  ( r5, r5, z);
      glVertex3f  ( r4, r3, z);
      glVertex3f  ( r5, r1, z);
      glVertex3f  ( r3, r2, z);
      glVertex3f  ( r1, r1, z);
   } glEnd ();
   /*---(outline)---------------------------*/
   glLineWidth (shape.r_lines);
   glColor4f   (0.0f, 0.5f, 0.0f, 0.5f);
   glBegin (GL_LINE_STRIP); {
      glVertex3f  ( r1, r1, z);
      glVertex3f  ( r2, r3, z);
      glVertex3f  ( r1, r5, z);
      glVertex3f  ( r3, r4, z);
      glVertex3f  ( r5, r5, z);
      glVertex3f  ( r4, r3, z);
      glVertex3f  ( r5, r1, z);
      glVertex3f  ( r3, r2, z);
      glVertex3f  ( r1, r1, z);
   } glEnd ();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_box(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_box = glGenLists(1);
   glNewList(shape.dl_box, GL_COMPILE);
   /*---(locals)----------------------------*/
   /*> float   r1 =  shape.r_center / 1.5;                                             <*/
   float   r1 =  my.w_wide / 4;
   float   z  =   50.00;
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON);
   glVertex3f( -r1, -r1, z);
   glVertex3f( -r1,  r1, z);
   glVertex3f(  r1,  r1, z);
   glVertex3f(  r1, -r1, z);
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_triangle(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_triangle = glGenLists(1);
   glNewList(shape.dl_triangle, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   r1 =  shape.r_center / 3.0;
   float   z  =  20.00;
   /*---(exterior)--------------------------*/
   glBegin(GL_LINE_STRIP);
   glLineWidth(shape.r_lines);
   glColor4f(0.3f, 0.3f, 0.3f, 0.5f);
   glVertex3f( -r1, -r1, z);
   glVertex3f( 0.0,  r1, z);
   glVertex3f(  r1, -r1, z);
   glVertex3f( -r1, -r1, z);
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_arrow          (void)
{
   /*---(locals)-----------+-----------+--+-*/
   float       r1          = shape.r_button;
   float       z           = -5.00;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_arrow = glGenLists(1);
   glNewList(shape.dl_arrow, GL_COMPILE);
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON); {
      glVertex3f ( -r1, -r1, z);
      glVertex3f ( 0.0,  r1, z);
      glVertex3f (  r1, -r1, z);
      glVertex3f ( -r1, -r1, z);
   } glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_touch2(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_touch2 = glGenLists(1);
   glNewList(shape.dl_touch2, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r  =  shape.r_center / 5.0;
   float   z  =  -5.00;
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   =  r * cos(rad);
      y   =  r * sin(rad);
      glVertex3f( x, y, z);
   }
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_back (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_back   = glGenLists(1);
   glNewList(shape.dl_back, GL_COMPILE);
   /*---(locals)---------------------------*/
   float   r  =  shape.r_center / 1.5;
   int     i;
   /*---(edges)----------------------------*/
   r = (shape.r_edge  + shape.r_max ) / 2;
   glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
   glPushMatrix();
   glRotatef(-45.0, 0.0f, 0.0f, 1.0f);
   for (i = 0; i < 4; i += 1) {
      glPushMatrix();
      glTranslatef(r, 0.0f, 0.0f);
      glCallList(shape.dl_touch2);
      glPopMatrix();
      glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
   }
   glPopMatrix();
   /*---(edges)----------------------------*/
   r = (shape.r_outer + shape.r_edge) / 2;
   glColor4f(0.5f, 0.0f, 0.0f, 1.0f);
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glPushMatrix();
      glTranslatef(r, 0.0f, 0.0f);
      glCallList(shape.dl_touch2);
      glPopMatrix();
      glRotatef(-45.0, 0.0f, 0.0f, 1.0f);
   }
   glPopMatrix();
   /*---(outer)----------------------------*/
   r = (shape.r_inner + shape.r_outer) / 2;
   glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
   glPushMatrix();
   glRotatef(-23.0, 0.0f, 0.0f, 1.0f);
   for (i = 0; i < 8; i += 1) {
      glPushMatrix();
      glTranslatef(r, 0.0f, 0.0f);
      glCallList(shape.dl_touch2);
      glPopMatrix();
      glRotatef(-45.0, 0.0f, 0.0f, 1.0f);
   }
   glPopMatrix();
   /*---(inner)----------------------------*/
   r = (shape.r_center + shape.r_inner) / 2;
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glPushMatrix();
      glTranslatef(r, 0.0f, 0.0f);
      glCallList(shape.dl_inner);
      /*> glCallList(shape.dl_touch);                                                       <*/
      glPopMatrix();
      glRotatef(-45.0, 0.0f, 0.0f, 1.0f);
   }
   glPopMatrix();
   /*---(boundaries)-----------------------*/
   /*> glColor4f(0.2f, 0.2f, 0.2f, 1.0f);                                             <* 
    *> glBegin(GL_LINE_STRIP);                                                        <* 
    *> for (d = 0; d <= 360; d += 10) {                                               <* 
    *>    rad =  d * DEG2RAD;                                                         <* 
    *>    x   =  shape.r_center * cos(rad);                                            <* 
    *>    y   =  shape.r_center * sin(rad);                                            <* 
    *>    glVertex3f( x, y, z);                                                       <* 
    *> }                                                                              <* 
    *> glEnd();                                                                       <* 
    *> glBegin(GL_LINE_STRIP);                                                        <* 
    *> for (d = 0; d <= 360; d += 10) {                                               <* 
    *>    rad =  d * DEG2RAD;                                                         <* 
    *>    x   =  shape.r_inner * cos(rad);                                             <* 
    *>    y   =  shape.r_inner * sin(rad);                                             <* 
    *>    glVertex3f( x, y, z);                                                       <* 
    *> }                                                                              <* 
    *> glEnd();                                                                       <* 
    *> glBegin(GL_LINE_STRIP);                                                        <* 
    *> for (d = 0; d <= 360; d += 10) {                                               <* 
    *>    rad =  d * DEG2RAD;                                                         <* 
    *>    x   =  shape.r_outer * cos(rad);                                             <* 
    *>    y   =  shape.r_outer * sin(rad);                                             <* 
    *>    glVertex3f( x, y, z);                                                       <* 
    *> }                                                                              <* 
    *> glEnd();                                                                       <* 
    *> glBegin(GL_LINE_STRIP);                                                        <* 
    *> for (d = 0; d <= 360; d += 10) {                                               <* 
    *>    rad =  d * DEG2RAD;                                                         <* 
    *>    x   =  shape.r_edge * cos(rad);                                              <* 
    *>    y   =  shape.r_edge * sin(rad);                                              <* 
    *>    glVertex3f( x, y, z);                                                       <* 
    *> }                                                                              <* 
    *> glEnd();                                                                       <*/
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_touch(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_touch = glGenLists(1);
   glNewList(shape.dl_touch, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r  =  (20 * 0.70) / 2;
   float   z  =  -5.00;
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   =  r * cos(rad);
      y   =  r * sin(rad);
      glVertex3f( x, y, z);
   }
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_balls(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_balls = glGenLists(1);
   glNewList(shape.dl_balls, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r  =  shape.r_center / 5.0;
   float   z  =  -5.00;
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON); {
      for (d = 0; d <= 360; d += 10) {
         rad = d * DEG2RAD;
         x   =  r * cos(rad);
         y   =  r * sin(rad);
         glVertex3f( x, y, z);
      }
   } glEnd();
   /*---(line)------------------------------*/
   glLineWidth (shape.r_lines);
   glColor4f   (0.0f, 0.5f, 0.0f, 0.5f);
   glBegin(GL_LINE_STRIP); {
      for (d = 0; d <= 360; d += 10) {
         rad = d * DEG2RAD;
         x   =  r * cos(rad);
         y   =  r * sin(rad);
         glVertex3f( x, y, z + 5);
      }
   } glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_belly(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_belly = glGenLists(1);
   glNewList(shape.dl_belly, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r1 =  shape.r_button;
   float   r2 =  shape.r_button * 0.50;
   float   z  =  -5.0;
   /*---(exterior)--------------------------*/
   glBegin(GL_POLYGON);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   = r1 * cos(rad);
      y   = r1 * sin(rad);
      glVertex3f( x, y, z);
   }
   glEnd();
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON);
   glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   = r2 * cos(rad);
      y   = r2 * sin(rad);
      glVertex3f( x, y, z + 0.01);
   }
   glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
displist_orient(void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(begin)-----------------------------*/
   shape.dl_orient = glGenLists(1);
   glNewList(shape.dl_orient, GL_COMPILE);
   /*---(locals)----------------------------*/
   float   d;
   float   rad;
   float   x, y;
   float   r1 =  shape.r_button;
   float   r2 =  shape.r_button * 0.50;
   float   r3 =  shape.r_button * 0.60;
   float   z  =  -5.0;
   /*---(exterior)--------------------------*/
   glBegin(GL_POLYGON);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   = r1 * cos(rad);
      y   = r1 * sin(rad);
      glVertex3f( x, y, z);
   }
   glEnd();
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON);
   glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
   for (d = 0; d <= 360; d += 10) {
      rad = d * DEG2RAD;
      x   = r2 * cos(rad);
      y   = r2 * sin(rad);
      glVertex3f( x, y, z + 0.01);
   }
   glEnd();
   /*---(bar)-------------------------------*/
   glBegin(GL_POLYGON);
   glVertex3f( -r1, -r3, z);
   glVertex3f(  r3,  r1, z);
   glVertex3f(  r1,  r3, z);
   glVertex3f( -r3, -r1, z);
   glEnd();
   /*> glBegin(GL_POLYGON);                                                           <* 
    *> glVertex3f( -r3, -r1, z);                                                      <* 
    *> glVertex3f( -r3,  r1, z);                                                      <* 
    *> glVertex3f(  r3,  r1, z);                                                      <* 
    *> glVertex3f(  r3, -r1, z);                                                      <* 
    *> glEnd();                                                                       <*/
   /*---(end)-------------------------------*/
   glEndList();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*============================================================================*
 *=======                         END OF SOURCE                        =======*
 *============================================================================*/
