/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:00:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/15 15:42:54 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all_in_child(t_main *main, int *pids)
{
	rl_clear_history();
	free_and_null_split_input(main);
	free_token_commands(main, main->tokens);
	free_token_redirects(main, main->tokens);
	free(*(main->tokens));
	free_environment(&(main->env_list));
	free(pids);
}

void	free_all_in_parent(t_main *main)
{
	rl_clear_history();
	free_and_null_split_input(main);
	free_token_commands(main, main->tokens);
	free_token_redirects(main, main->tokens);
	free(*(main->tokens));
	free_environment(&(main->env_list));
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
				printf("Command not found\n");
			else
				printf("Command not found: %s\n", token.command[0]);
		}
		else
			perror("Error in getting path to command");
		free_all_in_child(main, pids);
		exit(errno);
	}
	env = convert_list_to_array(main->env_list);
	if (execve(path, token.command, env) == -1)
	{
		free_all_in_child(main, pids);
		free(path);
		free(env);
		exit(errno);
	}
}

int	execute_builtin(t_main *main, t_tokens token)
{
	char	*command;
	int		cmd_len;

	(void)main;
	command = token.command[0];
	cmd_len = ft_strlen(command);
	if (ft_strncmp(command, "echo\0", cmd_len) == 0)
		return (echo(main, token));
	else if (ft_strncmp(command, "cd\0", cmd_len) == 0)
		return (cd(main, token));
	else if (ft_strncmp(command, "pwd\0", cmd_len) == 0)
		return (pwd(main, token));
	else if (ft_strncmp(command, "export\0", cmd_len) == 0)
		return (export(main, token));
	else if (ft_strncmp(command, "unset\0", cmd_len) == 0)
		return (unset(main, token));
	else if (ft_strncmp(command, "env\0", cmd_len) == 0)
		return (env(main, token));
	else if (ft_strncmp(command, "exit\0", cmd_len) == 0)
	{
		printf("Executing exit\n");
		//return(exit_command(main));
		return (0);
	}
	return (0);
}

void	execute_child_process(t_main *main, t_tokens token, int *pids)
{
	int	status;

	if (is_builtin(token))
	{
		status = execute_builtin(main, token);
		free_all_in_child(main, pids);
		exit(status);
	}
	execute_command(main, token, pids);
}

void	restore_stdin_stdout(t_main *main, int original_stdin,
	int original_stdout)
{
	(void) main;
	if (dup2(original_stdin, STDIN_FILENO) == -1
		|| dup2(original_stdout, STDOUT_FILENO) == -1)
	{
		close(original_stdin);
		close(original_stdout);
		perror("Exiting minishell because of: ");
		free_all_in_parent(main);
		exit(1);
	}
}

void	execute_builtin_in_parent(t_main *main, t_tokens token)
{
	int original_stdin;
    int original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdin == -1 || original_stdout == -1)
	{
		perror(NULL);
		main->exit_code = errno;
		return ;
	}
	handle_infile(token, NULL);
	handle_outfile(token, NULL);
	execute_builtin(main, token);
	restore_stdin_stdout(main, original_stdin, original_stdout);
	close(original_stdin);
	close(original_stdout);
}
