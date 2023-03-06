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

int put_4bit_info(int type, unsigned int value, unsigned int mode, int bytes)
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



unsigned int get_4binstru_reg_mode(unsigned mode, int num_bytes)
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
unsigned int get_4binstru_6bit_mode(unsigned mode, int num_bytes)
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


unsigned int sub_half(unsigned int t1, unsigned int t2, int wcarry)
/*----------------------------------------------------------------
| REQUIRES : TWO UNSIGNED INTS TO ADD                            |
|           wcarry== 1 indicated with borrow                     |
| EFFECTS  : ADDS INTERGERS AND RETURNS RESULT SETTING PSW       |
| MODIFYIES| NOTHING                                             |
----------------------------------------------------------------*/
{
    if (wcarry == 1)
    {
	t2 = t2 - proc.PSW_Cbit;
    }
    if (t2 == t1)
    {
	printf("in 1 \n");
	t2 = t2 - t1;
	printf("t2 value is %u \n", t2);
	proc.PSW_Zbit = 1;
	proc.PSW_Nbit = t2 >> 15;
	proc.PSW_Cbit = 0;
	proc.PSW_Vbit = 0;
    }
    else if (t2 > t1)
    {
	printf("in 2 \n");
	t2 = t2 - t1;
	proc.PSW_Zbit = 0;
	proc.PSW_Nbit = t2 >> 15;
	proc.PSW_Cbit = 0;
	proc.PSW_Vbit = 0;
    }
    else
    {
	printf("in 3 \n");
	t2 = t2 - t1;
	proc.PSW_Zbit = 0;
	proc.PSW_Nbit = t2 >> 14;
	proc.PSW_Cbit = 0;
	if (t2 > 65531)
	{
	    proc.PSW_Vbit = 1;
	}
	else
	{
	    proc.PSW_Vbit = 0;
	}
    }
    return t2;
}



unsigned int sub_byte(unsigned int t1, unsigned int t2, int wcarry)
/*----------------------------------------------------------------
| REQUIRES : TWO UNSIGNED INTS TO ADD                            |
|           wcarry== 1 indicated with borrow                     |
| EFFECTS  : ADDS INTERGERS AND RETURNS RESULT SETTING PSW       |
| MODIFYIES| NOTHING                                             |
----------------------------------------------------------------*/
{
    if (wcarry == 1)
	t2 = t2 - proc.PSW_Cbit;
    if (t2 == t1)
    {
	t2 = t2 - t1;
	proc.PSW_Zbit = 1;
	proc.PSW_Nbit = t2 >> 7;
	proc.PSW_Cbit = 0;
	proc.PSW_Vbit = 0;
    }
    else if (t2 > t1)
    {
	t2 = t2 - t1;
	proc.PSW_Zbit = 0;
	proc.PSW_Nbit = t2 >> 7;
	proc.PSW_Cbit = 0;
	proc.PSW_Vbit = 0;
    }
    else
    {
	t2 = t2 + (~t1 + 1);
	proc.PSW_Zbit = 0;
	proc.PSW_Nbit = t2 >> 7;
	proc.PSW_Cbit = 0;
	if (t2 < 127)
	{
	    proc.PSW_Vbit = 0;
	}
	else
	{
	    proc.PSW_Vbit = 1;
	}
    }
    return t2;
}

