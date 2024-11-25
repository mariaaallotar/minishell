/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:00:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/25 12:08:04 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	error_print(t_tokens token)
{
	if (is_directory(token.command[0]))
	{
		printf("%s\n", strerror(EISDIR));
		return (126);
	}
	else if (errno == ENOENT)
	{
		printf("%s\n", strerror(ENOENT));
		return (127);
	}
	else
	{
		perror(NULL);
		return (errno);
	}	
}

static void	env_is_null(t_main *main, int *pids, char **path)
{
	free_all_in_child(main, pids);
	free(*path);
	exit(errno);
}

void	execute_command(t_main *main, t_tokens token, int *pids)
{
	char	*path;
	char	**env;
	int		exit_value;

	path = get_path(main, *(token.command), pids);
	if (path == NULL)
		path_error_handling(main, token, pids);
	if (main->env_list == NULL)
		env = NULL;
	else
	{
		env = convert_list_to_array(main->env_list);
		if (env == NULL)
			env_is_null(main, pids, &path);
	}
	if (execve(path, token.command, env) == -1)
	{
		exit_value = error_print(token);
		free_all_in_child(main, pids);
		free(path);
		free(env);
		exit(exit_value);
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
