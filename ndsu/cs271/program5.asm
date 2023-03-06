//PROG5 JOB (2550130,NDSU),'CHRIS TJON',CLASS=S                         PRO00010
/*ROUTE PRINT NDSUVM1.NU110975                                          PRO00020
$JOB    ASSIST   2550130                                                PRO00030
* DOES NOT WORK CORRECTLY....BUGS
PROG5    START                                                          PRO00040
         BALR  12,0                                                     PRO00050
         USING *,12                                                     PRO00060
         ST    14,SAVE                                                  PRO00070
         XPRNT SPACE-1,133                                              PRO00080
         XPRNT SPACE-1,133                                              PRO00090
         XPRNT HEAD-1,133                                               PRO00100
         XPRNT SPACE-1,133                                              PRO00110
SAVE     DS    F                                                        PRO00120
         DC    C' '                                                     PRO00130
SPACE    DC    CL132' '                                                 PRO00140
         DC    C' '                                                     PRO00150
HEAD     DC    CL132'                               PROGRAM FIVE    '   PRO00160
         L     15,=A(SUBRT)                                             PRO00170
         BALR  14,15                                                    PRO00180
         XPRNT =CL132'0                             THE END         '   PRO00190
         L     14,SAVE             LOADING THE OP SYS INTO 14           PRO00200
         BR    14                                                       PRO00210
SUBRT    CSECT                     SUBROUTINE TO PUT NUM IN OUTPUT      PRO00220
         STM   14,12,12(13)        STORE REGISTERS (OLD)                PRO00230
         BALR  12,0                ESTABLISH BASE REGISTER              PRO00240
         USING *,12                                                     PRO00250
         ST    13,SAVEAREA+4                                            PRO00260
         LA    14,SAVEAREA         LINK SAVE AREAS                      PRO00270
         ST    14,8(13)                                                 PRO00280
         LR    13,14                                                    PRO00290
*                                                                       PRO00300
         LA    1,RESLTLN           LOADING THE RESULT LINE              PRO00310
         EDMK  RESLTLN(14),CARD1   MOVING THE FIRST CARD INTO LINE      PRO00320
         BCTR  1,0                 SUBTRACTING ONE                      PRO00330
         MVI   0(1),C'$'           PUTING A $ IN THE LINE               PRO00340
         XPRNT RESLTLN             PRINTING THE RESULT                  PRO00350
SAVEAREA DS    F                                                        PRO00360
CARD1    DS    F                                                        PRO00370
*                                                                       PRO00380
*                                                                       PRO00390
DONE     L     13,SAVEAREA+4                                            PRO00400
         L     14,12(13)                                                PRO00410
         L     15,RTNCODE                                               PRO00420
         LM    0,12,20(13)                                              PRO00430
         MVI   12(13),X'FF'                                             PRO00440
         BR    14                                                       PRO00450
*                                                                       PRO00460
PARM1    DS    F                                                        PRO00470
PARM2    DS    F                                                        PRO00480
PARM3    DS    F                                                        PRO00490
PARM4    DS    F                                                        PRO00500
PARM5    DS    F                                                        PRO00510
PARMADDR DC    A(PARM1,PARM2,PARM3,PARM4,PARM5)                         PRO00520
         DC    X'80',AL3(PARM5)                                         PRO00530
CARD     DS    CL80                                                     PRO00540
         DC    C' '                                                     PRO00550
         LTORG                                                          PRO00560
RTNCODE  DS    F                                                        PRO00570
RESLTLN  DC    X'402020206B2020214B202040C3D9'                          PRO00580
         END                                                            PRO00590
$ENTRY                                                                  PRO00600
 100          +1        -1        2147483647   -2147483648              PRO00610
                                                                        PRO00620
         -            4812          -88373         +1047    -183        PRO00630
+2147483648 -2147483649 12345678901        -12345678901                 PRO00640
+0  -0                                                                  PRO00650
123,456.78            -999        -999                                  PRO00660
                                             $123,457.78                PRO00670
$ENTRY                                                                  PRO00680
/*                                                                      PRO00690
//                                                                      PRO00700
