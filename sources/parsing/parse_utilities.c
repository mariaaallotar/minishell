/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:11:31 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 10:27:27 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Left off here, listing more special chars
int	is_special(char c)
{
	if (c == '$' || c == '|' || c == '<' || c == '>' || c == '=')
		return (1);
	return (0);
}
