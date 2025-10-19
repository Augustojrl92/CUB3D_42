/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:57:51 by layala-s          #+#    #+#             */
/*   Updated: 2025/04/30 16:57:52 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	skip_leading_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

int	compact_spaces(char *line, char *ret, int start)
{
	int	i;
	int	j;
	int	in_space;

	i = start;
	j = 0;
	in_space = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_space(line[i]))
		{
			if (!in_space)
				ret[j++] = ' ';
			in_space = 1;
		}
		else
		{
			ret[j++] = line[i];
			in_space = 0;
		}
		i++;
	}
	if (j > 0 && ret[j - 1] == ' ')
		j--;
	return (ret[j] = '\0', j);
}

char	*clean_string(char *line)
{
	char	*ret;
	int		start;

	if (!line)
		return (NULL);
	ret = malloc(ft_strlen(line) + 1);
	if (!ret)
		return (NULL);
	start = skip_leading_spaces(line);
	compact_spaces(line, ret, start);
	return (ret);
}

void	get_elements(t_game *g, char **copy)
{
	int		count;
	int		i;
	char	*line;

	count = 0;
	i = 0;
	while (count < 6 && copy[i])
	{
		line = ft_strdup(copy[i]);
		if (!line)
			break ;
		if (empty_line(line))
		{
			free(line);
			i++;
			continue ;
		}
		g->elements[count] = clean_string(line);
		free(line);
		count++;
		i++;
	}
	i = 0;
	g->elements[count] = NULL;
}
