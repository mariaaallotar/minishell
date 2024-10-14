/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:57:31 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/14 14:13:40 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup2_outfile(t_tokens token)
{
	int				outfile;
	t_redirect_node	*node;

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
			//maria free everything in child
			exit(1);
		}
		node = node->next;
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		perror(NULL);
		//maria free everything in child
		exit(1);
	}
	close(outfile);
}

void	handle_outfile(t_tokens token, int* pipe_right)
{
	if (pipe_right != NULL)
	{
		if (dup2(pipe_right[1], STDOUT_FILENO) == -1)
		{
			close(pipe_right[0]);
			close(pipe_right[1]);
			perror(NULL);
			//maria free everything in child
			exit(1);
		}
		close(pipe_right[0]);
		close(pipe_right[1]);
	}
	if (token.outfiles != NULL)
		dup2_outfile(token);
}

void	dup2_infile(t_tokens token)
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
			//maria free everything in child
			exit(1);
		}
		node = node->next;
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror(NULL);
		//maria free everything in child
		exit(1);
	}
	close(infile);
}

void	handle_infile(t_tokens token, int* pipe_left)
{
	if (pipe_left != NULL)
	{
		if (dup2(pipe_left[0], STDIN_FILENO) == -1)
		{
			close(pipe_left[0]);
			close(pipe_left[1]);
			perror(NULL);
			//maria free everything in child
			exit(1);
		}
		close(pipe_left[0]);
		close(pipe_left[1]);
	}
	if (token.infiles != NULL)
		dup2_infile(token);
}

void	handle_infile_and_outfile(int i, int num_of_pipes,
	int pipe_array[2][2], t_tokens token)
{
	if (i == 0 && num_of_pipes == 0)
	{
		handle_infile(token, NULL);
		handle_outfile(token, NULL);
	}
	else if (i > 0 && num_of_pipes == 0)
	{
		handle_infile(token, pipe_array[0]);
		handle_outfile(token, NULL);
	}
	else if (i == 0)
	{
		handle_infile(token, NULL);
		handle_outfile(token, pipe_array[1]);
	}
	else
	{
		handle_infile(token, pipe_array[0]);
		handle_outfile(token, pipe_array[1]);
	}
}
