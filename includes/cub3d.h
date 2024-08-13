/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/13 19:54:20 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
#include "math.h"
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

// parsing functions
t_game_env *parser(int ac, char **av);
int get_rgba(int r, int g, int b, t_wall *wall);
void save_earth_sky(char **arr, t_game_env **game_env);
void save_walls(char **arr, t_game_env **game_env);
void free_print(char *s, t_wall *wall);
void check_map(char **map, t_wall *wall);
char **spliter(char *line);
void save_tools(char **arr, t_game_env **game_env);
void free_texture(t_wall *wall);

//general functions
t_game_env *parser(int ac, char **av);
int raycaster(t_game_env *game_env);

#define PI 3.14159265358979323846
#define NUM_RAYS 320

typedef struct s_p_pos
{
	int x;
	int y;
} t_p_pos;

typedef struct s_player
{
	t_p_pos pos;
	int raduis;
	int turn_dir;
	int walk_dir;
	float rota_angle;
	float move_speed;
	float rotate_speed;
} t_player;

typedef struct s_shared_data
{
	t_game_env *game_env;
	mlx_t *mlx;
	mlx_image_t* image;
	t_p_pos p_pos;
	t_p_pos real_pos;
	t_player player;
} t_shared_data;
t_p_pos get_player_pos(char **map);
# endif