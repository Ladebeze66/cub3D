/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:22 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 13:58:28 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_bzero(void *ptr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
	{
		return (malloc(size));
	}
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
