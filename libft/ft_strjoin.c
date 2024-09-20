/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:50:01 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:20:49 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Allocates and returns a new string, which is the result of the concatenation
*	of 's1' and 's2'
* Parameters:
*	*s1 - the prefix string
*	*s2 - the suffix string
* Returns:
*	The string
*	NULL if allocation failed
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*new_string;
	size_t		new_length;
	int			i;

	if (!s1 || !s2)
		return (NULL);
	new_length = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *)malloc(new_length * sizeof(char) + 1);
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		new_string[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		new_string[i++] = *s2;
		s2++;
	}
	new_string[i] = '\0';
	return (new_string);
}
