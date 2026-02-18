/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 19:51:26 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 15:05:00 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the last node of the list.
 * 
 * @param lst The beginning of the list.
 * @return * t_list* Last node of the list
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur_node;

	if (!lst)
		return (NULL);
	cur_node = lst;
	while (cur_node->next)
		cur_node = cur_node->next;
	return (cur_node);
}
