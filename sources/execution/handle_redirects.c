/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:06:40 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:01 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirect_pipe_left(int* pipe_left)
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

int redirect_pipe_right(int* pipe_right)
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

int redirect_pipes(int i, int num_of_pipes, int pipe_array[2][2])
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

int	open_infile(t_redirect_node	*node)
{
	int	infile;

	infile = open(node->name, O_RDONLY);
	if (infile == -1)
	{
		perror(node->name);
		return (-1);
	}
	return (infile);
}

int	open_outfile(t_redirect_node *node)
{
	int	outfile;

	outfile = -1;
	if (node->type == OUTFILE)
		outfile = open(node->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (node->type == APPEND)
		outfile = open(node->name, O_WRONLY | O_APPEND | O_CREAT, 0644);		//CHECK THAT IS CORRECT
	if (outfile == -1)
	{
		perror(node->name);
		return (-1);
	}
	return (outfile);
}

int	dup2_file(int file, int std_fileno)
{
	if (file != -1 && dup2(file, std_fileno) == -1)
	{
		close(file);
		perror(NULL);
		return (-1);
	}
	close(file);
	return (0);
}

int	handle_redirects(t_tokens token)
{
	int	infile;
	int	outfile;
	t_redirect_node	*node;

	infile = -1;
	outfile = -1;
	node = token.redirects;
	while (node != NULL)
	{
		if (node->type == INFILE || node->type == HEREDOC)
		{
			if (infile != -1)
				close(infile);
			infile = open_infile(node);
			if (infile == -1)
			{
				if (outfile != -1)
					close(outfile);
				return (-1);
			}
		}
		else if (node->type == OUTFILE || node->type == APPEND)
		{
			if (outfile != -1)
				close(outfile);
			outfile = open_outfile(node);
			if (outfile == -1)
				return (-1);
		}
		node = node->next;
	}
	if (dup2_file(infile, STDIN_FILENO) == -1)
	{
		if (outfile != -1)
			close(outfile);
		return (-1);
	}
	if (dup2_file(outfile, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}