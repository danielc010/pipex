/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 19:55:26 by dachin        #+#    #+#                 */
/*   Updated: 2025/08/20 15:05:05 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory (using malloc(3)) and returns a new node. The 
 * ’content’ member variable is initialized with the given parameter ’content’.
 * The variable ’next’ is initialized to NULL.
 * @param content The content to store in the new node.
 * @return t_list* A pointer to the new node.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
