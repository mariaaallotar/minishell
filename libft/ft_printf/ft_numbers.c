/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:42:00 by eberkowi          #+#    #+#             */
/*   Updated: 2024/07/24 10:48:16 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	recursive_putnbr(int n, int fd)
{
	char	temp;
	int		count;
	int		write_error;

	write_error = 0;
	count = 0;
	if (n / 10 > 0)
		count = recursive_putnbr(n / 10, fd);
	if (count == -1)
		return (-1);
	count++;
	temp = (n % 10) + 48;
	write_error = write(fd, &temp, 1);
	if (write_error == -1)
		return (-1);
	return (count);
}

int	ft_putnbr2_fd(int n, int fd)
{
	int	count;
	int	temp;

	temp = 0;
	count = 0;
	if (n == -2147483648)
		temp = write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		temp = write(fd, "-", 1);
		if (temp == -1)
			return (-1);
		count++;
		n = -n;
		temp = recursive_putnbr(n, fd);
	}
	else
		temp = recursive_putnbr(n, fd);
	if (temp == -1)
		return (-1);
	count += temp;
	return (count);
}

int	recursive_putnbr_unsigned(long n, int fd)
{
	char	temp;
	int		count;
	int		write_error;

	write_error = 0;
	count = 0;
	if (n / 10 > 0)
		count = recursive_putnbr_unsigned(n / 10, fd);
	if (count == -1)
		return (-1);
	count++;
	temp = (n % 10) + 48;
	write_error = write(fd, &temp, 1);
	if (write_error == -1)
		return (-1);
	return (count);
}

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	int	count;

	count = 0;
	count = recursive_putnbr_unsigned(n, fd);
	return (count);
}
