/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 21:26:23 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 15:04:51 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes and frees the given node and all its successors, using the 
 * function ’del’ and free(3). Finally, set the pointer to the list to NULL.
 * @param lst The address of a pointer to a node.
 * @param del The address of the function used to delete the content of 
 * the node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur_node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		cur_node = *lst;
		*lst = (*lst)->next;
		del(cur_node->content);
		free(cur_node);
	}
}
