/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:51:17 by layala-s          #+#    #+#             */
/*   Updated: 2025/04/20 17:04:29 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*alloc_strcuts(void)
{
	t_game	*game;
	int		i;

	i = 0;
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->e = malloc(sizeof(t_element));
	if (!game->e)
		return (free(game), NULL);
	game->elements = malloc(sizeof(char *) * 7);
	if (!game->elements)
	{
		free(game->e);
		return (free(game), NULL);
	}
	while (i < 6)
		game->elements[i++] = 0;
	game->mini = malloc(sizeof(t_minimap));
	if (!game->mini)
	{
		free(game->elements);
		return (free(game->elements), free(game), NULL);
	}
	return (game);
}

t_game	*init_struct(void)
{
	t_game	*game;
	int		i;

	game = alloc_strcuts();
	if (!game)
		return (NULL);
	i = 0;
	while (i < MAX_KEYS)
		game->keys[i++] = 0;
	game->e->ea_tx = NULL;
	game->e->we_tx = NULL;
	game->e->so_tx = NULL;
	game->e->no_tx = NULL;
	game->e->c_rgb = NULL;
	game->e->f_rgb = NULL;
	game->p_count = 0;
	game->player_x = 0.5;
	game->player_y = 0.5;
	game->dir_x = 0;
	game->dir_y = -1;
	game->plane_x = 0.66;
	return (game->plane_y = 0, game);
}

char	**copy_file(const char *filename)
{
	int		fd;
	int		line_count;
	char	*line;
	char	**temp;

	temp = malloc(sizeof(char *) * 1024);
	if (!temp)
		return (NULL);
	line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(temp), NULL);
	line = get_next_line(fd);
	while (line)
	{
		temp[line_count++] = line;
		line = get_next_line(fd);
	}
	temp[line_count] = NULL;
	close(fd);
	return (temp);
}

int	main(int ac, char **av)
{
	t_game	*game;
	char	**temp;

	game = NULL;
	if (check_input(ac, av) != 0)
		exit(EXIT_FAILURE);
	game = init_struct();
	if (!game)
		return (1);
	temp = copy_file(av[1]);
	if (!temp)
		exit_error("Error: Can't find .cub file", 1, game);
	get_map(game, temp);
	parse_data(game, temp);
	validate_map(game);
	start_game(game);
	free_game(game);
	return (0);
}
