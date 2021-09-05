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
    int dis = -1;
    int disSize = -1;
    int immd = -1;

    while (true)
    {
        byte = getNextByte(instructions, ++cur_byte, bytes);
        if (byte == -1)
            break;

        if (isPrefix(byte))
        {
            prefix = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        }

        if (byte == OP_2_BYTE_ESCAPE)
        {
            esc_1 = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        } 

        if (esc_1 == OP_2_BYTE_ESCAPE && (byte == OP_3_BYTE_ESCAPE_1 || byte = OP_3_BYTE_ESCAPE_2))
        {
            esc_2 = byte;
            byte = getNextByte(instructions, ++cur_byte, bytes);
        }
        
        opcode = byte;

        Opcode opcode_details;
        if (esc_1 == -1)
            opcode_details = one_byte_opcode_map[opcode & 0xf0][opcode & 0x0f][prefix];
        else if (esc_2 == -1)
            opcode_details = two_byte_opcode_map[opcode & 0xf0][opcode & 0x0f][prefix];
        else if (esc_2 == OP_3_BYTE_ESCAPE_1)
            opcode_details = three_byte_opcode_map_1[opcode & 0xf0][opcode & 0x0f][prefix];
        else if (esc_2 == OP_3_BYTE_ESCAPE_2)
            opcode_details = three_byte_opcode_map_2[opcode & 0xf0][opcode & 0x0f][prefix];

        if (opcode_details.modRM)
        {
            byte = getNextByte(instructions, ++cur_byte, bytes);
            mod = byte & 7;
            reg_or_op = (byte & 56) >> 3;
            rm = (byte & 192) >> 6;

            if(isSIBPresent(mod, reg_or_op, rm))
            {
                byte = getNextByte(instructions, ++cur_byte, bytes);
                scale = byte & 7;
                index = (byte & 56) >> 3;
                base = (byte & 192) >> 6;
            }

            disSize = getDisSize(mod, reg_or_op, rm);

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
                    dis += (dis << 8) + byte;
                    byte = getNextByte(instructions, ++cur_byte, bytes);
                    dis += (dis << 8) + byte;
                    byte = getNextByte(instructions, ++cur_byte, bytes);
                    dis += (dis << 8) + byte;
                    break;
                default:
                    break;
            }
        }

        if (opcode_details.immdSize)
        {
            byte = getNextByte(instructions, ++cur_byte, bytes);
            immd = byte;
        }

        executeInstruction();
        resetVariablesBeforeNextInstruction();
    }
}

bool isSIBPresent(int mod, int reg_or_op, int rm)
{
    switch (mod)
    {
        case 0:
        case 1:
            if rm == 4:
                return true;
            return false;

        default:
            return false;
    }
}

bool getDisSize(int mod, int reg_or_op, int rm)
{
    switch (mod)
    {
        case 0:
            if rm == 5:
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

int getAddrFromSIB_8bit(int mod, int scale, int index, int base, int dis)
{
    int addr;
    int w_bit = 0;

    if (base == 5)
    {
        addr = reg(index, w_bit) * scale + reg(base, w_bit);
    } else {
        switch (mod)
        {
            case 0:
                addr = reg(index, w_bit) * scale + dis;
                break;
            case 1:
            case 2:
                addr = reg(index, w_bit) * scale + dis + reg(5, w_bit);
                break;  
            default:
                break;
        }
    }

    return addr;
}

int getAddrFromSIB_32bit(int mod, int scale, int index, int base, int dis)
{
    int addr;
    int w_bit = 1;

    if (base == 5)
    {
        addr = reg(index, w_bit) * scale + reg(base, w_bit);
    } else {
        switch (mod)
        {
            case 0:
                addr = reg(index, w_bit) * scale + dis;
                break;
            case 1:
            case 2:
                addr = reg(index, w_bit) * scale + dis + reg(5, w_bit);
                break;  
            default:
                break;
        }
    }

    return addr;
}

int sign_extend(int val)
{
    
}