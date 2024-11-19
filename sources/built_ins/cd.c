/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:38:24 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/19 14:10:08 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_directory_variable(t_main *main, char *key)
{
	char	*value;
	char	*key_value;

	value = get_pwd();
	key_value = ft_strjoin(key, value);
	if (key_value == NULL)
	{
		free(value);
		perror(NULL);
		return (errno);
	}
	free(value);
	update_variable(main, key_value);
	free(key_value);
	return (0);
}

char	*get_path_to_home(t_main *main)
{
	t_list	*home_variable;
	char	*message;

	home_variable = find_node(main, "HOME=");
	if (home_variable == NULL)
	{
		message = "cd: HOME not set\n";
		write(STDERR_FILENO, message, ft_strlen(message));
		return (NULL);
	}
	return (home_variable->content + 5);
}

int	cd(t_main *main, t_tokens token)
{
	int		return_value;
	char	*path;
	char	*message;

	if (token.command[1] != NULL && token.command[2] != NULL)
	{
		message = "cd: too many arguments\n";
		write(STDERR_FILENO, message, ft_strlen(message));
		return (1);
	}
	if (token.command[1] == NULL)
		path = get_path_to_home(main);
	else
		path = token.command[1];
	if (path == NULL)
		return (1);
	update_directory_variable(main, "OLDPWD=");
	return_value = chdir(path);
	if (return_value == -1)
	{
		perror("cd");
		return (1);
	}
	update_directory_variable(main, "PWD=");
	return (0);
}
