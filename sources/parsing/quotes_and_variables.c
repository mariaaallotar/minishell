/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:56:04 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/17 16:15:38 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int check_for_no_vars(char **str)
{
	int i;
	
	i = 0;
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '\t')
	{
		if ((*str)[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

static int remove_outside_quotes(char **str)
{
	size_t remove_quote_len;
	size_t i;
	char *temp;

	temp = ft_strdup(*str);
	free(*str);
	*str = NULL;
	remove_quote_len = ft_strlen(temp) - 1;
	*str = malloc(remove_quote_len);
	if (!*str)
	{
		printf("Error: Failed to malloc remove-outside-quotes\n");
		free(temp);
		return (0);
	}
	i = 0;
	while (i < remove_quote_len - 1)
	{
		(*str)[i] = temp[i + 1];
		i++;
	}
	(*str)[i] = '\0';
	free(temp);
	return (1);
}

//Left off here. Just finished remove_outside_quotes in the case where there are no $'s
//Now need to create temporary array of strings that holds each $VAR and non-VAR chunk
//of the given *str. Each element of the 2d array is then expanded if needed, then
//those elements are joined into one string to form the final result

static int double_quotes(char **str)
{
	//char **quote_split;
	//size_t quote_split_len;
	
	//Check if it's a double quote
	if ((*str)[0] != '\"')
		return (1);
		
	//Check for a $ and just remove outside quotes if not found
	if (check_for_no_vars(str))
	{
		if (!remove_outside_quotes(str))
			return (0);
		return (1);
	}
	
	//Create quote_split
	
	//Free and Null
	//free(*str);
	//*str = NULL;
	return (1);
}

void quotes_and_variables(t_main *main, t_tokens **tokens)
{
	int token_id;
	int cmd_id;

	token_id = 0;
	cmd_id = 0;

	//Loop through all tokens
	while (token_id < main->num_of_pipes + 1)
	{
		//Loop through all commands within 1 token
		cmd_id = 0;
		if ((*tokens)[token_id].command)
		{
			while ((*tokens)[token_id].command[cmd_id])
			{
				if (!double_quotes(&(*tokens)[token_id].command[cmd_id]))
					free_and_exit_quote_malloc_failed(main, tokens, token_id, cmd_id);
				cmd_id++;
			}
		}
		token_id++;
	}	
}
