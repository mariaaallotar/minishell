/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:51:41 by eberkowi          #+#    #+#             */
/*   Updated: 2024/04/26 15:33:39 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		j;
	size_t	len;

	len = (ft_strlen((char *)src));
	if (dstsize <= ft_strlen(dst))
		len += dstsize;
	else
		len += ft_strlen(dst);
	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (i + 1 < dstsize && src[j])
	{
		dst[i++] = src[j++];
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (len);
}
