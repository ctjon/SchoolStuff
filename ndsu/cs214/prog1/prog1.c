/*---------------------------------------------------------------------------*
 | PROGRAM 1                                                                 |
 | WRITTEN BY: CHRISTOHER C. TJON                                            |
 | FOR: CS214                                                                |
 | 22 MARCH 1990                                                             |
 |                                                                           |
 | The purpose of this program is to manipulate a list of up to 100 integers |
 | with the following options:                                               |
 |                                                                           |
 |                  1: Read a list of up to 100 integers. The values are     |
 |                     preceded by the number of integers in the set.        |
 |                  2: Display the list sorted in order largest to smallest  |
 |                  3: Display the list sorted in order smallest to largest  |
 |                  4: Display the average of the values                     |
 |                  5: List the values in current order each followed by     |
 |                     how much it differs from the average.                 |
 |                                                                           |
 *---------------------------------------------------------------------------*/

#define ABS(z) (((z) < 0) ? -(z) : (z))
#define BOOLEAN short
#define TRUE 1
#define FALSE 0
#define AND &&
#define OR ||

     int  j,i,nums,choice,sum=0,values[100],amount,temp;
     BOOLEAN entered;

     float average;

/*----< Procedure Print Menu >-----------------------------------------------*/

print_menu() 
{
          printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
               " '0' : EXIT Program",
               " '1' : Enter list ",
               " '2' : Display sorted (ascending)  list ",
               " '3' : Display sorted (descending) list ",
               " '4' : Display Average ",
               " '5' : Display List and corresponding ",
               "       deviation from the average\n ");
}               

/*----<Procedure Enter List >------------------------------------------------*/

enter_list()
{               
               sum = 0;
               entered = TRUE;
               printf("\n Please enter number of Integers you \n");
               printf("  would like to evaluate:   ");
               scanf("%d",&amount);
               printf("\n Now you must enter this many Integers : ");
               for (i = 1; i <= amount; ++i)
               {
                    scanf("%d",&values[i]);
                    values[i] = values[i];
                    sum += values[i];
               }     
}

/*----< Procedure Ascending Display >----------------------------------------*/

ascending_display()
{
               for (i = 1; i < amount; i++)
               {
                    for (j = 1;j < amount; j++)
                    {
                         if (values[j + 1] < values[j]) 
                         {
                              temp = values[j+1];
                              values[j+1] = values[j];
                              values[j] = temp;
                         }
                    }
               }
               printf("\n In ascending order :\n");
               for (i = 1; i <= amount; i++){
                    printf("\n %d",values[i]);
               }
               printf("\n Press <ENTER> to continue \n");
               getchar();
}
               
/*----< Procedure Descending Display >---------------------------------------*/

descending_display()
{
                for (i = 1; i < amount; i++)
                {
                    for (j = 1;j < amount; j++)
                    {
                         if (values[j + 1] > values[j]) 
                         {
                         temp = values[j+1];
                         values[j+1] = values[j];
                         values[j] = temp;
                         }
                    }
                }     
                printf("\n In descending order :\n");
                for (i = 1; i <= amount; i++)
                     printf("\n %d",values[i]);
                printf("\n Press <ENTER> to continue \n");
                getchar();
}
                  
/*----< Procedure Display Average >------------------------------------------*/

display_average()
{
                     average = (float) sum / (float) amount;
                     printf("\n The average is : %f",average);
                     printf("\n Press <ENTER> to continue \n");
                     getchar();
}

/*----< Procedure Display Deviation >----------------------------------------*/

display_deviation()
{
                     printf("\n  VALUE   :   DEVIATION \n\n\n");
                     for (i = 1; i <= amount; i++)
                     {
                          printf("\n         %d      ",values[i]);
                          printf("   %f              ",ABS(values[i]-average));
                     }
                     printf("\n Press <ENTER> to continue \n");
                     getchar();
}
 
/*----< Begin Main >---------------------------------------------------------*/

main()

{
     entered = FALSE;
     while (1) {
          print_menu();
          scanf("%d",&choice);
          if      (choice == 0) exit (0);
          else if (choice == 1) enter_list();
          else if ((choice == 2) AND (entered == TRUE)) ascending_display();
          else if ((choice == 3) AND (entered == TRUE)) descending_display();
          else if ((choice == 4) AND (entered == TRUE)) display_average();
          else if ((choice == 5) AND (entered == TRUE)) display_deviation();
     }
}       
/*----< End Main >-----------------------------------------------------------*/

