/* LIST.C */

#include <stdio.h>

#ifdef __MSDOS__
#include <alloc.h>
#endif

#include "debug.h"
#include "list.h"
#include "util.h"

LIST *create_list(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: list                                                               |
| EFFECTS: initializes an empty list                                           |
+-----------------------------------------------------------------------------*/
{
    return (NULL);
}

LIST *add_node(LIST * list, int size, void *data)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: adds a node containing data at the current position in the list     |
+-----------------------------------------------------------------------------*/
{
    LIST *save;

    save = list;
    if ((list = (LIST *) malloc(sizeof(LIST))) == NULL)
	list_error("add_node - out of memory - halting"), exit(1);
    list->size = size;
    if ((list->data = (void *) malloc(size)) == NULL)
	list_error("add_node - out of memory - halting"), exit(1);
    debug("add_node - adding -> [%s]", data);
    memcpy(list->data, data, size);
    list->next = save;
    return (list);
}

LIST *insert_at_front(LIST * list, int size, void *data)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: adds a node containing data at the front of the list                |
+-----------------------------------------------------------------------------*/
{
    return (add_node(list, size, data));
}

LIST *insert_at_end(LIST * list, int size, void *data)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: adds a node containing data at the end of the list                  |
+-----------------------------------------------------------------------------*/
{
    if (list_is_empty(list))
    {
	debug("calling add_node to add [%s] to list", data);
	list = add_node(list, size, data);
    }
    else
    {
	debug("bypassing [%s] to add [%s] to list", list->data, data);
	list->next = insert_at_end(list->next, size, data);
    }
    return (list);

}

LIST *insert_after_Nth(LIST * list, int size, int n, void *data)
/*-----------------------------------------------------------------------------+
| REQUIRES: the list has been initialized and is at least n nodes long         |
| MODIFIES: list                                                               |
| EFFECTS: inserts data after the Nth node of the list                         |
+-----------------------------------------------------------------------------*/
{
    if ((n < 1) || list_is_empty(list))
	list_error("insert_after_Nth - list lenght < 1 or NULL");
    else
    {
	if (n == 1)
	{
	    list->next = add_node(list->next, size, data);
	    debug("insert_after_Nth - inserting Nth node");
	}
	else
	{
	    debug("insert_after_Nth - bypassing -> [%s]", list->data);
	    list->next = insert_after_Nth(list->next, size, n - 1, data);
	}
    }
    return (list);
}

LIST *insert_after_item(LIST * list, int size, void *item, void *data)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized and item is an element of list           |
| MODIFIES: list                                                               |
| EFFECTS: adds data after first occurance of item in the list                 |
+-----------------------------------------------------------------------------*/
{
    if (list_is_empty(list))
	list_error("insert_after_item - item specified is not in list");
    else
    {
	if (memcmp(list->data, item, size) == 0)
	{
	    debug("insert_after_item - found it [%s]", list->data);
	    list->next = add_node(list->next, size, data);
	}
	else
	{
	    debug("insert_after_item - bypassing [%s]", list->data);
	    list->next = insert_after_item(list->next, size, item, data);
	}
    }
    return (list);
}

BOOLEAN is_in_list(LIST * list, void *data, int size)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: returns TRUE(1) if data is in list, FALSE (0) otherwise             |
+-----------------------------------------------------------------------------*/
{
    if (list_is_empty(list))
	return (FALSE);
    else
    {
	if (memcmp(list->data, data, size) == 0)
	{
	    debug("is_in_list - found [%s]", list->data);
	    return (TRUE);
	}
	else
	{
	    debug("is_in_list - looking at [%s]", list->data);
	    return (is_in_list(list->next, data, size));
	}
    }
}

LIST *delete_item(LIST * list, void *data, int size)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: deletes the node that contains first occurance of data from the list|
+-----------------------------------------------------------------------------*/
{
    if (list_is_empty(list))
    {
	debug("delete_item - [%s] not found in list", data);
    }
    else if (memcmp(list->data, data, size) == 0)
    {
	debug("delete_item - found [%s] and deleting", data);
	delete_node(list);
	list = list->next;
    }
    else
	list->next = delete_item(list->next, data, sizeof(data));
    return (list);
}

LIST *next_node(LIST * list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: returns a pointer to the next node on the list                      |
+-----------------------------------------------------------------------------*/
{
    return (list->next);
}

void *node_item(LIST * list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: returns a pointer to the next node on the list                      |
+-----------------------------------------------------------------------------*/
{
    return (list->data);
}

LIST *get_item_node(LIST * list, void *data, int size)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: returns the node that contains first occurance of data from the list|
+-----------------------------------------------------------------------------*/
{
    /* THIS DOES NOT WORK RIGHT YET */
    LIST *node;
    if (list_is_empty(list))
    {
	debug("get_item_node - [%s] not found in list", data);
	return (NULL);
    }
    else if (memcmp(list->data, data, size) == 0)
    {
	debug("get_item_node - found [%s] an returning node", list->data);
	memcpy(node, list, sizeof(list));
	return (node);
    }
    else
	list->next = get_item_node(node->next, data, sizeof(data));
}

LIST *delete_node(LIST * list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: deletes the node at the current position in the list                |
+-----------------------------------------------------------------------------*/
{

    LIST *save;

    debug("delete_node - deleting node containing [%s]", list->data);
    save = list;
    list = list->next;
    free(save);
    return (list);
}

LIST *delete_Nth(LIST * list, int n)
/*-----------------------------------------------------------------------------+
| REQUIRES: 0 < N <= list_length(list)                                         |
| MODIFIES: list                                                               |
| EFFECTS: deletes the Nth element of the list                                 |
+-----------------------------------------------------------------------------*/
{
    if (list_is_empty(list))
	list_error("delete_Nth - attempt to delete a non-existing Nth element");
    else
    {
	if (n == 1)
	{
	    debug("delete_Nth - deleting %dth node containing [%s]", n, list->data);
	    list = delete_node(list);
	}
	else
	{
	    debug("delete_Nth - bypassing %dth node containing [%s]", n, list->data);
	    list->next = delete_Nth(list->next, n - 1);
	}
    }
    return (list);
}

BOOLEAN list_is_empty(LIST * list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: returns TRUE(1) if the list is empty, FALSE(0) otherwise            |
+-----------------------------------------------------------------------------*/
{
    if (list == NULL)
    {
	return (TRUE);
    }
    else
    {
	return (FALSE);
    }
}

int list_length(LIST * list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: nothing                                                            |
| EFFECTS: returns the number of nodes in the list                             |
+-----------------------------------------------------------------------------*/
{
    if (list_is_empty(list))
	return (0);
    else
	return (1 + (list_length(list->next)));
}

LIST *destroy_list(LIST * list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: list                                                               |
| EFFECTS: destroys the list and leaves list as a pointer to an empty list     |
+-----------------------------------------------------------------------------*/
{
    register long int i = 1;

    while (!(list_is_empty(list)))
    {
	debug("destroy_list - deleting node #%ld containing [%s]", i++, list->data);
	list = delete_node(list);
    }
    return (list);
}

LIST *replicate_list(LIST * old_list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized                                          |
| MODIFIES: new_list                                                           |
| EFFECTS: completely replicates the old_list in a structure called new_list   |
+-----------------------------------------------------------------------------*/
{
    LIST *new_list;

    if (list_is_empty(old_list))
	new_list = create_list();
    else
    {
	debug("replicating node containing [%s]", old_list->data);
	new_list = add_node(NULL, old_list->size, old_list->data);
	new_list->next = replicate_list(old_list->next);
    }
    return (new_list);
}

LIST *concat_list(LIST * left_list, LIST * right_list)
/*-----------------------------------------------------------------------------+
| REQUIRES: lists have been initialized                                        |
| MODIFIES: left_list                                                          |
| EFFECTS: concatenates the right list to the end of the left list             |
+-----------------------------------------------------------------------------*/
{
    LIST *list;

    if (list_is_empty(right_list))
    {
	debug("concat_list - right list is empty - doing nothing");
	return (left_list);
    }
    else if (list_is_empty(left_list))
    {
	debug("concat_list - left list is empty - assigning right list");
	return (right_list);
    }
    else
    {
	while (!(list_is_empty(right_list)))
	{
	    debug("concat_list - adding [%s] to end of left_list", right_list->data);
	    left_list = insert_at_end(left_list, right_list->size, right_list->data);
	    right_list = right_list->next;

	}
	return (left_list);
    }
}

void list_error(char *error_message)
/*-----------------------------------------------------------------------------+
| REQUIRES: error_message is a valid character string                          |
| MODIFIES: nothing                                                            |
| EFFECTS: Prints an error message to the screen and the error.log             |
+-----------------------------------------------------------------------------*/
{
    FILE *error_log;

    if ((error_log = fopen("error.log", "a")) != NULL)
    {
	fprintf(stderr, "%s\n", error_message);
	fprintf(error_log, "%s\n", error_message);
	fclose(error_log);
    }
    else
	perror("Error opening error log"), exit(1);
}

void dump_list(LIST * list)
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized and list->data is a char                 |
| MODIFIES: nothing                                                            |
| EFFECTS: Prints out the contents of the list from front to back              |
+-----------------------------------------------------------------------------*/
{
    while (!(list_is_empty(list)))
    {
	aprintf("%s\n", (char *) list->data);
	list = next_node(list);
    }
}

void dump_list_to_file(LIST * list, char fname[14])
/*-----------------------------------------------------------------------------+
| REQUIRES: list has been initialized and list->data is a char                 |
| MODIFIES: nothing                                                            |
| EFFECTS: Prints out the contents of the list from front to back to a file    |
+-----------------------------------------------------------------------------*/
{
    FILE *output_file;

    if ((output_file = fopen(fname, "w")) != NULL)
    {
	debug("dumping list to [%s]", fname);
	while (!(list_is_empty(list)))
	{
	    fprintf(output_file, "%s\n", (char *) list->data);
	    list = next_node(list);
	}
	fclose(output_file);
    }
    else
	perror("dump_list_to_file - error opening output_file"), exit(1);
}
