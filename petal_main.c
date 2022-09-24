/*============================[[    beg-code    ]]============================*/
#include    "petal.h"




char
main                    (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(debugging)----------------------*/
   rc = PROG_urgents (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("urgents"   , rc);
   if (rc <  0) { PROG_shutdown (); return --rce; }
   /*---(initialization)-----------------*/
   rc = PROG_startup (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("startup"   , rc);
   if (rc <  0) { PROG_shutdown (); return --rce; }
   /*---(visual setup)-------------------*/
   rc = PROG_dawn    ();
   DEBUG_PROG   yLOG_value    ("dawn"      , rc);
   if (rc <  0) { PROG_shutdown (); return --rce; }
   /*---(main-loop)----------------------*/
   rc = yVIOPENGL_main  ("10ms", "100ms", NULL);
   DEBUG_PROG   yLOG_value    ("main"      , rc);
   /*---(visual shutdown)----------------*/
   rc = PROG_dusk     ();
   DEBUG_PROG   yLOG_value    ("dusk"      , rc);
   /*---(wrap-up)------------------------*/
   rc = PROG_shutdown ();
   DEBUG_PROG   yLOG_value    ("shutdown"  , rc);
   /*---(complete)-----------------------*/
   return 0;
}

/*> int                                                                                <* 
 *> main               (int a_argc, char *a_argv[])                                    <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----------+-+/                                        <* 
 *>    int         rc          = 0;             /+ generic return code            +/   <* 
 *>    /+---(start-up)-----------------------+/                                        <* 
 *>    if (rc == 0)  rc = PROG_logger (a_argc, a_argv);                                <* 
 *>    if (rc == 0)  rc = PROG_init   ();                                              <* 
 *>    if (rc == 0)  rc = PROG_urgs   (a_argc, a_argv);                                <* 
 *>    if (rc == 0)  rc = PROG_args   (a_argc, a_argv);                                <* 
 *>    if (rc == 0)  rc = PROG_begin  ();                                              <* 
 *>    if (rc != 0) {                                                                  <* 
 *>       PROG_end    ();                                                              <* 
 *>       return -1;                                                                   <* 
 *>    }                                                                               <* 
 *>    /+---(mainloop)-----------------------+/                                        <* 
 *>    PROG_event();                                                                   <* 
 *>    /+---(shutdown)-----------------------+/                                        <* 
 *>    PROG_end();                                                                     <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/* PURPOSE : process the xwindows event stream                                */
char
PROG_event         (void)
{
   int x, y;         /* x,y coordinate of pointer        */
   int r;            /* radius -- distance from center   */
   int rc;
   int         c           = 0;
   char  x_cmd[200] = "";
   tTSPEC      x_dur;
   /*---(prepare)------------------------*/
   /*  second = 1,000,000,000,000,000,000 atto seconds  (as)
    *         =     1,000,000,000,000,000 femto seconds (fs)
    *         =         1,000,000,000,000 pico seconds  (ps)
    *         =             1,000,000,000 nano seconds  (ns) a light-foot
    *         =                 1,000,000 micro seconds (us)
    *         =                     1,000 milli seconds (ms)
    */
   x_dur.tv_sec    = 0;
   x_dur.tv_nsec   = my.loop_msec * 1000000;
   /*---(for keypresses)-------------------*/
   /*> XKeyEvent *key_event;                                                          <* 
    *> int        the_bytes;                                                          <* 
    *> char       the_key[5];                                                         <*/
   /*> printf ("begin loop\n");                                                       <*/
   DRAW_main ();
   DEBUG_TOPS   printf("EVENT LOOP :: begin -------------\n\n");
   while (1) {
      if (XPending(YX_DISP)) {
         XNextEvent(YX_DISP, &YX_EVNT);
         /*> printf ("event %5d\n", ++c);                                             <*/
         switch(YX_EVNT.type) {
         case Expose:
            DEBUG_LOOP   printf("V> main() event loop -- exposure\n");
            DRAW_main();
            break;

         case ConfigureNotify:
            DEBUG_LOOP   printf("V> main() event loop -- configure\n");
            /*> if (YX_EVNT.xconfigure.width != X || YX_EVNT.xconfigure.height != Y) {                                        <* 
             *>    DEBUG_LOOP   printf("   - moved    x=%4d, y=%4d", X, Y);                                                   <* 
             *>    X = YX_EVNT.xconfigure.width;                                                                              <* 
             *>    Y = YX_EVNT.xconfigure.height;                                                                             <* 
             *>    DEBUG_LOOP   printf("  TO  x=%4d, y=%4d\n", X, Y);                                                         <* 
             *> }                                                                                                             <* 
             *> if (YX_EVNT.xconfigure.width != (int) WIDTH || YX_EVNT.xconfigure.height != (int) HEIGHT) {                   <* 
             *>    DEBUG_LOOP   printf("   - resized  w=%3d, h=%3d¦", YX_EVNT.xconfigure.width, YX_EVNT.xconfigure.height);   <* 
             *>    DRAW_resize(shape.sz_width, shape.sz_height);                                                              <* 
             *> }                                                                                                             <*/
            break;

         case KeyPress:
            break;

         case KeyRelease:
            break;

         case ButtonPress:
            /*---(get basic info)------------------*/
            x = YX_EVNT.xbutton.x - shape.sz_centerx;
            y = shape.sz_centery - YX_EVNT.xbutton.y;
            r = sqrt((x * x) + (y * y));
            /*---(determine section)---------------*/
            if      (y <= -shape.sz_centery) stroke.section = 'n';   /* navigation bar   */
            else if (r >=  shape.r_max)   stroke.section = 'a';   /* arrows           */
            else                         stroke.section = 'p';   /* petal            */
            /*---(handle it)-----------------------*/
            printf("ButtonPress   at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            DEBUG_LOOP    printf("ButtonPress   at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            if (stroke.section == 'p') STROKE_begin(x, y, r);
            break;

         case MotionNotify:
            /*---(defense)-------------------------*/
            if (stroke.section != 'p')    break;
            /*---(get basic info)------------------*/
            x = YX_EVNT.xbutton.x - shape.sz_centerx;
            y = shape.sz_centery - YX_EVNT.xbutton.y;
            r = sqrt((x * x) + (y * y));
            printf("ButtonMove    at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            DEBUG_LOOP    printf("MotionNotify  at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            /*---(handle it)-----------------------*/
            stroke_next(x, y, r);
            break;

         case ButtonRelease:
            /*---(get basic info)------------------*/
            x = YX_EVNT.xbutton.x - shape.sz_centerx;
            y = shape.sz_centery - YX_EVNT.xbutton.y;
            r = sqrt((x * x) + (y * y));
            printf("ButtonRelease at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            DEBUG_LOOP    printf("ButtonRelease at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            /*---(handle it)-----------------------*/
            switch (stroke.section) {
            case 'n' : rc = event_navigation(x);    break;
            case 'a' : rc = event_arrows(x, y);     break;
            case 'p' : rc = STROKE_end(x, y, r);    break;
            }
            break;

         default          :
            DEBUG_LOOP   printf("UNKNOWN event (%d)¦", YX_EVNT.type);
            break;
         }
      }
      rc = 0;
      /*> rc = TOUCH_read ();                                                         <*/
      if (rc == 0) DRAW_main ();
      /*---(sleeping)--------------------*/
      nanosleep    (&x_dur, NULL);
      /*> if (ndot > 0 && (ndot % 3) == 0) DRAW_main ();                            <*/
      /*> while (rc == 0)  rc = TOUCH_read ();                                        <*/
   }
   DEBUG_TOPS   printf("EVENT LOOP :: end ---------------\n\n");
   return 0;
}



/*============================[[ end-of-code ]]===============================*/
