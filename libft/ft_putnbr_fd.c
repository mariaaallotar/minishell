/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:16:29 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:19:10 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rec_div(int n, int fd)
{
	char	temp;

	if (n / 10 > 0)
		ft_rec_div(n / 10, fd);
	temp = (n % 10) + 48;
	write(fd, &temp, 1);
}

/**
* Outputs the integer ’n’ to the given file descriptor
* Parameters:
*	n - number to output
*	fd - filedescriptor on which to write
*/
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		ft_rec_div(n, fd);
	}
	else
		ft_rec_div(n, fd);
}
