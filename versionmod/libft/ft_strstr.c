/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:54:44 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/11/14 21:08:57 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*p;
	const char	*beginning;
	const char	*n;

	p = haystack;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*p != '\0')
	{
		if (*p == *needle)
		{
			beginning = p;
			n = needle;
			while (*p == *n && *n != '\0' && *p != '\0')
			{
				p++;
				n++;
			}
			if (*n == '\0')
				return ((char *)beginning);
			p = beginning;
		}
		p++;
	}
	return (NULL);
}
