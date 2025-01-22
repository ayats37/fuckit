/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:04:30 by taya              #+#    #+#             */
/*   Updated: 2025/01/22 21:31:30 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_input(t_data *data)
{
	if (data->argc < 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 ... outfile");
		exit(EXIT_FAILURE);
	}
	data->cmd_nbrs = data->argc - 3;
}

void	create_pipes(t_data *data, int pipe_fd[][2])
{
	int	i;
	if (data->here_doc)
		i = 1;
	else
		i = 0;
	while (i < data->cmd_nbrs - 1)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	create_children(t_data *data, int pipe_fd[][2])
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->cmd_nbrs)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			data->i = i;
			child(data, pipe_fd);
		}
		i++;
	}
}

void	close_pipes(t_data *data, int pipe_fd[][2])
{
	int	i;

	i = 0;
	while (i < data->cmd_nbrs - 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

void	wait_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_nbrs)
	{
		wait(NULL);
		i++;
	}
}
