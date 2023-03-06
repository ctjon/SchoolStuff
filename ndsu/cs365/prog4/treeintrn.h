/* Tree Module */
#ifndef __TREEINTRNH__
#define __TREEINTRNH__
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

struct node
{
	char word[80];		/* Word				 */
	int balance;		/* Depth (for balancing)	 */
	struct node *left;
	struct node *right;
};

int *return_balance;


struct node *add_avl_node ();

/*-----------------------------------------------------------------------------+
| requires - tree has been initialized                                         |
| modifies - tree                                                              |
| effects  - adds a node to tree while maintaining AVL standards               |
+-----------------------------------------------------------------------------*/


struct node *add_node ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - inserts node containing *word in tree.                            |
+-----------------------------------------------------------------------------*/


struct node *create_tree ();

/*-----------------------------------------------------------------------------+
| requires - nothing                                                           |
| modifies - tree                                                              |
| effects  - initializes the tree                                              |
+-----------------------------------------------------------------------------*/


struct node *delete_node ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - deletes node containing *word from tree                           |
+-----------------------------------------------------------------------------*/


void delete_tree ();

/*-----------------------------------------------------------------------------+| requires - the tree has been initialized                                     |
| modifies - tree                                                              |
| effects  - destroys the tree                                                 |
+-----------------------------------------------------------------------------*/


struct node *find_predecessor ();

/*-----------------------------------------------------------------------------+
| requires - tree has been initialized                                         |
| modifies - nothing                                                           |
| effects  - returns the the rightmost node in the left subtree of the node we |
|            seek to delete                                                    |
+-----------------------------------------------------------------------------*/


int height ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns the height of the tree	                               |
+-----------------------------------------------------------------------------*/


void inorder_traverse ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - does an inorder traversal of tree                                 |
+-----------------------------------------------------------------------------*/


int is_in ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns 1 if *word is in the tree else returns 0                  |
+-----------------------------------------------------------------------------*/


int node_count ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns the number of nodes in tree                               |
+-----------------------------------------------------------------------------*/


void postorder_traverse ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - does a postorder traversal of tree                                |
+-----------------------------------------------------------------------------*/


void preorder_traverse ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - does a preorder traversal of tree                                 |
+-----------------------------------------------------------------------------*/


struct node *rotate_left ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - rotates the tree to the left                                      |
+-----------------------------------------------------------------------------*/


struct node *rotate_right ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - rotates the tree to the right                                     |
+-----------------------------------------------------------------------------*/


int same_tree ();

/*-----------------------------------------------------------------------------+
| requires - tree1 and tree2 are valid binary trees                            |
| modifies - nothing                                                           |
| effects  - returns TRUE(1) if the tree1 and tree2 are identical else FALSE(0)|
+-----------------------------------------------------------------------------*/


void save_tree ();

/*-----------------------------------------------------------------------------+
| requires - *tree has been initialized and *save_file has been opened         |
| modifies - save_file                                                         |
| effects  - saves a copy of the tree to a file                                |
+-----------------------------------------------------------------------------*/


int tree_is_empty ();

/*-----------------------------------------------------------------------------+
| requires - tree has been initialized                                         |
| modifies - nothing                                                           |
| effects  - returns 1 if tree is empty else 0                                 |
+-----------------------------------------------------------------------------*/


char *word_of ();

/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns the word at a given node                                  |
+-----------------------------------------------------------------------------*/


#endif				/* __TREEINTRNH__ */
