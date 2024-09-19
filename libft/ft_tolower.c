/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:55:46 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:23:25 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Converts an upper-case letter to the corresponding lower-case letter
* Works only on characters in the standard ascii table (dec 0-127)
* Parameters: 
	c - int representation of a character
* Returns: 
	if c is upper-case: corresponding lower-case letter
	if c is NOT upper case: the argument unchanged
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
