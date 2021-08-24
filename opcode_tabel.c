#include "instruction_impl.h"
#include "structs.h"

struct Opcode one_byte_opcode_map[16][16][12];
struct Opcode two_byte_opcode_map[16][16][12];
struct Opcode three_byte_opcode_map_1[16][16][12];
struct Opcode three_byte_opcode_map_2[16][16][12];

void initialize_opcode_map(){

    one_byte_opcode_map[0][0][0].dis = 1;
    one_byte_opcode_map[0][0][0].immd = 1;
    one_byte_opcode_map[0][0][0].modRM = 1;
    one_byte_opcode_map[0][0][0].SIB = 1;
    one_byte_opcode_map[0][0][0].instruction = opcode_1;

    one_byte_opcode_map[0][0][1].dis = 1;
    one_byte_opcode_map[0][0][1].immd = 1;
    one_byte_opcode_map[0][0][1].modRM = 1;
    one_byte_opcode_map[0][0][1].SIB = 1;
    one_byte_opcode_map[0][0][1].instruction = opcode_2;

    one_byte_opcode_map[0][0][2].dis = 1;
    one_byte_opcode_map[0][0][2].immd = 1;
    one_byte_opcode_map[0][0][2].modRM = 1;
    one_byte_opcode_map[0][0][2].SIB = 1;
    one_byte_opcode_map[0][0][2].instruction = opcode_3;

    one_byte_opcode_map[0][0][3].dis = 1;
    one_byte_opcode_map[0][0][3].immd = 1;
    one_byte_opcode_map[0][0][3].modRM = 1;
    one_byte_opcode_map[0][0][3].SIB = 1;
    one_byte_opcode_map[0][0][3].instruction = opcode_4;
}