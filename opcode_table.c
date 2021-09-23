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

    // immediate
    one_byte_opcode_map[12][6][0].immdSize = 1;
    one_byte_opcode_map[12][6][0].modRM = true;
    one_byte_opcode_map[12][6][0].instruction = &mov_immd_to_rm_8bit;

    one_byte_opcode_map[12][7][0].immdSize = 4;
    one_byte_opcode_map[12][7][0].modRM = true;
    one_byte_opcode_map[12][7][0].instruction = &mov_immd_to_rm_32bit;

    // 0 -> 7 = immd8
    int i;
    for (i = 0; i < 8; i++)
    {
        one_byte_opcode_map[11][i][0].immdSize = 1;
        one_byte_opcode_map[11][i][0].modRM = false;
        one_byte_opcode_map[11][i][0].instruction = &mov_immd_to_reg_8bit;
    }
    // 8 -> 15 = imm32
    for (i = 8; i < 16; i++)
    {
        one_byte_opcode_map[11][i][0].immdSize = 4;
        one_byte_opcode_map[11][i][0].modRM = false;
        one_byte_opcode_map[11][i][0].instruction = &mov_immd_to_reg_32bit;
    }
    
    // // displacement & reg
    // one_byte_opcode_map[11][0][0].immdSize = 0;
    // one_byte_opcode_map[11][0][0].modRM = false;
    // one_byte_opcode_map[11][0][0].instruction = &mov_mem_to_al_8bit;

    // one_byte_opcode_map[11][1][0].immdSize = 0;
    // one_byte_opcode_map[11][1][0].modRM = false;
    // one_byte_opcode_map[11][1][0].instruction = &mov_mem_to_eax_32bit;

    // one_byte_opcode_map[11][2][0].immdSize = 0;
    // one_byte_opcode_map[11][2][0].modRM = false;
    // one_byte_opcode_map[11][2][0].instruction = &mov_al_to_mem_8bit;

    // one_byte_opcode_map[11][3][0].immdSize = 0;
    // one_byte_opcode_map[11][3][0].modRM = false;
    // one_byte_opcode_map[11][3][0].instruction = &mov_eax_to_mem_32bit;

    // one_byte_opcode_map[][][0].immdSize = ;
    // one_byte_opcode_map[][][0].modRM = ;
    // one_byte_opcode_map[][][0].instruction = &;
    
}

#endif