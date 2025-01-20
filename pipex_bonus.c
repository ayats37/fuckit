/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:45:32 by taya              #+#    #+#             */
/*   Updated: 2025/01/20 16:55:43 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_cmd_path(char *cmd, char **env)
{
	char	**command;
	char	**paths;
	char	*result;

	command = split_cmd(cmd);
	if (!command)
		return (NULL);
	paths = get_paths(env);
	if (!paths)
	{
		ft_free_arr(command);
		return (NULL);
	}
	result = check_paths(paths, command[0]);
	ft_free_arr(paths);
	ft_free_arr(command);
	return (result);
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[argc - 4][2];
	pid_t	pid;
	int		i;
	int		nbr_cmds;

	if (argc < 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 ... outfile");
		exit(EXIT_FAILURE);
	}
	nbr_cmds = argc - 3;
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
	i = 0;
	while (i < nbr_cmds - 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
	i = 0;
	while (i < nbr_cmds)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
