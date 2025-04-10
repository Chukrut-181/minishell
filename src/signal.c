/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:44:38 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/10 11:09:16 by igchurru         ###   ########.fr       */
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
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	update_exit_status(130);
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

int	get_exit_status(void)
{
	return (g_exit_status);
}

void	setup_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
