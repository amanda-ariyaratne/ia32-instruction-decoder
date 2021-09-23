#ifndef FLAG_CONDITIONS
#define FLAG_CONDITIONS

bool hasAddCarry(unsigned int op1, unsigned int op2, unsigned int val, int w_bit)
{
    if (w_bit)
    {
        if (val < op1 || val < op2)
            return true;
        return false;
    }
    if ((val & 0x000000ff) < op1 || (val & 0x000000ff) < op2)
        return true;
    return false;    
}

bool hasAddOverflow(unsigned int op1, unsigned int op2, unsigned int val, int w_bit)
{
    bool a; bool b; bool c;
    if (w_bit)
    {
        a = (op1 >> 31);
        b = (op2 >> 31);
        c = (val >> 31);
    } else {
        a = ((op1 & 0x00000080) >> 7);
        b = ((op2 & 0x00000080) >> 7);
        c = ((val & 0x00000080) >> 7);
    }

    return (!a & !b & c) | (a & b & !c);
}

bool hasSubCarry(unsigned int op1, unsigned int op2)
{
    if (op1 < op2)
        return true;
    return false;
}

bool hasSubOverflow(unsigned int op1, unsigned int op2, unsigned int val, int w_bit)
{
    bool a; bool b; bool c;
    if (w_bit)
    {
        a = (op1 >> 31);
        b = (op2 >> 31);
        c = (val >> 31);
    } else {
        a = ((op1 & 0x00000080) >> 7);
        b = ((op2 & 0x00000080) >> 7);
        c = ((val & 0x00000080) >> 7);
    }

    return (!a & !b & c) | (a & b & !c);
}

bool isResultZero(unsigned int val, int w_bit)
{
    if (w_bit) return val == 0;

    return (val & 0x000000ff) == 0;
}

bool isResultNegative(unsigned int val, int w_bit)
{
    if (w_bit) return val & 0x80000000;
    return val & 0x00000080;
}

#endif