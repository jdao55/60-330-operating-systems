#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

pthread_mutex_t mlock;
int circle_count=0;

double rand_double(uint *seed){return rand_r(seed)/((double)RAND_MAX+1);}
void *point_gen(void* amount);
void find_pi_q3(int point_num, int threads);
void find_pi_q4_2(int point_num);
void find_pi_q4_20(int point_num);
void find_pi_q4_40(int point_num);
void find_pi_q4_80(int point_num);
void find_pi_q4_100(int point_num);

int main()
{
   
    puts("Question 3");
    find_pi_q3(1000000,2);
    find_pi_q3(1000000,20);
    find_pi_q3(1000000,40);
    find_pi_q3(1000000,80);
    find_pi_q3(1000000,100);
   
    puts("\nQuestion 4");
    find_pi_q4_2(1000000);
    find_pi_q4_20(1000000);
    find_pi_q4_40(1000000);
    find_pi_q4_80(1000000);
    find_pi_q4_100(1000000);

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
    pthread_mutex_lock(&mlock);
    circle_count+=hit_count;
    pthread_mutex_unlock(&mlock);
    return NULL;
}

void find_pi_q3(int point_num, int threads)
{

    pthread_t *tid;
    int i;
    tid=(pthread_t *)malloc(sizeof(pthread_t)*threads);
    struct timeval t1, t2;
    double elapsedTime=0;
    int err;
    circle_count=0;
    
    gettimeofday(&t1, NULL);

    int thread_points=point_num/threads;
    for(i=0;i<threads;i++)
    {
        err=pthread_create(&tid[i], NULL, point_gen, (void*)&(thread_points));
        if(err)
        {
            perror("");
            exit(EXIT_FAILURE);
        }
    }
    
    
    for(i=0;i<threads;i++)
    {
        pthread_join(tid[i], NULL);
    }
    double pi=4.0* (circle_count)/(double)point_num;
    pthread_mutex_destroy(&mlock);
    free(tid);
    gettimeofday(&t2, NULL);
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("PI = %f points = %d \tmilisec=%lf slaves=%d\n",
           pi, point_num,elapsedTime, threads);   
}

void find_pi_q4_2(int point_num)
{
    uint seed;
    int i=0, hit_count;
    double x,y;
    circle_count=0;
    struct timeval t1, t2;
    double elapsedTime=0;
    gettimeofday(&t1, NULL);
    #pragma omp parallel private(x,y,seed, hit_count,i) shared(circle_count) num_threads(2)
    {
        hit_count=0;
        seed=25234 + 17* __builtin_omp_get_thread_num();
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
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("PI = %f points = %7d \tmilisec=%lf slaves=2\n",
           pi, point_num,elapsedTime); 
    
}
void find_pi_q4_20(int point_num)
{
    uint seed;
    int i=0, hit_count;
    double x,y;
    circle_count=0;
    struct timeval t1, t2;
    double elapsedTime=0;
    gettimeofday(&t1, NULL);
#pragma omp parallel private(x,y,seed, hit_count,i) shared(circle_count) num_threads(20)
    {
        hit_count=0;
        seed=25234 + 17* __builtin_omp_get_thread_num();
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
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("PI = %f points = %7d \tmilisec=%lf slaves=20\n",
           pi, point_num,elapsedTime); 
    
}
void find_pi_q4_40(int point_num)
{
    uint seed;
    int i=0, hit_count;
    double x,y;
    circle_count=0;
    struct timeval t1, t2;
    double elapsedTime=0;
    gettimeofday(&t1, NULL);
#pragma omp parallel private(x,y,seed, hit_count,i) shared(circle_count) num_threads(40)
    {
        hit_count=0;
        seed=25234 + 17* __builtin_omp_get_thread_num();
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
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("PI = %f points = %7d \tmilisec=%lf slaves=40\n",
           pi, point_num,elapsedTime); 
    
}
void find_pi_q4_80(int point_num)
{
    uint seed;
    int i=0, hit_count;
    double x,y;
    circle_count=0;
    struct timeval t1, t2;
    double elapsedTime=0;
    gettimeofday(&t1, NULL);
#pragma omp parallel private(x,y,seed, hit_count,i) shared(circle_count) num_threads(80)
    {
        hit_count=0;
        seed=25234 + 17* __builtin_omp_get_thread_num();
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
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("PI = %f points = %7d \tmilisec=%lf slaves=80\n",
           pi, point_num,elapsedTime); 
    
}
void find_pi_q4_100(int point_num)
{
    uint seed;
    int i=0, hit_count;
    double x,y;
    circle_count=0;
    struct timeval t1, t2;
    double elapsedTime=0;
    gettimeofday(&t1, NULL);
#pragma omp parallel private(x,y,seed, hit_count,i) reduction(+:circle_count) num_threads(100)
    {
        hit_count=0;
        seed=25234 + 17* __builtin_omp_get_thread_num();
        #pragma omp for
        for(i=0;i<point_num;i++)
        {
            x=rand_double(&seed);
            y=rand_double(&seed);
            if(sqrt(x*x+y*y)<1.0)
            {
                ++circle_count;
            }
            
        }
    }
              
    double pi=4.0* (circle_count/(double)point_num);
    gettimeofday(&t2, NULL);
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("PI = %f points = %7d \tmilisec=%lf slaves=100\n",
           pi, point_num,elapsedTime); 
    
}
