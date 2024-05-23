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
        perror("error: \n");
        exit(1);
    }
    while(envp[i])
    {
        if (!  ft_strncmp( envp[i], "PATH=" , 5 ))
            cmd = get_command_path(args[0] , envp[i] + 5);
        i++;
    }
    if ( dup2(fd , 0) < 0 )
    {
        perror("error: \n");
    } 
    if (dup2(pipe_write , 1) < 0 )
    {
        perror("error: \n");
    }
    execve(cmd , args , envp);
    perror ("error exece cmd1 \n");
    exit(1);
}

void child_process2(char **argv , char **envp  , int pipe_read )
{
    int     i;
    char    *cmd;
    char    **args;
    int     fd;

    i = 0;
    args = ft_split(argv[3] , ' ');
    fd = open(argv[4] , O_WRONLY | O_CREAT | O_TRUNC, 0666) ;
    if (fd < 0)
        perror("error : \n");
    while(envp[i])
    {
        if (! ft_strncmp( envp[i], "PATH=" , 5 ))
            cmd = get_command_path(args[0], envp[i] + 5);
        i++;
    }
    if (dup2(fd , 1) < 0 )
        perror("error: \n");
    if (dup2(pipe_read , 0) < 0  )
        perror("error: \n");
    execve(cmd, args , envp);
    perror ("error exece cmd2 \n");
    exit (1);
}

void error_handler(int argc , int *pipefd)
{

    if (argc != 5)
    {
        perror("Please entre the arguments properly\n");
        exit(1);
    }
    if ( pipe(pipefd) < 0 )
    {
        perror("There was an error creating the pipe\n"); 
        exit(1);
    }

}

int main(int argc , char **argv , char **envp )
{
    pid_t   pid;
    int     pipefd[2];

    error_handler(argc , pipefd ) ; 
    if ((pid = fork()) < 0)
    {
        perror("failed to fork child process\n");
        exit(1);
    }
    if (pid == 0)
    {
        close(pipefd[0]); 
        child_process1(argv , envp , pipefd[1]);
    }
    if ((pid = fork()) < 0)
    {
        printf ("error \n"); 
        exit(1);
    }
    if (pid == 0)
    {
        close(pipefd[1] );
        child_process2(argv , envp  , pipefd[0] );
    }
    close(pipefd[0]);
    close(pipefd[1]); 
    while(wait(NULL) != -1) ;
}