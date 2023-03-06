#include <stdio.h>
#include "intrpt.h"
#include "processor.h"
#include "memory.h"
#include "bus.h"



int 
push_PSW(void)
/* Pushed the PSW onto the stack. */
{
    pshp();
    return 0;
}

int 
push_pc(void)
/*
 * Pushes the PC onto the stack.
 */
{
    proc.reg[SP].content = proc.reg[SP].content - 2;
    write_on_bus((proc.reg[PC].content & 0x00FF), (proc.reg[PC].content & 0xFF00) >> 8);
    write_to_mem((int) proc.reg[SP].content, 2);
    return 0;
}
int             acknowledge(void)
/* Outputs an acknowledgement */
{
    printf("Interupt request received. /n");
    return 0;
}

int vector_address(int vector)
/*Receives a 5-bit interrupt vector address to input the
new PSW contents */
{

}

int new_PSW(void)
/*Uses the interrupt vector address to input the new PSW contents
Then adds 2 to the address and uses the new address to input the
branch address*/
{

}

