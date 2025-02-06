/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:34:56 by eandres           #+#    #+#             */
/*   Updated: 2024/04/15 19:14:15 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *) malloc(sizeof(*str) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char	*ft_itoa(int num)
{
	char		*dest;
	int			count;
	int			i;
	long int	n;

	n = num;
	count = count_size(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
	dest = ft_strnew(count);
	if (dest == NULL)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		dest[0] = '-';
		i++;
	}
	while (count-- > i)
	{
		dest[count] = (n % 10) + '0';
		n /= 10;
	}
	return (dest);
}
