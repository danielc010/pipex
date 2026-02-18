/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:42:44 by dachin            #+#    #+#             */
/*   Updated: 2025/05/26 17:58:49 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief The strlen() function calculates the length of the string pointed to 
 * by s, excluding the terminating null byte ('\0').
 * @param s 
 * @return size_t The strlen() function returns the number of bytes in the 
 * string pointed to by s.
 */
size_t	ft_strlen(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}
