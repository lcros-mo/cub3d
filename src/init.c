/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcros-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:47:28 by lcros-mo          #+#    #+#             */
/*   Updated: 2021/05/11 17:48:52 by lcros-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	init_file_vble(t_cub *info)
{
	info->res.x = 0;
	info->res.y = 0;
	info->tex.path_no = NULL;
	info->tex.path_so = NULL;
	info->tex.path_we = NULL;
	info->tex.path_ea = NULL;
	info->tex.path_sp = NULL;
	ft_bzero(info->col.rgb_s, 3);
	ft_bzero(info->col.rgb_f, 3);
	info->line = NULL;
	info->map = NULL;
	info->sprites = NULL;
	info->bmp = 0;
	info->r.b = NULL;
	info->r.l = NULL;
	info->r.stc = NULL;
}

static void	init_mov_vble(t_cub *info)
{
	info->mov.left = 0;
	info->mov.right = 0;
	info->mov.up = 0;
	info->mov.down = 0;
	info->mov.posx = 0.0;
	info->mov.posy = 0.0;
	info->mov.dirx = 0.0;
	info->mov.diry = 0.0;
	info->mov.planex = 0.0;
	info->mov.planey = 0.0;
	info->mov.mapx = 0;
	info->mov.mapy = 0;
	info->cam.left = 0;
	info->cam.right = 0;
	info->cam.x = 0.0;
}

void	init_raycast_vble(t_cub *info)
{
	info->ray.dirx = 0.0;
	info->ray.diry = 0.0;
	info->ray.sidex = 0.0;
	info->ray.sidey = 0.0;
	info->ray.deltax = 0.0;
	info->ray.deltay = 0.0;
	info->ray.perp = 0.0;
	info->ray.stepx = 0;
	info->ray.stepy = 0;
	info->ray.step = 0.0;
	info->ray.hit = 0;
	info->ray.side = 0;
	info->ray.lineh = 0;
	info->ray.texnum = 0;
	info->ray.x = 0;
	info->ray.y = 0;
	info->ray.pos = 0.0;
	info->draw.start = 0;
	info->draw.end = 0;
	info->draw.wallx = 0;
	info->draw.wally = 0;
	info->mov.mapx = 0;
	info->mov.mapy = 0;
	info->cam.x = 0.0;
}

static void	init_tex_vble(t_cub *c)
{
	int	x;

	x = 0;
	while (x < MAX_TEXTURES)
	{
		c->twall[x].img = NULL;
		c->twall[x].addr = NULL;
		c->twall[x].wid = 0;
		c->twall[x].hei = 0;
		c->twall[x].bpp = 0;
		c->twall[x].sz = 0;
		c->twall[x].endian = 0;
		x++;
	}
	init_sp_vble(c);
}

void	init_struct(t_cub *info)
{
	init_file_vble(info);
	init_mov_vble(info);
	init_raycast_vble(info);
	init_tex_vble(info);
	info->draw.repaint = 1;
	info->libx.mlx = NULL;
	info->libx.window = NULL;
	info->win.img = NULL;
	info->nrows = 0;
	info->check.texno = 0;
	info->check.texso = 0;
	info->check.texwe = 0;
	info->check.texea = 0;
	info->check.texsp = 0;
	info->check.res = 0;
	info->check.floor = 0;
	info->check.sky = 0;
	info->check.map = 0;
	info->check.player = 0;
}
