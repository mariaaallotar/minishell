/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:50:02 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/01 13:32:53 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cmp_eq(const char *s1, const char *s2, size_t n)
{
	if (!*s1 && !*s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	while ((*s1 || *s2) && n-- >= 1)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	if (*s2 != '=')
		return (1);
	return (0);
}

static int	expand_exit_code(t_main *main, char **str)
{
	free(*str);
	*str = NULL;
	*str = ft_itoa(main->exit_code);
	if (!*str)
		return (0);
	return (1);
}

int	find_var_in_env(t_main *main, char **str)
{
	int		len;
	t_list	*temp;

	if ((*str)[0] == '$' && (*str)[1] == '?')
	{
		if (!expand_exit_code(main, str))
			return (0);
		return (1);
	}
	temp = main->env_list;
	len = ft_strlen(*str);
	while (temp)
	{
		if (!cmp_eq(*str + 1, (char *)temp->content, len - 1))
		{
			free(*str);
			*str = NULL;
			*str = ft_strdup((char *)temp->content + len);
			if (!*str)
				return (0);
			return (1);
		}
		temp = temp->next;
	}
	if ((*str)[0] == '$' && (*str)[1])
	{
		free(*str);
		*str = NULL;
		*str = ft_strdup("");
		if (!*str)
			return (0);
	}
	return (1);
}
