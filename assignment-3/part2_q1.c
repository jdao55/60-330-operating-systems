#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

int circle_count=0;
double rand_double(uint *seed){return rand_r(seed)/((double)RAND_MAX+1);}
void *point_gen(void* amount);
void find_pi_q1(int point_num);
void find_pi_q2(int point_num);

int main()
{
    puts("1st call is repeated to load fucntions to cache");
    puts("\nBechmarks:");
    puts("Question 1");
     find_pi_q1(100);
    find_pi_q1(100);
    find_pi_q1(1000);
    find_pi_q1(10000);
    find_pi_q1(100000);
    find_pi_q1(1000000);
    puts("\nQuestion 2");
    find_pi_q2(100);
    find_pi_q2(100);
    find_pi_q2(1000);
    find_pi_q2(10000);
    find_pi_q2(100000);
    find_pi_q2(1000000);
    return 0;
}

void *point_gen(void* amount)
{
    uint seed=time(NULL);
    int i, hit_count=0;
    double x,y;
    for(i=0;i<*((int *) amount);i++)
    {
        x=rand_double(&seed);
        y=rand_double(&seed);
        if(sqrt(x*x+y*y)<1.0)
        {
            ++hit_count;
        }
    }
    circle_count+=hit_count;
    return NULL;
}

void find_pi_q1(int point_num)
{

    pthread_t tid;
    struct timeval t1, t2;
    double elapsedTime=0;
    int err;
    circle_count=0;
    gettimeofday(&t1, NULL);
    err=pthread_create(&tid, NULL, point_gen, (void*)&point_num);
    if(err)
    {
        perror("");
        exit(EXIT_FAILURE);
    }
    pthread_join(tid, NULL);
    double pi=4.0* (circle_count)/(double)point_num;
    gettimeofday(&t2, NULL);
    elapsedTime += (1000000*(t2.tv_sec-t1.tv_sec)+(t2.tv_usec - t1.tv_usec)) / 1000.0;
    printf("Caculated PI = %f using %7d points in %lf milisec\n",
           pi, point_num,elapsedTime);   
}
void find_pi_q2(int point_num)
{
    uint seed;
    int i=0, hit_count;
    double x,y;
    circle_count=0;
    struct timeval t1, t2;
    double elapsedTime=0;
    gettimeofday(&t1, NULL);
    #pragma omp parallel private(x,y,seed, hit_count,i) shared(circle_count)
    {
        hit_count=0;
        seed=25234 + 17*__builtin_omp_get_thread_num();
        #pragma omp for
        for(i=0;i<point_num;i++)
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
              
    double pi=4.0* (circle_count/(double)point_num);
    gettimeofday(&t2, NULL);
    elapsedTime += (1000000*(t2.tv_sec-t1.tv_sec)+(t2.tv_usec - t1.tv_usec)) / 1000.0;
    printf("Caculated PI = %f using %7d points in %lf milisec\n",
           pi, point_num,elapsedTime); 
    
}
