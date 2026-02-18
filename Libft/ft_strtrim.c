/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:14:36 by dachin            #+#    #+#             */
/*   Updated: 2025/05/07 13:55:20 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(set))
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}

/**
 * @brief Allocates memory (using malloc(3)) and returns a
 * copy of 's1' with characters from 'set' removed
 * from the beginning and the end.
 * 
 * @param set The string to be trimmed.
 * @param c The string containing the set of characters to be removed.
 * @return int 
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	while (s1[i] && ft_in_set(set, s1[i]))
		++i;
	while (ft_in_set(set, s1[j]) && j > i)
		--j;
	ptr = malloc(((j - i) + 2) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < j + 1)
	{
		ptr[k] = s1[i];
		++k;
		++i;
	}
	ptr[k] = '\0';
	return (ptr);
}
