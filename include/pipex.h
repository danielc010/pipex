/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 09:34:08 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/02 23:21:53 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
# define PIPEX

# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>

// parsing.c
char	**extract_path_to_array(char **envp);
char	*extract_cmd_name(char *cmd);
char	**append_cmd(char **paths_array, char *cmd);
char	*get_path(char *cmd, char **envp);

// utils.c
void	free_array(char **array);
void	open_files(char *argv1, char *argv4, int *infile_fd, int *outfile_fd);
void create_pipe(int fd[2], int *infile_fd, int *outfile_fd);
#endif
