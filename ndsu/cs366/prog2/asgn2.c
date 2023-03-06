/*
 * ASGN2.C
 *
 * Written by Mike Langowski and Chris Tjon
 *
 * This program is an extension of ASGN1.C.  Additions to ASGN1.C are:
 * Creation of secondary indices on the City fields of both master files.
 * Handling changes and deletions as in ASGN1.C , and handle insertions by
 * creating and using differential files.  The indices are maintaned in a 
 * up-to-date condition against the Change transactions that affect values
 * of the City fields of master files.
 * 
 * Secondary indices will be implemented as inverted lists.  Three files will be
 * involved in the implementation of these indices: two directory
 * files,CLCITYDR and SUCITYDR, and InvLists, which stores the accession list
 * for both indices.
 * 
 * The index directories will be indexed using B+ trees. The accession list will
 * be implemented as linked lists.  Pointers are represented here as the line
 * number in the file (i.e if ptr = 8 then that refers to line number 8 in
 * the accesion list).
 * 
 * Both differtial files are sorted on their key values and then merged with its
 * corresponding master file, with deleted records dropped, to created a new
 * master file
 * 
 * Input for this program will be a single batched transaction file. A
 * validation check on each transaction, as in Assign 1, is done.  Any
 * transaction that fails to be valid is recorded in error.log
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CLIENT_FLAG 0
#define SUPPLY_FLAG 1

/* These are the the types of client changes possible */
static char *client_change[] = {"age", "city", NULL};

/* These are the types of supply changes possible */
static char *supply_change[] = {"name", "amount", "city", NULL};

/* Define the client structure */
typedef struct
{
    char status;
    char name[2];
    char age[2];
    char city[3];
    char nl;
}
       CLIENT;

/* Define the supply structure */
typedef struct
{
    char status;
    char order[2];
    char name[2];
    char amount[3];
    char city[3];
    char nl;
}
       SUPPLY;

/* Define the entry structure */
typedef struct
{
    char key[16];
    int ndptr;
}      ENTRY_TYPE;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/* procudures used in the batch processing */
int getsize(FILE * file, int size);
int valid_trans(char *buf);
void update(FILE * client, FILE * client_temp, FILE * supply,
            FILE * supply_temp, char *data);
int find_record(FILE * file, int size, int len, char *data);
void merge(FILE * master_file, FILE * temp_file, int flag);
void sort(void);


/* procedures used for the B+ trees */
void build_btree(FILE * in, int sec_key_ind);
int lst_insert(char key[2], char skey[3]);
void add_tolst(char key[2], int ptr);
void b_insert(ENTRY_TYPE entry);
void non_leaf_insert(int ndptr, ENTRY_TYPE entry);
int get_parent(int ndptr, char key[3], int nxtptr);
void add_entry(ENTRY_TYPE entry, int ndptr);
void *split_node(int ndptr, ENTRY_TYPE entry, char newkey[3], int *newptr);
int split_leaf(int ptr, ENTRY_TYPE entry);
void *get_smallkey(int ndptr, char skey[3]);
int tree_search(ENTRY_TYPE entry);
int b_find(ENTRY_TYPE entry);
void *num_to_str(char str[3], int num);
int str_to_num(char str[3]);
void *get_field(char field[3], char rec[20], int beg);



/* Batch Processing Global Variables */
FILE *error;
int line_num = 0;
int client_recs, supply_recs;

/* B+ Tree Global Variables */
FILE *dir,                      /* Current directory opened: cl_dir or sp_dir */
     *in_lst;                   /* inverted list file */
char roottype;                  /* Current root used for the open directory */
int Croot = 0,                  /* Client root */
    Sroot = 0;                  /* Supply root */


