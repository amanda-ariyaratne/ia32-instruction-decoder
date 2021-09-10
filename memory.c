#ifndef MEMORY
#define MEMORY

// #define SIZE 100

// struct MemLoc {
//    unsigned int addr;   
//    unsigned int val;
// };

// struct MemLoc* hashArray[SIZE]; 
// struct MemLoc* dummyItem;
// struct MemLoc* item;

// int hashCode(int key) {
//    return key % SIZE;
// }

unsigned int mem_load(unsigned int addr)
{
    return 5;
}

void mem_store(unsigned int addr, int w_bit, unsigned int val)
{
    return;
}

#endif