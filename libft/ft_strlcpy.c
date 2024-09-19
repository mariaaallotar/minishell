/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:51:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:21:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Copies up to (dstsize - 1) characters from the string src to dst,
* 	NUL-terminating the result if dstsize is not 0.
* If the src and dst strings overlap, the behavior is undefined.
* Parameters:
*	*dst - the destination to copy to
*	*src - the source to copy from
*	dstsize - the size of dst memory
* Returns:
*	The size of the string it tried to copy, in practice the size of src
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
