/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_setup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mminkjan <mminkjan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 20:34:26 by mminkjan       #+#    #+#                */
/*   Updated: 2020/02/08 12:00:31 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_mlx(t_wolf *wolf)
{
	int		endian;

	endian = 0;
	wolf->mlx_ptr = mlx_init();
	wolf->win_ptr = mlx_new_window(wolf->mlx_ptr, \
		wolf->win_width, wolf->win_height, "Wolf3d");
	if (wolf->win_ptr == NULL)
		wolf_failure_exit(wolf, NULL,  MALLOC_ERR);
	wolf->img_ptr = \
		mlx_new_image(wolf->img_ptr, wolf->win_width, wolf->win_height);
	if (wolf->img_ptr == NULL)
		wolf_failure_exit(wolf, NULL, MALLOC_ERR);
	wolf->addr_str = mlx_get_data_addr(wolf->img_ptr, &wolf->bpp,
		&wolf->size_line, &endian);
	if (wolf->addr_str == NULL)
		wolf_failure_exit(wolf, NULL, MALLOC_ERR);
}
