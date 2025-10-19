/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:30:00 by aurodrig          #+#    #+#             */
/*   Updated: 2025/05/21 01:09:36 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_square(t_game *game, int sx, int sy, int color)
{
	int	dy;
	int	dx;

	dy = 0;
	while (dy < game->minimap_scale)
	{
		dx = 0;
		while (dx < game->minimap_scale)
		{
			put_pixel(game, sx + dx, sy + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	draw_player(t_game *game)
{
	int	px;
	int	py;
	int	dot_size;

	px = (int)(game->player_x * game->minimap_scale) + MINIMAP_MARGIN;
	py = (int)(game->player_y * game->minimap_scale) + MINIMAP_MARGIN;
	dot_size = game->minimap_scale / 2;
	draw_square(game, px - dot_size / 2, py - dot_size / 2, 0xFF0000);
}

void	get_minimap_vals(t_game *game)
{
	game->mini->row = 0;
	game->mini->map_rows = 0;
	game->mini->map_cols = ft_strlen(game->map[0]);
	game->mini->max_width = game->win_width * MINIMAP_PERCENTAGE;
	game->mini->max_height = game->win_height * MINIMAP_PERCENTAGE;
	while (game->map[game->mini->map_rows])
		game->mini->map_rows++;
	game->mini->scale_x = game->mini->max_width / game->mini->map_cols;
	game->mini->scale_y = game->mini->max_height / game->mini->map_rows;
	if (game->mini->scale_x < game->mini->scale_y)
		game->minimap_scale = game->mini->scale_x;
	else
		game->minimap_scale = game->mini->scale_y;
	if (game->minimap_scale < 1)
		game->minimap_scale = 1;
}

void	draw_minimap(t_game *game)
{
	int	color;

	get_minimap_vals(game);
	while (game->map[game->mini->row])
	{
		game->mini->col = 0;
		while (game->map[game->mini->row][game->mini->col])
		{
			game->mini->sx = game->mini->col * \
								game->minimap_scale + MINIMAP_MARGIN;
			game->mini->sy = game->mini->row * \
								game->minimap_scale + MINIMAP_MARGIN;
			if (game->map[game->mini->row][game->mini->col] == '1')
				color = 0xFFFFFF;
			else if (game->map[game->mini->row][game->mini->col] == '0')
				color = 0x000000;
			else
				color = 0x696969;
			draw_square(game, game->mini->sx, game->mini->sy, color);
			game->mini->col++;
		}
		game->mini->row++;
	}
	draw_player(game);
}
