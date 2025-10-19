/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:10 by aurodrig          #+#    #+#             */
/*   Updated: 2025/05/21 00:35:55 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	static int	once;
	char		*dst;

	once = 1;
	if (once)
	{
		once = 0;
	}
	if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
		return ;
	dst = game->img_data + y * game->size_line + x * (game->bpp / 8);
	*(unsigned int *)dst = (unsigned int)color;
}

void	validate_rgb(t_game *game)
{
	char	**f_rgb;
	char	**c_rgb;

	f_rgb = get_rgb(game->e->f_rgb);
	check_rgb(f_rgb, game);
	free_rgb(f_rgb);
	c_rgb = get_rgb(game->e->c_rgb);
	check_rgb(c_rgb, game);
	free_rgb(c_rgb);
}
