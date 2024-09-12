/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:42:11 by eberkowi          #+#    #+#             */
/*   Updated: 2024/07/24 10:48:23 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(char *str, ...);
int	ft_putchar_fd(int c, int fd);
int	ft_putstr_fd(char *s, int fd);
int	ft_itoh(unsigned int i, int fd, char x_or_X);
int	ft_ptoh(size_t i, int fd);
int	ft_putnbr2_fd(int n, int fd);
int	ft_putnbr_unsigned_fd(unsigned int n, int fd);

#endif
