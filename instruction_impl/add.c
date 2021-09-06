void add_reg1_to_reg2_8bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(rm, w_bit, val);
}

void add_reg1_to_reg2_32bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(rm, w_bit, val);
}

void add_reg2_to_reg_1_8bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(reg, w_bit, val);
}

void add_reg2_to_reg_1_32bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(reg, w_bit, val);
}

void add_mem_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem(addr);

    unsigned int val = op1 + op2;
    reg_store(reg, w_bit, val);
}

void add_mem_to_reg_32bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr); // TODO: function mem_load

    unsigned int val = op1 + op2;
    reg_store(reg, w_bit, val);
}

void add_reg_to_mem_8bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr);

    unsigned int val = op1 + op2;
    mem_store(addr, w_bit, val); // TODO: function mem_store
}

void add_reg_to_mem_32bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(reg, w_bit);
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op2 = mem_load(addr);

    unsigned int val = op1 + op2;
    mem_store(addr, w_bit, val); // TODO: function mem_store
}

void add_immd_to_reg_8bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(rm, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 + op2;

    reg_store(rm, w_bit, val);
}

void add_immd_to_reg_32bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(rm, w_bit);
    unsigned int op2 = immd;
    unsigned int val = op1 + op2;

    reg_store(rm, w_bit, val);
}

void add_immd_to_reg_32bit_sign_extended(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(rm, w_bit);
    unsigned int op2 = sign_extend(immd);
    unsigned int val = op1 + op2;

    reg_store(rm, w_bit, val);
}

void add_immd_to_al_ax_eax_8bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(0, w_bit);   // TODO: remove hardcode val of register 0
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;
    reg_store(0, w_bit, val);
}

void add_immd_to_al_ax_eax_32bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(0, w_bit);   // TODO: remove hardcode val of register 0
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;
    reg_store(0, w_bit, val);
}

void add_immd_to_memory_8bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr);
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;
    mem_store(addr, w_bit, val);    // TODO: function mem_store
}

void add_immd_to_memory_32bit(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr);
    unsigned int op2 = immd;

    unsigned int val = op1 + op2;
    mem_store(addr, w_bit, val);    // TODO: function mem_store
}

void add_immd_to_memory_32bit_sign_extended(int mod, int reg, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int addr = getEffectiveAddressFromModRM(mod, rm, scale, index, base, dis);
    unsigned int op1 = mem_load(addr);
    unsigned int op2 = sign_extend(immd);

    unsigned int val = op1 + op2;
    mem_store(addr, w_bit, val);    // TODO: function mem_store
}