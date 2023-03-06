/* GET_BITS.C */

unsigned int get_bits(unsigned int x, int p, int n)
/*----------------------------------------------------------------------------+
| REQUIRES: p and n are sensible values with respect to x                     |
| MODIFIES: nothing                                                           |
| EFFECTS:  returns n bits from position p in x                               |
+----------------------------------------------------------------------------*/
{
    return ((x >> (p + 1 - n)) & ~(~0 << n));
}
