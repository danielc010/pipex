/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 12:39:22 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/04 14:48:04 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41)
		, EXIT_FAILURE);
	init_pipex(&data, argv, envp);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("Error forking child 1")
		, cleanup_and_exit(&data), EXIT_FAILURE);
	if (pid1 == 0)
		execute_child1(&data, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("Error forking child 2")
		, cleanup_and_exit(&data), EXIT_FAILURE);
	if (pid2 == 0)
		execute_child2(&data, argv, envp);
	cleanup_resources(&data);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}

