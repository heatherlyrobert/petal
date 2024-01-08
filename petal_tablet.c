/*============================[[    beg-code    ]]============================*/
#include    "petal.h"


struct {
   char        abbr;
   char        name        [LEN_LABEL];
   int         left;
   int         topp;
   int         wide;
   int         tall;
   char        pen;                         /* /dev/input? for pen input      */
   char        but;                         /* /dev/input? for button input   */
   char        desc        [LEN_LABEL];
} s_tablets [LEN_LABEL] = {
   /* ··········´··········  */
   { '*', "xppen"                ,     0,     0, 32767, 32767,  7,  6, "xp-pen 11 artist pro"                        },
   {  0 , ""                     ,     0,     0,     0,     0,  0,  0,  ""                                            },
};


char
TABLET_set_by_abbr      (char a_abbr)
{
   char        rce         =  -10;
   char        i           =    0;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (s_tablets [i].abbr == 0)          break;
      if (s_tablets [i].abbr != a_abbr)     continue;
      my.t_left  = s_tablets [i].left;
      my.t_topp  = s_tablets [i].topp;
      my.t_wide  = s_tablets [i].wide;
      my.t_tall  = s_tablets [i].tall;
      return 1;
   }
   return 0;
}
