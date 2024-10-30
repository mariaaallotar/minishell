/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:33:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/28 11:03:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*buf;
	size_t	size;

	size = 10;
	buf = NULL;
	while (1)
	{
		buf = getcwd(buf, size);
		if (buf == NULL)
			size += 10;
		else
			return (buf);
	}
}

int	pwd(t_main *main, t_tokens token)
{
	char	*buf;

	(void)main;
	if (token.command[0] == NULL)
		return (1);
	buf = get_pwd();
	printf("%s\n", buf);
	free(buf);
	return (0);
}
