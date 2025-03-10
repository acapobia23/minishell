#include "../mini.h"

void	ft_free_mtx(char **matrix)
{
	char	**ptr;

	if (matrix == NULL)
		return ;
	ptr = matrix;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(matrix);
}

char	*ft_mystrjoin(char **mtx)
{
	char	*str;
	char	*tmp;
	int		i;

	if (!mtx)
		return (NULL);
	str = ft_strdup((const char *)mtx[0]);
	if (!str)
		return (NULL);
	i = 1;
	while (mtx[i])
	{
		tmp = ft_strdup((const char *)str);
		str = ft_strjoin((const char *)tmp, (const char *)mtx[i]);
		free(tmp);
		if (!str)
			return (NULL);
		i++;
	}
	return (str);
}

static char	*take_quote_str(char *arg, int start)
{
	char	*str;
	char	*tmp;
	int		end;
	int		i;
	char	quote;

	i = start;
	while (arg[i] != '\'' && arg[i] != '"')
		i++;
	quote = arg[i];
	end = skip_quote(arg, start);
	tmp = ft_strcut(start, end, arg);
	if (!tmp)
		return (NULL);
	str = ft_mystrtrim(tmp, quote);
	free(tmp);
	if (!str)
		return (NULL);
	return (str);
}

static int	ft_count_size(char *arg)
{
	int		size;
	char	c;
	int		i;

	i = 0;
	size = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			c = arg[i];
			size++;
			i++;
			while (arg[i] && arg[i] != c)
				i++;
		}
		i++;
	}
	return (size);
}

char	**ft_split_quote(char *arg)
{
	char	**mtx;
	int		size;
	int		i;
	int		tmp;

	tmp = 0;
	i = 0;
	mtx = NULL;
	size = ft_count_size(arg);
	mtx = ft_calloc((size + 1), sizeof(char *));
	if (!mtx)
		return (NULL);
	while (i < size)
	{
		mtx[i] = take_quote_str(arg, tmp);
		if (!mtx[i])
		{
			ft_free_mtx(mtx);
			return (NULL);
		}
		tmp = skip_quote(arg, tmp);
		i++;
	}
	return (mtx);
}
