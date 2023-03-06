/*----------------------------------------------------------------------------+
| Project: ASMX16.C                                                           |
| For: CS374                                                                  |
| Date: 28 April 1994                                                         |
| Authors	Chris Tjon, Jaime Salas Manzano, Kris Ottem, Mark Howatt      |
|                * with contributions from Russ Leitzen                       |
+-----------------------------------------------------------------------------*/

#include "tables.h"
#include "standard.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int error_count = 0;		/* # of assembly errors  */

main(int argc, char *argv[])
{
    char src_file[20] = "",		/* source file name     */
         file_name[20] = "",		/* file name w/o ext    */
         listing_file_name[20] = "",	/* list file name       */
         object_file_name[20] = "";	/* object file name     */
    FILE *src_file_ptr,			/* source file FILE ptr */
        *object_file_ptr,		/* object file FILE ptr */
        *listing_file_ptr;		/* list file FILE ptr   */
    char buffer[80] = "",		/* array for input line */
         cbuffer[80] = "";		/* array for input line w/o comment */
    char tmps[MAX_CHARS_PER_LINE];
    char temp[20] = "", temp1[20] = "", temp2[60] = "";
    char c;
    char *type;
    int LC;				/* Location Counter */
    int i, j, k, z;
    int found = 0, scindex, check;
    int line_count;		/* line# in listing file */
    int save_line_count;
    int instruction_length;
    int procedure_flag = 0;
    int program_flag = 0;
    struct symbol_entry *wptr;
    struct line_info larr[80];	/* array of line info   */

    if (argc == 1)
    {
	errmsg(stderr, ERR_NO_ARGUMENT, NULL);
	exit(-1);
    }
    else
    {
	strcpy(src_file, argv[1]);
	if ((z = loc_chr_str(src_file, '.')) < strlen(src_file))
	{
	    memcpy(file_name, src_file, z);
	    strcat(file_name, '\0');
	}
	else
	{
	    strcpy(file_name, src_file);
	    strcat(src_file, ".xas");
	}

	if ((src_file_ptr = fopen(src_file, "r")) == NULL)
	{
	    errmsg(stderr, ERR_FILE_OPENING, src_file);
	    exit(-1);
	}
    }


    strcpy(object_file_name, file_name);
    strcat(object_file_name, ".xob");
    strcpy(listing_file_name, file_name);
    strcat(listing_file_name, ".xlt");

    if ((listing_file_ptr = fopen(listing_file_name, "w")) == NULL)
    {
	errmsg(stderr, ERR_FILE_OPENING, listing_file_name);
	exit(-1);
    }


    /*----------------------------------------------------------------------------
    					Pass 1
    ----------------------------------------------------------------------------*/
    LC = 0;
    while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
    {
    }
    sscanf(buffer, "%s", tmps);
    if (strcmp(tmps, DIR_UNIT))
	errmsg(stderr, ERR_DIRECTIVE_MISSING, DIR_UNIT);

    while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
    {
    }
    sscanf(buffer, "%s %s %s", tmps, temp1, temp2);

    while (!strcmp(tmps, DIR_EXTERNAL))
    {
	wptr = (struct symbol_entry *) malloc(sizeof(struct symbol_entry));
	add_symbol_entry(wptr, temp1, TYPE_EXTERNAL, "", 0xFFFF);
	while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
	{
	}
	sscanf(buffer, "%s %s %s", tmps, temp1, temp2);
    }

    while (!strcmp(tmps, DIR_PUBLIC))
    {
	wptr = (struct symbol_entry *) malloc(sizeof(struct symbol_entry));
	add_symbol_entry(wptr, temp1, TYPE_PUBLIC, "", 0xFFFF);
	while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
	{
	}
	sscanf(buffer, "%s %s %s", tmps, temp1, temp2);
    }

    if (strcmp(tmps, DIR_PROCEDURE) == 0)
	procedure_flag = 1;
    else
    if (strcmp(temp1, DIR_EQU) == 0)
    {
	wptr = (struct symbol_entry *) malloc(sizeof(struct symbol_entry));
	add_symbol_entry(wptr, tmps, TYPE_NONE, "", get_nbr(temp2), 0);

    }
    else
    if (strcmp(tmps, DIR_ORG) == 0)
    {
	LC = get_nbr(temp1);
    }

    else
    if (strcmp(tmps, DIR_PROGRAM))
	errmsg(stderr, ERR_DIRECTIVE_MISSING, DIR_PROGRAM);
    else
	program_flag = 1;


    for (;;)
    {
	while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
	{
	    strcpy(buffer, "");
	}
	if (c == EOF)
	{
	    errmsg(stderr, ERR_END_OF_FILE, NULL);
	    exit(-1);
	}
	if ((scindex = loc_chr_str(buffer, ';')))
	{
	    strncpy(cbuffer, buffer, scindex);
	}
	else
	{
	    strcpy(cbuffer, buffer);
	}

	sscanf(cbuffer, "%s %s %s ", temp, temp1, temp2);

	if (strcmp(temp, DIR_PROGRAM) == 0)
	{
	    program_flag = 1;
	    found = 1;
	}
	else
	if (strcmp(temp1, DIR_EQU) == 0)
	{
	    wptr = (struct symbol_entry *) malloc(sizeof(struct symbol_entry));
	    add_symbol_entry(wptr, temp, TYPE_NONE, "", get_nbr(temp2), 0);
	}
	else
	if (strcmp(temp, DIR_ORG) == 0)
	{
	    LC = get_nbr(temp1);
	}
	else
	if (strcmp(temp, DIR_PROCEDURE) == 0)
	{
	    found = 1;
	    procedure_flag = 1;
	}
	else
	if (!program_flag)
	{
	    if (!procedure_flag)
		break;
	}

	if ((strcmp(temp1, DIR_DB) == 0) || (strcmp(temp1, DIR_DH) == 0) || (strcmp(temp1, DIR_DW) == 0) || (strcmp(temp1, DIR_DD) == 0))
	{
	    type = "CONSTANT";
	    for (wptr = &symbol_anchor; wptr != NULL_PTR && strcmp(temp, wptr->name); wptr = wptr->next);
	    if (wptr->type == TYPE_PUBLIC)
	    {
		wptr->value = wptr->location = LC;
		LC += get_data_size(temp1, temp2, larr, &line_count);

	    }
	    else
	    {
		wptr = (struct symbol_entry *) malloc(sizeof(struct symbol_entry));
		add_symbol_entry(wptr, temp, TYPE_INTERNAL, type, LC, LC);
		LC += get_data_size(temp1, temp2, larr, &line_count);
	    }
	}
	else
	if (strcmp(temp1, DIR_EQU) == 0)
	{
	    wptr = (struct symbol_entry *) malloc(sizeof(struct symbol_entry));
	    add_symbol_entry(wptr, temp, TYPE_NONE, "", get_nbr(temp2), 0);
	}

	else
	if (strcmp(temp, DIR_ORG) == 0)
	{
	    LC = get_nbr(temp1);
	}
	else
	if (strcmp(temp, DIR_ENDP) == 0)
	{
	    if (procedure_flag)
		procedure_flag = 0;
	    /* do nothing */
	}
	else
	if (strcmp(temp, DIR_END) == 0)
	{
	    /* goto PASS 2 */
	    break;
	}
	else
	{
	    /* see if it is a command and increment */
	    type = "LABEL";
	    if (!strcmp(temp, "RETN"))
	    {
		LC += 2;
		found = 1;
	    }
	    else
	    {
		for (i = 0; opcode_table[i].name[0] != NULL_CHAR && !found; i++)
		{
		    if (strcmp(temp, opcode_table[i].name) == 0)
		    {
			found = 1;
			LC = LC + opcode_table[i].length;
		    }
		}
		for (i = 0; opcode_table[i].name[0] != NULL_CHAR && !found; i++)
		{
		    if (strcmp(temp1, opcode_table[i].name) == 0)
		    {
			found = 1;
			wptr = (struct symbol_entry *) malloc(sizeof(struct symbol_entry));
			add_symbol_entry(wptr, temp, TYPE_INTERNAL, type, 0, LC);
			LC = LC + opcode_table[i].length;
		    }
		}
	    }
	    if (!found)
	    {
		printf("%s %s\n", temp, temp1);
		printf("ERR_INVALID_DIRECTIVE\n");
	    }
	    found = 0;

	}
	strcpy(temp, "");
	strcpy(temp1, "");
	strcpy(temp2, "");
    }
    fclose(src_file_ptr);


    /*---------------------------------------------------------------------------
    					Pass 2
    ----------------------------------------------------------------------------*/
    if ((src_file_ptr = fopen(src_file, "r")) == NULL)
    {
	errmsg(stderr, ERR_FILE_OPENING, src_file);
	exit(-1);
    }

    if ((object_file_ptr = fopen(object_file_name, "w")) == NULL)
    {
	errmsg(stderr, ERR_FILE_OPENING, object_file_name);
	exit(-1);
    }

    LC = 0;
    line_count = 0;
    while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
    {
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
	strcpy(buffer, "");
    }
    sscanf(buffer, "%s", tmps);
    if (strcmp(tmps, DIR_UNIT))
	errmsg(stderr, ERR_DIRECTIVE_MISSING, DIR_UNIT);
    else
    {
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
	strcpy(buffer, "");
    }

    while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
    {
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
	strcpy(buffer, "");
    }
    sscanf(buffer, "%s %s %s", tmps, temp1, temp2);

    while (!strcmp(tmps, DIR_EXTERNAL))
    {
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
	strcpy(buffer, "");
	while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
	{
	    larr[++line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);
	    strcpy(buffer, "");
	}
	sscanf(buffer, "%s %s %s", tmps, temp1, temp2);
    }

    while (!strcmp(tmps, DIR_PUBLIC))
    {
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
	strcpy(buffer, "");
	while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
	{
	    larr[++line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);
	    strcpy(buffer, "");
	}
	sscanf(buffer, "%s %s %s", tmps, temp1, temp2);
    }


    if (strcmp(tmps, DIR_PROCEDURE) == 0)
    {
	procedure_flag = 1;
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
	strcpy(buffer, "");
    }
    else
    if (strcmp(temp1, DIR_EQU) == 0)
    {
	for (wptr = &symbol_anchor; wptr != NULL_PTR && strcmp(tmps, wptr->name); wptr = wptr->next)
	{
	}
	if (!strcmp(tmps, wptr->name))
	{
	    if (wptr->used == TRUE)
	    {
		larr[line_count].error = DUPLICATE_DEF_ERR;
		error_count++;
	    }
	    else
		wptr->used = TRUE;
	}
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
    }
    else
    if (strcmp(tmps, DIR_ORG) == 0)
    {
	LC = get_nbr(temp1);
	larr[++line_count].addr = ORG_LINE;
	larr[line_count].prefix = 0xC000 | (LC / 2);
    }

    else
    if (strcmp(tmps, DIR_PROGRAM))
	errmsg(stderr, ERR_DIRECTIVE_MISSING, DIR_PROGRAM);
    else
    {
	larr[++line_count].addr = COMMENT_LINE;
	strcpy(larr[line_count].extra, buffer);
	strcpy(buffer, "");
    }

    for (;;)
    {
	while ((c = mygetline(src_file_ptr, buffer)) != EOF && (c == ';' || c == '\n'))
	{
	    larr[++line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);
	    strcpy(buffer, "");
	}

	if ((scindex = loc_chr_str(buffer, ';')))
	{
	    strncpy(cbuffer, buffer, scindex);
	}
	else
	{
	    strcpy(cbuffer, buffer);
	}
	larr[++line_count].addr = LC;
	larr[line_count].error = NO_ERROR;
	larr[line_count].opcode = BLANK_NBR;
	larr[line_count].oper1 = BLANK_NBR;
	larr[line_count].oper2 = BLANK_NBR;
	larr[line_count].r = ' ';
	larr[line_count].n = ' ';
	larr[line_count].prefix = BLANK_NBR;
	strcpy(larr[line_count].extra, buffer);

	sscanf(cbuffer, "%s %s %s ", temp, temp1, temp2);

	if (strcmp(temp, DIR_PROGRAM) == 0)
	{
	    program_flag = 1;
	    found = 1;
	    larr[line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);
	    strcpy(buffer, "");
	}
	else
	if (strcmp(temp, DIR_PROCEDURE) == 0)
	{
	    procedure_flag = 1;
	    found = 1;
	    larr[line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);
	    strcpy(buffer, "");
	}
	else
	if (!program_flag)
	{
	    if (!procedure_flag)
		break;
	}


	if ((strcmp(temp1, DIR_DB) == 0) || (strcmp(temp1, DIR_DH) == 0) || (strcmp(temp1, DIR_DW) == 0) || (strcmp(temp1, DIR_DD) == 0))
	{
	    for (wptr = &symbol_anchor; wptr != NULL_PTR && strcmp(temp, wptr->name); wptr = wptr->next)
	    {
	    }
	    if (!strcmp(temp, wptr->name))
	    {
		if (wptr->used == TRUE)
		{
		    larr[line_count].error = DUPLICATE_DEF_ERR;
		    error_count++;
		}
		else
		    wptr->used = TRUE;
	    }
	    save_line_count = line_count;
	    j = get_dsize(temp1, temp2, &larr[line_count], &line_count);
	    LC += j;
	    larr[save_line_count].prefix = 0x8000 | (j / 2);
	}
	else
	if (strcmp(temp1, DIR_EQU) == 0)
	{
	    for (wptr = &symbol_anchor; wptr != NULL_PTR && strcmp(temp, wptr->name); wptr = wptr->next);
	    if (!strcmp(temp, wptr->name))
	    {
		if (wptr->used == TRUE)
		{
		    larr[line_count].error = DUPLICATE_DEF_ERR;
		    error_count++;
		}
		else
		    wptr->used = TRUE;
	    }

	    larr[line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);
	}
	else
	if (strcmp(temp, DIR_ORG) == 0)
	{
	    LC = get_nbr(temp1);
	    larr[line_count].addr = ORG_LINE;
	    larr[line_count].prefix = 0xC000 | (LC / 2);
	}
	else
	if (strcmp(temp, DIR_ENDP) == 0)
	{
	    /* do nothing */
	    if (procedure_flag)
		procedure_flag = 0;
	    larr[line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);

	}
	else
	if (strcmp(temp, DIR_END) == 0)
	{
	    /* ASSEMBLY IS COMPLETE */
	    larr[line_count].addr = COMMENT_LINE;
	    strcpy(larr[line_count].extra, buffer);
	    break;
	}
	else
	{
	    /* see if it is a command and increment */
	    for (i = 0; opcode_table[i].name[0] != NULL_CHAR && !found; i++)
	    {
		if (strcmp(temp, opcode_table[i].name) == 0)
		{
		    found = 1;
		}
	    }
	    for (i = 0; opcode_table[i].name[0] != NULL_CHAR && !found; i++)
	    {
		if (strcmp(temp1, opcode_table[i].name) == 0)
		{
		    found = 1;
		    strcpy(buffer, temp1);
		    strcat(buffer, "  ");
		    strcat(buffer, temp2);
		}
	    }
	    if (!found)
	    {
		errmsg(stderr, ERR_INVALID_DIRECTIVE, NULL);
	    }
	    else
	    if (!strcmp(temp, DIR_PROGRAM) || !strcmp(temp, DIR_PROCEDURE))
	    {
	    }
	    else
	    {
		get_ops(buffer, &larr[line_count]);
		instruction_length = 2;
		if (larr[line_count].oper1 != BLANK_NBR)
		    instruction_length += 2;
		if (larr[line_count].oper2 != BLANK_NBR)
		    instruction_length += 2;
		LC += instruction_length;
		larr[line_count].prefix |= ((instruction_length / 2) << 9);
		larr[line_count].prefix |= line_count;
	    }
	    found = 0;
	}
	strcpy(buffer, "");
	strcpy(temp, "");
	strcpy(temp1, "");
	strcpy(temp2, "");
    }
    fclose(src_file_ptr);
    print_listing(listing_file_ptr, line_count, larr, LC);
    print_symbol_table(listing_file_ptr);
    fprintf(listing_file_ptr, "\n		ASSEMBLY COMPLETE	");
    fprintf(listing_file_ptr, "ERROR COUNT = %d\n", error_count);
    printf("\n		ASSEMBLY COMPLETE	");
    printf("ERROR COUNT = %d\n", error_count);
    fclose(listing_file_ptr);
    if (!error_count)
	print_object(object_file_ptr, line_count, larr);
    fclose(object_file_ptr);
    return (0);
}

