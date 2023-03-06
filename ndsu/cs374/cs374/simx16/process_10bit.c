#include 	<stdio.h>
#include 	"processor.h"
#include 	"bus.h"
#include 	"memory.h"

typedef struct BIT {
    unsigned int    bit:1;
} bit ;

unsigned int    temp_instr, mode, regstr, address, opr;
unsigned int    byte0, byte1, temp, temp2;
bit	tmp ;

int do_shift_rotate( unsigned int opr ) {
 
    switch (opr) { 
    case 112:			/* SLLB */
		proc.PSW_Cbit = ((opr & 0x0080) >> 7);
		opr = (opr << 1);
		opr = opr + temp2;
		return opr;

    case 48:			/* SLLH */
		proc.PSW_Cbit = ((opr & 0x8000) >> 15);
		opr = (opr << 1);
		proc.PSW_Vbit = 0;
		return opr;

    case 114:			/* SALB */
		proc.PSW_Cbit = ((opr & 0x0080) >> 7);
		opr = (opr << 1);
		proc.PSW_Vbit = 0;
		return opr;
    case 50:			/* SALH */
		proc.PSW_Cbit = ((opr & 0x8000) >> 15);
		opr = (opr << 1);
		proc.PSW_Vbit = 0;
		return opr;
    case 113:			/* SLRB */

		proc.PSW_Cbit = opr;
		opr = (opr >> 1);
		proc.PSW_Vbit = 0;
		return opr;

    case 49:			/* SLRH */
		proc.PSW_Cbit = opr;
		opr = (opr >> 1);
		proc.PSW_Vbit = 0;
		return opr;
    case 115:			/* SARB */
		proc.PSW_Cbit = opr;
		tmp.bit = (opr >> 7);
		temp2 = (tmp.bit << 7);
		opr = (opr >> 1);
		opr = (opr + temp2);
		proc.PSW_Zbit = 0;
		return opr;
    case 51:			/* SARH */
		proc.PSW_Cbit = opr;
		tmp.bit = (opr >> 15);
		temp2 = (tmp.bit << 15);
		opr = (opr >> 1);
		opr = (opr + temp2);
		proc.PSW_Vbit = 0;
		return opr;
    case 120:			/* ROLB */
		proc.PSW_Cbit = ((opr & 0x0080) >> 7);
		opr = (opr << 1);
		opr = (opr + proc.PSW_Cbit);
		proc.PSW_Vbit = 0;
		return opr;
    case 56:			/* ROLH */
		proc.PSW_Cbit = ((opr & 0x8000) >> 15);
		opr = (opr << 1);
		opr = (opr + proc.PSW_Cbit);
		proc.PSW_Vbit = 0;
		return opr;
    case 121:			/* RORB */
		proc.PSW_Cbit = opr;
		tmp.bit = (opr >> 7);
		temp2 = (tmp.bit << 7);
		opr = (opr >> 1);
		opr = (opr + temp2);
		proc.PSW_Zbit = 0;
		return opr;


    case 57:			/* RORH */
		proc.PSW_Cbit = (opr >> 15);
		tmp.bit = (opr >> 15);
		temp2 = (tmp.bit << 7);
		opr = (opr >> 1);
		opr = (opr + temp2);
		proc.PSW_Vbit = 0;
		return opr;
    case 122:			/* RCLB */
		proc.PSW_Cbit = ((opr & 0x0080) >> 7);
		opr = (opr << 1);
		opr = (opr + proc.PSW_Cbit);
		proc.PSW_Vbit = 0;
		return opr;
    case 58:			/* RCLH */
		proc.PSW_Cbit = ((opr & 0x8000) >> 15);
		opr = (opr << 1);
		opr = (opr + proc.PSW_Cbit);
		proc.PSW_Vbit = 0;
		return opr;
    case 123:			/* RCRB */
		proc.PSW_Cbit = (opr >> 7);
		tmp.bit = (opr >> 7);
		temp2 = ( tmp.bit << 7); 
		opr = (opr >> 1);
		opr = (opr + temp2);
		proc.PSW_Vbit = 0;
		return opr;
    case 59:			/* RCRH */
		proc.PSW_Cbit = (opr << 15);
		tmp.bit = (opr >> 15);
		temp2 = (tmp.bit >> 15);
		opr = (opr >> 1);
		opr = (opr + temp2);
		proc.PSW_Vbit = 0;
		return opr;
    }
}
int do_branch_instr(unsigned int address) {

    switch (address) {
    case 28: if (proc.PSW_Zbit == 1) {				/* BREQ */
	        proc.reg[PC].content = address ; 
	        break; }
    case 20: if (proc.PSW_Zbit == 0) {				/* BRNE */
	 	proc.reg[PC].content = address ; 
		break; }
    case 21: if ((proc.PSW_Cbit | proc.PSW_Zbit) == 0) {	/* BUGT */
		proc.reg[PC].content = address ; 
		break; }
    case 29: if ((proc.PSW_Cbit | proc.PSW_Zbit) == 1) {	/* BULE */
		proc.reg[PC].content = address ; 
		break; }
    case 25: if (proc.PSW_Cbit == 1) {				/* BULT */
		proc.reg[PC].content = address ; 
		break; }
    case 17: if (proc.PSW_Cbit == 0) {				/* BUGE */
		proc.reg[PC].content = address ; 
		break; }
    case 22: if (((proc.PSW_Nbit ^ proc.PSW_Vbit) | proc.PSW_Zbit) == 0) {
		proc.reg[PC].content = address ; 		/* BSGT */
		break; }
    case 30: if (((proc.PSW_Nbit ^ proc.PSW_Vbit) | proc.PSW_Zbit) == 1) {
		proc.reg[PC].content = address ; 		/* BSLE */
		break; }
    case 27: if ((proc.PSW_Nbit ^ proc.PSW_Vbit) == 1) {	/* BSLT */
		proc.reg[PC].content = address ; 
		break; }
    case 19: if ((proc.PSW_Nbit ^ proc.PSW_Vbit) == 0) {	/* BSGE */
		proc.reg[PC].content = address ;
		break; }
    case 26: if (proc.PSW_Nbit == 1) {		 		/* BRNG */
		proc.reg[PC].content = address ; 
		break; }
    case 18: if (proc.PSW_Nbit == 0) {				/* BRNN */
		proc.reg[PC].content = address ; 
		break; }
    case 24: if (proc.PSW_Vbit == 1) {	 			/* BROV */
		proc.reg[PC].content = address ;
		break; }
    case 16: if (proc.PSW_Vbit == 0) {				/* BRNV */
		proc.reg[PC].content = address ; 
		break; }
    case 31: proc.reg[PC].content = address ; 			/* BRUN */
		break;
    default: printf("error woring opcode\n") ;
	     return -1 ;
    }
    return 0 ;
}

