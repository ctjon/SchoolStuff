/* LIST.H */

#ifndef __LIST_H__
#define __LIST_H__

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef int BOOLEAN;

typedef struct list_node
{
    void *data;
    int size;
    struct list_node *next;
}         LIST;

LIST *create_list(void);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: list                                                               |
| EFFECTS: initializes an empty list                                           |
+-----------------------------------------------------------------------------*/

LIST *add_node(LIST * list, int size, void *data);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: adds a node containing data at the current position in the list     |
+-----------------------------------------------------------------------------*/

LIST *insert_at_front(LIST * list, int size, void *data);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: adds a node containing data at the front of the list                |
+-----------------------------------------------------------------------------*/

LIST *insert_at_end(LIST * list, int size, void *data);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: adds a node containing data at the end of the list                  |
+-----------------------------------------------------------------------------*/

LIST *insert_after_Nth(LIST * list, int size, int n, void *data);
/*-----------------------------------------------------------------------------+
| REQUIRES: the list has been initialized and is at least n nodes long         |
| MODIFIES: list                                                               |
| EFFECTS: inserts data after the Nth node of the list                         |
+-----------------------------------------------------------------------------*/

LIST *insert_after_item(LIST * list, int size, void *item, void *data);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized and item is an element of list           |
| MODIFIES: list                                                               |
| EFFECTS: adds data after first occurance of item in the list                 |
+-----------------------------------------------------------------------------*/

BOOLEAN is_in_list(LIST * list, void *data, int size);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: returns TRUE(1) if data is in list, FALSE (0) otherwise             |
+-----------------------------------------------------------------------------*/

LIST *delete_item(LIST * list, void *data, int);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: deletes the node that contains first occurance of data from the list|
+-----------------------------------------------------------------------------*/

LIST *next_node(LIST * list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: returns a pointer to the next node on the list                      |
+-----------------------------------------------------------------------------*/

void *node_item(LIST * list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: returns a pointer to the next node on the list                      |
+-----------------------------------------------------------------------------*/

LIST *get_item_node(LIST * list, void *data, int size);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: returns the node that contains first occurance of data from the list|
+-----------------------------------------------------------------------------*/

LIST *delete_node(LIST * list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: deletes the node at the current position in the list                |
+-----------------------------------------------------------------------------*/

LIST *delete_Nth(LIST * list, int n);
/*-----------------------------------------------------------------------------+
| REQUIRES: 0 < N <= list_length(list)                                         |
| MODIFIES: list                                                               |
| EFFECTS: deletes the Nth element of the list                                 |
+-----------------------------------------------------------------------------*/

BOOLEAN list_is_empty(LIST * list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: returns TRUE(1) if the list is empty, FALSE(0) otherwise            |
+-----------------------------------------------------------------------------*/

int list_length(LIST * list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: returns the number of nodes in the list                             |
+-----------------------------------------------------------------------------*/

LIST *destroy_list(LIST * list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: destroys the list and leaves list as a pointer to an empty list     |
+-----------------------------------------------------------------------------*/

LIST *replicate_list(LIST * old_list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: new_list                                                           |
| EFFECTS: completely replicates the old_list in a structure called new_list   |
+-----------------------------------------------------------------------------*/

LIST *concat_list(LIST * left_list, LIST * right_list);
/*-----------------------------------------------------------------------------+
| REQUIRES: lists have been initialized                                        |
| MODIFIES: left_list                                                          |
| EFFECTS: concatenates the right list to the end of the left list             |
+-----------------------------------------------------------------------------*/

void list_error(char *error_message);
/*-----------------------------------------------------------------------------+
| REQUIRES: error_message is a valid character string                          |
| MODIFIES: nothing                                                            |
| EFFECTS: Prints an error message to the screen and the error.log             |
+-----------------------------------------------------------------------------*/

void dump_list(LIST * list);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: Prints out the contents of the list from front to back              |
+-----------------------------------------------------------------------------*/

void dump_list_to_file(LIST * list, char fname[14]);
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: Prints out the contents of the list from front to back to a file    |
+-----------------------------------------------------------------------------*/

#endif				/* __LISTH__ */
