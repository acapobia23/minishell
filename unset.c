/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:17:45 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/20 22:19:06 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int check_var_name(char *str)
{
    int i;
    
    if (!str || !str[0])
        return (0);
    if (ft_isdigit(str[0]))
        return (0);
    i = 0;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) || str[i] == '_')
            return (0);
        i++;
    }
    return (1);
}

int remove_env_var(t_env **env, char *arg)
{
    t_env *current;
    t_env *prev;

    if (!env || !(*env))
        return (1);
    current = *env;
    prev = NULL;
    while (current)
    {
        if (ft_strcmp_until(current->value, arg, '=') == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(current->value);
            free(current);
            return (0);
        }
        prev = current;
        current = current->next;
    }
    return (1);
}

int unset_builtin(t_mini *mini)
{
    if (!mini->cmd->arg || !mini->cmd->arg[0])
        return (0);
    if (!mini->env)
        return (1);
    while (mini->cmd->arg)
    {
        if (!check_var_name)
        {
            printf("unset: '%s' : not a valid identifier\n", mini->cmd->(*arg));
            return (1);
        }
        else
            remove_env_var(mini->env, mini->cmd->(*arg));
    }
    return (0);
}
