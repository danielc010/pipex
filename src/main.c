/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 12:39:22 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/04 17:28:36 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	*pids;

	if (argc < 5)
		error_exit("Usage: ./pipex file1 cmd1 cmd2 cmdn file2");
	data.num_cmds = argc - 3;
	init_pipex(&data, argv, envp, argc);
	pids = fork_children(&data, argv, envp);
	cleanup_resources(&data);
	wait_children(pids, data.num_cmds);
	return (EXIT_SUCCESS);
}