int main(void)
/******************************************************************************/
{
    void update();
    FILE *client, *client_temp, *supply, *supply_temp, *trans1, *trans2,
        *cl_dir, *sp_dir;
    char buf[BUFSIZ];

    if ((client = fopen("client.m", "r+")) == NULL)
        perror("Open client.m failed"), exit(1);
    if ((client_temp = fopen("client.tmp", "w+")) == NULL)
        perror("Open client.tmp failed"), exit(1);
    if ((supply = fopen("supply.m", "r+")) == NULL)
        perror("Open supply.m failed"), exit(1);
    if ((supply_temp = fopen("supply.tmp", "w+")) == NULL)
        perror("Open supply.tmp failed"), exit(1);
    if ((trans1 = fopen("xaction1", "r")) == NULL)
        perror("Open transaction 1 failed"), exit(1);
    if ((trans2 = fopen("xactions2", "r")) == NULL)
        perror("Open transaction 2 failed"), exit(1);
    if ((error = fopen("errors.log", "w")) == NULL)
        perror("Open errors.log failed"), exit(1);

    client_recs = getsize(client, sizeof(CLIENT));
    supply_recs = getsize(supply, sizeof(SUPPLY));

    while (fgets(buf, BUFSIZ, trans1) != NULL)
    {
        line_num++;
        if (valid_trans(buf))
            update(client, client_temp, supply, supply_temp, buf);
    }
    while (fgets(buf, BUFSIZ, trans2) != NULL)
    {
        line_num++;
        if (valid_trans(buf))
            update(client, client_temp, supply, supply_temp, buf);
    }
    merge(client, client_temp, CLIENT_FLAG);
    merge(supply, supply_temp, SUPPLY_FLAG);
    fclose(client);
    fclose(client_temp);
    fclose(supply);
    fclose(supply_temp);
    fclose(trans1);
    fclose(trans2);
    fclose(error);
    sort();

    if ((in_lst = fopen("InvLists", "w+")) == NULL)
        perror("Open InvLists failed"),exit(1);

    if ((client = fopen("client.n", "r")) == NULL)
        perror("Open client.n failed"), exit(1);
    if ((cl_dir = fopen("CLCITYDR", "w+")) == NULL)
        perror("Open CLCITYDR failed"),exit(1);

    dir = cl_dir;           /* current directory is client directory */
    roottype = 'C';         /* identify that Croot will be used as the root */
    build_btree(client, 5);
    fclose(client);
    fclose(cl_dir);

    if ((supply = fopen("supply.n", "r")) == NULL)
        perror("Open supply.n failed"), exit(1);
    if ((sp_dir = fopen("SPCITYDR", "w+")) == NULL)
        perror("Open SPCITYDR failed"),exit(1);
    dir = sp_dir;           /* current directory is supply directory */
    roottype = 'S';         /* identify that Sroot will be used as the root */
    build_btree(supply, 8);
    fclose(supply);
    fclose(sp_dir);

    fclose(in_lst);
    return 0;
}
/******************************************************************************/


int getsize(FILE * file, int size)
/******************************************************************************/
/* requires: file is initialized properly and size is the size of the         */
/*           structures stored in the file                                    */
/* modifies: nothing                                                          */
/* effects:  returns the number of records in a file                          */
/******************************************************************************/
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

