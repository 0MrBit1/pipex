/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:19:11 by acharik           #+#    #+#             */
/*   Updated: 2024/05/24 23:24:58 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/wait.h>

int		get_pipes_number(char **argv);
char	*get_command_path(char *cmd, char *PATH_VARIABLE);
void	error_handler(int argc, int *pipefd);
char	*return_command(char **args, char **envp);
void	dup_fds(int fd, int pipefd, int fd_dup, int pipe_dup);