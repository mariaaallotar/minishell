/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:38:06 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/22 11:20:39 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_for_int_after_exit(char *element, int *temp_code)
{
	size_t itoa_result_len;
	size_t element_len;
	size_t len_to_compare;
	char *itoa_result;
	
	*temp_code = ft_atoi(element);
	itoa_result = ft_itoa(*temp_code);
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

void	close_open_fds(int open_fds[2])
{
	close(open_fds[0]);
	close(open_fds[1]);
}

void	free_everything_everything(t_main *main)
{
	free_and_null_split_input(main);
	free_token_commands(main, main->tokens);
	free_token_redirects(main, main->tokens);
	free(*(main->tokens));
	free_environment(&(main->env_list));
	rl_clear_history();
}

int	exit_command(t_main *main, t_tokens token, int parent, int open_fds[2])
{
	int temp_code;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (token.command[1] == NULL)	//only exit
	{
		if (!parent)
			return (0);
		printf("exit\n");
		close_open_fds(open_fds);
		free_everything_everything(main);
		exit(0);
	}
	if (check_for_int_after_exit(token.command[1], &temp_code) && token.command[2] == NULL)		//exit, number, NULL
	{
		if (!parent)
			return (temp_code);
		printf("exit\n");
		close_open_fds(open_fds);
		free_everything_everything(main);
		exit(temp_code);
	}
	else if (!check_for_int_after_exit(token.command[1], &temp_code))				//exit, not number, NULL
	{
		printf("exit: numeric argument required\n");
		if (!parent)
			return (2);
		free_everything_everything(main);
		printf("exit\n");
		close_open_fds(open_fds);
		exit(2);
	}
	printf("exit: too many arguments\n");
	return (1);
}
