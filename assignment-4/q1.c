#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/*
typedef struct
{
    uint32_t page;
    uint32_t offset;
    
}address;
*/

void get_addr(uint64_t addr)
{
    uint64_t page=addr>>12;
    uint64_t offset=addr&0x00000fFF;
    printf("The address %lu contains:\npage number = %lu\noffset = %lu\n", addr,page,offset);
    
}

int main(int argc, char * argv[])
{
    unsigned long addr=atoll(argv[1]);
    get_addr(addr);
    return 0;
}
