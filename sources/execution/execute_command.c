/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:00:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/28 15:44:14 by maheleni         ###   ########.fr       */
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
			perror(NULL);
		free_all_in_child(main, pids);
		exit(errno);
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

int	execute_builtin(t_main *main, t_tokens token, int parent, int open_fds[2])
{
	char	*command;

	command = token.command[0];
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (echo(main, token));
	else if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (cd(main, token));
	else if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (pwd(main, token));
	else if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (export(main, token));
	else if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (unset(main, token));
	else if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (env(main, token));
	else if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
		return (exit_command(main, token, parent, open_fds));
	return (0);
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
	int	exit_code;
	int	original_stdin_stdout[2];

	original_stdin_stdout[0] = dup(STDIN_FILENO);
	original_stdin_stdout[1] = dup(STDOUT_FILENO);
	if (original_stdin_stdout[0] == -1 || original_stdin_stdout[1] == -1)
	{
		perror(NULL);
		main->exit_code = errno;
		return ;
	}
	handle_infile(token, NULL);
	handle_outfile(token, NULL);
	exit_code = execute_builtin(main, token, 1, original_stdin_stdout);
	main->exit_code = exit_code;
	restore_stdin_stdout(main, original_stdin_stdout[0], original_stdin_stdout[1]);
	close(original_stdin_stdout[0]);
	close(original_stdin_stdout[1]);
}
