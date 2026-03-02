/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/02 14:57:36 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/02 23:22:14 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

void	open_files(char *argv1, char *argv4, int *infile_fd, int *outfile_fd)
{
	*infile_fd = open(argv1, O_RDONLY);
	if (*infile_fd == -1)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	*outfile_fd = open(argv4, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile_fd == -1)
	{
		perror("Error opening outfile");
		close(*infile_fd);
		exit(EXIT_FAILURE);
	}
}

void create_pipe(int fd[2], int *infile_fd, int *outfile_fd)
{
	if (pipe(fd) == -1)
	{
		perror("Error creating pipe");
		close(*infile_fd);
		close(*outfile_fd);
		exit(EXIT_FAILURE);
	}
}
