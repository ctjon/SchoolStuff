#include     <stdio.h>
#include     <stdlib.h>
#include     "loader.h"
#include     "bus.h"
#include     "memory.h"
#include     "processor.h"
#include     "debug.h"

char temp[80];
unsigned int byte0, byte1;
unsigned int low0, high0, low1, high1;
unsigned int mem_addr;
unsigned int start, offset, size;
int hw_count;
int half_words;
int flag;

void load_init();
void load_memory();
void load_now();

void get_line(FILE * input_file);
void get_data(FILE * input_file);
void get_instr(FILE * input_file);
void get_half_word(FILE * input_file);
void relocate();
char *get_number(char c);

int load(char *load_file, unsigned int *off)
/* requires: name of the file, and the offset 				*/
/* modifies: program counter, stack pointer, and memory 		*/
/* effect  : loads an *.xld file to memory and sets the program 	*/
/*  	     counter to the starting address of the program.  It also   */
/*           set the stack pointer to the correct address in memory     */ 
/* 	     It relocates addressing if necessary, if there is an offset*/

{
    FILE *input_file, *output_file;
    int start_line, start_addr, stack_addr, n_lines;
    char *line;
    char ch;
    int n, n1, n2;

    if ((input_file = fopen(load_file, "r")) == NULL)
    {
	printf("ERROR: Cannot open file: %s\n", load_file);
	return -1;
    }
    else
	debug("Opening file: %s", load_file);

    offset = (unsigned) off;	/* offset of memory */
    debug("offset is %d", offset);

    mem_init();			/* initialize memory */

    fscanf(input_file, "%i", &start_line);
    debug("start_line = %d", start_line);

    fscanf(input_file, "%i", &start_addr);	/* starting address */
    debug("start_addr = %d", start_addr);
    start_addr = start_addr + offset;
    debug("NEW start_addr = %d MEM:%x", start_addr, start_addr);

    fscanf(input_file, "%i", &stack_addr);	/* stack address     */
    debug("stack_addr = %d ", stack_addr);
    stack_addr = stack_addr + offset;
    debug("NEW stack_addr = %d MEM:%x", stack_addr, stack_addr);

    fscanf(input_file, "%i", &n_lines);
    debug("n_lines = %d", n_lines);

    fscanf(input_file, "%c", &ch);	/* reads end of line */

    for (n = 1; n <= n_lines; n++)	/* read asembly lines */
	get_line(input_file);

    fscanf(input_file, "%i", &half_words);	/* number of half words */
    debug("half_words = %i", half_words);

    fscanf(input_file, "%c", &ch);	/* reads end of line */
    load_init();		/* initialize load variables */
    load_memory(input_file);	/* load into memory */
    debug("MEMORY LOAD COMPLETE");
    mem_dump();			/* complete memory dump */
    proc.reg[PC].content = start_addr;
	debug("proc.PC set to [%x]",proc.reg[PC].content);
    proc.reg[SP].content = stack_addr;
	debug("proc.SP set to [%x]",proc.reg[PC].content);
    return 0;
}

void load_memory(FILE * input_file)
/* requires:  A pointer to the input file				*/
/* modifies:  memory map						*/
/* effects :   */

{
    unsigned int is_org, is_data, is_instr;
    unsigned int temp;

    do
    {
	get_half_word(input_file);	/* get a half word */
	is_org = low0 >> (unsigned) 6;	/* check if its 11 for ORG */
	is_data = low0 >> (unsigned) 7;	/* check if its 10 for data */
	is_instr = low0 >> (unsigned) 7;	/* check if its 00 for instr */
	debug("org = %d data = %d instr = %d", is_org, is_data, is_instr);
	if (is_org == 3)
	{			/* ORG */
	    temp = (int) byte1;	/* get number of memory address */
	    mem_addr = (offset) + (temp * 2);
	}
	else if (is_data == 1)	/* data declarations */
	    get_data(input_file);
	else if (is_instr == 0)	/* instructions */
	    get_instr(input_file);
    } while (half_words > hw_count);
}
void get_data(FILE * input_file)
{
    unsigned int num_half_words;
    int n;

    num_half_words = byte1;	/* number of hw's of data */
    for (n = 1; n <= num_half_words; n++)
    {
	get_half_word(input_file);	/* get a half word */
	load_now();		/* write it to memory */
	mem_addr = mem_addr + 2;
    }
    if (flag == 0)
    {				/* marks firs data FFFC */
	mem_addr = mem_addr - 2;
	byte0 = 255;		/* FF */
	byte1 = 252;		/* FC */
	load_now();
	mem_addr = mem_addr + 2;
	flag = 1;
    }
}

