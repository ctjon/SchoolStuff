                                              
                                                CHRISTOPHER C. TJON
                                                110975-8
                                                QUESTION: 23 PART: A
                                                PAGE 311
                                                        
A: THE DIAGRAM FOR THE (M,N) MINIMAX TREE WHERE M = 3 AND N = 2 IS AS FOLLOWS:
                                                                             
A'S MOVE                                                 (3,2)  
                    *                             *
                   /                             /                            
B'S MOVE         ( 0 )                         ( 0 )                          
               /     \                /          |       \                    
A'S MOVE    ( 0 )    ( 1 )        ( 1 )        ( 1 )    ( 0 )                 
              |     /    \        /   \        /   \      |                   
B'S MOVE    ( 0 ) ( 1 ) ( 1 )  ( 1 ) ( 0 )  ( 1 ) ( 1 ) ( 0 )                 
                    |     |      |            |     |                         
A'S MOVE          ( 1 ) ( 1 )  ( 1 )        ( 1 ) ( 1 )        
----------------------------------------------------------------------------------
                                             *
                                             |
B'S MOVE                                   ( 0 )  
                     /                  /                \
A'S MOVE          ( 1 )              ( 1 )               (1,2) SAME AS (2,1)  
                  /   \         /      |       \         \     M & N REVERSED
B'S MOVE       ( 1 ) ( 0 )  ( 0 )    ( 1 )    ( 0 )      (0,2) SAME AS (2,0) 
                 |         /    \      |     /     \           M & N REVERSED
A'S MOVE       ( 1 )     ( 0 ) ( 0 ) ( 1 ) ( 0 ) ( 1 ) 
                           |     |           |
B'S MOVE                 ( 0 ) ( 0 )       ( 0 )   
---------------------------------------------------------------------------------- 
                                              *
                                               \
B'S MOVE                                     ( 0 )   
                       /                       /                   \         \ 
A'S MOVE             ( 1 )                   ( 1 )               ( 1 )     ( 0 )
              /        |      \       /        |        \       /    \       |
B'S MOVE    ( 0 )    ( 1 )  ( 0 )   ( 0 )    ( 1 )    ( 0 )    ( 1 ) ( 1 ) ( 0 )
           /     \     |            /   \      |     /     \     |     |
A'S MOVE ( 0 ) ( 1 ) ( 1 )       ( 0 ) ( 1 ) ( 1 ) ( 0 ) ( 0 ) ( 1 ) ( 1 )
           |                       |                 |     |
B'S MOVE ( 0 )                   ( 0 )             ( 0 ) ( 0 )                
----------------------------------------------------------------------------------
                       *
                        \
B'S MOVE               ( 0 )
               /         |         \
A'S MOVE     ( 1 )     ( 0 )     ( 1 ) 
            /     \      |
B'S MOVE  ( 1 )  ( 0 ) ( 0 )
            |
A'S MOVE  ( 1 )             
    
    
 NOTE: / OR \ BELOW AN * INDICATES THAT THE PATH GOES TO THE ROOT NODE   
