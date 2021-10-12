#include <stdbool.h>
#include "flag_condition_tests.c"
#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef CMP
#define CMP

// TODO : Set AF and PF flags accordingly

void setCmpFlags(unsigned int op1, unsigned int op2, unsigned int val, int w_bit);

void cmp_immd_with_al_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare imm8 with AL\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(0, w_bit); 
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);

}

void cmp_immd_with_eax_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare imm32 with EAX\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(0, w_bit); 
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);

}

void cmp_immd_with_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;

    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_immd_with_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;

    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_immd_with_rm(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        cmp_immd_with_reg(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        cmp_immd_with_mem(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void cmp_immd_with_reg_32bit_sign_extended(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare imm8 with reg32\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = sign_extend(immd);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_immd_with_mem_32bit_sign_extended(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare imm8 with mem32\n");
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = sign_extend(immd);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_immd_with_rm_32bit_sign_extended(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        cmp_immd_with_reg_32bit_sign_extended(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        cmp_immd_with_mem_32bit_sign_extended(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void cmp_reg1_with_reg2_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg8 with reg8.\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(rm, w_bit); 
    unsigned int op2 = reg_load(reg, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_mem_with_reg_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg8 with mem8.\n");
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = reg_load(reg, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_reg_with_rm_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        cmp_reg1_with_reg2_8bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        cmp_mem_with_reg_8bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void cmp_reg1_with_reg2_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg32 with reg32.\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(rm, w_bit); 
    unsigned int op2 = reg_load(reg, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_mem_with_reg_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg32 with mem32.\n");
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = reg_load(reg, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_reg_with_rm_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        cmp_reg1_with_reg2_32bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        cmp_mem_with_reg_32bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void cmp_reg2_with_reg1_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg8 with reg8.\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_reg_with_mem_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg8 with mem8.\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_rm_with_reg_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        cmp_reg2_with_reg1_8bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        cmp_reg_with_mem_8bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void cmp_reg2_with_reg1_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg32 with reg32.\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_reg_with_mem_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare reg32 with mem32.\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);
}

void cmp_rm_with_reg_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        cmp_reg2_with_reg1_32bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        cmp_reg_with_mem_32bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void setCmpFlags(unsigned int op1, unsigned int op2, unsigned int val, int w_bit)
{
    if (hasSubCarry(op1, op2)) set_flag_cf(); else clear_flag_cf();
    if (hasSubOverflow(op1, op2, val, w_bit)) set_flag_of(); else clear_flag_of();
    if (isResultZero(val, w_bit)) set_flag_zf(); else clear_flag_zf();
    if (isResultNegative(val, w_bit)) set_flag_sf(); else clear_flag_sf();
}

#endif