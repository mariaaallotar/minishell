/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:50:02 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/24 13:26:28 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//strncmp with check for equals
//Same as ft_strncmp but also checks for '=' directly after given element in env
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

int	find_var_and_remalloc(t_main *main, char **str)
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

void	expand_variables(t_main *main)
{
	int	i;

	i = 0;
	while (main->split_input[i])
	{
		if ((main->split_input[i])[0] == '$')
		{
			if (!find_var_and_remalloc(main, &main->split_input[i]))
			{
				printf("Error: Failed to malloc environment variable\n");
				free_and_exit_variable_malloc_failed(main, i + 1);
			}
		}
		i++;
	}
}
