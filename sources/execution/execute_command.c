/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:00:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/06 11:09:16 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all_in_parent(t_main *main)
{
	rl_clear_history();
	remove_heredocs(main, main->tokens);
	free_and_null_split_input(main);
	free_token_commands(main, main->tokens);
	free_token_redirects(main, main->tokens);
	free(*(main->tokens));
	free_environment(&(main->env_list));
}

void	free_all_in_child(t_main *main, int *pids)
{
	free_all_in_parent(main);
	free(pids);
}


void	execute_command(t_main *main, t_tokens token, int *pids)
{
	char	*path;
	char	**env;

	path = get_path(main, token.command, pids);
	if (path == NULL)
	{
		dup2(STDERR_FILENO, 1);
		if (errno == 127)
		{
			if (token.command == NULL || token.command[0] == NULL)
				printf(" : command not found\n");
			else
				printf("%s: command not found\n", token.command[0]);
		}
		else
			perror(token.command[0]);
		free_all_in_child(main, pids);
		if (errno == EISDIR)
			exit(126);
		exit (errno);
	}
	env = convert_list_to_array(main->env_list);
	if (env == NULL)
	{
		free_all_in_child(main, pids);
		free(path);
		exit(errno);
	}
	if (execve(path, token.command, env) == -1)
	{
		free_all_in_child(main, pids);
		free(path);
		free(env);
		exit(errno);
	}
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

void	execute_child_process(t_main *main, t_tokens token, int *pids)
{
	int	status;

	activate_signals_for_child();
	if (is_builtin(token))
	{
		status = execute_builtin(main, token, 0, NULL);
		free_all_in_child(main, pids);
		exit(status);
	}
	execute_command(main, token, pids);
}
