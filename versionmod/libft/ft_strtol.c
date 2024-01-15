/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:00:32 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 11:56:12 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_whitespaces_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	determine_base(const char *str, int *base, int index)
{
	if ((*base == 0 || *base == 16) && str[index] == '0'
		&& (str[index + 1] == 'x' || str[index + 1] == 'X'))
	{
		*base = 16;
		index += 2;
	}
	else if (*base == 0)
	{
		if (str[index] == '0')
			*base = 8;
		else
			*base = 10;
	}
	return (index);
}

static int	check_base(const char *str, int *base, int *sign)
{
	int	i;

	*sign = 1;
	i = skip_whitespaces_and_sign(str, sign);
	i = determine_base(str, base, i);
	return (i);
}

static long	convert_strtol(const char *str, int base, int sign)
{
	long	result;
	int		digit;

	result = 0;
	while (*str)
	{
		digit = 0;
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'A' && *str <= 'Z')
			digit = *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'z')
			digit = *str - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		if (sign > 0 && result > (LONG_MAX - digit) / base)
			return (errno = ERANGE, LONG_MAX);
		if (sign < 0 && result < (LONG_MIN + digit) / base)
			return (errno = ERANGE, LONG_MIN);
		result = result * base + digit;
		str++;
	}
	return (result * sign);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	int		sign;
	int		i;
	long	result;

	if (base < 0 || base == 1 || base > 36)
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	i = check_base(str, &base, &sign);
	result = convert_strtol(str + i, base, sign);
	if (endptr)
		*endptr = (char *)(str + i);
	while (*str)
	{
		if ((*str >= '0' && *str <= '9' && *str - '0' < base)
			|| (*str >= 'A' && *str <= 'Z' && *str - 'A' + 10 < base)
			|| (*str >= 'a' && *str <= 'z' && *str - 'a' + 10 < base))
			*endptr = (char *)(str + 1);
		else
			break ;
		str++;
	}
	return (result);
}
