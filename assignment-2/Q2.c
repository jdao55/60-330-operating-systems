#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>


void kill_ppid(char *str);
void show_proceses();
int main()
{
    //check if program Q1 is present
    if( access( "Q1", F_OK ) == -1 )
    {
        perror("Program Q1 not in current directory");
        exit(1);
    }
    // file exists
    puts("Forking and running Q1\n...\n");
    pid_t pid =fork();
    if (pid <0)
    {
        perror("error forking");
        exit(1);
    }
    //run Question 1 to create zombies
    else if (!pid)
    {
        //Runing Q1
        execlp("./Q1", "Q1", NULL);
    }
    else
    {
        FILE *fp;
        char *line=NULL;
        size_t len=0;
        
        //run ps
        printf("Proccess list \n");
        show_proceses();

        //kill zombies
        printf("\nkilling zombies processes\n");
        fp=popen("ps -l | grep defunct", "r");  
        //print output of ps, and kill any zombie processes
        while(getline(&line, &len, fp)!=-1)
            kill_ppid(line);
        pclose(fp);

        wait(NULL);
        //show processes after killing zombies
        printf("\n\nUpdated proccess list \n");
        show_proceses();
       
    }
    return 0;
}

void kill_ppid(char *str)
{
    int i;
    char * ppid, *pid;
    strtok(str, " ");
    for(i=0; i<2; i++)
    {
        strtok(NULL," ");
    }
    pid=strtok(NULL," ");
    ppid=strtok(NULL," ");
    printf("proccess %s is a zombie termimating parent process %s\n",pid, ppid);
    kill(atoi(ppid), SIGKILL);
}

void show_proceses()
{
    FILE *fp;
    char *line=NULL;
    size_t len=0;
    fp=popen("ps -l", "r");
   
    //print output of ps
    while(getline(&line, &len, fp)!=-1)
    {
        printf("%s", line);
    }
    pclose(fp);
}
