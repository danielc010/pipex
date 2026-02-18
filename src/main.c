/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 12:39:22 by dachin        #+#    #+#                 */
/*   Updated: 2026/02/18 18:27:33 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path(char **envp)
{
	printf("DEBUG: Checking envp...\n");
	if (!envp)
		printf("DEBUG: envp is NULL!\n");
	else
		printf("DEBUG: envp is valid\n");

	int i = 0;
	while (envp[i])
	{
		printf("DEBUG: envp[%d] = '%s'\n", i, envp[i]);  // Print each one
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			printf("DEBUG: Found PATH! Value = '%s'\n", envp[i] + 5);
			return (envp[i] + 5);
		}
		++i;
	}
	printf("DEBUG: Never found PATH in envp!\n");
	return (NULL);
}

char *extract_cmd_name(char *cmd)
{
	char **cmd_split;
	char *cmd_name;
	cmd_split = ft_split(cmd, ' ');
	cmd_name = cmd_split[0];
	printf("DEBUG: cmd is %s!\n", cmd);
	return (cmd_name);
}

char	**fill_path_array(char *path_line)
{
	char **path_array;
	path_array = ft_split(path_line, ':');
	printf("DEBUG: After split:\n");
	int j = 0;
	while (path_array[j])
	{
		printf("DEBUG: paths[%d] = '%s'\n", j, path_array[j]);
		j++;
	}
	return (path_array);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;  // ← Tell compiler you know it's unused
    (void)argv;  // ← Tell compiler you know it's unused

	// argv[1] = infile
	char *cmd1 = argv[2];
	// char *cmd2 = argv[3];
	// argv[4] = outfile

	int	infile_fd;
	int	outfile_fd;
	int	i;

	// argc validation
	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
	}

	// Open files
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		perror("Error opening infile");
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		perror("Error opening outfile");

	// Parse command
	char *command;
	command = extract_cmd_name(cmd1);

	// Get path
	char *path_line = get_path(envp);
	char **parths_array;
	char *full_path;
	if (path_line)
	{
		parths_array = fill_path_array(path_line);
		i = 0;
		while (parths_array[i])
		{
			full_path = ft_strjoin(ft_strjoin(parths_array[i], "/"), command);
			printf("DEBUG: Testing path: '%s'\n", full_path);
			if (access(full_path, X_OK) == 0)
			{
				printf("DEBUG: ✓ Found executable at: '%s'\n", full_path);
			}
			++i;
		}
	}
	else
		ft_printf("Path not found in environment.\n");

	// // The pipe & first fork
	// int	fd[2];
	// pipe(fd); // fd[0]=read, fd[1]=write

	// pid_t	pid1 = fork();
	// if (pid1 == 0)
	// {
	// 	// Child block
	// 	ft_printf("This is the child block of fork 1. PID is %d\n", getpid());
	// 	exit(0);
	// }
	// else
	// {
	// 	// Parent block
	// 	ft_printf("This is the parent block of fork 1. PID is %d\n", getpid());
	// }

	// pid_t	pid2 = fork();
	// if (pid2 == 0)
	// {
	// 	// Child block
	// 	ft_printf("This is the child block of fork 2. PID is %d\n", getpid());
	// }
	// else
	// {
	// 	// Parent block
	// 	ft_printf("This is the parent block of fork 2. PID is %d\n", getpid());
	// }

	// // Wait for both children
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}
