/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:52:24 by taya              #+#    #+#             */
/*   Updated: 2025/01/15 15:28:27 by taya             ###   ########.fr       */
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
        ft_free_arr(command);
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
        ft_free_arr(paths);
    }
    i = 0;
    while (paths[i])
    {
        full_path = malloc(((ft_strlen(paths[i]) + ft_strlen(cmd)) + 2) * sizeof(char));
        if (!full_path)
        {
            perror("allocation failed");
            free(full_path);
            return (NULL);
        }
        ft_strcpy(full_path, paths[i]);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, command[0]);
        if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
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

void    first_child(char **argv, int *pipe_fd,  char **env)
{
    int fd;
    char *cmd_path;
    char    **cmd_args;
    
    fd  = ft_open_file(argv[1], 0);
    if (fd == -1)
        exit(EXIT_FAILURE);  
    dup2(fd, STDIN_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(fd);
    cmd_args = ft_split(argv[2], ' ');
    if (cmd_args == NULL)
    {
        perror("ft_split failed");
        exit(EXIT_FAILURE);
    }
    cmd_path = find_cmd_path(argv[2], env);
    if (!cmd_path)
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    execve(cmd_path, cmd_args, env);
    perror("execve failed");
    free(cmd_path);
    free(cmd_args);
    exit(EXIT_FAILURE);
}
void    second_child(char **argv, int *pipe_fd,  char **env)
{
    int fd;
    char *cmd_path;
    char **cmd_args;
    
    fd  = ft_open_file(argv[4], 1);
    if (fd == -1)
        exit(EXIT_FAILURE);
    dup2(fd, STDOUT_FILENO);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    close(fd);
    cmd_args = ft_split(argv[3], ' ');
    cmd_path = find_cmd_path(argv[3], env);
    if (cmd_args == NULL)
    {
        perror("ft_split failed");
        exit(EXIT_FAILURE);
    }
    if (!cmd_path)
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    execve(cmd_path, cmd_args, env);
    perror("execve failed");
    free(cmd_path);
    free(cmd_args);
    exit(EXIT_FAILURE);
}


int main(int argc, char **argv, char **env)
{
    pid_t pid1;
    pid_t pid2;
    int pipe_fd[2];
    
    if (argc != 5)
    {
        perror("Usage: ./pipex infile cmd1 cmd2 outfile");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
        first_child(argv, pipe_fd, env);
    pid2 = fork();
    if(pid2 == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0)
        second_child(argv, pipe_fd, env);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}
