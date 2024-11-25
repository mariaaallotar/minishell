/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:45:33 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/25 12:16:47 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(char *command)
{
	struct stat	file_stat;

	if (access(command, F_OK) == 0)
	{
		if (stat(command, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
			{
				errno = EISDIR;
				return (1);
			}
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

static int	command_begins_with_dot_or_contains_slash(char *command)
{
	int	i;

	if (command[0] == '.')
		return (1);
	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	path_does_not_exist(t_main *main)
{
	t_list	*node;

	node = find_node(main, "PATH=");
	if (node == NULL)
	{
		errno = ENOENT;
		return (1);
	}
	return (0);
}

char	*get_path(t_main *main, char *command, int *pids)
{
	errno = 0;
	if (command_begins_with_dot_or_contains_slash(command))
		return (ft_strdup(command));
	if (path_does_not_exist(main))
		return (ft_strdup(command));
	return (find_path(main, command, pids));
}
