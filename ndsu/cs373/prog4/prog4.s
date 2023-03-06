* 
* Chris Tjon
* CS373
* Program 4
* 20 October 1993
* 
	ORG	$900
SIZE	EQU	5*4		;size of the array * 4 to get longs
ARRAY	DS.L	SIZE		;number of array elements
	ORG  	$1000
MAIN    MOVE.L	#$3000,SP	;initialize the stack pointer
	LINK	A6,#0		;create a copy of the stack pointer
	PEA	CLT		;push the address of the compare function
	MOVE.L	#SIZE,-(SP)	;push the number of elements in the array
	PEA	ARRAY		;push the address of the array
	BSR	SORT		;call sort
	ADDA.L	#12,SP		;fix the stack pointer
	UNLK	A6		;unlink the A6 stack pointer
END	BRA	END		;terminate execution


*
* fix subroutine
*	D0 = return value
*	D1 = original parameter
*	D2 = the exponent
*	D3 = temporary storage
*	D4 = the mantissa
*
FIX	LINK	A6,#0		;link the A6 register
	MOVEM.L	D1-D4,-(SP)	;save the registers on the stack
	CLR.L	D0		;clear D0
	CLR.L	D1		;clear D1
	CLR.L	D2		;clear D2
	CLR.L	D3		;clear D3
	CLR.L	D4		;clear D4
	MOVE.L	8(A6),D1	;get parameter off the stack and place in D1
	MOVE.L	#$80000000,D0	;place mask for sign bit in D0
	AND.L	D1,D0		;AND sign mask with parameter in D1 - sets sign
	MOVE.L	#$7F800000,D2	;place exponent mask in D2
	AND.L	D1,D2		;AND exponent mask with parameter in D1
	LSR.L	#7,D2		;left justify the exponent
	SWAP	D2		;put exponent in lower word of D2
	BNE	NZERO		;check if exponent == 0
	CLR.L	D4		;clear D4
	BRA	DONE		;branch to DONE
NZERO	SUB.B	#$7F,D2		;exponent != 0 
	MOVE.W	#$1F,D3		;place $1F in D3
	SUB.W	D2,D3		;D3 = D3 - D2
	BLE	OVERFLW		;check for overflow
	MOVE.L	#$7FFFFF,D4	;place mantissa mask in D4
	AND.L	D1,D4		;AND mantissa mask with parameter in D1
	BSET.L	#$17,D4		;take care of hidden bit
	LSL.L	#8,D4		;left justify the mantissa
SHIFT	LSR.L	#1,D4		;shift D4 by over by D3 bits
	SUBQ.B	#1,D3		;subtract 1 from D3
	BNE	SHIFT		;if D3 != 0 branch to SHIFT
	BTST.L	#$1F,D0		;check to see if result is negative
	BEQ	DONE		;if result >= 0 then branch to done
	NEG.L	D4		;result < 0 so NEG it
	BRA 	DONE		;branch to DONE
OVERFLW	BTST.L	#$1F,D0		;check sign bit of return value
	BNE	SPEC		;if return value < 0 do the shift
	MOVE.W	#1,CCR		;else we have overflow, set CCR to 1
	MOVE.W	#$FFFF,$908	;set n = -1
DONE	MOVE.L	D4,D0		;place result in D0
	MOVEM.L	(SP)+,D1-D4	;restore previous registers from the stack
	UNLK	A6		;unlink the A6 register
	RTS                     ;return
SPEC	MOVE.L	#$80000000,D4	;place sign bit mask in D4
	MOVEM.L	(SP)+,D1-D4	;restore previous registers from the stack
	UNLK	A6		;unling the A6 register
	RTS			;return


*
* sort routine
*	A1 = address of the array
*	A2 = address of the function to call
*	D1 = number of array elements
*	D2 = index
*	D3 = temp storage 
*
SORT	LINK	A6,#0		;link the A6 register
	MOVEM.L	D1-D4/A1-A2,-(SP)	;save the registers on the stack
	MOVE.L	8(A6),A1	;retreive the address of the array
	MOVE.L	12(A6),D1	;retrieve the number of elements in the array
	MOVE.L	16(A6),A2	;retrieve the address of the function to call
