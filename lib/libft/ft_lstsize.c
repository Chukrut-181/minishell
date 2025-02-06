/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:04:43 by eandres           #+#    #+#             */
/*   Updated: 2024/04/16 18:13:30 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tab;
	size_t	i;

	i = 0;
	tab = lst;
	if (!lst)
		return (0);
	while (tab != NULL)
	{
		tab = tab->next;
		i++;
	}
	return (i);
}
