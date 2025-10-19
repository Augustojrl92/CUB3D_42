/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:57:02 by layala-s          #+#    #+#             */
/*   Updated: 2025/04/22 13:57:04 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_extension(char *filename, char *extension)
{
	int	len_file;
	int	len_ext;

	len_ext = ft_strlen(extension);
	len_file = ft_strlen(filename);
	if (len_file <= len_ext)
		return (0);
	if (ft_strncmp(filename + len_file - len_ext, extension, len_ext) == 0)
		return (1);
	return (0);
}

int	check_input(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Error\nUsage: ./cub3d <map_file.cub>", 36);
		exit(EXIT_FAILURE);
	}
	else if (!check_extension(av[1], ".cub"))
	{
		write(2, "Error: File extension should be .cub", 37);
		exit(EXIT_FAILURE);
	}
	return (0);
}
