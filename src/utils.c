/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:57:24 by layala-s          #+#    #+#             */
/*   Updated: 2025/05/21 00:27:35 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_element_value(char *s, int n, t_game *g)
{
	int	i;

	i = 0;
	if (n == 3)
	{
		if (!check_extension(s, ".xpm"))
		{
			exit_error("Error: texture file should be <texture_path.xpm>", \
			1, g);
		}
	}
	if (n == 2)
	{
		while (s[i])
		{
			if (s[i] == '-' || (ft_isalpha(s[i])))
				exit_error("Error: RGB should have positive numeric values", \
				1, g);
			i++;
		}
	}
}

void	init_elements(char **str, char *element, int n, t_game *g)
{
	char	*s;

	*str = malloc(ft_strlen(element) + 1);
	if (!(*str))
		return ;
	s = *str;
	copy_str(*str, element, n);
	check_element_value(s, n, g);
}

void	exit_error(char *msg, int code_free, t_game *g)
{
	printf("%s\n", msg);
	if (code_free == 1)
	{
		safe_free(g);
		if (g->map)
			free(g->map);
		if (g->e)
			free(g->e);
		if (g->elements)
			free(g->elements);
		if (g->mini)
			free(g->mini);
		free(g);
	}
	exit(EXIT_FAILURE);
}

int	get_textures(t_game *game)
{
	if (load_texture(game, &game->no, game->e->no_tx) != 0)
		return (1);
	if (load_texture(game, &game->so, game->e->so_tx) != 0)
	{
		mlx_destroy_image(game->mlx_ptr, game->no.img);
		return (1);
	}
	if (load_texture(game, &game->ea, game->e->ea_tx) != 0)
	{
		mlx_destroy_image(game->mlx_ptr, game->no.img);
		mlx_destroy_image(game->mlx_ptr, game->so.img);
		return (1);
	}
	if (load_texture(game, &game->we, game->e->we_tx) != 0)
	{
		mlx_destroy_image(game->mlx_ptr, game->no.img);
		mlx_destroy_image(game->mlx_ptr, game->ea.img);
		mlx_destroy_image(game->mlx_ptr, game->so.img);
		return (1);
	}
	return (0);
}

void	safe_free(t_game *g)
{
	int	i;

	if (!g)
		return ;
	if (g->map)
	{
		i = 0;
		while (g->map[i])
			free(g->map[i++]);
	}
	if (g->e)
	{
		free(g->e->ea_tx);
		free(g->e->we_tx);
		free(g->e->so_tx);
		free(g->e->no_tx);
		free(g->e->c_rgb);
		free(g->e->f_rgb);
	}
	if (g->elements)
	{
		i = 0;
		while (i < 6)
			free(g->elements[i++]);
	}
}
