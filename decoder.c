#include <stdbool.h>
#include "enums.c"
#include "opcode_table.c"

// #ifndef DECODER
#define DECODER

void decode(int* instructions, int bytes);
bool isSIBPresent(int mod, int rm);
int getDisSize(int mod, int rm, int base);
int getNextByte(int* instructions, int current_byte, int total_bytes);
bool isPrefix(int byte);
unsigned int getEffectiveAddressFromModRM(int mod, int rm, int scale, int index, int base, unsigned int dis);
unsigned int getAddrFromSIB(int mod, int scale, int index, int base, unsigned int dis);
unsigned int sign_extend(unsigned int val);

void decode(int* instructions, int bytes)
{
    int cur_byte = -1;
    int byte;
    int prefix = 0;
    int esc_1 = -1;
    int esc_2 = -1;
    int opcode = -1;
    int mod = -1;
    int reg_or_op = -1;
    int rm = -1;
    int scale = -1;
    int index = -1;
    int base = -1;
    unsigned int dis = -1;
    int disSize = -1;
    unsigned int immd = -1;

    while (true)
    {
        byte = getNextByte(instructions, ++cur_byte, bytes);
        if (byte == -1)
            break;

        if (isPrefix(byte))
        {
            prefix = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
            printf("prefix %d \n", byte);
        }

        if (byte == OP_2_BYTE_ESCAPE)
        {
            esc_1 = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
            printf("escape1 %d \n", byte);
        } 

        if (esc_1 == OP_2_BYTE_ESCAPE && (byte == OP_3_BYTE_ESCAPE_1 || byte == OP_3_BYTE_ESCAPE_2))
        {
            esc_2 = byte;
            printf("escape2 %d \n", byte);
            byte = getNextByte(instructions, ++cur_byte, bytes);
            
        }
        
        opcode = byte;
        printf("opcode %d %d \n", byte >> 4, byte & 0x0f);

        struct Opcode opcode_details;
        if (esc_1 == -1)
            opcode_details = one_byte_opcode_map[opcode >> 4][opcode & 0x0f][prefix];
        else if (esc_2 == -1)
            opcode_details = two_byte_opcode_map[opcode >> 4][opcode & 0x0f][prefix];
        else if (esc_2 == OP_3_BYTE_ESCAPE_1)
            opcode_details = three_byte_opcode_map_1[opcode >> 4][opcode & 0x0f][prefix];
        else if (esc_2 == OP_3_BYTE_ESCAPE_2)
            opcode_details = three_byte_opcode_map_2[opcode >> 4][opcode & 0x0f][prefix];

        if (opcode_details.modRM)
        {
            byte = getNextByte(instructions, ++cur_byte, bytes);
            rm = byte & 7;
            reg_or_op = (byte & 56) >> 3;
            mod = (byte & 192) >> 6;

            printf("mod %d \n", mod);
            printf("reg or op %d \n", reg_or_op);
            printf("rm %d \n", rm);

            if(isSIBPresent(mod, rm))
            {
                byte = getNextByte(instructions, ++cur_byte, bytes);
                scale = byte & 7;
                index = (byte & 56) >> 3;
                base = (byte & 192) >> 6;
            }

            disSize = getDisSize(mod, rm, base);

            switch (disSize)
            {
                case 1:
                    byte = getNextByte(instructions, ++cur_byte, bytes);
                    dis = byte;
                    break;
                case 4:
                    byte = getNextByte(instructions, ++cur_byte, bytes);
                    dis = byte;
                    byte = getNextByte(instructions, ++cur_byte, bytes);
                    dis = (dis << 8) + byte;
                    byte = getNextByte(instructions, ++cur_byte, bytes);
                    dis = (dis << 8) + byte;
                    byte = getNextByte(instructions, ++cur_byte, bytes);
                    dis = (dis << 8) + byte;
                    break;
                default:
                    break;
            }
        }

        if (opcode_details.immdSize)
        {
            immd = 0;
            for (int i = 0; i < opcode_details.immdSize; i++)
            {
                byte = getNextByte(instructions, ++cur_byte, bytes);
                immd = ((immd << 8) + byte);
            }

            printf("immediate %d \n", immd);
        }

        // Execute Instruction
        opcode_details.instruction(mod, reg_or_op, rm, scale, index, base, dis, immd);

        // Reset Variables Before Next Instruction
        prefix = 0;
        esc_1 = -1;
        esc_2 = -1;
        opcode = -1;
        mod = -1;
        reg_or_op = -1;
        rm = -1;
        scale = -1;
        index = -1;
        base = -1;
        dis = -1;
        disSize = -1;
        immd = -1;
    }
}

bool isSIBPresent(int mod, int rm)
{
    switch (mod)
    {
        case 0:
        case 1:
        case 2:
            if (rm == 4)
                return true;
        default:
            return false;
    }
}

int getDisSize(int mod, int rm, int base)
{
    switch (mod)
    {
        case 0:
            if (rm == 5)
                return 4;
            else if (rm == 4 && base == 5)
                return 4;
            return 0;
        case 1:
            return 1;
        case 2:
            return 4;
        default:
            return 0;
    }
}

int getNextByte(int* instructions, int current_byte, int total_bytes)
{
    if (current_byte == total_bytes)
    {
        return -1;
    }

    int byte = (instructions[(2*current_byte)] << 4) + instructions[(2*current_byte) + 1];

    return byte;
}

bool isPrefix(int byte)
{
    switch(byte)
    {
        case LOCK:
        case REPNE:
        case REP_REPE:
        case SEG_CS:
        case SEG_SS:
        case SEG_ES:
        case SEG_DS:
        case SEG_FS:
        case SEG_GS:
        case OP_SIZE:
        case ADD_SIZE:
            return true;
        default:
            return false;
    }
}

// #endif