/*----------------------------------------------------------------------------
	Name:	  loc_chr_str
	Purpose:  locates the position of a character in a string
	Params:	  s = string, c = character
	Returns:  position of c in s or NULL_PTR
------------------------------------------------------------------------------*/
int loc_chr_str(char s[MAX_CHARS_PER_LINE], int c)
{
    int i;
    for (i = 0; c != '\0' && i != MAX_CHARS_PER_LINE; i++)
    {
	if (s[i] == c)
	    return (i);
    }
    return (NULL_PTR);
}

/*----------------------------------------------------------------------------
	Name:	  mygetline
	Purpose:  read 1 line from the input file
	Params:   fp = FILE pointer and buf = array of characters
	Returns:  first character in input line and first input line stored in buf
------------------------------------------------------------------------------*/
int mygetline(FILE * fp, char *buf)
{
    char c;
    int i;

    if ((c = getc(fp)) == EOF)
	return (EOF);
    for (i = 0; c != '\n' && i != MAX_CHARS_PER_LINE; i++)
    {
	buf[i] = c;
	c = getc(fp);
    }
    buf[i] = '\0';
    return (buf[0]);
}

/*----------------------------------------------------------------------------
	Name:     add_symbol_entry
	Purpose:  add symbol and its associated parameters to the symbol table
	Params:   symbol_entry_ptr = pointer to symbol_table entry
		  label = string,  type = integer (e.g. TYPE_INTERNAL)
		  type1 = string (e.g CONSTANT or LABEL)
		  value = integer,  LC = integer
	Returns:  N/A
------------------------------------------------------------------------------*/
int add_symbol_entry(struct symbol_entry * symbol_entry_ptr, char *label, int type, char *type1, int value, int location)
{
        symbol_entry_ptr->next = NULL_PTR;
    symbol_entry_ptr->name = (char *) malloc(strlen(label) + 1);
    strcpy(symbol_entry_ptr->name, label);
    symbol_entry_ptr->value = value;
    symbol_entry_ptr->type = type;
    symbol_entry_ptr->type1 = (char *) malloc(strlen(type1) + 1);
    strcpy(symbol_entry_ptr->type1, type1);
    symbol_entry_ptr->location = location;
    symbol_entry_ptr->used = FALSE;
    add_element(symbol_entry_ptr, &symbol_anchor);

    return (0);
}

