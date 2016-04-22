#===(source start)======================================================================================================================================================#



#===[[ VARABLES ]]======================================================================================================================================================#

#===(current variables)=================================================================================================================================================#
BASE    = petal
DEBUG   = ${BASE}_debug
UNIT    = ${BASE}_unit
HDIR    = /home/member/p_gvskav/petal.v07.revival
IDIR    = /usr/local/bin
MDIR    = /usr/share/man/man1

#===(compilier variables)===============================================================================================================================================#
# must have "-x c" on gcc line so stripped files work with alternate extensions
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INCS    = -I/usr/local/include 

#===(linker options)========================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
LINK    = gcc
LIBDIR  = -L/usr/local/lib
LIBS    = ${LIBDIR}         -lySTR            -lyX11            -lyFONT           -lyHUBLIN         -lX11             -lGL              -lm
LIBD    = ${LIBDIR}         -lySTR_debug      -lyX11            -lyFONT           -lyHUBLIN         -lX11             -lGL              -lm               -lyLOG
LIBU    = ${LIBDIR}         -lySTR_debug      -lyX11            -lyFONT           -lyHUBLIN         -lX11             -lGL              -lm               -lyLOG            -lyVAR            -lyUNIT

#===(file lists)============================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
HEADS   = ${BASE}.h
OBJS    = ${BASE}_main.os   ${BASE}_prog.os   ${BASE}_touch.os  ${BASE}_stroke.os ${BASE}_draw.os   ${BASE}_shape.os  ${BASE}_misc.os
OBJD    = ${BASE}_main.o    ${BASE}_prog.o    ${BASE}_touch.o   ${BASE}_stroke.o  ${BASE}_draw.o    ${BASE}_shape.o   ${BASE}_misc.o
OBJU    = ${BASE}_unit.o    ${BASE}_prog.o    ${BASE}_touch.o   ${BASE}_stroke.o  ${BASE}_draw.o    ${BASE}_shape.o   ${BASE}_misc.o

#===(make variables)====================================================================================================================================================#
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#===[[ EXECUTABLES ]]===================================================================================================================================================#

#all                : ${BASE} ${DEBUG} ${UNIT}
all                : ${BASE} ${DEBUG}

${BASE}            : ${OBJD}
	${LINK}  -o ${BASE}        ${OBJS}   ${LIBS}

${DEBUG}           : ${OBJD}
	${LINK}  -o ${DEBUG}       ${OBJD}   ${LIBD}

#${UNIT}            : ${OBJU}
#	${LINK}  -o ${UNIT}        ${OBJU}   ${LIBU}



#===[[ OBJECT FILES ]]==================================================================================================================================================#

${BASE}_main.o     : ${HEADS}       ${BASE}_main.c
	${COMP}    ${BASE}_main.c                           ${INC}
	${STRIP}   ${BASE}_main.c      > ${BASE}_main.cs
	${COMP}    ${BASE}_main.cs    -o ${BASE}_main.os    ${INC}

${BASE}_prog.o     : ${HEADS}       ${BASE}_prog.c
	${COMP}    ${BASE}_prog.c                           ${INC}
	${STRIP}   ${BASE}_prog.c      > ${BASE}_prog.cs
	${COMP}    ${BASE}_prog.cs    -o ${BASE}_prog.os    ${INC}

${BASE}_touch.o    : ${HEADS}       ${BASE}_touch.c
	${COMP}    ${BASE}_touch.c                          ${INC}
	${STRIP}   ${BASE}_touch.c     > ${BASE}_touch.cs
	${COMP}    ${BASE}_touch.cs   -o ${BASE}_touch.os   ${INC}

${BASE}_stroke.o    : ${HEADS}      ${BASE}_stroke.c
	${COMP}    ${BASE}_stroke.c                         ${INC}
	${STRIP}   ${BASE}_stroke.c    > ${BASE}_stroke.cs
	${COMP}    ${BASE}_stroke.cs  -o ${BASE}_stroke.os  ${INC}

${BASE}_draw.o     : ${HEADS}       ${BASE}_draw.c
	${COMP}    ${BASE}_draw.c                           ${INC}
	${STRIP}   ${BASE}_draw.c      > ${BASE}_draw.cs
	${COMP}    ${BASE}_draw.cs    -o ${BASE}_draw.os    ${INC}

${BASE}_shape.o    : ${HEADS}       ${BASE}_shape.c
	${COMP}    ${BASE}_shape.c                          ${INC}
	${STRIP}   ${BASE}_shape.c     > ${BASE}_shape.cs
	${COMP}    ${BASE}_shape.cs   -o ${BASE}_shape.os   ${INC}

${BASE}_misc.o     : ${HEADS}       ${BASE}_misc.c
	${COMP}    ${BASE}_misc.c                           ${INC}
	${STRIP}   ${BASE}_misc.c      > ${BASE}_misc.cs
	${COMP}    ${BASE}_misc.cs    -o ${BASE}_misc.os    ${INC}

#${BASE}_unit.o     : ${BASE}.unit
#	uUNIT    ${BASE}
#	${COMP}  -x c ${BASE}_unit.code
#	mv ${BASE}_unit.code ${BASE}_unit.c
#	${COMP}  ${BASE}_unit.c



#===[[ SCRIPTS ]]=======================================================================================================================================================#

clean              :
	#---(all versions)--------------------#
	${CLEAN} ${BASE}
	${CLEAN} ${DEBUG}
	${CLEAN} ${UNIT}
	#---(object and stripped files)-------#
	${CLEAN} ${BASE}*.o
	${CLEAN} ${BASE}*.cs
	${CLEAN} ${BASE}*.os
	${CLEAN} ${BASE}*.Sc
	${CLEAN} ${BASE}*.So
	#---(created unit code)---------------#
	${CLEAN} ${UNIT}.code
	${CLEAN} ${UNIT}.c
	#---(junk files)----------------------#
	${CLEAN} *~
	${CLEAN} temp*

bigclean           :
	${CLEAN} .*.swp

install            : ${BASE}
	#---(production version)--------------#
	${COPY}   ${BASE}    ${IDIR}/
	chown     root:root  ${IDIR}/${BASE}
	chmod     0755       ${IDIR}/${BASE}
	@sha1sum  ${BASE}
	#---(debug version)-------------------#
	${COPY}  ${DEBUG}    ${IDIR}/
	chown     root:root  ${IDIR}/${DEBUG}
	chmod     0755       ${IDIR}/${DEBUG}
	@sha1sum  ${DEBUG}
	#---(man page)------------------------#
	rm -f       ${MDIR}/${BASE}.1.bz2
	cp -f       ${BASE}.1  ${MDIR}/
	bzip2       ${MDIR}/${BASE}.1
	chmod 0644  ${MDIR}/${BASE}.1.bz2

remove             :
	#---(all versions)--------------------#
	${CLEAN}  ${IDIR}/${BASE}
	${CLEAN}  ${IDIR}/${DEBUG}
	#---(documentation)-------------------#
	${CLEAN}  ${MDIR}/${BASE}.1.bz2



#*============================----end-of-source---============================*#
