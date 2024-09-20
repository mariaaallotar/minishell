/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:38:46 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/19 14:38:57 by maheleni         ###   ########.fr       */
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
