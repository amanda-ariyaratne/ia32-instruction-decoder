#include <stdbool.h>

struct Opcode {
   bool SIB;
   bool dis;
   bool immd;
   bool modRM;
   int (*instruction) (int a, int b, int c);
};