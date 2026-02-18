/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:12:42 by dachin            #+#    #+#             */
/*   Updated: 2025/05/28 09:31:02 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strnstr() function locates the first occurrence of the null-
 * terminated string little in the string big, where not more than len 
 * characters are searched.  Characters that appear after a ‘\0’ character are 
 * not searched.  Since the strnstr() function is a FreeBSD specific API, it 
 * should only be used when portability is not a concern.
 * @param big 
 * @param little Null terminated string
 * @param n 
 * @return char* If little is an empty string, big is returned; if little 
 * occurs nowhere in big, NULL is returned; otherwise a pointer to the first 
 * character of the first occurrence of little is returned.
 */
char	*ft_strnstr(char *big, char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!little[0])
		return (big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j]
			&& big[i + j] && i + j < len)
		{
			++j;
			if (!little[j])
				return (&big[i]);
		}
		++i;
	}
	return (NULL);
}
