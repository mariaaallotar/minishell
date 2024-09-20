/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:12:11 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:16:05 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Determines if a character is a digit
* Works only on characters in the standard ascii table (dec 0-127)
* Parameters: 
	c - int representation of a character
* Returns: 
	1 - if c is a digit
	0 - otherwise
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
