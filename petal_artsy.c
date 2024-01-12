/*============================[[    beg-code    ]]============================*/
#include    "petal.h"

static    float   s_tall     = 800.0;
static    float   s_wide     = 800.0;
static    float   s_cen      = 400.0;
static    float   s_mid      = 400.0;
static    float   s_bar      =  40.0;

static    float   r_ball     =  20.0;
static    float   r_fast     =  80.0;
static    float   r_center   = 100.0;
static    float   r_inner    = 200.0;
static    float   r_outer    = 300.0;
static    float   r_edge     = 340.0;

static    uint    dl_ball    = 0;
static    uint    dl_center  = 0;
static    uint    dl_fast    = 0;
static    uint    dl_inner   = 0;
static    uint    dl_outer   = 0;
static    uint    dl_edge    = 0;
static    uint    dl_ring    = 0;

char
ARTSY_resize            (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_wide       =   800;
   s_tall       =   800;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY_init              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   my.g_tex     =    -1;
   my.g_fbo     =    -1;
   my.g_dep     =    -1;
   /*> yCOLOR_palette (190, "rcomp", "pale", "warm");                                 <*/
   rc = yGLTEX_config ();
   DEBUG_GRAF   yLOG_value    ("config"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__center           (float a_radius, float a_depth, uint *b_dlist)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uint        x_dlist     =   -1;
   int         i           =    0;
   float       c           [4][3];
   float       r           = a_radius;
   float       z           = a_depth;
   float       v           = 0.0;
   float       d;
   float       rad;
   float       x, y;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%7.2fr, %7.2fd", a_radius, a_depth);
   /*---(defense)---------------------------*/
   DEBUG_GRAF   yLOG_point   ("b_dlist"   , b_dlist);
   --rce;  if (b_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create list)-----------------------*/
   x_dlist = *b_dlist;
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   if (x_dlist != NULL) {
      DEBUG_GRAF   yLOG_note    ("must delete existing list");
      glDeleteLists (x_dlist , 1);
      x_dlist = NULL;
   } else {
      DEBUG_GRAF   yLOG_note    ("list not yet created");
   }
   x_dlist = glGenLists (1);
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   --rce;  if (x_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)-----------------------------*/
   glNewList (x_dlist, GL_COMPILE);
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   glLineWidth (1.0);
   /*---(interior)--------------------------*/
   glColor4f   (1.00, 0.50, 0.00, 1.00);
   r  = a_radius * 0.85;
   glBegin(GL_POLYGON); {
      for (d = 0; d <= 360; d += 10) {
         rad = d * DEG2RAD;
         x   = r * cos(rad);
         y   = r * sin(rad);
         glVertex3f ( x, y, z);
      }
   } glEnd();
   /*---(inside star)-----------------------*/
   glColor4f   (1.00, 1.00, 1.00, 1.00);
   r  = a_radius * 1.00;
   for (i = 0;  i < 8; ++i) {
      glBegin (GL_POLYGON); {
         glVertex3f ( 0, 0, z + 2);
         for (d = i * 45; d <= (i + 1) * 45; d += 15) {
            rad = d * DEG2RAD;
            x   = r * cos(rad) * (((((int) d) % 45) == 0) ? 0.6f : 0.4f);
            y   = r * sin(rad) * (((((int) d) % 45) == 0) ? 0.6f : 0.4f);
            glVertex3f ( x, y, z + 2);
         }
         glVertex3f ( 0, 0, z + 2);
      } glEnd();
   }
   /*---(star outline)----------------------*/
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   r  = a_radius * 1.00;
   glBegin (GL_LINE_STRIP); {
      for (d = 0; d <= 360; d += 15) {
         rad = d * DEG2RAD;
         x   = r * cos(rad) * (((((int) d) % 45) == 0) ? 0.6f : 0.4f);
         y   = r * sin(rad) * (((((int) d) % 45) == 0) ? 0.6f : 0.4f);
         glVertex3f ( x, y, z + 2);
      }
   } glEnd();
   /*---(outline)---------------------------*/
   r  = a_radius * 0.85;
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
   /*---(save-back)-------------------------*/
   *b_dlist = x_dlist;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__bezier           (char a_type, float r1, float r2, float r3, float d1, float d2, float z, float a_cut)
{
   float       c           [4][3];
   float       v           = 0.0;
   /*---(right-side)------------------------*/
   c [0][0] = 0.0;
   c [0][1] = 0.0;
   c [1][0] = r1 * cos (-d1 * DEG2RAD);
   c [1][1] = r1 * sin (-d1 * DEG2RAD);
   c [2][0] = r2 * cos (-d2 * DEG2RAD);
   c [2][1] = r2 * sin (-d2 * DEG2RAD);
   c [3][0] = r3 * cos (0.0 * DEG2RAD);
   c [3][1] = r3 * sin (0.0 * DEG2RAD);
   c [0][2] = c [1][2] = c [2][2] = c [3][2] = z;
   /*---(draw)------------------------------*/
   glMap1f     (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &(c [0][0]));
   glEnable    (GL_MAP1_VERTEX_3);
   /*---(right-side)------------------------*/
   if (a_type == 'l')  glBegin     (GL_LINE_STRIP);
   else                glBegin     (GL_POLYGON);
   for (v = a_cut; v <= 1.00; v += 0.01) {
      glEvalCoord1f (v);
   }
   if (a_type != 'l')  glVertex3f( 0, 0, z);
   glEnd       ();
   glDisable   (GL_MAP1_VERTEX_3);
   /*---(left-side)-------------------------*/
   c [1][0] = r1 * cos ( d1 * DEG2RAD);
   c [1][1] = r1 * sin ( d1 * DEG2RAD);
   c [2][0] = r2 * cos ( d2 * DEG2RAD);
   c [2][1] = r2 * sin ( d2 * DEG2RAD);
   /*---(draw)------------------------------*/
   glMap1f     (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &(c [0][0]));
   glEnable    (GL_MAP1_VERTEX_3);
   if (a_type == 'l')  glBegin     (GL_LINE_STRIP);
   else                glBegin     (GL_POLYGON);
   for (v = a_cut; v <= 1.00; v += 0.01) {
      glEvalCoord1f (v);
   }
   if (a_type != 'l')  glVertex3f( 0, 0, z);
   glEnd       ();
   glDisable   (GL_MAP1_VERTEX_3);
   /*---(save-back)-------------------------*/
   return 0;
}

char
ARTSY__inner            (float a_radius, float a_depth, uint *b_dlist)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uint        x_dlist     =   -1;
   float       r           = a_radius;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%7.2fr, %7.2fd", a_radius, a_depth);
   /*---(defense)---------------------------*/
   DEBUG_GRAF   yLOG_point   ("b_dlist"   , b_dlist);
   --rce;  if (b_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create list)-----------------------*/
   x_dlist = *b_dlist;
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   if (x_dlist != NULL) {
      DEBUG_GRAF   yLOG_note    ("must delete existing list");
      glDeleteLists (x_dlist , 1);
      x_dlist = NULL;
   } else {
      DEBUG_GRAF   yLOG_note    ("list not yet created");
   }
   x_dlist = glGenLists (1);
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   --rce;  if (x_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)-----------------------------*/
   glNewList (x_dlist, GL_COMPILE);
   glLineWidth (1.0);
   /*---(draw)------------------------------*/
   glColor4f   (1.00, 1.00, 1.00, 1.00);
   ARTSY__bezier ('p', r * 0.80, r * 1.00, r * 1.30, 70.0,  0.0, a_depth    ,  0.0);
   glColor4f   (1.00, 0.00, 0.00, 0.15);
   ARTSY__bezier ('p', r * 0.80, r * 1.00, r * 1.30, 70.0,  0.0, a_depth + 2,  0.0);
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   ARTSY__bezier ('l', r * 0.80, r * 1.00, r * 1.30, 70.0,  0.0, a_depth + 4,  0.0);
   /*---(end)-------------------------------*/
   glEndList();
   /*---(save-back)-------------------------*/
   *b_dlist = x_dlist;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__outer            (float a_radius, float a_depth, uint *b_dlist)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uint        x_dlist     =   -1;
   float       r           = a_radius;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%7.2fr, %7.2fd", a_radius, a_depth);
   /*---(defense)---------------------------*/
   DEBUG_GRAF   yLOG_point   ("b_dlist"   , b_dlist);
   --rce;  if (b_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create list)-----------------------*/
   x_dlist = *b_dlist;
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   if (x_dlist != NULL) {
      DEBUG_GRAF   yLOG_note    ("must delete existing list");
      glDeleteLists (x_dlist , 1);
      x_dlist = NULL;
   } else {
      DEBUG_GRAF   yLOG_note    ("list not yet created");
   }
   x_dlist = glGenLists (1);
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   --rce;  if (x_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)-----------------------------*/
   glNewList (x_dlist, GL_COMPILE);
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   glLineWidth (1.0);
   /*---(draw)------------------------------*/
   glColor4f   (1.00, 1.00, 1.00, 1.00);
   ARTSY__bezier ('p', r * 0.80, r * 0.90, r * 1.00, 45.0,  5.0, a_depth    ,  0.0);
   glColor4f   (0.00, 1.00, 0.00, 0.30);
   ARTSY__bezier ('p', r * 0.80, r * 0.90, r * 1.00, 45.0,  5.0, a_depth + 2,  0.0);
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   ARTSY__bezier ('l', r * 0.80, r * 0.90, r * 1.00, 45.0,  5.0, a_depth + 4,  0.0);
   /*---(end)-------------------------------*/
   glEndList();
   /*---(save-back)-------------------------*/
   *b_dlist = x_dlist;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__edge             (float a_radius, float a_depth, uint *b_dlist)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uint        x_dlist     =   -1;
   float       r           = a_radius;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%7.2fr, %7.2fd", a_radius, a_depth);
   /*---(defense)---------------------------*/
   DEBUG_GRAF   yLOG_point   ("b_dlist"   , b_dlist);
   --rce;  if (b_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create list)-----------------------*/
   x_dlist = *b_dlist;
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   if (x_dlist != NULL) {
      DEBUG_GRAF   yLOG_note    ("must delete existing list");
      glDeleteLists (x_dlist , 1);
      x_dlist = NULL;
   } else {
      DEBUG_GRAF   yLOG_note    ("list not yet created");
   }
   x_dlist = glGenLists (1);
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   --rce;  if (x_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)-----------------------------*/
   glNewList (x_dlist, GL_COMPILE);
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   glLineWidth (1.0);
   /*---(draw)------------------------------*/
   glColor4f   (1.00, 1.00, 1.00, 1.00);
   ARTSY__bezier ('p', r * 0.95, r * 1.00, r * 1.00, 50.0,  0.0, a_depth    ,  0.0);
   glColor4f   (0.00, 0.50, 0.75, 0.30);
   ARTSY__bezier ('p', r * 0.95, r * 1.00, r * 1.00, 50.0,  0.0, a_depth + 2,  0.0);
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   ARTSY__bezier ('l', r * 0.95, r * 1.00, r * 1.00, 50.0,  0.0, a_depth + 4,  0.0);
   /*---(end)-------------------------------*/
   glEndList();
   /*---(save-back)-------------------------*/
   *b_dlist = x_dlist;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__ball             (float a_radius, float a_depth, uint *b_dlist)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uint        x_dlist     =   -1;
   float       r           = a_radius;
   float       d;
   float       rad;
   float       x, y;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%7.2fr, %7.2fd", a_radius, a_depth);
   /*---(defense)---------------------------*/
   DEBUG_GRAF   yLOG_point   ("b_dlist"   , b_dlist);
   --rce;  if (b_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create list)-----------------------*/
   x_dlist = *b_dlist;
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   if (x_dlist != NULL) {
      DEBUG_GRAF   yLOG_note    ("must delete existing list");
      glDeleteLists (x_dlist , 1);
      x_dlist = NULL;
   } else {
      DEBUG_GRAF   yLOG_note    ("list not yet created");
   }
   x_dlist = glGenLists (1);
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   --rce;  if (x_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)-----------------------------*/
   glNewList (x_dlist, GL_COMPILE);
   glLineWidth (1.0);
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON); {
      for (d = 0; d <= 360; d += 1) {
         rad = d * DEG2RAD;
         x   =  r * cos(rad);
         y   =  r * sin(rad);
         glVertex3f( x, y, a_depth);
      }
   } glEnd();
   /*---(line)------------------------------*/
   /*> glColor4f   (0.00f, 0.00f, 0.00f, 0.50f);                                      <* 
    *> glBegin(GL_LINE_STRIP); {                                                      <* 
    *>    for (d = 0; d <= 360; d += 10) {                                            <* 
    *>       rad = d * DEG2RAD;                                                       <* 
    *>       x   =  r * cos(rad);                                                     <* 
    *>       y   =  r * sin(rad);                                                     <* 
    *>       glVertex3f( x, y, a_depth + 2);                                          <* 
    *>    }                                                                           <* 
    *> } glEnd();                                                                     <*/
   /*---(end)-------------------------------*/
   glEndList();
   /*---(save-back)-------------------------*/
   *b_dlist = x_dlist;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__fast             (float a_radius, float a_depth, uint *b_dlist)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uint        x_dlist     =   -1;
   float       r           = a_radius;
   float       d;
   float       rad;
   float       x, y;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%7.2fr, %7.2fd", a_radius, a_depth);
   /*---(defense)---------------------------*/
   DEBUG_GRAF   yLOG_point   ("b_dlist"   , b_dlist);
   --rce;  if (b_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create list)-----------------------*/
   x_dlist = *b_dlist;
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   if (x_dlist != NULL) {
      DEBUG_GRAF   yLOG_note    ("must delete existing list");
      glDeleteLists (x_dlist , 1);
      x_dlist = NULL;
   } else {
      DEBUG_GRAF   yLOG_note    ("list not yet created");
   }
   x_dlist = glGenLists (1);
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   --rce;  if (x_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)-----------------------------*/
   glNewList (x_dlist, GL_COMPILE);
   glLineWidth (1.0);
   /*---(interior)--------------------------*/
   glBegin(GL_POLYGON); {
      for (d =  0; d <= 90; d += 1) {
         rad = d * DEG2RAD;
         x   =  r * 1.10 * cos(rad);
         y   =  r * 1.10 * sin(rad);
         glVertex3f( x, y, a_depth);
      }
      for (d = 90; d >=  0; d -= 1) {
         rad = d * DEG2RAD;
         x   =  r * 0.90 * cos(rad);
         y   =  r * 0.90 * sin(rad);
         glVertex3f( x, y, a_depth);
      }
      rad = 0.0 * DEG2RAD;
      x   =  r * 1.10 * cos(rad);
      y   =  r * 1.10 * sin(rad);
      glVertex3f( x, y, a_depth);
   } glEnd();
   /*---(line)------------------------------*/
   /*> glColor4f   (0.00f, 0.00f, 0.00f, 0.50f);                                      <* 
    *> glBegin(GL_LINE_STRIP); {                                                      <* 
    *>    for (d = 0; d <= 360; d += 10) {                                            <* 
    *>       rad = d * DEG2RAD;                                                       <* 
    *>       x   =  r * cos(rad);                                                     <* 
    *>       y   =  r * sin(rad);                                                     <* 
    *>       glVertex3f( x, y, a_depth + 2);                                          <* 
    *>    }                                                                           <* 
    *> } glEnd();                                                                     <*/
   /*---(end)-------------------------------*/
   glEndList();
   /*---(save-back)-------------------------*/
   *b_dlist = x_dlist;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__ring             (float a_radius, float a_depth, uint *b_dlist)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uint        x_dlist     =   -1;
   float       r           = a_radius;
   float       d;
   float       rad;
   float       x, y;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%7.2fr, %7.2fd", a_radius, a_depth);
   /*---(defense)---------------------------*/
   DEBUG_GRAF   yLOG_point   ("b_dlist"   , b_dlist);
   --rce;  if (b_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create list)-----------------------*/
   x_dlist = *b_dlist;
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   if (x_dlist != NULL) {
      DEBUG_GRAF   yLOG_note    ("must delete existing list");
      glDeleteLists (x_dlist , 1);
      x_dlist = NULL;
   } else {
      DEBUG_GRAF   yLOG_note    ("list not yet created");
   }
   x_dlist = glGenLists (1);
   DEBUG_GRAF   yLOG_point   ("x_dlist"   , x_dlist);
   --rce;  if (x_dlist == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)-----------------------------*/
   glNewList (x_dlist, GL_COMPILE);
   glLineWidth (1.0);
   /*---(fill)------------------------------*/
   glBegin(GL_POLYGON); {
      glVertex3f( 0, 0, a_depth);
      for (d =  -7.5; d <=  7.5; d += 1) {
         rad = d * DEG2RAD;
         r   =  a_radius - 35 + 10 * cos ((d * 24) * DEG2RAD);
         x   =  r * cos(rad);
         y   =  r * sin(rad);
         DEBUG_GRAF   yLOG_complex ("point"     , "%7.2fd, %7.2frad, %7.2fr, %7.2fx, %7.2fy", d, rad, r, x, y);
         glVertex3f( x, y, a_depth);
      }
      glVertex3f( 0, 0, a_depth);
   } glEnd();
   /*---(spokes)----------------------------*/
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   r = 400;
   glBegin(GL_LINES); {
      for (d = 0; d <= 360; d += 5) {
         glVertex3f( 0, 0, a_depth + 2);
         rad = d * DEG2RAD;
         r   =  a_radius - 35 + 10 * cos ((d * 24) * DEG2RAD);
         x   =  r * cos(rad);
         y   =  r * sin(rad);
         glVertex3f( x, y, a_depth + 2);
      }
   } glEnd();
   /*---(line)------------------------------*/
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   glBegin(GL_LINE_STRIP); {
      for (d = -7.5; d <= 7.5; d += 1) {
         rad = d * DEG2RAD;
         r   =  a_radius - 35 + 10 * cos ((d * 24) * DEG2RAD);
         x   =  r * cos(rad);
         y   =  r * sin(rad);
         DEBUG_GRAF   yLOG_complex ("point"     , "%7.2fd, %7.2frad, %7.2fr, %7.2fx, %7.2fy", d, rad, r, x, y);
         glVertex3f( x, y, a_depth);
      }
   } glEnd();
   /*---(ring)------------------------------*/
   glLineWidth (10.0);
   r = 378;
   glColor4f   (1.00, 0.00, 0.00, 0.50);
   glBegin(GL_LINE_STRIP); {
      for (d = 0; d <= 360; d += 1) {
         rad = d * DEG2RAD;
         x   =  r * cos(rad);
         y   =  r * sin(rad);
         glVertex3f( x, y, a_depth);
      }
   } glEnd();
   /*---(end)-------------------------------*/
   glEndList();
   /*---(save-back)-------------------------*/
   *b_dlist = x_dlist;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ARTSY__start            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter    (__FUNCTION__);
   /*---(create objects)-----------------*/
   DEBUG_GRAF   yLOG_complex  ("existing"  , "%4dt, %4df, %4dd", my.g_tex, my.g_fbo, my.g_dep);
   if (my.g_tex != -1) {
      DEBUG_GRAF   yLOG_note     ("old texture exists, delete old texture");
      rc = yGLTEX_free (&my.g_tex, &my.g_fbo, &my.g_dep);
      DEBUG_GRAF   yLOG_value    ("delete"    , rc);
   } else {
      DEBUG_GRAF   yLOG_note     ("old texture NULL, nothing to delete");
   }
   /*---(create objects)-----------------*/
   DEBUG_GRAF   yLOG_complex  ("size"      , "%4.0fw, %4.0ft", s_wide, s_tall);
   DEBUG_GRAF   yLOG_note     ("create texture");
   rc = yGLTEX_new (&my.g_tex, &my.g_fbo, &my.g_dep, s_wide, s_tall);
   DEBUG_GRAF   yLOG_value    ("delete"    , rc);
   DEBUG_GRAF   yLOG_complex  ("new"       , "%4drc, %4dt, %4df, %4dd", rc, my.g_tex, my.g_fbo, my.g_dep);
   /*---(setup)--------------------------*/
   DEBUG_GRAF   yLOG_note     ("setup opengl view");
   rc = yGLTEX_draw (my.g_tex, my.g_fbo, YGLTEX_MIDCEN, s_wide, s_tall, 1.0);
   DEBUG_GRAF   yLOG_value    ("draw"      , rc);
   glColor4f (0.0f, 0.0f, 0.0f, 1.0f);
   /*---(complete)-------------------------*/
   DEBUG_GRAF   yLOG_exit     (__FUNCTION__);
   return 0;
}

