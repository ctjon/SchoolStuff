/* Tree Module */
#include <stdio.h>
#include <string.h>
#include "treeintrn.h"
#include "soundex.h"

void dump_tree ();
int tab = 0;


struct node *add_avl_node (tree, return_balance, word)
/*-----------------------------------------------------------------------------+
| requires - tree has been initialized                                         |
| modifies - tree                                                              |
| effects  - adds a node to tree while maintaining AVL standards               |
+-----------------------------------------------------------------------------*/
struct node *tree;
int *return_balance;
char word[80];
{
	if (tree_is_empty (tree))
	  {
		  tree = (struct node *) malloc (sizeof (struct node));

		  tree->left = tree->right = NULL;
		  tree->balance = 0;
		  strcpy (tree->word, word);
		  *return_balance = 1;
	  }
	else
	  {
		  if (strcmp (word, tree->word) < 0)
		    {
			    tree->left = add_avl_node (tree->left,
						       return_balance, word);
			    tree->balance -= (*return_balance);
		    }
		  else if (strcmp (word, tree->word) > 0)
		    {
			    tree->right = add_avl_node (tree->right,
						      return_balance, word);
			    tree->balance += (*return_balance);
		    }
		  else if (strcmp (word, tree->word) == 0)
		    {
			    *return_balance = 0;
		    }
		  if (tree->balance < -1 || tree->balance > 1)
		    {
			    if (tree->balance < -1)
			      {	/* Rotate Right */
				      if (tree->left->balance < 0)
					      tree = rotate_right (tree);
				      else
					{
						tree->left = rotate_left (tree->left);
						tree = rotate_right (tree);
					}
			      }
			    else if (tree->balance > 1)
			      {	/* Rotate Left */
				      if (tree->right->balance > 0)
					      tree = rotate_left (tree);
				      else
					{
						tree->right = rotate_right (tree->right);
						tree = rotate_left (tree);
					}
			      }
			    *return_balance = 0;
			    tree->balance = 0;
		    }
		  else
			  *return_balance = abs (tree->balance);
	  }
	return (tree);
}


struct node *add_node (tree, word)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - inserts node containing *word in tree.                            |
+-----------------------------------------------------------------------------*/
struct node *tree;
char word[];

{
	if (tree_is_empty (tree))
	  {
		  tree = (struct node *) malloc (sizeof (struct node));

		  strcpy (tree->word, word);
		  tree->left = tree->right = NULL;
	  }
	else if (strcmp (word, word_of (tree)) < 0)
		tree->left = add_node (tree->left, word);
	else
		tree->right = add_node (tree->right, word);
	return (tree);
}


struct node *create_tree ()
/*-----------------------------------------------------------------------------+
| requires - nothing                                                           |
| modifies - tree                                                              |
| effects  - initializes the tree                                              |
+-----------------------------------------------------------------------------*/
{
	struct node *tree;

	tree = NULL;
	return (tree);
}


struct node *delete_node (tree, word)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - deletes node containing *word from tree                           |
+-----------------------------------------------------------------------------*/
struct node *tree;
char word[];
{
	struct node *temp, *pred;

	if (tree_is_empty (tree))
		return (NULL);
	else if (strcmp (word, word_of (tree)) == 0)
	  {
		  if (tree->left == NULL)
		    {
			    temp = tree;
			    tree = tree->right;
			    free (temp);
			    return (tree);
		    }
		  else if (tree->right == NULL)
		    {
			    temp = tree;
			    tree = tree->left;
			    free (temp);
			    return (tree);
		    }
		  else
		    {
			    pred = find_predecessor (tree);
			    strcpy (tree->word, pred->word);
			    tree->left = delete_node (tree->left, word);
		    }
	  }
	else if (strcmp (word, word_of (tree)) < 0)
		tree->left = delete_node (tree->left, word);
	else
		tree->right = delete_node (tree->right, word);
	return (tree);
}

void delete_tree (tree)
/*-----------------------------------------------------------------------------+| requires - the tree has been initialized                                     |
| modifies - tree                                                              |
| effects  - destroys the tree                                                 |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	if (tree_is_empty (tree))
		return;
	delete_tree (tree->left);
	delete_tree (tree->right);
	free (tree);
}

void dump_tree (tree, tab)
/*-----------------------------------------------------------------------------+
| requires - tree has been initialized                                         |
| modifies - nothing                                                           |
| effects  - prints out a complete view of the tree structure to include the   |
|            the contents of the nod, the balance factor and the level of the  |
|            node.  This view is rotated 90 degrees to the left to accomodate  |
|	     deep trees                                                        |
+-----------------------------------------------------------------------------*/
struct node *tree;
int tab;

{
	register int i;

	if (!tree_is_empty (tree))
	  {
		  dump_tree (tree->right, tab + 1);
		  for (i = 0; i < tab; i++)
			  printf ("   ");
		  printf ("%s:%i:l=%i\n", word_of (tree), tree->balance, tab);
		  dump_tree (tree->left, tab + 1);
	  }
	else
	  {
		  for (i = 0; i < tab; i++)
			  printf ("   ");
		  printf ("---\n");
	  }
}


