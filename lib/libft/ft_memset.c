/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:30:46 by eandres           #+#    #+#             */
/*   Updated: 2024/04/11 11:22:51 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	char	*temp_dest;

	temp_dest = (char *)dest;
	while (count > 0)
	{
		*temp_dest = c;
		temp_dest++;
		count--;
	}
	return (dest);
}
