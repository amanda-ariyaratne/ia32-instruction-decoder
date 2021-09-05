#include <string.h>
#include <stdio.h>

// registers
unsigned int eax = 0xbf8db144;
unsigned int ecx = 0x88c5cffb;
unsigned int edx = 0x1;
unsigned int ebx = 0xae5ff4;
unsigned int esp = 0xbf8db0bc;
unsigned int ebp = 0xbf8db118;
unsigned int esi = 0x9a0ca0;
unsigned int edi = 0x0;

int reg(int reg_num, int w)
{
    if (w == 1) {
        switch (reg_num)
        {
            case 0:
                return eax;
            case 1:
                return ecx;
            case 2:
                return edx;
            case 3:
                return ebx;
            case 4:
                return esp;
            case 5:
                return ebp;
            case 6:
                return esi;
            case 7:
                return edi;
            default:
                printf("Invalid register. Exit Program.");
                exit(1);
        }
    } else {
        switch(reg_num)
        {
            case 0:
                return eax & 255;
            case 1:
                return ecx & 255;
            case 2:
                return edx & 255;
            case 3:
                return ebx & 255;
            case 4:
                return esp & 255;
            case 5:
                return ebp & 255;
            case 6:
                return esi & 255;
            case 7:
                return edi & 255;
            default:
                printf("Invalid register. Exit Program.");
                exit(1);
        }   
    }
}

// Segment Register (sreg) Field
unsigned int cs =  0x73; 
unsigned int ss =  0x7b; 
unsigned int ds =  0x7b; 
unsigned int es =  0x7b; 
unsigned int fs =  0x0;
unsigned int gs =  0x33;

int sreg(int sreg_addr)
{
    switch(sreg_addr)
    {
        case 0:
            return es;
        case 1:
            return cs;
        case 2:
            return ss;
        case 3:
            return ds;
        case 4:
            return fs;
        case 5:
            return gs;
        default:
            printf("Invalid SREG. Exit Program.");
            exit(1);
    }
}

// Instruction Pointer Register
unsigned int eip = 0x8048354;

int next_instruction()
{
    return eip;
}

// flag register
unsigned int eflags = 0x246;

int flags()
{
    return eflags;
}


void reg_store(int reg_num, int w, unsigned int val)
{
    if (w == 1) {
        switch (reg_num)
        {
            case 0:
                eax = val;
            case 1:
                ecx = val;
            case 2:
                edx = val;
            case 3:
                ebx = val;
            case 4:
                esp = val;
            case 5:
                ebp = val;
            case 6:
                esi = val;
            case 7:
                edi = val;
            default:
                printf("Invalid register. Exit Program.");
                exit(1);
        }
    } else {
        switch(reg_num)
        {
            case 0:
                eax = (eax & 0xffffff00) + (val & 255);
            case 1:
                ecx = (ecx & 0xffffff00) + (val & 255);
            case 2:
                edx = (edx & 0xffffff00) + (val & 255);
            case 3:
                ebx = (ebx & 0xffffff00) + (val & 255);
            case 4:
                esp = (esp & 0xffffff00) + (val & 255);
            case 5:
                ebp = (ebp & 0xffffff00) + (val & 255);
            case 6:
                esi = (esi & 0xffffff00) + (val & 255);
            case 7:
                edi = (edi & 0xffffff00) + (val & 255);
            default:
                printf("Invalid register. Exit Program.");
                exit(1);
        }   
    }
}