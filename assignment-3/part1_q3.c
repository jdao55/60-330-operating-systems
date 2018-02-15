#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

int circle_count=0;
pthread_mutex_t mlock;

double rand_double();
void *point_gen(void* amount);

int main()
{
    srand(time(NULL));
    pthread_t tid[4];
    int err, i;
    int args=1000000;
    int targs=1000000/4;
    if (pthread_mutex_init(&mlock, NULL) != 0)
    {
        perror("\n mutex init failed\n");
        return 1;
    }
    for(i=0;i<4;i++)
    {
        err=pthread_create(&tid[i], NULL, point_gen, (void*)&targs);
        if(err)
        {
            perror("");
            exit(EXIT_FAILURE);
        }
    }
    for(i=0;i<4;i++)
    {
        pthread_join(tid[i], NULL);
    }
    double pi=4.0* (circle_count)/(double)args;
    printf("Caculated Pi value for %d hits out of %d points is:\n %lf\n",circle_count, args, pi);
    pthread_mutex_destroy(&mlock);
    return 0;
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
    pthread_mutex_lock(&mlock);
    circle_count+=hit_count;
    pthread_mutex_unlock(&mlock);
    return NULL;
}


double rand_double()
{ 
    return random()/((double)RAND_MAX+1);
}
