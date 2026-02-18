/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 13:02:06 by dachin        #+#    #+#                 */
/*   Updated: 2025/09/02 11:30:11 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief The strlen() function calculates the length of the string pointed to 
 * by s, excluding the terminating null byte ('\0').
 * @param s 
 * @return size_t The strlen() function returns the number of bytes in the 
 * string pointed to by s.
 */
// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 		++i;
// 	return (i);
// }

/**
 * @brief The strchr() function locates the first occurrence of c (converted to a
 * char) in the string pointed to by s.  The terminating null character is
 * considered to be part of the string; therefore if c is `\0', the functions 
 * locate the terminating `\0'.
 * @param s 
 * @param c 
 * @return char* The functions strchr() and strrchr() return a pointer to the 
 * located character, or NULL if the character does not appear in the string.
 */
// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		++i;
// 	}
// 	if (s[i] == (char)c)
// 		return ((char *)&s[i]);
// 	return (NULL);
// }

/**
 * @brief Allocates memory (using malloc(3)) and returns a substring from the 
 * string 's'. The substring starts at index 'start' and has a maximum length 
 * of 'len'.
 * @param s The original string from which to create the substring.
 * @param start The starting index of the substring within 's'.
 * @param len The maximum length of the substring.
 * @return char* The substring. NULL if the allocation fails.
 */
// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*substring;
// 	unsigned int	i;

// 	i = 0;
// 	if (!s || start >= ft_strlen(s))
// 	{
// 		substring = malloc(1 * sizeof(char));
// 		if (!substring)
// 			return (NULL);
// 		substring[0] = '\0';
// 		return (substring);
// 	}
// 	if (len > ft_strlen(s + start))
// 		len = (ft_strlen(s + start));
// 	substring = malloc((len + 1) * sizeof(char));
// 	if (!substring)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		substring[i] = s[start + i];
// 		++i;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }

/**
 * @brief Allocates memory (using malloc(3)) and returns a new string, 
 * which is the result of concatenating ’s1’ and ’s2’.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return char* The new string. NULL if the allocation fails.
 */
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	len1;
// 	size_t	len2;
// 	char	*ptr;

// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	ptr = malloc((len1 + len2 + 1) * sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	while (s1 && i < len1)
// 	{
// 		ptr[i] = s1[i];
// 		++i;
// 	}
// 	j = 0;
// 	while (s2 && j < len2)
// 	{
// 		ptr[i + j] = s2[j];
// 		++j;
// 	}
// 	ptr[i + j] = '\0';
// 	return (ptr);
// }

/**
 * @brief Write a function that returns a line read from a file descriptor
 * @param fd The file descriptor to read from
 * @return char* Read line: correct behavior
 * NULL: there is nothing else to read, or an error occurred
 */
char	*get_next_line_bonus(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	char		*newline;
	ssize_t		bytes_read;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		stash[fd] = update_stash(stash[fd], buffer);
		if (!stash[fd])
			return (cleanup_on_error(&stash[fd], buffer), NULL);
		newline = process_newline(&stash[fd]);
		if (newline)
			return (free(buffer), newline);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (cleanup_on_error(&stash[fd], buffer), NULL);
	return (handle_eof(&stash[fd], buffer));
}
