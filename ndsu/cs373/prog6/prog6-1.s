*
* Chris Tjon
* CS373
* PROGRAM #5
*
	ORG	$B8		SET THE VECTOR FOR TRAP 14
	DC.L	TR14INT		
	ORG	$200
TIVR	DC.L	TIRQ
SFLAG	DS.B	1
FLAG	DS.B	1
TR14LOC EQU	$BEB8		LOCATION OF TRAP #14 HANDLER
	ORG 	$1000
STARTS  LEA     ENDS,SP         ; START OF SUPERVISOR MEMORY SPACE
        MOVE.W  #$2700,SR       ; m68ks does NOT default to this! (SR C 2700)
	RESET			ALWAYS DO THIS TO INSURE CLEAN 68230
	LEA	$10000,A5	PUT BASE ADDRESS OF 68230 IN A5
	MOVE.L	#50000,D0	PUT COUNT FOR 0.4 SECOND DELAY IN D0
	MOVEP.L	D0,$25(A5)	PUT DELAY IN COUNTER PRELOAD REG
	MOVE.B	#TIVR/4,$23(A5)	LOAD TIVR WITH VEC #
	MOVE.B	#$A1,$21(A5)	SET TCR - START THE TIMER ENABLE - INT
        CLR.B   D0
RUN     LEA     PROC1,A0        ; LOAD PTR TO USER PROCESS 1 IMAGE
        BSR     GOUSER
        LEA     PROC2,A0        ; LOAD PTR TO USER PROCESS 2 IMAGE
        BSR     GOUSER
        ADDQ.B  #1,D0
        CMPI.B  #5,D0
        BLT.S   RUN
DONE	MOVE.B	#0,$21(A5)	DISABLE TIMER
	MOVE	#$2700,SR
        MOVE.B  #228,D7         ; PUT RESTART OP-CODE FOR TUTOR IN D7
        TRAP    #14             ; GO TO TUTOR (causes m68ks error halt)
*
*	THE FOLLOWING IS THE TIMER SERVICE CODE
TIRQ	MOVE.B	#1,$10035	CLEAR ZERO DETECT BIT (SERVICE INT)
	JMP	GOSUPER
FLAGSET	TAS	SFLAG
	RTE
*
TR14INT	ORI	#$700,SR	TURN OFF INTERUTPS
	JMP	TR14LOC
*	
*
*
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
*               BEGIN SUPERVISOR STACK STORAGE AREA FOR PROCESS 1
STATUS  EQU     $0100           ; USER MODE - NO INTERRUPTS
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

* PROCESS 1 (USER SPACE) BEGINS AT $2000
STRING1	DC.B	' PROCESS #1 CALLS',$D,$A,0
START1  CLR.L	D1	;clear D1
LOOP1	ADDQ.L	#1,D1	;increment the counter
	MOVE.L	D1,-(SP)	;push the counter onto the stack
	PEA	STRING1	;push the effective address of the string onto the stack
	BSR	PRINT	;call the print routine
	ADDQ.L	#8,SP	;fix the stack
	BRA	LOOP1	;branch to LOOP1
        ORG     $3000
END1    DS.L    0
* PROCESS 2 (USER SPACE) BEGINS AT $3000
STRING2	DC.B	' PROCESS #2 CALLS',$D,$A,0
START2  CLR.L	D1	;clear D1
LOOP2	ADDQ.L	#1,D1	;increment the counter
	MOVE.L	D1,-(SP)	;push the counter onto the stack
	PEA	STRING2	;push the effective address of the string onto the stack
	BSR	PRINT	;call the print routine
	ADDQ.L	#8,SP	;fix the stack
	BRA	LOOP2	;branch to loop2
        ORG     $4000
END2    DS.L    0
*
* PRINT ROUTINE
*
PRINT	DS.L	0	;*
	LINK	A0,#-80	;*define space for the string
	MOVEM.L	D0-D7/A1-A6,-(SP)	;*save current registers status on stack
	MOVE.L	A0,A6	;*setup the pointer for the return value
	SUBA.L	#80,A6	;*get to start of the space reserved for the string
	MOVE.L	12(A0),D0	;*place value to convert in D0
	MOVE.B	#236,D7	;*setup value for tutor to call HEX2DEC
	TRAP #14	;*call HEX2DEC
	MOVE.L	8(A0),A1	;*store the address of the string in A1
PLOOP	MOVE.B	(A1)+,(A6)+	;*copy 1 byte pointed to by A1 to A6
	CMP.B	#0,(A1)	;*check for 
	BNE	PLOOP	;*branch to PLOOP until done
	SUB.L	#1,A6	;*fix the A6 register since it is off by one
	MOVE.L	A0,A5	;*get stack frame pointer
	SUBA.L	#80,A5	;*find the beginning of the string
	MOVE.B	#243,D7	;*setup value for tutor to call PRINT routine
	TRAP	#14	;*call print routine
	MOVEM.L	(SP)+,D0-D7/A1-A6	;restore previous register configuration
	UNLK	A0	;*unlink the A0 register
	RTS		;*return
*
	END
