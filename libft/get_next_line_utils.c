/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:59:33 by layala-s          #+#    #+#             */
/*   Updated: 2024/05/22 16:59:35 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_ft_strlen(const char *c)
{
	int	len;

	len = 0;
	if (c == NULL)
		return (0);
	while (c[len] != '\0')
		len++;
	return (len);
}

char	*gnl_ft_strchr(char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

size_t	gnl_ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = gnl_ft_strlen(src);
	if (!src || !dest)
		return (0);
	while (size > 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	if (size > 0)
		dest[i] = '\0';
	return (len);
}

size_t	gnl_ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = gnl_ft_strlen(dest);
	src_len = gnl_ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size < dest_len)
		src_len = src_len + size;
	else
		src_len = src_len + dest_len;
	while (src[i] != '\0' && (dest_len + i) < size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*join;

	len = gnl_ft_strlen(s1) + gnl_ft_strlen(s2);
	join = (char *)malloc(len + 1 * (sizeof(char)));
	if (join == NULL)
		return (NULL);
	if (s1)
		gnl_ft_strlcpy(join, s1, len + 1);
	else
		join[0] = '\0';
	if (s2)
		gnl_ft_strlcat(join, s2, len + 1);
	if (s1)
		free(s1);
	return (join);
}
