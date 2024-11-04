/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:28:24 by eandres           #+#    #+#             */
/*   Updated: 2024/04/11 11:52:56 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_bor(char c, char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_bor(s1[start], set))
	{
		start++;
	}
	if (!s1[start])
	{
		return (ft_calloc(1, 1));
	}
	while (ft_bor(s1[end], set))
	{
		end--;
	}
	return (ft_substr(s1, start, (end - start + 1)));
}