char
ARTSY__finish           (void)
{
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter    (__FUNCTION__);
   /*---(existing)-----------------------*/
   DEBUG_GRAF   yLOG_complex  ("existing"  , "%4dt, %4df, %4dd", my.g_tex, my.g_fbo, my.g_dep);
   glFlush         ();
   /*---(snapshot)-----------------------*/
   DEBUG_GRAF   yLOG_char     ("save_png"  , my.save_png);
   if (strchr ("y+", my.save_png) != NULL) {
      DEBUG_GRAF   yLOG_note     ("taking snapshot");
      DEBUG_GRAF   yLOG_complex  ("size"      , "%4.0fw, %4.0ft", s_wide, s_tall);
      rc = yGLTEX_tex2png ("/tmp/petal_snapshot.png", s_wide, s_tall);
      DEBUG_GRAF   yLOG_value    ("tex2png"   , rc);
      if (my.save_png == 'y')  my.save_png = '-';
   }
   /*---(lock-in)------------------------*/
   rc = yGLTEX_done    (my.g_tex);
   DEBUG_GRAF   yLOG_complex  ("done"      , "%4dt, %4df, %4dd", my.g_tex, my.g_fbo, my.g_dep);
   /*---(complete)-------------------------*/
   DEBUG_GRAF   yLOG_exit     (__FUNCTION__);
   return 0;
}

