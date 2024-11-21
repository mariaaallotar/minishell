/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:38:06 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/21 13:37:33 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long	ft_atoi_long(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	result = 0;
	while (*str && ft_isdigit(*str))
	{
		result = (result * 10) + sign * (*str - '0');
		if (sign == 1 && result < 0)
			return (-1);
		else if (sign == -1 && result > 0)
			return (0);
		str++;
	}
	return (result);
}

int	int_after_exit(char *element, long *exit_code)
{
	size_t	itoa_result_len;
	size_t	element_len;
	size_t	len_to_compare;
	char	*itoa_result;

	if (*element == '+')
		element++;
	*exit_code = ft_atoi_long(element);
	itoa_result = NULL;
	itoa_result = ft_itoa_long(*exit_code);
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
	print_error("exit\n");
	close(open_fds[0]);
	close(open_fds[1]);
	exit(exit_code);
}

long	exit_command(t_main *main, t_tokens token, int parent, int open_fds[2])
{
	long	code;

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
