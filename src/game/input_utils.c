/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:41:51 by layala-s          #+#    #+#             */
/*   Updated: 2025/05/23 10:41:52 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < MAX_KEYS)
		game->keys[keycode] = 1;
	if (keycode == XK_Escape)
		exit_game(game);
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < MAX_KEYS)
		game->keys[keycode] = 0;
	return (0);
}

void	key_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->mlx_win, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->mlx_win, 17, 1L << 2, exit_game, game);
}
