/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:56:10 by layala-s          #+#    #+#             */
/*   Updated: 2025/05/11 21:22:39 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	get_lines(t_game *g, int map_count, int map_start, char **copy)
{
	int	i;

	i = 0;
	while (i < map_count)
	{
		g->map[i] = ft_strdup(copy[map_start + i]);
		printf("%s", g->map[i]);
		i++;
	}
	g->map[map_count] = NULL;
	i = 0;
	return (0);
}

void	get_map(t_game *g, char **copy)
{
	int		i;
	int		map_start;
	int		map_count;

	i = 0;
	map_count = 0;
	map_start = -1;
	while (copy[i])
	{
		if (is_map_line(copy[i]))
		{
			map_start = i;
			break ;
		}
		i++;
	}
	if (map_start == -1)
		exit_error("Error: Map not found", 1, g);
	while (copy[map_start + map_count] && \
			is_map_line(copy[map_start + map_count]))
		map_count++;
	g->map = malloc(sizeof(char *) * (map_count + 1));
	if (!g->map)
		return ;
	get_lines(g, map_count, map_start, copy);
}

void	get_position(t_game *g)
{
	int		pos_x;
	int		pos_y;
	char	ori;

	pos_y = 0;
	while (g->map[pos_y])
	{
		pos_x = 0;
		while (g->map[pos_y][pos_x])
		{
			ori = g->map[pos_y][pos_x];
			if (ori == 'N' || ori == 'S' || ori == 'E' || ori == 'W')
			{
				g->player_x = pos_x + 0.5;
				g->player_y = pos_y + 0.5;
				set_direction(g, ori);
				set_plane(g, ori);
				g->map[pos_y][pos_x] = '0';
			}
			pos_x++;
		}
		pos_y++;
	}
}

void	validate_map(t_game *g)
{
	if (check_first_last(g->map) != 0 || check_values(g->map, g) != 0)
		exit_error("Error: Invalid map", 1, g);
	if (g->p_count > 1 || g->p_count < 1)
		exit_error("Error: only ONE player character <W, S, N, E>", 1, g);
}
