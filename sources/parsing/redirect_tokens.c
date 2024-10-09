/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:07 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/08 15:05:05 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redirect_node	*lstnew_redirect_node(char *name, int type)
{
	t_redirect_node	*new_node;

	new_node = (t_redirect_node *)malloc(sizeof(t_redirect_node));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

static t_redirect_node	*lstlast_redirect_node(t_redirect_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	lstadd_back_redirect_node(t_redirect_node **lst, t_redirect_node *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		lstlast_redirect_node(*lst)->next = new;
	else
		*lst = new;
}

void add_in_or_heredoc(t_main *main, t_tokens **tokens, int cmd_id, int *spl_id)
{
	t_redirect_node *new_node;
	
	if (!ft_strncmp(main->split_input[*spl_id], "<", 2))
	{
		new_node = lstnew_redirect_node(main->split_input[*spl_id + 1], INFILE);
		// ADD MALLOC CHECK
		if (!(*tokens)[cmd_id].infiles)
			(*tokens)[cmd_id].infiles = new_node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].infiles, new_node);
		(*spl_id) += 2;
	}
	else if (!ft_strncmp(main->split_input[*spl_id], "<<", 3))
	{
		new_node = lstnew_redirect_node(main->split_input[*spl_id + 1], HEREDOC);
		// ADD MALLOC CHECK
		if (!(*tokens)[cmd_id].infiles)
			(*tokens)[cmd_id].infiles = new_node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].infiles, new_node);		
		(*tokens)[cmd_id].heredoc_delimiter = &main->split_input[*spl_id + 1];
		(*spl_id) += 2;
	}
}

void add_out_or_append(t_main *main, t_tokens **tokens, int cmd_id, int *spl_id)
{
	t_redirect_node *new_node;
	
	if (!main->split_input[*spl_id])
		return ;
	if (!ft_strncmp(main->split_input[*spl_id], ">", 2))
	{
		new_node = lstnew_redirect_node(main->split_input[*spl_id + 1], OUTFILE);
		// ADD MALLOC CHECK
		if (!(*tokens)[cmd_id].outfiles)
			(*tokens)[cmd_id].outfiles = new_node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].outfiles, new_node);
		(*spl_id) += 2;
	}
	else if (!ft_strncmp(main->split_input[*spl_id], ">>", 3))
	{
		new_node = lstnew_redirect_node(main->split_input[*spl_id + 1], APPEND);
		// ADD MALLOC CHECK
		if (!(*tokens)[cmd_id].outfiles)
			(*tokens)[cmd_id].outfiles = new_node;
		else
			lstadd_back_redirect_node(&(*tokens)[cmd_id].outfiles, new_node);
		(*spl_id) += 2;
	}
}

void check_for_redirect_error(t_main *main, t_tokens **tokens)
{
	int i;

	i = 0;
	while (main->split_input[i])
	{
		if (is_redirect((main->split_input[i])[0]))
		{
			if (!(main->split_input[i + 1]))
			{
				printf("syntax error near unexpected token '\\n'\n");
				free_and_exit_spl_and_cmd(main, tokens, 2); //TODO change to not exit, just skip execution
			}
			if (is_redirect((main->split_input[i + 1])[0]))
			{
				printf("syntax error near unexpected token '%s'\n", main->split_input[i + 1]);
				free_and_exit_spl_and_cmd(main, tokens, 2); //TODO change to not exit, just skip execution
			}
		}
		i++;
	}
}
