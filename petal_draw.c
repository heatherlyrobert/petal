/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



#define  HELP_ONLY    if (stroke.help > 0 && stroke.help < 10 && stroke.help != i + 1)   continue

#define  YSTR_PETAL   "tm[c�nf_rx�u.p,ilqdbeh's]ogzw)�j;k:ay(v-"
#define  YSTR_INNER   "tn�ieo�a"
#define  YSTR_OUTER   "cfrupldhsgwjkyvm"
#define  YSTR_EDGE    "_�.xq,'bz];)(:[-"



char
DRAW_done_show     (char *a_flag)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   switch (a_flag [0]) {
   case 'y'  : shape.r_done_show = 'y';        break;
   default   : shape.r_done_show = '-';        break;
   }
   DEBUG_GRAF   yLOG_value   ("done"      , shape.r_done_show);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_debug_set     (char *a_flag)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   switch (a_flag [0]) {
   case 'y'  : shape.r_debug = 'y';        break;
   default   : shape.r_debug = '-';        break;
   }
   DEBUG_GRAF   yLOG_value   ("debug"     , shape.r_debug);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_press         (char *a_state)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   switch (a_state [0]) {
   case '-'  :
      locks  [SHIFT] = 0; states [SHIFT] = 0;
      locks  [MODE ] = 0; states [MODE ] = 0;
      break;
   case 's'  :
      locks  [SHIFT] = 0;
      states [SHIFT] = 0;
      break;
   case 'S'  :
      /*---(unlock)---------*/
      if (locks  [SHIFT] == 1) { locks  [SHIFT] = 0; states [SHIFT] = 0;  break; }
      /*---(lock)-----------*/
      if (states [SHIFT] == 1)   locks  [SHIFT] = 1;
      /*---(press)----------*/
      states [SHIFT] = 1;
      locks  [MODE ] = 0; states [MODE ] = 0;
      break;
   case 'm'  :
      locks  [MODE ] = 0;
      states [MODE ] = 0;
      break;
   case 'M'  :
      /*---(unlock)---------*/
      if (locks  [MODE ] == 1) { locks  [MODE ] = 0; states [MODE ] = 0;  break; }
      /*---(lock)-----------*/
      if (states [MODE ] == 1)   locks  [MODE ] = 1;
      /*---(press)----------*/
      states [MODE ] = 1;
      locks  [SHIFT] = 0; states [SHIFT] = 0;
      break;
   }
   return 0;
}

