/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:11:22 by eberkowi          #+#    #+#             */
/*   Updated: 2024/04/30 11:22:57 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (count != 0 && SIZE_MAX / count < size)
		return (NULL);
	result = (void *)malloc(count * size);
	if (result == NULL)
		return (NULL);
	else
		ft_bzero(result, count * size);
	return (result);
}
