/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:04:43 by eandres           #+#    #+#             */
/*   Updated: 2024/04/11 11:52:44 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dest;
	char	*temp_src;

	len = ft_strlen(src) + 1;
	temp_src = (char *)src;
	dest = (char *)malloc(sizeof(char) * len);
	if (dest == NULL)
	{
		return (0);
	}
	ft_strcpy(dest, temp_src);
	return (dest);
}
