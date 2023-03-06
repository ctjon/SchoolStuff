/*
 * ASGN1.C Written By: Chris Tjon For: CS366
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int getsize(FILE * file, int size);
int valid_trans(char *buf);
void update_record(FILE * client, FILE * supply, char *data);
int find_record(FILE * file, int size, int len, char *data);

static char *client_change[] =
{"age", "city", NULL};
static char *supply_change[] =
{"name", "amount", "city", NULL};

typedef struct
{
    char status;
    char name[2];
    char age[2];
    char city[3];
    char nl;
}      CLIENT;

typedef struct
{
    char status;
    char order[2];
    char name[2];
    char amount[3];
    char city[3];
    char nl;
}      SUPPLY;


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

FILE *error;
int line_num = 0;
int client_recs, supply_recs;

int main()
{
    FILE *client, *supply, *trans;
    char buf[BUFSIZ];
    void update_record();
    if ((client = fopen("client.m", "r+")) == NULL)
	perror("Open client"), exit(1);
    if ((supply = fopen("supply.m", "r+")) == NULL)
	perror("Open supply"), exit(1);
    if ((trans = fopen("xaction1", "r")) == NULL)
	perror("Open Transaction"), exit(1);
    if ((error = fopen("errors.log", "w")) == NULL)
	perror("Open Errors.log"), exit(1);
    client_recs = getsize(client, sizeof(CLIENT));
    supply_recs = getsize(supply, sizeof(SUPPLY));
    while (fgets(buf, BUFSIZ, trans) != NULL)
    {
	line_num++;
	if (valid_trans(buf))
	    update_record(client, supply, buf);
    }
    fclose(client);
    fclose(supply);
    fclose(error);
    fclose(trans);
    return 0;
}


/*
 * getsize - returns the number of records in a file
 */
int getsize(FILE * file, int size)
{
    struct stat buf;
    fstat(fileno(file), &buf);
    if (buf.st_size % size)
    {
	fprintf(error, "Error: File damage has occured, aborting...\n");
	exit(1);
    }
    return buf.st_size / size;
}



/*
 * valid_trans - tests transaction for valid type
 */
int valid_trans(char *buf)
{
    /* Check for valid Delete or Change code */
    if (strncmp(buf, "DL", 2) && strncmp(buf, "CH", 2))
    {
	fprintf(error, "Error: Unrecognized command in trans file: %s", buf);
	return FALSE;
    }
    /* Check for valid Client or Supply code */
    if (strncmp(&buf[3], "CL", 2) && strncmp(&buf[3], "SP", 2))
    {
	fprintf(error, "Error: Unrecognized master in trans file: %s", buf);
	return FALSE;
    }
    /* Check for spaces in the appropriate columns */
    if ((buf[2] != ' ') || (buf[5] != ' '))
    {
	fprintf(error, "Error: Unrecognized transaction in trans file: %s", buf);
	return FALSE;
    }
    return TRUE;
}


/*
 * update_record - update a record on the master files
 */
void update_record(FILE * client, FILE * supply, char *data)
{

    void delete_client(FILE * file, char *data);
    void delete_supply(FILE * file, char *data);
    void change_client(FILE * file, char *data);
    void change_supply(FILE * file, char *data);
    if (strncmp(&data[3], "CL", 2) == 0)
    {
	if (strncmp(data, "DL", 2) == 0)
	    delete_client(client, data);
	else
	    change_client(client, data);
    }
    else
    {
	if (strncmp(data, "DL", 2) == 0)
	    delete_supply(supply, data);
	else
	    change_supply(supply, data);
    }
}


/*
 * delete_client - delete a client out of the client master file
 */
void delete_client(FILE * file, char *data)
{
    CLIENT buf;
    /* ensure that the transaction record is not missing whitespace */
    if ((data[8] != '\n') && (data[8] != ' '))
    {
	fprintf(error, "Invalid transaction in transaction file %s\n", data);
	return;
    }
    /* find the correct record or else generate an error */
    if (find_record(file, sizeof(CLIENT), client_recs, &data[6]) == FALSE)
    {
	fprintf(error, "Client ID not located in master file %s\n", data);
	return;
    }
    fread(&buf, sizeof(CLIENT), 1, file);
    buf.status = 'D';
    fseek(file, -sizeof(CLIENT), 1);
    fwrite(&buf, sizeof(CLIENT), 1, file);
}

void delete_supply(FILE * file, char *data)
{
    SUPPLY buf;
    /* ensure that the transaction record is not missing whitespace */
    if ((data[8] != '\n') && (data[8] != ' '))
    {
	fprintf(error, "Invalid transaction in transaction file %s\n", data);
	return;
    }
    /* find the correct record or else generate an error */
    if (find_record(file, sizeof(SUPPLY), supply_recs, &data[6]) == FALSE)
    {
	fprintf(error, "Unable to locate deletion record %s\n", data);
	return;
    }
    fread(&buf, sizeof(SUPPLY), 1, file);
    buf.status = 'D';
    fseek(file, -sizeof(SUPPLY), 1);
    fwrite(&buf, sizeof(SUPPLY), 1, file);
    fflush(file);
}



