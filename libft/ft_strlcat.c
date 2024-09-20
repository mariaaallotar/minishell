/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:51:41 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:21:03 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Appends (concatenate) string src to the end of dst
*	It will append at most dstsize - strlen(dst) - 1 characters.  
*	It will then NUL-terminate, unless dstsize is 0 or the original dst string
*	was longer than dstsize
* If the src and dst strings overlap, the behavior is undefined.
* Parameters:
*	*dst - the destination to append to
*	*src - the source to copy from
*	dstsize - the size of dst memory
* Returns:
*	The size of the string it tried to create, in practice the initial length
*		of dst plus the length of src
*/
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
