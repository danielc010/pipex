/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/04 09:18:49 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/18 13:26:05 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

// Close all pipes
void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		++i;
	}
}

// Close fds, free memory without exit
void	cleanup_resources(t_pipex *data)
{
	int	i;

	if (!data)
		return ;
	if (data->cmd_paths)
	{
		i = 0;
		while (i < data->num_cmds)
		{
			if (data->cmd_paths[i])
				free(data->cmd_paths[i]);
			++i;
		}
		free(data->cmd_paths);
	}
	if (data->pipes)
	{
		close_all_pipes(data->pipes, data->num_cmds - 1);
		i = 0;
		while (i < data->num_cmds - 1)
			free(data->pipes[i++]);
		free(data->pipes);
	}
	close(data->infile_fd);
	close(data->outfile_fd);
}

// Close fds, free memory with exit
void	cleanup_and_exit(t_pipex *data)
{
	if (!data)
		exit(EXIT_FAILURE);
	cleanup_resources(data);
	exit(EXIT_FAILURE);
}

// Fork once for every cmd, as it needes its own process image.
// Need dup & execve for the child process i.e. pid == 0.
void	fork_children(t_pipex *data, char **argv, char **envp)
{
	int	i;

	if (!data || !argv || !envp)
		cleanup_and_exit(data);
	data->pids = malloc(sizeof(pid_t) * data->num_cmds);
	if (!data->pids)
		cleanup_and_exit(data);
	i = 0;
	while (i < data->num_cmds)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			cleanup_and_exit(data);
		if (data->pids[i] == 0)
			execute_cmd(data, i, argv, envp);
		++i;
	}
}
