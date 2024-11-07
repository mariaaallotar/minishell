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
			print_error("Error: Failed to malloc environment variable in quotes\n");
			free_and_exit_quote_split_expand(main, tokens, quote_split, i);
		}
		i++;
	}	
}

static int get_num_of_existing_elements(t_main *main, char **quote_split)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (i < main->quote_split_length)
	{
		if (quote_split[i])
			result++;
		i++;
	}
	return (result);
}

int next_id(t_main *main, char **quote_split)
{
	while(main->id_quote_split < main->quote_split_length)
	{
		if (quote_split[main->id_quote_split])
			return (main->id_quote_split);
		(main->id_quote_split)++;
	}
	return (0);
}

static int	combine_remaining_elements(t_main *main, t_tokens **tokens
		, char ***quote_split, char **str, int num_of_existing_elements)
{
	char	*temp;

	temp = NULL;
	//printf("id_quote_split_value = %d\n", main->id_quote_split);
	while (main->id_quote_split < num_of_existing_elements)
	{
		temp = ft_strdup(*str);
		if (!temp)
			free_and_exit_combine_elements(main, tokens, quote_split);
		free(*str);
		*str = NULL;
		*str = ft_strjoin(temp, (*quote_split)[next_id(main, *quote_split)]);
		if (!*str)
		{
			print_error("Error: Failed to malloc str in combine quote_split\n");
			free(temp);
			return (0);
		}
		free(temp);
		temp = NULL;
		(main->id_quote_split)++;
	}
	return (1);
}

static int	combine_quote_split(t_main *main, t_tokens **tokens
		, char ***quote_split, char **str)
{
	int num_of_existing_elements;
	char *temp;

	free(*str);
	*str = NULL;
	main->id_quote_split = 0;
	num_of_existing_elements = get_num_of_existing_elements(main, *quote_split);
	//printf("elements_in_quote = %d\n", main->quote_split_length);
	//printf("num_of_existing = %d\n", num_of_existing_elements);
	if (num_of_existing_elements == 0)
		return (1);
	if (num_of_existing_elements == 1)
	{
		*str = ft_strdup((*quote_split)[next_id(main, *quote_split)]);
		if (!*str)
		{
			print_error("Error: Failed to malloc str in combine quote_split\n");
			return (0);
		}
		return (1);
	}
	else
	{
		temp = NULL;
		temp = ft_strdup((*quote_split)[next_id(main, *quote_split)]);
		if (!temp)
		{
			print_error("Error: Failed to malloc temp var in combine_quote_split\n");
			return (0);
		}
		(main->id_quote_split)++;
		*str = ft_strjoin(temp, (*quote_split)[next_id(main, *quote_split)]);
		if (!*str)
		{
			print_error("Error: Failed to malloc str in combine_quote_split\n");
			free(temp);
			return (0);
		}
		free(temp);
		(main->id_quote_split)++;
	}

	if (!combine_remaining_elements(main, tokens, quote_split, str, num_of_existing_elements))
		return (0);
	return (1);
}

static void get_quote_split_length(t_main *main, char **quote_split)
{
	main->quote_split_length = 0;
	if (!quote_split)
		return ;
	while (quote_split[main->quote_split_length])
		(main->quote_split_length)++;
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
	//print_quote_split(quote_split); //REMOVE
	get_quote_split_length(main, quote_split);
	//printf("quote_split_length = %d\n", main->quote_split_length);
	expand_vars_or_do_inner_expansion(main, tokens, &quote_split, expand);
	if (!combine_quote_split(main, tokens, &quote_split, str))
	{
		ft_free_split(&quote_split); //NEED TO CHANGE THIS TO USE LENGTH INSTEAD OF NULL
		return (0);
	}
	if (!check_for_heredoc_quotes(str, is_heredoc, expand.quote_type, &quote_split))
		return (0);
	//printf("combined_quote_split = %s\n", *str);
	ft_free_split(&quote_split); //NEED TO CHANGE THIS TO USE LENGTH INSTEAD OF NULL
	return (1);
}
