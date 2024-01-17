/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocarray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:52:29 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 11:46:15 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_mul_no_overflow(void)
{
	return ((size_t)1 << (sizeof(size_t) * 4));
}

void	*ft_reallocarray(void *optr, size_t nmemb, size_t size, size_t oldsize)
{
	size_t	mul_no_overflow;

	mul_no_overflow = get_mul_no_overflow();
	if ((nmemb >= mul_no_overflow || size >= mul_no_overflow)
		&& nmemb > 0 && SIZE_MAX / nmemb < size)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (ft_realloc(optr, nmemb * size, oldsize));
}
