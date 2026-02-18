/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_uint.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 12:07:31 by dachin        #+#    #+#                 */
/*   Updated: 2025/06/12 09:11:40 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_length_i(unsigned int n)
{
	int		length_i;

	length_i = 0;
	while (n != 0)
	{
		n /= 10;
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

char	*ft_itoa_uint(unsigned int n)
{
	char			*s;
	unsigned int	len_str;

	len_str = ft_length_i(n);
	if (n == 0)
		return (ft_zero_helper());
	s = (char *)malloc((len_str + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[len_str] = '\0';
	while (n > 0)
	{
		s[len_str - 1] = n % 10 + '0';
		n /= 10;
		--len_str;
	}
	return (s);
}
