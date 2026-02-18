/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_string.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: danielchin <danielchin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 20:11:02 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 10:18:33 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_string(va_list *args)
{
	char	*str_val;

	str_val = va_arg(*args, char *);
	if (str_val == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
	{
		ft_putstr_fd(str_val, 1);
		return (ft_strlen(str_val));
	}
}
