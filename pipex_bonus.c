/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:45:32 by taya              #+#    #+#             */
/*   Updated: 2025/01/21 19:59:48 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_data data;
	int pipe_fd[MAX_PIPES][2];
	
	data.argc = argc;
	data.argv = argv;
	data.env = env;
	if (argc - 4 > MAX_PIPES)
		return(1);
	check_input(&data);
	create_pipes(&data, pipe_fd);
	create_children(&data, pipe_fd);
	close_pipes(&data, pipe_fd);
	wait_children(&data);
	return (0);
}