char
ARTSY__draw_fasts        (void)
{
   int       i;
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      if (my.show_balls == 'y') {
         glPushMatrix(); {
            glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
            glTranslatef (r_fast, 0.0f, 0.0f);
            glColor4f (1.00, 1.00, 1.00, 1.00);
            glCallList   (dl_ball);
            glColor4f (0.00, 0.00, 0.50, 0.50);
            glCallList   (dl_ball);
         } glPopMatrix();
      }
   }
   glPopMatrix();
   return 0;
}

char
ARTSY__draw_inners       (void)
{
   /*---(locals)-------------------------*/
   int       i;                             /* loop iterator -- word          */
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glPushMatrix(); {
         glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
         glColor4f    (0.7f, 0.7f, 0.7f, 1.0f);
         glCallList   (dl_inner);
      } glPopMatrix();
      if (my.show_balls == 'y') {
         glPushMatrix(); {
            glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
            glTranslatef (r_inner * 0.65, 0.0f, 0.0f);
            glColor4f (1.00, 1.00, 1.00, 1.00);
            glCallList   (dl_ball);
            glColor4f (1.00, 0.00, 0.00, 0.30);
            glCallList   (dl_ball);
         } glPopMatrix();
      }
   }
   glPopMatrix();
   return 0;
}

