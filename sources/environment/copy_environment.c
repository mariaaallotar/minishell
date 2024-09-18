/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:30:11 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 15:28:14 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list_content(void *content)
{
	char	*str;

	str = content;
	printf("%s\n", str);
}

void	print_linked_list(t_list *env_list)
{
	ft_lstiter(env_list, print_list_content);
}

t_list	*copy_env(char *envp[])
{
	t_list	*env_list;
	t_list	*new;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		new = ft_lstnew(envp[i]);
		if (i == 0)
		{
			env_list = new;
			i++;
			continue;
		}
		ft_lstadd_back(&env_list, new);
		i++;
	}
	return (env_list);
}

void	test_env(char *envp[])
{
	t_list *env_list;

	env_list = copy_env(envp);
	print_linked_list(env_list);
}
