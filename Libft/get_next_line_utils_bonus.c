/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 13:02:13 by dachin        #+#    #+#                 */
/*   Updated: 2025/07/22 10:36:17 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Helper 1: Update stash with new buffer content
char	*update_stash(char *stash, char *buffer)
{
	char	*new_stash;

	if (stash)
	{
		new_stash = ft_strjoin(stash, buffer);
		free(stash);
		return (new_stash);
	}
	return (ft_substr(buffer, 0, ft_strlen(buffer)));
}

// Helper 2: Process newline and update stash
char	*process_newline(char **stash)
{
	char	*newline_ptr;
	char	*newline;
	char	*temp;

	if (!*stash || !ft_strchr(*stash, '\n'))
		return (NULL);
	newline_ptr = ft_strchr(*stash, '\n');
	newline = ft_substr(*stash, 0, newline_ptr - *stash + 1);
	if (!newline)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	temp = handle_remaining_stash(*stash, newline_ptr);
	if (!temp)
	{
		free(*stash);
		*stash = NULL;
		return (newline);
	}
	free(*stash);
	*stash = temp;
	return (newline);
}

// Helper 3: Handle remaining stash after newline
char	*handle_remaining_stash(char *stash, char *newline_ptr)
{
	char	*temp;

	if (newline_ptr - stash + 1 < (long)ft_strlen(stash))
	{
		temp = ft_substr(stash, newline_ptr - stash + 1,
				ft_strlen(stash) - (newline_ptr - stash + 1));
		return (temp);
	}
	return (NULL);
}

// Helper 4: Handle rest of the line - no more bytes read
char	*handle_eof(char **stash, char *buffer)
{
	char	*newline;
	char	*last_line;

	free(buffer);
	if (!*stash || !**stash)
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	newline = process_newline(stash);
	if (newline)
		return (newline);
	last_line = ft_substr(*stash, 0, ft_strlen(*stash));
	free(*stash);
	*stash = NULL;
	return (last_line);
}

// Helper 5: Cleanup on error
void	cleanup_on_error(char **stash, char *buffer)
{
	if (buffer)
		free(buffer);
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
}