char
ARTSY__draw_outers       (void)
{
   /*---(locals)-------------------------*/
   int       i;                             /* loop iterator -- word          */
   glPushMatrix();
   for (i = 0; i < 8; i += 1) {
      glPushMatrix(); {
         /*> glRotatef    (45 - (i * 45), 0.0f, 0.0f, 1.0f);                          <*/
         glRotatef    ( 22.5 - (i * 45), 0.0f, 0.0f, 1.0f);
         glCallList   (dl_outer);
      } glPopMatrix();
      if (my.show_balls == 'y') {
         glPushMatrix(); {
            glRotatef    (45 - (i * 45), 0.0f, 0.0f, 1.0f);
            glRotatef    (22.5, 0.0f, 0.0f, 1.0f);
            glTranslatef (r_outer * 0.70, 0.0f, 0.0f);
            glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
            glCallList(  dl_ball);
            glColor4f (0.00, 0.60, 0.00, 0.45);
            glCallList(  dl_ball);
         } glPopMatrix();
      }
   }
   glPopMatrix();
   return 0;
}

char
ARTSY__draw_edges        (void)
{
   /*---(locals)-------------------------*/
   int       i;                             /* loop iterator -- word          */
   glPushMatrix(); {
      for (i = 0; i < 8; i += 1) {
         glPushMatrix(); {
            glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
            glCallList  (dl_edge);
         } glPopMatrix();
         if (my.show_balls == 'y') {
            glPushMatrix(); {
               glRotatef    (90 - (i * 45), 0.0f, 0.0f, 1.0f);
               glTranslatef (r_edge * 0.85, 0.0f, 0.0f);
               glColor4f (1.00, 1.00, 1.00, 1.00);
               glCallList   (dl_ball);
               glColor4f (0.00, 0.00, 0.60, 0.45);
               glCallList   (dl_ball);
            } glPopMatrix();
         }
      }
   } glPopMatrix();
   return 0;
}

