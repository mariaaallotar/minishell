/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:15:30 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:21:40 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Applies the function ’f’ to each character of the string ’s’ to create a new
*	string resulting from successive applications of ’f’
* Parameters:
*	*s - string to apply f to
*	f - a function to apply to every character in string s
*		Parameters:
*			unsigned int - index of the char in s
*			char - the character to apply the function to
*		Returns:
*			a character
* Returns:
*	The string created from the successive applications of ’f’
*	New empty string if s is empty
*	NULL if the allocation fails
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	int		i;

	if (!s || !f)
		return (NULL);
	newstr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
