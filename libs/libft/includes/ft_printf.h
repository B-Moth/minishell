/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:16:12 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/14 18:56:36 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include"libft.h"
# include<stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_print_char(char c);
int	ft_print_str(const char *s);
int	ft_print_pointer(unsigned long p);
int	ft_print_int(int n);
int	ft_print_uns_int(unsigned int u);
int	ft_print_hex_low(int i);
int	ft_print_hex_up(int i);

#endif 