struct basic_struct
{
    struct basic_struct *next;
};

/*----------------------------------------------------------------------------
	Name:     add_element
	Purpose:  add symbol_entry to actual symbol_table structure
	Params:   ptr1 = pointer to symbol_entry to add to symbol table
		  ptr2 = pointer to actual symbol_table
	Returns:  N/A
------------------------------------------------------------------------------*/
int add_element(struct symbol_entry * ptr1, struct symbol_entry * ptr2)
{
    struct symbol_entry *ptr3;

    if (ptr2->next == NULL_PTR)
    {
	ptr2->next = ptr1;
    }
    else
    {
	for (ptr3 = ptr2->next; ptr3->next != NULL_PTR; ptr3 = ptr3->next)
	{
	}
	ptr3->next = ptr1;
    }

    return (0);
}

/*----------------------------------------------------------------------------
	Name:     power
	Purpose:  calculates the value of a number raised to power (e.g. 2^2=4
	Params:   nbr = integer, pwr = integer
	Returns:  result of number(nbr) raiser to power(pwr)
------------------------------------------------------------------------------*/
int power(int nbr, int pwr)
{
    int i, value;
    for (i = 1, value = nbr; i < pwr; i++)
	value = value * nbr;
    return (value);
}

/*----------------------------------------------------------------------------
	Name:	  get_nbr
	Purpose:  converts a string into a number.
	Params:	  s = string  (eg. 1000)  (eg. 1000H)
	Returns:  Value of the string.
------------------------------------------------------------------------------*/
int get_nbr(char *s)
{
    int i, value;
    if (s[strlen(s) - 1] == 'H' || s[strlen(s) - 1] == 'h')	/* if hex */
	sscanf(s, "%x", &value);
    else
    if (s[strlen(s) - 1] == 'B' || s[strlen(s) - 1] == 'b')	/* if binary */
    {
	if (s[strlen(s) - 2] == '1')
	    value = 1;
	else
	    value = 0;
	for (i = 1; i < (strlen(s) - 1); i++)
	{
	    if (s[strlen(s) - 2 - i] == '1')
		value += power(2, i);
	}
    }
    else
	sscanf(s, "%d", &value);
    return (value);
}


/*------------------------------------------------------------------------------
	Name:	  get_reg_nbr
	Purpose:  convert the name of a register into a actual number.
	Params:	  buf = name of a register.
	Returns:  Register number.
------------------------------------------------------------------------------*/
int get_reg_nbr(char *buf)
{
    if  (!strcmp(buf, "R0"))
	    return (REG_R0);
    if (!strcmp(buf, "R1"))
	return (REG_R1);
    if (!strcmp(buf, "R2"))
	return (REG_R2);
    if (!strcmp(buf, "R3"))
	return (REG_R3);
    if (!strcmp(buf, "R4"))
	return (REG_R4);
    if (!strcmp(buf, "R5"))
	return (REG_R5);
    if (!strcmp(buf, "SP"))
	return (REG_SP);
    if (!strcmp(buf, "PC"))
	return (REG_PC);
    return (REG_ERR);
}


/*------------------------------------------------------------------------------
	Name:	  get_data_size
	Purpose:  convert the name of a register into a actual number.
	Params:	  dir = directive
		  s = copy of current line starting after the directive.
		  lptr = pointer to the array element of the current line.
		  LC = location counter.
	Returns:  number of bytes that are used/needed.
------------------------------------------------------------------------------*/
int get_data_size(char *dir, char *s, struct line_info * lptr, int *LC)
{
    int nbr, mult;
    char c;
    char buf[MAX_CHARS_PER_LINE];
    char buf2[MAX_CHARS_PER_LINE];
    int bcnt;
    int i, j, cnt;
    int tmpl, tmpl2;

    switch (dir[1])
    {
    case 'B':
	mult = 1;
	break;
    case 'H':
	mult = 2;
	break;
    case 'W':
	mult = 4;
	break;
    case 'D':
	mult = 8;
	break;
    }
    /*-------------------------------------------------------------------
		Reserve multiple Bytes, Halfwords, Words, and Double Words
	-------------------------------------------------------------------*/
    if (isdigit(s[0]))
    {
	nbr = get_nbr(s);
	if (((nbr * mult) % 2) == 1)
	    return (nbr * mult + 1);
	else
	    return (nbr * mult);
    }
    /*----------------------------------------------------------------------
		Store a value in memory
	----------------------------------------------------------------------*/
    if (s[0] == '(')
    {
	/*--------------------------------------------------------------
			count the number of assignments and store them
		--------------------------------------------------------------*/
	for (cnt = 0, i = 1; s[i] != ')'; i++)
	{
	    if (s[i] == ',')
		cnt++;
	}
	for (bcnt = 0, i = 0; i <= cnt; i++)
	{
	    strcpy(buf, &s[1]);
	    strcpy(s, buf);
	    for (j = 0; s[j] != ',' && s[j] != ')'; buf[j] = s[j++]);
	    buf[j] = '\0';
	    strcpy(buf2, &s[j]);
	    strcpy(s, buf2);
	    if (buf[strlen(buf) - 1] == 'H' || buf[strlen(buf) - 1] == 'h')
	    {
		if (strlen(buf) > 9)
		{
		    sscanf(buf, "%x", &tmpl);
		    buf[strlen(buf) - 9] = '\0';
		    sscanf(buf, "%x", &tmpl2);
		}
		else
		    sscanf(buf, "%x", &tmpl);
	    }
	    else
	    {
		if (strlen(buf) > 8)
		{
		    sscanf(buf, "%d", &tmpl);
		    buf[strlen(buf) - 8] = '\0';
		    sscanf(buf, "%d", &tmpl2);
		}
		else
		    sscanf(buf, "%d", &tmpl);
	    }
	    bcnt += mult;
	}
	if (bcnt % 2)
	    return (bcnt + 1);
	else
	    return (bcnt);
    }
}


