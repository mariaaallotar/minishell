/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:33:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/26 10:23:47 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*buf;
	size_t	size;

	size = 10;
	buf = NULL;
	while (size < 10000)
	{
		buf = getcwd(buf, size);
		if (buf == NULL)
			size += 10;
		else
			return (buf);
	}
	return (NULL);
}

char	*get_pwd_from_env(t_main *main)
{
	t_list	*node;
	char	*pwd;

	node = find_node(main, "PWD=");
	if (node == NULL)
	{
		return (NULL);
	}
	pwd = node->content + 4;
	return (pwd);
}

int	pwd(t_main *main, t_tokens token)
{
	char	*buf;

	(void)main;
	if (token.command[0] == NULL)
		return (1);
	buf = get_pwd_from_env(main);
	if (!buf)
	{
		buf = get_pwd();
		printf("%s\n", buf);
		free(buf);
	}
	else
		printf("%s\n", buf);
	return (0);
}