unsigned int
get_address()
{

    unsigned int    temp_instr, mode, regstr, address, operator;
    unsigned int    byte0, byte1, temp;

    if (temp_instr == 58) {	/* Immidiate */
	read_from_mem((int) proc.reg[PC].content, 2);
	read_from_bus(&byte0, &byte1);
	proc.reg[PC].content = proc.reg[PC].content + 2;
	temp = byte1 << 8;
	address = temp + byte0;
	if (do_branch_instr(address) == 0)
	    return 0;
	else
	    return -1;
    } else if (mode == 1) {	/* Reg Indirect */
	read_from_mem((int) proc.reg[(int) regstr].content, 2);
	read_from_bus(&byte0, &byte1);
	temp = byte1 << 8;
	address = temp + byte0;
	if (do_branch_instr(address) == 0)
	    return 0;
	else
	    return -1;

    } else if (mode == 6) {	/* Relative */
	if (regstr == 7) {
	    printf("error, PC relative addressing only\n");
	    return -1;
	}
	read_from_mem((int) proc.reg[PC].content, 2);
	read_from_bus(&byte0, &byte1);
	address = proc.reg[PC].content;
	proc.reg[PC].content = proc.reg[PC].content + 2;
	temp = byte1 << 8;
	address = address + (temp + byte0);
	if (do_branch_instr(address) == 0) {
	    return 0;
	} else {
	    return -1;
	}
    } else {
	printf("error, wrong addressing mode\n");
	return -1;
    }
}
unsigned int
get_operator()
{

    unsigned int    temp_instr, mode, regstr, address, operator;
    unsigned int    byte0, byte1, temp;

    if (temp_instr == 58) {	/* Immidiate */
	printf("error, cannot have immidiate addressing\n");
	return -1;
    } else if ((temp_instr == 59) || (temp_instr == 3)) {	/* Direct */
	read_from_mem((int) proc.reg[PC].content, 2);
	read_from_bus(&byte0, &byte1);
	proc.reg[PC].content = proc.reg[PC].content + 2;
	temp = byte1 << 8;
	operator = temp + byte0;
	if (operator = do_shift_rotate(operator) == 0) {
	    byte1 = (operator & 0xff00) >> 8;
	    byte0 = (operator & 0x00ff);
	    write_on_bus(byte0, byte1);
	    write_to_mem(proc.reg[PC].content - 2, 2);
	    return 0;
	} else
	    return -1;
    } else if (mode == 0) {	/* Register */
	operator = proc.reg[regstr].content;
	if (operator = do_shift_rotate(operator) == 0) {
	    proc.reg[regstr].content = operator;
	    return 0;
	} else
	    return -1;
    } else if (mode == 1) {	/* Reg Indirect */
	read_from_mem((int) proc.reg[(int) regstr].content, 2);
	read_from_bus(&byte0, &byte1);
	temp = byte1 << 8;
	operator = temp + byte0;
	if (operator = do_shift_rotate(operator) == 0) {
	    byte1 = (operator & 0xff00) >> 8;
	    byte0 = (operator & 0x00ff);
	    write_on_bus(byte0, byte1);
	    write_to_mem((int) proc.reg[(int) regstr].content, 2);
	    return 0;
	} else
	    return -1;
    } else if (mode == 5) {	/* Reg Ind AuInc */
	read_from_mem((int) proc.reg[(int) regstr].content, 2);
	read_from_bus(&byte0, &byte1);
	temp = byte1 << 8;
	operator = temp + byte0;
	proc.reg[(int) regstr].content =
	    proc.reg[(int) regstr].content + 2;
	if (operator = do_shift_rotate(operator) == 0) {
	    byte1 = (operator & 0xff00) >> 8;
	    byte0 = (operator & 0x00ff);
	    write_on_bus(byte0, byte1);
	    write_to_mem((int) proc.reg[(int) regstr].content - 2, 2);
	    return 0;
	} else {
	    return -1;
	}
    } else if (mode == 7) {	/* Reg Ind AuDec */
	proc.reg[(int) regstr].content =
	    proc.reg[(int) regstr].content - 2;
	read_from_mem((int) proc.reg[(int) regstr].content, 2);
	read_from_bus(&byte0, &byte1);
	temp = byte1 << 8;
	operator = temp + byte0;
	if (operator = do_shift_rotate(operator) == 0) {
	    byte1 = (operator & 0xff00) >> 8;
	    byte0 = (operator & 0x00ff);
	    write_on_bus(byte0, byte1);
	    write_to_mem((int) proc.reg[(int) regstr].content, 2);
	    return 0;
	} else
	    return -1;
    } else if (mode == 6) {	/* Relative */
	read_from_mem((int) proc.reg[PC].content, 2);
	read_from_bus(&byte0, &byte1);
	proc.reg[PC].content = proc.reg[PC].content + 2;
	temp = byte1 << 8;
	operator = temp + byte0;
	address = proc.reg[(int) regstr].content + operator;
	read_from_mem(address, 2);
	read_from_bus(&byte0, &byte1);
	temp = byte1 << 8;
	operator = (temp + byte0);
	if (operator = do_shift_rotate(operator) == 0) {
	    byte1 = (operator & 0xff00) >> 8;
	    byte0 = (operator & 0x00ff);
	    write_on_bus(byte0, byte1);
	    write_to_mem(address, 2);
	    return 0;
	} else {
	    return -1;
	}
    } else {
	printf("error, wrong addressing mode\n");
	return -1;
    }
}

int
process_10bit_instr(unsigned int instruction)
{

    temp_instr = instruction & 0x003f;
    mode = temp_instr & 0x0003;
    regstr = temp_instr & 0x0038;

    if (instruction <= 31) {
	if (get_address() == 0)
	    return 0;
	else
	    return -1;
    } else {
	if (get_operator() == 0)
	    return 0;
	else
	    return -1;
    }
}
