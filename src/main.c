/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 12:39:22 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/06 17:09:41 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	*pids;
	int i;

	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		data.heredoc = 1;
		data.limiter = argv[2];
		data.num_cmds = argc - 4;

		// Read from terminal till LIMITER
		read_heredoc(&data);

		// Open outfile in APPEND mode.
		open_files_heredoc(&data, argv, argc);

		create_pipe(&data);

		// Get command paths (offset by 1)
		data.cmd_paths = malloc(sizeof(char *) * (data.num_cmds + 1));
		if (!data.cmd_paths)
			error_exit("malloc failed");
		data.cmd_paths[data.num_cmds] = NULL;
		i = 0;
		while (i < data.num_cmds)
		{
			data.cmd_paths[i] = get_path(argv[i + 3], envp);
			if (!data.cmd_paths[i])
			{
				write(2, "Command not found: ", 19);
				write(2, argv[i + 3], ft_strlen(argv[i + 3]));
				write(2, "\n", 1);
				cleanup_and_exit(&data);
			}
			++i;
		}

		// Execute commands
		pids = fork_children(&data, argv, envp);
		cleanup_resources(&data);
		wait_children(pids, data.num_cmds);
	}
	else if (argc >= 5)
	{
		data.heredoc = 0;
		data.num_cmds = argc - 3;
		init_pipex(&data, argv, envp, argc);
		pids = fork_children(&data, argv, envp);
		cleanup_resources(&data);
		wait_children(pids, data.num_cmds);
	}
	return (EXIT_SUCCESS);
}

