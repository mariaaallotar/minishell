/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:07:23 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/08 12:10:09 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_pipe_left(int *pipe_left)
{
	if (pipe_left != NULL)
	{
		if (dup2(pipe_left[0], STDIN_FILENO) == -1)
		{
			close(pipe_left[0]);
			close(pipe_left[1]);
			perror(NULL);
			return (-1);
		}
		close(pipe_left[0]);
	}
	return (0);
}

int	redirect_pipe_right(int *pipe_right)
{
	if (pipe_right != NULL)
	{
		if (dup2(pipe_right[1], STDOUT_FILENO) == -1)
		{
			close(pipe_right[0]);
			close(pipe_right[1]);
			perror(NULL);
			return (-1);
		}
		close(pipe_right[0]);
		close(pipe_right[1]);
	}
	return (0);
}

int	redirect_pipes(int i, int num_of_pipes, int pipe_array[2][2])
{
	int	return_value;

	if (i == 0)
		return_value = redirect_pipe_left(NULL);
	else
		return_value = redirect_pipe_left(pipe_array[0]);
	if (return_value == -1)
	{
		if (num_of_pipes > 0)
		{
			close(pipe_array[1][0]);
			close(pipe_array[1][1]);
		}
		return (-1);
	}
	if (num_of_pipes == 0)
		return_value = redirect_pipe_right(NULL);
	else
		return_value = redirect_pipe_right(pipe_array[1]);
	if (return_value == -1)
		return (-1);
	return (0);
}
