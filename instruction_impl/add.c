void add_reg1_to_reg2_8bit(int reg, int reg_or_op, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(rm, w_bit, val);
}

void add_reg1_to_reg2_32bit(int reg, int reg_or_op, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(rm, w_bit, val);
}

void add_reg2_to_reg_1_8bit(int reg, int reg_or_op, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(reg, w_bit, val);
}

void add_reg2_to_reg_1_32bit(int reg, int reg_or_op, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(reg, w_bit); 
    unsigned int op2 = reg(rm, w_bit);
    unsigned int val = op1 + op2;

    reg_store(reg, w_bit, val);
}

void add_mem_to_reg_8bit(int reg, int reg_or_op, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 0;
    unsigned int op1 = reg(reg1, w_bit);
    unsigned int op2;

    switch (mod)
    {
        case 0:
            int addr;
            switch (rm)
            {
                case 4:
                    addr = getAddrFromSIB_8bit(mod, scale, index, base, dis);
                    break;
                case 5:
                    addr = dis;
                    break;
                default:
                    addr = reg(rm, w_bit);
                    break;
            }
            op2 = mem(addr); // TODO: function mem
            break;
        case 1:
        case 2:
            int addr;
            switch (rm)
            {
                case 4:
                    addr = getAddrFromSIB_8bit(mod, scale, index, base, dis) + dis;
                    break;
                default:
                    addr = reg(rm, w_bit) + dis;
                    break;
            }
            op2 = mem(addr);
            break;
        default:
            break;
    }

    unsigned int val = op1 + op2;
    reg_store(reg, w_bit, val);
}

void add_mem_to_reg_32bit(int reg, int reg_or_op, int rm, int scale, int index, int base, int dis, int immd)
{
    int w_bit = 1;
    unsigned int op1 = reg(reg1, w_bit);
    unsigned int op2;

    switch (mod)
    {
        case 0:
            int addr;
            switch (rm)
            {
                case 4:
                    addr = getAddrFromSIB_8bit(mod, scale, index, base, dis);
                    break;
                case 5:
                    addr = dis;
                    break;
                default:
                    addr = reg(rm, w_bit);
                    break;
            }
            op2 = mem(addr); // TODO: function mem
            break;
        case 1:
        case 2:
            int addr;
            switch (rm)
            {
                case 4:
                    addr = getAddrFromSIB_8bit(mod, scale, index, base, dis) + dis;
                    break;
                default:
                    addr = reg(rm, w_bit) + dis;
                    break;
            }
            op2 = mem(addr);
            break;
        default:
            break;
    }

    unsigned int val = op1 + op2;
    reg_store(reg, w_bit, val);
}