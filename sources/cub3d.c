/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:07:11 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/13 19:53:15 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void leaks(void)
{
	system("leaks cub3d");
}

int main(int ac, char **av)
{
	// atexit(leaks);
	raycaster(parser(ac, av));
	return (0);
}