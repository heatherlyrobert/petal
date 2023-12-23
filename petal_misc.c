/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



/*---(GLX Globals)---------------------------------*/
/*> XWindowAttributes      gwa;                                                       <*/

ulong  g_focus = 0;


FILE   *f = NULL;


/*============================--------------------============================*/
/*===----                         layout tables                        ----===*/
/*============================--------------------============================*/


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

char*
unit_accessor(char *a_question, int a_num)
{
   if        (strcmp(a_question, "dot")         == 0) {
      if (ndot == 0) {
         snprintf(unit_answer, LEN_RECD, "Dot Trace (%4d) : there are no dots", a_num);
      } else if (a_num < 0) {
         snprintf(unit_answer, LEN_RECD, "Dot Trace (%4d) : can not be negative", a_num);
      } else if (a_num >= ndot) {
         snprintf(unit_answer, LEN_RECD, "Dot Trace (%4d) : out of range %3d to %3d", a_num, 0, ndot - 1);
      } else
         snprintf(unit_answer, LEN_RECD, "Dot Trace (%4d) : %4dx, %4dy, %4dc", a_num, dots[a_num].relx, dots[a_num].rely, ndot);
   } else if (strcmp(a_question, "current")     == 0) {
      if (stroke.outward) {
         snprintf(unit_answer, LEN_RECD, "Current   (fore) : 0=%2d, 1=%2d, 2=%2d, 3=%2d, m=%2d", stroke.zth, stroke.fst, stroke.snd, stroke.trd, stroke.max);
      } else {
         snprintf(unit_answer, LEN_RECD, "Current   (back) : 0=%2d, 1=%2d, 2=%2d, 3=%2d, m=%2d", stroke.zth, stroke.fst, stroke.snd, stroke.trd, stroke.max);
      }
   } else if (strcmp(a_question, "status")      == 0) {
      snprintf(unit_answer, LEN_RECD, "Letter Status    : done=%d, accept=%d, fail=%d", stroke.done, stroke.pass, stroke.fail);
   }
   return unit_answer;
}



/*============================================================================*
 *=======                         END OF SOURCE                        =======*
 *============================================================================*/
