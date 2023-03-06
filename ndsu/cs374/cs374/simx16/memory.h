#include     <stdio.h>
#define      MAXMEM 256		/* maximum memory size */

typedef struct real_byte
{
    char lo;
    char hi;
}         CHAR_BYTE;

CHAR_BYTE mem_nibble;

typedef struct mem_unit
{
    unsigned int byte:8;
}        MEMORY;

MEMORY mem_unit[MAXMEM];

int mem_init(void);
/* return 0 on success and -1 on failure */
/* Create memory array and initialize every bit to zero and index for use */

int mem_shutdown(void);
/* return 0 on success and -1 on failure */
/* garbage collection of memory array for host system */

int mem_dump();
/* return 0 on succes and -1 on failure */
/* dump every byte currently in memory */

/* additional functions only used by memory now */

void get_hi_nibble(int n);
void get_lo_nibble(int n);
