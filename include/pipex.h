#include "libft.h"
#include "ft_printf.h"
#include <sys/wait.h>
#include <fcntl.h>

int get_pipes_number(char **argv);
char *get_command_path(char *cmd , char *PATH_VARIABLE);
void error_handler(int argc , int *pipefd); 
char *return_command(char **args , char **envp);
void dup_fds(int fd ,  int pipefd , int fd_dup , int pipe_dup );