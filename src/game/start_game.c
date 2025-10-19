/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:51:33 by aurodrig          #+#    #+#             */
/*   Updated: 2025/05/21 01:24:07 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	game_loop(t_game *game)
{
	handle_input(game);
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img, 0, 0);
	return (0);
}

void	free_game(t_game *g)
{
	int	i;

	i = 0;
	free(g->e->ea_tx);
	free(g->e->we_tx);
	free(g->e->so_tx);
	free(g->e->no_tx);
	free(g->e->c_rgb);
	free(g->e->f_rgb);
	free(g->e);
	while (i < 6)
		free(g->elements[i++]);
	i = 0;
	while (g->map[i])
		free(g->map[i++]);
	free(g->map);
	free(g->mini);
	free(g->elements);
	free(g);
}

int	exit_game(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->no.img);
	mlx_destroy_image(game->mlx_ptr, game->ea.img);
	mlx_destroy_image(game->mlx_ptr, game->so.img);
	mlx_destroy_image(game->mlx_ptr, game->we.img);
	mlx_destroy_image(game->mlx_ptr, game->img);
	mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free_game(game);
	exit(EXIT_SUCCESS);
}

int	load_texture(t_game *game, t_texture *tx, char *path)
{
	tx->img = mlx_xpm_file_to_image(game->mlx_ptr, path, \
		&tx->width, &tx->heigth);
	if (!tx->img)
		return (1);
	tx->addr = mlx_get_data_addr(tx->img, &tx->bpp, \
		&tx->size_line, &tx->endian);
	return (0);
}

void	start_game(t_game *game)
{
	validate_rgb(game);
	get_position(game);
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit(1);
	if (get_textures(game))
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		exit_error("Error: can't find texture", 1, game);
	}
	game->mlx_win = mlx_new_window(game->mlx_ptr, game->win_width, \
		game->win_height, "cub3D");
	if (!game->mlx_win)
		exit(1);
	game->img = mlx_new_image(game->mlx_ptr, game->win_width, game->win_height);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, \
		&game->endian);
	key_hooks(game);
	mlx_loop_hook(game->mlx_ptr, game_loop, game);
	mlx_loop(game->mlx_ptr);
}
