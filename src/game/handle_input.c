/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:33 by aurodrig          #+#    #+#             */
/*   Updated: 2025/05/19 19:20:16 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	move(t_game *g, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = g->player_x + dx;
	new_y = g->player_y + dy;
	if (ft_is_walkable(g->map, new_x, g->player_y))
		g->player_x = new_x;
	if (ft_is_walkable(g->map, g->player_x, new_y))
		g->player_y = new_y;
}

static void	rotate(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->dir_x;
	old_plane_x = g->plane_x;
	g->dir_x = g->dir_x * cos(angle) - g->dir_y * sin(angle);
	g->dir_y = old_dir_x * sin(angle) + g->dir_y * cos(angle);
	g->plane_x = g->plane_x * cos(angle) - g->plane_y * sin(angle);
	g->plane_y = old_plane_x * sin(angle) + g->plane_y * cos(angle);
}

void	handle_input(t_game *g)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.05;
	if (g->keys[XK_w])
		move(g, g->dir_x * move_speed, g->dir_y * move_speed);
	if (g->keys[XK_s])
		move(g, -g->dir_x * move_speed, -g->dir_y * move_speed);
	if (g->keys[XK_a])
		move(g, -g->plane_x * move_speed, -g->plane_y * move_speed);
	if (g->keys[XK_d])
		move(g, g->plane_x * move_speed, g->plane_y * move_speed);
	if (g->keys[XK_Left])
		rotate(g, -rot_speed);
	if (g->keys[XK_Right])
		rotate(g, rot_speed);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	static int	prev_x = -1;
	double		sensitivity;
	int			dx;

	sensitivity = 0.003;
	if (prev_x == -1)
		prev_x = x;
	dx = x - prev_x;
	if (dx != 0 && ft_abs(dx) < 100)
		rotate(game, dx * sensitivity);
	prev_x = x;
	(void)y;
	return (0);
}
