#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

int circle_count=0;
double rand_double(uint *seed){return rand_r(seed)/((double)RAND_MAX+1);}

int main()
{
    uint seed;
    const int args=100000000;
    int i=0, hit_count;
    double x,y;
    

    #pragma omp parallel private(x,y,seed, hit_count,i) shared(circle_count)
    {
        hit_count=0;
        seed=25234 + 17* __builtin_omp_get_thread_num();
        #pragma omp for
        for(i=0;i<args;i++)
        {
            x=rand_double(&seed);
            y=rand_double(&seed);
            if(sqrt(x*x+y*y)<1.0)
            { 
                ++hit_count;
            }
            
        }
        #pragma omp critical
        {
            circle_count+=hit_count;
        }
    }
              
    double pi=4.0* (circle_count/(double)args);
    printf("Caculated PI value for %d hits out of %d points is:\n %lf\n",circle_count, args, pi);
    
    return 0;
}
