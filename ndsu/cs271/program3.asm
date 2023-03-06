//PROGRAM3 JOB (2550130 NDSU),'CHRIS',CLASS=S                           PRO00010
/*ROUTE PRINT NDSUVM1.NU110975                                          PRO00020
$JOB  ASSIST  2550130                                                   PRO00030
*********************************************************************** PRO00040
*   CHRISTOPHER C. TJON                                               * PRO00050
*   PROGRAM 3                                                         * PRO00060
*   CS271                                                             * PRO00070
*   DR. UBHAYA                                                        * PRO00080
*********************************************************************** PRO00090
* THIS ONE DOES NOT WORK CORRECTLY
PROG3    START                                                          PRO00100
         BALR  12,0                                                     PRO00110
         USING *,12,11,10                                               PRO00120
TABLE0   L     11,TABLE1                                                PRO00130
         L     10,TABLE2                                                PRO00140
         B     OVER                                                     PRO00150
TABLE1   DC    A(TABLE0+4096)                                           PRO00160
TABLE2   DC    A(TABLE0+8192)                                           PRO00170
TABLE    DS    1024F                                                    PRO00180
OVER     LA    6,TABLE                                                  PRO00190
         LA    7,1024                                                   PRO00200
         L     8,*                                                      PRO00210
         L     9,=F'0'                                                  PRO00220
         MVCL  6,8                                                      PRO00230
         L     0,COUNT                                                  PRO00240
         L     1,TEN24                                                  PRO00250
         SR    4,4                                                      PRO00260
SQARE    SR    2,2                                                      PRO00270
         SR    3,3                                                      PRO00280
         L     3,COUNT                                                  PRO00290
         MR    2,3                                                      PRO00300
         ST    3,TABLE(4)                                               PRO00310
         A     4,=F'4'                                                  PRO00320
         A     0,ONE                                                    PRO00330
         ST    0,COUNT                                                  PRO00340
         BCT   1,SQARE                                                  PRO00350
HEAD0    XPRNT PAGEFEED,1                                               PRO00370
         XPRNT HEAD1,132                                                PRO00380
         XPRNT HEAD2,132                                                PRO00390
         XPRNT =CL132' '                                                PRO00400
         XPRNT =CL132' '                                                PRO00410
         SR    5,5                                                      PRO00430
         SR    4,4                                                      PRO00440
         L     3,LINECT                                                 PRO00450
LOAD     L     8,TABLE(5)                                               PRO00460
         XDECO 8,OUT(4)                                                 PRO00470
         A     5,=F'4'                                                  PRO00480
         C     5,=F'4093'                                               PRO00490
         BH    PRINTM                                                   PRO00500
         A     4,=F'12'                                                 PRO00510
         C     4,=F'122'                                                PRO00520
         BL    LOAD                                                     PRO00530
         L     4,=F'0'                                                  PRO00540
         XPRNT OUT-1,133                                                PRO00550
         MVC   OUT(132),=CL132' '                                       PRO00560
         A     3,=F'1'                                                  PRO00570
         C     3,FORTY5                                                 PRO00580
         BE    NEWPAGE                                                  PRO00590
         B     LOAD                                                     PRO00600
PRINTM   XPRNT OUT-1,133                                                PRO00610
         B     SEARCHPG                                                 PRO00620
NEWPAGE  XPRNT PAGEFEED,1                                               PRO00630
         L     3,LINECT                                                 PRO00640
         C     5,=F'4093'                                               PRO00650
         BL    LOAD                                                     PRO00660
SEARCHPG XPRNT PAGEFEED,1                                               PRO00680
         XPRNT SEARCHL1,132                                             PRO00690
         XPRNT SEARCHL2,132                                             PRO00700
         XPRNT =CL132' '                                                PRO00710
         XPRNT =CL132' '                                                PRO00720
NEXT     XREAD CARD,80                                                  PRO00740
         XDECI 2,CARD                                                   PRO00750
         BM    PRINT                                                    PRO00760
         CLI   2(1),C'$'                                                PRO00770
         BO    DONE                                                     PRO00780
         SR    4,4                                                      PRO00790
         L     5,=F'1024'                                               PRO00800
SEARCH   CR    4,5                                                      PRO00810
         BH    EQUALNTF                                                 PRO00820
         LA    9,0(4,5)                                                 PRO00830
         D     8,=F'2'                                                  PRO00840
         LR    3,9                                                      PRO00850
         M     6,=F'4'                                                  PRO00860
         C     2,TABLE(9)                                               PRO00870
         BE    FOUND                                                    PRO00880
         BNL   SERCHTOP                                                 PRO00890
         S     3,=F'4'                                                  PRO00910
         LR    5,3                                                      PRO00920
         B     SEARCH                                                   PRO00930
SERCHTOP LA    4,1(,3)                                                  PRO00950
         B     SEARCH                                                   PRO00960
FOUND    XDECO 2,OUT+40                                                 PRO00980
         L     7,TABLE(9)                                               PRO00990
         XDECO 7,OUT+50                                                 PRO01000
         XPRNT OUT,132                                                  PRO01010
         B     NEXT                                                     PRO01020
EQUALNTF XDECO 2,OUT+40                                                 PRO01040
         L     7,TABLE(9)                                               PRO01050
         XDECO 7,OUT+60                                                 PRO01060
         XPRNT OUT,132                                                  PRO01070
         B     NEXT                                                     PRO01080
PRINT    XDECO 2,OUT+40                                                 PRO01090
         XPRNT OUT,132                                                  PRO01100
         B     NEXT                                                     PRO01110
DONE     BR    14                                                       PRO01150
CARD     DS    CL80                                                     PRO01170
PAGEFEED DC    C'1'                                                     PRO01180
HEAD1    DC    CL60' '                                                  PRO01190
         DC    CL11'C. TJON'                                            PRO01200
         DC    CL61' '                                                  PRO01210
HEAD2    DC    CL60' '                                                  PRO01220
         DC    CL12'PROGRAM 3 '                                         PRO01230
         DC    CL60' '                                                  PRO01240
SEARCHL1 DC    CL45' '                                                  PRO01250
         DC    CL40' NUMBER     SQUARE    NUMBER     ROOT'              PRO01260
         DC    CL47' '                                                  PRO01270
SEARCHL2 DC    CL45' '                                                  PRO01280
         DC    CL40'SEARCHED     FOUND     FOUND      FOUND '           PRO01290
         DC    CL47' '                                                  PRO01300
DB       DS    D                                                        PRO01310
         DC    C' '                                                     PRO01320
OUT      DC    CL132' '                                                 PRO01330
TEMP     DS    C'               '                                       PRO01420
ONE      DC    F'1'                                                     PRO01380
ELEVEN   DC    F'11'                                                    PRO01360
FORTY5   DC    F'45'                                                    PRO01350
TEN24    DC    F'1024'                                                  PRO01390
         DC    C' '                                                     PRO01400
COUNT    DC    F'0'                                                     PRO01370
CHECK    DC    CL30' '                                                  PRO01410
LINECT   DC    F'0'                                                     PRO01340
         END                                                            PRO01430
$ENTRY                                                                  PRO01450
25                                                                      PRO01460
2048                                                                    PRO01470
38                                                                      PRO01480
567                                                                     PRO01490
-86                                                                     PRO01500
9                                                                       PRO01510
555                                                                     PRO01520
2055                                                                    PRO01530
45                                                                      PRO01540
-8                                                                      PRO01550
7                                                                       PRO01560
3                                                                       PRO01570
529                                                                     PRO01580
$                                                                       PRO01590
$ENTRY                                                                  PRO01600
/*                                                                      PRO01610
//                                                                      PRO01620
