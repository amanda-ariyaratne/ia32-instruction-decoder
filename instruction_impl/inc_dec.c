#include <stdbool.h>
#include "flag_condition_tests.c"
#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef INC_DEC
#define INC_DEC

unsigned int inc_or_dec;

void inc_dec_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = 1;
    unsigned int val;

    if (reg == 0)
        val = op1 + op2;
    else
        val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);

    printf("INS: Inc/Dec - reg %d, %d op %d = %d \n", reg, op1, op2, val);
}

void inc_dec_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = 1;
    unsigned int val;

    if (reg == 0)
        val = op1 + op2;
    else
        val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);

    printf("INS: Inc/Dec reg 32bit - reg %d, %d op %d = %d \n", reg, op1, op2, val);
}

void inc_dec_rm(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        inc_dec_reg(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        inc_dec_mem(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void inc_dec_reg_alt_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    reg = opcode & 0x07;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int op2 = 1;
    unsigned int inc_or_dec_sign = (opcode >> 3) & 1;
    unsigned int val;

    if (inc_or_dec_sign == 0)
        val = op1 + op2;
    else
        val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(reg, w_bit, val);

    printf("INS: Inc/Dec reg 32bit - reg %d, %d op %d = %d \n", reg, op1, op2, val);
}

#endif