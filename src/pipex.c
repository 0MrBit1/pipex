#include "../include/pipex.h"

int child_process()
{




    
}

int main(int argc , char **argv  )
{
    pid_t   child_pid;
    int     pipefd[2]; 

    if (pipe(pipefd) < 0 )
    {
        perror("There was an error creating the pipe , please try again.\n"); 
        return 1;
    }
    child_pid  = fork();
    if (child_pid)
    {
        close(pipefd[0]);
        return (0);
    }
    child_process(argv , pipefd[1]);
}
