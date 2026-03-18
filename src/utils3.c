/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/06 16:17:01 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/18 06:45:54 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Pipe shows the parent's code which is also the last child's code (last cmd).
// status is used to capture the raw kernel status, which is a bitmask encoding
// how the process ended (normal exit, killed by signal, etc)
// WIFEXITED(status) checks the bitmask. Guards against undef behavior - if a
// process was killed by a signal (i.e. SIGSEGV), calling WEXITSTATUS causes UB.
// WEXITSTATUS(status) exracts the actual exit code from the bitmask.
void	wait_children(pid_t *pids, int num_cmds)
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
	exit(exit_code);
}

// The first and last cmds are special in terms of dup2.
// First cmd - reads from infile
// Last cmd - writes to outfile.
// Middle cmds - read from prev pipe and write to next pipe.
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
}

// Per POSIX and used by bash, sh and other shells, 127 is the standard shell
// exit code for command not found.
static void	cmd_not_found(char *cmd_str)
{
	write(2, "command not found: ", 19);
	write(2, cmd_str, ft_strlen(cmd_str));
	write(2, "\n", 1);
	exit(127);
}

// EACCES means file found but not executable → exit 126. Otherwise → exit 1.
static void	handle_execve_error(char *cmd)
{
	if (errno == EACCES)
	{
		perror(cmd);
		exit(126);
	}
	perror(cmd);
	exit(EXIT_FAILURE);
}

// Run execve. Remember that only if an error occurs, execve returns -1.
// On success execve never returns.
// !cmd_args check protects NULL pointer dereferencing in handle_execve_error.
void	execute_cmd(t_pipex *data, int cmd_index, char **argv, char **envp)
{
	char	**cmd_args;
	int		argv_offset;

	setup_fds(data, cmd_index);
	close_all_pipes(data->pipes, data->num_cmds - 1);
	close(data->infile_fd);
	close(data->outfile_fd);
	if (data->heredoc)
		argv_offset = 3;
	else
		argv_offset = 2;
	if (!data->cmd_paths[cmd_index])
		cmd_not_found(argv[cmd_index + argv_offset]);
	cmd_args = ft_split(argv[cmd_index + argv_offset], ' ');
	if (!cmd_args)
		exit(EXIT_FAILURE);
	if (execve(data->cmd_paths[cmd_index], cmd_args, envp) == -1)
		handle_execve_error(cmd_args[0]);
}
