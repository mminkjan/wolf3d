/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 12:57:21 by jesmith        #+#    #+#                */
/*   Updated: 2020/03/23 20:59:51 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	free_values(void **values)
{
	size_t	y;

	y = 0;
	while (values[y] != NULL)
	{
		free(values[y]);
		y++;
	}
	free(values);
}

static void	mlx_free(t_wolf *wolf)
{
		if (wolf->graphics.mlx_ptr)
	{
		ft_bzero(wolf->graphics.mlx_ptr, sizeof(wolf->graphics.mlx_ptr));
		free(wolf->graphics.mlx_ptr);
	}
	if (wolf->graphics.win_ptr)
	{
		ft_bzero(wolf->graphics.win_ptr, sizeof(wolf->graphics.win_ptr));
		free(wolf->graphics.win_ptr);
	}
		if (wolf->graphics.image_ptr)
	{
		ft_bzero(wolf->graphics.image_ptr, sizeof(wolf->graphics.image_ptr));
		free(wolf->graphics.image_ptr);
	}
}

int			wolf_failure_exit(t_wolf *wolf, int **map_values,
				char *exit_message)
{
	size_t i;

	close(wolf->fd);
	ft_putendl(exit_message);
	if (map_values)
		free_values((void**)map_values);
	if (wolf->item)
		lst_del(&wolf->item, ft_del);
	i = 0;
	while (wolf->graphics.wall[i] && wolf->graphics.wall[i]->addr_str)
	{
		free(wolf->graphics.wall[i]->addr_str);
		free(wolf->graphics.wall[i]);
		i++;
	}
	mlx_free(wolf);
	ft_bzero(wolf, sizeof(t_wolf));
	exit(EXIT_FAILURE);
	return (-1);
}

int			wolf_success_exit(t_wolf *wolf)
{
	size_t i;
	
	exit(EXIT_SUCCESS);
	close(wolf->fd);
	free_values((void**)wolf->map);
	lst_del(&wolf->item, ft_del);
	i = 0;
	while (i < 15)
	{
		free(wolf->graphics.wall[i]->addr_str);
		free(wolf->graphics.wall[i]);
		i++;
	}
	mlx_free(wolf);
	ft_bzero(wolf, sizeof(t_wolf));
	return (0);
}

