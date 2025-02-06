/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:50:52 by eandres           #+#    #+#             */
/*   Updated: 2024/04/16 14:55:24 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char	*temp_str;
	int		result;
	int		sign;

	result = 0;
	sign = 1;
	temp_str = (char *)str;
	while (*temp_str == 32 || (*temp_str >= 9 && *temp_str <= 13))
		temp_str++;
	if (*temp_str == '-' || *temp_str == '+')
	{
		if (*temp_str == '-')
			sign *= -1;
		temp_str++;
	}
	while (*temp_str >= '0' && *temp_str <= '9')
	{
		result = result * 10 + *temp_str - '0';
		temp_str++;
	}
	return (result * sign);
}
