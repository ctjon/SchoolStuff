/* PROCESSOR.H */

#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define SP 6
#define PC 7
#define IR 8
#define scratch 9
#endif

typedef struct registers
{
	unsigned int content:16;
} REGISTER;

typedef struct processor
{
    unsigned int PSW_unused:8;
    unsigned int PSW_Ibit:1;	/* current interrupt level */
    unsigned int PSW_IPL:3;	/* current interrupt mask */
    unsigned int PSW_Zbit:1;	/* zero bit */
    unsigned int PSW_Nbit:1;	/* negative bit */
    unsigned int PSW_Cbit:1;	/* carry bit */
    unsigned int PSW_Vbit:1;	/* overflow */

    REGISTER reg[10];
} PROCESSOR;

PROCESSOR proc;

void processor(void);
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

#endif
