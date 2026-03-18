/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/06 16:17:01 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/18 13:29:40 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Pipe shows the parent's code which is also the last child's code (last cmd).
// status is used to capture the raw kernel status, which is a bitmask encoding
// how the process ended (normal exit, killed by signal, etc)
// WIFEXITED(status) checks the bitmask. Guards against undef behavior - if a
// process was killed by a signal (i.e. SIGSEGV), calling WEXITSTATUS causes UB.
// WEXITSTATUS(status) exracts the actual exit code from the bitmask.
void	wait_children(pid_t *pids, int num_cmds, int outfile_err)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == num_cmds - 1 && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		++i;
	}
	free(pids);
	if (outfile_err)
		exit_code = EXIT_FAILURE;
	exit(exit_code);
}

void	free_child_data(t_pipex *data)
{
	int	i;

	free(data->pids);
	if (data->cmd_paths)
	{
		i = 0;
		while (i < data->num_cmds)
		{
			free(data->cmd_paths[i]);
			++i;
		}
		free(data->cmd_paths);
		data->cmd_paths = NULL;
	}
	if (data->pipes)
	{
		i = 0;
		while (i < data->num_cmds - 1)
		{
			free(data->pipes[i]);
			++i;
		}
		free(data->pipes);
		data->pipes = NULL;
	}
}
