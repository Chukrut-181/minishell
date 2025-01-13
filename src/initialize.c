/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urdudilz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:39:10 by igchurru          #+#    #+#             */
/*   Updated: 2025/01/13 17:41:47 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * ft_locate_pipe - Checks for a pipe symbol (`|`) in the command array.
 *
 * This function scans the given command array starting from the second element
 * (index 1) to locate a pipe (`|`). If it is found, it updates the provided
 * index to point to the position just after the pipe and returns `1`.
 * If no pipe is found, it returns `0`.
 *
 * **array: A null-terminated array of command strings.
 * *index: A pointer to the index of the current position in the array.
 *         This value is updated to point past the pipe if one is found.
 *
 * Return:
 * - `1` if a pipe is found.
 * - `0` if no pipe is found.
 *
 * Workflow:
 * 1. Start scanning the array from index 1 (ignoring the first element).
 * 2. Check if each element matches the pipe symbol (`|`).
 * 3. If a pipe is found:
 *    - Update `*index` to move past the pipe and subsequent commands.
 *    - Return `1` to indicate success.
 * 4. If the loop completes without finding a pipe, return `0`.
 */
int	ft_locate_pipe(char **array, int *index)
{
	int	i;

	i = 1;
	while (array && array[i])
	{
		if (!ft_strcmp(array[i], "|"))
		{
			*index = *index + i + 1;
			return (1);
		}
		else
			i++;
	}
	return (0);
}

/*
 * ft_get_full_command - Extracts the full command from a command array.
 *
 * This function processes a command array to extract the command
 * and its arguments,excluding redirection operators (`<`, `>`)
 * and their associated files. The extracted command is stored in the
 * `full_cmd` field of the `t_mini` structure as a dynamically allocated
 * array of strings.
 *
 * *node: A pointer to the `t_mini` structure where the command will be stored.
 * **array: A null-terminated array of command strings that may include
 * redirection operators.
 *
 * Workflow:
 * 1. Skip input redirection (`<`) if it appears at the beginning of the array:
 *    - Increment the index `k` to bypass the operator and its associated file.
 * 2. Count the number of valid command arguments:
 *    - Stop counting at a pipe (`|`) or output redirection (`>`).
 * 3. Allocate memory for the `full_cmd` field in the `node` to store the
 *    command arguments.
 * 4. Populate the `full_cmd` array:
 *    - Copy strings from the `array` into `full_cmd`, starting from the
 *      calculated position.
 *    - Terminate the array with a NULL pointer.
 *
 * Note:
 * - Does not handle syntax validation for incorrect command formatting.
 */
void	ft_get_full_command(t_mini *node, char **array)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	if (array && array[k] && *array[k] == '<')
		k += 2;
	i = 0;
	while (array && array[k] && (*array[k] != '|' && *array[k] != '>'))
	{
		k++;
		i++;
	}
	node->full_cmd = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		node->full_cmd[j] = ft_strdup(array[k - i]);
		j++;
		k++;
	}
	node->full_cmd[j] = NULL;
}

/*
 * ft_check_redirections - Checks and handles input/output redirections
 	in a command array.
 *
 * This function processes the provided command array to identify input (`<`)
 * and output (`>`) redirections. It opens the appropriate files and updates
 * the `infile` and `outfile` fields with the corresponding file descriptors.
 *
 * **node: A pointer to the current `t_mini` structure being processed.
 * **array: A null-terminated array of command strings,
 *			including potential redirection operators.
 *
 * Workflow:
 * 1. Initialize an index `i` to iterate through the array.
 * 2. Check for an input redirection (`<`) at the start of the array:
 *    - If found, open the file specified after `<` in read-only mode.
 *    - Update the `infile` field of the `node` with the resulting fd.
 * 3. Iterate through the array until:
 *    - A pipe (`|`) char is encountered, signaling the end of the command.
 *    - The end of the array is reached.
 * 4. Determine if an output redirection (`>`) is present at the end
 *    of the array:
 *    - If found, open the file specified after `>` in write-only mode.
 *    - Create the file if it does not exist or truncate it if it does.
 *    - Update the `outfile` field of the `node` with the resulting fd.
 * 5. If no redirection is found, the file descriptors remain unchanged.
 *
 * Notes:
 * - The function does not validate the correctness of the redirection syntax.
 * - If an invalid file is specified for redirection, `open` will return `-1`.
 *   which may require additional error handling elsewhere in the program.
 * - Input and output redirections are mutually exclusive in this implementation.
 */
