#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

int circle_count=0;
double rand_double();
void *point_gen(void* amount);

int main()
{
    srand(time(NULL));
    pthread_t tid;
    int err;
    int args=10000000;
    err=pthread_create(&tid, NULL, point_gen, (void*)&args);
    if(err)
    {
        perror("");
        exit(EXIT_FAILURE);
    }
    pthread_join(tid, NULL);
    double pi=4.0* (circle_count)/(double)args;
    printf("Caculated PI value for %d hits out of %d points is:\n %lf\n",circle_count, args, pi);   
}

void *point_gen(void* amount)
{
    int i, hit_count=0;
    double x,y;
    for(i=0;i<*((int *) amount);i++)
    {
        x=rand_double();
        y=rand_double();
        if(sqrt(x*x+y*y)<1.0)
        {
            ++hit_count;
        }
    }
    circle_count+=hit_count;
    return NULL;
}


double rand_double()
{ 
    return random()/((double)RAND_MAX+1);
}
