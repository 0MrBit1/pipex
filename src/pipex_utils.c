#include "../include/pipex.h"

char *cmd_helper(char *cmd , char *PATH_VARIABLE , int start , int i )
{
    char    *cmd_path;
    char    *potencial_path;

    while(PATH_VARIABLE[i])
    {   
        if (PATH_VARIABLE[i] == ':')
        {
            potencial_path = ft_substr(PATH_VARIABLE , start , i - start ) ;
            cmd_path = ft_strjoin(potencial_path , cmd);
            free(potencial_path);
            if (!access(cmd_path , X_OK))
            {
                free(cmd);
                return cmd_path;
            }
            else 
                free(cmd_path);
            start = ++i; 
        }
        i++;
    }
    return NULL ;
}
char *get_command_path(char *cmd , char *PATH_VARIABLE)
{
    char    *cmd_path;

    if (!access(cmd , X_OK))
        return cmd;
    cmd = ft_strjoin("/" , cmd); 
    cmd_path = cmd_helper(cmd , PATH_VARIABLE , 0 , 0 ); 
    return cmd_path;
}
void dup_fds(int fd ,  int pipefd , int fd_dup , int pipe_dup )
{
    if (dup2(fd , fd_dup) < 0 )
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
char *return_command(char **args , char **envp)
{
    int i ;

    i = 0;
    while(envp[i])
    {
        if (!  ft_strncmp( envp[i], "PATH=" , 5 ))
            return get_command_path(args[0] , envp[i] + 5);
        i++;
    }
    return NULL;
}
void error_handler(int argc , int *pipefd)
{
    if (argc != 5)
    {
        perror("Please follow this format : in_file cmd1 cmd2 out_file\n");
        exit(1);
    }
    if ( pipe(pipefd) < 0 )
    {
        perror("There was an error creating the pipe\n"); 
        exit(1);
    }
}
