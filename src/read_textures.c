/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcros-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:47:54 by lcros-mo          #+#    #+#             */
/*   Updated: 2021/05/11 17:48:52 by lcros-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static char	*path_tex(char *line, t_cub *c, int nchar)
{
	int	i;

	i = nchar;
	while (ft_isspace(line[i]))
		i++;
	line = line + i;
	i = ft_strlen(line) - 1;
	while (ft_isspace(line[i]))
	{
		line[i] = '\0';
		i--;
	}
	if (error_tex_elements(line) == 1)
		clean_exit(c, "Too many elements in texture\n", 1);
	if (check_text(c, line) == 1)
		return (ft_strdup(line));
	if (check_text(c, line) < 0)
		clean_exit(c, "The texture extension must be .xpm\n", 1);
	clean_exit(c, "Repeated texture\n", 1);
	return (NULL);
}

static int	vertical_text(char *line, t_cub *info)
{
	if (!ft_strncmp(line, "NO", 2) && !info->check.texno)
	{
		info->tex.path_no = path_tex(line, info, 2);
		if (!ft_isspace(line[2]) || !info->tex.path_no)
			clean_exit(info, "Wrong north texture\n", 1);
		info->check.texno = 1;
		return (1);
	}
	else if (!ft_strncmp(line, "NO", 2) && info->check.texno)
		clean_exit(info, "Duplicate north texture identifier\n", 1);
	else if (!ft_strncmp(line, "SO", 2) && !info->check.texso)
	{
		info->tex.path_so = path_tex(line, info, 2);
		if (!ft_isspace(line[2]) || !info->tex.path_so)
			clean_exit(info, "Wrong south texture\n", 1);
		info->check.texso = 1;
		return (1);
	}
	else if (!ft_strncmp(line, "SO", 2) && info->check.texso)
		clean_exit(info, "Duplicate south texture identifier\n", 1);
	return (0);
}

static int	horizontal_text(char *line, t_cub *info)
{
	if (!ft_strncmp(line, "WE", 2) && !info->check.texwe)
	{
		info->tex.path_we = path_tex(line, info, 2);
		if (!ft_isspace(line[2]) || !info->tex.path_we)
			clean_exit(info, "Wrong west texture\n", 1);
		info->check.texwe = 1;
		return (1);
	}
	else if (!ft_strncmp(line, "WE", 2) && info->check.texwe)
		clean_exit(info, "Duplicate west texture identifier\n", 1);
	else if (!ft_strncmp(line, "EA", 2) && !info->check.texea)
	{
		info->tex.path_ea = path_tex(line, info, 2);
		if (!ft_isspace(line[2]) || !info->tex.path_ea)
			clean_exit(info, "Wrong east texture\n", 1);
		info->check.texea = 1;
		return (1);
	}
	else if (!ft_strncmp(line, "EA", 2) && info->check.texea)
		clean_exit(info, "Duplicate east texture identifier\n", 1);
	return (0);
}

void	info_tex(char *line, t_cub *info)
{
	int	done;

	remove_spaces(info, &line);
	done = vertical_text(line, info) || horizontal_text(line, info);
	if (!done && !ft_strncmp(line, "S", 1) && !info->check.texsp)
	{
		info->tex.path_sp = path_tex(line, info, 1);
		if (!ft_isspace(line[1]) || !info->tex.path_sp)
			clean_exit(info, "Wrong sprite texture\n", 1);
		info->check.texsp = 1;
	}
	else if (!done && !ft_strncmp(line, "S", 1) && info->check.texsp)
		clean_exit(info, "Duplicate sprite texture identifier\n", 1);
}

int	is_texture(char *line)
{
	char	*aux;

	aux = ft_strchr(line, 'N');
	if (aux && aux[1] == 'O')
		return (1);
	aux = ft_strchr(line, 'S');
	if (aux && aux[1] == 'O')
		return (1);
	aux = ft_strchr(line, 'W');
	if (aux && aux[1] == 'E')
		return (1);
	aux = ft_strchr(line, 'E');
	if (aux && aux[1] == 'A')
		return (1);
	aux = ft_strchr(line, 'S');
	if (aux && ft_isspace(aux[1]))
		return (1);
	return (0);
}
