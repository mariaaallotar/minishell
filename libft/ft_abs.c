/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:40:58 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:13:25 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculates the absolute value of the number given as a parameter
 * 
 * @param nb number to calculate absolute value of
 * @returns the absolute value of the number
 */
int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}
