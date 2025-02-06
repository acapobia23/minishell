#include "libft.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ')
		return (0);
	else
		return (-1);
}
