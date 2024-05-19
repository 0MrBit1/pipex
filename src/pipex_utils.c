#include "../include/pipex.h"


char *get_command_path(char *cmd , char *PATH_VARIABLE)
{
    int     i;
    int     start;
    char    *cmd_path;
    char    *potencial_path;

    i = 0;
    start = 0;
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