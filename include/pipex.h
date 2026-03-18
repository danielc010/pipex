/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 09:34:08 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/18 13:33:37 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

// num_cmds: number of cmds
// pipes: array of pipe pairs
// cmd_paths: array of cmd paths
// heredoc: flag for heredoc mode
typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		num_cmds;
	int		**pipes;
	char	**cmd_paths;
	int		heredoc;
	int		outfile_err;
	pid_t	*pids;
	char	*limiter;
}	t_pipex;

// parsing.c
char	**extract_path_to_array(char **envp);
char	*extract_cmd_name(char *cmd);
char	**append_cmd(char **paths_array, char *cmd);
char	*get_path(char *cmd, char **envp);

// utils.c (initialization)
void	create_pipe(t_pipex *data);
void	init_pipex(t_pipex *data, char **argv, char**envp, int argc);
int		error_exit(char *msg);

// utils2.c (cleanup + fork)
void	free_array(char **array);
void	close_all_pipes(int **pipes, int num_pipes);
void	cleanup_resources(t_pipex *data);
void	cleanup_and_exit(t_pipex *data);
void	fork_children(t_pipex *data, char **argv, char **envp);

// utils3.c (child lifecycle)
void	wait_children(pid_t *pids, int num_cmds, int outfile_err);
void	free_child_data(t_pipex *data);

// utils4.c (execution)
void	run_execve(t_pipex *data, int cmd_index, char **cmd_args, char **envp);
void	execute_cmd(t_pipex *data, int cmd_index, char **argv, char **envp);

// heredoc.c
void	init_heredoc(t_pipex *data, char **argv, char**envp, int argc);

#endif
