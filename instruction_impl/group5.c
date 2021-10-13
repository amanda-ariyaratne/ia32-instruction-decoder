#include "inc_dec.c"
#include "push.c"

#ifndef GROUP_5
#define GROUP_5

void group5_reg_or_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (reg == 0)
        inc_dec_rm(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else if (reg == 1)
        inc_dec_rm(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else if (reg == 6)
        push_reg_or_mem(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

#endif