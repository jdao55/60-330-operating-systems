#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



int main(int argc, char * argv[])
{
    if(argc<2)
    {
        puts("Call with: q1 <32 bit adresses>");
        exit(1);
    }
    uint32_t addr=atol(argv[1]);
    uint32_t page=addr>>12;
    uint32_t offset=addr&0x00000fFF;
    printf("The address %d contains:\npage number = %d\noffset = %d\n", addr,page,offset);
    return 0;
}
