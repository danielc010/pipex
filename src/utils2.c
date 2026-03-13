/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/04 09:18:49 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/13 06:27:47 by dachin        ########   odam.nl         */
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

// Fork once for every cmd. Run execve for the child process i.e. pid == 0.
pid_t	*fork_children(t_pipex *data, char **argv, char **envp)
{
	pid_t	*pids;
	int		i;

	if (!data || !argv || !envp)
		cleanup_and_exit(data);
	pids = malloc(sizeof(pid_t) * data->num_cmds);
	if (!pids)
		cleanup_and_exit(data);
	i = 0;
	while (i < data->num_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			cleanup_and_exit(data);
		if (pids[i] == 0)
			execute_cmd(data, i, argv, envp);
		++i;
	}
	return (pids);
}
