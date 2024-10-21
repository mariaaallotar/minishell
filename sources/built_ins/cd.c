/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:38:24 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/17 11:40:31 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_oldpwd(t_main *main)
{
	char	*value;
	char	*key_value;

	value = get_pwd();
	key_value = ft_strjoin("OLDPWD=", value);
	if (key_value == NULL)
	{
		perror(NULL);
		return (errno);
	}
	free(value);
	update_variable(main, key_value);
	free(key_value);
	return (0);
}

int	cd(t_main *main, t_tokens token)
{
	int		return_value;
	char	*value;
	char	*key_value;

	(void) main;
	if (token.command[2] != NULL)
	{
		dup2(STDERR_FILENO, 1);
		printf("Cd only takes one argument\n");
		return (1);
	}
	update_oldpwd(main);
	return_value = chdir(token.command[1]);
	if (return_value == -1)
	{
		perror(NULL);
		return (errno);
	}
	value = get_pwd();
	key_value = ft_strjoin("PWD=", value);
	if (key_value == NULL)
	{
		perror(NULL);
		return (errno);
	}
	free(value);
	update_variable(main, key_value);
	free(key_value);
	return (0);
}
