/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:58 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:18:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Outputs the character ’c’ to the given file descriptor
* Parameters:
*	c - character to output
*	fd - filedescriptor of where to output
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
