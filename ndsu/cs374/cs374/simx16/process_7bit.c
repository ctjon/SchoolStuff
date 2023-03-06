#include <stdio.h>
#include "processor.h"
#include "bus.h"
#include "debug.h"

typedef struct BYTE
{
    unsigned int byte:8;
}    byte;
typedef struct BIT
{
    unsigned int bit:1;
}   bit;

int put_7bit_info(int type, unsigned int value, unsigned int mode, int bytes)
/*----------------------------------------------------------------------+
| REQUIRES : value is the number to place in the approcriate place
             according to mode. mode specifies where to place things
             bytes tells how many bytes to place. 1 or  2;
             type is used to indicate move instruction 1 means move
| EFFECTS  :   placeses value in appropriate place,                     |
| MODIFYIES| register in auto incr or dec mode                          |
+----------------------------------------------------------------------*/
{
    byte reg, mod;
    mod.byte = mode << 2;
    mod.byte = mod.byte >> 2;
    if (mod.byte == 59)
    {
	write_on_bus(value, value >> 8);
	write_to_mem((int) proc.reg[scratch].content, bytes);
	return 0;
    }
    reg.byte = mod.byte >> 3;
    mod.byte = mod.byte << 5;
    mod.byte = mod.byte >> 5;
    if (mod.byte == 0)
    {
	proc.reg[(int) reg.byte].content = value;
    }
    else if (mod.byte == 1)
    {				/* indirect */
	write_on_bus(value, value >> 8);
	write_to_mem((int) proc.reg[(int) reg.byte].content, bytes);
	return 0;
    }
    else if (mod.byte == 3)
    {				/* increment */
	write_on_bus(value, value >> 8);
	write_to_mem((int) proc.reg[(int) reg.byte].content, bytes);
	if (type == 1)
	{
	    proc.reg[(int) reg.byte].content = proc.reg[(int) reg.byte].content + bytes;
	}
	return 0;
    }
    else if (mod.byte == 7)
    {				/* decrement */
	if (type == 1)
	{
	    proc.reg[(int) reg.byte].content = proc.reg[(int) reg.byte].content + bytes;
	}
	write_on_bus(value, value >> 8);
	write_to_mem((int) proc.reg[(int) reg.byte].content, bytes);
	return 0;
    }
    else if (mod.byte == 6)
    {				/* relative */
	write_on_bus(value, value >> 8);
	write_to_mem((int) proc.reg[(int) reg.byte].content + (int) proc.reg[scratch].content, bytes);
	return 0;
    }
    else
    {
	printf("error in put info\n");
    }
}



