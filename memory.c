#ifndef MEMORY
#define MEMORY

unsigned int mem[100]; 

unsigned int mem_load(unsigned int addr)
{
    return 5;
}

void mem_store(unsigned int addr, int w_bit, unsigned int val)
{
    mem[10] = val;
}

#endif