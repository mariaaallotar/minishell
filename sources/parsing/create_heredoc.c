/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:52:55 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/19 10:17:40 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_filename(char **name, int num_of_heredocs)
{
	char	*heredoc_num;

	heredoc_num = NULL;
	heredoc_num = ft_itoa(num_of_heredocs);
	if (!heredoc_num)
	{
		print_error("Error: Failed to malloc heredoc filename number\n");
		return (0);
	}
	*name = NULL;
	*name = ft_strjoin("heredoc_", heredoc_num);
	if (!*name)
	{
		print_error("Error: Failed to malloc heredoc filename joining\n");
		free(heredoc_num);
		return (0);
	}
	free(heredoc_num);
	return (1);
}

int	create_heredoc(t_main *main, t_tokens **tokens)
{
	int				token_id;
	int				num_of_heredocs;
	t_redirect_node	*temp;

	token_id = 0;
	num_of_heredocs = 0;
	while (token_id <= main->num_of_pipes)
	{
		temp = (*tokens)[token_id].redirects;
		while (temp)
		{
			if (temp->type == HEREDOC)
			{
				if (!create_filename(&temp->name, num_of_heredocs))
					free_all_and_exit(main, tokens);
				if (readline_to_file(main, tokens, temp) == 0)
					return (0);
				num_of_heredocs++;
			}
			temp = temp->next;
		}
		token_id++;
	}
	return (1);
}
