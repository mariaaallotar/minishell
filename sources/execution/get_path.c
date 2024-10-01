/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:45:33 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/01 13:46:36 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_path_to_file(char *command)
{
	if (access(command[0], F_OK) == 0)
		return (1);
	else
		return (0);
}

int	is_path_to_executable(char *command)
{
	if (access(command[0], X_OK) == 0)
		return (1);
	return (0);
}

int	is_direcotory(char *command)
{
	struct stat	file_stat;

	if (access(command, F_OK) == 0)
	{
		if(stat(command, &file_stat) == 0)
		{
			if(S_ISDIR(file_stat.st_mode))
			{
				errno = EISDIR;
				return (1);
			}
			else
				return (0);
		}
		else
		{
			perror("stat");
			exit(1);
		}
	}
	else
		return (0);
}

int	empty_command(char *command)
{
	if (command[0] == NULL || command[0] == '\0')	//anything else? How much is checked in parsing
	{
		errno = 127;
		return (1);
	}
	return (0);
}

char	*get_path(char **command, t_list *env_list)
{
	if (empty_command(command[0]))
		return (NULL);
	else if (is_direcotory(command[0]))
		return (NULL);
	else if (is_path_to_file(command[0]))
	{
		if (is_path_to_executable(command[0]))
			return (command[0]);
		else
			return (NULL);
	}
	return (find_path(command[0]));
}
