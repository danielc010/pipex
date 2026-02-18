/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_hex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 09:20:54 by dachin        #+#    #+#                 */
/*   Updated: 2025/06/12 10:00:48 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_hex(va_list *args, int upper)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (ft_uitoa_hex(n, upper));
}
