/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:34:36 by nbenyahy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/14 12:28:10 by nbenyahy         ###   ########.fr       */
=======
/*   Updated: 2024/08/14 12:11:50 by amejdoub         ###   ########.fr       */
>>>>>>> raycasting
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*player_position(char **map)
{
	int	j;
	int	i;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				return ((int [2]){i, j});
			j++;
		}
		i++;
	}
	return ((int [2]){0, 0});
}

void	flod_fill_checker(char **map, int *xy, t_wall *wall)
{
	if ((xy[0] <= 0 || xy[1] <= 0 || xy[0] >= (int)ft_arrsize(map) - 1
			|| xy[1] >= (int)ft_strlen(map[xy[0]]) - 1)
		&& map[xy[0]][xy[1]] != '1')
		free_print("invalid map. The map must be closed/surrounded by walls\n",
			wall);
	if (map[xy[0]][xy[1]] == ' ' || map[xy[0]][xy[1]] == '\0')
		free_print("invalid map. The map must be closed/surrounded by walls\n",
			wall);
	else if (map[xy[0]][xy[1]] == '0')
	{
		map[xy[0]][xy[1]] = '1';
		flod_fill_checker(map, (int [2]){xy[0] + 1, xy[1]}, wall);
		flod_fill_checker(map, (int [2]){xy[0] - 1, xy[1]}, wall);
		flod_fill_checker(map, (int [2]){xy[0], xy[1] + 1}, wall);
		flod_fill_checker(map, (int [2]){xy[0], xy[1] - 1}, wall);
	}
	else
		return ;
}

void	check_map(char **map, t_wall *wall)
{
	char	**temp_map;
	int		*xy;
	int		i;
	int		len;

	temp_map = NULL;
	len = ft_arrsize(map) + 1;
	temp_map = ft_alloc(sizeof(char *) * len, temp_map, CALLOC);
	i = 0;
	while (map[i])
	{
		temp_map[i] = ft_strdup(map[i]);
		i++;
	}
	temp_map[i] = NULL;
	xy = player_position(map); // hayda kanet
	temp_map[xy[0]][xy[1]] = '0';
	flod_fill_checker(temp_map, xy, wall);
}