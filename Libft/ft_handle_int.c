/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_int.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: danielchin <danielchin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 20:18:09 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 15:36:26 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_int(va_list *args)
{
	char	*string;
	int		char_count;
	int		int_val;

	int_val = va_arg(*args, int);
	string = ft_itoa(int_val);
	char_count = 0;
	ft_putstr_fd(string, 1);
	char_count = ft_strlen(string);
	free(string);
	return (char_count);
}
