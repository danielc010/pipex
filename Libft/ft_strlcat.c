/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/23 12:05:02 by dachin        #+#    #+#                 */
/*   Updated: 2025/06/20 13:43:50 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strlcpy() and strlcat() functions copy and concatenate strings 
 * respectively.  They are designed to be safer, more consistent, and less 
 * error prone replacements for strncpy(3) and strncat(3).  Unlike those 
 * functions, strlcpy() and strlcat() take the full size of the buffer 
 * (not just the length) and guarantee to NUL-terminate the result (as long 
 * as size is larger than 0 or, in the case of strlcat(), as long as there 
 * is at least one byte free in dst).  Note that a byte for the NUL should 
 * be included in size.  Also note that strlcpy() and strlcat() only operate 
 * on true “C” strings.  This means that for strlcpy() src must be 
 * NUL-terminated and for strlcat() both src and dst must be NUL-
 * terminated.
 * 
 * The strlcpy() function copies up to size - 1 characters from the 
 * NUL-terminated string src to dst, NUL-terminating the result.
 * 
 * The strlcat() function appends the NUL-terminated string src to the end of 
 * dst.  It will append at most size - strlen(dst) - 1 bytes, 
 * NUL-terminating the result.
 * @param dst 
 * @param src 
 * @param n 
 * @return size_t 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = 0;
	s_len = ft_strlen(src);
	i = 0;
	while (d_len < n && dst[d_len])
		++d_len;
	if (d_len == n)
		return (n + s_len);
	while ((i < (n - d_len - 1)) && src[i])
	{
		dst[d_len + i] = src[i];
		++i;
	}
	if (d_len + i < n)
		dst[d_len + i] = '\0';
	return (d_len + s_len);
}
