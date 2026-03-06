/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/06 16:17:01 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/06 17:03:43 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	wait_children(pid_t *pids, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
		waitpid(i++, NULL, 0);
	free(pids);
}

// Read from terminal until LIMITER appears. All the commands are to be stored somewhere?
void	read_heredoc(t_pipex *data)
{
	char	*line;
	int		heredoc_pipe[2];
	size_t	limiter_len;

	if (pipe(heredoc_pipe) == -1)
		error_exit("heredoc pipe creation falied");
	limiter_len = ft_strlen(data->limiter);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9); // Prompt user
		line = get_next_line(STDIN_FILENO); // Read line from terminal
		if (!line) // Ctrl+D pressed (EOF)
			break ;
		// Check if this line is the LIMITER
		if (ft_strncmp(line, data->limiter, limiter_len) == 0
			&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break ; // Stop reading
		}
		// Write the line to the pipe
		write(heredoc_pipe[1], line, ft_strlen(line));
		free(line);
	}
	close(heredoc_pipe[1]); // Close write end
	data->infile_fd = heredoc_pipe[0]; // Use read end as infile
}

void	open_files_heredoc(t_pipex *data, char **argv, int argc)
{
	// Open outfile in APPEND mode (not TRUNC)
	data->outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->outfile_fd == -1)
	{
		perror("Error opening outfile");
        close(data->infile_fd);
        exit(EXIT_FAILURE);
	}
}
