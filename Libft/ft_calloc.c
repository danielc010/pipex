/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:06:30 by dachin            #+#    #+#             */
/*   Updated: 2025/05/28 16:56:42 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
/**
 * @brief The calloc() function allocates memory for an array of  nmemb  
 * elements of  size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero.  If nmemb or size is 0,  then  calloc()  returns
 * either  NULL,  or a unique pointer value that can later be successfully
 * passed to free().  If the multiplication of nmemb and size would result
 * in  integer  overflow, then calloc() returns an error.  By contrast, an
 * integer overflow would not be detected in the following  call  to  malloc(),
 * with the result that an incorrectly sized block of memory would be 
 * allocated: malloc(nmemb * size);
 * @param nmemb 
 * @param size 
 * @return void* The malloc() and calloc() functions return a pointer to  
 * the  allocated memory,  which  is  suitably  aligned for any built-in type.
 * On error, these functions return NULL.  NULL may also be returned by a 
 * successful call  to  malloc() with a size of zero, or by a successful call 
 * to calloc() with nmemb or size equal to zero.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
