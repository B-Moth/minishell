/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:10 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/11 21:34:28 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

// Takes a the fractionnal part of floating point number, and returns 
// the absolute value of the fractionnal part
// Return NULL on error 
static char	*handle_floatpart(double fpart, int decimals)
{
	char	*strfloat;

	if (fpart < 0)
		fpart *= -1;
	while (decimals-- > 0)
		fpart *= 10;
	strfloat = ft_itoa((int)fpart);
	if (!strfloat)
		return (NULL);
	return (strfloat);
}

// SUBOPTIMAL : Pas precis + gere uniquement une partie entier < MAX_INT
// et une partie fractionnaire < MAX_INT
// Takes a double and converts it to a string with decimals number precision
// Returns NULL on error
char	*ft_dtoa(double d, int decimals)
{
	char	*strint;
	char	*strfloat;
	char	*res;

	res = ft_itoa((int) d);
	if (d < 0 && (int) d >= 0)
	{
		strfloat = ft_strjoin("-", res);
		strint = ft_strjoin(strfloat, ".");
		if (strfloat)
			free(strfloat);
	}
	else
		strint = ft_strjoin(res, ".");
	if (res)
		free(res);
	strfloat = handle_floatpart(d - (int)d, decimals);
	res = ft_strjoin(strint, strfloat);
	if (strint)
		free(strint);
	if (strfloat)
		free(strfloat);
	return (res);
}
