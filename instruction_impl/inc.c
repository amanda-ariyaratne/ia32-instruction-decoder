#include <stdbool.h>
#include "flag_condition_tests.c"
#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef INC
#define INC

void inc_reg_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: Inc reg 8bit\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = 1;
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
}

void inc_mem_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = 1;

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

void inc_rm_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        inc_reg_8bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        inc_mem_8bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void inc_reg_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: Inc reg 8bit\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = 1;
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
}

void inc_mem_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = 1;

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

void inc_rm_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        inc_reg_32bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        inc_mem_32bit(opcode, mod, reg, rm, scale, index, base, dis, immd);
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

#endif