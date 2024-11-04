#include "libft.h"

int	main()
{
	int	fd = open("prueba2.txt", O_RDWR);
	char	*str;
	
	str = "Hola";
		str = get_next_line(fd);
		printf("%s", str);
	close(fd);
	return (0);
}
