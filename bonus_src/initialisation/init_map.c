/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:17:36 by sait-alo          #+#    #+#             */
/*   Updated: 2024/03/07 21:17:40 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static	int	push_image(t_map *game, t_xpm *image, int x, int y)
{
	image->x = x * 60;
	image->y = y * 60;
	return (mlx_put_image_to_window(game->ptr, game->win, image->xpm_data,
			image->x, image->y));
}

static	void	push_player_image(t_map *game, int x, int y)
{
	if (game->view_ == 0)
	{
		if (game->map_lines[y][x + 1] == 'E' &&
			(game->collected == game->c_count))
			push_image(game, game->king_right[2], x, y);
		else
			push_image(game, game->king_right[game->king_frame], x, y);
	}
	else
	{
		if (game->map_lines[y][x - 1] == 'E' &&
			(game->collected == game->c_count))
			push_image(game, game->king_left[2], x, y);
		else
			push_image(game, game->king_left[game->king_frame], x, y);
	}
}

static	void	push_exit_image(t_map *game, int x, int y)
{
	if (game->player_x <= x)
	{
		if ((game->c_count == game->collected) && !game->death_flag)
		{
			push_image(game, game->exit_left[game->exit_frame], x, y);
			push_image(game, game->exit_idle_left[game->princess_frame], x, y);
		}
		else
			push_image(game, game->exit_left[0], x, y);
	}
	else
	{
		if ((game->c_count == game->collected) && !game->death_flag)
		{
			push_image(game, game->exit_right[game->exit_frame], x, y);
			push_image(game, game->exit_idle_right[game->princess_frame], x, y);
		}
		else
			push_image(game, game->exit_right[0], x, y);
	}
}

static	void	check_element_and_push(t_map *game, int x, int y, char element)
{
	if (element == '0')
		push_image(game, game->bg, x, y);
	else if (element == '1')
		push_image(game, game->wall, x, y);
	else if (element == 'C')
		push_image(game, game->collectible, x, y);
	else if (element == 'E')
		push_exit_image(game, x, y);
	else if (element == 'P')
	{
		push_player_image(game, x, y);
		if (game->death_flag == 1)
			push_image(game, game->king_death[game->death_frame], x, y);
	}
	else if (element == 'W')
	{
		if (game->enemy_reach_left == 1)
			push_image(game, game->enemy[1], x, y);
		else
			push_image(game, game->enemy[0], x, y);
	}
}

void	init_map(t_map *game)
{
	int		x;
	int		y;
	
	y = 0;
	while (game->map_lines[y])
	{
		x = 0;
		while (game->map_lines[y][x])
		{
			check_element_and_push(game, x, y, game->map_lines[y][x]);
			x++;
		}
		y++;
	}
	game->moves = ft_itoa(game->player_moves);
	mlx_string_put(game->ptr, game->win, 30,
		(game->height * 60) - 30, 0xF0B207, "King Moves :");
	mlx_string_put(game->ptr, game->win, 120,
		(game->height * 60) - 29, 0xF0B207, game->moves);
	free(game->moves);
}
