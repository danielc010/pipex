/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_hex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/30 21:57:34 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 10:05:13 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_zero_helper_hex(uintptr_t addr)
{
	if (addr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
		return (0);
}

static int	hex_len(uintptr_t addr)
{
	int	num_hex_digits;

	num_hex_digits = 0;
	while (addr > 0)
	{
		addr /= 16;
		++num_hex_digits;
	}
	return (num_hex_digits);
}

int	ft_itoa_hex(void *ptr_val)
{
	uintptr_t	addr;
	int			string_length;
	int			current_index;
	char		hex_buffer[19];
	int			digit;

	addr = (uintptr_t)ptr_val;
	if (ft_zero_helper_hex(addr))
		return (5);
	hex_buffer[0] = '0';
	hex_buffer[1] = 'x';
	string_length = hex_len(addr) + 2;
	current_index = string_length - 1;
	while (current_index >= 2)
	{
		digit = addr % 16;
		if (digit < 10)
			hex_buffer[current_index] = '0' + digit;
		else
			hex_buffer[current_index] = 'a' + (digit - 10);
		addr /= 16;
		--current_index;
	}
	write(1, hex_buffer, string_length);
	return (string_length);
}
