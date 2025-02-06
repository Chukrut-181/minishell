/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:47:22 by eandres           #+#    #+#             */
/*   Updated: 2024/04/15 15:47:03 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dest, const char *str, size_t len)
{
	size_t	i;
	size_t	j;

	if (*str == '\0')
		return ((char *)dest);
	i = 0;
	while (dest[i] && i < len)
	{
		j = 0;
		while (dest[i + j] == str[j] && (i + j) < len)
		{
			j++;
			if (str[j] == '\0')
				return ((char *)dest + i);
		}
		i++;
	}
	return (NULL);
}
