/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/04 09:18:49 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/04 15:03:10 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

// Close fds, free memory without exit
void	cleanup_resources(t_pipex *data)
{
	if (!data)
		return ;
	if (data->cmd1_path)
		free(data->cmd1_path);
	if (data->cmd2_path)
		free(data->cmd2_path);
	close_inoutpipefd(data->fd, &data->infile_fd, &data->outfile_fd);
}

// Close fds, free memory with exit
void	cleanup_and_exit(t_pipex *data)
{
	if (!data)
		exit(EXIT_FAILURE);
	cleanup_resources(data);
	exit(EXIT_FAILURE);
}

// Code execution for child1
// Redirect stdin (0) to read from infile
// Redirect stdout (1) to write to pipe
void	execute_child1(t_pipex *data, char **argv, char **envp)
{
	char	**cmd1_args;

	if (!data || !argv || !envp)
		exit(EXIT_FAILURE);

	if (dup2(data->infile_fd, 0) == -1 || dup2(data->fd[1], 1) == -1)
	{
		perror("child1 dup2 failed");
		exit(EXIT_FAILURE);
	}
	close_inoutpipefd(data->fd, &data->infile_fd, &data->outfile_fd);
	cmd1_args = ft_split(argv[2], ' ');
	if (!cmd1_args)
	{
		perror("Error splitting cmd1");
		exit(EXIT_FAILURE);
	}
	if (execve(data->cmd1_path, cmd1_args, envp) == -1)
	{
		perror("execve cmd1 failed");
		exit(EXIT_FAILURE);
	}
}

// Code execution for child2
// Redirect stdin (0) to read from pipe
// Redirect stdout (1) to write to outfile
void	execute_child2(t_pipex *data, char **argv, char **envp)
{
	char	**cmd2_args;

	if (!data || !argv || !envp)
		exit(EXIT_FAILURE);
	if (dup2(data->fd[0], 0) == -1 || dup2(data->outfile_fd, 1) == -1)
	{
		perror("child2 dup2 failed");
		exit(EXIT_FAILURE);
	}
	close_inoutpipefd(data->fd, &data->infile_fd, &data->outfile_fd);
	cmd2_args = ft_split(argv[3], ' ');
	if (!cmd2_args)
	{
		perror("Error splitting cmd2");
		exit(EXIT_FAILURE);
	}
	if (execve(data->cmd2_path, cmd2_args, envp) == -1)
	{
		perror("execve cmd2 failed");
		exit(EXIT_FAILURE);
	}
}
