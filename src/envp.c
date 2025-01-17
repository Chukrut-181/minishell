/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:09:32 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/17 11:02:37 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * ft_get_full_envp - Allocates and initializes a copy of the env variables.
 * @node: Pointer to the `t_mini` struct where the env vars will be stored.
 * @envp: Double-pointer to the original env vars passed to the program.
 * 
 * Description:
 * This function creates a full copy of the env vars and stores them in 
 * the `envp` field of the `t_mini` struct. It counts the number of env vars,
 * allocates memory for an array of strings, and iterates over each env var, 
 * delegating the copying process to the `ft_get_single_envp` function.
 * A pointer to the original `envp` array is stored in the `env_copy` field.
 * 
 * Steps:
 * 1. Counts the number of strings in the `envp` array (`env_count`).
 * 2. Allocates memory for an array of pointers.
 * 3. Checks if memory allocation succeeded; if not, logs an error
 *    using `perror` and exits.
 * 4. Iterates through `envp`, invoking `ft_get_single_envp`
 *    to duplicate each string.
 * 5. Sets the last pointer in the allocated array to `NULL`.
 * 6. Stores a pointer to the original `envp` in the
 *    `env_copy` field of `node`.
 */
/* void	ft_get_full_envp(t_mini *node, char **envp)
{
	int	i;
	int	env_count;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	node->envp = malloc(sizeof(char *) * (env_count + 1));
	if (!node->envp)
	{
		perror("malloc failed for env_vars\n");
		return ;
	}
	i = 0;
	while (i < env_count)
	{
		ft_get_single_envp(node, i, envp);
		i++;
	}
	node->envp[env_count] = NULL;
	node->env_copy = envp;
} */

void ft_get_full_envp(t_mini *mini, char **envp)
{
    int count = 0;
    
    // Contamos cuántas variables de entorno hay
    while (envp[count] != NULL) {
        count++;
    }
    // Asignamos memoria para el arreglo de punteros
    mini->env_copy = malloc((count + 1) * sizeof(char *));  // +1 para el NULL al final
    if (mini->env_copy == NULL) {
        perror("Error al asignar memoria para mini->env_copy");
        exit(1);
    }

    // Copiamos cada variable de entorno
    for (int i = 0; i < count; i++)
	{
        mini->env_copy[i] = ft_strdup(envp[i]);  // Copia cada cadena
        if (mini->env_copy[i] == NULL) 
		{
            perror("Error al copiar una variable de entorno");
            exit(1);
        }
    }

    // Aseguramos que el arreglo termina con un puntero NULL
    mini->env_copy[count] = NULL;
}

/*
 * ft_get_single_envp - Duplicates a single env var string.
 * @node: Pointer to the `t_mini` structure where the string will be stored.
 * @i: Index of the environment variable to duplicate.
 * @envp: Double-pointer to the original environment variables.
 * 
 * Description:
 * This function duplicates the `i`th string in the `envp` array and stores
 * it in the `node->envp` array. It first calculates the length of the string,
 * then allocates memory for it (including space for the null terminator).
 * After verifying the allocation, it copies the content of the string
 * using `ft_strlcpy`.
 * 
 * Steps:
 * 1. Calculates the length of the `i`th env var string using `ft_strlen`.
 * 2. Allocates memory for the string (length + 1 for null terminator).
 * 3. If allocation fails, logs an error using `perror` and frees
 *    the already allocated array.
 * 4. Copies the string content from `envp[i]` to the newly allocated memory.
 */
/* void	ft_get_single_envp(t_mini *node, int i, char **envp)
{
	int	len;

	len = ft_strlen(envp[i]);
	node->envp[i] = malloc(sizeof(char) * (len + 1));
	if (!node->envp[i])
	{
		perror("malloc failed for env_vars[i]\n");
		ft_free_array(node->envp);
		return ;
	}
	ft_strlcpy(node->envp[i], envp[i], len + 1);
} */
