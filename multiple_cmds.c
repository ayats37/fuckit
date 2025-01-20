/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:54:14 by taya              #+#    #+#             */
/*   Updated: 2025/01/20 17:41:42 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(char **argv, int pipe_fd[][2], int i)
{
	int	fd;

	fd = ft_open_file(argv[1], 0);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipe_fd[i][1], STDOUT_FILENO);
}

void	last_cmd(char **argv, int pipe_fd[][2], int i, int argc)
{
	int	fd;

	fd = ft_open_file(argv[argc - 1], 1);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(pipe_fd[i - 1][0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	middle_cmd(int pipe_fd[][2], int i)
{
	dup2(pipe_fd[i - 1][0], STDIN_FILENO);
	dup2(pipe_fd[i][1], STDOUT_FILENO);
}
void	execute_command(char **argv, char **env, int i)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(argv[i + 2], ' ');
	if (cmd_args == NULL)
	{
		perror("ft_split failed");
		exit(EXIT_FAILURE);
	}
	cmd_path = find_cmd_path(argv[i + 2], env);
	if (!cmd_path)
	{
		perror("command not found");
		ft_free_arr(cmd_args);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd_args, env);
	perror("execve failed");
	free(cmd_path);
	ft_free_arr(cmd_args);
	exit(EXIT_FAILURE);
}
void	child(int argc, char **argv, char **env, int i, int nbr_cmds,
		int pipe_fd[2][2])
{
	int	j;

	j = 0;
	if (i == 0)
		first_cmd(argv, pipe_fd, i);
	else if (i == nbr_cmds - 1)
		last_cmd(argv, pipe_fd, i, argc);
	else
		middle_cmd(pipe_fd, i);
	while (j < nbr_cmds - 1)
	{
		close(pipe_fd[j][0]);
		close(pipe_fd[j][1]);
		j++;
	}
    if (argv[i + 2] && argv[i + 2][0] != '\0')
	    execute_command(argv, env, i);
	else
    {
        perror("comamnd not found");
        exit(1);
    }
}
