#include     <stdio.h>
#include     "memory.h"
#include     "bus.h"

int mem_init(void)
{
    /* return 0 on success and -1 on failure */
    /* Create memory array and initialize every bit to zero and index for use */

    int n = 0;
    int c = 0;
    int s = 0;
    printf("\n");
    printf("     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
    printf("  0 ");
    for (n = 0; n < MAXMEM; n++)
    {
	mem_unit[n].byte = 0;
	if (c == 16)
	{
	    s++;
	    c = 1;
	    printf("\n");
	    printf("%3x ", s);
	}
	else
	    c++;
	get_lo_nibble(n);
	get_hi_nibble(n);
	printf("%c%c ", mem_nibble.lo, mem_nibble.hi);
    }
    printf("\n\n");
    return 0;
}

int mem_dump(void)
{
    /* return 0 on success and -1 on failure */
    /* dump every bit currently in memory */

    int n = 0;
    int c = 0;
    int s = 0;
    printf("MEMORY DUMP\n");
    printf("     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
    printf("  0 ");
    for (n = 0; n < MAXMEM; n++)
    {
	if (c == 16)
	{
	    s++;
	    c = 1;
	    printf("\n");
	    printf("%3x ", s);
	}
	else
	    c++;
	get_lo_nibble(n);
	get_hi_nibble(n);
	printf("%c%c ", mem_nibble.lo, mem_nibble.hi);
    }
    printf("\n\n");
    return 0;
}

int mem_shutdown(void)
{
    /* return 0 on success and -1 on failure */
    /* garbage collection of memory array for host system */
    debug("going into mem_shutdown");
    free(mem_unit);
}
