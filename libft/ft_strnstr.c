/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:15 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:22:17 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_needle(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*haystack != *needle)
			return (0);
		haystack++;
		needle++;
	}
	return (1);
}

/**
* Locates the first occurrence of the null-terminated string needle in the
*	string haystack, where not more than len characters are searched
* Parameters:
*	*haystack - string to search from
*	*needle - string to find in haystack
*	len - amount of characters to search from (at most)
* Returns:
*	*haystack - needle is an empty string
*	NULL - needle occurs nowhere in haystack
*	pointer to the first character of the first occurrence of needle
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len >= ft_strlen(needle))
	{
		if (ft_find_needle(haystack, needle))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
