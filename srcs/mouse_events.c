/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 17:15:28 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/26 12:55:38 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int	mouse_move(int x, int y, t_wolf *wolf)
{
	double radian;

	radian = PI / 180;
	y = 0;
	if (wolf->event.mouse_press == 1)
	{
		if (x > wolf->event.hold_x)
		{
			wolf->dir_angle += 2 * radian;
			if (wolf->dir_angle > 360 * radian)
				wolf->dir_angle -= 360 * radian;
		}
		else if (x < wolf->event.hold_x)
		{
			wolf->dir_angle -= 2 * radian;
			if (wolf->dir_angle < 0)
				wolf->dir_angle += 360 * radian;
		}
	}
	wolf->event.hold_x = x;
	printf("%f\n", wolf->dir_angle);
	return (0);
}

static int	mouse_release(int key, int x, int y, t_wolf *wolf)
{
	x = 0;
	y = 0;
	if (key == MOUSE_PRESS)
		wolf->event.mouse_press = 0;
	return (0);
}

static int	mouse_press(int key, int x, int y, t_wolf *wolf)
{
	if (key == MOUSE_PRESS)
	{
		wolf->event.mouse_press = 1;
		wolf->event.hold_x = x;
		wolf->event.hold_y = y;
	}
	return (0);
}

void		mlx_mouse(t_wolf *wolf)
{
	mlx_hook(wolf->win_ptr, 4, 0, mouse_press, wolf);
	mlx_hook(wolf->win_ptr, 6, 0, mouse_move, wolf);
	mlx_hook(wolf->win_ptr, 5, 0, mouse_release, wolf);
}
