/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:44:58 by layala-s          #+#    #+#             */
/*   Updated: 2025/05/20 23:23:49 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	tx_orientation(t_game *g, t_texture **tx, t_ray_data *r, t_draw_tex *d)
{
	if (r->side == 0 && r->ray_x > 0)
		*tx = &g->we;
	else if (r->side == 0 && r->ray_x < 0)
		*tx = &g->ea;
	else if (r->side == 1 && r->ray_y > 0)
		*tx = &g->no;
	else
		*tx = &g->so;
	if (r->side == 0)
		d->wall_x = g->player_y + r->perp_dist * r->ray_y;
	else
		d->wall_x = g->player_x + r->perp_dist * r->ray_x;
}

void	draw_texture(t_game *g, int x, t_ray_data *r)
{
	t_texture	*tx;
	t_draw_tex	d;

	tx_orientation(g, &tx, r, &d);
	d.wall_x -= floor(d.wall_x);
	d.tx_x = (int)(d.wall_x * (double)tx->width);
	if ((r->side == 0 && r->ray_x < 0) || (r->side == 1 && r->ray_y > 0))
		d.tx_x = tx->width - d.tx_x - 1;
	d.step = 1.0 * tx->heigth / r->line_height;
	d.tx_pos = (r->draw_start - g->win_height / 2 + r->line_height / 2) * \
				d.step;
	d.y = r->draw_start;
	while (d.y < r->draw_end)
	{
		d.tx_y = (int)d.tx_pos & (tx->heigth - 1);
		d.tx_pos += d.step;
		d.color = *(int *)(tx->addr + (d.tx_y * tx->size_line + d.tx_x * \
						(tx->bpp / 8)));
		put_pixel(g, x, d.y, d.color);
		d.y++;
	}
}
