#include "instruction_impl.h"
#include "structs.h"

struct Opcode one_byte_opcode_map[16][16][12];
struct Opcode two_byte_opcode_map[16][16][12];
struct Opcode three_byte_opcode_map_1[16][16][12];
struct Opcode three_byte_opcode_map_2[16][16][12];

void init_one_byte_opcode_map(){

    one_byte_opcode_map[0][0][0].immdSize = 0;
    one_byte_opcode_map[0][0][0].modRM = true;

}