/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:16:39 by dachin            #+#    #+#             */
/*   Updated: 2025/05/27 20:52:02 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  memchr()  function scans the initial n bytes of the memory area 
 * pointed to by s for the first instance of c.  Both c and the bytes of the 
 * memory area pointed to by s are interpreted as unsigned char.
 * @param s 
 * @param c 
 * @param n 
 * @return void* The  memchr()  and memrchr() functions return a pointer to 
 * the matching byte or NULL if the character does not occur in the given 
 * memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)(c))
			return ((void *)&p[i]);
		++i;
	}
	return (NULL);
}
