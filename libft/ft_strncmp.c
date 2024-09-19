/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:53:49 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:21:57 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Compares lexicographically the null-terminated strings s1 and s2 but 
*	not more than n characters
* Parameters:
*	*s1 - first of strings to compare
*	*s2 - second of trings to compare
*	n - amount of characters to compare (at most)
* Returns:
*	An integer that represents the difference in the first unequal charcters 
*		in the strings
*	(int > 0) - s1 is grater than s2
*	(int = 0) - s1 is equal to s2
*	(int < 0) - s1 is smaller than s2
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!*s1 && !*s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	while ((*s1 || *s2) && n-- >= 1)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
