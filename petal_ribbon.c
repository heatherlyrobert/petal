/*============================[[    beg-code    ]]============================*/
#include    "petal.h"



char
RIBBON_prev_workspace   (void)
{
   DEBUG_DATA   yLOG_note    ("prev workspace");
   system("fluxbox-remote \"PrevWorkspace\"");
   return 0;
}

char
RIBBON_next_workspace   (void)
{
   DEBUG_DATA   yLOG_note    ("next workspace");
   system("fluxbox-remote \"NextWorkspace\"");
   return 0;
}

char
RIBBON_prev_window      (void)
{
   DEBUG_DATA   yLOG_note    ("previous window");
   system("fluxbox-remote \"PrevWindow (workspace=[current])\"");
   return 0;
}

char
RIBBON_next_window      (void)
{
   DEBUG_DATA   yLOG_note    ("next window");
   system("fluxbox-remote \"NextWindow (workspace=[current])\"");
   return 0;
}

char
RIBBON_letter_help      (void)
{
   DEBUG_DATA   yLOG_note    ("toggle letter help");
   if (stroke.help == 0) stroke.help = -1; else stroke.help = 0;
   return 0;
}

char
RIBBON_show_balls       (void)
{
   DEBUG_DATA   yLOG_note    ("toggle balls");
   if (my.show_pball == 'y')  SHAPE_pball ("hide");
   else                       SHAPE_pball ("show");
   return 0;
}

char
RIBBON_exit             (void)
{
   DEBUG_DATA   yLOG_note    ("exit");
   yCMD_direct (":qa");
   return 0;
}

char
RIBBON_status           (char *r_valid, short *r_x, short *r_y, char *r_touch)
{
   if (r_valid != NULL)  *r_valid = my.m_valid;
   if (r_x     != NULL)  *r_x     = my.m_x;
   if (r_y     != NULL)  *r_y     = my.m_y;
   if (r_touch != NULL)  *r_touch = my.m_touch;
   return 0;
}

char
RIBBON_init             (void)
{
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(configure)----------------------*/
   rc = yVIOPENGL_ribbon_purge  ();
   DEBUG_PROG   yLOG_value   ("purge"     , rc);
   rc = yVIOPENGL_ribbon_config (RIBBON_status, YF_ORA_FULL, YF_BLU_FULL, YF_CRI_FULL, 10);
   DEBUG_PROG   yLOG_value   ("config"    , rc);
   /*---(workspaces)---------------------*/
   rc = yVIOPENGL_ribbon_add    (0x00, -90, "map"    , "warning"    , RIBBON_prev_workspace);
   rc = yVIOPENGL_ribbon_add    (0x10,  90, "map"    , "warning"    , RIBBON_next_workspace);
   /*---(windows)------------------------*/
   rc = yVIOPENGL_ribbon_add    (0x01, 180, "play"   , "play"       , RIBBON_prev_window);
   rc = yVIOPENGL_ribbon_add    (0x11,   0, "play"   , "play"       , RIBBON_next_window);
   /*---(alt/control)--------------------*/
   rc = yVIOPENGL_ribbon_add    (0x02,  90, "play"   , "play"       , NULL);
   rc = yVIOPENGL_ribbon_add    (0x12, -90, "play"   , "play"       , NULL);
   /*---(help)---------------------------*/
   rc = yVIOPENGL_ribbon_add    (0x03,   0, "draw"   , "type"       , RIBBON_letter_help);
   rc = yVIOPENGL_ribbon_add    (0x13,   0, "tech"   , "final_state", RIBBON_show_balls);
   /*---(clipboard)----------------------*/
   rc = yVIOPENGL_ribbon_add    (0x04,   0, "draw"   , "quill"      , NULL);
   rc = yVIOPENGL_ribbon_add    (0x14,   0, "talk"   , "typewriter" , NULL);
   /*---(direction)----------------------*/
   rc = yVIOPENGL_ribbon_add    (0x05,   0, "draw"   , "fill"       , NULL);
   rc = yVIOPENGL_ribbon_add    (0x15,   0, "draw"   , "copy"       , NULL);
   /*---(direction)----------------------*/
   rc = yVIOPENGL_ribbon_add    (0x06,   0, "sec"    , "login"      , NULL);
   rc = yVIOPENGL_ribbon_add    (0x16,   0, "sec"    , "logout"     , RIBBON_exit);
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

