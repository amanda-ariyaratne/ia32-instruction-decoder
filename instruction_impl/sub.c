#include <stdbool.h>
#include "flag_condition_tests.c"
#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef SUB
#define SUB

void sub_reg1_from_reg2(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
    printf("INS: sub_reg1_from_reg2 %d - %d = %d \n", op1, op2, val);
}

void sub_reg2_from_reg1(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(rm, w_bit); 
    unsigned int op2 = reg_load(reg, w_bit);
    unsigned int val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(reg, w_bit, val);
    printf("INS: sub_reg2_from_reg1 %d - %d = %d \n", op1, op2, val);
}

void sub_mem_from_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);
    unsigned int val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(reg, w_bit, val);
    printf("INS: sub_mem_from_reg %d - %d = %d \n", op1, op2, val);
}

void sub_reg_from_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = reg_load(reg, w_bit);
    unsigned int val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
    printf("INS: sub_reg_from_mem %d - %d = %d \n", op1, op2, val);
}

void sub_immd_from_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
    printf("INS: sub_immd_from_reg %d - %d = %d \n", op1, op2, val);
}

void sub_immd_from_eax(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = (opcode & 1);
    unsigned int op1 = reg_load(0, w_bit);   // TODO: remove hardcode val of register 0
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(0, w_bit, val);
    printf("INS: sub_immd_from_eax %d - %d = %d \n", op1, op2, val);
}

void sub_immd_from_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = (opcode & 1);
    int s_bit = ((opcode >> 1) & 1);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = s_bit==1 ? immd : sign_extend(immd);
    unsigned int val = op1 - op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
    printf("INS: sub_immd_from_mem %d - %d = %d \n", op1, op2, val);
}

void sub_reg_from_rm(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        sub_reg1_from_reg2(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        sub_reg_from_mem(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void sub_rm_from_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        sub_reg2_from_reg1(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        sub_mem_from_reg(opcode, mod, reg, rm, scale, index, base, dis, immd);
}
#endif