/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:06:40 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/28 14:41:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	open_outfile(t_redirect_node *node, int *infile)
{
	int	outfile;

	outfile = -1;
	if (node->type == OUTFILE)
		outfile = open(node->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (node->type == APPEND)
		outfile = open(node->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (outfile == -1)
	{
		perror(node->name);
		if (*infile != -1)
			close (*infile);
		return (-1);
	}
	return (outfile);
}

int	open_file(int *infile, int *outfile, t_redirect_node *node)
{
	if (node->type == INFILE || node->type == HEREDOC)
	{
		if (*infile != -1)
			close(*infile);
		if (node->name == NULL)
		{
			print_error("ambiguous redirect\n");
			return (-1);
		}
		*infile = open_infile(node);
		if (*infile == -1)
		{
			if (*outfile != -1)
				close(*outfile);
			return (-1);
		}
		return (0);
	}
	if (*outfile != -1)
		close(*outfile);
	*outfile = open_outfile(node, infile);
	if (*outfile == -1)
		return (-1);
	return (0);
}

int	dup2_redirects(int infile, int outfile)
{
	if (infile != -1)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
		{
			perror(NULL);
			close(infile);
			if (outfile != -1)
				close(outfile);
			return (-1);
		}
		close (infile);
	}
	if (outfile != -1)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			close(outfile);
			return (-1);
		}
		close (outfile);
	}
	return (0);
}

int	handle_redirects(t_tokens token)
{
	int				infile;
	int				outfile;
	t_redirect_node	*node;

	infile = -1;
	outfile = -1;
	node = token.redirects;
	while (node != NULL)
	{
		if (open_file(&infile, &outfile, node) == -1)
			return (-1);
		node = node->next;
	}
	if (dup2_redirects(infile, outfile) == -1)
		return (-1);
	return (0);
}
