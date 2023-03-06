#include  <stdio.h> 
#include  "loader.h"
#include  "memory.h"
#include  "bus.h"

int main(int argc, char *argv[]) {

    char *input_file ;
    unsigned int *offset ;
    
    if (argc == 3) 
       {  offset = (unsigned int *) atoi(argv[2]) ; 
	  input_file = *++argv ;
	  printf("opening %s \n",input_file) ;
	  printf("sending offset %d\n",offset)  ;
	  load(input_file, offset) ;
	  processor();
       }		
    else printf("file not opened\n") ;

}
