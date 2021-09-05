#include <stdbool.h>

struct Opcode {
   int immdSize;
   bool modRM;
   int (*instruction) (int reg, int reg_or_op, int rm, int scale, int index, int base, int dis, int immd);
};