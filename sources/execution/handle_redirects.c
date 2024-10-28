/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:57:31 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/28 10:44:28 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dup2_outfile(t_tokens token)
{
	t_redirect_node	*node;
	int				outfile;

	node = token.outfiles;
	while (node != NULL)
	{
		if (node != token.outfiles)
			close(outfile);
		if (node->type == OUTFILE)
			outfile = open(node->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (node->type == APPEND)
			outfile = open(node->name, O_WRONLY | O_APPEND | O_CREAT, 0644);		//CHECK THAT IS CORRECT
		if (outfile == -1)
		{
			perror(node->name);
			return (-1);
		}
		node = node->next;
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		perror(NULL);
		return (-1);
	}
	close(outfile);
	return (0);
}

int	handle_outfile(t_tokens token, int* pipe_right)
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
	if (token.outfiles != NULL)
		return (dup2_outfile(token));
	return (0);
}

int	dup2_infile(t_tokens token)
{
	int	infile;
	t_redirect_node	*node;

	node = token.infiles;
	while(node != NULL)
	{
		if (node != token.infiles)
			close(infile);
		infile = open(node->name, O_RDONLY);
		if (infile == -1)
		{
			perror(node->name);
			return (-1);
		}
		node = node->next;
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	close(infile);
	return (0);
}

int	handle_infile(t_tokens token, int* pipe_left)
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
	if (token.infiles != NULL)
		return (dup2_infile(token));
	return (0);
}

int	handle_infile_and_outfile(int i, int num_of_pipes,
	int pipe_array[2][2], t_tokens token)
{
	int	return_value;

	if (i == 0)
		return_value = handle_infile(token, NULL);
	else
		return_value = handle_infile(token, pipe_array[0]);
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
		return_value = handle_outfile(token, NULL);
	else
		return_value = handle_outfile(token, pipe_array[1]);
	if (return_value == -1)
		return (-1);
	return (0);
}
