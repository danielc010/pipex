/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_pointer.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: danielchin <danielchin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 20:15:52 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 10:22:26 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_pointer(va_list *args)
{
	void	*ptr_val;

	ptr_val = va_arg(*args, void *);
	return (ft_itoa_hex(ptr_val));
}
