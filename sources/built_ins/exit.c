/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:38:06 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/20 16:27:05 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	int_after_exit(char *element, int *exit_code)
{
	size_t	itoa_result_len;
	size_t	element_len;
	size_t	len_to_compare;
	char	*itoa_result;

	if (*element == '+')
		element++;
	*exit_code = ft_atoi(element);
	itoa_result = NULL;
	itoa_result = ft_itoa(*exit_code);
	if (!itoa_result)
		return (0);
	itoa_result_len = ft_strlen(itoa_result);
	element_len = ft_strlen(element);
	if (itoa_result_len > element_len)
		len_to_compare = itoa_result_len;
	else
		len_to_compare = element_len;
	if (!ft_strncmp(element, itoa_result, len_to_compare))
	{
		free(itoa_result);
		return (1);
	}
	free(itoa_result);
	return (0);
}

void	free_and_exit(t_main *main, int open_fds[2], int exit_code)
{
	remove_heredocs(main, main->tokens);
	free_and_null_split_input(main);
	free_token_commands(main, main->tokens);
	free_token_redirects(main, main->tokens);
	free(*(main->tokens));
	free_environment(&(main->env_list));
	rl_clear_history();
	printf("exit\n");
	close(open_fds[0]);
	close(open_fds[1]);
	exit(exit_code);
}

int	exit_command(t_main *main, t_tokens token, int parent, int open_fds[2])
{
	int	code;

	if (token.command[1] == NULL)
	{
		if (!parent)
			return (0);
		free_and_exit(main, open_fds, 0);
	}
	if (int_after_exit(token.command[1], &code) && token.command[2] == NULL)
	{
		if (!parent)
			return (code);
		free_and_exit(main, open_fds, code);
	}
	else if (!int_after_exit(token.command[1], &code))
	{
		print_error("exit: numeric argument required\n");
		if (!parent)
			return (2);
		free_and_exit(main, open_fds, 2);
	}
	print_error("exit: too many arguments\n");
	return (1);
}
