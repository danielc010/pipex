/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/04 09:18:49 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/04 10:15:47 by dachin        ########   odam.nl         */
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

void	execute_child1(t_pipex *data, char **argv, char **envp)
{
			char	**cmd1_args;
		// redirect stdin (0) to read from infile
		if (dup2(data->infile_fd, 0) == -1)
		{
			perror("child1 dup2 stdin failed");
			exit(EXIT_FAILURE);
		}
		// redirect stdout (1) to write to pipe
		if (dup2(data->fd[1], 1) == -1)
		{
			perror("child1 dup2 stdout failed");
			exit(EXIT_FAILURE);
		}
		// Close unused fd
		close_inoutpipefd(data->fd, &data->infile_fd, &data->outfile_fd);

		// Split commands into arguments
		cmd1_args = ft_split(argv[2], ' ');
		if (!cmd1_args)
		{
			perror("Error splitting cmd1");
			exit(EXIT_FAILURE);
		}

		// Execute the command
		if (execve(data->cmd1_path, cmd1_args, envp) == -1)
		{
			perror("execve cmd1 failed");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);

}

void	execute_child2(t_pipex *data, char **argv, char **envp)
{
		char	**cmd2_args;
		// redirect stdin (0) to read from pipe
		if (dup2(data->fd[0], 0) == -1)
		{
			perror("child2 dup2 stdin failed");
			exit(EXIT_FAILURE);
		}
		// redirect stdout (1) to write to outfile
		if (dup2(data->outfile_fd, 1) == -1)
		{
			perror("child2 dup2 stdout failed");
			exit(EXIT_FAILURE);
		}
		// Close unused fd
		close_inoutpipefd(data->fd, &data->infile_fd, &data->outfile_fd);

		// Split commands into arguments
		cmd2_args = ft_split(argv[3], ' ');
		if (!cmd2_args)
		{
			perror("Error splitting cmd2");
			exit(EXIT_FAILURE);
		}
		// Execute the command
		if (execve(data->cmd2_path, cmd2_args, envp) == -1)
		{
			perror("execve cmd2 failed");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
