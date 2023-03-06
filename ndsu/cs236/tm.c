/**************************/
/* TM.C                   */
/* Written By: Chris Tjon */
/* For: CS236             */
/* Date: 3 May 1993       */
/**************************/

#include <stdio.h>
#include "list.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define MAX_ALPHABET 2		/* maximum alphabet symbols */
#define MAX_TAPE_SYM 2		/* maximum tape symbols     */
#define MAX_STATES 3		/* includes halt state      */
#define MAX_TAPE_LENGTH 40
#define INFINITE_AT 20

typedef struct tm_node
{
    int state;
    char tape_symbol;
    int move_to;
    char write_symbol;
    int move_dir;		/* may be -1,0,1 (for left, stationary, and
				 * right) */
}       TM_NODE;

LIST *q00, *q01, *q10, *q11;
LIST *save_q00, *save_q01, *save_q10, *save_q11;
long int num_crashed, num_halted, num_infinite, num_machines;
int max_ones, num_ones, num_moves, tape_pos;
char tape[MAX_TAPE_LENGTH], tape_symbols[MAX_TAPE_SYM];

LIST *build_move_list(int state, char tape_symbol, int num_states);
void run_unbounded(TM_NODE * move);
void run_bounded(TM_NODE * move);

void main(int argc, char *argv[])
{
    extern LIST *save_q00, *save_q01, *save_q10, *save_q11;
    extern LIST *q00, *q01, *q10, *q11;
    extern long int num_crashed, num_halted, num_infinite, num_machines;
    extern int max_ones, num_ones, num_moves, tape_pos;
    extern char tape[MAX_TAPE_LENGTH], tape_symbols[MAX_TAPE_SYM];
    register int i, j, k, l, m;

    if (argc != 2)
    {
	fprintf(stderr, "Usage: tm u|b\n");
	exit(1);
    }

    /*
     * define the tape symbol alphabet
     */
    tape_symbols[0] = '0';
    tape_symbols[1] = '1';

    /*
     * set up global counters
     */
    num_machines = 0;
    max_ones = 0;
    num_halted = 0;
    num_crashed = 0;
    num_infinite = 0;
    num_moves = 0;

    /*
     * initialize the move lists
     */
    save_q00 = build_move_list(0, tape_symbols[0], MAX_STATES);
    save_q01 = build_move_list(0, tape_symbols[1], MAX_STATES);
    save_q10 = build_move_list(1, tape_symbols[0], MAX_STATES);
    save_q11 = build_move_list(1, tape_symbols[1], MAX_STATES);

    /*
     * create copies of the list pointers so that we don't destroy the
     * originals
     */

    q00 = save_q00;
    q01 = save_q01;
    q10 = save_q10;
    q11 = save_q11;

    /*
     * run the machine with all combinations of the lists
     */

    for (i = 1; i <= list_length(save_q00); i++)
    {
	for (j = 1; j <= list_length(save_q01); j++)
	{
	    for (k = 1; k <= list_length(save_q10); k++)
	    {
		for (l = 1; l <= list_length(save_q11); l++)
		{
		    /*
		     * initialize the tape
		     */
		    for (m = 0; m <= MAX_TAPE_LENGTH - 1; m++)
			tape[m] = '0';
		    num_ones = 0;
		    num_moves = 0;
		    num_machines++;
		    switch (*argv[1])
		    {
		    case 'b':
			tape_pos = 1;
			run_bounded((TM_NODE *) node_item(q00));
			break;
		    case 'u':
			tape_pos = (MAX_TAPE_LENGTH / 2);
			run_unbounded((TM_NODE *) node_item(q00));
			break;
		    default:
			fprintf(stderr, "Usage: tm u|b\n");
			exit(1);
		    }
		    q11 = next_node(q11);
		}
		q11 = save_q11;
		q10 = next_node(q10);
	    }
	    q10 = save_q10;
	    q01 = next_node(q01);
	}
	q01 = save_q01;
	q00 = next_node(q00);
    }

    /*
     * destroy the lists as we are done
     */
    q00 = destroy_list(q00);
    q01 = destroy_list(q01);
    q10 = destroy_list(q10);
    q11 = destroy_list(q11);

    printf("\n");
    if (*argv[1] == 'b')
	printf("Bounded Tape Results:\n");
    if (*argv[1] == 'u')
	printf("Unbounded Tape Results:\n");
    printf("Total Machines = %ld\n", num_machines);
    printf("Total Halting = %ld\n", num_halted);
    printf("Total Infinite = %ld\n", num_infinite);
    printf("Total Crashed = %ld\n", num_crashed);
    printf("Max ones written %d\n", max_ones);
}

