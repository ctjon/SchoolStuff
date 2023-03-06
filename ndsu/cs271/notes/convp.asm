//JOBNAME JOB (2550130,NDSU),'YOUR NAME',CLASS=S                        CON00010
/*ROUTE PRINT NDSUVM1.NU------                                          CON00020
$JOB  ASSIST  2550130                                                   CON00030
*  <--- YOUR ASSIST PROGRAM GOES HERE.                                  CON00040
*    DATA GOES BETWEEN THE TWO $ENTRY CARDS.                            CON00050
MP2       START                                                         CON00060
          USING MP2,15                                                  CON00070
*TYPE PROGRAM BELOW THIS                                                CON00080
GETCARD  XREAD CARD,4                                                   CON00090
         PACK  TEMP(8),CARD(4)                                          CON00100
         CVB   4,TEMP                                                   CON00110
         ST    4,RES                                                    CON00120
         XDUMP CARD,16                                                  CON00130
         L      4,=F'-12'                                               CON00140
         CVD   4,TEMP                                                   CON00150
         UNPK  CARD(4),TEMP(8)                                          CON00160
         XDUMP CARD,4                                                   CON00170
         OI    CARD+3,X'F0'                                             CON00180
         XDUMP CARD,16                                                  CON00190
         XPRNT CARD-1,5                                                 CON00200
         BR    14                                                       CON00210
         DC    4C'0'                                                    CON00220
CARD     DS    CL4                                                      CON00230
TEMP     DS    D                                                        CON00240
RES      DS    F                                                        CON00250
         END                                                            CON00260
$ENTRY                                                                  CON00270
 -12                                                                    CON00280
$ENTRY                                                                  CON00290
