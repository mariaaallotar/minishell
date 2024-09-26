/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:50:02 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/26 17:09:26 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	strncmp_and_check_equals(const char *s1, const char *s2, size_t n)
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

static void free_and_exit_failed_var(t_main *main, int i)
{
	while (main->split_input[i++])
		free(main->split_input[i]);
	ft_free_split(&main->split_input);
	free(main->input);
	printf("Error: Failed to malloc environment variable\n");
	exit (1);
}

static void find_var_and_remalloc(t_main *main, int i, char *env[])
{
	int len;
	int j;

	len = ft_strlen(main->split_input[i]);
	j = 0;
	while (env[j])
	{
		if (!strncmp_and_check_equals(main->split_input[i] + 1, env[j], len - 1))
		{
			free(main->split_input[i]);
			main->split_input[i] = NULL;
			main->split_input[i] = ft_strdup(env[j] + len);
			if (!main->split_input[i])
				free_and_exit_failed_var(main, i + 1);
			return ;
		}
		j++;
	}
}

//LEft off here. Need to now "delete" an element in split_input if
//the $VAR does not exist in env :(

void expand_variables(t_main *main)
{
	char *env[] = {"VARS=hello", "VAR=ls -l", "TILDA=a b c", NULL}; //REMOVE
	int i;
	
	i = 0;
	while(main->split_input[i])
	{
		if ((main->split_input[i])[0] == '$')
			find_var_and_remalloc(main, i, env);
		i++;
	}
}
