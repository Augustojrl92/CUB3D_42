/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:52:12 by aurodrig          #+#    #+#             */
/*   Updated: 2025/05/20 23:46:23 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_ray(t_game *game, t_ray_data *r, int x)
{
	r->camera_x = 2.0 * x / game->win_width - 1.0;
	r->ray_x = game->dir_x + game->plane_x * r->camera_x;
	r->ray_y = game->dir_y + game->plane_y * r->camera_x;
	r->map_x = (int)game->player_x;
	r->map_y = (int)game->player_y;
}

void	draw_vertical_line(t_game *game, int x, int y0, int y1)
{
	int	y;

	if (y0 < 0)
		y0 = 0;
	if (y1 >= game->win_height)
		y1 = game->win_height - 1;
	y = y0;
	while (y <= y1)
	{
		put_pixel(game, x, y, game->color);
		y++;
	}
}

void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

void	draw_slice(t_game *game, t_ray_data *r, int x)
{
	char	**rgb_c;
	char	**rgb_f;

	rgb_c = get_rgb(game->e->c_rgb);
	game->color = parse_rgb(rgb_c);
	draw_vertical_line(game, x, 0, r->draw_start - 1);
	draw_texture(game, x, r);
	rgb_f = get_rgb(game->e->f_rgb);
	game->color = parse_rgb(rgb_f);
	draw_vertical_line(game, x, r->draw_end + 1, game->win_height - 1);
	free_rgb(rgb_c);
	free_rgb(rgb_f);
}
