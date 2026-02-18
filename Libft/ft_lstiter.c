/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dachin <dachin@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:58 by dachin            #+#    #+#             */
/*   Updated: 2025/05/06 13:53:58 by dachin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates through the list ’lst’ and applies the function ’f’ to the 
 * content of each node.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function to apply to each
node’s content.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cur_node;

	if (!lst || !f)
		return ;
	cur_node = lst;
	while (cur_node)
	{
		f(cur_node->content);
		cur_node = cur_node->next;
	}
}
