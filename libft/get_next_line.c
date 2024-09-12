/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:44:24 by eberkowi          #+#    #+#             */
/*   Updated: 2024/07/24 11:20:44 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_null(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static int	get_result_length(char *storage)
{
	int	count;

	count = 0;
	while (storage[count] && storage[count] != '\n')
		count++;
	if (storage[count] == '\n')
		count++;
	return (count);
}

static char	*add_buffer(char *storage, char *buffer, ssize_t read_size)
{
	char	*temp;

	if (read_size == 0)
	{
		if (*storage == 0)
			free_null(&storage);
		return (storage);
	}
	buffer[read_size] = '\0';
	temp = ft_strdup(storage);
	free_null(&storage);
	if (!temp)
		return (NULL);
	storage = ft_strjoin(temp, buffer);
	free_null(&temp);
	if (!storage)
		return (NULL);
	if (*storage == 0)
		free_null(&storage);
	return (storage);
}

static char	*fill_storage(int fd, char *storage)
{
	char	buffer[BUF_SIZE + 1];
	ssize_t	read_size;

	read_size = 1;
	if (!storage)
	{
		storage = ft_strdup("");
		if (!storage)
			return (NULL);
	}
	while (read_size > 0 && !ft_strchr(storage, '\n'))
	{
		read_size = read(fd, buffer, BUF_SIZE);
		if (read_size == -1)
			return (free_null(&storage));
		storage = add_buffer(storage, buffer, read_size);
		if (!storage)
			return (NULL);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*result;
	char		*temp;
	size_t		result_length;

	if (fd < 0 || BUF_SIZE <= 0)
		return (NULL);
	result = NULL;
	temp = NULL;
	storage = fill_storage(fd, storage);
	if (!storage)
		return (NULL);
	result_length = get_result_length(storage);
	result = ft_substr(storage, 0, result_length);
	if (!result)
		return (free_null(&storage));
	temp = ft_strdup(storage + (result_length));
	free_null(&storage);
	if (!temp)
		return (free_null(&result));
	storage = ft_strdup(temp);
	free_null(&temp);
	if (!storage)
		return (free_null(&result));
	return (result);
}
