/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:31:35 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 13:59:12 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize, size_t oldsize)
{
	char	*newptr;

	if (ptr == NULL)
	{
		return (malloc(newsize));
	}
	if (newsize <= oldsize)
	{
		return (ptr);
	}
	newptr = malloc(newsize);
	if (newptr == NULL)
	{
		return (NULL);
	}
	ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}
