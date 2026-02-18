/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:07:31 by dachin            #+#    #+#             */
/*   Updated: 2025/05/07 13:51:51 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length_i(int n)
{
	int		length_i;
	long	m;

	length_i = 0;
	m = (long)n;
	if (m < 0)
		length_i = 1;
	while (m != 0)
	{
		m /= 10;
		length_i++;
	}
	return (length_i);
}

static char	*ft_zero_helper(void)
{
	char	*s;

	s = (char *)malloc(2 * sizeof(char));
	if (!s)
		return (NULL);
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		j;
	long	m;

	m = (long)n;
	j = ft_length_i(m);
	if (m == 0)
		return (ft_zero_helper());
	s = (char *)malloc((j + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[j] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		m *= -1;
	}
	while (m > 0 && j > 0)
	{
		s[j - 1] = m % 10 + '0';
		m /= 10;
		--j;
	}
	return (s);
}
