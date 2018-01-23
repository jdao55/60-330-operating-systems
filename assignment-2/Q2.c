#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
void get_process_info(const char* ps_out, char * ppid, char * cmd);

int main()
{
    pid_t pid =fork();
    if (pid <0)
    {
        perror("error forking");
        exit(1);
    }
    //run Question 1 to create zombies
    else if (!pid)
    {
        execlp("./Q1", "Q1", NULL);
    }
    else
    {
        FILE *fp;
        int status;
        char *line=NULL;
        size_t len=0;

        char ppid[8], cmd[20];

        //run ps
        fp=popen("ps -l", "r");

        //print output of ps, and kill any zombie processes
        while(getline(&line, &len, fp)!=-1)
        {
            printf("%s\n", line);
            get_process_info(line, ppid, cmd);
            //kill if parent if process is defunct(zombie)
            if(strstr(cmd, "<defunct>")!=NULL)
            {
                kill(atoi(ppid), SIGKILL);
            }
        }
        status = pclose(fp);


        //show processes after killing zombies
        fp=popen("ps -l", "r");
        while(getline(&line, &len, fp)!=-1)
        {
            printf("%s\n", line);
        }
        status = pclose(fp);

        
        
    }
    return 0;
}
