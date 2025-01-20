/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 04:38:19 by taya              #+#    #+#             */
/*   Updated: 2025/01/20 04:38:37 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void check_args(int argc)
{
    if (argc != 5)
    {
        perror("Usage: ./pipex infile cmd1 cmd2 outfile");
        exit(EXIT_FAILURE);
    }
}

void handle_pipe(int *pipe_fd)
{
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
}

pid_t create_process(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    return (pid);
}