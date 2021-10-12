#include <stdbool.h>
#include "flag_condition_tests.c"
#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef INC
#define INC

void setAddFlags(unsigned int op1, unsigned int op2, unsigned int val, int w_bit);

void inc_reg_8bit(mod, reg, rm, scale, index, base, dis, immd)
{
    printf("INS: Inc reg 8bit\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = 1;
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
}

void inc_mem_8bit(mod, reg, rm, scale, index, base, dis, immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = 1;

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

void inc_rm_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        inc_reg_8bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        inc_mem_8bit(mod, reg, rm, scale, index, base, dis, immd);
}

void inc_reg_32bit(mod, reg, rm, scale, index, base, dis, immd)
{
    printf("INS: Inc reg 8bit\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = 1;
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
}

void inc_mem_32bit(mod, reg, rm, scale, index, base, dis, immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = 1;

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

void inc_rm_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        inc_reg_32bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        inc_mem_32bit(mod, reg, rm, scale, index, base, dis, immd);
}

// void inc_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
// {
//     printf("INS: Inc reg 8bit\n");
//     reg = 0;
//     int w_bit = 0;
    
//     unsigned int op1 = reg_load(reg, w_bit);
//     unsigned int op2 = 1;
//     unsigned int val = op1 + op2;

//     setAddFlags(op1, op2, val, w_bit);
//     reg_store(reg, w_bit, val);
// }

void setAddFlags(unsigned int op1, unsigned int op2, unsigned int val, int w_bit)
{
    if (hasAddCarry(op1, op2, val, w_bit)) set_flag_cf(); else clear_flag_cf();
    if (hasAddOverflow(op1, op2, val, w_bit)) set_flag_of(); else clear_flag_of();
    if (isResultZero(val, w_bit)) set_flag_zf(); else clear_flag_zf();
    if (isResultNegative(val, w_bit)) set_flag_sf(); else clear_flag_sf();
}

#endif