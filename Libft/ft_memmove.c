/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:42:03 by dachin            #+#    #+#             */
/*   Updated: 2025/05/28 09:05:12 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_src;
	unsigned char	*tmp_dest;

	i = n;
	if (n == 0 || (!dest && !src))
		return (dest);
	tmp_src = (unsigned char *)src;
	tmp_dest = (unsigned char *)dest;
	if (tmp_dest < tmp_src || tmp_dest > tmp_src + n)
		return (ft_memcpy(tmp_dest, tmp_src, n));
	else
	{
		while (i > 0)
		{
			--i;
			tmp_dest[i] = tmp_src[i];
		}
	}
	return (dest);
}
