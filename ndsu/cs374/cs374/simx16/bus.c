/* BUS.C */

#include "bus.h"
#include "memory.h"
#include "debug.h"

void get_lo_nibble(int n)
/* gets the hex repersentation of decimal numbers */
{
    unsigned int mem;

    mem = mem_unit[n].byte;
    mem = mem >> 4;
    switch (mem)
    {
    case 0:
	mem_nibble.lo = '0';
	break;
    case 1:
	mem_nibble.lo = '1';
	break;
    case 2:
	mem_nibble.lo = '2';
	break;
    case 3:
	mem_nibble.lo = '3';
	break;
    case 4:
	mem_nibble.lo = '4';
	break;
    case 5:
	mem_nibble.lo = '5';
	break;
    case 6:
	mem_nibble.lo = '6';
	break;
    case 7:
	mem_nibble.lo = '7';
	break;
    case 8:
	mem_nibble.lo = '8';
	break;
    case 9:
	mem_nibble.lo = '9';
	break;
    case 10:
	mem_nibble.lo = 'A';
	break;
    case 11:
	mem_nibble.lo = 'B';
	break;
    case 12:
	mem_nibble.lo = 'C';
	break;
    case 13:
	mem_nibble.lo = 'D';
	break;
    case 14:
	mem_nibble.lo = 'E';
	break;
    case 15:
	mem_nibble.lo = 'F';
	break;
    }
}

void get_hi_nibble(int n)
/* gets the hex repersentation of decimal numbers */
{
    unsigned int mem, temp;

    mem = mem_unit[n].byte;
    mem = mem << 4;
    mem = mem & 240;
    temp = mem >> 4;

    switch (temp)
    {
    case 0:
	mem_nibble.hi = '0';
	break;
    case 1:
	mem_nibble.hi = '1';
	break;
    case 2:
	mem_nibble.hi = '2';
	break;
    case 3:
	mem_nibble.hi = '3';
	break;
    case 4:
	mem_nibble.hi = '4';
	break;
    case 5:
	mem_nibble.hi = '5';
	break;
    case 6:
	mem_nibble.hi = '6';
	break;
    case 7:
	mem_nibble.hi = '7';
	break;
    case 8:
	mem_nibble.hi = '8';
	break;
    case 9:
	mem_nibble.hi = '9';
	break;
    case 10:
	mem_nibble.hi = 'A';
	break;
    case 11:
	mem_nibble.hi = 'B';
	break;
    case 12:
	mem_nibble.hi = 'C';
	break;
    case 13:
	mem_nibble.hi = 'D';
	break;
    case 14:
	mem_nibble.hi = 'E';
	break;
    case 15:
	mem_nibble.hi = 'F';
	break;
    }
}

int write_to_mem(int addr, int num_bytes)
/*----------------------------------------------------------------------------+
| REQUIRES: memory and bus are initialized and bus contains legitimate value  |
| MODIFIES: memory (at addr)                                                  |
| EFFECTS:  takes the current bus value and stores it in memory at addr       |
+----------------------------------------------------------------------------*/
{
    /* return 0 on success and -1 on failure */
    /* takes the info from bus and puts it in memory */

    int i_num_bytes, i_addr;

    debug("MEMORY: address = %x index = %d num_bytes = %d", addr, addr, num_bytes);
    i_num_bytes = (int) num_bytes;
    i_addr = (int) addr;

    if (i_num_bytes == 1)
    {
	mem_unit[i_addr].byte = bus.byte1;
	get_lo_nibble(i_addr);
	get_hi_nibble(i_addr);
	debug("WRITE:  %c %c", mem_nibble.lo, mem_nibble.hi);
	return 0;
    }

    else if (i_num_bytes == 2)
    {
	mem_unit[i_addr].byte = bus.byte1;
	get_lo_nibble(i_addr);
	get_hi_nibble(i_addr);
	debug("WRITE:  %c %c ", mem_nibble.lo, mem_nibble.hi);
	mem_unit[i_addr + 1].byte = bus.byte0;
	get_lo_nibble(i_addr + 1);
	get_hi_nibble(i_addr + 1);
	debug("%c %c", mem_nibble.lo, mem_nibble.hi);
	return 0;
    }
    else
	return -1;
}


int read_from_mem(int addr, int num_bytes)
/*----------------------------------------------------------------------------+
| REQUIRES: memory and bus are initialized                                    |
| MODIFIES: bus                                                               |
| EFFECTS:  places num_bytes stored at addr on bus                            |
+----------------------------------------------------------------------------*/
{
    /* return 0 on success and -1 on failure */
    /* reads from memory and writes it to the bus */

    int i_num_bytes, i_addr;

    i_num_bytes = (int) num_bytes;
    i_addr = (int) addr;

    if (i_num_bytes == 1)
    {
	bus.byte1 = mem_unit[i_addr].byte;
	get_lo_nibble(i_addr);
	get_hi_nibble(i_addr);
	debug("READ :  %c %c", mem_nibble.lo, mem_nibble.hi);
	return 0;
    }
    else if (i_num_bytes == 2)
    {
	bus.byte1 = mem_unit[i_addr].byte;
	get_lo_nibble(i_addr);
	get_hi_nibble(i_addr);
	debug("READ :  %c %c ", mem_nibble.lo, mem_nibble.hi);
	bus.byte0 = mem_unit[i_addr + 1].byte;
	get_lo_nibble(i_addr + 1);
	get_hi_nibble(i_addr + 1);
	debug("%c %c", mem_nibble.lo, mem_nibble.hi);
	return 0;
    }
    else
	return -1;
}


int write_on_bus(unsigned int byte0, unsigned int byte1)
/*----------------------------------------------------------------------------+
| REQUIRES: bus has been initialized                                          |
| MODIFIES: bus.byte0 and bus.byte1                                           |
| EFFECTS:  assigns byte0 to low order byte of bus and byte1 to high order    |
|           byte of bus                                                       |
+----------------------------------------------------------------------------*/
{
    bus.byte0 = byte1;
    bus.byte1 = byte0;
    return 0;
}

int read_from_bus(unsigned int *byte0, unsigned int *byte1)
/*----------------------------------------------------------------------------+
| REQUIRES: bus has been initialized and contains a legitmate value           |
| MODIFIES: byte0 and byte1                                                   |
| EFFECTS:  assigns low order byte of bus to byte0 and high order byte of bus |
|           to byte1                                                          |
+----------------------------------------------------------------------------*/
{
    *byte0 = bus.byte1;
    *byte1 = bus.byte0;
    return 0;
}
