/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:25:58 by layala-s          #+#    #+#             */
/*   Updated: 2025/05/15 19:16:19 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*clean_str(char *str)
{
	int		i;
	int		j;
	char	*clean;

	clean = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	if (!clean)
		return (NULL);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			clean[j++] = str[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

char	**get_rgb(char *color)
{
	char	**raw_rgb;
	char	**clean_rgb;
	int		i;

	raw_rgb = ft_split(color, ',');
	if (!raw_rgb)
		return (NULL);
	clean_rgb = malloc(sizeof(char *) * 4);
	if (!clean_rgb)
		return (NULL);
	i = 0;
	while (raw_rgb[i] && i < 3)
	{
		clean_rgb[i] = clean_str(raw_rgb[i]);
		i++;
	}
	clean_rgb[i] = NULL;
	i = 0;
	while (raw_rgb[i])
		free(raw_rgb[i++]);
	free(raw_rgb);
	return (clean_rgb);
}

int	check_rgb(char **rgb, t_game *g)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(rgb[0]);
	green = ft_atoi(rgb[1]);
	blue = ft_atoi(rgb[2]);
	if (ft_strlen(rgb[0]) > 4 || ft_strlen(rgb[1]) > 4 \
		|| ft_strlen(rgb[2]) > 4 || (red < 0 || red > 255) \
		|| (green < 0 || green > 255) \
		|| (blue < 0 || blue > 255))
	{
		free_rgb(rgb);
		exit_error("Error: RGB Range should be <0 to 255>", 1, g);
	}
	return (0);
}

int	parse_rgb(char **rgb)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(rgb[0]);
	green = ft_atoi(rgb[1]);
	blue = ft_atoi(rgb[2]);
	return ((red << 16) | (green << 8) | blue);
}
