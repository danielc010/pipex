/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_percent.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: danielchin <danielchin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 07:34:37 by danielchin    #+#    #+#                 */
/*   Updated: 2025/06/12 15:23:04 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_percent(void)
{
	write(1, "%", 1);
	return (1);
}
