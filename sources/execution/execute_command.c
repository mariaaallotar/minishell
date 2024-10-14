/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:00:41 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/14 15:15:11 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_main *main, t_tokens token)
{
	char	*path;
	char	**env;

	path = get_path(main, token.command);
	if (path == NULL)
	{
		dup2(STDERR_FILENO, 1);
		if (errno == 127)
			printf("Command not found: %s\n", token.command[0]);
		else
			perror("Error in getting path to command:");
		//maria free everything in child
		exit(1);
	}
	env = convert_list_to_array(main->env_list);
	if (execve(path, token.command, env) == -1)
	{
		//maria free everything in child
		free(env);
		free(path);
		exit(1);
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
		//maria free everyhting in child
		exit(status);
	}
	execute_command(main, token);
	//could also execve error be handled here?
	//so same frees for both builin normal exeecution and for failed execve
	// minus maybe path?
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
		perror(NULL);
		//maria free everything everything?? remember pids
		//exit minishell (this is only run in parent)
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
		//do not exit, because we are in parent
		//maria free	do we even free here, why not just return and free normally before next prompt?
	}
	handle_infile(token, NULL);
	handle_outfile(token, NULL);
	execute_builtin(main, token);
	restore_stdin_stdout(main, original_stdin, original_stdout);
	close(original_stdin);
	close(original_stdout);
}