char
DRAW_help          (char *a_help)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   stroke.help = -1;
   strlcpy (stroke.help_txt, "", LEN_LABEL);
   /*---(defense)------------------------*/
   if (a_help == NULL) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(set)----------------------------*/
   strlcpy (stroke.help_txt, a_help, LEN_LABEL);
   switch (a_help [0]) {
   case '-'  : stroke.help = -1;        break;
   case 'a'  : stroke.help =  0;        break;
   case 'i'  : stroke.help = 10;        break;
   case 'o'  : stroke.help = 11;        break;
   case 'e'  : stroke.help = 12;        break;
   case 'm'  : stroke.help = 13;        break;
   case 't'  : stroke.help = 14;        break;
   case 'N'  :
               if      (a_help [1] == 'N')  stroke.help =  1;
               else if (a_help [1] == 'W')  stroke.help =  8;
               else if (a_help [1] == 'E')  stroke.help =  2;
               else                         stroke.help =  1;
               break;
   case 'E'  : stroke.help =  3;        break;
   case 'S'  : 
               if      (a_help [1] == 'S')  stroke.help =  5;
               else if (a_help [1] == 'W')  stroke.help =  6;
               else if (a_help [1] == 'E')  stroke.help =  4;
               else                         stroke.help =  5;
               break;
   case 'W'  : stroke.help =  7;        break;
   case '!'  : stroke.help = 20;        break;
   default   : stroke.help = -1;        break;
   }
   DEBUG_GRAF   yLOG_value   ("help"      , stroke.help);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_color         (char *a_color)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   shape.r_color_txt = a_color [0];
   switch (a_color [0]) {
   case '-'  : shape.r_color = -1;        break;
   case 'c'  : shape.r_color =  0;        break;
   case 'a'  : shape.r_color =  1;        break;
   case 'i'  : shape.r_color =  2;        break;
   case 'o'  : shape.r_color =  3;        break;
   case 'e'  : shape.r_color =  4;        break;
   case 'm'  : shape.r_color =  4;        break;
   case 't'  : shape.r_color =  5;        break;
   default   : shape.r_color = -1;  shape.r_color_txt = '�';        break;
   }
   DEBUG_GRAF   yLOG_value   ("help"      , shape.r_color);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_speed         (char *a_speed)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(short-cut)----------------------*/
   shape.r_inc_txt = a_speed [0];
   switch (a_speed [0]) {
   case '-' :
   case '0' :   shape.r_inc   = 0.000;  break;
   case '1' :   shape.r_inc   = 0.200;  break;
   case '2' :   shape.r_inc   = 0.150;  break;
   case '3' :   shape.r_inc   = 0.100;  break;
   case '4' :   shape.r_inc   = 0.050;  break;
   case '5' :   shape.r_inc   = 0.040;  break;
   case '6' :   shape.r_inc   = 0.030;  break;
   case '7' :   shape.r_inc   = 0.025;  break;
   case '8' :   shape.r_inc   = 0.020;  break;
   case '9' :   shape.r_inc   = 0.010;  break;
   default  :   shape.r_inc   = 0.000;  shape.r_inc_txt = '�';  break;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_seq           (char a_mode, char *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   char        c, m;
   char        t           [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(mode)---------------------------*/
   switch (a_mode) {
   case '-'  : shape.r_mode = '-';  break;  /* one-at-a-time      */
   case '2'  : shape.r_mode = '2';  break;  /* show last two, shadowed      */
   case '3'  : shape.r_mode = '3';  break;  /* show last three, shadowed    */
   case 'c'  : shape.r_mode = 'c';  break;  /* show all cum, one color      */
   case 'r'  : shape.r_mode = 'r';  break;  /* show all cum, rainbow        */
   case '*'  : shape.r_mode = '*';  break;  /* show all cum, shadowed       */
   case '!'  : shape.r_mode = '!';  break;  /* show all at once, one color  */
   default   : shape.r_mode = '-';  break;
   }
   /*---(sequence)-----------------------*/
   if (a_text == NULL || a_text [0] == '\0') {
      strlcpy (shape.r_eng, "", LEN_RECD);
      strlcpy (shape.r_seq, "", LEN_RECD);
      shape.r_len    =     0;
      shape.r_pos    =    -1;
      shape.r_exec   =    -1;
      shape.r_letter =  '\0';
      shape.r_prog   = -1.00;
      strlcpy (shape.r_done, "", LEN_RECD);
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   } else {
      if      (strcmp (a_text, "!!")    == 0)  strlcpy (shape.r_eng, YSTR_LOWER   , LEN_RECD);
      else if (strcmp (a_text, "**")    == 0)  strlcpy (shape.r_eng, YSTR_PETAL   , LEN_RECD);
      else if (strcmp (a_text, "hw")    == 0)  strlcpy (shape.r_eng, "hello�world", LEN_RECD);
      else if (strcmp (a_text, "inner") == 0)  strlcpy (shape.r_eng, YSTR_INNER   , LEN_RECD);
      else if (strcmp (a_text, "outer") == 0)  strlcpy (shape.r_eng, YSTR_OUTER   , LEN_RECD);
      else if (strcmp (a_text, "edge" ) == 0)  strlcpy (shape.r_eng, YSTR_EDGE    , LEN_RECD);
      else                                  strlcpy (shape.r_eng, a_text       , LEN_RECD);
   }
   /*---(translate)----------------------*/
   l = strlen (shape.r_eng);
   strlcpy (shape.r_seq , "", LEN_RECD);
   for (i = 0; i < l; ++i) {
      /*---(gather english)--------------*/
      c  = shape.r_eng [i];
      /*---(find states)-----------------*/
      switch (c) {
      case '�'    :  strlcat (shape.r_seq, "E", LEN_RECD);  continue;  break;
      case '�'    :  strlcat (shape.r_seq, "N", LEN_RECD);  continue;  break;
      case '�'    :  strlcat (shape.r_seq, "T", LEN_RECD);  continue;  break;
      case '�'    :  strlcat (shape.r_seq, "A", LEN_RECD);  continue;  break;
      case '�'    :  strlcat (shape.r_seq, "C", LEN_RECD);  continue;  break;
      case '�'    :  strlcat (shape.r_seq, "H", LEN_RECD);  continue;  break;
      }
      /*---(get letter)------------------*/
      rc = LETTER_to_stroke ('y', c, &m, NULL, NULL, NULL);
      DEBUG_GRAF   yLOG_complex ("to_stroke" , "%c/%3dc, %4drc, %dm", c, rc, m);
      if (rc < 0)  c = '�';
      /*---(handle modes)----------------*/
      switch (m) {
      case SHIFT  :  strlcat (shape.r_seq, "S", LEN_RECD);  break;
      case MODE   :  strlcat (shape.r_seq, "M", LEN_RECD);  break;
      }
      /*---(add letter)------------------*/
      sprintf (t, "%c", g_letters [rc]);
      strlcat (shape.r_seq, t, LEN_RECD);
      /*---(done)------------------------*/
   }
   /*---(fill-in)------------------------*/
   shape.r_len    = strlen (shape.r_seq);
   shape.r_pos    = 0;
   shape.r_exec   = 0;
   shape.r_letter = shape.r_seq [0];
   shape.r_prog   = 0.00;
   strlcpy (shape.r_done, "", LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_stroke        (char a_type, char a_letter)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   float       x_deg       =  0.0;
   float       x_radians   =  0.0;
   float       x_lead      =  0.0;
   float       x_tail      =  0.0;
   float       x_sarc      =  0.0;
   float       x           =  0.0;
   float       y           =  0.0;
   float       x_controls  [4][3];
   float       x_pos       =  0.0;
   float       x_cen, x_mid;
   float       z           = 300.0;
   char        m, i, o, e;
   float       r           =  0.0;
   float       x_seg       =  0.0;
   char        c           =    0;
   float       x_end       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(short-cut)----------------------*/
   DEBUG_GRAF   yLOG_double  ("r_prog"    , shape.r_prog);
   if (shape.r_prog < 0) {
      DEBUG_GRAF   yLOG_note    ("r_prog less than zero, draw nothing");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_GRAF   yLOG_char    ("a_letter"  , a_letter);
   if (a_letter == '\0') {
      DEBUG_GRAF   yLOG_note    ("a_letter is null, draw nothing");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(get stroke)------------------------*/
   DEBUG_GRAF   yLOG_value   ("r_pos"     , shape.r_pos);
   rc = LETTER_to_stroke ('-', a_letter, &m, &i, &o, &e);
   DEBUG_GRAF   yLOG_value   ("to_stroke" , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_complex ("letter"    , "%dm, %di, %do, %de", m, i, o, e);
   /*---(center)----------------------------*/
   DEBUG_GRAF   yLOG_complex ("size"      , "%3dw, %3dh, %3dn", shape.sz_width, shape.sz_height, shape.sz_nav);
   x_cen  = shape.sz_width / 2.0;
   x_mid  = shape.sz_nav + (shape.sz_height - shape.sz_nav) / 2.0;
   x_seg  = (2.0 * 3.1415927) / 8.0;
   DEBUG_GRAF   yLOG_complex ("center"    , "%3.0fx, %3.0fy, %3.0fz", x_cen, x_mid, z);
   /*---(start)-----------------------------*/
   if (m < 20) {
      x_controls [0][0] = x_cen;
      x_controls [0][1] = x_mid;
      x_controls [0][2] = z;
      DEBUG_GRAF   yLOG_complex ("center"    , "%dc, %3.0fx, %3.0fy, %3.0fz", c, x_controls [c][0], x_controls [c][1], x_controls [c][2]);
      ++c;
   }
   /*---(inner)-----------------------------*/
   if (m < 20 && i > -1) {
      if      (o < 0)  r = shape.r_inner * 0.80;
      else if (e < 0)  r = shape.r_inner * 1.20;
      else             r = shape.r_inner * 1.00;
      x_controls [1][0] = r * sin (x_seg * i) + x_cen;
      x_controls [1][1] = r * cos (x_seg * i) + x_mid;
      x_controls [1][2] = z;
      DEBUG_GRAF   yLOG_complex ("inner"     , "%dc, %3.0fx, %3.0fy, %3.0fz", c, x_controls [c][0], x_controls [c][1], x_controls [c][2]);
      ++c;
   }
   /*---(outer)-----------------------------*/
   if (m < 20 && o > -1) {
      if      (e < 0)  r = shape.r_outer * 0.85;
      else             r = shape.r_outer * 0.95;
      x_controls [2][0] = r * sin (x_seg * o + x_seg / 2.0) + x_cen;
      x_controls [2][1] = r * cos (x_seg * o + x_seg / 2.0) + x_mid;
      x_controls [2][2] = z;
      DEBUG_GRAF   yLOG_complex ("outer"     , "%dc, %3.0fx, %3.0fy, %3.0fz", c, x_controls [c][0], x_controls [c][1], x_controls [c][2]);
      ++c;
   }
   /*---(edge)------------------------------*/
   if (m < 20 && e > -1) {
      r = shape.r_edge  * 1.00;
      x_controls [3][0] = r * sin (x_seg * e) + x_cen;
      x_controls [3][1] = r * cos (x_seg * e) + x_mid;
      x_controls [3][2] = z;
      DEBUG_GRAF   yLOG_complex ("egde"      , "%dc, %3.0fx, %3.0fy, %3.0fz", c, x_controls [c][0], x_controls [c][1], x_controls [c][2]);
      ++c;
   }
   /*---(draw)------------------------*/
   switch (a_type) {
      /*> case 'c' : glColor4f (0.3f, 0.5f, 1.0f, 0.90f);  break;                        <*/
   case 'c' : glColor4f (0.0f, 0.5f, 1.0f, 0.90f);  break;
   case '2' : glColor4f (0.8f, 0.5f, 0.8f, 0.65f);  break;
   case '3' : glColor4f (0.8f, 0.5f, 0.3f, 0.50f);  break;

   case 'B' : glColor4f (0.0f, 0.0f, 0.0f, 0.90f);  break;
   case  0  : glColor4f (0.0f, 0.3f, 0.7f, 0.50f);  break;
   case  1  : glColor4f (0.0f, 0.0f, 1.0f, 0.50f);  break;
   case  2  : glColor4f (0.3f, 0.0f, 0.7f, 0.50f);  break;
   case  3  : glColor4f (0.5f, 0.0f, 0.5f, 0.50f);  break;
   case  4  : glColor4f (0.7f, 0.0f, 0.3f, 0.50f);  break;
   case  5  : glColor4f (1.0f, 0.0f, 0.0f, 0.50f);  break;
   case  6  : glColor4f (0.7f, 0.3f, 0.0f, 0.50f);  break;
   case  7  : glColor4f (0.5f, 0.5f, 0.0f, 0.50f);  break;
   case  8  : glColor4f (0.3f, 0.7f, 0.0f, 0.50f);  break;
   case  9  : glColor4f (0.0f, 1.0f, 0.0f, 0.50f);  break;
   case 10  : glColor4f (0.0f, 0.7f, 0.3f, 0.50f);  break;
   case 11  : glColor4f (0.0f, 0.5f, 0.5f, 0.50f);  break;


   case '+' : glColor4f (0.8f, 0.5f, 0.3f, 0.40f);  break;
   }
   /*---(draw normal)-----------------------*/
   if (m < 20) {
      x_end = shape.r_prog;
      if (x_end > 1.00)  x_end = 1.00;
      glLineWidth (shape.r_trace);
      glMap1f   (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, c, &x_controls [0][0]);
      glEnable  (GL_MAP1_VERTEX_3);
      glBegin   (GL_LINE_STRIP); {
         for (x_pos = 0.0; x_pos <= x_end; x_pos += 0.05) {
            glEvalCoord1f (x_pos);
         }
      } glEnd();
      glDisable (GL_MAP1_VERTEX_3);
      glLineWidth(0.8);
   }
   /*---(draw special)----------------------*/
   DEBUG_GRAF   yLOG_complex ("prog"      , "%6.3fp, %6.3fi", shape.r_prog, shape.r_inc);
   if (m == 20) {
      c  = 2;
      r  = shape.r_edge  * 1.00;
      if (shape.r_prog <= 1.00)   r  = r * shape.r_prog;
      x  = r * sin (x_seg * rc) + x_cen;
      y  = r * cos (x_seg * rc) + x_mid;
      DEBUG_GRAF   yLOG_complex ("special"   , "%6.3fr, %3.0fx, %3.0fy, %3.0fz", r, x, y, z);
      glLineWidth (shape.r_trace);
      glBegin   (GL_LINE_STRIP); {
         glVertex3f (x_cen, x_mid, z);
         glVertex3f (x    , y    , z);
      } glEnd();
      if (shape.r_prog == 0.00) {
         switch (rc) {
         case 0 : DRAW_press ("S");  break;
         case 1 : DRAW_press ("M");  break;
         }
      }
   } else {
      if (shape.r_prog > 0.99) {
         if (locks [SHIFT] == 0) {
            if (states [SHIFT] != 0)  states [SHIFT] = 0;
         }
         if (locks [MODE ] == 0) {
            if (states [MODE ] != 0)  states [MODE ] = 0;
         }
      }
   }
   /*---(letter output)---------------*/
   shape.r_done [shape.r_exec]     = shape.r_eng [shape.r_exec];
   shape.r_done [shape.r_exec + 1] = '\0';
   /*---(increment position)----------*/
   switch (c) {
   case 2 :
      shape.r_prog += shape.r_inc * 0.85;
      break;
   case 3 :
      shape.r_prog += shape.r_inc * 0.65;
      break;
   case 4 :
      shape.r_prog += shape.r_inc * 0.50;
      break;
   }
   DEBUG_GRAF   yLOG_complex ("prog"      , "%6.3fp, %6.3fi", shape.r_prog, shape.r_inc);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_stroke_all         (void)
{
   /*---(locals)----------------------------*/
   char        i;
   float       x_prog      = 0.0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   if (shape.r_pos < 0) {
      DEBUG_GRAF   yLOG_note    ("r_pos less than zero, no drawing");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (shape.r_pos >= shape.r_len) {
      DEBUG_GRAF   yLOG_note    ("r_pos greater than r_len, no drawing");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_GRAF   yLOG_char    ("r_mode"    , shape.r_mode);
   /*---(draw current only)--------------*/
   if (shape.r_mode == '-') {
      DRAW_stroke     ('c', shape.r_seq [shape.r_pos]);
   }
   /*---(draw last two)------------------*/
   else if (shape.r_mode == '2') {
      x_prog = shape.r_prog;
      if (shape.r_pos > 0) {
         shape.r_prog = 1.00;
         DRAW_stroke     ('2', shape.r_seq [shape.r_pos - 1]);
      }
      shape.r_prog = x_prog;
      DRAW_stroke     ('c', shape.r_seq [shape.r_pos]);
   }
   /*---(draw last two)------------------*/
   else if (shape.r_mode == '3') {
      x_prog = shape.r_prog;
      if (shape.r_pos > 1) {
         shape.r_prog = 1.00;
         DRAW_stroke     ('3', shape.r_seq [shape.r_pos - 2]);
      }
      if (shape.r_pos > 0) {
         shape.r_prog = 1.00;
         DRAW_stroke     ('2', shape.r_seq [shape.r_pos - 1]);
      }
      shape.r_prog = x_prog;
      DRAW_stroke     ('c', shape.r_seq [shape.r_pos]);
   }
   /*---(draw all, normal, with shadow)--*/
   else if (shape.r_mode == '*') {
      if (shape.r_pos == 0) {
         DRAW_stroke     ('c', shape.r_seq [0]);
      } else {
         x_prog = shape.r_prog;
         for (i = 0; i <= shape.r_pos; ++i) {
            if (i < shape.r_pos - 1) {
               shape.r_prog = 1.00;
               DRAW_stroke     ('3', shape.r_seq [i]);
               continue;
            }
            if (i < shape.r_pos) {
               shape.r_prog = 1.00;
               DRAW_stroke     ('2', shape.r_seq [i]);
               continue;
            }
            shape.r_prog = x_prog;
            DRAW_stroke     ('c', shape.r_seq [i]);
         }
      }
   }
   /*---(draw all, normal, rainbow)------*/
   else if (shape.r_mode == 'r') {
      x_prog = shape.r_prog;
      for (i = 0; i <= shape.r_pos; ++i) {
         if (i == shape.r_pos) {
            shape.r_prog = x_prog;
            if (shape.r_prog > 1.00) {
               shape.r_prog = 1.00;
               DRAW_stroke     (i % 12, shape.r_seq [i]);
            } else {
               DRAW_stroke     ('B', shape.r_seq [i]);
            }
         } else {
            shape.r_prog = 1.00;
            DRAW_stroke     (i % 12, shape.r_seq [i]);
         }
      }
   }
   /*---(draw all, normal, no shadow)----*/
   else if (shape.r_mode == 'c') {
      if (shape.r_pos == 0) {
         DRAW_stroke     ('c', shape.r_seq [0]);
      } else {
         x_prog = shape.r_prog;
         for (i = 0; i <= shape.r_pos; ++i) {
            if (i < shape.r_pos - 1) {
               shape.r_prog = 1.00;
               DRAW_stroke     ('c', shape.r_seq [i]);
               continue;
            }
            if (i < shape.r_pos) {
               shape.r_prog = 1.00;
               DRAW_stroke     ('c', shape.r_seq [i]);
               continue;
            }
            shape.r_prog = x_prog;
            DRAW_stroke     ('c', shape.r_seq [i]);
         }
      }
   }
   /*---(draw all now)-------------------*/
   else if (shape.r_mode == '!') {
      for (i = 0; i < shape.r_len; ++i) {
         shape.r_pos = shape.r_exec = i;
         shape.r_prog = 1.00;
         DRAW_stroke     ('c', shape.r_seq [i]);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_done               (void)
{
   int         l           =    0;
   if (shape.r_done_show != 'y')  return 0;
   l = strlen (shape.r_eng);
   glPushMatrix(); {
      glColor4f  (0.0f, 0.0f, 0.0f, 1.0f);
      if        (l < 12) {
         glTranslatef (5, shape.sz_height - 25, 200.0f);
         yFONT_print  (my.txf_sm, my.size_norm +  3, YF_TOPLEF, shape.r_done);
      } else if (l < 20) {
         glTranslatef (5, shape.sz_height - 21, 200.0f);
         yFONT_print  (my.txf_sm, my.size_norm     , YF_TOPLEF, shape.r_done);
      } else if (l < 35) {
         glTranslatef (5, shape.sz_height - 18, 200.0f);
         yFONT_print  (my.txf_sm, my.size_norm -  3, YF_TOPLEF, shape.r_done);
      } else {
         glTranslatef (5, shape.sz_height - 15, 200.0f);
         yFONT_print  (my.txf_sm, my.size_norm -  6, YF_TOPLEF, shape.r_done);
      }
   } glPopMatrix();
   return 0;
}



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
   char        i;
   float       x_prog      = 0.0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(center)----------------------------*/
   x_mid  = shape.sz_nav + (shape.sz_height - shape.sz_nav) / 2.0;
   x_cen  = shape.sz_width / 2.0;
   z      =   20.0;
   /*---(start)--------------------------*/
   long  x_start, x_stop;
   x_start = time_stamp();
   DEBUG_GRAF   yLOG_complex ("position"  , "%6.3fp, %3dl, %3dp, %3dx, %c", shape.r_prog, shape.r_len, shape.r_pos, shape.r_exec, shape.r_seq [shape.r_pos]);
   if (shape.r_pos >= 0 && shape.r_len > 0) {
      if (shape.r_prog >  1.00) {
         if (shape.r_pos >= shape.r_len) {
            shape.r_pos     = shape.r_len - 1;
            shape.r_prog    =  1.01;
         } else {
            ++shape.r_pos;
            if (shape.r_pos >= shape.r_len)   shape.r_pos     = shape.r_len - 1;
            else   {
               if (shape.r_pos > 0 && strchr ("SM", shape.r_seq [shape.r_pos - 1]) == NULL) ++(shape.r_exec);
               shape.r_prog    =  0.00;
            }
            shape.r_letter  = shape.r_seq [shape.r_pos];
         }
      }
   }
   DEBUG_GRAF   yLOG_complex ("position"  , "%6.3fp, %3dl, %3dp, %3dx, %c", shape.r_prog, shape.r_len, shape.r_pos, shape.r_exec, shape.r_seq [shape.r_pos]);
   /*---(draw)---------------------------*/
   glLineWidth (1.0);
   glColor4f   (0.0f, 0.0f, 0.0f, 1.0f);
   DRAW_back    ();
   glPushMatrix(); {
      glTranslatef (x_cen, x_mid,  z);
      DRAW_image   ();
      DRAW_labels  ();
      /*> DRAW_current();                                                                <*/
      /*> DRAW_locks();                                                               <*/
      /*> DRAW_arrows();                                                              <*/
   } glPopMatrix();
   /*---(NN)-------*/
   DRAW_stroke_all ();
   DRAW_navigation ();
   /*> DRAW_stroke  ('"');                                                            <*/
   /*> DRAW_context();                                                                <*/
   /*> DRAW_dots();                                                                   <*/
   DRAW_done       ();
   DRAW_debug      ();
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
         glTranslatef (shape.r_edge * 1.00, 0.0f, 0.0f);
         if (shape.r_color != 1 && shape.r_color != 4)
            glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
         else if ((i % 2) == 0)
            glColor4f (0.0f, 0.0f, 0.8f, 0.2f);
         else
            glColor4f (0.0f, 0.0f, 0.8f, 0.3f);
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
         if (shape.r_color == 1 || shape.r_color == 3 || shape.r_color == 5)
            glColor4f (0.6f, 0.0f, 0.6f, 0.3f);
         else
            glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
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
         if (shape.r_color == 1 || shape.r_color == 2 || shape.r_color == 5)
            glColor4f (0.6f, 0.0f, 0.3f, 0.3f);
         else
            glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
         glCallList   (shape.dl_balls);
      } glPopMatrix();
   }
   glPopMatrix();
   /*---(center)---------------------------*/
   glCallList (shape.dl_center);
   glPushMatrix(); {
      glTranslatef(0.0f, 0.0f, 25.0f);
      if (shape.r_color == 1 || shape.r_color == 0)
         glColor4f (1.0f, 1.0f, 0.0f, 0.4f);
      else
         glColor4f (1.0f, 1.0f, 1.0f, 0.1f);
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
DRAW_label_one          (char a_lvl, char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char       *x_labels    = NULL;
   float       r, d;
   char        c;
   float       x, y;
   float       rad;
   char        t           [LEN_TERSE] = "";
   char        x_pos       =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF   yLOG_svalue  ("a_lvl", a_lvl);
   DEBUG_GRAF   yLOG_svalue  ("a_pos", a_pos);
   DEBUG_GRAF   yLOG_svalue  ("help" , stroke.help);
   /*---(defense)------------------------*/
   if (stroke.help != 20) {
      if (stroke.help > 0 && stroke.help < 10 && stroke.help != a_pos + 1) {
         DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
   }
   if (shape.r_pos < 0) {
      DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   if (a_lvl == 6 && stroke.help == 20 && strchr ("SMTHNAEC", shape.r_letter) == NULL) {
      DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(check for label adjustments)----*/
   if      (states [MODE]) {
      DEBUG_GRAF   yLOG_snote   ("mode");
      x_labels = g_punct;
   } else if (states [SHIFT]) {
      DEBUG_GRAF   yLOG_snote   ("shift");
      x_labels = g_upper;
   } else {
      DEBUG_GRAF   yLOG_snote   ("normal");
      x_labels = g_letters;
   }
   /*---(settings)-----------------------*/
   switch (a_lvl) {
   case 1 :
      DEBUG_GRAF   yLOG_snote   ("inner      ");
      glColor4f (0.0f, 0.0f, 0.0f, 0.7f);
      r     = shape.r_inner * 0.90;
      d     = a_pos * 45;
      x_pos = a_pos * 5;
      c     = x_labels [x_pos];
      break;
   case 2 :
      glColor4f (0.0f, 0.0f, 0.0f, 0.7f);
      DEBUG_GRAF   yLOG_snote   ("outer left ");
      r     = shape.r_outer * 0.91;
      d     = a_pos * 45 - 12;
      x_pos = (a_pos * 5) + 1;
      c     = x_labels [x_pos];
      break;
   case 3 :
      glColor4f (0.0f, 0.0f, 0.0f, 0.7f);
      DEBUG_GRAF   yLOG_snote   ("edge left  ");
      r     = shape.r_edge  * 1.00;
      d     = a_pos * 45 - 35;
      x_pos = (a_pos * 5) + 2;
      c     = x_labels [x_pos];
      break;
   case 4 :
      glColor4f (0.0f, 0.0f, 0.0f, 0.7f);
      DEBUG_GRAF   yLOG_snote   ("outer right");
      r     = shape.r_outer * 0.91;
      d     = a_pos * 45 + 12;
      x_pos = (a_pos * 5) + 3;
      c     = x_labels [x_pos];
      break;
   case 5 :
      glColor4f (0.0f, 0.0f, 0.0f, 0.7f);
      DEBUG_GRAF   yLOG_snote   ("edge right ");
      r     = shape.r_edge  * 1.00;
      d     = a_pos * 45 + 35;
      x_pos = (a_pos * 5) + 4;
      c     = x_labels [x_pos];
      break;
   case 6 :
      DEBUG_GRAF   yLOG_snote   ("special    ");
      glColor4f (1.0f, 0.0f, 0.0f, 0.7f);
      r     = shape.r_edge  * 1.05;
      d     = a_pos * 45;
      x_pos = a_pos;
      c     = g_special [a_pos];
      break;
   }
   DEBUG_GRAF   yLOG_schar   (c);
   if (stroke.help == 20) {
      if (shape.r_loc != x_pos) {
         DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
   }
   /*---(position)-----------------------*/
   rad = (d / 360.0) * (2 * 3.1415927);
   x   = (r * sin (rad));
   y   = (r * cos (rad));
   DEBUG_GRAF   yLOG_svalue  ("x", x);
   DEBUG_GRAF   yLOG_svalue  ("y", y);
   /*---(draw)---------------------------*/
   glPushMatrix(); {
      snprintf     (t , 2, "%c", c);
      DEBUG_GRAF   yLOG_snote   (t);
      glTranslatef (  x,  y,   75.0);
      yFONT_print  (my.txf_sm, my.size_norm, YF_MIDCEN, t );
   } glPopMatrix();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
DRAW_labels             (void)
{
   /*---(locals)---------------------------*/
   int         i;
   float       r;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_GRAF   yLOG_value   ("help"      , stroke.help);
   if (stroke.help <  0) {
      DEBUG_GRAF   yLOG_note    ("text is turned off");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*> if (shape.r_prog < 0.00) {                                                     <* 
    *>    DEBUG_GRAF   yLOG_note    ("nothing moving");                               <* 
    *>    DEBUG_GRAF   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*> if (shape.r_letter == '\0') {                                                  <* 
    *>    DEBUG_GRAF   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(current)--------------------------*/
   /*> glPushMatrix();                                                                <* 
    *> glTranslatef(  0,  0,   75.0);                                                 <* 
    *> yFONT_print (my.txf_bg, my.size_big, YF_MIDCEN, stroke.text);                  <* 
    *> glPopMatrix();                                                                 <*/
   /*---(modes)----------------------------*/
   if (stroke.help < 10 || stroke.help == 13 || stroke.help == 20) {
      r = shape.r_edge * 1.10;
      for (i = 0; i < 8; i += 1)  DRAW_label_one (6, i);
   }
   /*---(edges)----------------------------*/
   if (stroke.help < 10 || stroke.help == 12 || stroke.help == 20) {
      r = shape.r_edge * 1.02;
      for (i = 0; i < 8; i += 1)  DRAW_label_one (3, i);
      for (i = 0; i < 8; i += 1)  DRAW_label_one (5, i);
   }
   /*---(outer)----------------------------*/
   if (stroke.help < 10 || stroke.help == 11 || stroke.help == 14 || stroke.help == 20) {
      r = shape.r_outer  * 0.91;
      for (i = 0; i < 8; i += 1)  DRAW_label_one (2, i);
      for (i = 0; i < 8; i += 1)  DRAW_label_one (4, i);
   }
   /*---(inner)----------------------------*/
   if (stroke.help < 10 || stroke.help == 10 || stroke.help == 14 || stroke.help == 20) {
      r = shape.r_inner  * 0.90;
      for (i = 0; i < 8; i += 1)  DRAW_label_one (1, i);
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
   if (states [MODE] != 0 || locks [MODE] != 0) {
      glPushMatrix(); {
         glLineWidth  (0.8);
         x = - shape.sz_width  / 4;
         y = (shape.sz_height - shape.sz_bar * 2) / 4;
         glColor4f    (1.0f, 1.0f, 0.0f, 0.0f);
         if      (locks  [MODE]   != 0) glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
         else if (states [MODE]   != 0) glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
         glTranslatef (  x,  y,  z);
         glCallList   (shape.dl_box);
      } glPopMatrix();
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
   glPushMatrix  (); {
      glTranslatef  (-r1, r1, z);
      glCallList    (shape.dl_triangle);
   } glPopMatrix();
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
DRAW_debug              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_LABEL] = "";
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_GRAF   yLOG_char    ("r_debug"   , shape.r_debug);
   if (shape.r_debug == '-') {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   glColor4f  (1.0f, 0.5f, 0.0f, 1.0f);
   /*---(config)-------------------------*/
   glPushMatrix (); {
      sprintf (t, "i: %c, %5.3f", shape.r_inc_txt, shape.r_inc);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   glPushMatrix (); {
      sprintf (t, "c: %c, %d", shape.r_color_txt, shape.r_color);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   glPushMatrix (); {
      sprintf (t, "h: %2d, %s", stroke.help, stroke.help_txt);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   glPushMatrix (); {
      sprintf (t, "m: %c", shape.r_mode);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   /*---(positions)----------------------*/
   glPushMatrix (); {
      sprintf (t, "l: %3d", shape.r_len);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   glPushMatrix (); {
      sprintf (t, "r: %3d", shape.r_pos);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   glPushMatrix (); {
      sprintf (t, "e: %3d", shape.r_exec);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   glPushMatrix (); {
      sprintf (t, "c: %c", chrvisible (shape.r_letter));
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
   glPushMatrix (); {
      sprintf (t, "p: %5.3f", shape.r_prog);
      glTranslatef (5, shape.sz_height - 50 - (n++) * 20, 200.0f);
      yFONT_print  (my.txf_sm, my.size_norm, YF_TOPLEF, t);
   } glPopMatrix ();
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
   if (yMACRO_exe_mode () == MACRO_RUN) {
      glColor4f  (0.7f, 0.0f, 0.0f, 1.0f);
      glBegin    (GL_POLYGON); {
         glVertex3f ( x_lef, x_top + 4, z);
         glVertex3f ( x_rig, x_top + 4, z);
         glVertex3f ( x_rig, x_top    , z);
         glVertex3f ( x_lef, x_top    , z);
      } glEnd();
   }
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
      if (states [SHIFT] != 0) glColor4f (1.0f, 1.0f, 0.0f, 0.7f);
      if (locks  [SHIFT] != 0) glColor4f (1.0f, 0.0f, 0.0f, 0.7f);
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
      if (states [MODE ] != 0) glColor4f (1.0f, 1.0f, 0.0f, 0.7f);
      if (locks  [MODE ] != 0) glColor4f (1.0f, 0.0f, 0.0f, 0.7f);
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
