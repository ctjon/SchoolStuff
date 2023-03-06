//JOBNAME JOB (2550130,NDSU),'YOUR NAME',CLASS=S                        MAC00010
/*ROUTE PRINT NDSUVM1.NU------                                          MAC00020
$JOB   ASSIST  2550130                                                  MAC00030
*  <--- YOUR ASSIST PROGRAM HERE; DATA BETWEEN $ENTRY CARDS             MAC00040
         MACRO                                                          MAC00050
&L       ADD   &A,&B,&C,&D                                              MAC00060
         LCLA   &K                                                      MAC00070
&K       SETA   1                                                       MAC00080
&L       L      5,&SYSLIST(&K)                                          MAC00090
.A       ANOP                                                           MAC00100
&K       SETA  &K+1                                                     MAC00110
         A     5,&SYSLIST(&K)                                           MAC00120
         AIF   ('&SYSLIST(&K+1)' NE '').A                               MAC00130
         ST    5,&SYSLIST(1)                                            MAC00140
         MEND                                                           MAC00150
PROG     START                                                          MAC00160
         BALR  12,0                                                     MAC00170
         USING *,12                                                     MAC00180
         ADD   X,Y,Z                                                    MAC00190
         XDUMP X,12                                                     MAC00200
         BR    14                                                       MAC00210
X        DC    F'4'                                                     MAC00220
Y        DC    F'5'                                                     MAC00230
Z        DC    F'3'                                                     MAC00240
         END                                                            MAC00250
$ENTRY                                                                  MAC00260
$ENTRY                                                                  MAC00270
