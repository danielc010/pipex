/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 17:39:09 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 15:04:45 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds the node ’new’ at the end of the list.
 * @param lst The address of a pointer to the first node of a list.
 * @param new The address of a pointer to the node to be added.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_node;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		cur_node = ft_lstlast(*lst);
		cur_node->next = new;
	}
}
