#include <stdbool.h>
#include "instruction_impl.h"

#ifndef STRUCT_OPCODE
#define STRUCT_OPCODE

struct Opcode {
   int immdSize;
   bool modRM;
   void (*instruction) (int mod, int reg, int rm, int scale, int index, int base, unsigned int dis, unsigned int immd);
};

#endif

#ifndef OPCODE_MAP
#define OPCODE_MAP

struct Opcode one_byte_opcode_map[16][16][12];
struct Opcode two_byte_opcode_map[16][16][12];
struct Opcode three_byte_opcode_map_1[16][16][12];
struct Opcode three_byte_opcode_map_2[16][16][12];

void init_one_byte_opcode_map(){
    // ADD
    one_byte_opcode_map[0][4][0].immdSize = 1;
    one_byte_opcode_map[0][4][0].modRM = false;
    one_byte_opcode_map[0][4][0].instruction = &add_immd_to_al_8bit;

    one_byte_opcode_map[0][5][0].immdSize = 4;
    one_byte_opcode_map[0][5][0].modRM = false;
    one_byte_opcode_map[0][5][0].instruction = &add_immd_to_eax_32bit;

    one_byte_opcode_map[8][0][0].immdSize = 1;
    one_byte_opcode_map[8][0][0].modRM = true;
    one_byte_opcode_map[8][0][0].instruction = &immd_to_reg_8bit;

    one_byte_opcode_map[8][1][0].immdSize = 4;
    one_byte_opcode_map[8][1][0].modRM = true;
    one_byte_opcode_map[8][1][0].instruction = &immd_to_reg_32bit;

    one_byte_opcode_map[8][3][0].immdSize = 1;
    one_byte_opcode_map[8][3][0].modRM = true;
    one_byte_opcode_map[8][3][0].instruction = &immd_to_reg_32bit_sign_extended;

    one_byte_opcode_map[0][0][0].immdSize = 0;
    one_byte_opcode_map[0][0][0].modRM = true;
    one_byte_opcode_map[0][0][0].instruction = &add_reg_to_rm_8bit;

    one_byte_opcode_map[0][1][0].immdSize = 0;
    one_byte_opcode_map[0][1][0].modRM = true;
    one_byte_opcode_map[0][1][0].instruction = &add_reg_to_rm_32bit;

    one_byte_opcode_map[0][2][0].immdSize = 0;
    one_byte_opcode_map[0][2][0].modRM = true;
    one_byte_opcode_map[0][2][0].instruction = &add_rm_to_reg_8bit;

    one_byte_opcode_map[0][3][0].immdSize = 0;
    one_byte_opcode_map[0][3][0].modRM = true;
    one_byte_opcode_map[0][3][0].instruction = &add_rm_to_reg_32bit;

    // AND
    one_byte_opcode_map[2][4][0].immdSize = 1;
    one_byte_opcode_map[2][4][0].modRM = false;
    one_byte_opcode_map[2][4][0].instruction = &and_immd_to_al_8bit;

    one_byte_opcode_map[0][5][0].immdSize = 4;
    one_byte_opcode_map[0][5][0].modRM = false;
    one_byte_opcode_map[0][5][0].instruction = &and_immd_to_eax_32bit;

    one_byte_opcode_map[8][0][0].immdSize = 1;
    one_byte_opcode_map[8][0][0].modRM = true;
    one_byte_opcode_map[8][0][0].instruction = &immd_to_reg_8bit;

    one_byte_opcode_map[8][1][0].immdSize = 4;
    one_byte_opcode_map[8][1][0].modRM = true;
    one_byte_opcode_map[8][1][0].instruction = &immd_to_reg_32bit;

    one_byte_opcode_map[8][3][0].immdSize = 1;
    one_byte_opcode_map[8][3][0].modRM = true;
    one_byte_opcode_map[8][3][0].instruction = &immd_to_reg_32bit_sign_extended;

    one_byte_opcode_map[2][0][0].immdSize = 0;
    one_byte_opcode_map[2][0][0].modRM = true;
    one_byte_opcode_map[2][0][0].instruction = &and_reg_to_rm_8bit;

    one_byte_opcode_map[2][1][0].immdSize = 0;
    one_byte_opcode_map[2][1][0].modRM = true;
    one_byte_opcode_map[2][1][0].instruction = &and_reg_to_rm_32bit;

    one_byte_opcode_map[2][2][0].immdSize = 0;
    one_byte_opcode_map[2][2][0].modRM = true;
    one_byte_opcode_map[2][2][0].instruction = &and_rm_to_reg_8bit;

    one_byte_opcode_map[2][3][0].immdSize = 0;
    one_byte_opcode_map[2][3][0].modRM = true;
    one_byte_opcode_map[2][3][0].instruction = &and_rm_to_reg_32bit;

    // LEA
    one_byte_opcode_map[8][13][0].immdSize = 0;
    one_byte_opcode_map[8][13][0].modRM = true;
    one_byte_opcode_map[8][13][0].instruction = &store_eff_addr_from_reg_32bit;

    // mov
    one_byte_opcode_map[8][8][0].immdSize = 0;
    one_byte_opcode_map[8][8][0].modRM = true;
    one_byte_opcode_map[8][8][0].instruction = &mov_reg1_to_reg2_8bit;

    one_byte_opcode_map[8][9][0].immdSize = 0;
    one_byte_opcode_map[8][9][0].modRM = true;
    one_byte_opcode_map[8][9][0].instruction = &mov_reg1_to_reg2_32bit;

    one_byte_opcode_map[8][10][0].immdSize = 0;
    one_byte_opcode_map[8][10][0].modRM = true;
    one_byte_opcode_map[8][10][0].instruction = &mov_rm_to_reg_8bit;

    one_byte_opcode_map[8][11][0].immdSize = 0;
    one_byte_opcode_map[8][11][0].modRM = true;
    one_byte_opcode_map[8][11][0].instruction = &mov_rm_to_reg_32bit;

    // // Mov (seg:offset) to AL
    // one_byte_opcode_map[10][0][0].immdSize = 1;
    // one_byte_opcode_map[10][0][0].modRM = false;
    // one_byte_opcode_map[10][0][0].instruction = &mov_disp8_to_al_8bit;

    // // Mov (seg:offset) to EAX
    // one_byte_opcode_map[10][1][0].immdSize = 4;
    // one_byte_opcode_map[10][1][0].modRM = false;
    // one_byte_opcode_map[10][1][0].instruction = &mov_disp32_to_eax_32bit;

    // // Mov AL to (seg:offset)
    // one_byte_opcode_map[10][2][0].immdSize = 1;
    // one_byte_opcode_map[10][2][0].modRM = false;
    // one_byte_opcode_map[10][2][0].instruction = &mov_al_to_disp8_8bit;

    // // Mov EAX to (seg:offset)
    // one_byte_opcode_map[10][3][0].immdSize = 4;
    // one_byte_opcode_map[10][3][0].modRM = false;
    // one_byte_opcode_map[10][3][0].instruction = &mov_eax_to_disp32_32bit;
    
    // MOV imm8 to r8 (B|0 -> 7)
    int i;
    for (i = 0; i < 8; i++)
    {
        one_byte_opcode_map[11][i][0].immdSize = 1;
        one_byte_opcode_map[11][i][0].modRM = false;
        one_byte_opcode_map[11][i][0].instruction = &mov_immd_to_reg_8bit;
    }
    // MOV imm32 to r32 (B|8 -> 15)
    for (i = 8; i < 16; i++)
    {
        one_byte_opcode_map[11][i][0].immdSize = 4;
        one_byte_opcode_map[11][i][0].modRM = false;
        one_byte_opcode_map[11][i][0].instruction = &mov_immd_to_reg_32bit;
    }

    // MOV imm8 to rm8
    one_byte_opcode_map[12][6][0].immdSize = 1;
    one_byte_opcode_map[12][6][0].modRM = true;
    one_byte_opcode_map[12][6][0].instruction = &mov_immd_to_rm_8bit;

    // MOV imm32 to rm32
    one_byte_opcode_map[12][7][0].immdSize = 4;
    one_byte_opcode_map[12][7][0].modRM = true;
    one_byte_opcode_map[12][7][0].instruction = &mov_immd_to_rm_32bit;

    // CMP
    one_byte_opcode_map[3][12][0].immdSize = 1;
    one_byte_opcode_map[3][12][0].modRM = false;
    one_byte_opcode_map[3][12][0].instruction = &cmp_immd_with_al_8bit;

    one_byte_opcode_map[3][13][0].immdSize = 4;
    one_byte_opcode_map[3][13][0].modRM = false;
    one_byte_opcode_map[3][13][0].instruction = &cmp_immd_with_eax_32bit;

    // INC
    one_byte_opcode_map[14][14][0].immdSize = 0;
    one_byte_opcode_map[14][14][0].modRM = true;
    one_byte_opcode_map[14][14][0].instruction = &inc_rm_8bit;
    
    one_byte_opcode_map[14][15][0].immdSize = 0;
    one_byte_opcode_map[14][15][0].modRM = true;
    one_byte_opcode_map[14][15][0].instruction = &inc_rm_32bit;


        // one_byte_opcode_map[][][0].immdSize = ;
    // one_byte_opcode_map[][][0].modRM = ;
    // one_byte_opcode_map[][][0].instruction = &;
    
}

#endif