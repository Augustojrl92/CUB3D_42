/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:35:24 by aurodrig          #+#    #+#             */
/*   Updated: 2025/05/12 19:25:15 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	calc_delta(t_ray_data *r)
{
	if (r->ray_x == 0.0)
		r->delta_x = 1e30;
	else
		r->delta_x = ft_abs(1.0 / r->ray_x);
	if (r->ray_y == 0.0)
		r->delta_y = 1e30;
	else
		r->delta_y = ft_abs(1.0 / r->ray_y);
}

static void	calc_step_side(t_game *game, t_ray_data *r)
{
	if (r->ray_x < 0.0)
	{
		r->step_x = -1;
		r->side_x = (game->player_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - game->player_x) * r->delta_x;
	}
	if (r->ray_y < 0.0)
	{
		r->step_y = -1;
		r->side_y = (game->player_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - game->player_y) * r->delta_y;
	}
}

static void	perform_dda(t_game *game, t_ray_data *r)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (game->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

static void	calc_line(t_game *game, t_ray_data *r)
{
	if (r->side == 0)
		r->perp_dist = (r->map_x - game->player_x \
			+ (1 - r->step_x) / 2.0) / r->ray_x;
	else
		r->perp_dist = (r->map_y - game->player_y \
			+(1 - r->step_y) / 2.0) / r->ray_y;
	r->line_height = (int)(game->win_height / r->perp_dist);
	r->draw_start = -r->line_height / 2 + game->win_height / 2;
	r->draw_end = r->line_height / 2 + game->win_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= game->win_height)
		r->draw_end = game->win_height - 1;
}

void	raycast(t_game *game)
{
	int				x;
	t_ray_data		r;

	x = 0;
	while (x < game->win_width)
	{
		init_ray(game, &r, x);
		calc_delta(&r);
		calc_step_side(game, &r);
		perform_dda(game, &r);
		calc_line(game, &r);
		draw_slice(game, &r, x);
		x++;
	}
}
