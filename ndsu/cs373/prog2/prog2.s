	ORG $900
RESULT	DS.L	1
INPUT	DS.L	1
	ORG $1000
	MOVE.L #$1000,SP		;set the stack pointer to $1000

MAIN	CLR.L D0			;clear Data Register 0 - result storage
	CLR.L D1			;clear Data Register 1
	CLR.L D2			;clear Data Register 2
	CLR.L D3			;clear Data Register 3
	MOVE.L INPUT,-(SP)		;place n on the stack
	BSR FACT			;call subroutine
	ADDQ.L #4,SP   			;fix stack pointer
	MOVE.L D0,RESULT		;store result in memory
	BRA.S STOP			;terminate

FACT	NOP				;factorial subroutine: y = fact(n)
	MOVE.L 4(SP),D2			;retrieve n from stack to local storage
	CMP.L #0,D2			;check for n = 0
	BEQ RET1			;branch for return of 1
	CMP.L #1,D2			;check for n = 1
	BEQ RET1			;branch for return of 1
	SUB.L #1,D2			;subtract 1 from D2
	MOVE.L D2,-(SP)			;place n-1 on the stack

	BSR FACT			;call fact with n-1 on top of stack

	ADDQ.L #4,SP			;fix the stack pointer
	MOVE.L 4(SP),D1			;retreive n to local storage in D1
	MOVE.L D0,D3			;copy result in D0 to D3:D3->yH|yL
	MULU.W D1,D0			;multiply [n * (yL)]
	SWAP D3				;swap L.O. & H.O. words in D3: D3->yL|yH
	MULU.W D1,D3			;multiply [n * (yH)]
	SWAP D3				;swap L.O. & H.O. W;s in D3: D3->yH|yL
	TST.W D3			;check 4 all 0's in L.O. Word of D3: yL
	BNE OVRFLOW			;check for overflow
	ADD.L D3,D0			;add D3 to D0
	BCS OVRFLOW			;check for carry and thus overflow
	RTS				;return

RET1	MOVE.L #1,D0			;place 1 in D0
	RTS				;return

OVRFLOW	MOVE.L #-1,RESULT		;overflow condition - return -1 ($ffff)

STOP	BRA.S STOP			;stop execution
	END
