/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:46:19 by taya              #+#    #+#             */
/*   Updated: 2025/01/20 00:41:27 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./libft/libft.h"


void    child(int argc, char **argv, char **env, int i, int nbr_cmds, int pipe_fd[2][2]);
int ft_open_file(const char *file, int mode);
char *get_path(char **env);
char    *ft_strcpy(char *dest, char *src);
char    *ft_strcat(char *dest, char *src);
void    ft_free_arr(char **arr);



#endif