char
ARTSY_draw               (void)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   int       i;                             /* loop iterator -- word          */
   int       j;                             /* loop iterator -- word          */
   int       w       = 0;
   int       pos     = 0;
   int       x_max   = 0;
   float     x_inc   = 0.0;
   int       n       =    0;
   float       x_pos       =    0;
   float       y_pos       =    0;
   float       x, y;
   char        t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter    (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ARTSY_init     ();
   DEBUG_GRAF   yLOG_value    ("init"      , rc);
   rc = ARTSY__start   ();
   DEBUG_GRAF   yLOG_value    ("start"     , rc);
   /*--(prepare dlists)-------------------*/
   rc = ARTSY__center (r_center, 20.0, &dl_center);
   DEBUG_GRAF   yLOG_value    ("center"    , rc);
   rc = ARTSY__fast   (r_fast  , 25.0, &dl_fast );
   DEBUG_GRAF   yLOG_value    ("fast"      , rc);
   rc = ARTSY__inner  (r_inner , 15.0, &dl_inner);
   DEBUG_GRAF   yLOG_value    ("inner"     , rc);
   rc = ARTSY__outer  (r_outer , 10.0, &dl_outer);
   DEBUG_GRAF   yLOG_value    ("outer"     , rc);
   rc = ARTSY__edge   (r_edge  ,  5.0, &dl_edge);
   DEBUG_GRAF   yLOG_value    ("edge"      , rc);
   rc = ARTSY__ball   (r_ball  , 50.0, &dl_ball);
   DEBUG_GRAF   yLOG_value    ("ball"      , rc);
   rc = ARTSY__ring   (390.0   ,-50.0, &dl_ring);
   DEBUG_GRAF   yLOG_value    ("ball"      , rc);
   /*---(draw)---------------------------*/
   glColor4f   (1.00, 1.00, 1.00, 1.00);
   glLineWidth (1.0);
   yFONT_print  (my.txf_sm,  24, YF_MIDLEF, "");
   glColor4f   (1.00, 0.50, 0.00, 1.00);
   glBegin(GL_POLYGON); {
      glVertex3f (   -400.0,      400.0,  -60.0);
      glVertex3f (    400.0,      400.0,  -60.0);
      glVertex3f (    400.0,     -400.0,  -60.0);
      glVertex3f (   -400.0,     -400.0,  -60.0);
   } glEnd();
   for (i = 0; i < 24; i += 1) {
      if (i % 2 == 0)  glColor4f   (1.00, 0.00, 0.00, 0.10);
      else             glColor4f   (1.00, 0.00, 0.00, 0.30);
      glPushMatrix(); {
         glRotatef    ( - (i * 15), 0.0f, 0.0f, 1.0f);
         glCallList   (dl_ring);
      } glPopMatrix();
   }
   /*> glCallList  (dl_ring);                                                         <*/
   ARTSY__draw_edges  ();
   ARTSY__draw_outers ();
   ARTSY__draw_inners ();
   ARTSY__draw_fasts  ();
   glCallList   (dl_center);
   glPushMatrix    (); {
      glTranslatef (0.0f, 0.0f, 25.0f);
      glColor4f    (1.00, 1.00, 1.00, 1.00);
      glCallList   (dl_ball);
      glColor4f    (1.00, 0.50, 0.00, 1.00);
      glCallList   (dl_ball);
   } glPopMatrix   ();
   /*---(prepare)------------------------*/
   ARTSY__finish  ();
   /*---(complete)-------------------------*/
   DEBUG_GRAF   yLOG_exit     (__FUNCTION__);
   return 0;
}

