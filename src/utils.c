/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/02 14:57:36 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/04 17:47:55 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Open both in and out files. Outfile to allow write,
// create if non-existent, overwrite if not-empty  (per > behaviour),
// 0644 means owner can read & write, other users can only read.
//** TODO*** guard clauses?
void	open_files(char **argv, t_pipex *data, int argc)
{
	if (!argv || !data)
		return ;
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd == -1)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	data->outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
	{
		perror("Error opening outfile");
		close(data->outfile_fd);
		exit(EXIT_FAILURE);
	}
}

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

// // Close all pipes
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

void	init_pipex(t_pipex *data, char **argv, char**envp, int argc)
{
	int	i;

	if (!data || !argv || !envp)
		return ;
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
		if (!data->cmd_paths[i])
		{
			write(2, "Command not found: ", 19);
			write(2, argv[i + 2], ft_strlen(argv[i + 2]));
			write(2, "\n", 1);
			cleanup_and_exit(data);
		}
		++i;
	}
}

int	error_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
