/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:17:12 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Compares the first n bytes (each interpreted as unsigned char) of the memory
*	areas s1 and s2
* Parameters:
*	*s1 - first memory area to compare
*	*s2 - second memory area to compare
*	n - amount of bytes to compare
* Returns:
*	An integer that represents the difference in the first unequal bytes 
*		in the memory
*	(int > 0) - s1 is grater than s2
*	(int = 0) - s1 is equal to s2
*	(int < 0) - s1 is smaller than s2
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
		n--;
	}
	return (0);
}
