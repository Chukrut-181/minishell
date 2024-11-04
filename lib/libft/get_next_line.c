/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:57:12 by eandres           #+#    #+#             */
/*   Updated: 2024/04/25 11:53:22 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	glob[BUFFER_SIZE + 1];
	char		*resul;
	int			i;

	i = 1;
	resul = (char *)malloc(sizeof (char) * 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !resul)
		return ((free(resul)), NULL);
	resul[0] = '\0';
	resul = mod_strjoin(resul, glob);
	while ((mod_strchr(resul, '\n') < 0) && i > 0)
	{
		i = read(fd, glob, BUFFER_SIZE);
		if (i > 0)
		{
			glob[i] = '\0';
			resul = mod_strjoin(resul, glob);
		}
		if (i == -1)
			return (free(resul), ft_bzero(glob, mod_strchr(glob, '\0')), NULL);
	}
	if (resul[0] == '\0')
		return (free(resul), NULL);
	return (ft_cut_buffer(glob), resul);
}

/* int	main()
{
	int	fd = open("prueba2.txt", O_RDWR);
	char	*str;
	
	str = "Hola";
	while (str[0] != '\0')
	{
		str = get_next_line(fd);
		printf("%s", str);
	}
	close(fd);
	return (0);
} */