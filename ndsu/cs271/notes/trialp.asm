//JOBNAME JOB (2550130,NDSU),'YOUR NAME',CLASS=S                        TRI00010
/*ROUTE PRINT NDSUVM1.NU------                                          TRI00020
$JOB   ASSIST  2550130                                                  TRI00030
*  <--- YOUR ASSIST PROGRAM HERE; DATA BETWEEN $ENTRY CARDS             TRI00040
* TO RUN THE PROGRAM USE THE COMMAND SUBMIT IN THE COMMAND PREFIX       TRI00050
* AREA OF THE FILE AND RECEIVE OUTPUT IN THE RDRLIST.                   TRI00060
TRIAL    START                                                          TRI00070
         USING  TRIAL,15                                                TRI00080
         SR     2,2                                                     TRI00090
         XREAD  CARD                                                    TRI00100
         LA     1,CARD                                                  TRI00110
LOOP     XDECI  0,0(,1)                                                 TRI00120
         BO     OVER                                                    TRI00130
         ST     0,NUMBERS(2)                                            TRI00140
         XDECO  0,OUT                                                   TRI00150
         XPRNT  OUT-1,13                                                TRI00160
         LA     2,4(2)                                                  TRI00170
         B      LOOP                                                    TRI00180
OVER     CLI    0(1),C'$'                                               TRI00190
         BE     DONE                                                    TRI00200
         XPRNT  =CL30'0*** BAD INPUT *** STOP',30                       TRI00210
DONE     XPRNT  =CL30'0*** PERFECT PROGRAM *** BYE',30                  TRI00220
         XDUMP  NUMBERS,20                                              TRI00230
         BR     14                                                      TRI00240
CARD     DS     CL80                                                    TRI00250
NUMBERS  DC     5F'0'                                                   TRI00260
         DC     C' '                                                    TRI00270
OUT      DS     CL12                                                    TRI00280
         END                                                            TRI00290
$ENTRY                                                                  TRI00300
  5    -8   -12   $                                                     TRI00310
$ENTRY                                                                  TRI00320
/*                                                                      TRI00330
//                                                                      TRI00340
