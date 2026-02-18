/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:26:08 by dachin            #+#    #+#             */
/*   Updated: 2025/05/07 13:52:18 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  strdup() function returns a pointer to a new string which is a du‐
 * plicate of the string s.  Memory for the new string  is  obtained  with
 * malloc(3), and can be freed with free(3).
 * @param s Source string
 * @return char* On  success,  the strdup() function returns a pointer to the 
 * duplicated string.  It returns NULL if insufficient memory was available, 
 * with er‐rno set to indicate the cause of the error.
 */
char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		++i;
	}
	ptr[i] = s[i];
	return (ptr);
}
