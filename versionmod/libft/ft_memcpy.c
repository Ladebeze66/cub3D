/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:43:15 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/02/20 16:13:43 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destmov;
	char	*srcmov;
	size_t	i;

	destmov = (char *)dest;
	srcmov = (char *)src;
	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		destmov[i] = srcmov[i];
		i++;
	}
	return (dest);
}
