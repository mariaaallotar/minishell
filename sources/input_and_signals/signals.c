/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:56:28 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/27 11:32:37 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Signal handler for Ctrl-C (SIGINT)
void handle_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_handlers()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	// Set up the SIGINT handler (Ctrl-C)
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGQUIT, &sa_quit, NULL);
}
