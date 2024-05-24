/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:34:40 by acharik           #+#    #+#             */
/*   Updated: 2024/05/24 23:32:16 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	child_process1(char **argv, char **envp, int *pipefd)
{
	char	*cmd;
	char	**args;
	int		fd;

	close(pipefd[0]);
	args = ft_split(argv[2], ' ');
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("error: \n");
		exit(1);
	}
	dup_fds(fd, pipefd[1], 0, 1);
	cmd = return_command(args, envp);
	execve(cmd, args, envp);
	perror("error exece cmd1 \n");
	free(cmd);
	free_array(args);
	exit(1);
}

void	child_process2(char **argv, char **envp, int *pipefd)
{
	int		i;
	char	*cmd;
	char	**args;
	int		fd;

	close(pipefd[1]);
	i = 0;
	args = ft_split(argv[3], ' ');
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		perror("error : \n");
	cmd = return_command(args, envp);
	dup_fds(fd, pipefd[0], 1, 0);
	execve(cmd, args, envp);
	free(cmd);
	free_array(args);
	perror("error exece cmd2 \n");
	exit(1);
}

void	parent_process(int *pipefd, char **argv, char **envp)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < 2)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Failed to fork child process\n");
			exit(1);
		}
		if (pid == 0)
		{
			if (i == 0)
				child_process1(argv, envp, pipefd);
			else if (i == 1)
				child_process2(argv, envp, pipefd);
		}
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) != -1)
		;
}

int	main(int argc, char **argv, char **envp)
{
	int	pipefd[2];

	error_handler(argc, pipefd);
	parent_process(pipefd, argv, envp);
}
