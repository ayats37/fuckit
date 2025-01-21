/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:45:32 by taya              #+#    #+#             */
/*   Updated: 2025/01/21 17:26:49 by taya             ###   ########.fr       */
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
	int	pipe_fd[MAX_PIPES][2];
	int	nbr_cmds;
	
	if (argc - 4 > MAX_PIPES)
		return(1);
	check_input(argc, &nbr_cmds);
	create_pipes(pipe_fd, nbr_cmds);
	create_children(argc, argv, env, pipe_fd, nbr_cmds);
	close_pipes(pipe_fd, nbr_cmds);
	wait_children(nbr_cmds);
	return (0);
}
