/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:12:01 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:15:54 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Determines if a character is an standard ascii character (dec 0-127)
* Parameters: 
	c - int representation of a character
* Returns: 
	1 - if c is part of ascii table
	0 - otherwise
*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