char
ARTSY_show              (float a_wtop, float a_wlef, float a_wbot, float a_wrig)
{
   glBindTexture   (GL_TEXTURE_2D, my.g_tex);
   glBegin(GL_POLYGON); {
      /*---(top/lef)--------*/
      glTexCoord2f ( 0.0   ,  1.0);
      glVertex3f   ( a_wlef,  a_wtop,  -10.0);
      /*---(top/rig)--------*/
      glTexCoord2f ( 1.0   ,  1.0);
      glVertex3f   ( a_wrig,  a_wtop,  -10.0);
      /*---(bot/rig)--------*/
      glTexCoord2f ( 1.0   ,  0.0);
      glVertex3f   ( a_wrig,  a_wbot,  -10.0);
      /*---(bot/lef)--------*/
      glTexCoord2f ( 0.0   ,  0.0);
      glVertex3f   ( a_wlef,  a_wbot,  -10.0);
      /*---(done)-----------*/
   } glEnd();
   glBindTexture   (GL_TEXTURE_2D, 0);
   return 0;
}

char
ARTSY_mask              (void)
{
   float     x_ratio      = 0;
   Pixmap    bounds;
   if (my.mask != 'y')  return 0;
   GC        gc;
   bounds    = XCreatePixmap (YX_DISP, YX_BASE, my.w_wide, my.w_tall, 1);
   gc        = XCreateGC     (YX_DISP, bounds, 0, NULL);
   XSetForeground (YX_DISP, gc, 0);
   XFillRectangle (YX_DISP, bounds, gc, 0, 0, my.w_wide, my.w_tall);
   XSetForeground (YX_DISP, gc, 1);
   XFillArc (YX_DISP, bounds, gc,   15.0,   15.0, my.w_wide - 30, my.w_tall - 30, 0.0 * 64.0, 360.0 * 64.0);
   XShapeCombineMask (YX_DISP, YX_BASE, ShapeBounding, 0, 0, bounds, ShapeSet);
   /*---(free)---------------------------*/
   XFreePixmap (YX_DISP, bounds);
   XFreeGC     (YX_DISP, gc);
   /*---(complete)-----------------------*/
   return 0;
}
