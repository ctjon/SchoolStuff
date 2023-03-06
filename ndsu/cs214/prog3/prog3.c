/*-------------------------------------------------------------------------+
 |                                                                         |
 |  PROGRAM 3                                                              |
 |  WRITTEN BY: CHRISTOPHER C. TJON                                        |
 |  FOR DR. ERICKSON'S CS214                                               |
 |  20 APRIL 1990                                                          |
 |                                                                         |
 |  This program amounts to nothing more than a simple database capable of |
 |  storing a simple list of words.  There are four options for the user.  |
 |                                                                         |
 |               1: Create the list (only done once)                       |
 |               2: Add a word to the list                                 |
 |               3: Delete a word from the list                            |
 |               4: Write the list out to the screen                       |
 |               5: Exit                                                   |
 |                                                                         |
 +-------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#define LENGTH 80

struct node {
	      char word[LENGTH];
	      struct node *left;
	      struct node *right;
	      };


/*----< Procedure Add Node >------------------------------------------------*/

struct node *add_node(tree,item)
 struct node *tree;
 char item[LENGTH];
{
	      if (tree==NULL)
		   { tree = (struct node *) malloc(sizeof(struct node));
                     strcpy(tree->word,item);
                     tree->right = NULL;
                     tree->left = NULL; }
              else if (strcmp(item,tree->word) < 0)
                     tree->left = add_node(tree->left,item);
              else
                     tree->right = add_node(tree->right,item);
              return(tree);
}


/*----< Procedure Delete Node >--------------------------------------------*/
struct node *delete_node(tree,item) 
 struct node *tree;
 char *item; {

 struct node *save, *pred;

 if ( tree == NULL)
        return(NULL); 
 else if (strcmp(item,tree->word) == 0)
        { if (tree->left == NULL) {
             save = tree;
             tree = tree->right; 
             free(save);
             return(tree); }          
          else if (tree->right == NULL) {
             save = tree;
             tree = tree->left;
             free(save); 
             return(tree); }
          else { pred = tree->left;
                 while (pred->right != NULL) 
                      pred = pred->right;
                 strcpy(tree->word,pred->word);
                 tree->left = delete_node(tree->left,tree->word); }
        }                   
else if (strcmp(tree->word,item) > 0)
      tree->left = delete_node(tree->left,item);
else  tree->right = delete_node(tree->right,item);
  return(tree);
}


/*----< Procedure Print Tree >---------------------------------------------*/

void print_tree(p) 
struct node *p;
{
	       if (p != NULL) {
		     print_tree(p->left);
		     printf("%s\n",p->word);
		     print_tree(p->right);
		    }
	     }


/*----< Main Program >------------------------------------------------------*/

main() {
char choice, item[LENGTH];
struct node *tree;
	 for (;;) {
                   choice = getchar();
		   if (choice == '1') {
			tree = NULL;
                        printf("Tree Initialized\n"); }
		   else if (choice == '2') {
                        printf("add ? ");
                        gets(item);
                        gets(item);
			tree = add_node(tree,item); }
		   else if (choice == '3'){
                        printf("delete ? ");
                        gets(item);
                        gets(item);
			tree = delete_node(tree,item); }
		   else if (choice == '4') {
                        printf("printing\n");
			print_tree(tree); }
                   else if (choice == '5') exit();
	 }
}

