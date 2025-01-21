/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:04:30 by taya              #+#    #+#             */
/*   Updated: 2025/01/21 17:25:40 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_input(int argc, int *nbr_cmds)
{
	if (argc < 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 ... outfile");
		exit(EXIT_FAILURE);
	}
	*nbr_cmds = argc - 3;
}

void	create_pipes(int pipe_fd[][2], int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds - 1)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	create_children(int argc, char **argv, char **env, int pipe_fd[][2],
		int nbr_cmds)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < nbr_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child(argc, argv, env, i, nbr_cmds, pipe_fd);
		i++;
	}
}

void	close_pipes(int pipe_fd[][2], int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds - 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

void	wait_children(int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds)
	{
		wait(NULL);
		i++;
	}
}
