/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fonctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:00:56 by sait-alo          #+#    #+#             */
/*   Updated: 2024/02/28 22:01:03 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	extension_check(char *map_path)
{
	char	*extention;

	if (!map_path)
		return (0);
	extention = ft_strrchr(map_path, '.');
	if (!extention)
		return (0);
	if (ft_strlen(extention) != 4)
		return (0);
	if (ft_strncmp(extention, ".ber", 4) == 0)
		return (1);
	return (0);
}

char	*read_map(int fd, t_map *map)
{
	char	*current_line;
	char	*full_line;
	char	*tmp;

	full_line = NULL;
	current_line = get_next_line(fd);
	if (!current_line)
		error("Invalid map : Empty map!");
	map->width = ft_strlen_read(current_line);
	if (map->width > (map->display_width / 60))
		error_read("Can't Open, Too big width", full_line, current_line);
	while (current_line)
	{
		tmp = full_line;
		read_errors_check(map, current_line, tmp);
		map->height++;
		if (map->height > map->display_height / 60)
			error_read("Can't Open, Too big map height", tmp, current_line);
		full_line = ft_strjoin(tmp, current_line);
		free(tmp);
		free(current_line);
		current_line = get_next_line(fd);
	}
	return (full_line);
}

/* Function to check if the map has only one player, one exit,
and at least one collectible */
int	component_check(char **map_lines, t_map *map)
{
	int	x;
	int	y;
	int	flag;

	y = 0;
	flag = 0;
	while (map_lines[y])
	{
		x = 0;
		while (map_lines[y][x])
		{
			if (map_lines[y][x] == 'P')
				save_cords_and_count(map, x, y);
			else if (map_lines[y][x] == 'E')
				map->e_count++;
			else if (map_lines[y][x] == 'C')
				map->c_count++;
			else if (not_valid_component(map_lines[y][x], map))
				flag = 1;
			x++;
		}
		y++;
	}
	check_result(flag, map, map_lines);
	return (0);
}

int	wall_check(char **map_lines, t_map *map)
{
	int	x;
	int	y;
	int	len;

	y = 0;
	len = 0;
	while (map_lines[y])
	{
		len = ft_strlen(map_lines[y]);
		if (len < 3 || map_lines[y][0] != '1' || map_lines[y][len - 1] != '1')
			error_map("Invalid map : Missing walls in edges", map_lines, map);
		if (y == 0 || map_lines[y + 1] == NULL)
		{
			x = 0;
			while (map_lines[y][x])
			{
				if (map_lines[y][x] != '1')
					error_map("Invalid map:Missing top/down walls",
						map_lines, map);
				x++;
			}
		}
		y++;
	}
	return (0);
}
