/*
 * FREQ.C Written By: Chris Tjon NAID#: 110975-8 For: CS 474 Program #4
 * 
 * This is the filter "freq" which splits its text input into words, one word
 * per line, all alphabetic characters translated to lower case, and puts
 * this result on its standard output sorted with total number of occurrances
 * of words.
 */

#include <stdio.h>

#define STDIN 0
#define STDOUT 1

int exec(char *arg0, char *arg1, char *arg2);
int spawn(void);

main()
{
    if (spawn()) exec("sort", "-n", "-r");
    else if (spawn()) exec("uniq", "-c", NULL);
    else if (spawn()) exec("sort", NULL, NULL);
    else exec("prep", NULL, NULL);
}

int exec(char *arg0, char *arg1, char *arg2)
{
    execlp(arg0, arg0, arg1, arg2, NULL);
    perror("execlp"), exit(1);
}

int spawn(void)
/*
 * spawn returns 0 when we are a child, otherwise spawn returns the pid of
 * the child which is provided by fork() (fork returns the child's pid)
 */
{
    int pfd[2], n;
    if (pipe(pfd) == -1) perror("open pipe"), exit(1);
    switch (n = fork())
    {
    case -1:
	perror("fork"), exit(1);
	break;
    case 0:
	if (close(STDOUT) == -1) perror("close STDOUT"), exit(1);
	if (dup(pfd[1]) == -1) perror("dup child"), exit(1);
	break;
    default:
	if (close(STDIN) == -1) perror("close STDIN"), exit(1);
	if (dup(pfd[0]) == -1) perror("dup parent"), exit(1);
    }
    if ((close(pfd[0]) == -1) || (close(pfd[1]) == -1))
	perror("close pipe"), exit(1);
    return (n);
}
