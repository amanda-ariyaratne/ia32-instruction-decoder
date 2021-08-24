#include <stdbool.h>
#include "enums.c"

void decode(int* instructions, int bytes);
bool isPrefix(int byte);
bool isEscapeCode(int byte);
int getNextByte(int* instructions, int current_byte, int total_bytes);
bool isModRMPresent(int prefix, int esc_1, int esc_2, int opcode);
bool isSIBPresent(int mod);
bool isDisplacementPresent();
bool isImmediateValuePresent();

void decode(int* instructions, int bytes)
{
    int cur_byte = -1;
    int byte;
    int prefix = -1;
    int esc_1 = -1;
    int esc_2 = -1;
    int opcode = -1;
    int mod = -1;
    int reg_or_op = -1;
    int rm = -1;
    int scale = -1;
    int index = -1;
    int base = -1;
    int dis = -1;
    int immd = -1;

    while (cur_byte != bytes)
    {
        byte = getNextByte(instructions, ++cur_byte, bytes);
        if (byte == -1)
            break;

        if (isPrefix(byte))
        {
            prefix = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        }

        // printf("prefix = %d\n", prefix);
            
        while (isEscapeCode(byte))
        {
            if (esc_1 == -1)
            {
                esc_1 = byte;
                byte = getNextByte(instructions, ++cur_byte, bytes);
            } else
            {
                esc_2 = byte;
                byte = getNextByte(instructions, ++cur_byte, bytes);
            }
        }

        // printf("esc_1 = %d\n", esc_1);
        // printf("esc_2 = %d\n", esc_2);
        
        opcode = byte;

        // printf("opcode = %d\n", opcode);

        if (isModRMPresent(prefix, esc_1, esc_2, opcode))
        {
            byte = getNextByte(instructions, ++cur_byte, bytes);
            mod = byte & 7;
            reg_or_op = (byte & 56) >> 3;
            rm = (byte & 192) >> 6;
        }

        // printf("mod = %d\n", mod);
        // printf("reg_or_op = %d\n", reg_or_op);
        // printf("rm = %d\n", rm);

        if (isSIBPresent(mod))
        {
            byte = getNextByte(instructions, ++cur_byte, bytes);
            scale = byte & 7;
            index = (byte & 56) >> 3;
            base = (byte & 192) >> 6;
        }

        // printf("scale = %d\n", scale);
        // printf("index = %d\n", index);
        // printf("base = %d\n", base);
        
        if (isDisplacementPresent())
        {
            byte = getNextByte(instructions, ++cur_byte, bytes);
            dis = byte;
        }

        // printf("dis = %d\n", dis);

        if (isImmediateValuePresent())
        {
            byte = getNextByte(instructions, ++cur_byte, bytes);
            immd = byte;
        }

        // printf("immd = %d\n", immd);

        // executeInstruction();
        // resetVariablesBeforeNextInstruction();
    }
}

bool isImmediateValuePresent()
{
    return false;
}

bool isDisplacementPresent()
{
    return true;
}

bool isSIBPresent(int mod)
{
    return true;
}

bool isModRMPresent(int prefix, int esc_1, int esc_2, int opcode)
{
    return true;
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

bool isEscapeCode(int byte)
{
    switch(byte)
    {
        case OP_2_BYTE_ESCAPE:
        case OP_3_BYTE_ESCAPE_1:
        case OP_3_BYTE_ESCAPE_2:
            return true;
        default:
            return false;
    }
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