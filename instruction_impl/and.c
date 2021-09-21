#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef AND
#define AND

void and_reg1_to_reg2_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: And reg1 to reg2 8bit\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 & op2;

    reg_store(rm, w_bit, val);
    printf("expect %d & %d = %d\n", op1, op2, val);
}

void and_reg_to_mem_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    unsigned int val = op1 & op2;
    mem_store(addr, w_bit, val);
}

void and_reg_to_rm_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        and_reg1_to_reg2_8bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        and_reg_to_mem_8bit(mod, reg, rm, scale, index, base, dis, immd);
}

void and_reg1_to_reg2_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: And reg1 to reg2 32bit\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 & op2;

    reg_store(rm, w_bit, val);
    printf("expect %u & %u = %u \n", op1, op2, val);
}

void and_reg_to_mem_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    unsigned int val = op1 & op2;
    mem_store(addr, w_bit, val);
}

void and_reg_to_rm_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        and_reg1_to_reg2_32bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        and_reg_to_mem_32bit(mod, reg, rm, scale, index, base, dis, immd);
}

void and_reg2_to_reg_1_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 & op2;

    reg_store(reg, w_bit, val);
}

void and_mem_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    unsigned int val = op1 & op2;
    reg_store(reg, w_bit, val);
}

// tested
void and_rm_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        and_reg2_to_reg_1_8bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        and_mem_to_reg_8bit(mod, reg, rm, scale, index, base, dis, immd);
}

// tested
void and_reg2_to_reg1_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit); 
    unsigned int op2 = reg_load(rm, w_bit);
    unsigned int val = op1 & op2;

    reg_store(reg, w_bit, val);
}

// tested
void and_mem_to_reg_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    unsigned int val = op1 & op2;
    reg_store(reg, w_bit, val);
}

void and_rm_to_reg_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        and_reg2_to_reg1_32bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        and_mem_to_reg_32bit(mod, reg, rm, scale, index, base, dis, immd);
}

void and_immd_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: And imm8 to reg 8bit\n");

    int w_bit = 0;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 & op2;

    reg_store(rm, w_bit, val);
    printf("expect %u & %u = %u \n", op1, op2, val);
}

void and_immd_to_reg_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: And imm32 to reg 32bit\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 & op2;

    reg_store(rm, w_bit, val);
    printf("expect %u & %u = %u \n", op1, op2, val);
}

void and_immd_to_reg_32bit_sign_extended(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: And imm8 to reg 32bit sign extended\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(rm, w_bit);
    unsigned int op2 = sign_extend(immd);
    unsigned int val = op1 & op2;

    reg_store(rm, w_bit, val);
    printf("expect %u & %u = %u \n", op1, op2, val);
}

void and_immd_to_al_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: And imm8 to AL\n");

    int w_bit = 0;
    unsigned int op1 = reg_load(0, w_bit);   // TODO: remove hardcode val of register 0
    unsigned int op2 = immd;

    unsigned int val = op1 & op2;

    reg_store(0, w_bit, val);
}

void and_immd_to_eax_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("INS: And imm32 to EAX\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(0, w_bit);   // TODO: remove hardcode val of register 0
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;
    reg_store(0, w_bit, val);
    printf("expect %u & %u = %u\n", op1, op2, val);
}

void and_immd_to_memory_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = immd;

    unsigned int val = op1 & op2;
    mem_store(addr, w_bit, val);
}

void and_immd_to_memory_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = immd;

    unsigned int val = op1 & op2;
    mem_store(addr, w_bit, val);
}

void and_immd_to_memory_32bit_sign_extended(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr, w_bit);
    unsigned int op2 = sign_extend(immd);

    unsigned int val = op1 & op2;
    mem_store(addr, w_bit, val);
}

#endif