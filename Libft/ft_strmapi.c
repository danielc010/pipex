/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:17:46 by dachin            #+#    #+#             */
/*   Updated: 2025/05/07 13:53:06 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function f to each character of the string s, passing 
 * its index as the first argument and the character itself as the second. 
 * A new string is created (using malloc(3)) to store the results from the 
 * successive applications of f.
 * @param s The string to iterate over.
 * @param f The function to apply to each character.
 * @return char* The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	p = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = (*f)(i, s[i]);
		++i;
	}
	p[i] = '\0';
	return (p);
}
