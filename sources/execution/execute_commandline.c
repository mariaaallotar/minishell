/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commandline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:33:14 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/28 10:27:35 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_tokens token)
{
	char	*command;
	int		str_len;

	if (token.command == NULL)
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

//pipe[0]: read, pipe[1]: write
void	close_pipes_in_parent(int i, int num_of_pipes, int *pipe_left, int *pipe_right)
{
	if (num_of_pipes > 0 && i == 0)			//first command
		close (pipe_right[1]);
	else if (num_of_pipes == 0 && i > 0)	//last command
		close(pipe_left[0]);
	else if (num_of_pipes > 0 && i > 0)		//middle command
	{
		close(pipe_left[0]);
		close(pipe_right[1]);
	}
}

int	*malloc_pids(int amount)
{
	int	*pids;

	pids = malloc ((amount) * sizeof(int));
	if (pids == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	return (pids);
}

int	create_pipe(int pipe_array[2][2])
{
	if (pipe(pipe_array[1]) == -1)
	{
		perror(NULL);
		return (0);
	}
	return (1);
}

int	create_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("Create fork");
	return (pid);
}

void	reassign_pipe_right_to_left(int pipe_array[2][2])
{
	pipe_array[0][0] = pipe_array[1][0];
	pipe_array[0][1] = pipe_array[1][1];
}

int	is_builtin_not_part_of_pipeline(t_tokens *tokens, int num_of_pipes, int i)
{
	if (is_builtin(tokens[i]) && num_of_pipes == 0 && i == 0)
		return (1);
	return (0);
}

void	close_pipes_on_error(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	ignore_sigint(void)
{
	struct sigaction sa_int;
	
	sa_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGINT, &sa_int, NULL);
}

void	activate_sigint(void)
{
	struct sigaction sa_int;
	
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0; // Ensure interrupted system calls are restarted
	sigaction(SIGINT, &sa_int, NULL);
}

int	execute_commandline(t_main *main, t_tokens *tokens)	//does this need to be return int?
{
	int	pipe_array[2][2];
	int	*pids;
	int	num_of_pipes;
	int	i;
	int	status;

	num_of_pipes = main->num_of_pipes;
	i = 0;
	if (tokens[0].command[0] != NULL && is_builtin_not_part_of_pipeline(tokens, num_of_pipes, i))
	{
		execute_builtin_in_parent(main, tokens[i]);
		return (main->exit_code);
	}
	pids = malloc_pids(num_of_pipes + 1);
	if (pids == NULL)
		return (errno);
	while (num_of_pipes >= 0)
	{
		if (i > 0)
			reassign_pipe_right_to_left(pipe_array);
		if (num_of_pipes > 0)
		{
			if (create_pipe(pipe_array) == 0)
			{
				if (i > 0)
					close_pipes_on_error(pipe_array[0]);
				free(pids);
				return (1);
			}
		}
		pids[i] = create_fork();
		if (pids[i] == -1)
		{
			if (i > 0)
				close_pipes_on_error(pipe_array[0]);
			if (num_of_pipes > 0)
				close_pipes_on_error(pipe_array[1]);
			free(pids);
			return (1);
		}
		if (pids[i] == 0)
		{
			if (handle_infile_and_outfile(i, num_of_pipes, pipe_array, tokens[i]) == -1)
			{
				free_all_in_child(main, pids);
				exit(errno);
			}
			execute_child_process(main, tokens[i], pids);
		}
		else
		{
			ignore_sigint();
			close_pipes_in_parent(i, num_of_pipes, pipe_array[0], pipe_array[1]);
		}
		num_of_pipes--;
		i++;
	}
	i = 0;
	status = 0;
	while (i < main->num_of_pipes + 1)
	{
		//TODO make this robust, has to work with signals as well
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			main->exit_code = WEXITSTATUS(status);
		i++;
	}
	activate_sigint();
	free(pids);
	return (main->exit_code);
}
