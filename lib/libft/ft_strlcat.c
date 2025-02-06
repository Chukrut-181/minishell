/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:33:30 by eandres           #+#    #+#             */
/*   Updated: 2024/04/16 16:13:11 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	n;
	size_t	ret;
	size_t	i;

	i = 0;
	n = 0;
	if (size == 0)
		return (ft_strlen(src));
	else if (size < ft_strlen(dest))
		ret = ft_strlen(src) + size;
	else
		ret = ft_strlen(dest) + ft_strlen(src);
	while (dest[i] != '\0')
		i++;
	while (src[n] != '\0' && i + 1 < size)
	{
		dest[i] = src[n];
		i++;
		n++;
	}
	dest[i] = '\0';
	return (ret);
}
