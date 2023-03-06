//JOBNAME JOB  (2550130,NDSU),'YOUR NAME',CLASS=A,TIME=(,10),           GEN00010
//   MSGLEVEL=(1,1)                                                     GEN00020
/*ROUTE PRINT NDSUVM1.NU------                                          GEN00030
//*  ASSEMBLY SOURCE GOES IMMEDIATELY AFTER 'ASM.SYSIN DD *'            GEN00040
//*  PROGRAM DATA GOES IMMEDIATELY AFTER 'GO.SYSIN DD *'                GEN00050
//A      EXEC  ASMFCLG                                                  GEN00060
//ASM.SYSIN DD *                                                        GEN00070
         PRINT NOGEN                                                    GEN00080
SUBRNAME START                                                          GEN00090
         STM   14,12,12(13)    STASH AWAY REGISTERS                     GEN00100
         BALR  12,0            ESTABLISH IMPLIED BASE REGISTER          GEN00110
         USING *,12                                                     GEN00120
         ST    13,SAV$AREA+4   LINK SAVE AREAS                          GEN00130
         LA    14,SAV$AREA                                              GEN00140
         ST    14,8(13)                                                 GEN00150
         LR    13,14           POINT GPR 13 AT LOCAL SAVE AREA          GEN00160
*                                                                       GEN00170
         OPEN  (CARDIN,INPUT,LINEOUT,OUTPUT)                            GEN00180
         OPEN  (XDUMP,OUTPUT)                                           GEN00190
         GET   CARDIN,CARD                                              GEN00200
         MVC   LINE+1(80),CARD                                          GEN00210
         PUT   LINEOUT,LINE                                             GEN00220
         SNAP  DCB=XDUMP,STORAGE=(SAV$AREA,SAV$AREA+72),PDATA=REGS      GEN00230
         CLOSE (CARDIN,,LINEOUT,,XDUMP)                                 GEN00240
*                                                                       GEN00250
DONE     EQU   *                                                        GEN00260
         L     13,SAV$AREA+4  RESTORE MAP TO TREASURE                   GEN00270
         L     14,12(13)      RESTORE RETURN ADDRESS                    GEN00280
         L     15,RTN$CODE    SET RETURN CODE                           GEN00290
         LM    0,12,20(13)    RESTORE ALL OTHER REGISTERS               GEN00300
         MVI   12(13),X'FF'   SET FOOTPRINT IN SAVE AREA                GEN00310
         BR    14                                                       GEN00320
*                                                                       GEN00330
CARD     DS    CL80                                                     GEN00340
LINE     DC    CL133' '                                                 GEN00350
RTN$CODE DS    F                                                        GEN00360
SAV$AREA DS    18F                                                      GEN00370
*                                                                       GEN00380
CARDIN   DCB   DSORG=PS,RECFM=F,MACRF=GM,BLKSIZE=80,                   *GEN00390
               LRECL=80,DDNAME=IN,EODAD=DONE                            GEN00400
LINEOUT  DCB   DSORG=PS,RECFM=FBA,MACRF=PM,BLKSIZE=133,                *GEN00410
               LRECL=133,DDNAME=OUT                                     GEN00420
XDUMP    DCB   DSORG=PS,RECFM=VBA,MACRF=(W),                           *GEN00430
               BLKSIZE=882,LRECL=125,DDNAME=DUMP                        GEN00440
         END                                                            GEN00450
//GO.IN DD  *                                                           GEN00460
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHH                                        GEN00470
JJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRR                                    GEN00480
/*                                                                      GEN00490
//GO.OUT DD  SYSOUT=Q                                                   GEN00500
//GO.SYSUDUMP DD SYSOUT=Q                                               GEN00510
//GO.DUMP DD   SYSOUT=Q                                                 GEN00520
//                                                                      GEN00530
