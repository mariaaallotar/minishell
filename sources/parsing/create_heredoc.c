/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:52:55 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/11 15:23:26 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void create_filename(char **name, int num_of_heredocs)
{
	char *heredoc_num;
	
	heredoc_num = NULL;
	heredoc_num = ft_itoa(num_of_heredocs);
	//TODO Malloc check
	*name = NULL;
	*name = ft_strjoin("heredoc_", heredoc_num);
	//TODO Malloc check
	free(heredoc_num);
}

//Left off here! naming the file and creating a file both work!
//Now just have to add readline to file :)

static void readline_to_file(char *filename)
{
	int heredoc_fd;
	
	heredoc_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	close(heredoc_fd);
}

void create_heredoc(t_main *main, t_tokens **tokens)
{
	int token_id;
	int num_of_heredocs;
	t_redirect_node *temp;
	char *delimiter;

	token_id = 0;
	num_of_heredocs = 0;
	while (token_id <= main->num_of_pipes)
	{
		temp = (*tokens)[token_id].infiles;
		while (temp)
		{
			if (temp->type == HEREDOC)
			{
				delimiter = ft_strdup(temp->name);
				//TODO Malloc check
				create_filename(&temp->name, num_of_heredocs);
				readline_to_file(temp->name);
				free(delimiter);
				delimiter = NULL;
				num_of_heredocs++;
			}
			temp = temp->next;
		}
		token_id++;
	}
}
