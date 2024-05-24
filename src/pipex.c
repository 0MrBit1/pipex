#include "../include/pipex.h"




void dup_fds(int fd ,  int pipefd , int fd_dup , int pipe_dup )
{

    if ( dup2(fd , fd_dup) < 0 )
    {
        perror("error: \n");
        exit(1);
    } 
    if (dup2(pipefd , pipe_dup) < 0 )
    {
        perror("error: \n");
        exit(1);
    }


}
void child_process1(char **argv , char **envp  , int *pipefd )
{
    int     i;
    char    *cmd;
    char    **args;
    int     fd; 

    close(pipefd[0]);
    i = 0;
    args = ft_split(argv[2] , ' ');
    fd = open(argv[1] , O_RDONLY) ; 
    if (fd < 0)
    { 
        perror("error: \n");
        exit(1);
    }
    dup_fds(fd ,  pipefd[1] , 0 , 1);
    while(envp[i])
    {
        if (!  ft_strncmp( envp[i], "PATH=" , 5 ))
            cmd = get_command_path(args[0] , envp[i] + 5);
        i++;
    }

    execve(cmd , args , envp);
    perror ("error exece cmd1 \n");
    exit(1);
}

void child_process2(char **argv , char **envp  , int *pipefd )
{
    int     i;
    char    *cmd;
    char    **args;
    int     fd;

    close(pipefd[1]);
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
    dup_fds(fd ,  pipefd[0] , 1 , 0);
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
void parent_process(int *pipefd , char **argv , char **envp )
{
    int i;
    pid_t   pid;

    i = 0;
    while ( i < 2)
    {
        pid = fork() ;
        if (pid < 0)
        {
            perror("failed to fork child process\n");
            exit(1);
        }
        if (pid == 0)
        {
            if (i == 0)
                child_process1(argv , envp , pipefd);
            else if (i == 1)
                child_process2(argv , envp  , pipefd );
        }
        i++ ; 
    }
    close(pipefd[0]);
    close(pipefd[1]); 
    while(wait(NULL) != -1);
}

int main(int argc , char **argv , char **envp )
{
    int     pipefd[2];
   

    error_handler(argc , pipefd) ;
    parent_process(pipefd , argv , envp );
}
