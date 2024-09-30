/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commandline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:33:14 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/30 15:32:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_tokens token, int i, int *pipe_left, int *pipe_right)
{
	if (i == 0)
	{
		dup2(pipe_right[1], STDOUT_FILENO);
		close(pipe_right[0]);
		close(pipe_right[1]);
		char *arg[] = {"sleep", "5"};
		printf("Executing command 1\n");
		if (execv(token.command[0], arg) == -1)
		{
			perror("Firs execve error ");
			exit(1);
		}
	}
	if (i == 1)
	{
		dup2(pipe_left[0], STDIN_FILENO);
		close(pipe_left[0]);
		dup2(pipe_right[1], STDOUT_FILENO);
		close(pipe_right[1]);
		char *arg[] = {"cat", NULL};
		printf("Executing command 2\n");
		if (execv(token.command[0], arg) == -1)
		{
			printf("Second execve error\n");
			exit(1);
		}
	}
	dup2(pipe_left[0], STDIN_FILENO);
	close(pipe_left[0]);
	close(pipe_left[1]);
	char *arg[] = {"cat", NULL};
	printf("Executing command 3\n");
	if (execv(token.command[0], arg) == -1)
	{
		printf("Second execve error\n");
		exit(1);
	}
}

int	execute_commandline(t_main *main, t_tokens *tokens)
{
	int	pipe_left[2];
	int	pipe_right[2];
	int	*pids;
	int	num_of_pipes;
	int	i;
	int	status;		//just main->exit_code?

	num_of_pipes = main->num_of_pipes;
	pids = malloc ((num_of_pipes + 1) * sizeof(int));
	i = 0;
	while (num_of_pipes >= 0)
	{
		if (i > 0)
		{
			pipe_left[0] = pipe_right[0];
			pipe_left[1] = pipe_right[1];
		}
		if (num_of_pipes > 0)
		{
			if (pipe(pipe_right) == -1)
			{
				//some error
				printf("Pipe error\n");
			}
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Fork error\n");
			//error(NULL);
		}
		if (pids[i] == 0)
		{
			execute_command(tokens[i], i, pipe_left, pipe_right);
		}
		else
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
		num_of_pipes--;
		i++;
	}
	i = 0;
	while (i < main->num_of_pipes + 1)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	return (status);
}
