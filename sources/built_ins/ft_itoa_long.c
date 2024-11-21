/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:12:38 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/21 13:28:58 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_length(long n)
{
	int	len;

	len = 0;
	if (n / 10 > 0)
		len = ft_get_length(n / 10);
	len++;
	return (len);
}

static void	ft_divide_ten(long n, char *num_string, int index)
{
	char	temp;

	if (n / 10 > 0)
		ft_divide_ten(n / 10, num_string, index - 1);
	temp = n % 10 + 48;
	num_string[index] = temp;
}

static char	*ft_positive_num(long n)
{
	char	*num_string;
	int		num_length;

	num_length = 0;
	num_length = ft_get_length(n);
	num_string = (char *)malloc((num_length + 1) * sizeof(char));
	if (!num_string)
		return (NULL);
	ft_divide_ten(n, num_string, num_length - 1);
	num_string[num_length] = '\0';
	return (num_string);
}

static char	*ft_negative_num(long n)
{
	char	*num_string;
	int		num_length;

	num_length = 0;
	num_length = ft_get_length(-n);
	num_string = (char *)malloc((num_length + 2) * sizeof(char));
	if (!num_string)
		return (NULL);
	ft_divide_ten(-n, num_string, num_length);
	num_string[0] = '-';
	num_string[num_length + 1] = '\0';
	return (num_string);
}

char	*ft_itoa_long(long n)
{
	char	*num_string;

	if (n == LONG_MIN)
	{
		num_string = ft_negative_num(n + 1);
		if (!num_string)
			return (NULL);
		num_string[19] = '8';
	}
	else if (n >= 0)
		num_string = ft_positive_num(n);
	else
		num_string = ft_negative_num(n);
	return (num_string);
}
