/*
 * This program solves the towers of hanoi problem
 * 9 Feb 1993
 */

#include <stdio.h>

void hanoi(int start, int temp, int end, int n);

void main(int argc, char *argv[])
{
    int start, end, temp, n;
    start = 'a';
    temp = 'b';
    end = 'c';
    n = atoi(argv[1]);
    printf("solving the Towers of Hanoi for %d disks \n", n);
    hanoi(start, temp, end, n);
}

void hanoi(int start, int temp, int end, int n)
{
    if (n == 1)
    {
	printf("%c %s %c\n", start, " --> ", end);
    }
    else
    {
	hanoi(start, end, temp, n - 1);
	printf("%c %s %c\n", start, " --> ", end);
	hanoi(temp, start, end, n - 1);
    }
}
