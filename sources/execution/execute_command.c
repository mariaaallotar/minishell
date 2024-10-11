/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:00:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/11 10:33:16 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_main *main, t_tokens token)
{
	char	*path;
	// char	**env;

	path = get_path(main, token.command);
	if (path == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		if (errno == 127)
			printf("Command not found: %s\n", token.command[0]);
		else
			perror("Error in getting path to command:");
		exit(1);
	}

	//make sure that in- and outfiles are correct at this point and pipes closed

	// env = transform_to_string_array(main->env_list);		//TODO
	// if (execve(path, token.command, env) == -1)
	// {
	// 	free(path);
	// 	//error
	// }

	//this is just for testing without env
	if (execv(path, token.command) == -1)
	{
		//make sure that path is always allocated by execution
		printf("Execv error on command %s\n", token.command[0]);
		free(path);
		//error
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
	{
		// return (cd());
		printf("Executing cd\n");
	}
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

void	execute_child_process(t_main *main, t_tokens token)
{
	int	status;

	if (is_builtin(token))
	{
		status = execute_builtin(main, token);
		exit(status);
	}
	execute_command(main, token);
}

void	execute_builtin_in_parent(t_main *main, t_tokens token)
{
	int original_stdin;
    int original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	handle_infile(token, NULL);
	handle_outfile(token, NULL);
	execute_builtin(main, token);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
