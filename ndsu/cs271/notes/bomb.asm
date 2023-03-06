//JOBNAME JOB  (2550130,NDSU),'YOUR NAME',CLASS=A,TIME=(,10),           BOM00010
//   MSGLEVEL=(1,1),MSGCLASS=A                                          BOM00020
/*ROUTE PRINT NDSU                                                      BOM00030
/*JOBPARM COPIES=1                                                      BOM00040
//*  GIVE THE COMMAND JSUBMIT IN THE PREFIX AREA TO GET THE OUTPUT.     BOM00050
//*  OUTPUT WILL BE ROUTED DIRECTLY TO THE COMPUTER CENTER.             BOM00060
//*  ASSEMBLY SOURCE GOES IMMEDIATELY AFTER 'ASM.SYSIN DD *'            BOM00070
//*  PROGRAM DATA GOES IMMEDIATELY AFTER 'GO.SYSIN DD *'                BOM00080
//A      EXEC  ASMFCLG                                                  BOM00090
//ASM.SYSIN DD *                                                        BOM00100
BOMB     START                                                          BOM00110
         STM   14,12,12(13)   STASH AWAY REGISTERS                      BOM00120
         BALR  12,0           ESTABLISH IMPLIED BASE REGISTER           BOM00130
         USING *,12                                                     BOM00140
         ST    13,SV0$AREA+4  STASH MAP TO TREASURE AND...              BOM00150
         LA    14,SV0$AREA    LINK SAVE AREAS                           BOM00160
         ST    14,8(13)                                                 BOM00170
         LR    13,14          POINT GPR13 AT LOCAL SAVE AREA            BOM00180
         MVC   RT0$CODE(4),=F'0'  SET RETURN CODE TO ZERO               BOM00190
*                                                                       BOM00200
         L     15,=V(SUB1)                                              BOM00210
         BALR  14,15                                                    BOM00220
*                                                                       BOM00230
DONE0    L     13,SV0$AREA+4  RESTORE MAP TO TREASURE                   BOM00240
         L     14,12(13)      RESTORE RETURN ADDRESS                    BOM00250
         L     15,RT0$CODE    SET RETURN CODE                           BOM00260
         LM    0,12,20(13)    RESTORE ALL OTHER REGISTERS               BOM00270
         MVI   12(13),X'FF'   SET FOOTPRINT IN SAVE AREA                BOM00280
         BR    14             RETURN                                    BOM00290
*                                                                       BOM00300
RT0$CODE DS    F                                                        BOM00310
SV0$AREA DS    18F                                                      BOM00320
         LTORG                                                          BOM00330
         EJECT                                                          BOM00340
SUB1     CSECT                                                          BOM00350
         STM   14,12,12(13)   STASH AWAY REGISTERS                      BOM00360
         BALR  12,0           ESTABLISH IMPLIED BASE REGISTER           BOM00370
         USING *,12                                                     BOM00380
         ST    13,SV1$AREA+4  STASH MAP TO TREASURE AND...              BOM00390
         LA    14,SV1$AREA    LINK SAVE AREAS                           BOM00400
         ST    14,8(13)                                                 BOM00410
         LR    13,14          POINT GPR13 AT LOCAL SAVE AREA            BOM00420
         MVC   RT1$CODE(4),=F'0'  SET RETURN CODE TO ZERO               BOM00430
*                                                                       BOM00440
         L     15,=V(SUB2)                                              BOM00450
         BALR  14,15                                                    BOM00460
*                                                                       BOM00470
DONE1    L     13,SV1$AREA+4  RESTORE MAP TO TREASURE                   BOM00480
         L     14,12(13)      RESTORE RETURN ADDRESS                    BOM00490
         L     15,RT1$CODE    SET RETURN CODE                           BOM00500
         LM    0,12,20(13)    RESTORE ALL OTHER REGISTERS               BOM00510
         MVI   12(13),X'FF'   SET FOOTPRINT IN SAVE AREA                BOM00520
         DC    X'0000'        BOMB                                      BOM00530
*                                                                       BOM00540
RT1$CODE DS    F                                                        BOM00550
SV1$AREA DS    18F                                                      BOM00560
         LTORG                                                          BOM00570
         EJECT                                                          BOM00580
SUB2     CSECT                                                          BOM00590
         STM   14,12,12(13)   STASH AWAY REGISTERS                      BOM00600
         BALR  12,0           ESTABLISH IMPLIED BASE REGISTER           BOM00610
         USING *,12                                                     BOM00620
         ST    13,SV2$AREA+4  STASH MAP TO TREASURE AND...              BOM00630
         LA    14,SV2$AREA    LINK SAVE AREAS                           BOM00640
         ST    14,8(13)                                                 BOM00650
         LR    13,14          POINT GPR13 AT LOCAL SAVE AREA            BOM00660
         MVC   RT2$CODE(4),=F'0'  SET RETURN CODE TO ZERO               BOM00670
*                                                                       BOM00680
         MVC   RT2$CODE(4),=F'8'                                        BOM00690
*                                                                       BOM00700
DONE2    L     13,SV2$AREA+4  RESTORE MAP TO TREASURE                   BOM00710
         L     14,12(13)      RESTORE RETURN ADDRESS                    BOM00720
         L     15,RT2$CODE    SET RETURN CODE                           BOM00730
         LM    0,12,20(13)    RESTORE ALL OTHER REGISTERS               BOM00740
         MVI   12(13),X'FF'   SET FOOTPRINT IN SAVE AREA                BOM00750
         BR    14             RETURN                                    BOM00760
*                                                                       BOM00770
RT2$CODE DS    F                                                        BOM00780
SV2$AREA DS    18F                                                      BOM00790
         LTORG                                                          BOM00800
         END                                                            BOM00810
//GO.SYSIN DD  *                                                        BOM00820
//GO.SYSUDUMP DD SYSOUT=A                                               BOM00830
//                                                                      BOM00840
