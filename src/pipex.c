#include "../include/pipex.h"

void child_process1(char **argv , char **envp  , int pipe_write )
{
    int     i;
    char    *cmd;
    char    **args;
    int     fd; 

    i = 0;
    args = ft_split(argv[2] , ' ');
    fd = open(argv[1] , O_RDONLY) ; 
    if (fd < 0)
    { 
        perror("error:");
        
    }
    while(envp[i])
    {
        if (!  ft_strncmp( envp[i], "PATH=" , 5 ))
        {  
            cmd = get_command_path(args[0] , envp[i] + 5);
        }
        i++;
    }
    if ( dup2(fd , 0) < 0 )
    {
        perror("error:");
    } 
    if (dup2(pipe_write , 1) < 0)
    {
        perror("error : ");
    } 
    execve(cmd , args , envp);
}

void child_process2(char **argv , char **envp  , int pipe_read )
{

    int     i;
    char    *cmd;
    char    **args;
    int     fd;

    i = 0;
    args = ft_split(argv[3] , ' ');
    fd = open(argv[4] , O_WRONLY) ;
    if (fd < 0)
    {
        perror("error : ");
    }
    while(envp[i])
    {
        if (! ft_strncmp( envp[i], "PATH=" , 5 ))
        {
            cmd = get_command_path(argv[3] , envp[i] + 5);
        }
        i++;
    }
    if (dup2(pipe_read , 0) < 0  )
    {
        perror("error:");
    }
    if (dup2(fd , 1) < 0 )
    {
        perror("error:");
    }
    execve(cmd, argv , envp);
}

int main(int argc , char **argv , char **envp )
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
        close(pipefd[0]); 
        child_process1(argv , envp , pipefd[1]); 
    }
    pid = fork() ; 
    if (pid == 0)
    {
        close(pipefd[1] );
        child_process2(argv , envp  , pipefd[0] );
    }
    close(pipefd[0]);
    close(pipefd[1]); 
    while(wait(NULL) == -1) ;
}
