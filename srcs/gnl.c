/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:55:04 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 13:55:04 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

static char	*ft_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*read_and_save(int fd, char *stored, char *buffer)
{
	int		byt_read;
	char	*temp;

	byt_read = 1;
	while (byt_read > 0 && (!stored || !ft_strchr(stored, '\n')))
	{
		byt_read = read(fd, buffer, BUFFER_SIZE);
		if (byt_read == -1)
			return (ft_free(&stored));
		if (byt_read == 0)
			break ;
		buffer[byt_read] = '\0';
		if (!stored)
			stored = ft_strdup("");
		if (!stored)
			return (NULL);
		temp = stored;
		stored = ft_strjoin(temp, buffer);
		free(temp);
		if (!stored)
			return (NULL);
	}
	return (stored);
}

static char	*extract_line(char **stored_ptr)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	if (!*stored_ptr || !**stored_ptr)
		return (NULL);
	while ((*stored_ptr)[i] && (*stored_ptr)[i] != '\n')
		i++;
	if ((*stored_ptr)[i] == '\n')
		i++;
	line = ft_substr(*stored_ptr, 0, i);
	tmp = ft_substr(*stored_ptr, i, ft_strlen(*stored_ptr) - i);
	free(*stored_ptr);
	*stored_ptr = tmp;
	if (*stored_ptr && **stored_ptr == '\0')
		ft_free(stored_ptr);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stored = read_and_save(fd, stored, buffer);
	free(buffer);
	if (!stored)
		return (NULL);
	line = extract_line(&stored);
	return (line);
}

void	gnl_cleanup(void)
{
	get_next_line(-1);
}
