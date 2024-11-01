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
			printf("Error: Failed to malloc environment variable in quotes\n");
			free_and_exit_quote_split_expand(main, tokens, quote_split, i);
		}
		i++;
	}	
}

static int	combine_remaining_elements(t_main *main, t_tokens **tokens
		, char ***quote_split, char **str)
{
	int		i;
	char	*temp;

	i = 2;
	temp = NULL;
	while ((*quote_split)[i])
	{
		temp = ft_strdup(*str);
		if (!temp)
			free_and_exit_combine_elements(main, tokens, quote_split);
		free(*str);
		*str = NULL;
		*str = ft_strjoin(temp, (*quote_split)[i]);
		if (!*str)
		{
			printf("Error: Failed to malloc str in combine quote_split\n");
			free(temp);
			return (0);
		}
		free(temp);
		temp = NULL;
		i++;
	}
	return (1);
}

static int	combine_quote_split(t_main *main, t_tokens **tokens
		, char ***quote_split, char **str)
{
	free(*str);
	*str = NULL;
	if (!(*quote_split)[1])
	{
		*str = ft_strdup((*quote_split)[0]);
		if (!*str)
		{
			printf("Error: Failed to malloc str in combine quote_split\n");
			return (0);
		}
		return (1);
	}
	else
		*str = ft_strjoin((*quote_split)[0], (*quote_split)[1]);
	if (!*str)
		return (0);
	if (!combine_remaining_elements(main, tokens, quote_split, str))
		return (0);
	return (1);
}

int	expand_quotes_and_vars(t_main *main, t_tokens **tokens
		, char **str, bool is_heredoc)
{
	char		**quote_split;
	t_expand	expand;

	expand.quote_type = '\0';
	expand.is_heredoc = is_heredoc;
	if (check_for_outside_quotes(*str, &expand.quote_type))
	{
		if (!remove_outside_quotes(str))
			return (0);
		if ((*str)[0] == '\0' || expand.quote_type == '\'')
			return (1);
	}
	if (!create_quote_split(*str, &quote_split))
		return (0);
	expand_vars_or_do_inner_expansion(main, tokens, &quote_split, expand);
	if (!combine_quote_split(main, tokens, &quote_split, str))
	{
		ft_free_split(&quote_split);
		return (0);
	}
	if (!check_for_heredoc_quotes(str, is_heredoc, expand.quote_type
			, &quote_split))
		return (0);
	ft_free_split(&quote_split);
	return (1);
}
