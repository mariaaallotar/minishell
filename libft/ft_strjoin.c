/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:50:01 by eberkowi          #+#    #+#             */
/*   Updated: 2024/05/03 13:38:47 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
