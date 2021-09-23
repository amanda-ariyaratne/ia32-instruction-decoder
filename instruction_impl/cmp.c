#include <stdbool.h>
#include "flag_condition_tests.c"
#include "../registers.c"
#include "../memory.c"
#include "../decoder2.c"

#ifndef CMP
#define CMP

// TODO : Set AF and PF flags accordingly

void setCmpFlags(unsigned int op1, unsigned int op2, unsigned int val, int w_bit);

void cmp_immd_with_al_8bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare imm8 with AL\n");
    int w_bit = 0;
    unsigned int op1 = reg_load(0, w_bit); 
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);

}

void cmp_immd_with_eax_32bit(int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd)
{
    printf("Compare imm32 with EAX\n");
    int w_bit = 1;
    unsigned int op1 = reg_load(0, w_bit); 
    unsigned int op2 = immd;
    unsigned int val = op1 - op2;

    setCmpFlags(op1, op2, val, w_bit);

}

void setCmpFlags(unsigned int op1, unsigned int op2, unsigned int val, int w_bit)
{
    if (hasSubCarry(op1, op2)) set_flag_cf(); else clear_flag_cf();
    if (hasSubOverflow(op1, op2, val, w_bit)) set_flag_of(); else clear_flag_of();
    if (isResultZero(val, w_bit)) set_flag_zf(); else clear_flag_zf();
    if (isResultNegative(val, w_bit)) set_flag_sf(); else clear_flag_sf();
}

#endif