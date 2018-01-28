#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
    pid_t pid =fork();
    //parent sleeps
    if (pid>0)
        sleep(60);
    //check for fork error
    else if(pid<0)
    {
        perror("error while forking: ");
        exit(1);
    }
    //child exits
    else
    {
        printf("Zombie process created for 60 sec\n");
        exit(0);
    }
    

    return 0;
}
