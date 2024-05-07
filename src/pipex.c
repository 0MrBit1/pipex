#include "../include/pipex.h"

char *read_file_content(char *file_path)
{
    char    *line;
    char    *file_content;
    int     fd;
    char    *to_free;

    fd = open(file_path , O_RDONLY);
    if (fd < 0)
        perror("error reading file");
    line = get_next_line(fd);
    file_content = ft_strdup("");
    while(line)
    {
        to_free = file_content;
        file_content = ft_strjoin(file_content , line); 
        free(to_free);
        free(line);
        line = get_next_line(fd);
    }
    return file_content; 
}

char *get_command_path(char *cmd)
{
    char    *PATH_VARIABLE;
    int     i;
    int     start;
    char    *cmd_path;
    char    *potencial_path;

    i = 0;
    start = 0;
    PATH_VARIABLE = "/home/abdo1/.local/bin:/home/abdo1/bin:/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin";
    while(PATH_VARIABLE[i])
    {
        if (PATH_VARIABLE[i] == ':')
        {
            potencial_path = ft_substr(PATH_VARIABLE , start , i - start ) ;
            cmd_path = ft_strjoin(potencial_path , cmd);
            free(potencial_path);
            if (!access(cmd_path , X_OK))
                return cmd_path;
            else 
                free(cmd_path);
            start = ++i; 
        }
        i++;
    }
    return NULL;
}

void child_of_child(char **argv , int pipe_write)
{
    int fd;
    char *cmd_path; 

    fd = open(argv[1] , O_RDONLY);
    dup2(fd , 0);
    dup2(pipe_write ,1 );
    cmd_path = get_command_path("/cat");
    execve(cmd_path ,  NULL , NULL);
}

void child_process(char **argv , int pipe_write)
{
    int     fd;
    char    *cmd_path;
    int     child_pid;
    int     pipefd[2];
    
    child_pid = fork();
    pipe(pipefd);
    if (child_pid)
    {
        waitpid(child_pid , NULL , 0);

        fd = open(argv[1] , O_RDONLY);
        dup2(fd , 0);
        dup2(pipe_write ,1 );
        cmd_path = get_command_path("/cat");
        execve(cmd_path ,  NULL , NULL);
    }
   child_of_child(argv , pipefd[1]);
}

int main(int argc , char **argv)
{
    pid_t child_pid;
    int pipefd[2] ; 
    
    child_pid  = fork();
    pipe(pipefd);
    if (child_pid)
    {
        waitpid(child_pid , NULL , 0);
        return 0;
    }
    child_process(argv , pipefd[1]);
}

