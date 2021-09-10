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

    one_byte_opcode_map[0][4][0].immdSize = 1;
    one_byte_opcode_map[0][4][0].modRM = false;
    one_byte_opcode_map[0][4][0].instruction = &add_immd_to_al_8bit;

    one_byte_opcode_map[0][5][0].immdSize = 4;
    one_byte_opcode_map[0][5][0].modRM = false;
    one_byte_opcode_map[0][5][0].instruction = &add_immd_to_eax_32bit;

    one_byte_opcode_map[8][0][0].immdSize = 1;
    one_byte_opcode_map[8][0][0].modRM = true;
    one_byte_opcode_map[8][0][0].instruction = &add_immd_to_reg_8bit;

    one_byte_opcode_map[8][1][0].immdSize = 4;
    one_byte_opcode_map[8][1][0].modRM = true;
    one_byte_opcode_map[8][1][0].instruction = &add_immd_to_reg_32bit;

    one_byte_opcode_map[8][3][0].immdSize = 1;
    one_byte_opcode_map[8][3][0].modRM = true;
    one_byte_opcode_map[8][3][0].instruction = &add_immd_to_reg_32bit_sign_extended;

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

    // one_byte_opcode_map[][][0].immdSize = ;
    // one_byte_opcode_map[][][0].modRM = ;
    // one_byte_opcode_map[][][0].instruction = &;

}

#endif