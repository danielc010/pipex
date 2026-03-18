/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/02 14:57:36 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/18 18:23:28 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	write_zsh_error(char *filename, int err_code)
{
	write(2, "zsh: ", 5);
	// write(2, filename, ft_strlen(filename));
	// write(2, ": ", 2);
	// write(2, strerror(err_code), ft_strlen(strerror(err_code)));
	write(2, strerror(err_code), ft_strlen(strerror(err_code)));
	write(2, ": ", 2);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
}

// Open both in and out files. Outfile to allow write,
// create if non-existent, overwrite if not-empty  (per > behaviour),
// 0644 means owner can read & write, other users can only read.
// Infile read error, outfile write error - shell behavior is to CONTINUE
// running both commands. /dev/null (special file on Unix that Reads returns
// EOF and Writes discards everything written to it) is used so child1 gets
// empty input while childn's stdout goes nowhere and exits 0.
static void	open_files(char **argv, t_pipex *data, int argc)
{
	int	saved_errno;

	if (!argv || !data)
		return ;
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd == -1)
	{
		saved_errno = errno;
		write_zsh_error(argv[1], saved_errno);
		if (saved_errno == EACCES || saved_errno == ENOENT)
			data->infile_fd = open("/dev/null", O_RDONLY);
		else
			exit(EXIT_FAILURE);
	}
	data->outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
	{
		write_zsh_error(argv[argc - 1], errno);
		data->outfile_err = 1;
		data->outfile_fd = open("/dev/null", O_WRONLY);
	}
}

// Create num_cmds - 1 pipes.
void	create_pipe(t_pipex *data)
{
	int	i;

	if (!data)
		return ;
	data->pipes = malloc(sizeof(int *) * (data->num_cmds - 1));
	if (!data->pipes)
		error_exit("malloc failed");
	i = 0;
	while (i < data->num_cmds - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(data->pipes[i]) == -1)
		{
			perror("Error creating pipe");
			close(data->infile_fd);
			close(data->outfile_fd);
			exit(EXIT_FAILURE);
		}
		++i;
	}
}

void	init_pipex(t_pipex *data, char **argv, char**envp, int argc)
{
	int	i;

	if (!data || !argv || !envp)
		error_exit("Invalid arguments to init_pipex");
	data->heredoc = 0;
	data->outfile_err = 0;
	data->pids = NULL;
	data->num_cmds = argc - 3;
	data->cmd_paths = malloc(sizeof(char *) * (data->num_cmds + 1));
	if (!data->cmd_paths)
		error_exit("malloc failed");
	data->cmd_paths[data->num_cmds] = NULL;
	open_files(argv, data, argc);
	create_pipe(data);
	i = 0;
	while (i < data->num_cmds)
	{
		data->cmd_paths[i] = get_path(argv[i + 2], envp);
		++i;
	}
}

int	error_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