/*------------------------------------------------------------------------------
	Name:	  get_dsize
	Purpose:  convert the name of a register into a actual number.
	Params:	  dir = directive
		  s = copy of current line starting after the directive.
		  lptr = pointer to the array element of the current line.
		  LC = location counter.
	Returns:  number of bytes that are used/needed.
------------------------------------------------------------------------------*/
int get_dsize(char *dir, char *s, struct line_info * lptr, int *LC)
{
    int nbr, mult;
    char c;
    char buf[MAX_CHARS_PER_LINE];
    char buf2[MAX_CHARS_PER_LINE];
    int bcnt;
    int i, j, cnt;
    int tmpl, tmpl2;

    switch (dir[1])
    {
    case 'B':
	mult = 1;
	break;
    case 'H':
	mult = 2;
	break;
    case 'W':
	mult = 4;
	break;
    case 'D':
	mult = 8;
	break;
    }
    /*-------------------------------------------------------------------
		Reserve multiple Bytes, Halfwords, Words, and Double Words
	-------------------------------------------------------------------*/
    if (isdigit(s[0]))
    {
	nbr = get_nbr(s);
	if (((nbr * mult) % 2) == 1)
	    return (nbr * mult + 1);
	else
	    return (nbr * mult);
    }
    /*----------------------------------------------------------------------
		Store a value in memory
	----------------------------------------------------------------------*/
    if (s[0] == '(')
    {
	lptr++;
	(*LC)++;
	lptr->oper1 = BLANK_NBR;
	lptr->oper2 = BLANK_NBR;
	lptr->r = BLANK_NBR;
	/*--------------------------------------------------------------
			count the number of assignments and store them
		--------------------------------------------------------------*/
	for (cnt = 0, i = 1; s[i] != ')'; i++)
	{
	    if (s[i] == ',')
		cnt++;
	}
	for (bcnt = 0, i = 0; i <= cnt; i++)
	{
	    strcpy(buf, &s[1]);
	    strcpy(s, buf);
	    for (j = 0; s[j] != ',' && s[j] != ')'; j++)
		buf[j] = s[j];
	    buf[j] = '\0';
	    strcpy(buf2, &s[j]);
	    strcpy(s, buf2);
	    if (buf[strlen(buf) - 1] == 'H' || buf[strlen(buf) - 1] == 'h')
	    {
		if (strlen(buf) > 9)
		{
		    sscanf(buf, "%x", &tmpl);
		    buf[strlen(buf) - 9] = '\0';
		    sscanf(buf, "%x", &tmpl2);
		}
		else
		    sscanf(buf, "%x", &tmpl);
	    }
	    else
	    {
		if (strlen(buf) > 8)
		{
		    sscanf(buf, "%d", &tmpl);
		    buf[strlen(buf) - 8] = '\0';
		    sscanf(buf, "%d", &tmpl2);
		}
		else
		    sscanf(buf, "%d", &tmpl);
	    }
	    bcnt += mult;
	    /*------------------------------------------------------
				store numbers in the line array.
			------------------------------------------------------*/
	    switch (mult)
	    {
	    case 1:
		if ((bcnt % 8) == 0)
		    lptr->r |= (tmpl << 8);
		else
		if ((bcnt % 8) == 7)
		    lptr->r = tmpl;
		else
		if ((bcnt % 8) == 6)
		    lptr->oper2 |= (tmpl << 8);
		else
		if ((bcnt % 8) == 5)
		    lptr->oper2 = tmpl;
		else
		if ((bcnt % 8) == 4)
		    lptr->oper1 |= (tmpl << 8);
		else
		if ((bcnt % 8) == 3)
		    lptr->oper1 = tmpl;
		else
		if ((bcnt % 8) == 2)
		    lptr->opcode |= (tmpl << 8);
		else
		if ((bcnt % 8) == 1)
		    lptr->opcode = tmpl;
		break;
	    case 2:
		if ((bcnt % 8) == 0)
		    lptr->r = tmpl;
		else
		if ((bcnt % 8) == 6)
		    lptr->oper2 = tmpl;
		else
		if ((bcnt % 8) == 4)
		    lptr->oper1 = tmpl;
		else
		if ((bcnt % 8) == 2)
		    lptr->opcode = tmpl;
		break;
	    case 4:
		if ((bcnt % 8) == 0)
		{
		    lptr->r = (tmpl >> 16);
		    lptr->oper2 = (tmpl & 0xFFFF);
		}
		else
		if ((bcnt % 8) == 4)
		{
		    lptr->oper1 = (tmpl >> 16);
		    lptr->opcode = (tmpl & 0xFFFF);
		}
		break;
	    case 8:
		lptr->opcode = (tmpl & 0xFFFF);
		tmpl >>= 16;
		lptr->oper1 = (tmpl & 0xFFFF);
		lptr->oper2 = (tmpl2 & 0xFFFF);
		tmpl2 >>= 16;
		lptr->r = (tmpl2 & 0xFFFF);
		break;
	    }
	    if ((bcnt % 8) > 4 || (bcnt % 8) == 0)
		lptr->addr = DOUBLE_LINE;
	    else
	    if ((bcnt % 8) > 2)
		lptr->addr = WORD_LINE;
	    else
		lptr->addr = HALFWORD_LINE;
	    if (!(bcnt % 8) && (i < cnt))
	    {
		lptr++;
		(*LC)++;
		lptr->oper1 = BLANK_NBR;
		lptr->oper2 = BLANK_NBR;
		lptr->r = BLANK_NBR;
	    }
	}
	tmpl = 0;
	tmpl2 = 0;
	if (bcnt % 2)
	    return (bcnt + 1);
	else
	    return (bcnt);
    }
}


