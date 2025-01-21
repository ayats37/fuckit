/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:46:19 by taya              #+#    #+#             */
/*   Updated: 2025/01/21 17:27:07 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef MAX_PIPES
# define MAX_PIPES 5120
# endif

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	child(int argc, char **argv, char **env, int i, int nbr_cmds,
			int pipe_fd[2][2]);
int		ft_open_file(const char *file, int mode);
char	*get_path(char **env);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
void	ft_free_arr(char **arr);
char	*get_path(char **env);
char	**split_cmd(char *cmd);
char	**get_paths(char **env);
char	*build_path(char *path, char *cmd);
char	*check_paths(char **paths, char *cmd);
char	*find_cmd_path(char *cmd, char **env);
void	first_cmd(char **argv, int pipe_fd[][2], int i);
void	last_cmd(char **argv, int pipe_fd[][2], int i, int argc);
void	middle_cmd(int pipe_fd[][2], int i);
void	check_input(int argc, int *nbr_cmds);
void	create_pipes(int pipe_fd[][2], int nbr_cmds);
void	create_children(int argc, char **argv, char **env, int pipe_fd[][2],
			int nbr_cmds);
void	close_pipes(int pipe_fd[][2], int nbr_cmds);
void	wait_children(int nbr_cmds);

#endif