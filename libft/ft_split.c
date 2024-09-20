/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:34:30 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 15:19:42 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	num_words;

	num_words = 0;
	while (*s)
	{
		if (*s != c)
		{
			num_words++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (num_words);
}

static int	ft_word_len(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != c && *s)
	{
		count++;
		s++;
	}
	return (count);
}

static char	*ft_place_word(char *result, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		result[i] = *s;
		i++;
		s++;
	}
	result[i] = '\0';
	return (result);
}

static char	**ft_free_all(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (0);
}

/**
* Allocates and returns an array of strings obtained by splitting 's' using
*	the character 'c' as a delimiter. The array must end with a NULL pointer
* Parameters:
*	*s - string to be split
*	c - delimiter character
* Returns:
*	Array of new strings resulting from the split
*	NULL if the allocation fails
*/
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = (char *)malloc(ft_word_len(s, c) + 1);
			if (result[i] == NULL)
				return (ft_free_all(result, i));
			ft_place_word(result[i++], s, c);
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	result[i] = 0;
	return (result);
}
