/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitoa_hex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: danielchin <danielchin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 06:57:27 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 18:15:15 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_zero_helper_hex(unsigned int n)
{
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
		return (0);
}

static int	hex_len(unsigned int n)
{
	int	num_hex_digits;

	num_hex_digits = 0;
	while (n > 0)
	{
		n /= 16;
		++num_hex_digits;
	}
	return (num_hex_digits);
}

static char	hex_digit(unsigned int digit, int upper)
{
	if (digit < 10)
		return ('0' + digit);
	if (upper)
		return ('A' + (digit - 10));
	return ('a' + (digit - 10));
}

int	ft_uitoa_hex(unsigned int n, int upper)
{
	int				string_length;
	int				current_index;
	char			hex_buffer[19];

	if (ft_zero_helper_hex(n))
		return (1);
	string_length = hex_len(n);
	current_index = string_length - 1;
	while (current_index >= 0)
	{
		hex_buffer[current_index] = hex_digit(n % 16, upper);
		n /= 16;
		--current_index;
	}
	write(1, hex_buffer, string_length);
	return (string_length);
}
