/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



int
main               (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = 0;             /* generic return code            */
   /*---(start-up)-----------------------*/
   if (rc == 0)  rc = PROG_logger (a_argc, a_argv);
   if (rc == 0)  rc = PROG_init   ();
   if (rc == 0)  rc = PROG_urgs   (a_argc, a_argv);
   if (rc == 0)  rc = PROG_args   (a_argc, a_argv);
   if (rc == 0)  rc = PROG_begin  ();
   if (rc != 0) {
      PROG_end    ();
      return -1;
   }
   /*---(mainloop)-----------------------*/
   PROG_event();
   /*---(shutdown)-----------------------*/
   PROG_end();
   /*---(complete)-----------------------*/
   return 0;
}

/* PURPOSE : process the xwindows event stream                                */
char
PROG_event         (void)
{
   int x, y;         /* x,y coordinate of pointer        */
   int r;            /* radius -- distance from center   */
   int rc;
   int         c           = 0;
   char  x_cmd[200] = "";
   /*---(for keypresses)-------------------*/
   /*> XKeyEvent *key_event;                                                          <* 
    *> int        the_bytes;                                                          <* 
    *> char       the_key[5];                                                         <*/
   printf ("begin loop\n");
   DEBUG_TOPS   printf("EVENT LOOP :: begin -------------\n\n");
   while (1) {
      if (XPending(DISP)) {
         XNextEvent(DISP, &EVNT);
         printf ("event %5d\n", ++c);
         switch(EVNT.type) {
         case Expose:
            DEBUG_LOOP   printf("V> main() event loop -- exposure\n");
            /*> still trying to understand why these two stroke calls,   */
            /*> stroke_begin(0, 0, 0);                                                <* 
             *> stroke_end(0, 0, 0);                                                  <* 
             *> DRAW_main();                                                          <*/
            break;

         case ConfigureNotify:
            DEBUG_LOOP   printf("V> main() event loop -- configure\n");
            if (EVNT.xconfigure.width != X || EVNT.xconfigure.height != Y) {
               DEBUG_LOOP   printf("   - moved    x=%4d, y=%4d", X, Y);
               X = EVNT.xconfigure.width;
               Y = EVNT.xconfigure.height;
               DEBUG_LOOP   printf("  TO  x=%4d, y=%4d\n", X, Y);
            }
            if (EVNT.xconfigure.width != (int) WIDTH || EVNT.xconfigure.height != (int) HEIGHT) {
               DEBUG_LOOP   printf("   - resized  w=%3d, h=%3d\n", EVNT.xconfigure.width, EVNT.xconfigure.height);
               DRAW_resize(shape.sz_width, shape.sz_height);
            }
            break;

         case KeyPress:
            break;

         case KeyRelease:
            break;

         case ButtonPress:
            /*---(get basic info)------------------*/
            x = EVNT.xbutton.x - shape.sz_centerx;
            y = shape.sz_centery - EVNT.xbutton.y;
            r = sqrt((x * x) + (y * y));
            /*---(determine section)---------------*/
            if      (y <= -shape.sz_centery) stroke.section = 'n';   /* navigation bar   */
            else if (r >=  shape.r_max)   stroke.section = 'a';   /* arrows           */
            else                         stroke.section = 'p';   /* petal            */
            /*---(handle it)-----------------------*/
            printf("ButtonPress   at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            DEBUG_LOOP    printf("ButtonPress   at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            if (stroke.section == 'p') stroke_begin(x, y, r);
            break;

         case MotionNotify:
            /*---(defense)-------------------------*/
            if (stroke.section != 'p')    break;
            /*---(get basic info)------------------*/
            x = EVNT.xbutton.x - shape.sz_centerx;
            y = shape.sz_centery - EVNT.xbutton.y;
            r = sqrt((x * x) + (y * y));
            printf("ButtonMove    at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            DEBUG_LOOP    printf("MotionNotify  at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            /*---(handle it)-----------------------*/
            stroke_next(x, y, r);
            break;

         case ButtonRelease:
            /*---(get basic info)------------------*/
            x = EVNT.xbutton.x - shape.sz_centerx;
            y = shape.sz_centery - EVNT.xbutton.y;
            r = sqrt((x * x) + (y * y));
            printf("ButtonRelease at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            DEBUG_LOOP    printf("ButtonRelease at %4dx, %4dy, %4dr, %cs\n", x, y, r, stroke.section);
            /*---(handle it)-----------------------*/
            switch (stroke.section) {
            case 'n' : rc = event_navigation(x);    break;
            case 'a' : rc = event_arrows(x, y);     break;
            case 'p' : rc = stroke_end(x, y, r);    break;
            }
            break;

         default          :
            DEBUG_LOOP   printf("UNKNOWN event (%d)\n", EVNT.type);
            break;
         }
      }
      rc = 0;
      rc = touch_read ();
      if (rc == 0) DRAW_main ();
      /*> if (ndots > 0 && (ndots % 3) == 0) DRAW_main ();                            <*/
      /*> while (rc == 0)  rc = touch_read ();                                        <*/
   }
   DEBUG_TOPS   printf("EVENT LOOP :: end ---------------\n\n");
   return 0;
}



/*============================[[ end-of-code ]]===============================*/
