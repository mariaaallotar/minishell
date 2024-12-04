/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:43:29 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/04 16:21:26 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes_in_parent(int i, int num_of_pipes, int *pipe_left,
	int *pipe_right)
{
	if (num_of_pipes > 0 && i == 0)
		close (pipe_right[1]);
	else if (num_of_pipes == 0 && i > 0)
		close(pipe_left[0]);
	else if (num_of_pipes > 0 && i > 0)
	{
		close(pipe_left[0]);
		close(pipe_right[1]);
	}
}

void	close_pipes_on_error(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

int	create_fork(int i, int num_of_pipes, int pipe_array[2][2], int *pids)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		if (i > 0)
			close_pipes_on_error(pipe_array[0]);
		if (num_of_pipes > 0)
			close_pipes_on_error(pipe_array[1]);
		while (--i >= 0)
			kill(pids[i], SIGINT);
		free(pids);
		return (-1);
	}
	pids[i] = pid;
	return (pid);
}

void	reassign_pipe_right_to_left(int pipe_array[2][2])
{
	pipe_array[0][0] = pipe_array[1][0];
	pipe_array[0][1] = pipe_array[1][1];
}

int	prepare_pipes(int i, int num_of_pipes, int pipe_array[2][2], int *pids)
{
	if (i > 0)
		reassign_pipe_right_to_left(pipe_array);
	if (num_of_pipes > 0)
	{
		if (pipe(pipe_array[1]) == -1)
		{
			perror(NULL);
			if (i > 0)
				close_pipes_on_error(pipe_array[0]);
			free(pids);
			return (-1);
		}
	}
	return (1);
}
