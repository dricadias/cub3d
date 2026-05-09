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

static char	*g_stored = NULL; //dont know if i can have this based on 42 rules (norminette)

static char	*ft_free(char *ptr)
{
	if (ptr)
		free(ptr);
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
		{
			printf("Error\nRead error: %s\n", strerror(errno));
			return (ft_free(stored));
		}
		if (byt_read == 0)
			break ;
		buffer[byt_read] = '\0';
		if (!stored)
			stored = ft_strdup("");
		if (!stored)
			return (NULL);
		temp = stored;
		stored = ft_strjoin(temp, buffer);
		ft_free(temp);
		if (!stored)
			return (NULL);
	}
	return (stored);
}

static char	*extract_line(char *stored)
{
	char	*updated;
	int		i;

	i = 0;
	if (!stored || !*stored)
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		i++;
	updated = ft_substr(stored, i, ft_strlen(stored) - i);
	if (updated && *updated == '\0')
		updated = ft_free(updated);
	stored[i] = '\0';
	return (updated);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		printf("Error\nBuffer allocation failed in GNL\n");
		return (NULL);
	}

	line = read_and_save(fd, g_stored, buffer);
	free(buffer);

	if (!line)
	{
		g_stored = NULL;
		return (NULL);
	}

	g_stored = extract_line(line);
	return (line);
}

// ✅ NEW: Cleanup function for GNL
void	gnl_cleanup(void)
{
	if (g_stored)
	{
		free(g_stored);
		g_stored = NULL;
	}
}