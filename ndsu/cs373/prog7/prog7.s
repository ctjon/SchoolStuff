*
* Chris Tjon
* CS373
* Program 7
*
* THIS IS 68000 ASSEMBLY FOR RUNNING A STEPPER MOTOR FROM THE PRINTER PORT
* OF THE ECB.  WRITTEN BY R. GAMMILL ON MAY 9, 1989.
* THIS IS AN EXAMPLE PROVIDED TO GIVE YOU THE INITIALIZATION AND CLEAN-UP.
* DO NOT ELIMINATE OR CHANGE ANY OF THE CODE THAT SETS UP THE 68230 EXCEPT
* YOU MUST PUT THE CORRECT VALUES INTO THE TIRV AND PIRV REGISTERS.

* Begin Changed Area *******************************************************
        ORG     $200
TIVR    DC.L    TIRQ
        ORG     $210
PIVR    DC.L    PIRQ
* End Changed Area *********************************************************
        ORG     $900            ; ALL DATA FOR CONTROL MUST START AT $900
DELAY   DC.L    250             ; 2 MS. DELAY  (DELAY OF 1 IS 8 MICROSECONDS)
COUNT   DC.L    5000            ; NUMBER OF HALF STEPS FOR RUN
HYSTER  DC.L    2               ; HYSTERESIS VALUE
TAB     DC.B   1,3,2,6,4,12,8,9 ; TABLE OF COIL VALUES FOR HALF STEPS
*                               ; TURNS ON COIL 1, 1 AND 2, 2, 2 AND 4, ...
* Begin Changed Area *******************************************************
CURRENT DC.B	' = CURRENT COIL SUMMATION',$A,$D,$0
IDLECNT DC.B    ' = IDLE COUNT',$A,$D,$0
MOTOR   DC.B    ' = NUMBER OF MOTOR REVERSALS',$A,$D,$0
H1IGNOR DC.B    ' = NUMBER OF H1 INTERUPTS INGNORED',$A,$D,$0
FLAG    DC.B    1
* End Changed Area *********************************************************
        ORG     $1000
START   LEA     IDLECNT,SP	; CODE MUST BEGIN AT $1000 - used to be DELAY
        LEA     $10000,A5       ; GET OFFSET FOR 68230 IN A5
        MOVE.L  DELAY,D0        ; PUT DELAY IN COUNTER PRELOAD REGISTER
        MOVEP.L D0,$25(A5)      ; NOTICE!!!  MOVEP INSTRUCTION!  READ UP!!!!
        MOVE.B  #TIVR/4,$23(A5) ; LOAD TIVR WITH INT VEC NUMBER (FILL IN ????)
        MOVE.B  #PIVR/4,$B(A5)  ; LOAD PIVR WITH INT VEC NUMBER (FILL IN ????)
        MOVE.B  #0,$1(A5)       ; LOAD PGCR WITH ZERO TO DISABLE STUFF
        MOVE.B  #$18,$3(A5)     ; LOAD PSRR (READ ECB MANUAL FOR MEANING)
        MOVE.B  #$FB,$D(A5)     ; LOAD PACR
        MOVE.B  #$30,$1(A5)     ; LOAD PGCR WITH ENABLE FOR H12 AND H34
        MOVE.B  #$A1,$21(A5)    ; SET TCR - START THE TIMER - ENABLE INT
        MOVE    #$2100,SR       ; ALLOW INT LEVELS 2 AND 3

*       ; YOUR CODE GOES IN HERE (BE SURE TO SERVICE THE INTERRUPTS!)
* Begin Changed Area *******************************************************
        MOVE.B  #$FF,$10005
        MOVE.L  #TAB,A2
        CLR.L   D1              ;idle loop count 
        CLR.L   D2              ;ignored H1 interrupt count
        CLR.L   D3              ;motor reversal count
        MOVE.L  #1,D4           ;motor direction register
        MOVE.L  COUNT,D5
        MOVE.L  COUNT,D6
        MOVE.L  #0,D7
TLOOP	ADDQ.L  #1,D1
        TAS.B   FLAG
        BNE     TLOOP
* End Changed Area *********************************************************

DONE    MOVE.B  #0,$11(A5)      ; TURN OFF MOTOR COILS!!!!!!!
        MOVE    #$2700,SR       ; DISALLOW INTS
        MOVE.B  #0,$21(A5)      ; DISABLE TIMER

*       ; THREE CALLS TO PRINT GO HERE

* Begin Changed Area *******************************************************
* PRINT THE IDLE COUNT
        MOVE.L  D1,-(SP)
        PEA     IDLECNT
        BSR     PRINT
        ADDQ.L  #8,SP
* PRINT THE NUMBER OF MOTOR REVERSALS
        MOVE.L  D2,-(SP)
        PEA     MOTOR
        BSR     PRINT
        ADDQ.L  #8,SP
* PRINT THE NUMBER OF H1 INTERUPTS IGNORED
        MOVE.L  D3,-(SP)
        PEA     H1IGNOR
        BSR     PRINT
        ADDQ.L  #8,SP
* End Changed Area *********************************************************

        MOVE.B  #228,D7
        TRAP    #14

*
* PRINT ROUTINE
*
PRINT	LINK    A0,#-80                 ;define space for the string
        MOVEM.L D0-D7/A1-A6,-(SP)       ;save the current register status
        MOVE.L  A0,A6                   ;setup pointer for return
        SUBA.L  #80,A6                  ;get to start of reserved space
        MOVE.L  12(A0),D0               ;place value to convert in D0
        MOVE.B  #236,D7                 ;setup TUTOR to call HEX2DEC
        TRAP    #14                     ;call HEX2DEC
        MOVE.L  8(A0),A1                ;place the address of STRING in A1
WHILE   MOVE.B  (A1)+,(A6)+     	;byte copy from (A1) to (A6)
        BNE     WHILE
        SUB.L   #1,A6           	;fix count made off 1 in while
        MOVE.L  A0,A5           	;get stack frame pointer
        SUBA.L  #80,A5          	;find the beginning of STRING
	MOVE.B  #243,D7         	;setup tutor to call PRINT routine
        TRAP    #14             	;call PRINT
        MOVEM.L (SP)+,D0-D7/A1-A6       ;restore saved register configuration
        UNLK    A0                      ;unlink A0
        RTS                             ;return
*
TIRQ	SUB.L   #1,D5			;subtract the number to go
        BNE     CONT			;if D5 > 0 the branch to CONT
        CLR.L   FLAG			;clear FLAG
        JMP     FINISH			;Jump to FINISH
CONT	CMP.B   #1,D4
        BNE     REVERS
        ADD.L   #1,D7
        JMP     OVER
REVERS	ADD.L   #-1,D7
OVER	AND.L   #7,D7
        MOVE.B  0(A2,D7),$11(A5)
*
        MOVE.L  0(A2,D7),-(SP)
        PEA     CURRENT
        BSR     PRINT
        ADDQ.L  #8,SP
*
FINISH	MOVE.B  #1,$35(A5)		;service the interrupt
        RTE
*
PIRQ	CMP.L   D6,D5
        BLE     PIRQL1
        ADD.L   #1,D3
        JMP     PIRQDUN
PIRQL1	NOT.B   D4
        ADD.L   #1,D2
        MOVE.L  D5,D6
        SUB.L   HYSTER,D6
PIRQDUN	MOVE.B  #1,$1B(A5)
        RTE
*
	END
