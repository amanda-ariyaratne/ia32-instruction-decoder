#include <stdbool.h>

struct Opcode {
   int immdSize;
   bool modRM;
   int (*instruction) (int mod, int reg, int rm, int scale, int index, int base, int dis, int immd);
};