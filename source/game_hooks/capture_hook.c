/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:42:38 by sait-alo          #+#    #+#             */
/*   Updated: 2024/03/13 15:42:43 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static	void	destroy_xpm(t_map *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(game->ptr, game->king[i]->xpm_data);
		mlx_destroy_image(game->ptr, game->princess_exit[i++]->xpm_data);
	}
	mlx_destroy_image(game->ptr, game->bg->xpm_data);
	mlx_destroy_image(game->ptr, game->wall->xpm_data);
	mlx_destroy_image(game->ptr, game->collectible->xpm_data);
}

static	void	free_xpm(t_map *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(game->princess_exit[i]);
		free(game->king[i++]);
	}
	free(game->wall);
	free(game->bg);
	free(game->collectible);
}

int	exit_game(t_map *game)
{
	free_map(game->map_lines);
	destroy_xpm(game);
	free_xpm(game);
	mlx_destroy_window(game->ptr, game->win);
	mlx_destroy_display(game->ptr);
	free(game->ptr);
	exit(0);
	return (0);
}

static	int	game_events(int pressed_key, t_map *game)
{
	if (pressed_key == ESC)
		exit_game(game);
	else if (pressed_key == W)
		move_player(game, UP);
	else if (pressed_key == S)
		move_player(game, DOWN);
	else if (pressed_key == D)
		move_player(game, RIGHT);
	else if (pressed_key == A)
		move_player(game, LEFT);
	return (0);
}

void	capture_hook(t_map *game)
{
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_hook(game->win, 2, (1L << 0), game_events, game);
}
