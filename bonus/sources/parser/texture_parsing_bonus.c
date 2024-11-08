/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:35:30 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/11/01 10:53:39 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	setup_wall(mlx_texture_t **wall, t_wall *wall_holder, char *s)
{
	char	*trimed;

	if (*wall)
		free_print("invalid data. symbol is duplicated\n", wall_holder);
	if (ft_strncmp(s + (ft_strlen(s) - 4), ".png", 4))
		free_print("invalid format. shoude be end with .png\n", wall_holder);
	trimed = ft_strtrim(s, " \n\t\v");
	*wall = mlx_load_png(trimed);
	if (!*wall)
		free_print("error while loading.\n", wall_holder);
	ft_alloc(0, trimed, FREE_PTR);
}

bool	check_rgb_format(char *s)
{
	int	ij[2];

	ij[0] = 0;
	ij[1] = 0;
	while (ij[1] < 2)
	{
		if (s[ij[0]] == '+' && s[ij[0]] && ft_isdigit(s[ij[0] + 1]))
			ij[0]++;
		while (s[ij[0]] && ft_isdigit(s[ij[0]]))
			ij[0]++;
		skip_spaces(&ij[0], s);
		if (!s[ij[0]] || s[ij[0]++] != ',')
			return (false);
		skip_spaces(&ij[0], s);
		if (!s[ij[0]] || (!ft_isdigit(s[ij[0]]) && !ft_strchr("+", s[ij[0]])))
			return (false);
		ij[1]++;
	}
	if (s[ij[0]] == '+')
		ij[0]++;
	while (s[ij[0]] && ft_isdigit(s[ij[0]]))
		ij[0]++;
	if (s[ij[0]])
		return (false);
	return (true);
}

int	calculate_colors(char *s, t_wall *wall)
{
	char	**rgba;
	int		color;

	rgba = ft_split(s, ',');
	color = 0;
	if (ft_arrsize(rgba) != 3 && ft_arrsize(rgba) != 4)
		free_print("invalid rgba colors\n", wall);
	if (ft_strlen(ft_strtrim(rgba[0], " \t\n")) > 4 || \
		ft_strlen(ft_strtrim(rgba[1], " \t\n")) > 4 || \
		ft_strlen(ft_strtrim(rgba[2], " \t\n")) > 4)
		free_print("invalid rgba colors\n", wall);
	if (ft_arrsize(rgba) == 3)
		color = get_rgba(ft_atoi(rgba[0]), ft_atoi(rgba[1]), ft_atoi(rgba[2]),
				wall);
	ft_alloc(0, rgba, FREE_PTR);
	return (color);
}

void	save_earth_sky(char **arr, t_game_env **game_env)
{
	char	*trimed;

	if (ft_strlen(arr[0]) == 1 && !ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		if ((*game_env)->floor_status != -1)
			free_print("invalid data. symbol is duplicated\n",
				(*game_env)->wall);
		trimed = ft_strtrim(arr[1], " \n\t\v");
		if (!check_rgb_format(trimed))
			free_print("invalid rgb format. \n", (*game_env)->wall);
		(*game_env)->floor = calculate_colors(trimed, (*game_env)->wall);
		(*game_env)->floor_status = 0;
	}
	if (ft_strlen(arr[0]) == 1 && !ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		if ((*game_env)->ceiling_status != -1)
			free_print("invalid data.\n", (*game_env)->wall);
		trimed = ft_strtrim(arr[1], " \n\t\v");
		if (!check_rgb_format(trimed))
			free_print("invalid rgb format \n", (*game_env)->wall);
		(*game_env)->ceiling = calculate_colors(trimed, (*game_env)->wall);
		(*game_env)->ceiling_status = 0;
	}
}

void	save_walls(char **arr, t_game_env **game_env)
{
	if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->north, (*game_env)->wall, arr[1]);
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "SO",
			ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->south, (*game_env)->wall, arr[1]);
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "WE",
			ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->west, (*game_env)->wall, arr[1]);
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "EA",
			ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->east, (*game_env)->wall, arr[1]);
}
