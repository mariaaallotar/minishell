/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:07:23 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/04 16:15:49 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_redirect_file(t_tokens token, int type)
{
	t_redirect_node	*node;

	node = token.redirects;
	while (node != NULL)
	{
		if (node->type == type)
			return (1);
		node = node->next;
	}
	return (0);
}

int	redirect_pipe_left(int *pipe_left, t_tokens token)
{
	if (pipe_left != NULL)
	{
		if (has_redirect_file(token, INFILE)
			|| has_redirect_file(token, HEREDOC))
		{
			close(pipe_left[0]);
			return (0);
		}
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

int	redirect_pipe_right(int *pipe_right, t_tokens token)
{
	if (pipe_right != NULL)
	{
		if (has_redirect_file(token, OUTFILE)
			|| has_redirect_file(token, APPEND))
		{
			close(pipe_right[1]);
			return (0);
		}
		if (dup2(pipe_right[1], STDOUT_FILENO) == -1)
		{
			close(pipe_right[0]);
			close(pipe_right[1]);
			perror(NULL);
			return (-1);
		}
		close(pipe_right[1]);
	}
	return (0);
}

int	redirect_pipes(int i, int num_of_pipes, int pipe_array[2][2],
	t_tokens token)
{
	int	return_value;

	return_value = 0;
	if (i > 0)
		return_value = redirect_pipe_left(pipe_array[0], token);
	if (return_value == -1)
	{
		if (num_of_pipes > 0)
		{
			close(pipe_array[1][0]);
			close(pipe_array[1][1]);
		}
		return (-1);
	}
	if (num_of_pipes > 0)
		return_value = redirect_pipe_right(pipe_array[1], token);
	if (return_value == -1)
		return (-1);
	return (0);
}
