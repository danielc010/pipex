/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/02 14:57:36 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/04 14:49:20 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Open both in and out files. Outfile to allow write,
// create if non-existent, overwrite if not-empty  (per > behaviour),
// 0644 means owner can read & write, other users can only read.
//** TODO*** guard clauses?
void	open_files(char **argv, t_pipex *data)
{
	if (!argv || !data)
		return ;
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd == -1)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	data->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
	{
		perror("Error opening outfile");
		close(data->outfile_fd);
		exit(EXIT_FAILURE);
	}
}

void	create_pipe(t_pipex *data)
{
	if (!data)
		return ;
	if (pipe(data->fd) == -1)
	{
		perror("Error creating pipe");
		close(data->infile_fd);
		close(data->outfile_fd);
		exit(EXIT_FAILURE);
	}
}

// Close these fds which are unused.
void	close_inoutpipefd(int pipe_fd[2], int *infile_fd, int *outfile_fd)
{
	if (!pipe_fd || !infile_fd || !outfile_fd)
		return ;
	close(*infile_fd);
	close(*outfile_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	init_pipex(t_pipex *data, char **argv, char**envp)
{
	if (!data || !argv || !envp)
		return ;
	data->cmd1_path = NULL;
	data->cmd2_path = NULL;
	open_files(argv, data);
	create_pipe(data);
	data->cmd1_path = get_path(argv[2], envp);
	if (!data->cmd1_path)
	{
		write(2, "Command not found: ", 19);
		write(2, argv[2], ft_strlen(argv[2]));
		write(2, "\n", 1);
		cleanup_and_exit(data);
	}
	data->cmd2_path = get_path(argv[3], envp);
	if (!data->cmd2_path)
	{
		write(2, "Command not found: ", 19);
		write(2, argv[3], ft_strlen(argv[3]));
		write(2, "\n", 1);
		cleanup_and_exit(data);
	}
}
