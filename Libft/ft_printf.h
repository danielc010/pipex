/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:06:27 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 15:20:38 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

int		ft_itoa_hex(void *ptr_val);
char	*ft_itoa_uint(unsigned int n);
int		ft_uitoa_hex(unsigned int n, int upper);
int		ft_handle_char(va_list *args);
int		ft_handle_string(va_list *args);
int		ft_handle_pointer(va_list *args);
int		ft_handle_int(va_list *args);
int		ft_handle_percent(void);
int		ft_handle_uint(va_list *args);
int		ft_handle_hex(va_list *args, int upper);
int		ft_printf(const char *format, ...);

#endif
