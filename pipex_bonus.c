/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:45:32 by taya              #+#    #+#             */
/*   Updated: 2025/01/18 16:59:32 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char    *find_cmd_path(char *cmd, char **env)
{
    char *path_string;
    char *full_path;
    char **paths;
    char **command;
    int i;

    command = ft_split(cmd, ' ');
    if (!command)
    {
        perror("failed to split command");
        return (NULL);
    }
    path_string = get_path(env);
    if (!path_string)
    {
        perror("path not found");
        return(NULL);
    }
    paths = ft_split(path_string, ':');
    if (!paths)
    {
        perror("failed to split path");
        return (NULL);
    }
    i = 0;
    while (paths[i])
    {
        full_path = malloc(((ft_strlen(paths[i]) + ft_strlen(command[0])) + 2) * sizeof(char));
        if (!full_path)
        {
            perror("allocation failed");
            return (NULL);
        }
        ft_strcpy(full_path, paths[i]);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, command[0]);
        if (access(full_path, F_OK | X_OK) == 0)
        {
            ft_free_arr(paths);
            ft_free_arr(command);
            return(full_path);
        }
        free(full_path);
        i++;  
    }
    ft_free_arr(paths);
    ft_free_arr(command);
    return (NULL);
}

void    first_cmd(char **argv, int pipe_fd[][2], int i)
{
        int fd;
        
        fd = ft_open_file(argv[1], 0);
        if (fd == -1)
            exit(EXIT_FAILURE);
        dup2(fd, STDIN_FILENO);
        close(fd);
        dup2(pipe_fd[i][1], STDOUT_FILENO);
}

void    last_cmd(char **argv, int pipe_fd[][2], int i, int argc)
{
    int fd;
    fd = ft_open_file(argv[argc - 1], 1);
    if (fd == -1)
        exit(EXIT_FAILURE);
    dup2(pipe_fd[i - 1][0], STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void    middle_cmd(int pipe_fd[][2], int i)
{
        dup2(pipe_fd[i - 1][0], STDIN_FILENO);
        dup2(pipe_fd[i][1], STDOUT_FILENO);
}

void    child(int argc, char **argv, char **env, int i, int nbr_cmds, int pipe_fd[2][2])
{ 
    int j;
    
    j = 0;
    if (i == 0) 
        first_cmd(argv, pipe_fd, i);
    else if (i == nbr_cmds - 1)
        last_cmd(argv, pipe_fd, i, argc);
    else 
        middle_cmd(pipe_fd, i);
    
    while (j < nbr_cmds - 1)
    {
        close(pipe_fd[j][0]);
        close(pipe_fd[j][1]);
        j++;
    }
    execve(find_cmd_path(argv[i + 2], env), ft_split(argv[i + 2], ' '), env);
    perror("execve failed");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
    int pipe_fd[argc - 4][2];
    pid_t pid;
    int i;
    int nbr_cmds;
    
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
