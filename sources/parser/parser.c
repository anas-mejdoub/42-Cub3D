/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:07 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/11 22:47:48 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_print(char *s)
{
	ft_alloc(0, NULL, FREE_ALL);
	print_err(1, s);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

char **spliter(char *line)
{
	char **arr;
	char *str;
	int i;

	arr = NULL;
	str = NULL;
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	str = ft_substr(line, 0, i);
	arr = ft_arradd_back(arr, str);
	ft_alloc(0, str, FREE_PTR);
	while (line[i] && line[i] == ' ')
		i++;
	str = ft_substr(line, i, ft_strlen(line) - i - 1);
	arr = ft_arradd_back(arr, str);
	ft_alloc(0, str, FREE_PTR);
	return (arr);
}

void save_walls(char **arr, t_game_env **game_env)
{
	if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
	{
		if ((*game_env)->wall->north)
			free_print("invalid data. symbol is duplicated\n");
		if (ft_strncmp(arr[1] + (ft_strlen(arr[1]) - 4), ".png", 4))
			free_print("invalid format. shoude be end with .png\n");
		(*game_env)->wall->north = mlx_load_png(arr[1]);
		if (!(*game_env)->wall->north)
			free_print("1error while loading.\n");
	}
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
	{
		if ((*game_env)->wall->south)
			free_print("invalid data. symbol is duplicated\n");
		if (ft_strncmp(arr[1] + (ft_strlen(arr[1]) - 4), ".png", 4))
			free_print("invalid format. shoude be end with .png\n");
		(*game_env)->wall->south = mlx_load_png(arr[1]);
		if (!(*game_env)->wall->south)
			free_print("2error while loading.\n");
		
	}
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
	{
		if ((*game_env)->wall->west)
			free_print("invalid data. symbol is duplicated\n");
		if (ft_strncmp(arr[1] + (ft_strlen(arr[1]) - 4), ".png", 4))
			free_print("invalid format. shoude be end with .png\n");
		(*game_env)->wall->west = mlx_load_png(arr[1]);
		if (!(*game_env)->wall->west)
			free_print("3error while loading.\n");
	}
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
	{
		if ((*game_env)->wall->east)
			free_print("invalid data. symbol is duplicated\n");
		if (ft_strncmp(arr[1] + (ft_strlen(arr[1]) - 4), ".png", 4))
			free_print("invalid format. shoude be end with .png\n");
		(*game_env)->wall->east = mlx_load_png(arr[1]);
		if (!(*game_env)->wall->east)
			free_print("4error while loading.\n");
	}
}

int calculate_colors(char *s)
{
	char **rgba;
	int	color;
	
	rgba = ft_split(s, ',');
	color = 0;
	if (ft_arrsize(rgba) != 3 && ft_arrsize(rgba) != 4)
	{
		ft_alloc(0, NULL, FREE_ALL);
		print_err(3, "invalid rgba colors\n");
	}
	if (ft_arrsize(rgba) == 3)
		color = get_rgba(ft_atoi(rgba[0]), ft_atoi(rgba[1]), ft_atoi(rgba[2]), 1);
	else if (ft_arrsize(rgba) == 4)
		color = get_rgba(ft_atoi(rgba[0]), ft_atoi(rgba[1]), ft_atoi(rgba[2]), ft_atoi(rgba[3]));
	ft_alloc(0, rgba, FREE_PTR);
	return (color);
}

void save_earth_sky(char **arr, t_game_env **game_env)
{
	if (ft_strlen(arr[0]) == 1 && !ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		if ((*game_env)->floor != -1)
			free_print("invalid data. symbol is duplicated\n");
		(*game_env)->floor = calculate_colors(arr[1]);
	}
	if (ft_strlen(arr[0]) == 1 && !ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		if ((*game_env)->ceiling != -1)
			free_print("invalid data. symbol is duplicated\n");
		(*game_env)->ceiling = calculate_colors(arr[1]);
		
	}
}

void save_tools(char **arr, t_game_env **game_env)
{
	if (ft_arrsize(arr) != 2)
	{
		ft_alloc(0, NULL, FREE_ALL);
		print_err(1, "invalid data. split  and ther value by space\n");
	}
	if (ft_strlen(arr[0]) == 2 && \
		(!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "SO", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "WE", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "EA", ft_strlen(arr[0]))))
		save_walls(arr, game_env);
	else if (ft_strlen(arr[0]) == 1 && \
		(!ft_strncmp(arr[0], "F", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "C", ft_strlen(arr[0]))))
		save_earth_sky(arr, game_env);
	else
	{
		ft_alloc(0, NULL, FREE_ALL);
		print_err(1, "invalid or missing data\n");
	}
}

void check_map_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW ", line[i]))
		{
			ft_alloc(0, NULL, FREE_ALL);
			free_print("invalid map\n");
		}
		i++;
	}
}

char **save_map(int fd, char *first_line)
{
	char **map;
	char *line;
	char *tmp;
	map = NULL;

	tmp = ft_strtrim(first_line, "\n");
	check_map_line(tmp);
	map = ft_arradd_back(map, tmp);
	ft_alloc(0, tmp, FREE_PTR);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (ft_strlen(line) == 1 && !strncmp(line, "\n", ft_strlen(line)))
		{
			ft_alloc(0, NULL, FREE_ALL);
			free_print("invalid map\n");
		}
		tmp = ft_strtrim(line, "\n");
		ft_alloc(0, line, FREE_PTR);
		check_map_line(tmp);
		map = ft_arradd_back(map, tmp);
		ft_alloc(0, tmp, FREE_PTR);
	}
	return (map);
}

void read_file(int fd, t_game_env **game_env)
{
	char *line;
	char **temp_arr;
	char **map;
	
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (ft_strlen(line) == 1 && !ft_strncmp(line, "\n", ft_strlen(line)))
		{
			ft_alloc(0, line, FREE_PTR);	
			continue;
		}
		temp_arr = spliter(line);
		if ((*game_env)->ceiling == -1 || (*game_env)->floor == -1 \
			|| !(*game_env)->wall->east || !(*game_env)->wall->west \
			|| !(*game_env)->wall->north || !(*game_env)->wall->south)
			save_tools(temp_arr, game_env);
		else
		{
			map = save_map(fd, line);
			(*game_env)->map = map;
			break;
		}
		ft_alloc(0, temp_arr, FREE_PTR);
	}
}

int parser(int ac ,char **av)
{
	t_game_env *game_env;
	char **arr;
	int fd;

	fd = 0;
	arr = NULL;
	game_env = NULL;
	if (ac == 1)
		print_err(1, "messing parameter\n");
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 4))
		print_err(1, "invalid format. should be *.cub\n");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_err(3, "can't open file ", av[1], "\n");
	game_env = ft_alloc(sizeof(t_game_env), game_env, CALLOC);
	if (!game_env)
		print_err(1, "malloc failed\n");
	game_env->ceiling = -1;
	game_env->floor = -1;
	game_env->wall = ft_alloc(sizeof(t_wall), game_env->wall, CALLOC);
	read_file(fd, &game_env);
	return (1);
}
