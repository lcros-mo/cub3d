/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcros-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:44:13 by lcros-mo          #+#    #+#             */
/*   Updated: 2021/05/11 17:48:52 by lcros-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/cub.h"
#include <stdlib.h>

static int	cont_char(char const *s, char c)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	if (s[0] && s[0] != c)
		cont++;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			cont++;
		i++;
	}
	return (cont);
}

static char	*ft_word(char const *s, char c, int i)
{
	int		p;
	int		k;
	char	*w;

	p = i;
	while (s[i] && s[i] != c)
		i++;
	w = (char *)malloc(sizeof(char) * ((i - p) + 1));
	if (!w)
		return (NULL);
	k = 0;
	while (p != i)
	{
		w[k] = s[p];
		k++;
		p++;
	}
	w[k] = '\0';
	return (w);
}

void	ft_split(char **s1, char z, t_cub *c)
{
	int		i;
	int		k;
	char	*aux;

	if (!*s1)
		return ;
	c->map = (char **)malloc(sizeof(char *) * (cont_char(*s1, z) + 1));
	if (!c->map)
		return ;
	i = 0;
	k = 0;
	while (i <= (int)ft_strlen(*s1) && cont_char(*s1, z))
	{
		aux = ft_word(*s1, z, i);
		if (ft_strlen(aux))
		{
			c->map[k] = ft_strdup(aux);
			i += (ft_strlen(c->map[k++]) + 1);
		}
		else
			i++;
		free(aux);
		aux = NULL;
	}
	c->map[k] = NULL;
}
