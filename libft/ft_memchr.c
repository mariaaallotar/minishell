/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:14:40 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:16:56 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Locates the first occurrence of c (converted to an unsigned char) in s.
* Continues searching even after '\0' if there is still n left.
* Parameters:
*	*s - pointer to memory to search from
*	c - int representation of character to find
*	n - amount of memorylocations to search
* Returns:
*	Location (void pinter) of first occurrance where c was found
*	NULL if c was NOT found anywhere
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
		n--;
	}
	return (NULL);
}
