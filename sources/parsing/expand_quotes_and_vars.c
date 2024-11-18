/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:55 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/21 14:41:30 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void print_quote_split(char **quote_split)
// {
// 	printf("\033[0;34m---QUOTE SPLIT ---\033[0m\n");
// 	int i = 0;
// 	while (quote_split[i])
// 	{
// 		printf("quote_split[%d] = %s\n", i, quote_split[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

void	expand_vars_or_do_inner_expansion(t_main *main, t_tokens **tokens
		, char ***quote_split, t_expand expand)
{
	int	i;

	i = 0;
	while ((*quote_split)[i])
	{
		if ((*quote_split)[i][0] == '\''
				&& !expand.is_heredoc && expand.quote_type == '\0')
		{
			if (!remove_outside_quotes(&(*quote_split)[i]))
				free_and_exit_quote_split_expand(main, tokens, quote_split, i);
		}
		else if (check_for_outside_quotes((*quote_split)[i], NULL)
				&& (*quote_split)[i][0] == '\"')
		{
			if (!inner_expansion(main, &(*quote_split)[i], expand.is_heredoc))
				free_and_exit_quote_split_expand(main, tokens, quote_split, i);
		}
		else if (!find_var_in_env(main, &(*quote_split)[i]))
		{
			print_error("Error: Failed to malloc env variable in quotes\n");
			free_and_exit_quote_split_expand(main, tokens, quote_split, i);
		}
		i++;
	}	
}

static void	get_quote_split_length(t_main *main, char **quote_split)
{
	main->quote_split_length = 0;
	if (!quote_split)
		return ;
	while (quote_split[main->quote_split_length])
		(main->quote_split_length)++;
}

static void	init_expand_struct(t_expand *expand, bool is_heredoc)
{
	(*expand).quote_type = '\0';
	(*expand).is_heredoc = is_heredoc;
}

int	expand_quotes_and_vars(t_main *main, t_tokens **tokens
		, char **str, bool is_heredoc)
{
	char		**quote_split;
	t_expand	expand;

	init_expand_struct(&expand, is_heredoc);
	if (check_for_outside_quotes(*str, &expand.quote_type))
	{
		if (!remove_outside_quotes(str))
			return (0);
		if ((*str)[0] == '\0' || expand.quote_type == '\'')
			return (1);
	}
	if (!create_quote_split(*str, &quote_split))
		return (0);
	get_quote_split_length(main, quote_split);
	expand_vars_or_do_inner_expansion(main, tokens, &quote_split, expand);
	if (!combine_quote_split(main, tokens, &quote_split, str))
	{
		ft_free_split(&quote_split);
		return (0);
	}
	if (!check_for_heredoc_quotes(str, is_heredoc
			, expand.quote_type, &quote_split))
		return (0);
	ft_free_split(&quote_split);
	return (1);
}
