/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_char.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: danielchin <danielchin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 20:08:19 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 10:58:32 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_char(va_list *args)
{
	int	char_val;

	char_val = va_arg(*args, int);
	ft_putchar_fd((char)char_val, 1);
	return (1);
}
