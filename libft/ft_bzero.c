/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:07:52 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:13:58 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Writes n zeroed bytes ('\0') to the string s
* Parameters: 
*	*s - string to write zeroed bytes to
*	n - amount of bytes to write (must be non-negaitve value)
* Note:
*	Bevaior undefined if n is bigger than size of s
*/
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = 0;
		ptr++;
	}
}
