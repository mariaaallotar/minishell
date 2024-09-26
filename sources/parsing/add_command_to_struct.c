/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_to_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:37:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/25 10:49:25 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_elements_in_command(t_main *main, int spl_id)
{
	int result;

	result = 0;
	while (main->split_input[spl_id] && !is_special(main->split_input[spl_id][0]))
	{
		spl_id++;
		result++;
	}
	return (result);
}

static char	*strdup_with_remove_quotes(const char *s1)
{
	int		i;
	char	*s2;

	s2 = (char *)malloc((ft_strlen(s1) - 2) * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i + 1] && !is_quote(s1[i + 1]))
	{
		s2[i] = s1[i + 1];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static void malloc_cmds(t_main *main, t_command **command, int cmd_id, int c)
{
	(*command)[cmd_id].command = malloc((c + 1) * sizeof(char *));
	if (!(*command)[cmd_id].command)
	{
		printf("Error: Failed to malloc command array in struct\n");
		free_all_and_exit(main, command, 1);
	}
}

void add_command(t_main *main, t_command **command, int cmd_id, int *spl_id)
{
	int element_count;
	int i;

	element_count = count_elements_in_command(main, *spl_id);
	if (element_count == 0)
		return ;
	malloc_cmds(main, command, cmd_id, element_count);
	i = 0;
	while (i < element_count)
	{
		(*command)[cmd_id].command[i] = NULL;
		if (is_quote((main->split_input[*spl_id])[0]))
			(*command)[cmd_id].command[i] = strdup_with_remove_quotes(main->split_input[*spl_id]);
		else
			(*command)[cmd_id].command[i] = ft_strdup(main->split_input[*spl_id]);
		if (!(*command)[cmd_id].command[i])
		{
			printf("Error: Failed to malloc add element to command\n");
			free_all_and_exit(main, command, 1);
		}
		(*spl_id)++;
		i++;
	}
	(*command)[cmd_id].command[i] = NULL;
}
