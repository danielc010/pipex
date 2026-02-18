/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_uint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: danielchin <danielchin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 07:25:10 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 10:14:19 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_uint(va_list *args)
{
	char			*string;
	int				char_count;
	unsigned int	uint_val;

	char_count = 0;
	uint_val = va_arg(*args, unsigned int);
	string = ft_itoa_uint(uint_val);
	ft_putstr_fd(string, 1);
	char_count = ft_strlen(string);
	free(string);
	return (char_count);
}
