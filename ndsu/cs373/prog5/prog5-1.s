*
* Chris Tjon
* CS373
* Program 5 - Part 1
*
* SCHEDULER TEST PROGRAM USING TRAP #0 SYS CALL!
	ORG	$0080		;*
	DC.L	GOSUPER		;*define the address of the GOSUPER procedure
        ORG     $1000
STARTS  LEA     ENDS,SP         ; START OF SUPERVISOR MEMORY SPACE
*	MOVE.W  #$2700,SR       ; m68ks does NOT default to this!
        CLR.B   D0              ; use the "SR C 2700" command. 
RUN     LEA     PROC1,A0        ; LOAD PTR TO USER PROCESS 1 IMAGE
        BSR     GOUSER
        LEA     PROC2,A0        ; LOAD PTR TO USER PROCESS 2 IMAGE
        BSR     GOUSER
        ADDQ.B  #1,D0
        CMPI.B  #5,D0
        BLT.S   RUN
STOP	BRA	STOP
	MOVE.B  #228,D7         ; PUT RESTART OP-CODE FOR TUTOR IN D7
	TRAP    #14             ; GO TO TUTOR (causes m68ks to halt)
*               THE FOLLOWING ARE THE SCHEDULER ROUTINES
*               GOSUPER - SAVES USER PROC IMAGE AND LOADS UP SCHED
GOSUPER MOVEM.L D0-D7/A0-A6,-(SP)  ; SAVE USER REGISTERS
        MOVE    USP,A0             ; GET USER SP IN A0
        MOVE.L A0,-(SP)            ; SAVE IT
        MOVEA.L SCHSP,SP           ; PICK UP SCHEDULER SP
        MOVEM.L (SP)+,D0-D7/A0-A6  ; GET SCHEDULER REGISTERS
        RTS
*               GOUSER - SAVES SCHED PROC IMAGE AND LOADS USER PROC
GOUSER  MOVEM.L D0-D7/A0-A6,-(SP)
        MOVE.L  SP,SCHSP
        MOVE.L  A0,SP           ; A0 MUST POINT TO USER PROC IMAGE
        MOVE.L  (SP)+,A0
        MOVE.L  A0,USP
        MOVEM.L (SP)+,D0-D7/A0-A6
        RTE
SCHSP   DS.L    1
*         BEGIN SUPERVISOR STACK STORAGE AREA FOR PROCESS 1
STATUS  EQU     $0700           ; USER MODE - NO INTERRUPTS
STAK1   DS.L    $100            ; THIS AREA FOR INSURANCE
PROC1   DS.L    0
P1SP    DC.L    END1
P1D0    DC.L    $1DDD0000
P1D1    DC.L    $1DDD1111
P1D2    DC.L    $1DDD2222
P1D3    DC.L    $1DDD3333
P1D4    DC.L    $1DDD4444
P1D5    DC.L    $1DDD5555
P1D6    DC.L    $1DDD6666
P1D7    DC.L    $1DDD7777
P1A0    DC.L    $1AAA0000
P1A1    DC.L    $1AAA1111
P1A2    DC.L    $1AAA2222
P1A3    DC.L    $1AAA3333
P1A4    DC.L    $1AAA4444
P1A5    DC.L    $1AAA5555
P1A6    DC.L    $1AAA6666
P1SR    DC.W    STATUS
P1PC    DC.L    START1
* BEGIN SUPERVISOR STACK STORAGE AREA FOR PROCESS 2
STAK2   DS.L    $100
PROC2   DS.L    0
P2SP    DC.L    END2
P2D0    DC.L    $2DDD0000
P2D1    DC.L    $2DDD1111
P2D2    DC.L    $2DDD2222
P2D3    DC.L    $2DDD3333
P2D4    DC.L    $2DDD4444
P2D5    DC.L    $2DDD5555
P2D6    DC.L    $2DDD6666
P2D7    DC.L    $2DDD7777
P2A0    DC.L    $2AAA0000
P2A1    DC.L    $2AAA1111
P2A2    DC.L    $2AAA2222
P2A3    DC.L    $2AAA3333
P2A4    DC.L    $2AAA4444
P2A5    DC.L    $2AAA5555
P2A6    DC.L    $2AAA6666
P2SR    DC.W    STATUS
P2PC    DC.L    START2
        ORG     $2000
ENDS    DS.L    0
*
* PROCESS 1 (USER SPACE) BEGINS AT $2000 AND ENDS AT $3000
*
STRING1	DC.B	'Calls to process 1 ->',$D,$A,0	;*define STRING1
START1  DS.L    0       ; CODE FOR USER PROC 1 GOES HERE
	TRAP	#0	;*return control to the scheduler
	BRA	START1
        ORG     $3000
END1    DS.L    0
*
* PROCESS 2 (USER SPACE) BEGINS AT $3000 AND ENDS AT $4000
*
STRING2	DC.B	'Calls to process 2 ->',$D,$A,0	;*define STRING2
START2  DS.L    0       ; CODE FOR USER PROC 2 GOES HERE
	TRAP	#0	;*return control to the scheduler
	BRA	START2
        ORG     $4000
END2    DS.L    0
	END
