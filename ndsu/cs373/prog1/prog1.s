	ORG $1000
	MOVE.W #$900,A1
	CLR.L D2
	MOVE.B $901,D2
	MOVE.W #$902,A0
	CLR.L D1
CHK	MOVE.B (A0),D0
	BLE.S SKIP
	ADDQ.W #1,D1
SKIP	ADDQ.L #1,A0
	SUBQ.B #1,D2
	BNE.S CHK
	MOVE.B D1,(A1)
STOP	BRA.S STOP
	END
