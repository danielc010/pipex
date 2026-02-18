/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/29 11:05:05 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 17:43:19 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
// 	char	*ptr;

// 	i = 0;
// 	j = 0;
// 	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	while (s1 && (i < ft_strlen(s1)))
// 	{
// 		ptr[i] = s1[i];
// 		++i;
// 	}
// 	while (s2 && (j < ft_strlen(s2)))
// 	{
// 		ptr[i] = s2[j];
// 		++j;
// 		++i;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*ptr;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc((len1 + len2 + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1 && i < len1)
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && j < len2)
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}
