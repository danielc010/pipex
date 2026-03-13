/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/02 15:33:18 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/02 22:09:26 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// splits the env var starting w "PATH=" then store in array
char	**extract_path_to_array(char **envp)
{
	int		i;
	char	**paths_array;
	char	*temp;

	i = 0;
	paths_array = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			temp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			paths_array = ft_split(temp, ':');
			free(temp);
			break ;
		}
		++i;
	}
	return (paths_array);
}

// extract only the non-argument / flag part of the command e.g. ls in "ls -l"
char	*extract_cmd_name(char *cmd)
{
	int		i;
	char	*result;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		++i;
	result = ft_substr(cmd, 0, i);
	if (!result)
		return (NULL);
	return (result);
}

// append a "/" and cmd to the path
char	**append_cmd(char **paths_array, char *cmd)
{
	int		i;
	char	*temp;
	char	*with_slash;

	i = 0;
	while (paths_array[i])
	{
		temp = ft_strjoin(paths_array[i], "/");
		if (!temp)
			return (NULL);
		with_slash = ft_strjoin(temp, cmd);
		free(temp);
		free(paths_array[i]);
		paths_array[i] = with_slash;
		++i;
	}
	return (paths_array);
}

static char	*path_lookup(char **envp, char *cmd_name)
{
	char	**paths_array;
	char	*result;
	int		i;

	paths_array = extract_path_to_array(envp);
	if (!paths_array || !append_cmd(paths_array, cmd_name))
		return (free(cmd_name), free_array(paths_array), NULL);
	free(cmd_name);
	i = 0;
	result = NULL;
	while (paths_array[i])
	{
		if (access(paths_array[i], X_OK) == 0)
		{
			result = ft_strdup(paths_array[i]);
			break ;
		}
		i++;
	}
	return (free_array(paths_array), result);
}

char	*get_path(char *cmd, char **envp)
{
	char	*cmd_name;

	cmd_name = extract_cmd_name(cmd);
	if (!cmd_name)
		return (NULL);
	if (cmd_name[0] == '/' || (cmd_name[0] == '.' && cmd_name[1] == '/'))
	{
		if (access(cmd_name, X_OK) == 0)
			return (cmd_name);
		return (free(cmd_name), NULL);
	}
	return (path_lookup(envp, cmd_name));
}
