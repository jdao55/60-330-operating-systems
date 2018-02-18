#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char * argv[])
{
    if(argc<2)
    {
        puts("Call with: q2 <number of adresses>");
        exit(1);
    }
    //init variables
    size_t i, addr_count=atoi(argv[1]);
    uint seed=time(NULL);
    uint *rand_num;
    srand(seed);
    clock_t time;
    double elapse_time;
    uint32_t page,offset;

    //init random address array
    rand_num=(uint *)malloc(addr_count*sizeof(uint));
    for(i=0;i<addr_count;i++)
    {
        rand_num[i]=rand();
    }
    //find addresses page and offset & find cpu time 
    time=clock();
    for(i=0;i<addr_count;i++)
    {
        page=rand_num[i]>>12;
        offset=rand_num[i] & 0x0FFF;
    }
    time=clock()-time;
    elapse_time=time/(CLOCKS_PER_SEC/1000.0);
    free(rand_num);

    printf("it took %ld cpu time or %.2lf milisec \n\
to find offset and page number of %ld addresses\n", time, elapse_time, addr_count);
    return 0;
}
