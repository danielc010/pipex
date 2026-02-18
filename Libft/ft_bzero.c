/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 16:49:46 by dachin        #+#    #+#                 */
/*   Updated: 2026/02/06 16:54:08 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief The bzero() function writes n zeroed bytes to the string s.
 * If n is zero, bzero() does nothing.
 * @param s
 * @param n
 */
void	ft_bzero(void	*s, size_t n)
{
	unsigned char	*tmp_s;
	size_t			i;

	i = 0;
	tmp_s = (unsigned char *)s;
	while (i < n)
	{
		tmp_s[i] = '\0';
		++i;
	}
}
