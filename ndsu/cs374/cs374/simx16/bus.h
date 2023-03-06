/* BUS.H */
#ifndef _BUSH_
#define _BUSH_

typedef struct bus
{
    unsigned int byte0:8;
    unsigned int byte1:8;
}   BUS;

BUS bus;

int read_from_mem(int addr, int num_bytes);
/*----------------------------------------------------------------------------+
| REQUIRES: memory and bus are initialized                                    |
| MODIFIES: bus                                                               |
| EFFECTS:  places num_bytes stored at addr on bus                            |
+----------------------------------------------------------------------------*/

int write_to_mem(int addr, int num_bytes);
/*----------------------------------------------------------------------------+
| REQUIRES: memory and bus are initialized and bus contains legitimate value  |
| MODIFIES: memory (at addr)                                                  |
| EFFECTS:  takes the current bus value and stores it in memory at addr       |
+----------------------------------------------------------------------------*/

int read_from_bus(unsigned int *byte0, unsigned int *byte1);
/*----------------------------------------------------------------------------+
| REQUIRES: bus has been initialized and contains a legitmate value           |
| MODIFIES: byte0 and byte1                                                   |
| EFFECTS:  assigns low order byte of bus to byte0 and high order byte of bus |
|           to byte1                                                          |
+----------------------------------------------------------------------------*/

int write_on_bus(unsigned int byte0, unsigned int byte1);
/*----------------------------------------------------------------------------+
| REQUIRES: bus has been initialized                                          |
| MODIFIES: bus.byte0 and bus.byte1                                           |
| EFFECTS:  assigns byte0 to low order byte of bus and byte1 to high order    |
|           byte of bus                                                       |
+----------------------------------------------------------------------------*/
#endif