unsigned int power2(int in)
/*----------------------------------------------------------------------+
| REQUIRES : in be and interger greater than zero                       |
| EFFECTS  : returns 2 raised to the power in                           |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/
{
    unsigned int t;
    int i;

    if (in >0)
    {
	t = 1;
	for (i = 1; i <= in; i++)
	{
	    t = t * 2;
	}
    }
    else
    {
	t = 1;
    }
    return t;
}

unsigned int add_half(unsigned int scr, unsigned int dest, int flag)
/*----------------------------------------------------------------------+
| REQUIRES : adds two half words  together.  If y is 1 it is add with   |
|                                                               carry   |
| EFFECTS  : adds two half words together                               |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/
{

    bit cary, term1, term2;
    unsigned int t1, t2, temp, sum;
    int i;
    sum = 0;
    t2 = dest;
    t1 = scr;
    if (flag == 0)
    {
	cary.bit = 0;
    }
    else
    {
	cary.bit = proc.PSW_Cbit;
    }
    term1.bit = t1;
    term2.bit = t2;
    for (i = 0; i <= 7; i++)
    {
	if ((term2.bit == 1) && (term1.bit == 0) && (cary.bit == 0))
	{
	    sum = sum + power2(i);
	    cary.bit = 0;
	}
	else if ((term2.bit == 0) && (term1.bit == 1) && (cary.bit == 0))
	{
	    sum = sum + power2(i);
	    cary.bit = 0;
	}
	else if ((term2.bit == 1) && (term1.bit == 1) && (cary.bit == 0))
	{
	    cary.bit = 1;
	}
	else if ((term2.bit == 0) && (term1.bit == 0) && (cary.bit == 1))
	{
	    sum = sum + power2(i);
	    cary.bit = 0;
	}
	else if ((term2.bit == 1) && (term1.bit == 0) && (cary.bit == 1))
	{
	    cary.bit = 0;
	}
	else if ((term2.bit == 0) && (term1.bit == 1) && (cary.bit == 1))
	{
	    cary.bit = 1;
	}
	else if ((term2.bit == 1) && (term1.bit == 1) && (cary.bit == 1))
	{
	    cary.bit = 1;
	    sum = sum + power2(i);
	}
	else
	{
	    cary.bit = 0;
	}
	term1.bit = t1 >> i + 1;
	term2.bit = t2 >> i + 1;
    }
    proc.PSW_Cbit = cary.bit;
    proc.PSW_Nbit = dest >> 15;
    proc.PSW_Zbit = 0;
    if (sum >= 65531)
    {
	proc.PSW_Vbit = 1;
    }
    else
    {
	proc.PSW_Vbit = 0;
    }
    return sum;
}



unsigned int add_byte(unsigned int scr, unsigned int dest, int y)
/*----------------------------------------------------------------------+
| REQUIRES : adds two bytes together.  If y is 1 it is add with carry   |
| EFFECTS  : adds two bytes together                                    |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/



{

    bit cary, term1, term2;
    unsigned int t1, t2, temp, sum;
    int i;
    sum = 0;
    if (y == 0)
    {
	cary.bit = 0;
    }
    else
    {
	cary.bit = proc.PSW_Cbit;
    }
    t1 = scr;
    t2 = dest;
    term1.bit = t1;
    term2.bit = t2;
    for (i = 0; i <= 7; i++)
    {
	if ((term2.bit == 1) && (term1.bit == 0) && (cary.bit == 0))
	{
	    sum = sum + power2(i);
	    cary.bit = 0;
	}
	else if ((term2.bit == 0) && (term1.bit == 1) && (cary.bit == 0))
	{
	    sum = sum + power2(i);
	    cary.bit = 0;
	}
	else if ((term2.bit == 1) && (term1.bit == 1) && (cary.bit == 0))
	{
	    cary.bit = 1;
	}
	else if ((term2.bit == 0) && (term1.bit == 0) && (cary.bit == 1))
	{
	    sum = sum + power2(i);
	    cary.bit = 0;
	}
	else if ((term2.bit == 1) && (term1.bit == 0) && (cary.bit == 1))
	{
	    cary.bit = 0;
	}
	else if ((term2.bit == 0) && (term1.bit == 1) && (cary.bit == 1))
	{
	    cary.bit = 1;
	}
	else if ((term2.bit == 1) && (term1.bit == 1) && (cary.bit == 1))
	{
	    cary.bit = 1;
	    sum = sum + power2(i);
	}
	else
	{
	    cary.bit = 0;
	}
	term1.bit = t1 >> i + 1;
	term2.bit = t2 >> i + 1;
    }
    proc.PSW_Cbit = cary.bit;
    proc.PSW_Nbit = sum >> 7;
    if (sum == 0)
    {
	proc.PSW_Zbit = 1;
    }
    else
    {
	proc.PSW_Zbit = 0;
    }
    if (sum >= 127)
    {
	proc.PSW_Vbit = 1;
    }
    else
    {
	proc.PSW_Vbit = 0;
    }
    return sum;
}

unsigned int get_psw(void)
/*----------------------------------------------------------------------+
| REQUIRES : nothing                                                    |
| EFFECTS  : returns the contents of the PSW                            |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/
{
    REGISTER contents;
    contents.content = proc.PSW_unused;
    contents.content = (contents.content < 1) + proc.PSW_Ibit;
    contents.content = (contents.content < 3) + proc.PSW_IPL;
    contents.content = (contents.content < 1) + proc.PSW_Zbit;
    contents.content = (contents.content < 1) + proc.PSW_Nbit;
    contents.content = (contents.content < 1) + proc.PSW_Cbit;
    contents.content = (contents.content < 1) + proc.PSW_Vbit;
    return contents.content;
}
int put_psw(unsigned int value)
/*----------------------------------------------------------------------+
| REQUIRES : unsigned value that is to go into the psw register         |
| EFFECTS  : replaces the value of the PSW with value.returns 0 if good |
| MODIFYIES| PSW                                                        |
+----------------------------------------------------------------------*/
{
    proc.PSW_Vbit = value;
    proc.PSW_Cbit = value >> 1;
    proc.PSW_Nbit = value >> 2;
    proc.PSW_Zbit = value >> 3;
    value = value >> 4;
    proc.PSW_IPL = value;
    proc.PSW_Ibit = value >> 3;
    value = value >> 4;
    proc.PSW_unused = value;
    return 0;
}

