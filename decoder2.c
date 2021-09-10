#ifndef DECODER
#define DECODER
unsigned int getEffectiveAddressFromModRM(int mod, int rm, int scale, int index, int base, unsigned int dis);
unsigned int getAddrFromSIB(int mod, int scale, int index, int base, unsigned int dis);
unsigned int sign_extend(unsigned int val);

unsigned int getEffectiveAddressFromModRM(int mod, int rm, int scale, int index, int base, unsigned int dis)
{
    unsigned int addr;
    int w_bit = 1;
    switch (mod)
    {
        case 0:
            switch (rm)
            {
                case 4:
                    addr = getAddrFromSIB(mod, scale, index, base, dis);
                    break;
                case 5:
                    addr = dis;
                    break;
                default:
                    addr = reg_load(rm, w_bit);
                    break;
            }
            break;
        case 1:
            switch (rm)
            {
                case 4:
                    addr = getAddrFromSIB(mod, scale, index, base, dis);
                    break;
                default:
                    addr = reg_load(rm, w_bit);
                    break;
            }
            addr += sign_extend(dis);
            break;
        case 2:
            switch (rm)
            {
                case 4:
                    addr = getAddrFromSIB(mod, scale, index, base, dis);
                    break;
                default:
                    addr = reg_load(rm, w_bit);
                    break;
            }
            addr += dis;
            break;
        default:
            break;
    }

    return addr;
}

unsigned int getAddrFromSIB(int mod, int scale, int index, int base, unsigned int dis)
{
    unsigned int addr;
    int w_bit = 1;
    if (base != 5)
    {
        switch (index)
        {
            case 4:
                addr = reg_load(base, w_bit);
                break;
            default:
                addr = reg_load(index, w_bit) * (2 << scale) + reg_load(base, w_bit);
                break;
        }
    } else {
        switch (mod)
        {
            case 0:
                switch (index)
                {
                    case 4:
                        addr = dis;
                        break;
                    default:
                        addr = reg_load(index, w_bit) * (2 << scale) + dis;
                        break;
                }
                break;
            case 1:
            case 2:
                switch (index)
                {
                    case 4:
                        addr = reg_load(5, w_bit) + dis;
                        break;
                    default:
                        addr = reg_load(index, w_bit) * (2 << scale) + dis + reg_load(5, w_bit);
                        break;
                }
                break;  
            default:
                break;
        }
    }

    return addr;
}

unsigned int sign_extend(unsigned int val)
{
    int sign = (val & 0x00000080);
    unsigned int sgn_extended = val;
    if (sign == 128)
        sgn_extended = 0xffffff00 + val;
    return sgn_extended;
}

#endif