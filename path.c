/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:39:42 by taya              #+#    #+#             */
/*   Updated: 2025/01/20 04:31:53 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_path(char **env)
{
    int i;

     i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            return (env[i] + 5); 
        i++;
    }
    return (NULL);
}

char **split_cmd(char *cmd)
{
    char **command = ft_split(cmd, ' ');
    if (!command)
    {
        perror("split failed");
        return (NULL);
    }
    return (command);
}

char **get_paths(char **env)
{
    char *path_string;
    char **paths;

    path_string = get_path(env);
    if (!path_string)
    {
        perror("path not found");
        return (NULL);
    }
    paths = ft_split(path_string, ':');
    if (!paths)
        perror("path split failed");
    return (paths);
}
char *build_path(char *path, char *cmd)
{
    char *full_path;

    full_path = malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
    if (!full_path)
        return (NULL);
    ft_strcpy(full_path, path);
    ft_strcat(full_path, "/");
    ft_strcat(full_path, cmd);
    return (full_path);
}
char *check_paths(char **paths, char *cmd)
{
    char *full_path;
    int i;

    i = 0;
    while (paths[i])
    {
        full_path = build_path(paths[i], cmd);
        if (!full_path)
            return (NULL);
        if (access(full_path, F_OK | X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

char *find_cmd_path(char *cmd, char **env)
{
    char **command;
    char **paths;
    char *result;

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
