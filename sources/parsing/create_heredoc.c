/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:52:55 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/23 10:31:36 by eberkowi         ###   ########.fr       */
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
		printf("Error: Failed to malloc heredoc filename number\n");
		return (0);
	}
	*name = NULL;
	*name = ft_strjoin("heredoc_", heredoc_num);
	if (!*name)
	{
		printf("Error: Failed to malloc heredoc filename joining\n");
		free(heredoc_num);
		return (0);
	}
	free(heredoc_num);
	return (1);
}

static void	readline_to_file(char *filename, char *delimiter)
{
	int		heredoc_fd;
	char	*input;
	int		input_len;
	int		delimiter_len;

	heredoc_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		input = readline("> ");
		// if (isatty(fileno(stdin)))
		// input = readline("> ");
		// else
		// {
		// 	char *line;
		// 	line = get_next_line(fileno(stdin));
		// 	input = ft_strtrim(line, "\n");
		// 	free(line);
		// }
		input_len = ft_strlen(input);
		delimiter_len = ft_strlen(delimiter);
		if (!ft_strncmp(input, delimiter, delimiter_len + 1))
		{
			free(input);
			input = NULL;
			break ;
		}
		write(heredoc_fd, input, input_len);
		write(heredoc_fd, "\n", 1);
		free(input);
		input = NULL;
	}
	close(heredoc_fd);
}

void	create_heredoc(t_main *main, t_tokens **tokens)
{
	int				token_id;
	int				num_of_heredocs;
	t_redirect_node	*temp;

	token_id = 0;
	num_of_heredocs = 0;
	while (token_id <= main->num_of_pipes)
	{
		temp = (*tokens)[token_id].infiles;
		while (temp)
		{
			if (temp->type == HEREDOC)
			{
				if (!create_filename(&temp->name, num_of_heredocs))
					free_all_and_exit(main, tokens);
				readline_to_file(temp->name, temp->delimiter);
				num_of_heredocs++;
			}
			temp = temp->next;
		}
		token_id++;
	}
}
