/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:47:39 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:20:23 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Allocates sufficient memory for a copy of the string s1, does the copy,
*	and returns a pointer to it.  The pointer may subsequently be used as an
*	argument to the function free
* Parametes:
*	*s1 - string to duplicate
* Returns:
*	Pointer to the duplicated string
*/
char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	s2 = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
