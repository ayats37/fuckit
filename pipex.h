/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:27:15 by taya              #+#    #+#             */
/*   Updated: 2025/01/14 18:44:01 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./libft/libft.h"

int ft_open_file(const char *file, int mode);
char *get_path(char **env);
char    *find_cmd_path(char *cmd, char **env);
void    first_child(char **argv, int *pipe_fd,  char **env);
void    second_child(char **argv, int *pipe_fd,  char **env);
char    *ft_strcpy(char *dest, char *src);
char    *ft_strcat(char *dest, char *src);

#endif

