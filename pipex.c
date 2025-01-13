/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:52:24 by taya              #+#    #+#             */
/*   Updated: 2025/01/13 21:40:33 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_open_file(const char *file, int mode)
{
    int fd;

    fd = 0;
    if (mode == 0)
    {
        fd = open(file, O_RDONLY);
        if (fd == -1)
        {
            perror("error opening file");
            return (-1);
        }
    }
    else if (mode == 1)
    {
        fd = open(file,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
             perror("error opening file");
            return (-1);
        }
    }
    return (fd);
}

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
    char **cnd;
    int i;

    cnd = ft_split(cmd, ' ');
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
        full_path = malloc(((ft_strlen(paths[i]) + ft_strlen(cmd)) + 2) * sizeof(char));
        if (!full_path)
        {
            perror("allocation failed");
            return (NULL);
        }
        ft_strcpy(full_path, paths[i]);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, cnd[0]);
        if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
        {
            free(paths);
            return(full_path);
        }
        free(full_path);
        i++;  
    }
    free(paths);
    return (NULL);
}

void    child(char **argv, int *pipe_fd,  char **env)
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
        perror("c");
        exit(EXIT_FAILURE);
    }
    printf("c;d path%s\n",cmd_path);
    printf("ARG;1 %s arg2 %s\n", cmd_args[0], cmd_args[1]);
    execve(cmd_path, cmd_args, env);
    perror("execve failed");
    free(cmd_path);
    free(cmd_args);
    exit(EXIT_FAILURE);
}
void    parent(char **argv, int *pipe_fd,  char **env)
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
        perror("c");
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
    pid_t pid;
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
    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
        child(argv, pipe_fd, env);
    else
    {
        wait(NULL);   
        parent(argv, pipe_fd, env);
    }
    return (0);
}
