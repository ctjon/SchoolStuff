//PROGRAM1 JOB (2550130,NDSU),'CHRIS TJON',CLASS=S
/*ROUTE PRINT NDSUVM1.NU110975
$JOB   ASSIST  2550130
*******************************************************
*  CHRISTOPHER C. TJON                                *
*  NAID# 110975-8                                     *
*  PROGRAM1                                           *
*  CS271                                              *
*  DR. UBHAYA                                         *
*  19 JUNE 1990                                       *
*******************************************************
PROG1    START
         USING  PROG1,15
BEG      L      2,G1
         L      4,G2
         L      6,G3
*************** DETERMINE MINIMUM *********************
         CR     2,4
         BP     STMIN1
         BM     STMIN2
RET1     CR     4,6
         BM     STMIN2
         BP     STMIN3
*************** CALCULATE SUM OF G1 G2 G3 *************
RET2     SR     2,2
         SR     4,4
         SR     6,6
         L      2,G1
         L      4,G2
         L      6,G3
         A      2,G2
         A      2,G3
         ST     2,GSUM
*************** CALCULATE AVERAGE *********************
         SR     7,7
         L      7,GSUM
         SR     6,6
         D      6,THREE
         ST     7,GAVG
         XDUMP  G1,28
         BR     14
*************** STORE MINIMUM IF G1 *******************
STMIN1   ST     2,GMIN
         B      RET1
*************** STORE MINIMUM IF G2 *******************
STMIN2   ST     4,GMIN
         B      RET2
*************** STORE MINIMUM IF G3 *******************
STMIN3   ST     6,GMIN
         B      RET2
*************** DATA STATEMENTS ***********************
G1       DC     F'87'
G2       DC     F'65'
G3       DC     F'81'
GMIN     DC     F'0'
GAVG     DC     F'0'
GSUM     DC     F'0'
THREE    DC     F'3'
         END
$ENTRY
//
