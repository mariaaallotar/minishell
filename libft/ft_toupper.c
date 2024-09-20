/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:55:55 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:23:35 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Converts a lower-case letter to the corresponding upper-case letter
* Works only on characters in the standard ascii table (dec 0-127)
* Parameters: 
	c - int representation of a character
* Returns: 
	if c is lower-case: corresponding upper-case letter
	if c is NOT lower case: the argument unchanged
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
