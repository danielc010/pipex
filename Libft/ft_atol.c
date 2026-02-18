/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/02 15:13:22 by dachin        #+#    #+#                 */
/*   Updated: 2025/09/02 15:13:22 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief The atoi() function converts the initial portion of the string 
 * pointed to by nptr to int.  The behavior is the same as 
 * strtol(nptr, NULL, 10); except that atoi() does not detect errors.
 * The  atol()  and  atoll() functions behave the same as atoi(), except that
 * they convert the initial portion ofthe string to their return type of long
 * or long long.
 * @param nptr 
 * @return long The converted value or 0 on error.
 */
long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	value;

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
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		value = value * 10 + (nptr[i] - '0');
		++i;
	}
	return (sign * value);
}

// #include <stdlib.h>
// #include <limits.h>
// int main(void)
// {
// 	// long n = 2147483647;
// 	printf("%ld\n", atol("0"));
// 	printf("%ld\n", ft_atol("0"));
// 	printf("%ld\n", atol("2147483647"));
// 	printf("%ld\n", ft_atol("2147483647"));
// 	printf("%ld\n", atol("-2147483648"));
// 	printf("%ld\n", ft_atol("-2147483648"));
// 	printf("%ld\n", atol("-2147483649"));
// 	printf("%ld\n", ft_atol("-2147483649"));
// 	printf("%ld\n", atol("2147483648"));
// 	printf("%ld\n", ft_atol("2147483648"));
// 	return 0;
// }