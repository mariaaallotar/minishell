/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:38:46 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/21 13:44:18 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list_content(void *content)
{
	char	*str;

	str = content;
	if (ft_strrchr(str, '=') == NULL)
		return ;
	printf("%s\n", str);
}

void	print_linked_list(t_list *env_list)
{
	ft_lstiter(env_list, print_list_content);
}
