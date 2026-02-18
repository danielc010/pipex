/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 17:24:36 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 17:40:21 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		++i;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
