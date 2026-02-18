/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:33:14 by danielchin        #+#    #+#             */
/*   Updated: 2025/05/28 10:21:39 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strlcpy() and strlcat() functions copy and concatenate strings 
 * respectively.  They are designed to be safer, more consistent, and less 
 * error prone replacements for strncpy(3) and strncat(3).  Unlike those func‐
 * tions, strlcpy() and strlcat() take the full size of the buffer (not just 
 * the length) and guarantee to NUL-terminate the result (as long as size is
 * larger than 0 or, in the case of strlcat(), as long as there is at least
 * one byte free in dst).  Note that a byte for the NUL should be included 
 * in size.  Also note that strlcpy() and strlcat() only operate on true “C”
 * strings.  This means that for strlcpy() src must be NUL-ter‐minated and 
 * for strlcat() both src and dst must be NUL-terminated.
 * 
 * The strlcpy() function copies up to size - 1 characters from the NUL-
 * terminated string src to dst, NUL-terminating the result.
 * 
 * The strlcat() function appends the NUL-terminated string src to the end 
 * of dst.  It will append at most size - strlen(dst) - 1 bytes, 
 * NUL-terminating the result.
 * @param dest 
 * @param src 
 * @param n 
 * @return size_t The strlcpy() and strlcat() functions return the total 
 * length of the string they tried to create.  For strlcpy() that means the 
 * length of src.  For strlcat() that means the initial length of dst plus 
 * the length of src.  While this may seem somewhat confusing, it was done 
 * to make truncation detection simple.
 * 
 * Note, however, that if strlcat() traverses size characters without finding a 
 * NUL, the length of the string is considered to be size and the destination 
 * string will not be NUL-terminated (since there was no space for the NUL).  
 * This keeps strlcat() from running off the end of a string.  In practice 
 * this should not happen (as it means that either size is incorrect or that 
 * dst is not a proper “C” string).  The check exists to prevent potential 
 * security problems in incorrect code.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (src[i] && (i < n - 1))
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
