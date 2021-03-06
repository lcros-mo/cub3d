/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcros-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:48:25 by lcros-mo          #+#    #+#             */
/*   Updated: 2021/05/11 17:48:52 by lcros-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static int	rgb2int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	my_mlx_pixel_put(t_cub *c, int x, int y, int color)
{
	c->win.addr[c->win.wid * y + x] = color;
}

void	free_map(t_cub *c)
{
	int	i;

	i = c->nrows;
	if (c->map)
	{
		while (i >= 0)
		{
			free(c->map[i]);
			c->map[i] = NULL;
			i--;
		}
		free(c->map);
		c->map = NULL;
	}
}

void	paint_sky_floor(t_cub *c)
{
	int	x;
	int	y;
	int	sky_color;
	int	floor_color;

	sky_color = rgb2int(c->col.rgb_s[0], c->col.rgb_s[1], c->col.rgb_s[2]);
	floor_color = rgb2int(c->col.rgb_f[0], c->col.rgb_f[1], c->col.rgb_f[2]);
	y = -1;
	while (++y < c->win.hei)
	{
		x = -1;
		while (++x < c->win.wid)
		{
			if (y < c->win.hei / 2)
				my_mlx_pixel_put(c, x, y, sky_color);
			else
				my_mlx_pixel_put(c, x, y, floor_color);
		}
	}
}

int	draw(t_cub *c)
{
	int	x;

	c->sp.zbuf = malloc(sizeof(double) * c->win.wid);
	if (c->draw.repaint)
	{
		x = -1;
		paint_sky_floor(c);
		while (++x < c->win.wid)
			raycaster(c, x);
		sprite2screen(c);
	}
	if (!c->bmp)
	{
		mlx_put_image_to_window(c->libx.mlx, c->libx.window, c->win.img, 0, 0);
		c->draw.repaint = move_keys(c, SQUARES_SEC);
		c->draw.repaint |= rotate_keys(c, RADIANS_SEC);
	}
	free(c->sp.zbuf);
	return (1);
}
