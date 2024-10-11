/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commandline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:33:14 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/11 10:33:52 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_tokens token)
{
	char	*command;
	int		str_len;

	if (token.command == NULL)
	{
		printf("Command NULL\n");
		return (0);
	}
	command = token.command[0];
	str_len = ft_strlen(command);
	if (ft_strncmp(command, "echo\0", str_len) == 0)
		return (1);
	else if (ft_strncmp(command, "cd\0", str_len) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd\0", str_len) == 0)
		return (1);
	else if (ft_strncmp(command, "export\0", str_len) == 0)
		return (1);
	else if (ft_strncmp(command, "unset\0", str_len) == 0)
		return (1);
	else if (ft_strncmp(command, "env\0", str_len) == 0)
		return (1);
	else if (ft_strncmp(command, "exit\0", str_len) == 0)
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
		perror("In malloc_pids");
		exit(1);
	}
	return (pids);
}

void	create_pipe(int pipe_array[2][2])
{
	if (pipe(pipe_array[1]) == -1)
	{
		//some error
		printf("In create_pipe");
		exit(1);
	}
}

int	create_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("In create_fork");
		//error(NULL);
		exit(1);
	}
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

int	execute_commandline(t_main *main, t_tokens *tokens)
{
	int	pipe_array[2][2];
	int	*pids;
	int	num_of_pipes;
	int	i;
	int	status;

	num_of_pipes = main->num_of_pipes;
	pids = malloc_pids(num_of_pipes + 1);
	i = 0;
	while (num_of_pipes >= 0)
	{
		if (is_builtin_not_part_of_pipeline(tokens, num_of_pipes, i))
			execute_builtin_in_parent(main, tokens[i]);
		else
		{
			if (i > 0)
				reassign_pipe_right_to_left(pipe_array);
			if (num_of_pipes > 0)
				create_pipe(pipe_array);
			pids[i] = create_fork();
			if (pids[i] == 0)
			{
				handle_infile_and_outfile(i, num_of_pipes, pipe_array, tokens[i]);
				execute_child_process(main, tokens[i]);
			}
			else
				close_pipes_in_parent(i, num_of_pipes, pipe_array[0], pipe_array[1]);
		}
		num_of_pipes--;
		i++;
	}
	i = 0;
	while (i < main->num_of_pipes + 1)
	{
		//TODO make this robust, has to work with signals as well
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			main->exit_code = WEXITSTATUS(status);
		i++;
	}
	free(pids);
	return (main->exit_code);	//correct?
}