SRTLP   CMP.L	#4,D1		;compare D1 > 1
	BLE	SRT_RTS		;D1 <= 1 so get out of this loop
	PEA	(A2)		;push the effective address of comparelt
	MOVE.L	D1,-(SP)	;push the number of array elements
	PEA	(A1)		;push the effective address of the array
	BSR	SELECT		;call the select subroutine
	ADDA.L	#12,SP		;fix the stacck
	MOVE.L	D0,D2		;copy the return value
	SUBQ.L	#4,D1		;subtract one from the number of elements
	MOVE.L	0(A1,D2),D4	;temp = array[index]
	MOVE.L	0(A1,D1),0(A1,D2)	;array[index] = array[size]
	MOVE.L	D4,0(A1,D1)	;array[size] = temp
	BRA	SRTLP		;continue to loop
SRT_RTS	MOVE.L	0(A1),D0	;return the first element of the array
	MOVEM.L (SP)+,D1-D4/A1-A2	;restore the register prior status
	UNLK	A6		;unlink the A6 register
	RTS			;return


*
* select subroutine
*	D1 = size of the array
*	A1 = address of the array
*	A2 = address of comparelt
*	D2 = sub_index (see flowchart)
*	D3 = x (see flowchart)
*	D4 = temporary storage
*
SELECT	LINK	A6,#0		;link the A6 register
	MOVEM.L	D1-D4/A1-A2,-(SP)	;save current register state on stack
	MOVE.L	8(A6),A1	;retrieve array address from the stack
	MOVE.L	12(A6),D1	;retrieve size of the array from the stack
	MOVE.L	16(A6),A2	;retrieve address of comparelt from the stack
	MOVE.L	#0,D2		;set D2 to 0 - sub_index
	MOVE.L	#4,D3		;set D3 to 4 - x
	SUBQ.L	#4,D1		;subtract one from the size of the array
SELOOP	MOVE.L	0(A1,D2.L),-(SP)	;push the sub_index value
	MOVE.L	0(A1,D3.L),-(SP)	;push the x value
	JSR	0(A2)		;call comparelt
	ADDA.L	#8,SP		;fix the stack
	TST.L	D0		;check result of comparelt
	BEQ	SKIP		;if D0 == 0 branch to SKIP
	MOVE.L	D3,D2		;set sub_index = x
SKIP	ADDQ.L	#4,D3		;increment x
	CMP.L	D1,D3		;compare x (D3) and size of the array (D1)
	BGT	SELRTS		;if x > size of array 
	BRA	SELOOP		;otherwise continue 
SELRTS	MOVE.L	D2,D0		;setup return value
	MOVEM.L (SP)+,D1-D4/A1-A2	;restore the previous registers
	UNLK	A6		;unlink the A6 register
	RTS			;return


*
* comparelt subroutine
*	D1 = first argument
*	D2 = second argument
*
CLT	LINK	A6,#0		;link the A6 register
	MOVEM.L	D1-D2,-(SP)	;save the current register status on the stack
	MOVE.L	8(A6),D1	;retrieve the first argument and place in D1
	MOVE.L	12(A6),D2	;retrieve the second argument and place in D2
	MOVE.L	D1,-(SP)	;push first argument onto the stack
	BSR	FIX		;call fix subroutine
	ADDQ	#4,SP		;fix the stack
	MOVE.L	D0,D1		;place fix return value into D1
	MOVE.L	D2,-(SP)	;push second argument onto the stack
	BSR 	FIX		;call fix subroutine
	ADDQ	#4,SP		;fix the stack
	MOVE.L	D0,D2		;place fix return value into D2
	CMP.L	D2,D1		;compare the integer representations of args
	BMI	NEGLT		;if D1 < D2 then branch to NEGLT
	MOVE.L	#0,D0		;else D1 > D2 so return 0
	BRA	CLTRTS		;branch to CLTRTS
NEGLT	MOVE.L	#1,D0		;D1 < D2 so return 1
CLTRTS	MOVEM.L	(SP)+,D1-D2	;restore the previous register state
	UNLK	A6		;unlink the A6 register
	RTS			;return


	END
