#ifndef POP
#define POP

void pop_to_register(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    unsigned int val = mem_load(stack_top, w_bit);
    stack_top += 4;
    reg_store(4, w_bit, stack_top);
    reg_store(rm, w_bit, val);
}

void pop_to_memory(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    unsigned int val = mem_load(stack_top, w_bit);
    stack_top += 4;
    reg_store(4, w_bit, stack_top);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    mem_store(addr, w_bit, val);
}

void pop_to_reg_or_mem(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    if (mod == 3)
        pop_to_register(opcode, mod, reg, rm, scale, index, base, dis, immd);
    else
        pop_to_memory(opcode, mod, reg, rm, scale, index, base, dis, immd);
}

void pop_to_register_alt(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    unsigned int val = mem_load(stack_top, w_bit);
    stack_top += 4;
    reg_store(4, w_bit, stack_top);
    int new_reg = opcode & 7;
    reg_store(new_reg, w_bit, val);
}

void pop_to_segment_register_1(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    unsigned int val = mem_load(stack_top, w_bit);
    stack_top += 4;
    reg_store(4, w_bit, stack_top);
    int seg = (opcode & 24) >> 3;
    sreg_store(seg, val);
}

void pop_segment_register_2(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    unsigned int val = mem_load(stack_top, w_bit);
    stack_top += 4;
    reg_store(4, w_bit, stack_top);
    int seg = (opcode & 56) >> 3;
    sreg_store(seg, val);
}

#endif