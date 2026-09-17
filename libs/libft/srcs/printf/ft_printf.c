/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:11:47 by tlebon            #+#    #+#             */
/*   Updated: 2024/01/17 11:53:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	choose_arg(char det, va_list *ap)
{
	if (det == 'c')
		return (ft_print_char(va_arg(*ap, int)));
	else if (det == 's')
		return (ft_print_str(va_arg(*ap, char *)));
	else if (det == 'p')
		return (ft_print_pointer(va_arg(*ap, unsigned long)));
	else if (det == 'd')
		return (ft_print_int(va_arg(*ap, int)));
	else if (det == 'i')
		return (ft_print_int(va_arg(*ap, int)));
	else if (det == 'u')
		return (ft_print_uns_int(va_arg(*ap, unsigned int)));
	else if (det == 'x')
		return (ft_print_hex_low(va_arg(*ap, int)));
	else if (det == 'X')
		return (ft_print_hex_up(va_arg(*ap, int)));
	else if (det == '%')
		return (ft_print_char('%'));
	else if (det == '\0')
		return (-1);
	else
		return (ft_print_char('%') + ft_print_char(det));
}

static int	writing_loop(const char *s, va_list *pap)
{
	int		size;
	int		buff;
	size_t	cu;

	cu = 0;
	size = 0;
	while (s[cu])
	{
		if (s[cu] == '%')
		{
			buff = choose_arg(s[cu + 1], pap);
			if (buff == -1)
				return (-1);
			size += buff;
			cu += 2;
		}
		else
		{
			write(1, &s[cu], 1);
			cu++;
			size++;
		}
	}
	return (size);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	va_list	*pap;
	int		size;

	va_start(ap, s);
	pap = &ap;
	if (!s)
		return (-1);
	size = writing_loop(s, pap);
	va_end(ap);
	return (size);
}
