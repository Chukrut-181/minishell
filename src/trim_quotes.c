/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:51:34 by igchurru          #+#    #+#             */
/*   Updated: 2024/11/20 09:42:14 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_quotes(char const *s1)
{
	int	count;
	int	i;
	bool	dquote;	// Booleano: 1 si estamos dentro de comillas dobles.
	bool	squote;	// Ídem, pero comilla simple.

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (s1 && s1[i])
	{
		squote = (squote + (!dquote && s1[i] == '\'')) % 2;	//tomamos el módulo (0 ó 1) que será el bool.
		dquote = (dquote + (!squote && s1[i] == '\"')) % 2;	//tomamos el módulo (0 ó 1)
		if ((s1[i] == '\"' && !squote) || (s1[i] == '\'' && !dquote)) //si hay " fuera de '' || si hay ' fuera de ""...
			count++;	//...contamos.
		i++;	//avanzamos por el string.
	}
	if (squote || dquote)	//si los booleanos no terminan en 0 significa que hay comillas impares; es un error.
		return (-1);
	return (count);	//retornamos la cuenta.
}

char	*ft_strtrim_quotes(char const *s1, int squote, int dquote)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = count_quotes(s1);
	if (!s1 || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]])
	{
		squote = (squote + (!dquote && s1[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || squote) && (s1[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}