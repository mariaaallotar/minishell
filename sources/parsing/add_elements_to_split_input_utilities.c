/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements_to_split_input_utilities.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:37:17 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/30 15:40:40 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces_and_tabs(char *input, int *id_input)
{
	while (input[*id_input] && (input[*id_input] == ' '
			|| input[*id_input] == '\t'))
		(*id_input)++;
}

int	char_is_space_or_special_and_quotes_are_closed(char c, t_parsing p)
{
	if ((c == ' ' || c == '\t' || char_is_special(c))
		&& p.num_of_singles % 2 == 0 && p.num_of_doubles % 2 == 0)
		return (1);
	return (0);
}

void	update_inside_status(t_parsing *p)
{
	if (p->num_of_singles % 2 != 0)
		p->inside_singles = true;
	else
		p->inside_singles = false;
	if (p->num_of_doubles % 2 != 0)
		p->inside_doubles = true;
	else
		p->inside_doubles = false;
}

void	update_number_of_quotes(char c, t_parsing *p)
{
	if (c == '\"' && !p->inside_singles)
		p->num_of_doubles++;
	else if (c == '\'' && !p->inside_doubles)
		p->num_of_singles++;
}

int	check_for_unclosed_quotes(t_parsing p)
{
	if (p.inside_singles || p.inside_doubles)
	{
		printf("Error: Unclosed quotes\n");
		return (1);
	}
	return (0);
}
