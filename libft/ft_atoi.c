/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:54 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/20 16:27:12 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Converts the initial portion of the string pointed to by str to
*	int representation.
* Parameters:
*	*str - string of numbers to convert to int
* Returns:
*	The number in int representation
* Note:
*	When INT overflows or underflows the function keeps returning numbers, 
*		when LONG overflows the function returns -1 and when LONG underflows
*		the function returns 0
*/
int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	result = 0;
	while (*str && ft_isdigit(*str))
	{
		result = (result * 10) + sign * (*str - '0');
		if (sign == 1 && result < 0)
			return (-1);
		else if (sign == -1 && result > 0)
			return (0);
		str++;
	}
	return ((int)result);
}
