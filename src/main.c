/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 12:39:22 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/02 23:22:26 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	char	*cmd1_path;
	char	*cmd2_path;
	pid_t	pid1;
	pid_t	pid2;

	// argc validation
	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (EXIT_FAILURE);
	}
	open_files(argv[1], argv[4], &infile_fd, &outfile_fd);
	create_pipe(fd, &infile_fd, &outfile_fd);
	cmd1_path = get_path(argv[2], envp);
	if (!cmd1_path)
	{
		write(2, "Command not found: ", 19);
		write(2, argv[2], ft_strlen(argv[2]));
		write(2, "\n", 1);
		close(infile_fd);
		close(outfile_fd);
		close(fd[0]);
		close(fd[1]);
		return(EXIT_FAILURE);
	}
	cmd2_path = get_path(argv[3], envp);
	if (!cmd2_path)
	{
		write(2, "Command not found: ", 19);
		write(2, argv[3], ft_strlen(argv[3]));
		write(2, "\n", 1);
		free(cmd1_path);
		close(infile_fd);
		close(outfile_fd);
		close(fd[0]);
		close(fd[1]);
		return(EXIT_FAILURE);
	}

	// Fork Child 1
	pid1 =	fork();
	if (pid1 == -1)
	{
		perror("Error forking child 1");
		free(cmd1_path);
		free(cmd2_path);
		close(infile_fd);
		close(outfile_fd);
		close(fd[0]);
		close(fd[1]);
		return (EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		char	**cmd1_args;
		// redirect stdin (0) to read from infile
		if (dup2(infile_fd, 0) == -1)
		{
			perror("child1 dup2 stdin failed");
			exit(EXIT_FAILURE);
		}
		// redirect stdout (1) to write to pipe
		if (dup2(fd[1], 1) == -1)
		{
			perror("child1 dup2 stdout failed");
			exit(EXIT_FAILURE);
		}
		// Close unused fd
		close(infile_fd);
		close(outfile_fd);
		close(fd[0]);
		close(fd[1]);

		// Split commands into arguments
		cmd1_args = ft_split(argv[2], ' ');
		if (!cmd1_args)
		{
			perror("Error splitting cmd1");
			exit(EXIT_FAILURE);
		}

		// Execute the command
		if (execve(cmd1_path, cmd1_args, envp) == -1)
		{
			perror("execve cmd1 failed");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}

	// Fork Child 2
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error forking child 2");
		free(cmd1_path);
		free(cmd2_path);
		close(infile_fd);
		close(outfile_fd);
		close(fd[0]);
		close(fd[1]);
		return (EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		char	**cmd2_args;
		// redirect stdin (0) to read from pipe
		if (dup2(fd[0], 0) == -1)
		{
			perror("child2 dup2 stdin failed");
			exit(EXIT_FAILURE);
		}
		// redirect stdout (1) to write to outfile
		if (dup2(outfile_fd, 1) == -1)
		{
			perror("child2 dup2 stdout failed");
			exit(EXIT_FAILURE);
		}
		// Close unused fd
		close(infile_fd);
		close(outfile_fd);
		close(fd[0]);
		close(fd[1]);

		// Split commands into arguments
		cmd2_args = ft_split(argv[3], ' ');
		if (!cmd2_args)
		{
			perror("Error splitting cmd2");
			exit(EXIT_FAILURE);
		}
		// Execute the command
		if (execve(cmd2_path, cmd2_args, envp) == -1)
		{
			perror("execve cmd2 failed");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}

	// PARENT CLEANUP
	free(cmd1_path);
	free(cmd2_path);
	close(infile_fd);
	close(outfile_fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (EXIT_SUCCESS);
	}