LIST *build_move_list(int state, char tape_symbol, int num_states)
/*-----------------------------------------------------------------------------+
| REQUIRES: move_list has been initialized                                     |
| MODIFIES: move_list                                                          |
| EFFECTS:  builds a move list for the state using tape_sym                    |
| RETURNS:  a pointer to move_list                                             |
+-----------------------------------------------------------------------------*/
{
    register int i, j, k;
    TM_NODE *node;
    LIST *move_list;
    extern char tape_symbols[MAX_TAPE_SYM];

    move_list = create_list();
    for (i = 0; i <= MAX_STATES - 1; i++)
    {
	for (j = 1; j <= MAX_TAPE_SYM; j++)
	{
	    for (k = -1; k <= 1; k++)	/* -1 and +1 left and right */
	    {
		if ((node = (TM_NODE *) malloc(sizeof(TM_NODE))) == NULL)
		{
		    fprintf(stderr, "tm - malloc failed - halting\n");
		    exit(1);
		}
		node->state = state;
		node->tape_symbol = tape_symbol;
		node->move_to = i;
		node->write_symbol = tape_symbols[j - 1];
		node->move_dir = k;
		move_list = insert_at_end(move_list, sizeof(TM_NODE), node);
	    }
	}
    }
    return move_list;
}

void run_unbounded(TM_NODE * move)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized and build_move_list has been run         |
| MODIFIES: nothing                                                            |
| EFFECTS:  runs the turing machine which starts with the setup pointed to by  |
|           move and uses an unbounded tape                                    |
| RETURNS:  nothing                                                            |
+-----------------------------------------------------------------------------*/
{
    extern LIST *q00, *q01, *q10, *q11;
    extern long int num_halted, num_infinite;
    extern int max_ones, num_ones, num_moves, tape_pos;
    extern char tape[MAX_TAPE_LENGTH];

    num_moves++;
    if (num_moves <= INFINITE_AT)
    {
	if ((tape[tape_pos] == '0') && (((char) move->write_symbol) == '1'))
	    num_ones++;
	if ((tape[tape_pos] == '1') && (((char) move->write_symbol) == '0'))
	    num_ones--;

	tape[tape_pos] = (char) move->write_symbol;

	tape_pos = tape_pos + move->move_dir;

	if (move->move_to == 0)
	{
	    if (tape[tape_pos] == '0')
		run_unbounded((TM_NODE *) node_item(q00));
	    else
		run_unbounded((TM_NODE *) node_item(q01));
	}
	else if (move->move_to == 1)
	{
	    if (tape[tape_pos] == '0')
		run_unbounded((TM_NODE *) node_item(q10));
	    else
		run_unbounded((TM_NODE *) node_item(q11));
	}
	else
	{
	    if (num_ones > max_ones)
		max_ones = num_ones;
	    num_halted++;
	}
    }
    else
	num_infinite++;
}

void run_bounded(TM_NODE * move)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized and build_move_list has been run         |
| MODIFIES: nothing                                                            |
| EFFECTS:  runs the turing machine which starts with the setup pointed to by  |
|           move and uses a bounded tape                                       |
| RETURNS:  nothing                                                            |
+-----------------------------------------------------------------------------*/
{
    extern LIST *q00, *q01, *q10, *q11;
    extern long int num_crashed, num_halted, num_infinite;
    extern int max_ones, num_ones, num_moves, tape_pos;
    extern char tape[MAX_TAPE_LENGTH];

    num_moves++;
    if ((num_moves < INFINITE_AT) && (tape_pos > 0))
    {
	if ((tape[tape_pos] == '0') && (((char) move->write_symbol) == '1'))
	    num_ones++;
	if ((tape[tape_pos] == '1') && (((char) move->write_symbol) == '0'))
	    num_ones--;

	tape[tape_pos] = (char) move->write_symbol;

	tape_pos = tape_pos + move->move_dir;

	if (move->move_to == 0)
	{
	    if (tape[tape_pos] == '0')
		run_bounded((TM_NODE *) node_item(q00));
	    else
		run_bounded((TM_NODE *) node_item(q01));
	}
	else if (move->move_to == 1)
	{
	    if (tape[tape_pos] == '0')
		run_bounded((TM_NODE *) node_item(q10));
	    else
		run_bounded((TM_NODE *) node_item(q11));
	}
	else if (tape_pos > 0)
	{
	    if (num_ones > max_ones)
		max_ones = num_ones;
	    num_halted++;
	}
        else num_crashed++;
    }
    else if (num_moves == INFINITE_AT)
	num_infinite++;
    else
	num_crashed++;
}
