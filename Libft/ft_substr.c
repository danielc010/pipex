/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/29 09:42:14 by dachin        #+#    #+#                 */
/*   Updated: 2025/07/08 08:46:01 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory (using malloc(3)) and returns a substring from the 
 * string 's'. The substring starts at index 'start' and has a maximum length 
 * of 'len'.
 * @param s The original string from which to create the substring.
 * @param start The starting index of the substring within 's'.
 * @param len The maximum length of the substring.
 * @return char* The substring. NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = 0;
	if (!s || start >= ft_strlen(s))
	{
		substring = malloc(1 * sizeof(char));
		if (!substring)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	if (len > ft_strlen(s + start))
		len = (ft_strlen(s + start));
	substring = malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start + i];
		++i;
	}
	substring[i] = '\0';
	return (substring);
}
