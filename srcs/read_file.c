/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:57:54 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 13:57:54 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	trim_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

static char	**add_line(char **arr, char *line, int count)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
	{
		printf("Error\nMemory allocation failed for file array\n");
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = line;
	new[i + 1] = NULL;
	if (arr)
		free(arr);
	return (new);
}

char	**read_file(char *filename)
{
	int		fd;
	char	*line;
	char	**file;
	int		count;

	/* nunca entra aqui ja viu argc
	if (!filename || !*filename)
		return (printf("Error\nNo filename provided\n"), NULL);
	*/
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open file: %s\n", strerror(errno)), NULL);
	file = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		file = add_line(file, line, count);
		if (!file)
		{
			free(line);
			close(fd);
			return (NULL);
		}
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	if (!file) //funciona!
		return (printf("Error\nEmpty file or reading error\n"), NULL);
	return (file);
}

//esta aqui mas é validation!!!!!!!111
int	is_map(char *line)
{
	int	i;
	int	has_map_char;

	if (!line || !*line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (0);
	i = 0;
	has_map_char = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (0);
		if (ft_strchr("01NSEW", line[i]))
			has_map_char = 1;
		i++;
	}
	return (has_map_char);
}

int	map_index(char **file)
{
	int	i;

	if (!file)
		return (-1);
	i = 0;
	while (file[i])
	{
		if (is_map(file[i]))
			return (i);
		i++;
	}
	return (-1);
}
