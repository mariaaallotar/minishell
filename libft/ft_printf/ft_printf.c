/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:41:29 by eberkowi          #+#    #+#             */
/*   Updated: 2024/07/24 10:48:13 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	flags(char index, int fd, va_list *args)
{
	int	count;

	count = 0;
	if (index == 'c')
		count = ft_putchar_fd(va_arg(*args, int), fd);
	else if (index == 's')
		count = ft_putstr_fd(va_arg(*args, char *), fd);
	else if (index == 'p')
		count = ft_ptoh(va_arg(*args, size_t), fd);
	else if (index == 'd' || index == 'i')
		count = ft_putnbr2_fd(va_arg(*args, int), fd);
	else if (index == 'u')
		count = ft_putnbr_unsigned_fd(va_arg(*args, unsigned int), fd);
	else if (index == 'x')
		count = ft_itoh(va_arg(*args, unsigned int), fd, 'x');
	else if (index == 'X')
		count = ft_itoh(va_arg(*args, unsigned int), fd, 'X');
	else if (index == '%')
		count = write(fd, "%%", 1);
	else
		return (0);
	return (count);
}

int	ft_printf(char *str, ...)
{
	int		i;
	int		fd;
	int		count;
	int		final_count;
	va_list	args;

	va_start(args, str);
	final_count = 0;
	fd = 1;
	i = 0;
	while (str[i])
	{
		count = 0;
		if (str[i] == '%')
			count = flags(str[++i], fd, &args);
		else
			count = write(fd, &str[i], 1);
		if (count == -1)
			return (-1);
		final_count += count;
		i++;
	}
	va_end(args);
	return (final_count);
}
