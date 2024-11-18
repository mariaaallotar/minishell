/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:56:28 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/18 12:54:34 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int signal_received = 0;

// Signal handler for Ctrl-C (SIGINT)
void handle_sigint_readline(int sig)
{
	signal_received = 128 + sig;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	signal_received = 128 + sig;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
}

void	activate_heredoc_signals(void)
{
	struct sigaction	sa_int;

	// sa_int.sa_handler = SIG_DFL;
	sa_int.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGINT, &sa_int, NULL);
}

void	ignore_sigint(void)
{
	struct sigaction sa_int;
	
	sa_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGINT, &sa_int, NULL);
}

void	activate_readline_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint_readline;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	activate_signals_for_child(void)
{
	struct sigaction sa_quit;
	struct sigaction sa_int;

	sa_quit.sa_handler = SIG_DFL;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0; // Ensure interrupted system calls are restarted
    sigaction(SIGQUIT, &sa_quit, NULL);

	sa_int.sa_handler = SIG_DFL;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0; // Ensure interrupted system calls are restarted
    sigaction(SIGINT, &sa_int, NULL);
}
