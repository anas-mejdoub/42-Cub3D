/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/11 21:37:03 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "stdio.h"
# include "fcntl.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_wall
{
	mlx_texture_t* north;
	mlx_texture_t* south;
	mlx_texture_t* west;
	mlx_texture_t* east;
} t_wall;

typedef struct s_game_env
{
	char	**map;
	t_wall	*wall;
	int		floor;
	int		ceiling;

}	t_game_env;

int parser(int ac, char **av);


# endif