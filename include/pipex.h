#include "libft.h"
#include "ft_printf.h"
#include <sys/wait.h>
#include <fcntl.h>

int get_pipes_number(char **argv);
char *get_command_path(char *cmd , char *PATH_VARIABLE);