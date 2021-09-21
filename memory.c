#ifndef MEMORY
#define MEMORY

#define SIZE 20

struct MemLoc {
   unsigned int addr;   
   unsigned int val;
};

struct MemLoc* mem[SIZE]; 
struct MemLoc* item;

unsigned int hash(unsigned int addr) {
   return addr % SIZE;
}

unsigned int mem_load(unsigned int addr, int w) {
    int hashIndex = hash(addr);  
   
    while(mem[hashIndex] != NULL) {
        if(mem[hashIndex]->addr == addr)
        {
            if (w)
                return mem[hashIndex]->val; 
            else
                return (mem[hashIndex]->val) & 255;
        }
            
      
        ++hashIndex;
        hashIndex %= SIZE;
   }        
	
   return 0;        
}

void mem_store(unsigned int addr, int w, unsigned int val)
{
    int hashIndex = hash(addr);  
   
    while(mem[hashIndex] != NULL) {
        if(mem[hashIndex]->addr == addr)
        {
            if (w)
                mem[hashIndex]->val = val; 
            else
                mem[hashIndex]->val = (mem[hashIndex]->val & 0xffffff00) + (val & 255);
            
            return;
        }
        ++hashIndex;
        hashIndex %= SIZE;
   }        
	
    struct MemLoc *item = (struct MemLoc*) malloc(sizeof(item));
    item->addr = addr;  
    item->val = val;

    while(mem[hashIndex] != NULL) {
        ++hashIndex;
        hashIndex %= SIZE;
    }
	
   mem[hashIndex] = item;
   return;
}

#endif