unsigned int get_7binstru_reg_mode(unsigned mode, int num_bytes)
/*----------------------------------------------------------------------+
| REQUIRES : mode of current 4 bit instruction being processe. mode     |
             must be of the 6 bit type.  Num_bytes tells how many bytes
             to return2  means it is a half word, 1 a byte;
| EFFECTS  : returns what the instruction is operating on               |
| MODIFYIES| register in auto incr or dec mode                          |
+----------------------------------------------------------------------*/
{
    byte reg, mod;
    unsigned displacement, byte0, byte1, value;
    reg.byte = mode >> 3;
    mod.byte = mode << 3;
    mod.byte = mod.byte >> 3;
    if (mod.byte == 0)
    {				/* register direct */
	return proc.reg[(int) reg.byte].content;
    }
    else if (mod.byte == 1)
    {				/* register indirect */
	if (num_bytes == 2)
	{
	    read_from_mem((int) proc.reg[(int) reg.byte].content, 2);
	    read_from_bus(&byte0, &byte1);
	    value = byte1;
	    value = (value << 8) + byte0;
	    return value;
	}
	else
	{
	    read_from_mem((int) proc.reg[(int) reg.byte].content, 1);
	    read_from_bus(&byte0, &byte1);
	    return byte0;
	}
    }
    else if (mod.byte == 5)
    {				/* reg indirect auto increment */
	if (num_bytes == 2)
	{
	    read_from_mem((int) proc.reg[(int) reg.byte].content, 2);
	    proc.reg[(int) reg.byte].content = proc.reg[(int) reg.byte].content + 2;
	    read_from_bus(&byte0, &byte1);
	    value = byte1;
	    value = (value << 8) + byte0;
	    return value;
	}
	else
	{
	    read_from_mem((int) proc.reg[(int) reg.byte].content, 1);
	    proc.reg[(int) reg.byte].content = proc.reg[(int) reg.byte].content + 1;
	    read_from_bus(&byte0, &byte1);
	    return byte0;
	}
    }
    else if (mod.byte == 7)
    {				/* reg indirect auto decrememnt */
	if (num_bytes == 2)
	{
	    proc.reg[(int) reg.byte].content = proc.reg[(int) reg.byte].content - 2;
	    read_from_mem((int) proc.reg[(int) reg.byte].content, 2);
	    read_from_bus(&byte0, &byte1);
	    value = byte1;
	    value = (value << 8) + byte0;
	    return value;
	}
	else
	{
	    proc.reg[(int) reg.byte].content = proc.reg[(int) reg.byte].content - 1;
	    read_from_mem((int) proc.reg[(int) reg.byte].content, 1);
	    read_from_bus(&byte0, &byte1);
	    return byte0;
	}
    }
    else if (mod.byte == 6)
    {				/* relative addressing */
	read_from_mem((int) proc.reg[PC].content, 2);
	proc.reg[PC].content = proc.reg[PC].content + 2;
	read_from_bus(&byte0, &byte1);
	displacement = (byte1 << 8) + byte0;
	proc.reg[scratch].content = displacement;
	if (num_bytes == 2)
	{
	    read_from_mem((int) displacement, 2);
	    read_from_bus(&byte0, &byte1);
	    value = (byte1 << 8) + byte0;
	    return value;
	}
	else
	{
	    read_from_mem((int) displacement, 1);
	    read_from_bus(&byte0, &byte1);
	    value = (byte1 << 8) + byte0;
	    return byte0;
	}
    }
    else
    {
	printf("error in get infor\n");
    }
}
unsigned int get_7binstru_6bit_mode(unsigned mode, int num_bytes)
/*----------------------------------------------------------------------+
| REQUIRES : mode of current 4 bit instruction being processe. mode     |
             must be of the 6 bit type.  Num_bytes tells how many bytes
             to return. 0 means half word 1 means byte;
| EFFECTS  : returns value pointed to by instruction                    |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/
{
    byte mod, r, m;
    int index;
    unsigned int address, value, contents, byte0, byte1;
    bit temp1;

    read_from_mem((int) proc.reg[PC].content, 2);
    proc.reg[PC].content = proc.reg[PC].content + 2;
    read_from_bus(&byte0, &byte1);
    value = byte1;
    value = (value << 8) + byte0;
    proc.reg[scratch].content = value;
    if (mode == 58)
    {				/* immediate mode */
	return value;
    }
    else if (mode == 59)
    {				/* direct mode */
	if (num_bytes == 2)
	{
	    read_from_mem((int) value, 2);
	    read_from_bus(&byte0, &byte1);
	    value = byte1;
	    value = (value << 8) + byte0;
	    return value;
	}
	else
	{
	    read_from_mem((int) value, 1);
	    read_from_bus(&byte0, &byte1);
	    return byte0;
	}
    }
    else
    {
	printf("invalid 6 bit mode field\n");
    }
}



int notb(unsigned int scr, unsigned int *dest)
/*-----------------------------------------------------------------------
| REQUIRES : scr is unsigned int. dest is pointer to unsigned int       |
| EFFECTS  :  the contents of scr are negated and stored in dest        |
| MODIFYIES| dest                                                       |
-----------------------------------------------------------------------*/
{
    *dest = ~scr;
    return 0;
}
int noth(unsigned int scr, unsigned int *dest)
/*-----------------------------------------------------------------------
| REQUIRES : scr is unsigned int. dest is pointer to unsigned int       |
| EFFECTS  :  the contents of scr are negated and stored in dest        |
| MODIFYIES| dest                                                       |
-----------------------------------------------------------------------*/
{
    *dest = ~scr;
    return 0;
}

int process_7bit_instr(unsigned int instruction)
/*----------------------------------------------------------------------+
| REQUIRES : nothing                                                    |
| EFFECTS  : takes 2 bytes off stack and puts them in the PSW                |
| MODIFYIES| the stack and the stack pointer register                   |
+----------------------------------------------------------------------*/
{
}
