/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcros-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:47:24 by lcros-mo          #+#    #+#             */
/*   Updated: 2021/05/11 17:48:52 by lcros-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	init_sp_vble(t_cub *c)
{
	c->sp.img = NULL;
	c->sp.addr = NULL;
	c->sp.wid = 0;
	c->sp.hei = 0;
	c->sp.bpp = 0;
	c->sp.sz = 0;
	c->sp.endian = 0;
	c->sp.posx = 0.0;
	c->sp.posy = 0.0;
	c->sp.draw_startx = 0;
	c->sp.draw_starty = 0;
	c->sp.draw_endx = 0;
	c->sp.draw_endy = 0;
	c->sp.h = 0;
	c->sp.w = 0;
	c->sp.screenx = 0;
	c->sp.color = 0;
	c->sp.zbuf = NULL;
}

static void	check_xpm(t_cub *c)
{
	int	x;

	x = 0;
	while (x < MAX_TEXTURES)
	{
		if (!c->twall[x].img)
			clean_exit(c, "Fail to convert the texture of a wall\n", 1);
		else
			c->twall[x].addr = (int *)mlx_get_data_addr(c->twall[x].img,
					&c->twall[x].bpp, &c->twall[x].sz, &c->twall[x].endian);
		x++;
	}
	if (!c->sp.img)
		clean_exit(c, "Fail to convert the texture of the sprite\n", 1);
	else
		c->sp.addr = (int *)mlx_get_data_addr(c->sp.img, &c->sp.bpp,
				&c->sp.sz, &c->sp.endian);
}

void	xpm2image(t_cub *c)
{
	c->twall[NO].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_no,
			&c->twall[NO].wid, &c->twall[NO].hei);
	c->twall[SO].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_so,
			&c->twall[SO].wid, &c->twall[SO].hei);
	c->twall[EA].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_ea,
			&c->twall[EA].wid, &c->twall[EA].hei);
	c->twall[WE].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_we,
			&c->twall[WE].wid, &c->twall[WE].hei);
	c->sp.img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_sp,
			&c->sp.wid, &c->sp.hei);
	check_xpm(c);
}

static void	resize_window(t_cub *c, int bmp)
{
	if (c->res.x > c->win.wid && bmp)
		c->win.wid = c->res.x;
	else if (c->res.x <= c->win.wid)
		c->win.wid = c->res.x;
	if (c->res.y > c->win.hei && bmp)
		c->win.hei = c->res.y;
	else if (c->res.y <= c->win.hei)
		c->win.hei = c->res.y;
}

void	init_mlx_func(t_cub *c)
{
	c->libx.mlx = mlx_init();
	if (!c->libx.mlx)
		clean_exit(c, "MLX was not initialized\n", 1);
	xpm2image(c);
	mlx_get_screen_size(c->libx.mlx, &c->win.wid, &c->win.hei);
	resize_window(c, c->bmp);
	if (!c->bmp)
	{
		c->libx.window = mlx_new_window(c->libx.mlx, c->win.wid,
				c->win.hei, "Cub3D");
		if (!c->libx.window)
			clean_exit(c, "When opening a new window\n", 1);
	}
	c->win.img = mlx_new_image(c->libx.mlx, c->win.wid, c->win.hei);
	if (!c->win.img)
		clean_exit(c, "When creating a new image\n", 1);
	c->win.addr = (int *)mlx_get_data_addr(c->win.img, &c->win.bpp, &c->win.sz,
			&c->win.endian);
	mlx_do_key_autorepeatoff(c->libx.mlx);
}
