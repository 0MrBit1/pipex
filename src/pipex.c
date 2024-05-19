#include "../include/pipex.h"

void child_process1(char **argv , char **envp , int pipe_write)
{
    int i;
    char *cmd;

    i = 0 ; 
    while(envp[i])
    {
        if (!  ft_strncmp(envp[i] ,  "PATH=" , 5 ) )
        {
            cmd = get_command_path(char *cmd , envp[i] + 5) ;
        }

    }

}

void child_process2(char **argv , char **envp  , int pipe_write)
{


}

int main(int argc , char **argv , char *envp )
{
    pid_t   pid;
    int     pipefd[2]; 

    if (pipe(pipefd) < 0 )
    {
        perror("There was an error creating the pipe , please try again.\n"); 
        return 1;
    }
    pid = fork();
    if (pid == 0)
    {
        child_process1( argv , pipefd[1] ) ;
    }
    pid = fork() ; 
    if (pid == 0)
    {
        child_process2(argv , pipefd[1] ) ;
    }
}
