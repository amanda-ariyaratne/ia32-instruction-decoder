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

int reg(char* reg_num, int w)
{
    if (w==0) {
        if (reg_num == "000"){
            return eax;
        }            
        else if (reg_num == "001")
            return ecx;
        else if (reg_num == "010")
            return edx;
        else if (reg_num == "011")
            return ebx;
        else if (reg_num == "100")
            return esp;
        else if (reg_num == "101")
            return ebp;
        else if (reg_num == "110")
            return esi;
        else if (reg_num == "111")
            return edi;
    }
    else {
        if (reg_num == "000")
            return eax & 255;
        else if (reg_num == "001")
            return ecx & 255;
        else if (reg_num == "010")
            return edx & 255;
        else if (reg_num == "011")
            return ebx & 255;
        else if (reg_num == "100")
            return esp & 255;
        else if (reg_num == "101")
            return ebp & 255;
        else if (reg_num == "110")
            return esi & 255;
        else if (reg_num == "111")
            return edi & 255;
    }
    return 0;
}

// Segment Register (sreg) Field
unsigned int cs =  0x73; 
unsigned int ss =  0x7b; 
unsigned int ds =  0x7b; 
unsigned int es =  0x7b; 
unsigned int fs =  0x0;
unsigned int gs =  0x33;

int sreg(char* sreg_addr){
    if (sreg_addr == "00" || sreg_addr == "000")
        return es;
    else if (sreg_addr == "01" || sreg_addr == "001")
        return cs;
    else if (sreg_addr == "10" || sreg_addr == "010")
        return ss;
    else if (sreg_addr == "11" || sreg_addr == "011")
        return ds;

    else if (sreg_addr == "100")
        return fs;
    else if (sreg_addr == "101")
        return gs;
    
    return 0;
}

// Instruction Pointer Register
unsigned int eip = 0x8048354;

int next_instruction(){
    return eip;
}

// flag register
unsigned int eflags = 0x246;

int flags(){
    return eflags;
}