int valid_trans(char *buf)
/******************************************************************************/
/* requires: buf is a valid char buf                                          */
/* modifies: nothing                                                          */
/* effects:  tests transaction for valid format and type                      */
/******************************************************************************/
{
    /* Check for valid Delete, Change, or Insert code */
    if (strncmp(buf, "DL", 2) && strncmp(buf, "CH", 2) && strncmp(buf, "IN", 2))
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

void update(FILE * client, FILE * client_temp, FILE * supply,
                 FILE * supply_temp, char *data)
/******************************************************************************/
/* requires: all files passed to it have been initialized properly and data   */
/*           is a valid transaction                                           */
/* modifies: client, client.tmp, supply, or supply.tmp depending on what type */
/*           of transaction you are updating                                  */
/* effects:  updates the master files with a record change or delete and      */
/*           and updates the master.tmp files with an insert                  */
/******************************************************************************/
{

    void delete(FILE * file, char *data, int flag);
    void change(FILE * file, char *data, int flag);
    void insert(FILE * master_file, FILE * temp_file, char *data, int flag);

    if (strncmp(&data[3], "CL", 2) == 0)
    {
        if (strncmp(data, "DL", 2) == 0)
            delete(client, data, CLIENT_FLAG);
        else if (strncmp(data, "CH", 2) == 0)
            change(client, data, CLIENT_FLAG);
        else if (strncmp(data, "IN", 2) == 0)
            insert(client, client_temp, data, CLIENT_FLAG);
    }
    else if (strncmp(&data[3], "SP", 2) == 0)
    {
        if (strncmp(data, "DL", 2) == 0)
            delete(supply, data, SUPPLY_FLAG);
        else if (strncmp(data, "CH", 2) == 0)
            change(supply, data, SUPPLY_FLAG);
        else if (strncmp(data, "IN", 2) == 0)
            insert(supply, supply_temp, data, SUPPLY_FLAG);
    }
    else
    {
        fprintf(error, "Invalid transaction in transaction file %s\n", data);
        return;
    }
}

void delete(FILE * file, char *data, int flag)
/******************************************************************************/
/* requires: file is a valid file pointer, data is valid, and flag is set     */
/* modifies: either the client master file or the supplier master file        */
/*           depending on the value of flag                                   */
/* effects:  delete - deletes record from either master file                  */
/******************************************************************************/
{
    CLIENT client_buf;
    SUPPLY supply_buf;
    if ((data[8] != '\n') && (data[8] != ' '))
    {
        fprintf(error, "Invalid transaction in transaction file %s\n", data);
        return;
    }
    /* find the correct client record or else generate an error */
    switch (flag)
    {
    case CLIENT_FLAG:
        /* ensure that the transaction record is not missing whitespace */
        if (find_record(file, sizeof(CLIENT), client_recs, &data[6]) == FALSE)
        {
            fprintf(error, "Client ID not located in master file %s\n", data);
            return;
        }
        fread(&client_buf, sizeof(CLIENT), 1, file);
        client_buf.status = 'D';
        fseek(file, -sizeof(CLIENT), 1);
        fwrite(&client_buf, sizeof(CLIENT), 1, file);
        break;

    case SUPPLY_FLAG:

        /* find the correct supply record or else generate an error */
        if (find_record(file, sizeof(SUPPLY), supply_recs, &data[6]) == FALSE)
        {
            fprintf(error, "Unable to locate deletion record %s\n", data);
            return;
        }
        fread(&supply_buf, sizeof(SUPPLY), 1, file);
        supply_buf.status = 'D';
        fseek(file, -sizeof(SUPPLY), 1);
        fwrite(&supply_buf, sizeof(SUPPLY), 1, file);
        break;
    }
    fflush(file);
}

void change(FILE * file, char *data, int flag)
/******************************************************************************/
/* requires: file is a valid file pointer, data is valid, and flag is set     */
/* modifies: either the client master file or the supplier master file        */
/*           depending on the value of flag                                   */
/* effects:  changes a record in either master file                           */
/******************************************************************************/
{
    CLIENT client_buf;
    SUPPLY supply_buf;
    register int i;
    char *tok;
    /* ensure that the transaction record is not missing whitespace */
    if ((data[8] != '\n') && (data[8] != ' '))
    {
        fprintf(error, "Invalid transaction in transaction file %s\n", data);
        return;
    }
    switch (flag)
    {
    case CLIENT_FLAG:
        /* find the correct record or else generate an error */
        if (find_record(file, sizeof(CLIENT), client_recs, &data[6]) == FALSE)
        {
            fprintf(error, "Unable to locate client %s\n", data);
            return;
        }
        fread(&client_buf, sizeof(CLIENT), 1, file);
        tok = strtok(&data[8], " =\n");
        for (i = 0; client_change[i]; i++)
            if (strcmp(tok, client_change[i]) == 0)
                break;
        /*
         * check to see if the change requested is valid form the list above
         * - static char client_change
         */
        if (!client_change[i])
        {
            fprintf(error, "Error: Unrecognized change request: %s\n", tok);
            return;
        }
        tok = strtok(NULL, " \n");
        switch (i)
        {
        case 0:                /* Age - ensure between 1-99 */
            if ((atoi(tok) > 99) || (atoi(tok) < 1))
            {
                fprintf(error, "Error: Invalid age range: %s\n", tok);
                break;
            }
            strncpy(client_buf.age, tok, 2);
            break;
        case 1:                /* city - ensure not longer than 3 char */
            if (strlen(tok) != 3)
            {
                fprintf(error, "Error: Invalid city code: %s\n", tok);
                break;
            }
            strncpy(client_buf.city, tok, 3);
            break;
        default:;
        }
        fseek(file, -sizeof(CLIENT), 1);
        fwrite(&client_buf, sizeof(CLIENT), 1, file);
        fflush(file);
        break;
    case SUPPLY_FLAG:
        /* find the correct record or else generate an error */
        if (find_record(file, sizeof(SUPPLY), supply_recs, &data[6]) == FALSE)
        {
            fprintf(error, "Unable to locate supplier %s\n", data);
            return;
        }
        fread(&supply_buf, sizeof(SUPPLY), 1, file);
        tok = strtok(&data[8], " =\n");
        for (i = 0; supply_change[i]; i++)
            if (strcmp(tok, supply_change[i]) == 0)
                break;
        /*
         * check to see if the change requested is valid form the list above
         * - static char sypply_change
         */
        if (!supply_change[i])
        {
            fprintf(error, "Error: Unrecognized change request: %s\n", tok);
            return;
        }
        tok = strtok(NULL, " \n");
        switch (i)
        {
        case 0:                /* name - ensure name is 2 long */
            if (strlen(tok) != 2)
            {
                fprintf(error, "Error: Invalid name : %s\n", tok);
                break;
            }
            strncpy(supply_buf.name, tok, 2);
            break;
        case 1:                /* amount - ensure length of amount is 3 */
            if (strlen(tok) != 3)
            {
                fprintf(error, "Error: Invalid amount: %s\n", tok);
                break;
            }
            strncpy(supply_buf.amount, tok, 3);
            break;
        case 2:                /* city - ensure length of city is 3 */
            if (strlen(tok) != 3)
            {
                fprintf(error, "Error: Invalid city: %s\n", tok);
                break;
            }
            strncpy(supply_buf.city, tok, 3);
            break;
        default:;
        }
        fseek(file, -sizeof(SUPPLY), 1);
        fwrite(&supply_buf, sizeof(SUPPLY), 1, file);
        fflush(file);
        break;
    }
}

void insert(FILE * master_file, FILE * temp_file, char *data, int flag)
/******************************************************************************/
/* requires: master_file and temp_file are valid file pointers, data is valid,*/
/*           and flag is set                                                  */
/* modifies: either the client master file and the client temp file or the    */
/*           supplier master file and the supplier temp file depending on the */
/*           value of flag                                                    */
/* effects:  places the record to be inserted into the appropriate temporary  */
/*           file.  This file will later be sorted with the sort the unix sort*/
/*           command so the records are simply placed at the end of the       */
/*           appropriate temp file                                            */
/******************************************************************************/
{
    CLIENT client_buf, test_client;
    SUPPLY supply_buf, test_supply;
    register int i;
    char *tok;

    /* Insert either a client or a supply record in the temporary file */
    switch (flag)
    {
    case CLIENT_FLAG:
        test_client.status = ' ';
        if (strncmp(&data[6], "client_name", 11) != 0)
        {
            fprintf(error, "Invalid transaction format %s\n", data);
            return;
        }
        tok = strtok(&data[17], " =\n");
        /* tok = client name at this point */
        sprintf(test_client.name, "%2s", tok);

        tok = strtok(NULL, " =\n");
        /* tok = age */

        tok = strtok(NULL, " =\n");
        /* tok = amount */
        if ((atoi(tok) > 99) || (atoi(tok) < 1))
        {
            fprintf(error, "Error: Invalid age range: %s\n", tok);
            break;
        }
        sprintf(test_client.age, "%2s", tok);
        tok = strtok(NULL, " =\n");
        /* tok = city */
        tok = strtok(NULL, " =\n");
        /* tok = city value */
        if (strlen(tok) != 3)
        {
            fprintf(error, "Error: Invalid city code: %s\n", tok);
            break;
        }
        sprintf(test_client.city, "%3s", tok);
        test_client.nl = '\n';
        /*
         * ensure that the client does not already exist in the client file
         */
        if (find_record(master_file, sizeof(CLIENT), client_recs, test_client.name) == TRUE)
        {
            fprintf(error, "Client ID already exists in master file %s\n", data);
            return;
        }
        /* linear search of tmp file  */
        fseek(temp_file, 0L, 0);
        while (!feof(temp_file))
        {
            fread(&client_buf, sizeof(CLIENT), 1, temp_file);
            if (strcmp(&test_client, &client_buf) == 0)
            {
                fprintf(error, "Client ID already exists in temp file %s\n", data);
                return;
            }
        }
        fseek(temp_file, 0L, 2);
        fwrite(&test_client, sizeof(CLIENT), 1, temp_file);
        break;

    case SUPPLY_FLAG:
        test_supply.status = ' ';
        if (strncmp(&data[6], "supply_order", 12) != 0)
        {
            fprintf(error, "Invalid transaction format %s\n", data);
            return;
        }
        tok = strtok(&data[18], " =\n");
        /* Tok = order number */
        sprintf(test_supply.order, "%2s", tok);

        tok = strtok(NULL, " =\n");
        /* tok = name */
        tok = strtok(NULL, " =\n");
        /* tok = new name value */
        sprintf(test_supply.name, "%2s", tok);
        tok = strtok(NULL, " =\n");
        /* tok = amount */
        tok = strtok(NULL, " =\n");
        /* tok = value of amount */
        sprintf(test_supply.amount, "%3s", tok);

        tok = strtok(NULL, " =\n");
        /* tok = city */
        tok = strtok(NULL, " =\n");
        /* tok = value of city */
        sprintf(test_supply.city, "%2s", tok);
        test_supply.nl = '\n';
        /*
         * ensure that the supplier does not already exist in the supply file
         */
        if (find_record(master_file, sizeof(SUPPLY), supply_recs, test_supply.name) == TRUE)
        {
            fprintf(error, "Supplier ID already exists in master file %s\n", data);
            return;
        }
        /* linear search of tmp file  */
        fseek(temp_file, 0L, 0);
        while (!feof(temp_file))
        {
            fread(&supply_buf, sizeof(SUPPLY), 1, temp_file);
            if (strcmp(&test_supply, &supply_buf) == 0)
            {
                fprintf(error, "Supplier ID already exists in temp file %s\n", data);
                return;
            }
        }
        fseek(temp_file, 0L, 2);
        fwrite(&test_supply, sizeof(SUPPLY), 1, temp_file);
        break;

    }
}

int find_record(FILE * file, int size, int len, char *data)
/******************************************************************************/
/* requires: file is a valid FILE pointer, size is a valid value of the size  */
/*           of the structures stored in the file, len is the length of the   */
/*           file in records, and data is valid data(checked by valid_trans() */
/* modifies: nothing                                                          */
/* effects:  find_record is a simple binary search.  It can be used on either */
/*           the supply file or the client file.  It is important to remember */
/*           that this procedure will only work properly on a sorted file     */
/******************************************************************************/
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

void merge(FILE * master_file, FILE * temp_file, int flag)
/******************************************************************************/
/* requires: master_file and temp_file are valid FILE pointers and flag is    */
/*           set for either SUPPLY_FLAG or CLIENT_FLAG                        */
/* modifies: master_file                                                      */
/* effects:  combines the master_file and temp_file and stores the combination*/
/*           in the master_file                                               */
/******************************************************************************/
{
    CLIENT client_buf;
    SUPPLY supply_buf;
    switch (flag)
    {
    case CLIENT_FLAG:
        fseek(master_file, 0L, 2);
        fseek(temp_file, 0L, 0);
        while (!feof(temp_file))
        {
            fread(&client_buf, sizeof(CLIENT), 1, temp_file);
            if (!feof(temp_file))
                fwrite(&client_buf, sizeof(CLIENT), 1, master_file);
        }
        break;
    case SUPPLY_FLAG:
        fseek(master_file, 0L, 2);
        fseek(temp_file, 0L, 0);
        while (!feof(temp_file))
        {
            fread(&supply_buf, sizeof(SUPPLY), 1, temp_file);
            if (!feof(temp_file))
                fwrite(&supply_buf, sizeof(SUPPLY), 1, master_file);
        }
        break;

    default:
        printf("Invalid flag passed to merge-> [%d]\n", flag);
        exit(1);
    }
}

void sort(void)
/******************************************************************************/
/* requires: grep and sort are in your current path and client.m and supply.m */
/*           exists as a valid master file                                    */
/* modifies: client.n and supply.n                                            */
/* effects:  places the sorted contents of client.m or supply.m into client.n */
/*           or supply.n respectively.  Observe that by changing "-o client.n"*/
/*           to "-o client.m" the sorted output would be stored back into the */
/*           original master file.                                            */
/******************************************************************************/
{
    if (system("grep -v D<client.m|sort +0.1 -0.2 -o client.n"))
        perror("sort client.m failed");
    if (system("grep -v D<supply.m|sort +0.1 -0.2 -o supply.n"))
        perror("sort supply.m failed");
}


void *get_field(char field[3], char rec[20], int beg)
/*
  this procedure will return a field of length 3 of rec starting at beg
  Requires: rec has a string and 0 < beg < 17
*/
{
    strncpy(field, rec + beg, 3);
    field[3] = '\0';    /*end of string*/
}

int str_to_num(char str[3])
/*
  this procedure will convert a string representation of number 3 bytes long
  to the corresponding integer value and return this value.  if str ="   "
  then returns a -1.
  Requires:  str = "   " or a three bit number representation (e.g. 002,123)
*/
{
    int dig1, dig2, dig3;

    if (str[0] == ' ')
        return -1;
    else
    {
        dig1 = str[0] - '0';
        dig2 = str[1] - '0';
        dig3 = str[2] - '0';
    }
    return (dig1 * 100 + dig2 * 10 + dig3);
}


void *num_to_str(char str[3], int num)
/*
  this procedure will convert the integer number num to a three bit character
  representation and place this in str
  Requires: 0 < num < 999
 */
{

    int dig1, dig2, dig3;


    dig3 = num % 10;
    num = num / 10;
    dig2 = num % 10;
    num = num / 10;
    dig1 = num % 10;
    str[0] = '0' + (int) dig1;
    str[1] = '0' + (int) dig2;
    str[2] = '0' + (int) dig3;
    str[3] = '\0';
}

int b_find(ENTRY_TYPE entry)
/*
  this procedure will given an entry, find its leaf node, this does not
  require that the entry exists. it simply returns the ptr to the leaf
  node where it would belong.
  Requires: entry.key has some value
*/

{
    int ptr;

    switch (roottype)
    {
    case 'C':
        entry.ndptr = Croot;
        break;
    case 'S':
        entry.ndptr = Sroot;
        break;
    }

    ptr = tree_search(entry);  /*searches from root*/
    return ptr;
}


int tree_search(ENTRY_TYPE entry)
/*
  searches tree for entry.  this will traverse the tree until at a leaf node
  the ptr to this node is then returned
  Requires:  entry.node has a value
*/

{
    char node[16], p0[3], p1[3], p2[3], k1[3], k2[3];
    int found = 0;

    fseek(dir, (entry.ndptr * 16), 0);
    fgets(node, 16, dir);
    get_field(p0, node, 0);
    while (!found)
    {
        if (strcmp(p0, "   ") == 0)
        {                        /* if node is a leaf */
            found = 1;                /* then found */
        }
        else                     /*else get next pointer*/
        {
            get_field(k1, node, 3);
            get_field(p1, node, 6);
            get_field(k2, node, 9);
            get_field(p2, node, 12);
            if (strcmp(entry.key, k1) < 0)
                entry.ndptr = str_to_num(p0);
            else
            {
                if ((strcmp(entry.key, k2) < 0) || (strcmp(k2, "   ") == 0))
                    entry.ndptr = str_to_num(p1);
                else
                    entry.ndptr = str_to_num(p2);
            }
            fseek(dir, (entry.ndptr * 16), 0);
            fgets(node, 16, dir);
            get_field(p0, node, 0);
        }
    }
    return entry.ndptr;
}



void *get_smallkey(int ndptr, char skey[3])
/*
  given the pointer to a node ndptr this will store the smallest key in
  that node in skey
  Requires:  A node exists at ndptr
*/

{
    fflush(dir);
    fseek(dir, (ndptr * 16) + 3, 0);
    fgets(skey, 4, dir);
}

int split_leaf(int ptr, ENTRY_TYPE entry)
/*
  given the ponter to the leaf and the entry to be inserted this will
  split the leaf where the first 2 nodes (in alphabetic ordrer) will
  be inserted at ptr.  The remaining entry will be placed in a new leaf
  and the corresponding ptr to this leaf is returned
  Requires: ptr points to an existing node that is a leaf.
            entry.key and entry.ndptr have a value.
	    dir file is open
*/

{
    char k1[3],  /*key one*/
         p1[3],  /*pointer one*/
         k2[3],  /*key two*/
         p2[3],  /*pointer two*/
         eptr[3],/*entry pointer*/
	 node[16];
    int newptr, tmp;

    fflush(dir);
    fseek(dir, (ptr * 16), 0);
    fgets(node, 16, dir);
    get_field(k1, node, 3);
    get_field(p1, node, 6);
    get_field(k2, node, 9);
    get_field(p2, node, 12);
    num_to_str(eptr, entry.ndptr);
    fflush(dir);
    fseek(dir, (ptr * 16), 0);
    if (strcmp(entry.key, k1) < 0)  /* NODE1=> entry.key eptr k1 p1 */
    {                               /* NODE2=> k2 p2                */
        fprintf(dir, "   %s%s%s%s\n", entry.key, eptr, k1, p1);
        fseek(dir, 0, 2);
        newptr = ftell(dir) / 16;

        fprintf(dir, "   %s%s      \n", k2, p2);
        tmp = ftell(dir) / 16;
    }
    else
    {
        if (strcmp(entry.key, k2) > 0)   /* NODE1=> k1 p1 entry.key eptr */
        {                                /* NODE2=> k2 p2                */
            fseek(dir, 0, 2);
            newptr = ftell(dir) / 16;
            fprintf(dir, "   %s%s      \n", entry.key, eptr);
        }
        else                              /* NODE1=> k1 p1 k2 p2 */
        {                                 /* NODE2=> entry.key eptr*/
            fseek(dir, 9 + (ptr * 16), 0);
            fprintf(dir, "%s%s\n", entry.key, eptr);
            fseek(dir, 0, 2);
            newptr = ftell(dir) / 16;
            fprintf(dir, "   %s%s      \n", k2, p2);
        }
    }

    return newptr;
}

void *split_node(int ndptr, ENTRY_TYPE entry, char newkey[3], int *newptr)
/*
  given the ponter to the leaf and the entry to be inserted this will
  split the node where the first node (in alphabetic ordrer) will
  be inserted at ptr.  The last entry will be placed in a new node where
  with appropriat pointers and the remaining key will be stored in newkey
  and the pointer to newptr.  
  Requires: ndptr points to an existing node that is not a leaf.
            entry.key and entry.ndptr have a value.
	    dir file is open
*/

{
    char k1[3], p1[3], k2[3], p2[3], eptr[3], ptr[3], node[16];
    int newnde;

    fflush(dir);
    fseek(dir, (ndptr * 16), 0);
    fgets(node, 16, dir);
    get_field(k1, node, 3);
    get_field(p1, node, 6);
    get_field(k2, node, 9);
    get_field(p2, node, 12);
    fflush(dir);
    num_to_str(eptr, entry.ndptr);
    if (strcmp(entry.key, k1) < 0)
    {
        fseek(dir, 3 + (ndptr * 16), 0);
        fprintf(dir, "%s%s      \n", entry.key, eptr);
        fseek(dir, 0, 2);
        *newptr = ftell(dir) / 16;
        strcpy(newkey, k1);
        fprintf(dir, "%s%s%s      \n", p1, k2, p2);
    }
    else
    {
        if (strcmp(entry.key, k2) > 0)
        {

            fseek(dir, 9 + (ndptr * 16), 0);
            fprintf(dir, "      \n");
            fseek(dir, 0, 2);
            *newptr = ftell(dir) / 16;
            strcpy(newkey, k2);
            fprintf(dir, "%s%s%s      \n", p2, entry.key, eptr);
        }
        else
        {
            fseek(dir, 9 + (ndptr * 16), 0);
            fprintf(dir, "      \n");
            fseek(dir, 0, 2);
            *newptr = ftell(dir) / 16;
            strcpy(newkey, entry.key);
            fprintf(dir, "%s%s%s      \n", eptr, k2, p2);
        }
    }
}


void add_entry(ENTRY_TYPE entry, int ndptr)
/*
  given an entry it will be placed at the node pointed to bye ndptr
  Requires:  ndptr has a value not passed EOF
             entry has value
*/

{
    char node[16], k1[3], p1[3], k2[3], p2[3], ptr[3];


    fflush(dir);
    fseek(dir, (ndptr * 16), 0);
    fgets(node, 16, dir);
    get_field(k1, node, 3);
    get_field(p1, node, 6);
    fflush(dir);
    if ((strcmp(entry.key, k1) < 0) || (strcmp(k1, "   ") == 0))
    {                                /* if smaller then k1 */
        fseek(dir, 9 + (ndptr * 16), 0);        /* then move k1 and p1 */
        fprintf(dir, "%s%s\n", k1, p1);
        fseek(dir, 3 + (ndptr * 16), 0);
    }
    else
        fseek(dir, 9 + (ndptr * 16), 0);
    num_to_str(ptr, entry.ndptr);
    fprintf(dir, "%s%s", entry.key, ptr);        /* add new entry */
}

int get_parent(int ndptr, char key[3], int nxtptr)
/*
  given the pointer and key value of a node this function will return the
  pointer of the parent
  Requires:  ndptr and key correspond to the same node that exists
*/

{
    char rec[3], k1[3], k2[3], ptr[3];
    int p0, p1, p2, found = 0;

    while (!found)
    {
        fflush(dir);
        fseek(dir, (nxtptr * 16), 0);
        fgets(rec, 16, dir);
        get_field(ptr, rec, 0);
        p0 = str_to_num(ptr);
        get_field(k1, rec, 3);
        if ((strcmp(key, k1) < 0) || (p0 == -1))
        {
            if ((ndptr == p0) || (p0 == -1))
                found = 1;
            else
                nxtptr = p0;
        }
        else
        {
            get_field(ptr, rec, 6);
            p1 = str_to_num(ptr);
            get_field(k2, rec, 9);
            if ((strcmp(key, k2) < 0) || (strcmp(k2, "   ") == 0))
            {
                if (ndptr == p1)
                    found = 1;
                else
                    nxtptr = p1;
            }
            else
            {
                get_field(ptr, rec, 12);
                p2 = str_to_num(ptr);
                if (ndptr == p2)
                    found = 1;
                else
                    nxtptr = p2;
            }
        }
    }
    return nxtptr;
}

void non_leaf_insert(int ndptr, ENTRY_TYPE entry)
/*
  given the entry this function will insert the non-leaf node at nptr
  Requires:  entry is represents a non-leaf
             ndptr < EOF
	     dir is open
*/
{
    char node[16], k2[3], rkey[3], sptr[3];
    int newptr, rt, newrt, Pptr;

    fflush(dir);
    fseek(dir, (ndptr * 16), 0);
    fgets(node, 16, dir);
    get_field(k2, node, 9);

    if (strcmp(k2, "   ") == 0)
        add_entry(entry, ndptr);
    else
    {
        split_node(ndptr, entry, rkey, &newptr);        /* remaining key and ptr
                                                         * to new node */
        switch (roottype)
        {
        case 'C':
            rt = Croot;
            break;                /* get the appropriate root */
        case 'S':
            rt = Sroot;
        }

        if (ndptr == rt)
        {                        /* if at root */
            fflush(dir);
            fseek(dir, 0, 2);
            num_to_str(sptr, ndptr);
            newrt = ftell(dir) / 16;
            fprintf(dir, "%s           \n ", sptr);        /* add new root */
            Pptr = newrt;
            switch (roottype)
            {                        /* assign new root */
            case 'C':
                Croot = newrt;
                break;
            case 'S':
                Sroot = newrt;
                break;
            }
        }
        else
            Pptr = get_parent(ndptr, k2, rt);

        strcpy(entry.key, rkey);
        entry.ndptr = newptr;
        non_leaf_insert(Pptr, entry);

    }
}


void b_insert(ENTRY_TYPE entry)
/*
   given an entry this routine will insert it into a B+tree
   Requires:  entry.key has a value
              dir is open

 */

{
    int ptr, newptr, Pptr, rt;
    char node[16], p0[3], k2[3], skey[3];

    ptr = b_find(entry);
    fflush(dir);
    fseek(dir, (ptr * 16), 0);
    fgets(node, 16, dir);
    get_field(k2, node, 9);
    if (strcmp(k2, "   ") == 0)
        add_entry(entry, ptr);
    else
    {
        newptr = split_leaf(ptr, entry);

        switch (roottype)
        {
        case 'C':
            rt = Croot;
            break;                /* get the appropriate root */
        case 'S':
            rt = Sroot;
        }

        get_smallkey(newptr, skey);
        get_field(p0, node, 0);
        if ((ptr == rt) && (strcmp(p0, "   ") == 0))
        {                        /* then root is leaf */
            fflush(dir);
            fseek(dir, 0, 2);
            rt = ftell(dir) / 16;
            fprintf(dir, "000%s001      \n", skey);
            switch (roottype)
            {
            case 'C':
                Croot = rt;
                break;                /* get the appropriate root */
            case 'S':
                Sroot = rt;
            }
        }
        else
        {
            Pptr = get_parent(ptr, entry.key, rt);
            strcpy(entry.key, skey);
            entry.ndptr = newptr;
            non_leaf_insert(Pptr, entry);
        }
    }
}

void add_tolst(char key[2], int ptr)
/*
   given the key this routine will insert it into the end of the linked list
   ptr has the beging value for the list of that key
   Requires:key has a 2 byte value
            in_lst is open
	    ptr points to beging of the required list
*/
   
{
    int nxt = 0, last;
    char pstr[3];
    last = ptr;
    while (ptr != -1)
    {
        fflush(in_lst);
        if ((fseek(in_lst, (ptr * 6) + 2, 0)) != 0)
            printf("fseek error\n"), exit(1);
        if ((fgets(pstr, 4, in_lst)) == NULL)
            printf("fgets got NULL\n"), exit(1);
        fflush(in_lst);
        last = ptr;
        ptr = nxt = str_to_num(pstr);
    }
    fflush(in_lst);
    fseek(in_lst, 0, 2);
    nxt = ftell(in_lst) / 6;
    fprintf(in_lst, "%s   \n", key);
    fflush(in_lst);
    fseek(in_lst, (last * 6) + 2, 0);
    num_to_str(pstr, nxt);
    fprintf(in_lst, "%s\n", pstr);
    fflush(in_lst);
}

int lst_insert(char key[2], char skey[3])
/*given the key this routine will insert the key to the lst and if the
  key is entered for the first time the address for the key is returned
  else -1 is returned
  Requires:  key and skey have a three byte value
             dir is open
*/
{
    char sk1[3], sk2[3], bptr[3], node[16];
    int pos, dup, lptr;
    ENTRY_TYPE entry;

    strcpy(entry.key, skey);
    pos = b_find(entry);
    fflush(dir);
    fseek(dir, (pos * 16), 0);
    if ((fgets(node, 16, dir)) == NULL)
        printf("lst_insert fgets read NULL\n"),exit(1) ;
    get_field(sk1, node, 3);
    get_field(sk2, node, 9);
    if (strcmp(sk1, skey) == 0)
    {
        get_field(bptr, node, 6);
        lptr = str_to_num(bptr);
        add_tolst(key, lptr);
        return -1;
    }
    else
    {
        if (strcmp(sk2, skey) == 0)
        {
            get_field(bptr, node, 12);
            lptr = str_to_num(bptr);
            add_tolst(key, lptr);
            return -1;
        }
        else
        {
            fflush(in_lst);
            fseek(in_lst, 0, 2);
            lptr = ftell(in_lst) / 6;
            fprintf(in_lst, "%s   \n", key);
            return lptr;
        }
    }
}


void build_btree(FILE * in, int sec_key_ind)
/*given the input file in this routine will bulid the accession list and
  appropriate directories for the secondary keys.  sec_key_ind should have
  the index in the record where the secondary key is located
  Requires:  in is open
             dir is open
*/

{
    char line[16], key[3], mkey[2];
    ENTRY_TYPE entry;
    int lptr;

    if ((fgets(line, 13, in)) == NULL)
        printf("fgets encountered nulls in build_tree, aborting\n"),exit(1);
    strncpy(mkey, line + 1, 2);
    mkey[2] = '\0';                /* get first master key */
    fseek(in_lst, 0, 2);
    fprintf(in_lst, "%s   \n", mkey);        /* put first record in list */
    get_field(key, line, sec_key_ind);
    fprintf(dir, "   %s000      \n", key);
    while ((fgets(line, 13, in)) != NULL)
    {
        strncpy(mkey, line + 1, 2);
        mkey[2] = '\0';
        get_field(entry.key, line, sec_key_ind);
        lptr = lst_insert(mkey, entry.key);

        if (lptr != -1)
        {
            entry.ndptr = lptr;
            b_insert(entry);
        }
    }
}

