/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 12:39:22 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/18 06:37:05 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	*pids;

	if (argc < 5)
	{
		write(2, "Too few arguments.\n", 20);
		return (EXIT_FAILURE);
	}
	else if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		init_heredoc(&data, argv, envp, argc);
		pids = fork_children(&data, argv, envp);
		cleanup_resources(&data);
		wait_children(pids, data.num_cmds);
	}
	else if (argc >= 5)
	{
		init_pipex(&data, argv, envp, argc);
		pids = fork_children(&data, argv, envp);
		cleanup_resources(&data);
		wait_children(pids, data.num_cmds);
	}
	return (EXIT_SUCCESS);
}
