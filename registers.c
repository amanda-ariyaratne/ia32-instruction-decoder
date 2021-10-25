#include <string.h>
#include <stdio.h>

#ifndef EFLAGS
#define EFLAGS

// flag register
unsigned int eflags = 0x246;

unsigned int flags()
{
    return eflags;
}

void set_flag_id(){eflags |= (1 << 21);}
void clear_flag_id(){eflags &= ~(1 << 21);}

void set_flag_vip(){eflags |= (1 << 20);}
void clear_flag_vip(){eflags &= ~(1 << 20);}

void set_flag_vif(){eflags |= (1 << 19);}
void clear_flag_vif(){eflags &= ~(1 << 19);}

void set_flag_ac(){eflags |= (1 << 18);}
void clear_flag_ac(){eflags &= ~(1 << 18);}

void set_flag_vm(){eflags |= (1 << 17);}
void clear_flag_vm(){eflags &= ~(1 << 17);}

void set_flag_rf(){eflags |= (1 << 16);}
void clear_flag_rf(){eflags &= ~(1 << 16);}

void set_flag_nt(){eflags |= (1 << 14);}
void clear_flag_nt(){eflags &= ~(1 << 14);}

void set_flag_iopl(){}
void clear_flag_iopl(){}

void set_flag_of(){eflags |= (1 << 11);}
void clear_flag_of(){eflags &= ~(1 << 11);}

void set_flag_df(){eflags |= (1 << 10);}
void clear_flag_df(){eflags &= ~(1 << 10);}

void set_flag_if(){eflags |= (1 << 9);}
void clear_flag_if(){eflags &= ~(1 << 9);}

void set_flag_tf(){eflags |= (1 << 8);}
void clear_flag_tf(){eflags &= ~(1 << 8);}

void set_flag_sf(){eflags |= (1 << 7);}
void clear_flag_sf(){eflags &= ~(1 << 7);}

void set_flag_zf(){eflags |= (1 << 6);}
void clear_flag_zf(){eflags &= ~(1 << 6);}

void set_flag_af(){eflags |= (1 << 4);}
void clear_flag_af(){eflags &= ~(1 << 4);}

void set_flag_pf(){eflags |= (1 << 2);}
void clear_flag_pf(){eflags &= ~(1 << 2);}

void set_flag_cf(){eflags |= (1 << 0);}
void clear_flag_cf(){eflags &= ~(1 << 0);}

#endif

#ifndef GENERAL_PURPOSE_REGISTERS
#define GENERAL_PURPOSE_REGISTERS

// registers
unsigned int eax = 0xbf8db144;
unsigned int ecx = 0x88c5cffb;
unsigned int edx = 0x1;
unsigned int ebx = 0xae5ff4;
unsigned int esp = 0xbf8db0bc;
unsigned int ebp = 0xbf8db118;
unsigned int esi = 0x9a0ca0;
unsigned int edi = 0x0;

unsigned int reg_load(int reg_num, int w)
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
                exit(1);
        }   
    }
}

void reg_store(int reg_num, int w, unsigned int val)
{
    
    if (w == 1) {
        switch (reg_num)
        {
            case 0:
                eax = val;
                break;
            case 1:
                ecx = val;
                break;
            case 2:
                edx = val;
                break;
            case 3:
                ebx = val;
                break;
            case 4:
                esp = val;
                break;
            case 5:
                ebp = val;
                break;
            case 6:
                esi = val;
                break;
            case 7:
                edi = val;
                break;
            default:
                exit(1);
        }
    } else {
        switch(reg_num)
        {
            case 0:
                eax = (eax & 0xffffff00) + (val & 255);
                break;
            case 1:
                ecx = (ecx & 0xffffff00) + (val & 255);
                break;
            case 2:
                edx = (edx & 0xffffff00) + (val & 255);
                break;
            case 3:
                ebx = (ebx & 0xffffff00) + (val & 255);
                break;
            case 4:
                esp = (esp & 0xffffff00) + (val & 255);
                break;
            case 5:
                ebp = (ebp & 0xffffff00) + (val & 255);
                break;
            case 6:
                esi = (esi & 0xffffff00) + (val & 255);
                break;
            case 7:
                edi = (edi & 0xffffff00) + (val & 255);
                break;
            default:
                exit(1);
        }   
    }
}

#endif

#ifndef SEGMENT_REGISTERS
#define SEGMENT_REGISTERS

// Segment Register (sreg) Field
unsigned int cs =  0x73; 
unsigned int ss =  0x7b; 
unsigned int ds =  0x7b; 
unsigned int es =  0x7b; 
unsigned int fs =  0x0;
unsigned int gs =  0x33;

int sreg_load(int sreg_addr)
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
            exit(1);
    }
}

int sreg_store(int sreg_addr, int val)
{
    switch(sreg_addr)
    {
        case 0:
            es = val;
        case 1:
            cs = val;
        case 2:
            ss = val;
        case 3:
            ds = val;
        case 4:
            fs = val;
        case 5:
            gs = val;
        default:
            exit(1);
    }
}

#endif

#ifndef INSTRUCTION_POINT_REGISTERS
#define INSTRUCTION_POINT_REGISTERS

// Instruction Pointer Register
unsigned int eip = 0x8048354;

int next_instruction()
{
    return eip;
}

#endif

#ifndef REGISTER_DUMP
#define REGISTER_DUMP

void regDump(int opcode, int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd) {
    FILE *fptr;
    fptr = fopen("log.txt", "a");
    if(fptr == NULL){
        printf("ERROR: No such file exist");   
        exit(1);             
    }
    fprintf(fptr, "**************************************INSTRUCTION**************************************\n");
    fprintf(fptr, "opcode %x%x, mod %d, reg_or_op %d, rm %d, scale %d, index %d, base %d, dis %d, immd %d\n\n", opcode >> 4, opcode & 0x0f, mod, reg, rm, scale, index, base, dis, immd);
    fprintf(fptr, "Flags %d\n", flags());
    fprintf(fptr, "General Purpose Registers\n EAX=%d\t ECX=%d\t EDX=%d\t EBX=%d\t ESP EBP=%d\t ESI=%d\t EDI=%d\n\n", eax, ecx, edx, ebx, esp, esi, edi);
    fprintf(fptr, "Segment Registers\n CS=%d\t SS=%d\t DS=%d\t ES=%d\t FS=%d\t GS=%d\n\n", cs,ss,ds,es,fs,gs);
    fprintf(fptr, "Instruction Pointer\n EIP=%d\n\n", eip);
    fclose(fptr);

    printf("**************************************INSTRUCTION**************************************\n");
    printf("opcode %x%x, mod %d, reg_or_op %d, rm %d, scale %d, index %d, base %d, dis %d, immd %d\n\n", opcode >> 4, opcode & 0x0f, mod, reg, rm, scale, index, base, dis, immd);
    printf("Flags %d\n", flags());
    printf("General Purpose Registers\n EAX=%d\t ECX=%d\t EDX=%d\t EBX=%d\t ESP EBP=%d\t ESI=%d\t EDI=%d\n\n", eax, ecx, edx, ebx, esp, esi, edi);
    printf("Segment Registers\n CS=%d\t SS=%d\t DS=%d\t ES=%d\t FS=%d\t GS=%d\n\n", cs,ss,ds,es,fs,gs);
    printf("Instruction Pointer\n EIP=%d\n\n", eip);
}

#endif