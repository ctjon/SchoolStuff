//PROGRAM2 JOB (2550130,NDSU),'CHRIS TJON',CLASS=S
/*ROUTE PRINT NDSUVM1.NU110975
$JOB   ASSIST  2550130
***********************************************************************
*  CHRISTOPHER C. TJON * THIS PROGRAM IS DESIGNED TO TAKE INPUT CARDS *
*  NAID# 110975-8      * CONTAINING A CODE FOLLOWED BY AN AMOUNT. THE *
*  PROGRAM 2           * CODE 0 INDICATES THE AMOUNT IS A DEPOSIT AND *
*  CS271               * THE CODE 1 INDICATES THE AMOUNT IS A CHECK   *
*  DR. UBHAYA          * OR WITHDRAWAL.  WHEN A -1 IS ENCOUNTERED IN  *
*  25 JUNE 1990        * THE INPUT THE PROGRAM TERMINATES.            *
***********************************************************************
PROG2    START
         USING  PROG2,15
R1 EQU 1                       < SET R1 EQUAL TO REGISTER 1           >
R2 EQU 2                       < SET R2 EQUAL TO REGISTER 2           >
R3 EQU 3                       < SET R3 EQUAL TO REGISTER 3           >
R4 EQU 4                       < SET R4 EQUAL TO REGISTER 4           >
R5 EQU 5                       < SET R5 EQUAL TO REGISTER 5           >
R6 EQU 6                       < SET R6 EQUAL TO REGISTER 6           >
R7 EQU 7                       < SET R7 EQUAL TO REGISTER 7           >
R8 EQU 8                       < SET R8 EQUAL TO REGISTER 8           >
R9 EQU 9                       < SET R9 EQUAL TO REGISTER 9           >
R10 EQU 10                     < SET R10 EQUAL TO REGISTER 10         >
R11 EQU 11                     < SET R11 EQUAL TO REGISTER 11         >
R12 EQU 12                     < SET R12 EQUAL TO REGISTER 12         >
R13 EQU 13                     < SET R13 EQUAL TO REGISTER 13         >
F0 EQU 0                       < SET F0 EQUAL TO FLOATING POINT REG 0 >
F2 EQU 2                       < SET F2 EQUAL TO FLOATING POINT REG 2 >
F4 EQU 4                       < SET F4 EQUAL TO FLOATING POINT REG 4 >
F6 EQU 6                       < SET F6 EQUAL TO FLOATING POINT REG 6 >
***********************************************************************
*********< GET BEGINNING BALANCE FROM FIRST CARD >*********************
***********************************************************************
         XPRNT  PGFEED         < PRINT A FORMFEED                     >
         B      HEADER         < BRANCH TO PRINT OUTPUT HEADER        >
RETURNH  XREAD  CARD,80        < READ IN THE FIRST CARD W/INITIAL BAL >
         BNZ    DONE           < IF THERE ARE NO CARDS BRANCH TO DONE >
         XDECI  R5,CARD        < PUT BINARY FORM OF CARD IN R5        >
         ST     R5,BEGBAL      < STORE AMOUNT IN BEGINNING BALANCE    >
         ST     R5,TOTAL       < STORE AMOUNT IN TOTAL BALANCE        >
         XDECO  R5,BBAL+32     < CONVERT BINARY AMOUNT FOR OUTPUT     >
         XPRNT  BBAL,80        < PRINT  STARTING AT AREA TO AREA+80   >
***********************************************************************
*********< GET THE OTHER TRANSACTIONS, LOOP UNTIL -1 ENCOUNTERED >*****
***********************************************************************
         L      R9,NEGONE      < LOAD NEGATIVE ONE IN R9              >
         L      R3,ZERO        < LOAD ZERO IN R3                      >
         L      R4,ONE         < LOAD ONE IN R4                       >
NXTCARD  XREAD  CARD           < READ IN THE NEXT CARD W/TRANSACTION  >
         LA     R1,CARD
NEXTREC  SR     R2,R2
         XDECI  R5,0(,R1)      < PUT TRANSACTION CODE IN R5           >
         BO     OVER
         XDECI  R6,0(,R1)      < PUT AMOUNT OF TRANSACTION IN R6      >
         LA     R2,4(2)
         CR     R9,R5          < COMPARE CODE WITH NEGATIVE ONE       >
         BE     DONE           < IF CODE = -1 THEN BRANCH TO DONE     >
         CR     R5,R3          < COMPARE CODE WITH ZERO               >
         BE     DEPOSIT        < IF CODE = 0 THEN BRANCE TO DEPOSIT   >
         CR     R5,R4          < COMPARE CODE WITH ONE                >
         BE     WITHDR         < IF CODE = 1 THEN BRANCH TO WITHDR    >
RETURN   XDECO  R5,AREA-8      < CONVERT BINARY AMOUNT FOR OUTPUT     >
         XDECO  R6,AREA+15     < CONVERT BINARY AMOUNT FOR OUTPUT     >
         XDECO  R8,AREA+32     < CONVERT BINARY AMOUNT FOR OUTPUT     >
         XPRNT  AREA,80        < PRINT OUT THE OUTPUT AREA            >
         B      NEXTREC        < BRANCH TO GET THE NEXT RECORD        >
OVER     CLI    0(1),C'$'
         BE     NXTCARD
***********************************************************************
*********< CALCULATE AVERAGE AMOUNT PER DEPOSIT >**********************
***********************************************************************
DONE     L      R5,AMTDEP      < LOAD AMOUNT DEPOSITED IN R5          >
         SR     R4,R4          < CLEAR REGISTER 4                     >
         D      R4,NUMDEP      < DIVIDE AMOUNT DEPOSITED BY #DEPOSITS >
         ST     R5,AVGDEP      < STORE AVERAGE AMOUNT DEPOSITED       >
***********************************************************************
*********< CALCULATE AVERAGE AMOUNT PER CHECK >************************
***********************************************************************
         L      R5,AMTCHK      < LOAD AMOUNT OF CHECKS IN R5          >
         SR     R4,R4          < CLEAR REGISTER 4                     >
         D      R4,NUMCHK      < DIVIDE AMOUNT OF CHECKS BY # CHECKS  >
         ST     R5,AVGCHK      < STORE AVERAGE AMOUNT OF EACH CHECK   >
***********************************************************************
         B      FOOTER         < CALL SUBROUTINE TO PRINT FOOTER      >
FINISH   BR     14             < RETURN CONTROL TO OPERATING SYSTEM   >
***********************************************************************
*********< SUBROUTINE TO PRINT OUTPUT HEADER >*************************
***********************************************************************
HEADER   XPRNT  PGFEED
         XPRNT  HLINE1,80      < PRINT OUT FIRST LINE OF HEADER       >
         XPRNT  HLINE2,80      < PRINT OUT SECOND LINE OF HEADER      >
         XPRNT  HLINE3,80      < PRINT OUT THIRD LINE OF HEADER       >
         B      RETURNH        < RETURN TO THE MAIN PROGRAM           >
***********************************************************************
*********< SUBROUTINE TO PRINT OUTPUT FOOTER >*************************
***********************************************************************
FOOTER   L      R1,NUMCHK      < LOAD NUMBER OF CHECKS IN REGISTER 1  >
         XDECO  R1,TEMP1       < CONVERT NUMBER OF CHECKS TO DECIMAL  >
         MVC    FLINE1+38(4),TEMP1+8
         XPRNT  FLINE1,80      < PRINT OUT FIRST LINE OF FOOTER       >
         L      R1,NUMDEP      < LOAD NUMBER OF DEPOSIT IN REGISTER 1 >
         XDECO  R1,TEMP2       < CONVERT NUMBER OF DEPOSIT TO DECIMAL >
         MVC    FLINE2+38(4),TEMP2+8
         XPRNT  FLINE2,80      < PRINT OUT SECOND LINE OF FOOTER      >
         L      R1,AVGCHK      < LOAD AVERAGE CHECK AMOUNT IN R1      >
         XDECO  R1,TEMP3       < CONVERT AVERAGE CHECK AMOUT TO DEC   >
         MVC    FLINE3+38(4),TEMP3+8
         XPRNT  FLINE3,80      < PRINT OUT THIRD LINE OF FOOTER       >
         L      R1,AVGDEP      < LOAD AVERAGE DEPOSIT AMOUNT IN R1    >
         XDECO  R1,TEMP4       < CONVERT AVERAGE DEPOSIT AMOUNT TO DEC)
         MVC    FLINE4+38(4),TEMP4+8
         XPRNT  FLINE4,80      < PRINT OUT FOURTH LINE OF FOOTER      >
         XPRNT  PGFEED         < PUT A PAGEFEED AT THE END OF REPORT  >
         B      FINISH         < RETURN TO THE MAIN PROGRAM           >
***********************************************************************
*********< SUBROUTINE TO ADD A DEPOSIT (CODE 0) >**********************
***********************************************************************
DEPOSIT  L      R8,TOTAL       < LOAD CURRENT BALANCE IN REGISTER 8   >
         L      R10,NUMDEP     < LOAD THE NUMBER OF DEPOSITS IN R10   >
         A      R10,ONE        < ADD ONE TO THE NUMBER OF DEPOSITS    >
         ST     R10,NUMDEP     < STORE THE NUMBER OF DEPOSITS IN R10  >
         L      R11,AMTDEP     < LOAD TOTAL AMOUNT OF DEPOSITS IN R11 >
         AR     R11,R6         < ADD CURRENT DEPOSIT TO TOTAL DEPOSIT >
         ST     R11,AMTDEP     < STORE THE NEW TOTAL AMOUNT DEPOSITED >
         AR     R8,R6          < ADD THE DEPSOIT LOADED IN REGISTER 6 >
         ST     R8,TOTAL       < STORE THE NEW BALANCE IN TOTAL       >
         B      RETURN         < RETURN TO THE MAIN PROGRAM           >
***********************************************************************
*********< SUBROUTINE TO SUBTRACT A CHECK (CODE 1) >*******************
***********************************************************************
WITHDR   L      R8,TOTAL       < LOAD CURRENT BALANCE IN REGISTER 8   >
         L      R10,NUMCHK     < LOAD THE NUMBER OF CHECKS IN R10     >
         A      R10,ONE        < ADD ONE TO THE NUMBER OF CHECKS      >
         ST     R10,NUMCHK     < STORE NUMBER OF CHECKS IN R10        >
         L      R11,AMTCHK     < LOAD TOTAL AMOUNT OF CHECKS IN R11   >
         AR     R11,R6         < ADD CURRENT CHECK TO TOTAL CHECKS    >
         ST     R11,AMTCHK     < STORE THE NEW TOTAL AMOUNT OF CHECKS >
         SR     R8,R6          < SUBTRACT THE WITHDRAWAL LOADED IN R6 >
         ST     R8,TOTAL       < STORE THE NEW BALANCE IN TOTAL       >
         B      RETURN         < RETURN TO THE MAIN PROGRAM           >
***********************************************************************
*********< DATA DEFINITIONS >******************************************
***********************************************************************
CARD     DS     CL80           < DEFINE STORAGE FOR THE INPUT CARDS   >
DUMMY9   DC     CL80' '
PGFEED   DC     CL80'1'        < PAGE FEED FOR TOP OF REPORT          >
DUMMY8   DC     CL80' '
BEGBAL   DC     F'0'           < BEGINNING BALANCE - FIRST LINE INPUT >
AMTDEP   DC     F'0'           < TOTAL AMOUNT DEPOSITED               >
AMTCHK   DC     F'0'           < TOTAL AMOUNT OF CHECKS / WITHDRAWALS >
NUMDEP   DC     F'0'           < NUMBER OR DEPOSITS - ZERO CODES      >
NUMCHK   DC     F'0'           < TOTAL NUMBER OF CHECKS PROCESSED     >
AVGDEP   DC     F'0'           < AVERAGE DEPOSIT AMOUNT               >
AVGCHK   DC     F'0'           < AVERAGE CHECK AMOUNT                 >
TOTAL    DC     F'0'           < TOTAL FINAL BALANCE OF THE ACCOUNT   >
ZERO     DC     F'0'           < THE CONSTANT ZERO                    >
ONE      DC     F'1'           < THE CONSTANT ONE                     >
NEGONE   DC     F'-1'          < THE CONSTANT NEGATIVE ONE            >
DUMMY1   DC     CL80' '        < DEFINE DUMMY AREA TO TAKE UNDERFLOW  >
AREA     DC     CL80' '        < DEFINE FIRST OUTPUT AREA             >
DUMMY    DC     CL80' '
HLINE1   DC     CL48' CHECK/DEPOSIT          AMOUNT          BALANCE'
DUMMY2   DC     CL80' '
HLINE2   DC     CL80'    CODE              (IN CENTS)       (IN CENTS)'
HLINE3   DC     CL99'                                                 '
BBAL     DC     CL80' '
FLINE1   DC     CL50'         #CHECKS                   = '
DUMMY3   DC     CL80' '        < DEFINE DUMMY AREA TO TAKE UNDERFLOW  >
         DC     CL30' '
DUMMY4   DC     CL80' '        < DEFINE DUMMY AREA TO TAKE UNDERFLOW  >
FLINE2   DC     CL50'         #DEPOSITS                 = '
         DC     CL30' '
DUMMY5   DC     CL80' '        < DEFINE DUMMY AREA TO TAKE UNDERFLOW  >
FLINE3   DC     CL50'         AVG. AMT./CHECK           = '
         DC     CL30' '
DUMMY6   DC     CL80' '        < DEFINE DUMMY AREA TO TAKE UNDERFLOW  >
FLINE4   DC     CL50'         AVG. AMT/DEPOSIT          = '
         DC     CL30' '
DUMMY7   DC     CL80' '        < DEFINE DUMMY AREA TO TAKE UNDERFLOW  >
TEMP1    DC     CL16' '
TEMP2    DC     CL16' '
TEMP3    DC     CL16' '
TEMP4    DC     CL16' '
         END
$ENTRY
        4295
0 5210 1 1011 $
 1  1246    $
 0  1000  $
  -1
$ENTRY
//
