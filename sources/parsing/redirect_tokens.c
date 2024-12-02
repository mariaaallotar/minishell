/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:07 by eberkowi          #+#    #+#             */
/*   Updated: 2024/12/02 15:26:14 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_in_or_heredoc(t_main *main, t_tokens **tokens, int cmd_id,
	int *spl_id)
{
	t_redirect_node	*node;

	node = NULL;
	if (!ft_strncmp(main->split_input[*spl_id], "<", 2))
	{
		node = lstnew_redirect_node(main->split_input[*spl_id + 1], INFILE);
		if (!node)
			free_and_exit_node_malloc_failed(main, tokens);
		if (!(*tokens)[cmd_id].redirects)
			(*tokens)[cmd_id].redirects = node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].redirects, node);
		(*spl_id) += 2;
	}
	else if (!ft_strncmp(main->split_input[*spl_id], "<<", 3))
	{
		node = lstnew_redirect_node(main->split_input[*spl_id + 1], HEREDOC);
		if (!node)
			free_and_exit_node_malloc_failed(main, tokens);
		if (!(*tokens)[cmd_id].redirects)
			(*tokens)[cmd_id].redirects = node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].redirects, node);
		(*spl_id) += 2;
	}
}

void	add_out_or_append(t_main *main, t_tokens **tokens, int cmd_id,
	int *spl_id)
{
	t_redirect_node	*node;

	node = NULL;
	if (!ft_strncmp(main->split_input[*spl_id], ">", 2))
	{
		node = lstnew_redirect_node(main->split_input[*spl_id + 1], OUTFILE);
		if (!node)
			free_and_exit_node_malloc_failed(main, tokens);
		if (!(*tokens)[cmd_id].redirects)
			(*tokens)[cmd_id].redirects = node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].redirects, node);
		(*spl_id) += 2;
	}
	else if (!ft_strncmp(main->split_input[*spl_id], ">>", 3))
	{
		node = lstnew_redirect_node(main->split_input[*spl_id + 1], APPEND);
		if (!node)
			free_and_exit_node_malloc_failed(main, tokens);
		if (!(*tokens)[cmd_id].redirects)
			(*tokens)[cmd_id].redirects = node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].redirects, node);
		(*spl_id) += 2;
	}
}

static int	print_syntax_error(t_main *main)
{
	main->exit_code = 2;
	print_error("syntax error near unexpected token\n");
	return (1);
}

int	check_for_redirect_error(t_main *main)
{
	int	i;

	i = 0;
	while (main->split_input[i])
	{
		if (!is_redirect((main->split_input[i])[0]))
		{
			i++;
			continue ;
		}
		if (!(main->split_input[i + 1])
			|| is_redirect((main->split_input[i + 1])[0]))
			return (print_syntax_error(main));
		if (ft_strncmp("<", main->split_input[i], 2)
			&& ft_strncmp(">", main->split_input[i], 2)
			&& ft_strncmp("<<", main->split_input[i], 3)
			&& ft_strncmp(">>", main->split_input[i], 3))
			return (print_syntax_error(main));
		i++;
	}
	return (0);
}
