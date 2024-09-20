/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:44 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:22:33 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Locates the last occurrence of c (converted to a char) in the string 
*	pointed to by s.
* The terminating null character is considered to be part of the 
*	string; therefore if c is `\0', the functions locate the terminating `\0'.
* Parameters:
*	*s - pointer to the string to find character c from
*	c - int representation of the character to find
* Returns:
*	Pointer to the last occurance of the character found.
*	NULL if c is not found anywhere in the string
*/
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
