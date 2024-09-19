/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:55:34 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:23:15 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Allocates and returns a substring from the string 's'
* Parameters:
*	*s - string to create substring from
*	start - start index of the substring in the string 's'
*	len - maximum length of the substring (NOT including '\0')
* Returns:
*	The substring
*	NULL if allocation fails or 's' is NULL
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*sub;
	size_t	s_length;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if ((size_t)start > s_length)
	{
		sub = (char *)malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = 0;
		return (sub);
	}
	if ((s_length - (size_t)start) < len)
		len = s_length - (size_t)start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (len-- > 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
