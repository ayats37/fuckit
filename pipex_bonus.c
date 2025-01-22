/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:45:32 by taya              #+#    #+#             */
/*   Updated: 2025/01/22 21:20:40 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_data *data, int pipe_fd[][2])
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, data->argv[2], ft_strlen(data->argv[2])) == 0
			&& line[ft_strlen(data->argv[2])] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[data->i][1], line, ft_strlen(line));
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		pipe_fd[MAX_PIPES][2];

	data.argc = argc;
	data.argv = argv;
	data.env = env;
	data.here_doc = (argc > 1 && !ft_strncmp(argv[1], "here_doc", 8));
	if (data.here_doc)
		data.cmd_nbrs = argc - 4;
	else
		data.cmd_nbrs = argc - 3;
	if (data.cmd_nbrs > MAX_PIPES)
	{
		ft_putstr_fd("Error: Too many commands\n", 2);
		return (1);
	}
	if (data.here_doc)
	{
		if (pipe(pipe_fd[0]) == -1)
		{
        	perror("pipe failed");
        	return (1);
    	}
		here_doc(&data, pipe_fd);
	}
	create_pipes(&data, pipe_fd);
	create_children(&data, pipe_fd);
	close_pipes(&data, pipe_fd);
	wait_children(&data);
	return (0);
}
