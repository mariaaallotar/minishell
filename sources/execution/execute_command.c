/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:00:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/21 13:43:11 by eberkowi         ###   ########.fr       */
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

void	path_error_handling(t_main *main, t_tokens token, int *pids)
{
	if (errno == 127)
	{
		if (token.command == NULL || token.command[0] == NULL)
			print_error(" : command not found\n");
		else
		{
			print_error(token.command[0]);
			print_error(": command not found\n");
		}
	}
	else
		perror(token.command[0]);
	free_all_in_child(main, pids);
	if (errno == EACCES || errno == EISDIR)
		exit (126);
	else if (errno == ENOENT)
		exit (127);
	exit (errno);
}

void	execute_command(t_main *main, t_tokens token, int *pids)
{
	char	*path;
	char	**env;

	path = get_path(main, *(token.command), pids);
	if (path == NULL)
		path_error_handling(main, token, pids);
	if (main->env_list == NULL)
		env = NULL;
	else
	{
		env = convert_list_to_array(main->env_list);
		if (env == NULL)
		{
			free_all_in_child(main, pids);
			free(path);
			exit(errno);
		}
	}
	if (execve(path, token.command, env) == -1)
	{
		free_all_in_child(main, pids);
		free(path);
		free(env);
		exit(errno);
	}
}

void	execute_child_process(t_main *main, t_tokens token, int *pids)
{
	int	status;

	activate_signals_for_child();
	if (token.command == NULL || token.command[0] == NULL)
		exit(0);
	if (is_builtin(token))
	{
		status = execute_builtin(main, token, 0, NULL);
		free_all_in_child(main, pids);
		exit(status);
	}
	execute_command(main, token, pids);
}
