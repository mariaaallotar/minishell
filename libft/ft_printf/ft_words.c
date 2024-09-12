/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:42:00 by eberkowi          #+#    #+#             */
/*   Updated: 2024/05/15 13:44:07 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd(int c, int fd)
{
	unsigned char	temp;
	int				count;

	temp = (unsigned char)c;
	count = write(fd, &temp, 1);
	if (count == -1)
		return (-1);
	else
		return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	count;
	int	temp;

	temp = 0;
	if (!s)
	{
		temp = write(fd, "(null)", 6);
		if (temp == -1)
			return (-1);
		return (6);
	}
	count = 0;
	while (*s)
	{
		temp = write(fd, &*s, 1);
		if (temp == -1)
			return (-1);
		count++;
		s++;
	}
	return (count);
}

int	ft_itoh(unsigned int i, int fd, char x_or_X)
{
	char	*str;
	int		temp;
	int		count;

	if (x_or_X == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	count = 0;
	if (i >= 16)
	{
		count = ft_itoh(i / 16, fd, x_or_X);
		if (count == -1)
			return (-1);
		temp = write(fd, &str[i % 16], 1);
	}
	else
		temp = write(fd, &str[i], 1);
	if (temp == -1)
		return (-1);
	count++;
	return (count);
}

int	recursive_ptoh(size_t i, int fd, char x_or_X)
{
	char	*str;
	int		temp;
	int		count;

	if (x_or_X == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	count = 0;
	if (i >= 16)
	{
		count = recursive_ptoh(i / 16, fd, x_or_X);
		if (count == -1)
			return (-1);
		temp = write(fd, &str[i % 16], 1);
	}
	else
		temp = write(fd, &str[i], 1);
	if (temp == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_ptoh(size_t i, int fd)
{
	int	count;
	int	temp;

	count = 0;
	count = write(fd, "0x", 2);
	if (count == -1)
		return (-1);
	temp = recursive_ptoh(i, fd, 'x');
	if (temp == -1)
		return (-1);
	count += temp;
	return (count);
}
