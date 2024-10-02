/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:47:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/02 10:46:43 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_path_if_executable(char *env_path, char *command, char **command_path)
{
	char	*path;

	path = ft_strjoin(env_path, "/");
	if (path == NULL)
	{
		perror("In set_path_if_executable");
		exit(1);
	}
	*command_path = ft_strjoin(path, command);
	if (command_path == NULL)
	{
		perror("In set_path_if_executable");
		exit(1);
	}
	free(path);
	if (access(*command_path, F_OK) == 0)
	{
		return (1);
	}
	free(*command_path);
	return (0);
}

char	**get_split_paths(char *path_variable)
{
	char	**env_paths;

	env_paths = ft_split((path_variable + ft_strlen("PATH=")), ':');
	if (env_paths == NULL)
	{
		perror(NULL);
		exit(1);
	}
	return (env_paths);
}

char	*get_path_variable(t_main *main)
{
	t_list	*node;

	node = find_node(main, "PATH=");
	if (node == NULL)
	{
		errno = ENOENT;
		//error
	}
	return (node->content);
}

char	*find_path(t_main *main, char *command)
{
	char	*path_varible;
	char	**env_paths;
	char	*command_path;
	int		i;

	path_varible = get_path_variable(main);
	env_paths = get_split_paths(path_varible);
	i = 0;
	while (env_paths[i])
	{
		if (set_path_if_executable(env_paths[i], command, &command_path))
		{
			ft_free_split(&env_paths);
			return (command_path);
		}
		i++;
	}
	errno = 127;
	ft_free_split(&env_paths);
	return (NULL);
}