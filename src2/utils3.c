/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/06 16:17:01 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/13 17:16:02 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Check that at the last cmd exit is normal. Guard check for when signal killed
// the child is important so last does not give a garbage value.
int	wait_children(pid_t *pids, int num_cmds)
{
	int	status;
	int	last;
	int	i;

	i = 0;
	last = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == num_cmds - 1 && WIFEXITED(status))
			last = WEXITSTATUS(status);
		i++;
	}
	free(pids);
	return (last);
}

// The first and last cmds are special in terms of dup2.
// First cmd - reads from infile, last cmd - writes to outfile.
// Middle cmds read from prev pipe and write to next pipe.
static void	setup_fds(t_pipex *data, int cmd_index)
{
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
}

static void	cmd_not_found(char *cmd_str)
{
	write(2, "Command not found: ", 19);
	write(2, cmd_str, ft_strlen(cmd_str));
	write(2, "\n", 1);
	exit(127);
}

// Run execve.
void	execute_cmd(t_pipex *data, int cmd_index, char **argv, char **envp)
{
	char	**cmd_args;
	int		argv_offset;

	setup_fds(data, cmd_index);
	if (data->heredoc)
		argv_offset = 3;
	else
		argv_offset = 2;
	if (!data->cmd_paths[cmd_index])
		cmd_not_found(argv[cmd_index + argv_offset]);
	cmd_args = split_cmd_args(argv[cmd_index + argv_offset]);
	if (!cmd_args || execve(data->cmd_paths[cmd_index], cmd_args, envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}
