#include <stdbool.h>
#include "flag_condition_tests.c"
#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef ADD
#define ADD

void add_reg1_to_reg2(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
}

void add_reg_to_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

void add_reg_to_rm(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        add_reg1_to_reg2(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        add_reg_to_mem(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void add_reg2_to_reg1(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(reg, w_bit, val);
}

void add_mem_to_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(reg, w_bit, val);
}

// tested
void add_rm_to_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        add_reg2_to_reg1(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        add_mem_to_reg(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void add_immd_to_reg(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = opcode & 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
}

void add_immd_to_reg_32bit_sign_extended(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = sign_extend(immd);
    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(rm, w_bit, val);
}

void add_immd_to_eax(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = (opcode & 1);
    unsigned int op1 = reg_load(0, w_bit);
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    reg_store(0, w_bit, val);
}

void add_immd_to_memory_8bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

void add_immd_to_memory_32bit(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

void add_immd_to_memory_32bit_sign_extended(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = sign_extend(immd);

    unsigned int val = op1 + op2;

    setAddFlags(op1, op2, val, w_bit);
    mem_store(addr, w_bit, val);
}

#endif