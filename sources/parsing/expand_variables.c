/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:50:02 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/18 14:26:11 by eberkowi         ###   ########.fr       */
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

//Find the given $VAR in the env replace the split_input element if found
int	find_var_and_remalloc(t_main *main, char **str)
{
	int		len;
	t_list	*temp;

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
	return (1);
}

void	expand_variables(t_main *main)
{
	int	i;

	i = 0;
	while (main->split_input[i])
	{
		if ((main->split_input[i])[0] == '$')
			if (!find_var_and_remalloc(main, &main->split_input[i]))
			{
				printf("Error: Failed to malloc environment variable\n");
				free_and_exit_variable_malloc_failed(main, i + 1);
			}
		i++;
	}
}

// //strncmp with check for equals
// //Same as ft_strncmp but also checks for '=' directly after given element in env
// static int	cmp_eq(const char *s1, const char *s2, size_t n)
// {
// 	if (!*s1 && !*s2)
// 		return ((unsigned char)*s1 - (unsigned char)*s2);
// 	while ((*s1 || *s2) && n-- >= 1)
// 	{
// 		if (*s1 != *s2)
// 			return ((unsigned char)*s1 - (unsigned char)*s2);
// 		s1++;
// 		s2++;
// 	}
// 	if (*s2 != '=')
// 		return (1);
// 	return (0);
// }

// //Find the given $VAR in the env replace the split_input element if found
// static void	find_var_and_remalloc(t_main *main, int i)
// {
// 	int		len;
// 	t_list	*temp;

// 	temp = main->env_list;
// 	len = ft_strlen(main->split_input[i]);
// 	while (temp)
// 	{
// 		if (!cmp_eq(main->split_input[i] + 1, (char *)temp->content, len - 1))
// 		{
// 			free(main->split_input[i]);
// 			main->split_input[i] = NULL;
// 			main->split_input[i] = ft_strdup((char *)temp->content + len);
// 			if (!main->split_input[i])
// 			{
// 				printf("Error: Failed to malloc environment variable\n");
// 				free_and_exit_variable_malloc_failed(main, i + 1);
// 			}
// 			return ;
// 		}
// 		temp = temp->next;
// 	}
// }

// void	expand_variables(t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	while (main->split_input[i])
// 	{
// 		if ((main->split_input[i])[0] == '$')
// 			find_var_and_remalloc(main, i);
// 		i++;
// 	}
// }
