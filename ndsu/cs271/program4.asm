//PROG4 JOB (2550130,NDSU),'CHRIS TJON',CLASS=S                         PRO00010
/*ROUTE PRINT NDSUVM1.NU110975                                          PRO00020
$JOB  ASSIST  2550130                                                   PRO00030
**********************************************************************  PRO00040
*  PROGRAM 4                                                         *  PRO00050
*  CHRISTOPHER C. TJON                                               *  PRO00060
*  110975-8                                                          *  PRO00070
*  FOR CS271                                                         *  PRO00080
*  DR. UBHAYA                                                        *  PRO00090
**********************************************************************  PRO00100
         MACRO                                                          PRO00110
&CONVT   HEDIT &L,&M,&N                                                 PRO00120
         LCLA  &NUMBER                                                  PRO00130
         LCLA  &COUNT                                                   PRO00140
&NUMBER  SETA  1                                                        PRO00150
         ST    2,S&SYSNDX                                               PRO00160
.A       ANOP                                                           PRO00170
&COUNT   SETA  1                                                        PRO00180
&CONVT   LH    2,&SYSLIST(&NUMBER,&COUNT)                               PRO00190
&COUNT   SETA  &COUNT+1                                                 PRO00200
         STH   2,&SYSLIST(&NUMBER,&COUNT)                               PRO00210
&NUMBER  SETA  &NUMBER+1                                                PRO00220
         AIF   ('&NUMBER' LT '4').A                                     PRO00230
         LH    2,S&SYSNDX                                               PRO00240
         B     T&SYSNDX                                                 PRO00250
S&SYSNDX DS    F                                                        PRO00260
T&SYSNDX DS    0F                                                       PRO00270
         MEND                                                           PRO00280
**********************************************************************  PRO00290
PROG     START                                                          PRO00300
         BALR  12,0                                                     PRO00310
         USING *,12                                                     PRO00320
         HEDIT (A,B),(C,D),(E,F)                                        PRO00330
         LH    3,B                                                      PRO00340
         LH    4,D                                                      PRO00350
         LH    5,F                                                      PRO00360
         XDECO 3,OUT                                                    PRO00370
         XDECO 4,OUT+12                                                 PRO00380
         XDECO 5,OUT+24                                                 PRO00390
         XPRNT =CL132' '                                                PRO00400
         XPRNT =CL132'             THESE ARE THE NUMBERS              ' PRO00410
         XPRNT =CL132' '                                                PRO00420
         XPRNT OUT-1,37                                                 PRO00430
         HEDIT (G,H),(I,J),(L,M)                                        PRO00440
         LH    3,H                                                      PRO00450
         LH    4,J                                                      PRO00460
         LH    5,L                                                      PRO00470
         XDECO 3,OUT                                                    PRO00480
         XDECO 4,OUT+12                                                 PRO00490
         XDECO 5,OUT+24                                                 PRO00500
         XPRNT OUT-1,37                                                 PRO00510
         XPRNT =CL132' '                                                PRO00520
         XPRNT =CL132'             THAT WERE SWAPPED                  ' PRO00530
         XPRNT =CL132' '                                                PRO00540
         BR    14                                                       PRO00550
         DC    C' '                                                     PRO00560
OUT      DS    CL48' '                                                  PRO00570
A        DC    H'15'                                                    PRO00580
B        DS    CL6                                                      PRO00590
C        DC    H'2342'                                                  PRO00600
D        DS    CL6                                                      PRO00610
E        DC    H'1236'                                                  PRO00620
F        DS    CL6                                                      PRO00630
G        DC    H'-844'                                                  PRO00640
H        DS    CL6                                                      PRO00650
I        DC    H'-9007'                                                 PRO00660
J        DS    CL6                                                      PRO00670
L        DC    H'6100'                                                  PRO00680
M        DS    CL6                                                      PRO00690
         END                                                            PRO00700
$ENTRY                                                                  PRO00710
$ENTRY                                                                  PRO00720
/*                                                                      PRO00730
//                                                                      PRO00740