void get_instr(FILE * input_file)
{
    unsigned int oper1, oper2, lenght, temp, temp1, temp2, temp3;

    temp1 = (unsigned) byte0;
    temp1 = temp1 >> (unsigned) 1;
    lenght = temp1 & (unsigned) 3;	/* get lenght of instructions in hw's */

    temp2 = (unsigned) byte0;
    temp2 = temp2 >> (unsigned) 3;
    oper2 = temp2 & (unsigned) 3;	/* get relocations? of 2nd operand */

    temp3 = (unsigned) byte0;
    temp3 = temp3 >> (unsigned) 5;
    oper1 = temp3 & (unsigned) 3;	/* get relocations? of 1st opernad */

    debug("Oper1 = %d Oper2 = %d Lenght = %d", oper1, oper2, lenght);

    if (lenght == 1)
    {				/* one halfword */
	get_half_word(input_file);
	switch (oper1)
	{			/* check for relocation */
	case 0:
	    break;
	case 1:
	    relocate();
	    break;		/* public */
	case 2:
	    relocate();
	    break;		/* internal */
	case 3:
	    relocate();
	    break;
	}			/* external */
	load_now();
	mem_addr = (mem_addr + 2);
    }
    else if (lenght == 2)
    {				/* two halfwords */
	get_half_word(input_file);
	load_now();		/* write 1st */
	mem_addr = (mem_addr + 2);
	get_half_word(input_file);
	switch (oper1)
	{			/* check for relocation */
	case 0:
	    break;
	case 1:
	    relocate();
	    break;		/* public */
	case 2:
	    relocate();
	    break;		/* internal */
	case 3:
	    relocate();
	    break;
	}			/* external */

	switch (oper2)
	{			/* check for relocation */
	case 0:
	    break;
	case 1:
	    relocate();
	    break;		/* public */
	case 2:
	    relocate();
	    break;		/* internal */
	case 3:
	    relocate();
	    break;
	}			/* external */

	load_now();		/* write 2nd */
	mem_addr = (mem_addr + 2);
    }

    else if (lenght == 3)
    {				/* three halfwords */
	get_half_word(input_file);
	load_now();		/* write 1st */
	mem_addr = (mem_addr + 2);
	get_half_word(input_file);
	switch (oper1)
	{			/* check for relocation */
	case 0:
	    break;
	case 1:
	    relocate();
	    break;		/* public */
	case 2:
	    relocate();
	    break;		/* internal */
	case 3:
	    relocate();
	    break;
	}			/* external */
	load_now();		/* write 2nd */
	mem_addr = (mem_addr + 2);
	get_half_word(input_file);
	switch (oper2)
	{			/* check for relocation */
	case 0:
	    break;
	case 1:
	    relocate();
	    break;		/* public */
	case 2:
	    relocate();
	    break;		/* internal */
	case 3:
	    relocate();
	    break;
	}			/* external */
	load_now();		/* write 3rd */
	mem_addr = (mem_addr + 2);
    }
}

void relocate()
{
    unsigned int temp, temp0, original, offseted;

    temp = (unsigned) byte0;
    temp0 = temp << (unsigned) 8;
    original = temp0 + (unsigned) byte1;	/* add byte0(shifted) and
						 * byte1 */
    offseted = original + offset;	/* add the offset */
    byte0 = offseted >> 8;	/* new byte0 */
    temp0 = byte0;
    temp = temp0 << 8;
    byte1 = offseted - temp;	/* new byte1 */
}

void load_now()
{
    write_on_bus(byte0, byte1);	/* put it in the bus */
    write_to_mem(mem_addr, size);	/* write to memory */
    read_from_mem(mem_addr, size);	/* read from memory */
    read_from_bus(&byte0, &byte1);	/* read from the bus */
}

