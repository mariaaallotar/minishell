/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:28 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:17:29 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Copies n bytes from memory area src to memory area dst.
* If dst and src overlap, behavior is undefined.
* Parameters:
	*dst - the destination to copy bytes to
	*src - the source to copy from
	n - amount of bytes to cpy
* Returns: 
	The destination
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (n > 0)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
		n--;
	}
	return ((void *)dst);
}
