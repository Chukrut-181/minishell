/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:46:35 by eandres           #+#    #+#             */
/*   Updated: 2024/11/09 08:07:36 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include "../include/minishell.h"

void management_unset(t_mini *mini)
{
    int i, j, k;
    int len;

    if (!mini->env_copy || !mini->full_cmd[1])
    {
        fprintf(stderr, "unset: invalid arguments\n");
        return;
    }
	printf("Entering management_unset\n");
    for (i = 1; mini->full_cmd[i]; i++)
    {
        len = count_val(mini->full_cmd[i]);
        for (j = 0; mini->env_copy[j]; j++)
        {
            if (ft_strncmp(mini->full_cmd[i], mini->env_copy[j], len) == 0 && mini->env_copy[j][len] == '=')
            {
                free(mini->env_copy[j]);
                for (k = j; mini->env_copy[k]; k++)
                {
                    mini->env_copy[k] = mini->env_copy[k + 1];
                }
                break;
            }
        }
    }
	printf("Exiting management_unset\n");
}

int count_val(const char *val)
{
    int i = 0;
    while (val[i] && val[i] != '=')
    {
        i++;
    }
    return i;
}

char **create_env_copy(char **env)
{
    int i, len = 0;
    char **env_copy;

    while (env[len])
        len++;

    env_copy = malloc(sizeof(char *) * (len + 1));
    if (!env_copy)
        return NULL;

    for (i = 0; i < len; i++)
    {
        env_copy[i] = strdup(env[i]);
        if (!env_copy[i])
        {
            while (i > 0)
                free(env_copy[--i]);
            free(env_copy);
            return NULL;
        }
    }
    env_copy[len] = NULL;
    return env_copy;
}

/* void update_env_copy(t_mini *mini)
{
    int i;
    
    if (mini->env_copy)
    {
        for (i = 0; mini->env_copy[i]; i++)
            free(mini->env_copy[i]);
        free(mini->env_copy);
    }
    
    mini->env_copy = create_env_copy(mini->envp);
} */

char *my_getenvp(const char *name, char **env_copy)
{
    int i, len;

    if (!name || !env_copy)
        return (NULL);

    len = strlen(name);
    for (i = 0; env_copy[i]; i++)
    {
        if (strncmp(env_copy[i], name, len) == 0 && env_copy[i][len] == '=')
            return (&env_copy[i][len + 1]);
    }
    return (NULL);
}

int my_setenv(const char *name, const char *value, int overwrite, t_mini *mini)
{
    int i, len;
    char *new_var;

    if (!name || !mini->env_copy)
        return -1;

    len = strlen(name);
    for (i = 0; mini->env_copy[i]; i++)
    {
        if (strncmp(mini->env_copy[i], name, len) == 0 && mini->env_copy[i][len] == '=')
        {
            if (!overwrite)
                return 0;
            free(mini->env_copy[i]);
            break;
        }
    }
    new_var = malloc(strlen(name) + strlen(value) + 2);
    if (!new_var)
        return -1;

    sprintf(new_var, "%s=%s", name, value);
    mini->env_copy[i] = new_var;

    if (!mini->env_copy[i])
        mini->env_copy[i + 1] = NULL;

    return 0;
}