struct node *find_predecessor (tree)
/*-----------------------------------------------------------------------------+
| requires - tree has been initialized                                         |
| modifies - nothing                                                           |
| effects  - returns the the rightmost node in the left subtree of the node we |
|            seek to delete                                                    |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	struct node *pred;

	pred = tree->left;
	while (pred->right != NULL)
		pred = pred->right;
}

int height (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns the height of the tree	                               |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	if (tree_is_empty (tree))
		return (0);
	else
		return (1 + max (height (tree->left), height (tree->right)));
}

void searching_traverse (tree, sword)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - does an inorder traversal of tree                                 |
+-----------------------------------------------------------------------------*/
struct node *tree;
char *sword;

{

	char temp[80];

	if (!tree_is_empty (tree))
	  {
		  searching_traverse (tree->left, sword);
		  strcpy (temp, soundex_rep_of (tree->word));
		  if (strcmp (sword, temp) == 0)
			  printf ("%s\n", tree->word);
		  searching_traverse (tree->right, sword);
	  }
}


void inorder_traverse (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - does an inorder traversal of tree                                 |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	if (!tree_is_empty (tree))
	  {
		  inorder_traverse (tree->left);
		  printf ("%s\n", word_of (tree));
		  inorder_traverse (tree->right);
	  }
}


int is_in (tree, word)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns 1 if *word is in the tree else returns 0                  |
+-----------------------------------------------------------------------------*/
struct node *tree;
char word[];

{
	if (tree_is_empty (tree))
		return (FALSE);
	else if (strcmp (word, word_of (tree)) == 0)
		return (TRUE);
	else if (strcmp (word, word_of (tree)) < 0)
		return (is_in (tree->left, word));
	else
		return (is_in (tree->right, word));
}

int node_count (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns the number of nodes in tree                               |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	if (tree_is_empty (tree))
		return (0);
	else
		return (1 + node_count (tree->left) + node_count (tree->right));
}

void postorder_traverse (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - does a postorder traversal of tree                                |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	if (!tree_is_empty (tree))
	  {
		  postorder_traverse (tree->left);
		  postorder_traverse (tree->right);
		  printf ("%s\n", word_of (tree));
	  }
}


void preorder_traverse (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - does a preorder traversal of tree                                 |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	if (!tree_is_empty (tree))
	  {
		  printf ("%s\n", word_of (tree));
		  preorder_traverse (tree->left);
		  preorder_traverse (tree->right);
	  }
}


struct node *rotate_left (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - rotates the tree to the left                                      |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	struct node *temp;

	temp = tree;
	tree = tree->right;
	temp->right = tree->left;
	tree->left = temp;
	tree->balance = 0;
	temp->balance = 0;
	return tree;
}


struct node *rotate_right (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - the tree                                                          |
| effects  - rotates the tree to the right                                     |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	struct node *temp;

	temp = tree;
	tree = tree->left;
	temp->left = tree->right;
	tree->right = temp;
	tree->balance = 0;
	temp->balance = 0;
	return tree;
}

int same_tree (tree1, tree2)
/*-----------------------------------------------------------------------------+
| requires - tree1 and tree2 are valid binary trees                            |
| modifies - nothing                                                           |
| effects  - returns TRUE(1) if the tree1 and tree2 are identical else FALSE(0)|
+-----------------------------------------------------------------------------*/
struct node *tree1, *tree2;

{
	if (tree_is_empty (tree1) && tree_is_empty (tree2))
		return (TRUE);
	else if (tree_is_empty (tree1) || tree_is_empty (tree2))
		return (FALSE);
	else if (strcmp (tree1->word, tree2->word) != 0)
		return (FALSE);
	else
		return (same_tree (tree1->left, tree2->left)
			&& same_tree (tree1->right, tree2->right));
}

void save_tree (save_file, tree)
/*-----------------------------------------------------------------------------+
| requires - *tree has been initialized and *save_file has been opened         |
| modifies - save_file                                                         |
| effects  - saves a copy of the tree to a file                                |
+-----------------------------------------------------------------------------*/
FILE *save_file;
struct node *tree;

{
	if (!tree_is_empty (tree))
	  {
		  save_tree (save_file, tree->left);
		  save_tree (save_file, tree->right);
		  fprintf (save_file, "%s\n", word_of (tree));
	  }
}


int tree_is_empty (tree)
/*-----------------------------------------------------------------------------+
| requires - tree has been initialized                                         |
| modifies - nothing                                                           |
| effects  - returns 1 if tree is empty else 0                                 |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	return (tree == NULL);
}

char *word_of (tree)
/*-----------------------------------------------------------------------------+
| requires - the tree has been initialized                                     |
| modifies - nothing                                                           |
| effects  - returns the word at a given node                                  |
+-----------------------------------------------------------------------------*/
struct node *tree;

{
	return (tree->word);
}

/*----< Local Functions >-----------------------------------------------------*/


int max (a, b)
/*-----------------------------------------------------------------------------+
| requires - a and b are valid integers                                        |
| modifies - nothing                                                           |
| effects  - compares a and b and returns the maximum value                    |
+-----------------------------------------------------------------------------*/
int a, b;
{
	if (a > b)
		return (a);
	else
		return (b);
}
