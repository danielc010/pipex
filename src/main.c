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

	if (argc < 5)
	{
		write(2, "Too few arguments.\n", 20);
		return (EXIT_FAILURE);
	}
	else if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		init_heredoc(&data, argv, envp, argc);
		fork_children(&data, argv, envp);
		cleanup_resources(&data);
		wait_children(data.pids, data.num_cmds, data.outfile_err);
	}
	else if (argc >= 5)
	{
		init_pipex(&data, argv, envp, argc);
		fork_children(&data, argv, envp);
		cleanup_resources(&data);
		wait_children(data.pids, data.num_cmds, data.outfile_err);
	}
	return (EXIT_SUCCESS);
}
