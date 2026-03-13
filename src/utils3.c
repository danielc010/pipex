/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/06 16:17:01 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/13 07:06:30 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	wait_children(pid_t *pids, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], NULL, 0);
		++i;
	}
	free(pids);
}

// Dup and run execve. The first and last cmds are special in terms of dup2.
// First cmd - reads from infile, last cmd - writes to outfile.
// Middle cmds read from prev pipe and write to next pipe.
void	execute_cmd(t_pipex *data, int cmd_index, char **argv, char **envp)
{
	char	**cmd_args;
	int		argv_offset;

	if (cmd_index == 0)
		dup2(data->infile_fd, STDIN_FILENO);
	else
		dup2(data->pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index == data->num_cmds - 1)
		dup2(data->outfile_fd, STDOUT_FILENO);
	else
		dup2(data->pipes[cmd_index][1], STDOUT_FILENO);
	close_all_pipes(data->pipes, data->num_cmds - 1);
	close(data->infile_fd);
	close(data->outfile_fd);
	if (data->heredoc)
		argv_offset = 3;
	else
		argv_offset = 2;
	cmd_args = ft_split(argv[cmd_index + argv_offset], ' ');
	if (!cmd_args || execve(data->cmd_paths[cmd_index], cmd_args, envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}
