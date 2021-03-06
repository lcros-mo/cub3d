/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcros-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:47:45 by lcros-mo          #+#    #+#             */
/*   Updated: 2021/05/11 17:48:52 by lcros-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	ray_pos_dir(t_cub *c, int x)
{
	c->cam.x = 2 * x / (double)c->win.wid - 1;
	c->ray.dirx = c->mov.dirx + c->mov.planex * c->cam.x;
	c->ray.diry = c->mov.diry + c->mov.planey * c->cam.x;
	c->mov.mapx = (int)c->mov.posx;
	c->mov.mapy = (int)c->mov.posy;
	c->ray.deltax = fabs(1 / c->ray.dirx);
	c->ray.deltay = fabs(1 / c->ray.diry);
}

static void	dda(t_cub *c)
{
	while (c->ray.hit == 0)
	{
		if (c->ray.sidex < c->ray.sidey)
		{
			c->ray.sidex += c->ray.deltax;
			c->mov.mapx += c->ray.stepx;
			c->ray.side = 0 + (c->ray.dirx < 0);
		}
		else
		{
			c->ray.sidey += c->ray.deltay;
			c->mov.mapy += c->ray.stepy;
			c->ray.side = 2 + (c->ray.diry > 0);
		}
		if (c->map[c->mov.mapx][c->mov.mapy] == WALL)
			c->ray.hit = 1;
	}
	if (c->ray.side <= 1)
		c->ray.perp = (c->mov.mapx - c->mov.posx + (1 - c->ray.stepx) / 2)
			/ c->ray.dirx;
	else
		c->ray.perp = (c->mov.mapy - c->mov.posy + (1 - c->ray.stepy) / 2)
			/ c->ray.diry;
}

static void	draw_calculus(t_cub *c)
{
	c->ray.lineh = (int)((double)c->win.hei / c->ray.perp);
	c->draw.start = (-c->ray.lineh / 2) + (c->win.hei / 2);
	if (c->draw.start < 0)
		c->draw.start = 0;
	c->draw.end = (c->ray.lineh / 2) + (c->win.hei / 2);
	if (c->draw.end >= c->win.hei)
		c->draw.end = c->win.hei - 1;
	if (c->draw.end < 0)
		c->draw.end = 0;
	if (c->ray.side <= 1)
		c->draw.wallx = c->mov.posy + c->ray.perp * c->ray.diry;
	else
		c->draw.wallx = c->mov.posx + c->ray.perp * c->ray.dirx;
	c->draw.wallx -= floor(c->draw.wallx);
	c->ray.x = (int)(c->draw.wallx * (double)(c->twall[c->ray.side].wid));
	if ((c->ray.side <= 1 && c->ray.dirx > 0) || (c->ray.side >= 2
			&& c->ray.diry > 0))
	{
		c->ray.x = c->twall[c->ray.side].wid - c->ray.x - 1;
	}
}

static void	draw_textures(t_cub *c, int x)
{
	int	i;
	int	color;

	i = c->draw.start;
	c->ray.step = 1.0 * c->twall[c->ray.side].hei / c->ray.lineh;
	c->ray.pos = (c->draw.start - c->win.hei / 2 + c->ray.lineh / 2)
		* c->ray.step;
	while (i < c->draw.end)
	{
		c->ray.y = (int)c->ray.pos & (c->twall[c->ray.side].hei - 1);
		c->ray.pos += c->ray.step;
		color = c->twall[c->ray.side].addr[c->twall[c->ray.side].wid
			* c->ray.y + c->ray.x];
		if (c->ray.side % 2)
			color = (color >> 1) & AND_ING;
		my_mlx_pixel_put(c, x, i, color);
		i++;
	}
	c->sp.zbuf[x] = c->ray.perp;
}

int	raycaster(t_cub *c, int x)
{
	init_raycast_vble(c);
	ray_pos_dir(c, x);
	step_initial_side(c);
	dda(c);
	draw_calculus(c);
	draw_textures(c, x);
	return (1);
}
