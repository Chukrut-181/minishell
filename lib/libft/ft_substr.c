/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:21:37 by eandres           #+#    #+#             */
/*   Updated: 2024/04/15 20:34:18 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0 || ft_strlen(s) == 0)
		return (ft_strdup(""));
	while (j < len && s[j + i] != '\0')
		j++;
	new_str = (char *)malloc((sizeof(char) * j) + 1);
	if (new_str == NULL)
		return (0);
	j = 0;
	while (i < ft_strlen(s) && j < len)
	{
		new_str[j] = s[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
