/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:12:48 by dachin            #+#    #+#             */
/*   Updated: 2025/05/28 08:32:36 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  memcpy()  function  copies  n  bytes from memory area src to 
 * memory area dest.  The memory areas must not overlap.  Use memmove(3) if 
 * the memory areas do overlap.
 * @param dest 
 * @param src 
 * @param n 
 * @return void* The memcpy() function returns a pointer to dest.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_src;
	unsigned char	*tmp_dest;

	i = 0;
	if (n == 0 || (!dest && !src))
		return (dest);
	tmp_src = (unsigned char *)src;
	tmp_dest = (unsigned char *)dest;
	while (i < n)
	{
		tmp_dest[i] = tmp_src[i];
		++i;
	}
	return (dest);
}
