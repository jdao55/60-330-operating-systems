#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <omp.h>

pthread_mutex_t mlock;
pthread_mutex_t mlock_2;
int circle_count=0;

double rand_double(uint *seed){return rand_r(seed)/((double)RAND_MAX+1);}
void *point_gen(void* amount);
void find_pi_q3(int point_num, int threads_num);
void find_pi_q4(int point_num, int threads_num);
int main()
{
    puts("1st call to loads fucntions to cache");
    find_pi_q3(1,1);
    find_pi_q4(1,1);
    puts("\nBechmarks:");
   
    puts("Question 3");
    find_pi_q3(1000000,2);
    find_pi_q3(1000000,20);
    find_pi_q3(1000000,40);
    find_pi_q3(1000000,80);
    find_pi_q3(1000000,100);
   
    puts("\nQuestion 4");
    find_pi_q4(1000000,2);
    find_pi_q4(1000000,20);
    find_pi_q4(1000000,40);
    find_pi_q4(1000000,80);
    find_pi_q4(1000000,100);

    return 0;
}

void *point_gen(void* amount)
{
    pthread_mutex_lock(&mlock_2);
    uint seed=time(NULL);//(25234 + 19*(time(NULL)%113));
    pthread_mutex_unlock(&mlock_2);
    int i, hit_count=0;
    double x,y;
    for(i=0;i<*((int *) amount);i++)
    {
        x=rand_double(&seed);
        y=rand_double(&seed);
        if((x*x+y*y)<1.0)
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
    if (pthread_mutex_init(&mlock, NULL) != 0 || pthread_mutex_init(&mlock_2, NULL) != 0)
    {
        perror("mutex init failed:");
        exit(1);
    }
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

    //free resources
    pthread_mutex_destroy(&mlock);
    pthread_mutex_destroy(&mlock_2);
    free(tid);

    gettimeofday(&t2, NULL);
    elapsedTime += (1000000*(t2.tv_sec-t1.tv_sec)+(t2.tv_usec - t1.tv_usec)) / 1000.0;

    printf("PI = %f points = %d \tmilisec=%lf slaves=%d\n",
           pi, point_num,elapsedTime, threads);   
}

void find_pi_q4(int point_num, int threads_num)
{
    uint seed;
    int i=0;
    double x,y;
    circle_count=0;
    struct timeval t1, t2;
    double elapsedTime=0;
    gettimeofday(&t1, NULL);
    #pragma omp parallel private(x,y,seed, i) reduction(+:circle_count) num_threads(threads_num)
    {
        circle_count=0;
        seed=time(NULL) + 17* omp_get_thread_num();
        #pragma omp for
        for(i=0;i<point_num;i++)
        {
            x=rand_double(&seed);
            y=rand_double(&seed);
            if((x*x+y*y)<1.0)
            {
                circle_count+=1;
            }
        }
    }
    //calc pi          
    double pi=4.0* (circle_count/(double)point_num);
    //get elapsedtime
    gettimeofday(&t2, NULL);
    elapsedTime += (1000000*(t2.tv_sec-t1.tv_sec)+(t2.tv_usec - t1.tv_usec)) / 1000.0;

    printf("PI = %f points = %7d \tmilisec=%lf slaves=%d\n",
           pi, point_num, elapsedTime, threads_num); 
    
}
