/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:47:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/25 10:12:31 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_path_if_executable(char *env_path, char *command, char **command_path)
{
	char	*path;

	path = ft_strjoin(env_path, "/");
	if (path == NULL)
		return (-1);
	*command_path = ft_strjoin(path, command);
	free(path);
	if (command_path == NULL)
		return (0);
	if (access(*command_path, F_OK) == 0 && access(*command_path, X_OK) == 0)
		return (1);
	free(*command_path);
	return (0);
}

char	*get_path_variable(t_main *main)
{
	t_list	*node;

	node = find_node(main, "PATH=");
	if (node == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	return (node->content);
}

char	**get_split_paths(t_main *main, int *pids)
{
	char	*path_variable;
	char	**env_paths;

	path_variable = get_path_variable(main);
	if (path_variable == NULL)
		return (NULL);
	env_paths = ft_split((path_variable + ft_strlen("PATH=")), ':');
	if (env_paths == NULL)
	{
		perror(NULL);
		free_all_in_child(main, pids);
		exit(errno);
	}
	return (env_paths);
}

char	*find_path(t_main *main, char *cmd, int *pids)
{
	char	**env_paths;
	char	*cmd_path;
	int		i;
	int		return_value;

	env_paths = get_split_paths(main, pids);
	if (env_paths == NULL)
		return (NULL);
	i = 0;
	while (env_paths[i])
	{
		return_value = set_path_if_executable(env_paths[i], cmd, &cmd_path);
		if (return_value == 1)
		{
			ft_free_split(&env_paths);
			return (cmd_path);
		}
		i++;
	}
	errno = 127;
	ft_free_split(&env_paths);
	return (NULL);
}
