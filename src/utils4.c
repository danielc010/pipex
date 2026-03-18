/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/18 13:05:24 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/18 13:31:27 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

// EACCES means file found but not executable - exit 126. Otherwise - exit 1.
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

void	run_execve(t_pipex *data, int cmd_index, char **cmd_args, char **envp)
{
	char	*cmd_name;

	if (execve(data->cmd_paths[cmd_index], cmd_args, envp) == -1)
	{
		cmd_name = cmd_args[0];
		cmd_args[0] = NULL;
		free_array(cmd_args);
		free_child_data(data);
		handle_execve_error(cmd_name);
		free(cmd_name);
	}
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
	{
		free_child_data(data);
		cmd_not_found(argv[cmd_index + argv_offset]);
	}
	cmd_args = ft_split(argv[cmd_index + argv_offset], ' ');
	if (!cmd_args)
	{
		free_child_data(data);
		exit(EXIT_FAILURE);
	}
	run_execve(data, cmd_index, cmd_args, envp);
}
