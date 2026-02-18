/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 13:02:10 by dachin        #+#    #+#                 */
/*   Updated: 2025/07/22 10:37:55 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*update_stash(char *stash, char *buffer);
char	*process_newline(char **stash);
char	*handle_remaining_stash(char *stash, char *newline_ptr);
char	*handle_eof(char **stash, char *buffer);
void	cleanup_on_error(char **stash, char *buffer);
char	*get_next_line(int fd);

#endif