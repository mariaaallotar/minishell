/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:11:22 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:14:11 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Contiguously allocates enough space for count objects that are size bytes of
* memory each and returns a pointer to the allocated memory
* The allocated memory is filled with bytes of value zero.
* Parameters:
*	count - amount of memoryspaces
*	size - size in bytes of each memoryspace
* Returns:
*	a pointer to the allocated memoryspace
*	NULL if allocation failed
*/
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
