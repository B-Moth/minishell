/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:52:59 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/14 19:46:14 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;
	int	inword;

	count = 0;
	i = 0;
	inword = 0;
	while (s[i])
	{
		if (inword == 0 && s[i] != c)
		{
			count++;
			inword = 1;
		}
		if (s[i] == c)
			inword = 0;
		i++;
	}
	return (count);
}

static void	free_tab(char **tab, int count)
{
	while (count > 0)
	{
		if (tab[count - 1])
			free(tab[count - 1]);
		count--;
	}
	if (tab)
		free(tab);
}

static int	find_start(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (i);
		i++;
	}
	return (-1);
}

static int	fill_tab(char **tab, char const *s, char c, int count)
{
	int	start;
	int	i;

	start = find_start(s, c);
	if (start == -1)
		return (-1);
	i = 0;
	while (s[start + i] != c && s[start + i])
		i++;
	tab[count] = ft_substr(s, start, i);
	if (tab[count] == NULL)
		return (-1);
	return (start + i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;
	int		curs;
	int		buff;

	if (!s)
		return (NULL);
	tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	count = 0;
	curs = 0;
	while (count < count_words(s, c))
	{
		buff = fill_tab(tab, s + curs, c, count);
		if (buff == -1)
		{
			free_tab(tab, count);
			return (NULL);
		}
		curs += buff;
		count++;
	}
	tab[count] = NULL;
	return (tab);
}
