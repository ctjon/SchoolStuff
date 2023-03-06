/* PROCESSOR.C */

#include <stdio.h>
#include <errno.h>

#include "processor.h"
#include "debug.h"
#include "bus.h"

static int Halt = FALSE;

/*----------------------------------------------------------------------------+
 |                                                                            |
 | GENERAL ALGORITHM OF PROCESSOR LOOP                                        |
 |                                                                            |
 | while (!done)                                                              |
 | {                                                                          |
 |     fetch instruction pointed to by PC into IR                             |
 |     increment the PC to point to next instruction                          |
 |     decode instruction and parameters                                      |
 |     call appropriate opcode service routine call                           |
 | }                                                                          |
 +---------------------------------------------------------------------------*/

void processor(void)
{

    int Halt = FALSE;
    unsigned int LO_byte;
    unsigned int HO_byte;
    unsigned int carry;

    debug("processor - processing initiated with PC = [%04x]\n", proc.reg[PC].content);
    while (!Halt)
    {
	/* tell memory to place next instruction on the bus */
	if ((read_from_mem(proc.reg[PC].content, 2)) != 0)
	{
	    printf("processor - read_from_mem error - fatal\n");
	    exit(1);
	}
	/* fetch instruction from bus */
	if ((read_from_bus(&LO_byte, &HO_byte)) != 0)
	{
	    printf("processor - get_from_bus error - fatal\n");
	    exit(1);
	}
	/* load Instruction Register */
	proc.reg[IR].content = LO_byte;
	proc.reg[IR].content = proc.reg[IR].content << 8;
	proc.reg[IR].content = proc.reg[IR].content + HO_byte;
	proc.PSW_Cbit = carry;
	debug("Current Instruction = [%04x]",proc.reg[IR].content);

	/* increment program counter to next instruction */
	proc.reg[PC].content += 2;		/* advance PC by 2 bytes */
        if (proc.reg[PC].content != NULL){
	debug("Program Counter Updated: PC=[%04x]",proc.reg[PC].content);
        }
	/* decode the instruction */
	if ((proc.reg[IR].content >= 0x4000) && (proc.reg[IR].content <= 0xF000))
	    process_4bit_instr(proc.reg[IR].content);
	else if ((proc.reg[IR].content >= 0x2000) && (proc.reg[IR].content <= 0x3E00))
	    process_7bit_instr(proc.reg[IR].content);
	else if ((proc.reg[IR].content >= 0x0400) && (proc.reg[IR].content <= 0x1EC0))
	    process_10bit_instr(proc.reg[IR].content);
	else
	    process_16bit_instr(proc.reg[IR].content);
	printf("processor = instruction = [%04x]\n", proc.reg[IR].content);
    }
    debug("processor - processing completed\n");
}
