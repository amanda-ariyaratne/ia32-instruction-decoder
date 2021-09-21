#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef MOV
#define MOV

void mov_reg1_to_reg2_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit); 

    reg_store(rm, w_bit, op1);
}

void mov_reg1_to_reg2_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit); 

    reg_store(rm, w_bit, op1);
}

void mov_reg2_to_reg1_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op2 = reg_load(rm, w_bit); 

    reg_store(reg, w_bit, op2);
}

void mov_reg2_to_reg1_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op2 = reg_load(rm, w_bit); 

    reg_store(reg, w_bit, op2);
}

void mov_mem_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    reg_store(reg, w_bit, op2);
}

void mov_reg_to_mem_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr, w_bit);

    reg_store(reg, w_bit, op2);
}

void mov_reg_to_mem_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);

    mem_store(addr, w_bit, op1);
}

void mov_reg_to_mem_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg_load(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);

    mem_store(addr, w_bit, op1);
}

void mov_reg_to_rm_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        mov_reg1_to_reg2_8bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        mov_reg_to_mem_8bit(mod, reg, rm, scale, index, base, dis, immd);
}

void mov_reg_to_rm_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        mov_reg1_to_reg2_32bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        mov_reg_to_mem_32bit(mod, reg, rm, scale, index, base, dis, immd);
}

// tested
void mov_rm_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        mov_reg2_to_reg_1_8bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        mov_mem_to_reg_8bit(mod, reg, rm, scale, index, base, dis, immd);
}


void mov_rm_to_reg_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        mov_reg2_to_reg1_32bit(mod, reg, rm, scale, index, base, dis, immd);
    else
        mov_mem_to_reg_32bit(mod, reg, rm, scale, index, base, dis, immd);
}

void mov_immd_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op2 = immd;

    reg_store(rm, w_bit, op2);
}

void mov_immd_to_reg_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op2 = immd;

    reg_store(rm, w_bit, op2);
}

void mov_immd_to_reg_32bit_sign_extended(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op2 = sign_extend(immd);
    reg_store(rm, w_bit, op2);
}

void add_immd_to_al_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int op2 = immd;

    reg_store(0, w_bit, op2);
}

void add_immd_to_eax_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int op2 = immd;

    reg_store(0, w_bit, op2);
}

void add_immd_to_memory_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = immd;

    mem_store(addr, w_bit, op2);
}

void add_immd_to_memory_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = immd;

    mem_store(addr, w_bit, op2);
}

void add_immd_to_memory_32bit_sign_extended(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = sign_extend(immd);

    mem_store(addr, w_bit, op2);
}

#endif