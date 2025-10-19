/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 04:21:07 by layala-s          #+#    #+#             */
/*   Updated: 2024/11/20 04:21:47 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = src;
	d = dst;
	while (n-- > 0)
	{
		*d++ = *s;
		if (*s++ == (unsigned char)c)
			return (d++);
	}
	return (0);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*temp;

	if (!size && ptr)
		size = 1;
	temp = malloc(size);
	if (ptr)
	{
		ft_memccpy(temp, ptr, '\0', size);
		free (ptr);
	}
	return (temp);
}
