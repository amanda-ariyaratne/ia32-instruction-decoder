#include <stdbool.h>
#include "enums.c"

void decode(char* instructions, int bytes)
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

    while (byte = getNextByte(instructions, ++cur_byte, bytes))
    {
        if (isPrefix(byte))
        {
            prefix = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        }
            
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
        
        opcode = byte;
        byte = getNextByte(instructions, ++cur_byte, bytes);

        if (isModRMPresent(prefix, esc_1, esc_2, opcode))
        {
            int mod = byte && 7;
            int reg_or_op = byte && 56;
            int rm = byte && 192;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        }

        if (isSIBPresent(mod))
        {
            scale = byte && 7;
            index = byte && 56;
            base = byte && 192;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        }
        
        if (isDisplacementPresent())
        {
            dis = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        }

        if (isImmediateValuePresent())
        {
            immd = byte;
        }

        executeInstruction();
        resetVariablesBeforeNextInstruction();
    }
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

int getNextByte(char* instructions, int current_byte, int total_bytes)
{
    if (current_byte == total_bytes)
    {
        return -1;
    }

    int byte = (instructions[current_byte] << 4) + instructions[current_byte + 1];
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