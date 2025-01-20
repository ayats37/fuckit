void first_child(char **argv, int *pipe_fd, char **env)
{
    int fd;
    char *cmd_path;
    char **cmd_args;
     
    fd = ft_open_file(argv[1], 0);
    if (fd == -1)
        exit(EXIT_FAILURE); 
    dup2(fd, STDIN_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(fd);
    if (!argv[2] || argv[2][0] == '\0')
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    cmd_args = ft_split(argv[2], ' ');
    if (cmd_args == NULL)
    {
        perror("ft_split failed");
        exit(EXIT_FAILURE);
    }
    cmd_path = find_cmd_path(argv[2], env);
    if (!cmd_path)
    {
        ft_free_arr(cmd_args);
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    execve(cmd_path, cmd_args, env);
    perror("execve failed");
    free(cmd_path);
    ft_free_arr(cmd_args);
    exit(EXIT_FAILURE);
}
void second_child(char **argv, int *pipe_fd, char **env)
{
    int fd;
    char *cmd_path;
    char **cmd_args;
    
    fd = ft_open_file(argv[4], 1);
    if (fd == -1)
        exit(EXIT_FAILURE);
    dup2(fd, STDOUT_FILENO);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    close(fd);
    if (!argv[3] || argv[3][0] == '\0')
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    cmd_args = ft_split(argv[3], ' ');
    if (cmd_args == NULL)
    {
        perror("ft_split failed");
        exit(EXIT_FAILURE);
    }
    cmd_path = find_cmd_path(argv[3], env);
    if (!cmd_path)
    {
        ft_free_arr(cmd_args);
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    execve(cmd_path, cmd_args, env);
    perror("execve failed");
    free(cmd_path);
    ft_free_arr(cmd_args);
    exit(EXIT_FAILURE);
}