/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:28:57 by sait-alo          #+#    #+#             */
/*   Updated: 2024/03/13 15:28:59 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	free_map(char **map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	save_cords_and_count(t_map *map, int x, int y)
{
	map->p_count++;
	map->player_x = x;
	map->player_y = y;
}

int	not_valid_component(char c, t_map *map)
{
	if (c == 'W')
		map->w_count++;
	return (c != 'E' && c != 'P' && c != 'C'
		&& c != '1' && c != '0' && c != 'W');
}

void	read_errors_check(t_map *map, char *current_line, char *tmp)
{
	if (!ft_strncmp(current_line, "\n", 1))
		error_read("Invalid map: Empty line detected", tmp, current_line);
	else if (ft_strlen_read(current_line) != map->width)
		error_read("Invalid map: Map not rectangular!", tmp, current_line);
}
