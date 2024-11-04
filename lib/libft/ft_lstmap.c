/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:27:19 by eandres           #+#    #+#             */
/*   Updated: 2024/04/16 13:37:33 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp_new;
	t_list	*temp_last;
	t_list	*new_lst;

	if (!lst || !f || !del)
		return (0);
	new_lst = ft_lstnew((*f)(lst->content));
	if (!new_lst)
		return (0);
	temp_new = new_lst;
	temp_last = lst->next;
	while (temp_last)
	{
		temp_new->next = ft_lstnew((*f)(temp_last->content));
		if (!temp_new->next)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		temp_new = temp_new->next;
		temp_last = temp_last->next;
	}
	return (new_lst);
}