int process_4bit_instr(unsigned int instruction)
/*----------------------------------------------------------------------+
| REQUIRES : instruction be the current instruction to be processed     |
|            operand1,and operand2 are unsigned intergers with the      |
|            values of the scr and dest for the 4bit instructions       |
| EFFECTS  : processes all of the 4bit instructions                     |
| MODIFYIES| registers, memory and ouput as per instructions            |
+----------------------------------------------------------------------*/
{
    int x, num_bytes;
    unsigned int out, value, source, dest;
    bit temp;
    byte mode, destm;
    value = instruction >> 13;
    temp.bit = instruction >> 14;
    if (temp.bit == 1)
	num_bytes = 1;
    if (temp.bit == 0)
	num_bytes = 2;
    switch (value)
    {
    case 7:
	/* move and or in or out instructions   */
	if (instruction == 0xEC97)
	{
	    pshp();
	    break;
	}
	if (instruction == 0xED72)
	{
	    popp();
	    break;
	}
	destm.byte = instruction >> 2;
	destm.byte = destm.byte >> 2;
	mode.byte = instruction >> 10;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    source = get_4binstru_6bit_mode(mode.byte, num_bytes);
	    put_4bit_info(1, source, destm.byte, num_bytes);
	    break;
	}
	else
	{
	    source = get_4binstru_reg_mode(mode.byte, num_bytes);
	    put_4bit_info(1, source, destm.byte, num_bytes);
	    break;
	}
	break;
    case 6:
	/* compare instructions  */
	mode.byte = instruction >> 10;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    source = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    source = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	mode.byte = instruction >> 2;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    dest = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    dest = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	if (num_bytes == 2)
	{
	    source = sub_half(source, dest, 0);
	}
	else
	{
	    source = sub_byte(source, dest, 0);
	}
	break;
    case 5:
	/* subtract with borrow instructions    */
	mode.byte = instruction >> 10;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    source = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    source = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	mode.byte = instruction >> 2;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    dest = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    dest = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	if (num_bytes == 2)
	{
	    source = sub_half(source, dest, 1);
	}
	else
	{
	    source = sub_byte(source, dest, 1);
	}
	put_4bit_info(0, mode.byte, source, num_bytes);
	break;

    case 4:
	/* subract instruction */
	mode.byte = instruction >> 10;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    source = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    source = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	mode.byte = instruction >> 2;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    dest = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    dest = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	if (num_bytes == 2)
	{
	    source = sub_half(source, dest, 0);
	}
	else
	{
	    source = sub_byte(source, dest, 0);
	}
	put_4bit_info(0, mode.byte, source, num_bytes);
	break;

    case 3:
	/* add with carry instruction */
	mode.byte = instruction >> 10;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    source = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    source = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	mode.byte = instruction >> 2;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    dest = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    dest = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	if (num_bytes == 2)
	{
	    source = add_half(source, dest, 1);
	}
	else
	{
	    source = add_byte(source, dest, 1);
	}
	put_4bit_info(0, mode.byte, source, num_bytes);
	break;
    case 2:
	/* add instruction  */
	mode.byte = instruction >> 10;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    source = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    source = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	mode.byte = instruction >> 2;
	mode.byte = mode.byte >> 2;
	if ((mode.byte == 58) || (mode.byte == 59))
	{
	    dest = get_4binstru_6bit_mode(mode.byte, num_bytes);
	}
	else
	{
	    dest = get_4binstru_reg_mode(mode.byte, num_bytes);
	}
	if (num_bytes == 2)
	{
	    source = add_half(source, dest, 0);
	}
	else
	{
	    source = add_byte(source, dest, 0);
	}
	put_4bit_info(0, mode.byte, source, num_bytes);
	break;
    default:
	printf("not a valid  4 bit opcode \n");
    }
}
int pshp(void)
/*----------------------------------------------------------------------+
| REQUIRES : nothing                                                    |
| EFFECTS  :  pushes the contents of the PSW on the stack               |
| MODIFYIES| the stack and the stack pointer register                   |
+----------------------------------------------------------------------*/
{
    unsigned int value;
    proc.reg[SP].content = proc.reg[SP].content - 2;
    value = get_psw();
    if (write_on_bus(value, value >> 8) == 0)
    {
	if (write_to_mem((int) proc.reg[SP].content, 2) == 0)
	{
	    return 0;
	}
	else
	{
	    printf("error in pshp write to mem \n");
	    return -1;
	}
    }
    else
    {
	printf("error in pshp write to bus \n");
	return -1;
    }
}
int popp(void)
/*----------------------------------------------------------------------+
| REQUIRES : nothing                                                    |
| EFFECTS  : takes 2 bytes off stack and puts them in the PSW                |
| MODIFYIES| the stack and the stack pointer register                   |
+----------------------------------------------------------------------*/
{
    unsigned int byte0, byte1, value;
    if (read_from_mem((int) proc.reg[SP].content, 2) == 0)
    {
	if (read_from_bus(&byte0, &byte1) == -1)
	{
	    printf("error in popp read from bus \n");
	    return -1;
	}
    }
    else
    {
	printf("error in popp read from mem \n");
	return -1;
    }
    value = (byte1 << 8) + byte0;
    if (put_psw(value) == 0)
    {
	proc.reg[SP].content = proc.reg[SP].content + 2;
	return 0;
    }
    else
    {
	printf("popp error on putpsw \n");
	return -1;
    }
}
