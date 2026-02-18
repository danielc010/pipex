/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/23 14:59:02 by dachin        #+#    #+#                 */
/*   Updated: 2025/07/30 12:21:47 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief The  atoi() function converts the initial portion of the nptrtring 
 * pointed to by nptr to int.
 * @param nptr 
 * @return int The converted value or 0 on error.
 */
int	ft_atoi(const char	*nptr)
{
	int	i;
	int	sign;
	int	value;

	i = 0;
	sign = 1;
	value = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		++i;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		++i;
	}
	while (ft_isdigit(nptr[i]))
	{
		value = value * 10 + (nptr[i] - '0');
		++i;
	}
	return (sign * value);
}