void get_half_word(FILE * input_file)
{
    char c1, c2, c3, c4, junk;
    char *s1, *s2, *s3, *s4;
    char ch;

    hw_count++;
    debug("-----------------HALF WORD # %d--------------------", hw_count);

    fscanf(input_file, "%c", &ch);	/* always a $ */
    if (ch != '$')
	fscanf(input_file, "%c", &ch);	/* at the end of line */
    /* read the next $    */
    fscanf(input_file, "%c", &c1);	/* get low0 */
    fscanf(input_file, "%c", &c2);	/* get high0 */
    fscanf(input_file, "%c", &c3);	/* get low1 */
    fscanf(input_file, "%c", &c4);	/* get high1 */
    fscanf(input_file, "%c", &junk);	/* space */
    debug("FILE:%c %c %c %c\t", c1, c2, c3, c4);

    s1 = get_number(c1);	/* get string of character */
    low0 = (unsigned) atoi(s1);	/* convert to unsigned int */
    s2 = get_number(c2);
    high0 = (unsigned) atoi(s2);
    s3 = get_number(c3);
    low1 = (unsigned) atoi(s3);
    s4 = get_number(c4);
    high1 = (unsigned) atoi(s4);

    low0 = low0 << (unsigned) 4;/* convert to proper order inside byte */
    byte0 = low0 + high0;
    low1 = low1 << 4;
    byte1 = low1 + high1;
}

void get_line(FILE * input_file)
{
    char ch;
    int n;
    char temp[81];

    n = 0;
    ch = '0';

    fscanf(input_file, "%c", &ch);	/* gets the asembly lines */
    while (ch != '\n')
    {
#ifdef DEBUG
	printf("%c", ch);
#endif
	temp[n] = ch;
	n++;
	fscanf(input_file, "%c", &ch);
    }
    temp[n] = '\0';
#ifdef DEBUG
    printf("%c", ch);
#endif
}


char *get_number(char c)
{

    char ch[3];			/* returns a string of characters */
    /* that represent the hex in decimal */

    switch (c)
    {
    case '0':
	ch[0] = '0';
	ch[1] = '0';
	ch[2] = '\0';
	break;
    case '1':
	ch[0] = '0';
	ch[1] = '1';
	ch[2] = '\0';
	break;
    case '2':
	ch[0] = '0';
	ch[1] = '2';
	ch[2] = '\0';
	break;
    case '3':
	ch[0] = '0';
	ch[1] = '3';
	ch[2] = '\0';
	break;
    case '4':
	ch[0] = '0';
	ch[1] = '4';
	ch[2] = '\0';
	break;
    case '5':
	ch[0] = '0';
	ch[1] = '5';
	ch[2] = '\0';
	break;
    case '6':
	ch[0] = '0';
	ch[1] = '6';
	ch[2] = '\0';
	break;
    case '7':
	ch[0] = '0';
	ch[1] = '7';
	ch[2] = '\0';
	break;
    case '8':
	ch[0] = '0';
	ch[1] = '8';
	ch[2] = '\0';
	break;
    case '9':
	ch[0] = '0';
	ch[1] = '9';
	ch[2] = '\0';
	break;
    case 'A':
	ch[0] = '1';
	ch[1] = '0';
	ch[2] = '\0';
	break;
    case 'B':
	ch[0] = '1';
	ch[1] = '1';
	ch[2] = '\0';
	break;
    case 'C':
	ch[0] = '1';
	ch[1] = '2';
	ch[2] = '\0';
	break;
    case 'D':
	ch[0] = '1';
	ch[1] = '3';
	ch[2] = '\0';
	break;
    case 'E':
	ch[0] = '1';
	ch[1] = '4';
	ch[2] = '\0';
	break;
    case 'F':
	ch[0] = '1';
	ch[1] = '5';
	ch[2] = '\0';
	break;
    }
    return (char *) ch;
}

void load_init()
{				/* initializes loader variables */
    mem_addr = 0;
    mem_addr = mem_addr + offset;	/* sets memory addres */
    size = 2;			/* size is the number of bytes */
    flag = 0;
}
