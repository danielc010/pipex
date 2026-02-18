/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 19:19:53 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 15:05:08 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of nodes in the list. 
 * @param lst The beginning of the list.
 * @return int The length of the list
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*cur_node;
	int		i;

	cur_node = lst;
	i = 0;
	while (cur_node)
	{
		cur_node = cur_node->next;
		i++;
	}
	return (i);
}
