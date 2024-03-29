/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-alo <sait-alo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:18:10 by sait-alo          #+#    #+#             */
/*   Updated: 2024/03/07 21:18:13 by sait-alo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static	t_xpm	*create_image(t_map	*mlx, char *path)
{
	t_xpm	*asset;

	asset = malloc(sizeof(t_xpm));
	if (!asset)
		return (NULL);
	*asset = (t_xpm){0};
	asset->path = path;
	asset->xpm_data = mlx_xpm_file_to_image(mlx->ptr, asset->path,
			&asset->width, &asset->height);
	return (asset);
}

/* Function to initalize all the assets and make theme ready to push*/
void	init_xpm(t_map *game)
{
	game->king[0] = create_image(game, "./assets/king-right.xpm");
	game->king[1] = create_image(game, "./assets/king-left.xpm");
	game->king[2] = create_image(game, "./assets/king-heart-right.xpm");
	game->king[3] = create_image(game, "./assets/king-heart-left.xpm");
	game->princess_exit[0] = create_image(game, "./assets/princess-left.xpm");
	game->princess_exit[1] = create_image(game, "./assets/EXIT-LEFT-0.xpm");
	game->princess_exit[2] = create_image(game, "./assets/princess-right.xpm");
	game->princess_exit[3] = create_image(game, "./assets/EXIT-RIGHT-0.xpm");
	game->bg = create_image(game, "./assets/bg.xpm");
	game->wall = create_image(game, "./assets/wall.xpm");
	game->collectible = create_image(game, "./assets/c1.xpm");
}
