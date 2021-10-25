#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"
#include "add.c"
#include "and.c"
#include "cmp.c"

#ifndef GROUP_1A
#define GROUP_1A

void immd_to_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (reg == 0)
        add_immd_to_reg(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else if (reg == 4)
        and_immd_to_reg(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else if (reg == 7)
        cmp_immd_with_rm(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void immd_to_reg_32bit_sign_extended(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (reg == 0)
        add_immd_to_reg_32bit_sign_extended(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else if (reg == 4)
        and_immd_to_reg_32bit_sign_extended(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else if (reg == 7)
        cmp_immd_with_rm_32bit_sign_extended(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void group1A_8F_reg_or_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (reg == 0)
        pop_to_reg_or_mem(opcode, mod, reg, rm, scale, index, base, dis, immd);
}
#endif