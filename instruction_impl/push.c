#ifndef PUSH
#define PUSH

void push_register(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;
    unsigned int val = reg_load(rm, w_bit);
    mem_store(stack_top, w_bit, val);
}

void push_memory(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;

    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int val = mem_load(addr, w_bit);
    mem_store(stack_top, w_bit, val);
}

void push_reg_or_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        push_register(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        push_memory(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

#endif