/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 12:39:22 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/13 16:37:00 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	*pids;

	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		data.heredoc = 1;
		data.limiter = argv[2];
		data.num_cmds = argc - 4;
		init_heredoc(&data, argv, envp, argc);
		pids = fork_children(&data, argv, envp);
		cleanup_resources(&data);
		return (wait_children(pids, data.num_cmds));
	}
	else if (argc >= 5)
	{
		data.heredoc = 0;
		data.num_cmds = argc - 3;
		init_pipex(&data, argv, envp, argc);
		pids = fork_children(&data, argv, envp);
		cleanup_resources(&data);
		return (wait_children(pids, data.num_cmds));
	}
	return (EXIT_SUCCESS);
}
