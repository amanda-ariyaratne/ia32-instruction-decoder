#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef LEA
#define LEA

void store_eff_addr_from_reg_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op2 = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);

    reg_store(reg, w_bit, op2);
}

#endif