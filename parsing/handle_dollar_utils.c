#include "../mini.h"

static int	ft_len_dollar(char *old, char *value)
{
	int	i;
	int	len_1;
	int	len_2;
	int	counter;

	i = 0;
	counter = 0;
	len_1 = 0;
	len_2 = ft_strlen((const char *)value);
	while (old[i])
	{
		if (old[i] == '$' && counter == 0)
		{
			i++;
			counter++;
			while (old[i] && old[i] != '$' &&ft_isspace(old[i]) != 0)
				i++;
		}
		else
		{
			len_1++;
			i++;
		}
	}
	return (len_1 + len_2);
}

static int	last_part_str(int i, char *old)
{
	int	new_i;

	if (old[i] == '$')
		i++;
	while ((old[i] && ft_isalnum(old[i])) || old[i] == '_')
		i++;
	new_i = i;
	return (new_i);
}

static char *ft_new_str(char *old,  char *value, int start)
{
	char	*new;
	int		len;
	int		i;
	int		c;
	int		j;

	len = ft_len_dollar(old, value);
	new = ft_calloc((len + 1), sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < start)
		new[i] = old[i];
	c = last_part_str(i, old);
	j = 0;
	while (value[j])
	{
		new[i] = value[j];
		i++;
		j++;
	}
	while (old[c])
	{
		new[i] = old[c];
		i++;
		c++;
	}
	return (new);
}

void	ft_join_dollar(t_token *curr, int *i, char *value)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_strdup((const char *)curr->arg);
	if (!tmp)
	{
		(*i) = -1;
		return ;
	}
	free(curr->arg);
	curr->arg = ft_new_str(tmp, value, (*i));
	if (!curr->arg)
	{
		(*i) = -1;
		return ;
	}
	while (curr->arg[(*i)] && curr->arg[(*i)] == value[j])
	{
		(*i)++;
		j++;
	}
	free(tmp);
}

static char	*cut_env_value(char	*env)
{
	char	*new;
	int		start;
	int		end;

	start = 0;
	while (env[start] != '=')
		start++;
	start++;
	end = start;
	while (env[end])
		end++;
	new = ft_strcut(start, end, env);
	if (!new)
		return (NULL);
	return (new);
}

char	*replace_value(char *value_rp,t_mini *mini)
{
	char	*new;
	int		len;
	t_env	*curr;

	len = ft_strlen((const char *)value_rp);
	if (value_rp[0] == '?')
	{
		new = ft_itoa(mini->exit_code);
		return (new);
	}
	curr = mini->env;
	while (curr)
	{
		if (ft_strncmp((const char *)value_rp, (const char *)curr->value, len) == 0)
		{
			new = cut_env_value(curr->value);
			if (!new)
				return (NULL);
			break ;
		}
		curr = curr->next;
	}
	if (curr == NULL)
		new = ft_strdup("");
	return (new);	
}
