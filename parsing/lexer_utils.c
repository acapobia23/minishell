#include "../mini.h"

int	find_flag(t_flag *flag, char *c)
{
	printf("char c find %s \n", c);
	if (c[0] == '"' && flag->double_quotes == true)
	return (0);
	else if (c[0] == '\'' && flag->singol_quotes == true)
		return (0);
	else if (c[0] == '$' && flag->dollar == true)
		return (0);
	else if (c[0] == '<' && flag->redirect_input == true)
		return (0);
	else if (c[0] == '>' && flag->redirect_output == true)
		return (0);
	else if (c[0] == '>' && c[1] == '>' && flag->append_mode == true)
		return (0);
	else if (c[0] == '|' && flag->pipe == true)
		return (0);
	else if (c[0] == '<' && c[1] == '<' && flag->delimiter == true)
		return (0);
	return (-1);
}