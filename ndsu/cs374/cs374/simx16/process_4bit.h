
 int put_4bit_info(unsigned int instruction, unsigned int operand2, unsigned int value);
/*----------------------------------------------------------------------+
| REQUIRES : instruction be the current instruction to be processed     |
|            operand1 unsigned interger scr tells if source or dest     |
| EFFECTS  : returns what the instruction is operating on               |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/

unsigned int get_4bit_info(unsigned int instruction, unsigned int operand1, int source);
/*----------------------------------------------------------------------+
| REQUIRES : instruction be the current instruction to be processed     |
|            operand1 unsigned interger scr tells if source or dest     |
             fields of the instruction are to be used.
| EFFECTS  : returns what the instruction is operating on               |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/
int
process_4bit_instr(unsigned int instruction, unsigned int operand1,
		   unsigned int operand2);
/*----------------------------------------------------------------------+
| REQUIRES : instruction be the current instruction to be processed     |
|            operand1,and operand2 are unsigned intergers with the      |
|            values of the scr and dest for the 4bit instructions       |
| EFFECTS  : processes all of the 4bit instructions                     |
| MODIFYIES| registers, memory and ouput as per instructions            |
+----------------------------------------------------------------------*/

    int
                    ccry(void);
/*-----------------------------------------------------------------------
| REQUIRES : nothing                          			        |
| EFFECTS  : sets the PSW_Cbit to 0 regaurdless                         |
| MODIFYIES| PSW_Cbit                                                   |
-----------------------------------------------------------------------*/
    int
                    scry(void);
/*-----------------------------------------------------------------------
| REQUIRES : nothing                          			        |
| EFFECTS  : sets the PSW_Cbit to 1 regaurdless                         |
| MODIFYIES| PSW_Cbit                                                   |
-----------------------------------------------------------------------*/




    int
                    notb(unsigned int scr, unsigned int *dest);
/*-----------------------------------------------------------------------
| REQUIRES : scr is unsigned int. dest is pointer to unsigned int       |
| EFFECTS  :  the contents of scr are negated and stored in dest        |
| MODIFYIES| dest                                                       |
-----------------------------------------------------------------------*/
    int
                    noth(unsigned int scr, unsigned int *dest);
/*-----------------------------------------------------------------------
| REQUIRES : scr is unsigned int. dest is pointer to unsigned int       |
| EFFECTS  :  the contents of scr are negated and stored in dest        |
| MODIFYIES| dest                                                       |
-----------------------------------------------------------------------*/
    int
                    popp(unsigned int *hw);
/*-----------------------------------------------------------------------
| REQUIRES : hw be the program status word 16 bits long                 |
| EFFECTS  : pushes the contents of the program status register on stack|
|             increments the stack pointer by 2;                        |
| MODIFYIES| stack                                                      |
-----------------------------------------------------------------------*/
    int
                    pshp(unsigned int hw);
/*-----------------------------------------------------------------------
| REQUIRES : hw be the program status word 16 bits long                 |
| EFFECTS  : pushes the contents of the program status register on stack|
|             increments the stack pointer by 2;                        |
| MODIFYIES| stack                                                      |
-----------------------------------------------------------------------*/






    int
                    popb(unsigned int *byte);
/*----------------------------------------------------------------------
| REQUIRES : byte be an unsigned interger                              |
| EFFECTS  : pops 2 bytes off stack and returns them in byte, then     |
|             increments the stack pointer by 2;                       |
| MODIFYIES| stack                                                     |
-----------------------------------------------------------------------*/
    int
                    poph(unsigned int *byte);
/*----------------------------------------------------------------------
| REQUIRES : byte be an unsigned interger                              |
| EFFECTS  : pops 2 bytes off stack and returns them in byte, then     |
|             increments the stack pointer by 2;                       |
| MODIFYIES| stack                                                     |
-----------------------------------------------------------------------*/
    int
                    pshh(unsigned int byte);
/*----------------------------------------------------------------------
| REQUIRES : byte be an unsigned interger                              |
| EFFECTS  :  pushes byte on the stack and decrements the stack pointer|
| MODIFYIES| stack                                                     |
-----------------------------------------------------------------------*/
    int
                    pshb(unsigned int byte);
/*----------------------------------------------------------------------
| REQUIRES : byte be an unsigned interger                              |
| EFFECTS  :  pushes byte on the stack and decrements the stack pointer|
| MODIFYIES| stack                                                     |
-----------------------------------------------------------------------*/
unsigned int
                    sub_half(unsigned int t1, unsigned int t2, int wcarry);
/*----------------------------------------------------------------
| REQUIRES : TWO UNSIGNED INTS TO ADD                            |
|           wcarry== 1 indicated with borrow                     |
| EFFECTS  : ADDS INTERGERS AND RETURNS RESULT SETTING PSW       |
| MODIFYIES| NOTHING                                             |
----------------------------------------------------------------*/

unsigned int  sub_byte(unsigned int t1, unsigned int t2, int wcarry);
/*----------------------------------------------------------------
| REQUIRES : TWO UNSIGNED INTS TO ADD                            |
|           wcarry== 1 indicated with borrow                     |
| EFFECTS  : ADDS INTERGERS AND RETURNS RESULT SETTING PSW       |
| MODIFYIES| NOTHING                                             |
----------------------------------------------------------------*/

   unsigned int   power2(int in);

    unsigned int  add_half(unsigned int scr, unsigned int dest, int flag);

    unsigned int add_byte(unsigned int scr, unsigned int dest, int y);

    unsigned int    get_psw(void);
/*----------------------------------------------------------------------+
| REQUIRES : nothing                                                    |
| EFFECTS  : returns the contents of the PSW                            |
| MODIFYIES| nothing                                                    |
+----------------------------------------------------------------------*/
