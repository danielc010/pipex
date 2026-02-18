/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:35:16 by dachin            #+#    #+#             */
/*   Updated: 2025/05/07 13:51:11 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the integer ’n’ to the specified file descriptor.
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	s[10];
	int		i;
	int		j;

	i = 9;
	j = 9;
	nbr = (long)n;
	if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	if (nbr < 0)
	{
		write (fd, "-", 1);
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		s[i] = nbr % 10 + '0';
		nbr /= 10;
		--i;
	}
	write (fd, &s[i + 1], j - i);
}
