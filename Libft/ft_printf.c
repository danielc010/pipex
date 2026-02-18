/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/29 17:35:16 by dachin        #+#    #+#                 */
/*   Updated: 2025/06/19 08:31:40 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conv_spec(int c, va_list *args)
{
	if (c == 'c')
		return (ft_handle_char(args));
	else if (c == 's')
		return (ft_handle_string(args));
	else if (c == 'p')
		return (ft_handle_pointer(args));
	else if (c == 'i' || c == 'd')
		return (ft_handle_int(args));
	else if (c == 'u')
		return (ft_handle_uint(args));
	else if (c == 'x')
		return (ft_handle_hex(args, 0));
	else if (c == 'X')
		return (ft_handle_hex(args, 1));
	else if (c == '%')
		return (ft_handle_percent());
	return (0);
}

static int	ft_help_print(const char *format, va_list *args)
{
	int			char_count;

	char_count = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			char_count += conv_spec(*format, args);
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			char_count++;
			format++;
		}
	}
	return (char_count);
}

int	ft_printf(const char *format, ...)
{
	int			char_count;
	va_list		args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	char_count = ft_help_print(format, &args);
	va_end(args);
	return (char_count);
}
