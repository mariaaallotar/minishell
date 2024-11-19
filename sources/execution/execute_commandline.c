/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commandline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:33:14 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/07 14:35:49 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_tokens token)
{
	char	*command;
	int		str_len;

	if (token.command == NULL || token.command[0] == NULL)
		return (0);
	command = token.command[0];
	str_len = ft_strlen(command);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

void	wait_for_processes(t_main *main, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < main->num_of_pipes + 1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			main->exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			main->exit_code = 128 + WTERMSIG(status);
		i++;
	}
}

int	execute_pipeline(t_main *main, int pipe_array[2][2], int *pids,
	t_tokens *tokens)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = main->num_of_pipes;
	while (pipes >= 0)
	{
		if (prepare_pipes(i, pipes, pipe_array, pids) == -1)
			return (errno);
		if (create_fork(i, pipes, pipe_array, pids) == -1)
			return (errno);
		if (pids[i] == 0)
		{
			if (redirect_pipes(i, pipes, pipe_array) == -1
				|| handle_redirects(tokens[i]) == -1)
			{
				free_all_in_child(main, pids);
				exit(1);
			}
			execute_child_process(main, tokens[i], pids);
		}
		ignore_sigint();
		close_pipes_in_parent(i++, pipes--, pipe_array[0], pipe_array[1]);
	}
	return (0);
}

int	*malloc_pids(t_main *main, int amount)
{
	int	*pids;

	pids = malloc ((amount) * sizeof(int));
	if (pids == NULL)
	{
		perror(NULL);
		main->exit_code = errno;
		return (NULL);
	}
	return (pids);
}

void	execute_commandline(t_main *main, t_tokens *tokens)
{
	int	pipe_array[2][2];
	int	*pids;

	if (execute_builtin_in_parent(main, tokens[0], main->num_of_pipes))
		return ;
	pids = malloc_pids(main, (main->num_of_pipes + 1));
	if (pids == NULL)
		return ;
	if (execute_pipeline(main, pipe_array, pids, tokens) != 0)
		return ;
	wait_for_processes(main, pids);
	activate_readline_signals();
	free(pids);
	return ;
}
