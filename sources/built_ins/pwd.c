/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:33:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/10 14:21:15 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*malloc_buf(int size)
{
	char	*buf;

	buf = malloc (size);
	if (buf == NULL)
	{
		printf("Malloc failed\n");
		//error;
		exit(1);
	}
	return (buf);
}

int	pwd(t_main *main, t_tokens token)
{
	char	*buf;
	size_t	size;

	(void)main;
	if (token.command[1] != NULL)
	{
		printf("Pwd does not take any arguments\n");
		return (1);
	}
	size = 10;
	while (1)
	{
		buf = malloc_buf(size);
		buf = getcwd(buf, size);
		if (buf == NULL)
		{
			free(buf);
			size *= 2;
		}
		else
			break ;
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
