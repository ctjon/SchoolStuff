/*----------------------------------------------------------------------------+
 |                                                                            |
 |  PROGRAM 2                                                                 |
 |  Written By: Christopher C. Tjon                                           |
 |  For Dr. Erickson's CS214                                                  |
 |  NAID# 110975-8                                                            |
 |  6 APR 1990                                                                |
 |                                                                            |
 +----------------------------------------------------------------------------*/

#include  <stdio.h>
#include  <string.h>
#define   OR         ||
#define   AND        &&
#define   BOOLEAN    short
#define   TRUE       1
#define   FALSE      0

/******************************************/
/********   Identities Record   ***********/
/******************************************/
/*  Used to store database of identities  */
/* for reference when main parses input   */
/* program for keywords.                  */
/******************************************/
struct identities {
       char                  id[80], newid[80];
       struct identities     *next;
       };


/******************************************/
/****        Global declarations       ****/
/******************************************/
       typedef   struct identities   RECORD;
			 BOOLEAN   line , blank , printed ;
			 char      word[80];

/******************************************/
/**************   Main   ******************/
/******************************************/
main() {
    struct                identities        ;
    RECORD                *head , *mover    ;
		char                  *termchar ;

/*******************************************/
/*  Establish '$' as the delimiter between */
/* the list of identities and the pgm.     */
/*******************************************/
    termchar = "$" ;

/*******************************************/
/*  Now, read in all identity pairs and    */
/* create a linked-list of record structs  */
/* containing these keywords and their     */
/* replacements.                           */
/*******************************************/
	 head  = (RECORD *) malloc ( sizeof ( RECORD ) ) ;
	 mover = head ;
	 getnextword() ;

	while ( strcmp ( word , termchar ) != 0 ) {
		strcpy ( mover ->id    , word ) ;
		getnextword();
		strcpy ( mover ->newid , word ) ;
		mover->next = (RECORD *) malloc(sizeof(RECORD));
		getnextword() ;
		mover  = mover->next ;
		mover->next = NULL   ;
	}

/*******************************************/
/*  At this point all the identities have  */
/* been read and recorded, so begin        */
/* parsing input pgm, looking for keywords */
/* and replacing those that are found.     */
/* NOTE: Brief description of a few var's  */
/*       -line, blank: used as 'signals'   */
/*         from getnextword function.      */
/*         If getnextword encounters a     */
/*         blank or new-line, it signals   */
/*         blank/line, so that that blank  */
/*         or line can be printed out      */
/*         after the word returned by get- */
/*         nextword() is printed.          */
/*         (a function to 'peek' agead in  */
/*         the input stream would prevent  */
/*         this pblm.                      */
/*******************************************/

printed = FALSE ;
line    = FALSE ;
blank   = FALSE ;
printf ("\n");

while ( word[0] != '\0' ) {

/*******************************************/
/*  Before each word is passed to          */
/* swapidentity it must be checked for     */
/* commenting. If a comment is encountered */
/* no identity verification will be done.  */
/*******************************************/

		swapidentity ( word , head ) ;
    if ( line == TRUE ) { /*******************************/
    printf ("\n");        /*  NOTE: swapidentity() does  */
    }                     /* all printing of words, so   */
    if ( blank == TRUE ) {/* after a word has been prntd */
    printf (" ");         /* the pgm must check to see   */
    }                     /* getnextword() read a blank- */
                          /* or newline char, and if so, */
    line =  FALSE ;       /* it must act accordingly.    */
    blank = FALSE ;       /*******************************/
    printed = FALSE ;
		getnextword() ;
    }
}

/******************************************/
/*********  getnextword function  *********/
/******************************************/
/*  Retrieves next word from the input    */
/* stream and returns a pointer to the    */
/* memory location  'word' where it is    */
/* located.                               */
/******************************************/
getnextword() {

            int                   i ;
						char                  c;

							word[0] = '\0';
              c = getchar();

              while ( c == '\n' OR c == ' ' OR c == '\t' ) {
               printf ( "%c" , c ) ;
               c = getchar();
              }

              if ( c != EOF ) {
                i = 0;
                while ( c != ' ' AND c != '\n' AND c != '\t' AND c != EOF ) {
                  word[i++] = c;
                  c = getchar();
                }

                if ( c == '\n' ) {
                  line = TRUE  ;
                }
                if ( c == ' ' )  {
                  blank = TRUE ;
                }

                word[i] = '\0' ;
							}
       }

/*****************************************/
/**********  swapidentity  ***************/
/*****************************************/
/*  Takes as a parameter a pointer to    */
/* the current word in the input stream  */
/* and checks the list of identities for */
/* any occurances of it. If it is found  */
/* in the identity list, the replacement */
/* is written to the output stream, else */
/* the current word is just echoed to    */
/* the output stream.                    */
/*****************************************/
			 swapidentity( src , list )
					char          *src ;
          RECORD        *list ;
       {
          RECORD        *ptr           ;
          BOOLEAN       DONE = FALSE   ;
          char          c , c1 , inword[80] ;


          ptr    = list ;
					strcpy ( inword , src ) ;
					if ( inword[0] == '/' AND inword[1] == '*'      )  {
               if   ( inword[ strlen( inword ) - 2 ] == '*' AND
                      inword[ strlen( inword ) - 1 ] == '/' )   {
                      printf ( "%s" , inword ) ;
                      DONE = TRUE ;
               }
               else {
                      printf ( "%s" , inword ) ;
                      if ( blank == TRUE ) {
                         printf ( "%c" , ' ' ) ;
                         blank = FALSE ;
                      }
                      do {
                           c  = getchar();
                           c1 = getchar();
                           printf ( "%c%c" , c , c1 ) ;
                      }   while ( c != '/' AND c1 != '/' ) ;
                      DONE = TRUE ;
               }
          }
          else {
            while ( ptr != NULL  AND DONE != TRUE ) {
							if ( strncmp ( ptr -> id , inword,strlen(inword)) == 0 ) {
                 printf("%s " , ptr -> newid ) ;
                 DONE = TRUE ;
							} else {
								ptr = ptr -> next ;
              }
            }
            if ( DONE != TRUE ) {
              printf ( "%s" , inword );
            }
          }  /*  else */
       }     /* swap  */


/*************      end       **************/
