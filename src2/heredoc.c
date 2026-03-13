/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/13 06:12:05 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/13 08:19:32 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Read line from terminal until LIMITER appears. All the commands are to be
// passed via pipe: write line to pipe, close write end and use read end as
// infile
static void	read_heredoc(t_pipex *data)
{
	char	*line;
	int		heredoc_pipe[2];
	size_t	limiter_len;

	if (pipe(heredoc_pipe) == -1)
		error_exit("heredoc pipe creation falied");
	limiter_len = ft_strlen(data->limiter);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, data->limiter, limiter_len) == 0
			&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break ;
		}
		write(heredoc_pipe[1], line, ft_strlen(line));
		free(line);
	}
	close(heredoc_pipe[1]);
	data->infile_fd = heredoc_pipe[0];
}

// Open outfile in APPEND mode (not TRUNC) like in usual pipex
static void	open_files_heredoc(t_pipex *data, char **argv, int argc)
{
	data->outfile_fd = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->outfile_fd == -1)
	{
		perror("Error opening outfile");
		close(data->infile_fd);
		exit(EXIT_FAILURE);
	}
}

// Cmd path offset by + 1 compared to usual pipex (getpath(argv[i + 2 + 1]))
void	init_heredoc(t_pipex *data, char **argv, char**envp, int argc)
{
	int	i;

	if (!data || !argv || !envp)
		error_exit("Invalid arguments to init_heredoc");
	read_heredoc(data);
	open_files_heredoc(data, argv, argc);
	create_pipe(data);
	data->cmd_paths = malloc(sizeof(char *) * (data->num_cmds + 1));
	if (!data->cmd_paths)
		error_exit("malloc failed");
	data->cmd_paths[data->num_cmds] = NULL;
	i = 0;
	while (i < data->num_cmds)
	{
		data->cmd_paths[i] = get_path(argv[i + 3], envp);
		++i;
	}
}
