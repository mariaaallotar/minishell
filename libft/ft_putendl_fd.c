/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:16:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:18:44 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Outputs the string ’s’ to the given file descriptor followed by a newline
* Parameters:
*	*s - string to output
*	fd - filedescriptor on which to write
*/
void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, &*s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
