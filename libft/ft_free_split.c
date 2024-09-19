/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:14:04 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:15:12 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees a list of strings
 * 
 * @param arr pointer to array of strings
 */
void	ft_free_split(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}