/*------------------------------------------------------------------------------
	Name:	  get_ops
	Purpose:  translates the operands of an instruction and records all the
		  needed information into the corresponding structure in an
		  array of line info.
	Inputs:	  buf = copy of the current line starting at the opcode.
		  lptr = pointer to the line info for the current line.
	Returns:  Nothing directly, but saves needed information into the
		  structure pointed to by lptr.
------------------------------------------------------------------------------*/
get_ops(char *buf, struct line_info * lptr)
{
    int i;
    char instruction[MAX_CHARS_PER_LINE];	/* current instruction */
    int opcodelen;		/* length of current opcode */
    char buf2[MAX_CHARS_PER_LINE];	/* temporary string */
    char tmps[MAX_CHARS_PER_LINE];	/* temporary string */
    char tmps1[MAX_CHARS_PER_LINE];
    char tmps2[MAX_CHARS_PER_LINE];
    char *oper1str, *oper2str;	/* the operands (1st and 2nd) */
    struct symbol_entry *wptr;	/* work ptr to scan the symbol table */
    int offset;
    int tmpreg;
    int c;
    int bracketflag1, plusflag1, minusflag1;
    int bracketflag2, plusflag2, minusflag2;


    /*----------------------------------------------------------------------
		Initialize the current line structure
	----------------------------------------------------------------------*/
    lptr->oper1 = lptr->oper2 = 0;
    lptr->r = ' ';
    lptr->prefix = 0x0000;
    /*----------------------------------------------------------------------
		Find the current instruction in the symbol table and set the
		initial opcode value.
	----------------------------------------------------------------------*/
    sscanf(buf, "%s", instruction);
    for (i = 0; strcmp(instruction, opcode_table[i].name); i++);
    lptr->opcode = opcode_table[i].value;

    lptr->opcode <<= (16 - (opcodelen = opcode_table[i].length));
    sscanf(buf, "%s %s", tmps, tmps1);
    strcpy(tmps, tmps1);
    if (tmps[0] == '\0' || tmps[0] == ';')	/* if no operands */
    {
	lptr->oper1 = BLANK_NBR;
	lptr->oper2 = BLANK_NBR;
	return;
    }
    /*----------------------------------------------------------------------
		Find the operands
	----------------------------------------------------------------------*/
    for (i = 0; i < strlen(tmps) && tmps[i] != ','; i++);
    if (i == strlen(tmps))	/* if only one operand */
    {
	oper1str = (char *) malloc(strlen(tmps) + 1);
	strcpy(oper1str, tmps);
	lptr->oper2 = BLANK_NBR;
    }
    else			/* else two operands */
    {
	oper1str = (char *) malloc(i + 1);
	oper2str = (char *) malloc(strlen(tmps) - i);
	strcpy(buf2, tmps);
	buf2[i] = '\0';
	strcpy(oper1str, buf2);
	strcpy(oper2str, &tmps[i + 1]);
    }
    /*----------------------------------------------------------------------
		Scan the operands for a [,-,+
	----------------------------------------------------------------------*/
    bracketflag1 = FALSE;
    plusflag1 = FALSE;
    minusflag1 = FALSE;
    for (i = 0; i < strlen(oper1str); i++)
    {
	if (oper1str[i] == '[')
	    bracketflag1 = TRUE;
	if (oper1str[i] == '+')
	    plusflag1 = TRUE;
	if (oper1str[i] == '-')
	    minusflag1 = TRUE;
    }
    bracketflag2 = FALSE;
    plusflag2 = FALSE;
    minusflag2 = FALSE;
    for (i = 0; i < strlen(oper2str); i++)
    {
	if (oper2str[i] == '[')
	    bracketflag2 = TRUE;
	if (oper2str[i] == '+')
	    plusflag2 = TRUE;
	if (oper2str[i] == '-')
	    minusflag2 = TRUE;
    }

    /*----------------------------------------------------------------------
		Find the mode of the first operand
	----------------------------------------------------------------------*/
    if ((((oper1str[0] == 'R') && (oper1str[1] >= '0' && oper1str[1] <= '5')) ||
	 (oper1str[0] == 'S' && oper1str[1] == 'P') ||
	 (oper1str[0] == 'P' && oper1str[1] == 'C')) &&
	oper1str[2] == '\0')
    {
	lptr->oper1 = BLANK_NBR;
	i = get_reg_nbr(oper1str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 9);
	    i = MODE_REG;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 7:
	    /* should generate an error if not R0 */
	    i = MODE_REG;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG;
	    lptr->opcode |= i;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (oper1str[0] == '#')	/* immediate */
    {
	if (isdigit(oper1str[1]) || oper1str[1] == '-' ||
	    oper1str[1] == '+')
	    lptr->oper1 = get_nbr(&oper1str[1]);
	else
	{
	    for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		 strcmp(&oper1str[1], wptr->name); wptr = wptr->next);
	    if (wptr != NULL_PTR)
		lptr->oper1 = wptr->value;
	}
	switch (opcodelen)
	{
	case 4:
	    i = MODE_IMM6;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 7:
	    i = MODE_IMM3;

	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    /* error - can't have immediate mode */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }

    else
    if (oper1str[0] == '[' && plusflag1 == TRUE)	/* post increment */
    {
	lptr->oper1 = BLANK_NBR;
	strcpy(tmps, &oper1str[1]);
	strcpy(oper1str, tmps);
	oper1str[strlen(oper1str) - 2] = '\0';
	i = get_reg_nbr(oper1str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 9);
	    i = MODE_REG_IND_INC;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 7:
	    /* should generate an error if not R0 */
	    i = MODE_REG_IND_INC;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND_INC;
	    lptr->opcode |= i;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (oper1str[0] == '-' && oper1str[1] == '[')	/* pre-decrement */
    {
	lptr->oper1 = BLANK_NBR;
	strcpy(tmps, &oper1str[2]);
	strcpy(oper1str, tmps);
	oper1str[strlen(oper1str) - 1] = '\0';
	i = get_reg_nbr(oper1str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 9);
	    i = MODE_REG_IND_DEC;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 7:
	    /* should generate an error if not R0 */
	    i = MODE_REG_IND_DEC;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND_DEC;
	    lptr->opcode |= i;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (oper1str[0] == '[')	/* register indirect */
    {
	lptr->oper1 = BLANK_NBR;
	strcpy(tmps, &oper1str[1]);
	strcpy(oper1str, tmps);
	oper1str[strlen(oper1str) - 1] = '\0';
	i = get_reg_nbr(oper1str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 9);
	    i = MODE_REG_IND;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 7:
	    /* should generate an error if not R0 */
	    i = MODE_REG_IND;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND;
	    lptr->opcode |= i;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (bracketflag1 == TRUE)	/* relative */
    {
	for (i = 0; oper1str[i] != '['; i++);
	strcpy(tmps, &oper1str[i + 1]);
	oper1str[i] = '\0';
	tmps[2] = '\0';
	tmpreg = get_reg_nbr(tmps);
	if (plusflag1 == TRUE || minusflag1 == TRUE)
	{
	    for (i = 0; oper1str[i] != '+' && oper1str[i] != '-'; i++);
	    oper1str[i] = ' ';
	    sscanf(oper1str, "%s%s", tmps, tmps2);
	    for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		 strcmp(tmps, wptr->name); wptr = wptr->next);
	    if (wptr != NULL_PTR)
	    {
		offset = wptr->value;
		if (wptr->type == TYPE_NONE)
		    lptr->n = 'N';
		else
		    lptr->r = 'R';
	    }
	    else
	    {
		/* error */
		error_count++;
	    }
	    if (isdigit(tmps2[0]))
	    {
		if (plusflag1 == TRUE)
		    offset += get_nbr(tmps2);
		else
		    offset -= get_nbr(tmps2);
	    }
	    else
	    {
		for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		     strcmp(tmps2, wptr->name); wptr = wptr->next);
		if (wptr != NULL_PTR)
		{
		    if (plusflag1 == TRUE)
			offset += wptr->value;
		    else
			offset -= wptr->value;
		    if (wptr->type == TYPE_NONE)
			lptr->n = 'N';
		    else
			lptr->r = 'R';
		}
		else;		/* error */
	    }
	}
	else
	if (isdigit(oper1str[0]))
	    offset = get_nbr(oper1str);
	else
	{
	    for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		 strcmp(oper1str, wptr->name); wptr = wptr->next);
	    if (wptr != NULL_PTR)
	    {
		offset = wptr->value;
		if (wptr->type == TYPE_NONE)
		    lptr->n = 'N';
		else
		    lptr->r = 'R';
	    }
	    else
	    {
		/* error */
		error_count++;
	    }
	}
	lptr->oper1 = offset;
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (tmpreg <<= 9);
	    i = MODE_REL;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 7:
	    /* should generate an error if not R0 */
	    i = MODE_REL;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    lptr->opcode |= (tmpreg <<= 3);
	    i = MODE_REL;
	    lptr->opcode |= i;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (plusflag1 == TRUE || minusflag1 == TRUE)
    {
	for (i = 0; oper1str[i] != '+' && oper1str[i] != '-'; i++);
	oper1str[i] = ' ';
	sscanf(oper1str, "%s%s", tmps, tmps2);
	for (wptr = &symbol_anchor; wptr != NULL_PTR &&
	     strcmp(tmps, wptr->name); wptr = wptr->next);
	if (wptr != NULL_PTR)
	{
	    offset = wptr->value;
	    if (wptr->type == TYPE_NONE)
		lptr->n = 'N';
	    else
		lptr->r = 'R';
	}
	else
	{
	    /* error */
	    error_count++;
	}
	if (isdigit(tmps2[0]))
	{
	    if (plusflag1 == TRUE)
		offset += get_nbr(tmps2);
	    else
		offset -= get_nbr(tmps2);
	}
	else
	{
	    for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		 strcmp(tmps2, wptr->name); wptr = wptr->next);
	    if (wptr != NULL_PTR)
	    {
		if (plusflag1 == TRUE)
		    offset += wptr->value;
		else
		    offset -= wptr->value;
		if (wptr->type == TYPE_NONE)
		    lptr->n = 'N';
		else
		    lptr->r = 'R';
	    }
	    else
	    {
		/* error */
		error_count++;
	    }
	}
	lptr->oper1 = offset;
	switch (opcodelen)
	{
	case 4:
	    if (!strcmp(instruction, "INPB") ||
		!strcmp(instruction, "INPH"))
	    {
		i = MODE_DIR6_IO;
		lptr->opcode |= (i <<= 6);
	    }
	    else
	    {
		i = MODE_DIR6_MEM;
		lptr->opcode |= (i <<= 6);
	    }
	    break;
	case 7:
	    i = MODE_DIR3;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    /* error - can't have immediate mode */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }


    else
    if (isalpha(oper1str[0]))	/* label,string */
    {
	for (wptr = &symbol_anchor; wptr != NULL_PTR &&
	     strcmp(oper1str, wptr->name); wptr = wptr->next)
	{
	}
	if (wptr != NULL_PTR)
	{
	    switch (wptr->type)
	    {
	    case TYPE_EXTERNAL:
		lptr->prefix |= 0x6000;
		break;
	    case TYPE_INTERNAL:
		lptr->prefix |= 0x4000;
		break;
	    case TYPE_PUBLIC:
		lptr->prefix |= 0x2000;
		break;
	    default:
		lptr->prefix |= 0x0000;
		break;
	    }

	    if (wptr->type == TYPE_NONE)
		lptr->n = 'N';
	    else
		lptr->r = 'R';
	    lptr->oper1 = wptr->value;

	    switch (opcodelen)
	    {
	    case 4:
		if (!strcmp(instruction, "INPB") ||
		    !strcmp(instruction, "INPH"))
		{
		    i = MODE_DIR6_IO;
		    lptr->opcode |= (i <<= 6);
		}
		else
		{
		    i = MODE_DIR6_MEM;
		    lptr->opcode |= (i <<= 6);
		}
		break;
	    case 7:
		i = MODE_DIR3;
		lptr->opcode |= (i <<= 6);
		break;
	    case 10:
		/* error - can't have immediate mode */
		error_count++;
		break;
	    default:
		/* error */
		/* error_count++;  */
		break;
	    }
	}
	else
	{
	    lptr->error = UNDEFINED_SYMBOL;
	    error_count++;
	}
    }
    else
    if (isdigit(oper1str[0]))	/* address,numeric */
    {
	lptr->r = ' ';
	lptr->oper1 = get_nbr(oper1str);
	switch (opcodelen)
	{
	case 4:
	    if (!strcmp(instruction, "INPB") ||
		!strcmp(instruction, "INPH"))
	    {
		i = MODE_DIR6_IO;
		lptr->opcode |= (i <<= 6);
	    }
	    else
	    {
		i = MODE_DIR6_MEM;
		lptr->opcode |= (i <<= 6);
	    }
	    break;
	case 7:
	    i = MODE_DIR3;
	    lptr->opcode |= (i <<= 6);
	    break;
	case 10:
	    /* error - can't have immediate mode */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }

    else;			/* different mode */

    if (lptr->oper2 == BLANK_NBR)	/* if only one free var and return */
    {
	free(oper1str);
	return;
    }
    /*----------------------------------------------------------------------
		Find the mode of the second operand
	----------------------------------------------------------------------*/
    if ((((oper2str[0] == 'R') && (oper2str[1] >= '0' && oper2str[1] <= '5')) ||
	 (oper2str[0] == 'S' && oper2str[1] == 'P') ||
	 (oper2str[0] == 'P' && oper2str[1] == 'C')) &&
	oper2str[2] == '\0')
    {
	lptr->oper2 = BLANK_NBR;
	i = get_reg_nbr(oper2str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG;
	    lptr->opcode |= i;
	    break;
	case 7:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG;
	    lptr->opcode |= i;
	    break;
	case 10:
	    /* error - invalide addressing mode */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (oper2str[0] == '#')	/* immediate */
    {				/* error - invalid addressing mode */
	error_count++;
    }
    else
    if (oper2str[0] == '[' && plusflag2 == TRUE)	/* post increment */
    {
	lptr->oper2 = BLANK_NBR;
	strcpy(tmps, &oper2str[1]);
	strcpy(oper2str, tmps);
	oper2str[strlen(oper2str) - 2] = '\0';
	i = get_reg_nbr(oper2str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND_INC;
	    lptr->opcode |= i;
	    break;
	case 7:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND_INC;
	    lptr->opcode |= i;
	    break;
	case 10:
	    /* error */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (oper2str[0] == '-' && oper2str[1] == '[')	/* pre-decrement */
    {
	lptr->oper2 = BLANK_NBR;
	strcpy(tmps, &oper2str[2]);
	strcpy(oper2str, tmps);
	oper2str[strlen(oper2str) - 1] = '\0';
	i = get_reg_nbr(oper2str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND_DEC;
	    lptr->opcode |= i;
	    break;
	case 7:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND_DEC;
	    lptr->opcode |= i;
	    break;
	case 10:
	    /* error */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (oper2str[0] == '[')	/* register indirect */
    {
	lptr->oper2 = BLANK_NBR;
	strcpy(tmps, &oper2str[1]);
	strcpy(oper2str, tmps);
	oper2str[strlen(oper2str) - 1] = '\0';
	i = get_reg_nbr(oper2str);
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND;
	    lptr->opcode |= i;
	    break;
	case 7:
	    lptr->opcode |= (i <<= 3);
	    i = MODE_REG_IND;
	    lptr->opcode |= i;
	    break;
	case 10:
	    /* error */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (bracketflag2 == TRUE)	/* relative */
    {
	for (i = 0; oper2str[i] != '['; i++);
	strcpy(tmps, &oper2str[i + 1]);
	oper2str[i] = '\0';
	tmps[2] = '\0';
	tmpreg = get_reg_nbr(tmps);
	if (plusflag2 == TRUE || minusflag2 == TRUE)
	{
	    for (i = 0; oper2str[i] != '+' && oper2str[i] != '-'; i++);
	    oper2str[i] = ' ';
	    sscanf(oper2str, "%s%s", tmps, tmps2);
	    for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		 strcmp(tmps, wptr->name); wptr = wptr->next);
	    if (wptr != NULL_PTR)
	    {
		offset = wptr->value;
		if (wptr->type == TYPE_NONE)
		    lptr->n = 'N';
		else
		    lptr->r = 'R';
	    }
	    else
	    {
		/* error */
		error_count++;
	    }
	    if (isdigit(tmps2[0]))
	    {
		if (plusflag2 == TRUE)
		    offset += get_nbr(tmps2);
		else
		    offset -= get_nbr(tmps2);
	    }
	    else
	    {
		for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		     strcmp(tmps2, wptr->name); wptr = wptr->next);
		if (wptr != NULL_PTR)
		{
		    if (plusflag2 == TRUE)
			offset += wptr->value;
		    else
			offset -= wptr->value;
		    if (wptr->type == TYPE_NONE)
			lptr->n = 'N';
		    else
			lptr->r = 'R';
		}
		else
		{
		    /* error */
		    error_count++;
		}
	    }
	}
	else
	if (isdigit(oper2str[0]))
	    offset = get_nbr(oper2str);
	else
	{
	    for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		 strcmp(oper2str, wptr->name); wptr = wptr->next);
	    if (wptr != NULL_PTR)
	    {
		offset = wptr->value;
		if (wptr->type == TYPE_NONE)
		    lptr->n = 'N';
		else
		    lptr->r = 'R';
	    }
	    else;		/* error */
	}
	lptr->oper2 = offset;
	switch (opcodelen)
	{
	case 4:
	    lptr->opcode |= (tmpreg <<= 3);
	    i = MODE_REL;
	    lptr->opcode |= i;
	    break;
	case 7:
	    lptr->opcode |= (tmpreg <<= 3);
	    i = MODE_REL;
	    lptr->opcode |= i;
	    break;
	case 10:
	    /* error */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else
    if (plusflag2 == TRUE || minusflag2 == TRUE)
    {
	for (i = 0; oper2str[i] != '+' && oper2str[i] != '-'; i++);
	oper2str[i] = ' ';
	sscanf(oper2str, "%s%s", tmps, tmps2);
	for (wptr = &symbol_anchor; wptr != NULL_PTR &&
	     strcmp(tmps, wptr->name); wptr = wptr->next);
	if (wptr != NULL_PTR)
	{
	    offset = wptr->value;
	    if (wptr->type == TYPE_NONE)
		lptr->n = 'N';
	    else
		lptr->r = 'R';
	}
	else
	{
	    /* error */
	    error_count++;
	}
	if (isdigit(tmps2[0]))
	{
	    if (plusflag2 == TRUE)
		offset += get_nbr(tmps2);
	    else
		offset -= get_nbr(tmps2);
	}
	else
	{
	    for (wptr = &symbol_anchor; wptr != NULL_PTR &&
		 strcmp(tmps2, wptr->name); wptr = wptr->next);
	    if (wptr != NULL_PTR)
	    {
		if (plusflag2 == TRUE)
		    offset += wptr->value;
		else
		    offset -= wptr->value;
		if (wptr->type == TYPE_NONE)
		    lptr->n = 'N';
		else
		    lptr->r = 'R';
	    }
	    else
	    {
		/* error */
		error_count++;
	    }
	}
	lptr->oper2 = offset;
	switch (opcodelen)
	{
	case 4:
	    if (!strcmp(instruction, "OUTB") ||
		!strcmp(instruction, "OUTH"))
	    {
		i = MODE_DIR6_IO;
		lptr->opcode |= i;
	    }
	    else
	    {
		i = MODE_DIR6_MEM;
		lptr->opcode |= i;
	    }
	    break;
	case 7:
	    i = MODE_DIR6_MEM;
	    lptr->opcode |= i;
	    break;
	case 10:
	    /* error - can't have immediate mode */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }


    else
    if (isalpha(oper2str[0]))	/* label,string */
    {				/*--------------------------------------------------------------
					Find operand in symbol table
				--------------------------------------------------------------*/
	for (wptr = &symbol_anchor; wptr != NULL_PTR &&
	     strcmp(oper2str, wptr->name); wptr = wptr->next);
	if (wptr != NULL_PTR)
	{
	    switch (wptr->type)
	    {
	    case TYPE_EXTERNAL:
		lptr->prefix |= 0x1800;
		break;
	    case TYPE_INTERNAL:
		lptr->prefix |= 0x1000;
		break;
	    case TYPE_PUBLIC:
		lptr->prefix |= 0x0800;
		break;
	    default:
		lptr->prefix |= 0x0000;
		break;
	    }
	    if (wptr->type == TYPE_NONE)
		lptr->n = 'N';
	    else
		lptr->r = 'R';

	    lptr->oper2 = wptr->location;
	    switch (opcodelen)
	    {
	    case 4:
		if (!strcmp(instruction, "OUTB") ||
		    !strcmp(instruction, "OUTH"))
		{
		    i = MODE_DIR6_IO;
		    lptr->opcode |= i;
		}
		else
		{
		    i = MODE_DIR6_MEM;
		    lptr->opcode |= i;
		}
		break;
	    case 7:
		i = MODE_DIR6_MEM;
		lptr->opcode |= i;
		break;
	    case 10:
		/* error - can't have immediate mode */
		error_count++;
		break;
	    default:
		/* error */
		error_count++;
		break;
	    }
	}
	else
	{
	    lptr->error = UNDEFINED_SYMBOL;
	    error_count++;
	}

    }
    else
    if (isdigit(oper2str[0]))	/* address, numeric */
    {
	lptr->oper2 = get_nbr(oper2str);
	switch (opcodelen)
	{
	case 4:
	    if (!strcmp(instruction, "OUTB") ||
		!strcmp(instruction, "OUTH"))
	    {
		i = MODE_DIR6_IO;
		lptr->opcode |= i;
	    }
	    else
	    {
		i = MODE_DIR6_MEM;
		lptr->opcode |= i;
	    }
	    break;
	case 7:
	    i = MODE_DIR6_MEM;
	    lptr->opcode |= i;
	    break;
	case 10:
	    /* error - can't have direct mode */
	    error_count++;
	    break;
	default:
	    /* error */
	    error_count++;
	    break;
	}
    }
    else;			/* different mode */
    free(oper1str);
    free(oper2str);
    strcpy(tmps, "");
    strcpy(tmps1, "");
    return;
}

/*------------------------------------------------------------------------------
	Name:	  print_symbol_table
	Purpose:  print the symbol tables into a file
	Params:	  fxlt = file pointer.
	Returns:  nothing.
------------------------------------------------------------------------------*/
int print_symbol_table(FILE * fxlt)

{
    int i;
    struct symbol_entry *wptr;

    fprintf(fxlt, "\nEXTERNAL SYMBOL TABLE\n");
    wptr = &symbol_anchor;
    for (i = 0, wptr = wptr->next; wptr != NULL_PTR; wptr = wptr->next)
    {
	if (wptr->type == TYPE_EXTERNAL)
	{
	    fprintf(fxlt, "%-15s ", wptr->name);
	    fprintf(fxlt, "%04X     ", wptr->value);
	    i++;
	    if (!(i % 3))
		fprintf(fxlt, "\n");
	}
    }
    if ((i % 3))
	fprintf(fxlt, "\n");
    fprintf(fxlt, "\nPUBLIC SYMBOL TABLE\n");
    wptr = &symbol_anchor;
    for (i = 0, wptr = wptr->next; wptr != NULL_PTR; wptr = wptr->next)
    {
	if (wptr->type == TYPE_PUBLIC)
	{
	    fprintf(fxlt, "%-15s ", wptr->name);
	    fprintf(fxlt, "%04X     ", wptr->value);
	    i++;
	    if (!(i % 3))
		fprintf(fxlt, "\n");
	}
    }
    if ((i % 3))
	fprintf(fxlt, "\n");
    fprintf(fxlt, "\nINTERNAL SYMBOL TABLE\n");
    wptr = &symbol_anchor;
    for (i = 0, wptr = wptr->next; wptr != NULL_PTR; wptr = wptr->next)
    {
	if (wptr->type == TYPE_INTERNAL)
	{
	    fprintf(fxlt, "%-15s ", wptr->name);
	    fprintf(fxlt, "%04X     ", wptr->location);
	    i++;
	    if (!(i % 3))
		fprintf(fxlt, "\n");
	}
    }
    if ((i % 3))
	fprintf(fxlt, "\n");
}



/*------------------------------------------------------------------------------
	Name:	  print_object
	Purpose:  print the object code	byte by byte into a file
	Params:	  fxob = file pointer.
		  linecnt = number of line in the listing file.
		  larr = pointer to the array of line information.
	Returns:  nothing.
------------------------------------------------------------------------------*/
int print_object(FILE * fxob, int linecnt, struct line_info * larr)

{
    int i, j;
    int hwcnt = 0;
    int tmpi;
    int objarr[1000];
    struct symbol_entry *wptr;


    for (j = 1; j < linecnt; j++)
    {
	if (larr[j].addr == COMMENT_LINE);
	else
	if (larr[j].addr == HALFWORD_LINE)
	    objarr[++hwcnt] = larr[j].opcode;
	else
	if (larr[j].addr == WORD_LINE)
	{
	    objarr[++hwcnt] = larr[j].opcode;
	    objarr[++hwcnt] = larr[j].oper1;
	}
	else
	if (larr[j].addr == DOUBLE_LINE)
	{
	    objarr[++hwcnt] = larr[j].opcode;
	    objarr[++hwcnt] = larr[j].oper1;
	    objarr[++hwcnt] = larr[j].oper2;
	    if (larr[j].r != BLANK_NBR)
		objarr[++hwcnt] = larr[j].r;
	}
	else
	{
	    if (larr[j].prefix >= 0x8000 && larr[j].prefix < 0xC000)
	    {
		objarr[++hwcnt] = larr[j].prefix;
		if (larr[j + 1].addr == HALFWORD_LINE ||
		    larr[j + 1].addr == WORD_LINE ||
		    larr[j + 1].addr == DOUBLE_LINE);
		else
		{
		    tmpi = larr[j].prefix & 0x3FFF;
		    for (; tmpi; tmpi--)
			objarr[++hwcnt] = 0x0000;
		}
	    }
	    else
	    if (larr[j].prefix >= 0xC000)
		objarr[++hwcnt] = larr[j].prefix;
	    else
	    {
		objarr[++hwcnt] = larr[j].prefix;
		objarr[++hwcnt] = larr[j].opcode;
		if (larr[j].oper1 != BLANK_NBR)
		    objarr[++hwcnt] = larr[j].oper1;
		if (larr[j].oper2 != BLANK_NBR)
		    objarr[++hwcnt] = larr[j].oper2;
	    }
	}
    }
    wptr = &symbol_anchor;
    for (i = 0, wptr = wptr->next; wptr != NULL_PTR; wptr = wptr->next)
	if (wptr->type == TYPE_EXTERNAL)
	    i++;
    fprintf(fxob, "%d\n", i);	/* external count number */
    wptr = &symbol_anchor;
    for (wptr = wptr->next; wptr != NULL_PTR; wptr = wptr->next)
    {
	if (wptr->type == TYPE_EXTERNAL)
	{
	    fprintf(fxob, "%s ", wptr->name);
	    fprintf(fxob, "$%04X\n", wptr->value);
	}
    }
    wptr = &symbol_anchor;
    for (i = 0, wptr = wptr->next; wptr != NULL_PTR; wptr = wptr->next)
	if (wptr->type == TYPE_PUBLIC)
	    i++;
    fprintf(fxob, "%d\n", i);	/* public count number */
    wptr = &symbol_anchor;
    for (wptr = wptr->next; wptr != NULL_PTR; wptr = wptr->next)
    {
	if (wptr->type == TYPE_PUBLIC)
	{
	    fprintf(fxob, "%s ", wptr->name);
	    fprintf(fxob, "$%04X\n", wptr->value);
	}
    }
    fprintf(fxob, "%d\n", hwcnt);
    for (j = 1; j <= hwcnt; j++)
    {
	fprintf(fxob, "$%04X ", objarr[j] & 0x0000FFFF);
	if (!(j % 12))
	    fprintf(fxob, "\n");
    }
}

/*------------------------------------------------------------------------------
	Name:	  print_listing
	Purpose:  print the listing file into fxlt.
	Params:	  fxlt = file pointer.
		  linecnt = number of line in the listing file.
		  larr = pointer to the array of line information.
		  LC = location counter.
	Returns:  nothing.
------------------------------------------------------------------------------*/
int print_listing(FILE * fxlt, int linecnt, struct line_info * larr, int LC)

{
    int j;
    char tmps[MAX_CHARS_PER_LINE];

    fprintf(fxlt, "%d = NUMBER OF MACHINE CODE BYTES\n", LC);
    for (j = 1; j <= linecnt; j++)
    {
	if ((larr[j].addr == COMMENT_LINE) || (larr[j].addr == ORG_LINE))
	{
	    sscanf(larr[j].extra, "%s", tmps);
	    if (larr[j].error == DUPLICATE_DEF_ERR)
		fprintf(fxlt, "     %c ", DUPLICATE_DEF_ERR);
	    else
		fprintf(fxlt, "   ");
	    if (strcmp(tmps, DIR_UNIT) && strcmp(tmps, DIR_END))
		fprintf(fxlt, "                             ");
	    fprintf(fxlt, "%s\n", larr[j].extra);
	}
	else
	if (larr[j].addr == HALFWORD_LINE)
	{
	    fprintf(fxlt, "       ");
	    fprintf(fxlt, "%04X\n", larr[j].opcode);
	}
	else
	if (larr[j].addr == WORD_LINE)
	{
	    fprintf(fxlt, "       ");
	    fprintf(fxlt, "%04X ", larr[j].opcode);
	    fprintf(fxlt, "%04X\n", larr[j].oper1);
	}
	else
	if (larr[j].addr == DOUBLE_LINE)
	{
	    fprintf(fxlt, "       ");
	    fprintf(fxlt, "%04X ", larr[j].opcode);
	    fprintf(fxlt, "%04X ", larr[j].oper1);
	    fprintf(fxlt, "%04X ", larr[j].oper2);
	    if (larr[j].r != BLANK_NBR)
		fprintf(fxlt, "%04X\n", larr[j].r);
	    else
		fprintf(fxlt, "\n");
	}
	else
	{
	    if (larr[j].error == NO_ERROR)
		fprintf(fxlt, "   ");
	    else
		fprintf(fxlt, " %c ", larr[j].error);
	    if (larr[j].addr == BLANK_NBR)
		fprintf(fxlt, "    ");
	    else
		fprintf(fxlt, "%04X", larr[j].addr);
	    if (larr[j].opcode == BLANK_NBR)
		fprintf(fxlt, "     ");
	    else
		fprintf(fxlt, "%04X ", larr[j].opcode);
	    if (larr[j].oper1 == BLANK_NBR)
		fprintf(fxlt, "     ");
	    else
		fprintf(fxlt, "%04X ", larr[j].oper1 & 0x0000FFFF);
	    if (larr[j].oper2 == BLANK_NBR)
		fprintf(fxlt, "     ");
	    else
		fprintf(fxlt, "%04X ", larr[j].oper2 & 0x0000FFFF);
	    fprintf(fxlt, "%1c%1c", larr[j].r, larr[j].n);
	    fprintf(fxlt, "     %s\n", larr[j].extra);
	}
    }
}


errmsg(FILE * fp, int i, char *extra)
{
    if (extra == NULL)
	fprintf(fp, "==> %04d, %s <==\n", error_list[i].nbr,
		error_list[i].text);
    else
	fprintf(fp, "==> %04d, %s:  %s <==\n", error_list[i].nbr,
		error_list[i].text, extra);
}