/*
 * change_client
 */
void change_client(FILE * file, char *data)
{
    CLIENT buf;
    register int i;
    char *tok;
    /* ensure that the transaction record is not missing whitespace */
    if ((data[8] != '\n') && (data[8] != ' '))
    {
	fprintf(error, "Invalid transaction in transaction file %s\n", data);
	return;
    }
    /* find the correct record or else generate an error */
    if (find_record(file, sizeof(CLIENT), client_recs, &data[6]) == FALSE)
    {
	fprintf(error, "Unable to locate client %s\n", data);
	return;
    }
    fread(&buf, sizeof(CLIENT), 1, file);
    tok = strtok(&data[8], " =\n");
    for (i = 0; client_change[i]; i++)
	if (strcmp(tok, client_change[i]) == 0)
	    break;
    /*
     * check to see if the change requested is valid form the list above -
     * static char client_change
     */
    if (!client_change[i])
    {
	fprintf(error, "Error: Unrecognized change request: %s\n", tok);
	return;
    }
    tok = strtok(NULL, " \n");
    switch (i)
    {
    case 0:			/* Age - ensure between 1-99 */
	if ((atoi(tok) > 99) || (atoi(tok) < 1))
	{
	    fprintf(error, "Error: Invalid age range: %s\n", tok);
	    break;
	}
	strncpy(buf.age, tok, 2);
	break;
    case 1:			/* city - ensure not longer than 3 char */
	if (strlen(tok) != 3)
	{
	    fprintf(error, "Error: Invalid city code: %s\n", tok);
	    break;
	}
	strncpy(buf.city, tok, 3);
	break;
    default:;
    }
    fseek(file, -sizeof(CLIENT), 1);
    fwrite(&buf, sizeof(CLIENT), 1, file);
}


/*
 * change_supply - change a record in the supply master
 */
void change_supply(FILE * file, char *data)
{
    SUPPLY buf;
    register int i;
    char *tok;
    /* ensure that the transaction record is not missing whitespace */
    if ((data[8] != '\n') && (data[8] != ' '))
    {
	fprintf(error, "Invalid transaction in transaction file %s\n", data);
	return;
    }
    /* find the correct record or else generate an error */
    if (find_record(file, sizeof(SUPPLY), supply_recs, &data[6]) == FALSE)
    {
	fprintf(error, "Unable to locate supplier %s\n", data);
	return;
    }
    fread(&buf, sizeof(SUPPLY), 1, file);
    tok = strtok(&data[8], " =\n");
    for (i = 0; supply_change[i]; i++)
	if (strcmp(tok, supply_change[i]) == 0)
	    break;
    /*
     * check to see if the change requested is valid form the list above -
     * static char sypply_change
     */
    if (!supply_change[i])
    {
	fprintf(error, "Error: Unrecognized change request: %s\n", tok);
	return;
    }
    tok = strtok(NULL, " \n");
    switch (i)
    {
    case 0:			/* name - ensure name is 2 long */
	if (strlen(tok) != 2)
	{
	    fprintf(error, "Error: Invalid name : %s\n", tok);
	    break;
	}
	strncpy(buf.name, tok, 2);
	break;
    case 1:			/* amount - ensure length of amount is 3 */
	if (strlen(tok) != 3)
	{
	    fprintf(error, "Error: Invalid amount: %s\n", tok);
	    break;
	}
	strncpy(buf.amount, tok, 3);
	break;
    case 2:			/* city - ensure length of city is 3 */
	if (strlen(tok) != 3)
	{
	    fprintf(error, "Error: Invalid city: %s\n", tok);
	    break;
	}
	strncpy(buf.city, tok, 3);
	break;
    default:;
    }
    fseek(file, -sizeof(SUPPLY), 1);
    fwrite(&buf, sizeof(SUPPLY), 1, file);
}


/*
 * find_record - binary search of either type of record within either master
 * file
 */
int find_record(FILE * file, int size, int len, char *data)
{
    char buf[BUFSIZ];
    register int beg, end, mid;
    int comp;
    beg = 0;
    end = len - 1;
    mid = end / 2;
    fflush(stdout);
    while (end >= beg)
    {
	fseek(file, (mid * size), 0);
	fread(buf, size, 1, file);
	if ((comp = strncmp(data, &buf[1], 2)) < 0)
	    end = mid - 1;
	else if (comp > 0)
	    beg = mid + 1;
	else
	{
	    fseek(file, -(size), 1);
	    return TRUE;
	}
	mid = (beg + end) / 2;
    }
    return FALSE;
}
