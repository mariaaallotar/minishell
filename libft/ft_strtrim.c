/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:55:16 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:23:02 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(char const *s1, char const *set, int index)
{
	while (*set)
	{
		if (s1[index] == *set)
			return (1);
		set++;
	}
	return (0);
}

/**
* Allocates and returns a copy of string 's' with the characters specified in
* 'set' removed from the beginning and the end of the string
* Example:					Example:
*	string - cbahahab			string - cbahah
*	set - abc					set - abc
*	returns: hah				returns: hah
* Parameters:
*	*s - string to be trimmed
*	*set - a set of characters to trim from 's'
* Returns;
*	The trimmed string
*	NULL if the allocation fails
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	int		j;
	int		end_index;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	end_index = ft_strlen(s1);
	while (s1[i] && ft_in_set(s1, set, i))
		i++;
	while (end_index > i && ft_in_set(s1, set, end_index - 1))
		end_index--;
	result = (char *)malloc((end_index - i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	while (i < end_index)
	{
		result[j] = s1[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