void	ft_check_redirections(t_mini *node, char **array)
{
	int	i;
	int	len;

	i = 0;
	if (!array || !array[i])
		return ;
	if (array && array[i] && *array[i] == '<')
		node->infile = open(array[i + 1], O_RDONLY);
	while (array[i])
	{
		if (*array[i] == '|')
			return ;
		else
			i++;
	}
	len = ft_arraylen(array);
	if (array && len - 3 >= 0 && *array[len - 3] == '>' && *array[len - 2] == '>')
	{
		node->outfile = open(array[len - 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	else if (array && len - 2 >= 0 && *array[len - 2] == '>')
	{
		node->outfile = open(array[len - 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
}

/*
 * ft_initialize_mini_node - Allocates and initializes a new `t_mini` node.
 *
 * This function creates a new `t_mini` structure, initializing its fields
 * to default values and copying the provided environment variables into it.
 * The new node is ready to be populated with command-specific information.
 *
 * **envp: The environment variables passed to the program.
 *
 * Return: A pointer to the newly allocated and initialized `t_mini` node,
 *         or `NULL` if memory allocation fails.
 *
 * Workflow:
 * 1. Allocate memory for a new `t_mini` structure using `malloc`.
 * 2. If allocation fails, return `NULL`.
 * 3. Use `ft_bzero` to zero out all fields of the structure,
 *    ensuring a clean slate.
 * 4. Copy the environment variables into the node using `ft_get_full_envp`.
 * 5. Set default values for the file descriptors:
 * 6. Initialize pointers to `NULL`:
 *    - `next` is set to `NULL` to indicate the end of the linked list.
 *    - `command` is set to `NULL` as no command is associated yet.
 * 7. Return the pointer to the new node.
 */
t_mini	*ft_initialize_mini_node(char **envp)
{
	t_mini	*new_node;

	new_node = malloc(sizeof(t_mini));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_mini));
	ft_get_full_envp(new_node, envp);
	new_node->infile = STDIN_FILENO;
	new_node->outfile = STDOUT_FILENO;
	new_node->next = NULL;
	new_node->command = NULL;
	new_node->full_cmd = NULL;
	new_node->full_path = NULL;
	return (new_node);
}

/*
 * ft_create_structure - Creates a linked list structure representing
 * commands and their attributes.
 *
 * This function processes a parsed input array of commands and operators,
 * creating a linked list of `t_mini` structures. Each structure holds 
 * information about a single command, including its arguments, associated
 * environment variables, execution path, and whether it is a built-in command.
 * The list is terminated when no more pipes are found in the input array.
 *
 * **array: Array of commands and operators, parsed from the user input.
 * **envp: The environment variables passed to the program.
 *
 * Return: A pointer to the head of the linked list of `t_mini` structures.
 *
 * Workflow:
 * 1. Initialize the first node using `ft_initialize_mini_node`.
 * 2. For each node:
 *    - Check for redirections in the command with `ft_check_redirections`.
 *    - Populate the node with the full command using `ft_get_full_command`.
 *    - Determine if the command is a built-in using `ft_check_if_builtin`.
 *    - Find the executable path for the command using `ft_get_path`.
 *    - Check for the presence of a pipe operator and update the
 *      `index` appropriately.
 * 3. If a pipe operator is found, allocate the next node, link it
 *    to the current one, and continue.
 * 4. When no more pipes are found, terminate the loop and return
 *    the head of the list.
 *
 * Notes:
 * - Each node is a command separated by a pipe (`|`) from the next command.
 * - Redirections (e.g., `<`, `>`, `>>`) are handled per node during processing.
 * - The function assumes `array` is properly formatted and null-terminated.
 */
t_mini *ft_create_structure(t_mini *mini, char **array, char **envp)
{
	t_mini *head;
	t_mini *next_node;
	int     index;

	head = mini;
	index = 0;
	while (1)
	{
		ft_check_redirections(mini, &array[index]);
		ft_get_full_command(mini, &array[index]);
		ft_check_if_builtin(mini);
		ft_get_path(mini);
		if (!ft_locate_pipe(&array[index], &index))
			break;
		next_node = ft_initialize_mini_node(envp);
		mini->next = next_node;
		mini = next_node;
	}
	return (head);
}
