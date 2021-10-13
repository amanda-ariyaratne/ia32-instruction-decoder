#ifndef PUSH
#define PUSH

void push_register(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;
    reg_store(4, w_bit, stack_top);
    unsigned int val = reg_load(rm, w_bit);
    mem_store(stack_top, w_bit, val);
}

void push_memory(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;
    reg_store(4, w_bit, stack_top);

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

void push_register_alt(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;
    reg_store(4, w_bit, stack_top);
    int new_reg = opcode & 7;
    unsigned int val = reg_load(new_reg, w_bit);
    mem_store(stack_top, w_bit, val);
}

void push_immediate(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int w_bit = 1;
    int s_bit = (opcode & 2) >> 1;
    if (s_bit) {
        immd = sign_extend(immd);
    }
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;
    reg_store(4, w_bit, stack_top);
    mem_store(stack_top, w_bit, immd);
}

void push_segment_register_1(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int seg = sreg_load((opcode & 24) >> 3);
    int w_bit = 1;
    
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;
    reg_store(4, w_bit, stack_top);
    mem_store(stack_top, w_bit, seg);
}

void push_segment_register_2(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    int seg = sreg_load((opcode & 56) >> 3);
    int w_bit = 1;
    
    unsigned int stack_top = reg_load(4, w_bit);
    stack_top -= 4;
    reg_store(4, w_bit, stack_top);
    mem_store(stack_top, w_bit, seg);
}

#endif