#include <stdio.h>
#include "processor.h"
#include "bus.h"
#include "debug.h"

int
process_16bit_instr(unsigned int instruction, unsigned int address)
{

    unsigned int    i_field;

    if (instruction == 0)
	return 0;		/* NOOP */
    else if (instruction == 1) {/* HALT */
	printf("Halting program\n");
	exit(0);
    } 
    else if (instruction == 2) {	/* CALL */
	proc.reg[SP].content = proc.reg[SP].content - 2;
	write_on_bus(proc.reg[PC].content, proc.reg[PC].content >> 8);
	write_to_mem((int) proc.reg[SP].content, 2);
	proc.reg[PC].content = address;
	return 0;
    } else if (instruction == 3) {	/* RETN */
	proc.reg[PC].content = proc.reg[SP].content;
	proc.reg[SP].content = proc.reg[SP].content + 2;
	return 0;
    } else if (instruction == 4) {	/* INTR */
	/* could it be the opposite of IRET */
	return 0;
    } else if (instruction == 5) {	/* TESB */
	if (address == 0) {
	    proc.PSW_Zbit = 1;
	    address = 1;
	    return 0;
	} else if (address == 1) {
	    proc.PSW_Zbit = 0;
	    return 0;
	} else {
	    printf("error, wrong operator in testb\n");
	    return -1;
	}
    } else if (instruction == 7) {	/* IRET */
	proc.reg[PC].content = proc.reg[SP].content;
	proc.reg[SP].content = proc.reg[SP].content + 2;
	/* ((SP)) --> (PSW) */
	proc.reg[SP].content = proc.reg[SP].content + 2;
	return 0;
    } else if (instruction == 48) {	/* CCRY */
	proc.PSW_Cbit = 0;
	return 0;
    } else if (instruction == 49) {
	proc.PSW_Cbit = 1;
	return 0;
    } else if ((instruction > 16) && (instruction < 31)) {	/* INTF */
	i_field = instruction & 0x000F;
	/* CONST --> Interrupt field */
	return 0;
    } else {
	printf("error, unrecognizable 16 bit instruction \n");
	return -1;
    }
}

