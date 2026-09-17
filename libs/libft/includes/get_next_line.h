/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:55:48 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/14 18:55:41 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);

// char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*lucas_safe(char *s1, char *s2);
// char	*ft_strjoin(char const *s1, char const *s2);
// size_t	ft_strlen(const char *str);
// char	*ft_strdup(const char *s);

#endif 