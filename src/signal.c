/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:44:38 by igchurru          #+#    #+#             */
/*   Updated: 2024/12/23 08:20:47 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * ft_handle_sigint - Signal handler for SIGINT (Ctrl-C).
 *
 * This function is invoked when the SIGINT signal is received, that is
 * when the user presses Ctrl-Option-C. It performs the following actions:
 * 
 * 1. Prints a newline to the terminal to move to a new line.
 * 2. Clears the current input line in the Readline buffer.
 * 3. Moves the cursor to the start of a new prompt line.
 * 4. Redisplays the shell prompt, ensuring a clean user experience.
 * 
 * By handling SIGINT in this way, the shell remains running, and the
 * user is presented with a new prompt without terminating the shell.
 *
 * @param signal: The signal number (expected to be SIGINT).
 */
void	ft_handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
