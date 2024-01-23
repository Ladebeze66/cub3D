/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:14:45 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 11:41:34 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*init_str_and_lasts(char **lasts, char *str)
{
	if (str == NULL)
	{
		str = *lasts;
		if (str == NULL)
			return (NULL);
	}
	else
	{
		*lasts = str;
	}
	return (str);
}

static char	*find_token_start(char **lasts, const char *delim)
{
	int	ch;

	ch = **lasts;
	while (ch != '\0' && ft_strchr(delim, ch) != NULL)
	{
		(*lasts)++;
		ch = **lasts;
	}
	if (**lasts == '\0')
	{
		*lasts = NULL;
		return (NULL);
	}
	return (*lasts);
}

static char	*find_token_end(char **lasts, const char *delim)
{
	int		ch;
	char	*str;

	str = *lasts;
	ch = **lasts;
	while (ch != '\0' && ft_strchr(delim, ch) == NULL)
	{
		(*lasts)++;
		ch = **lasts;
	}
	if (**lasts != '\0')
	{
		**lasts = '\0';
		(*lasts)++;
	}
	else
	{
		*lasts = NULL;
	}
	return (str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*lasts;

	str = init_str_and_lasts(&lasts, str);
	if (str == NULL)
		return (NULL);
	str = find_token_start(&lasts, delim);
	if (str == NULL)
		return (NULL);
	return (find_token_end(&lasts, delim));
}
