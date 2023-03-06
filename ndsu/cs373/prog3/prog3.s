	ORG	$900
INT	DS.L	1		;integer data storage area $900-$903
FP	DS.L	1		;float Data storage area $904-$907
OPTN	DS.W	1		;option N to determine what to do $908-$909
HBM	EQU	$FF800000	;define high bit mask
LBM	EQU	$007FFFFF	;define low bit mask

	ORG	$1000
MAIN	MOVE.L	#$4000,SP	;initialize the stack pointer
OPT1	CMP	#1,OPTN		;check to see if option == 1
	BNE	OPT2		;if option != 1 branch to OPT2
	BSR	N1		;if option == 1 call N1 subroutine
	BRA	END		;branch to end
OPT2	CMP 	#2,OPTN		;check to see if option == 2
	BNE	OPT3		;if option != 2 branch to OPT3
	BSR	N2		;if option == 2 call N2 subroutine
	BRA	END		;branch to end
OPT3	CMP 	#3,OPTN		;check to see if option == 3
	BNE	OPT4		;if option != 3 branch to OPT4
	BSR	N3		;if option == 3 call N3 subroutine
	BRA	END		;branch to end
OPT4	CMP	#4,OPTN		;check to see if option == 4
	BNE	NOTV		;if option != 4 branch to NOTV
	BSR	N4		;if option == 4 call N4 subroutine
	BRA 	END		;branch to end
NOTV	MOVE.W	#0,OPTN		;option is not valid, place 0 in OPTN field
END	BRA	END		;LOOP forever (STOP)

N1	NOP			;subroutine to setup N = 1
	MOVE.L	INT,-(SP)	;place integer argument on the stack
	BSR	FLOAT		;call the float function
	ADDQ.L	#4,SP		;fix the stack
	MOVE.L	D0,FP		;place floating point result in FP
	RTS			;return

N2	NOP			;subroutine to setup N = 2
	MOVE.L	FP,-(SP)	;place float argument on the stack
	BSR	FIX		;call the fix function
	ADDQ.L	#4,SP		;fix the stack
	BVC	OK		;if carry bit != 1 then branch to OK
	MOVE.W	-1,OPTN		;OVERFLOW -  put a -1 into OPTN	
OK	MOVE.L	D0,INT		;place integer result in INT
	RTS			;return

N3	NOP			;subroutine to setup N = 3
	BSR	N1		;call the N1 subroutine
	BSR	N2		;call the N2 subroutine
	RTS			;return

N4	NOP			;subroutine to setup N = 4
	BSR	N2		;call the N2 subroutine
	BSR	N1		;call the N1 subroutine
	RTS			;return

FLOAT   NOP			;function to convert binary int to IEEE fp
	CLR.L	D0		;clear D0 - stores return value
	CLR.L	D1		;clear D1 - stores integer to convert
	CLR.L	D2		;clear D2 - stores exponent
	CLR.L	D3		;clear D3 - temporary storage
	MOVE.L	4(SP),D1	;retrieve parameter and place in D1
	CMP	#0,D1		;compare D1 and 0
	BGT	LOOP		;if integer > 0 then branch to LOOP
	BEQ	FZERO		;if integer == 0 branch to FZERO
	NEG.L	D1		;negate D1 with 2's compliment
	BSET	#31,D0		;set the sign of the result to be negative
LOOP	ADDQ.L	#1,D2		;D2++
	LSL.L	#1,D1		;shift left one bit
	BCC	LOOP		;if carry clear(no carry) then branch to LOOP
	LSR.L	#8,D1		;shift D1 right 8 bits
	LSR.L 	#1,D1		;shift D1 right 1 more bit
	MOVE.L	#159,D3		;place 159 into D3
	SUB.L	D2,D3		;exponent = D3 - D2 - result in D3
	MOVE.L	D3,D2		;copy exponent to D2
	MOVE.L	#23,D3		;place 23 in D3 - number of bits to LSL
	LSL.L	D3,D2		;shift left 23 bits
	AND.L	#HBM,D2		;mask out all except the exponent
	OR.L	D2,D0		;place exponent in D0
	AND.L	#LBM,D1		;mask out all except the mantissa
	OR.L	D1,D0		;place mantissa in D1
	CLR.L	D3		;clear D3 - temporary storage
	BRA	FRTS		;branch to floats rts statement
FZERO	MOVE.L	#0,D0		;place 0 in D0
FRTS	RTS

FIX	NOP			;function to convert IEEE fp to binary int
	LINK	A6,#0
	MOVEM.L	D1-D4,-(SP)	
	CLR.L	D0
	CLR.L	D1
	CLR.L	D2
	CLR.L	D3
	CLR.L	D4
	MOVE.L	8(A6),D1
	MOVE.L	#$80000000,D0
	AND.L	D1,D0	
	MOVE.L	#$7F800000,D2	
	AND.L	D1,D2		

	LSR.L	#7,D2		
	SWAP	D2		
	BNE	NZERO		
	CLR.L	D4
	BRA	DONE

NZERO	SUB.B	#$7F,D2
	MOVE.W	#$1F,D3
	SUB.W	D2,D3
	BLE	OVERFLW		

	MOVE.L	#$7FFFFF,D4	
	AND.L	D1,D4		
	BSET.L	#$17,D4		
	LSL.L	#8,D4		

SHIFT	LSR.L	#1,D4		
	SUBQ.B	#1,D3
	BNE	SHIFT
	BTST.L	#$1F,D0		
	BEQ	DONE		
	NEG.L	D4		
	BRA 	DONE		
OVERFLW	BTST.L	#$1F,D0		
	BNE	SPEC		
	MOVE.W	#1,CCR		
	MOVE.W	#$FFFF,$908
DONE	MOVE.L	D4,D0
	MOVEM.L	(SP)+,D1-D4
	UNLK	A6
	RTS
SPEC	MOVE.L	#$80000000,D4
	MOVEM.L	(SP)+,D1-D4
	UNLK	A6
	RTS
	END
