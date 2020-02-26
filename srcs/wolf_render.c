/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 11:40:53 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/26 13:26:14 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static t_point		calculate_intersect(t_point startA, t_point startB, t_point slopeA, t_point slopeB)
{
	t_point		intersect;
	double 		denominator;
	double		t;
	double		s;

	intersect.x = NAN;
	intersect.y = NAN;
	denominator = (-slopeB.x * slopeA.y + slopeA.x * slopeB.y);
	if (denominator == 0)
		return (intersect);
	s = (-slopeA.y * (startA.x - startB.x) + slopeA.x * (startA.y - startB.y)) / denominator;
	t = ( slopeB.x * (startA.y - startB.y) - slopeB.y * (startA.x - startB.x)) / denominator;
	if (s > 0 && s < 1 && t > 0 && t < 1)
	{
		intersect.x = startA.x + (t * slopeA.x);
		intersect.y = startA.y + (t * slopeA.y);
	}
	return (intersect);
}

static t_point		intersect_point(t_point startA, t_point endA,
						t_point startB, t_point endB)
{
	t_point intersect;
	t_point slopeA;
	t_point slopeB;

	intersect.x = 0;
	intersect.y = 0;
	slopeA.x = endA.x - startA.x;
	slopeA.y = endA.y - startA.y;
	slopeB.x = endB.x - startB.x;
	slopeB.y = endB.y - startB.y;
	return(calculate_intersect(startA, startB, slopeA, slopeB));
}

static t_point		find_intersect(t_wolf *wolf, t_item ray, int prev_height, double angle)
{
	t_point intersect;
	t_point	min_intersect;
	t_item	*object;
	double	distance;
	double	min_distance;

	(void)prev_height;
	object = wolf->item;
	min_distance = INFINITY;
	while (object != NULL)
	{
		intersect = \
			intersect_point(ray.start, ray.end, object->start, object->end);
		if (angle < wolf->dir_angle)
			distance = fabs(ray.start.x - intersect.x) / cos(-angle);
		else
			distance = fabs(ray.start.x - intersect.x) / cos(angle);
		if (distance < min_distance)
		{
			min_distance = distance;
			min_intersect.x = intersect.x;
			min_intersect.y = intersect.y;
			min_intersect.obj_dist = distance;
			min_intersect.texture = object->texture;
			draw_ray(wolf, ray.start, intersect, 0xfc03ad);// red
		}
		object = object->next;
	}
	return (min_intersect);
}

static double		clerp_angle(double angle)
{
	if (angle > 360 * (PI / 180))
		angle -= 360 * (PI / 180);
	else if (angle < 0)
		angle += 360 * (PI / 180);
	return (angle);
}

static void			render_wolf(t_wolf *wolf)
{
	double		ray_angle;
	double		angle;
	t_item		ray;
	t_point		intersect;
	t_height	plane_project;
	int			x;
	double		height;

	x = 0;
	ray_angle = FOV / WIDTH;
	angle = wolf->dir_angle - (FOV / 2);
	while (x < WIDTH)
	{
		angle = clerp_angle(angle);
		ray.start.x = wolf->pos.x;
		ray.start.y = wolf->pos.y;
		ray.end.x = ray.start.x + wolf->max_ray * cos(angle);
		ray.end.y = ray.start.y + wolf->max_ray * sin(angle);
		angle += ray_angle;
		intersect = find_intersect(wolf, ray, wolf->height, angle);
		// if (angle < wolf->dir_angle)
		// 	intersect.obj_dist *= cos(-angle);
		// else
		// 	intersect.obj_dist *= cos(-angle);
		height = wolf->wall_height / intersect.obj_dist * 255;
		plane_project.y_start = wolf->wall_height / 2 - height / 2;
		plane_project.y_end = wolf->wall_height / 2 + height / 2;
		draw_column(wolf, plane_project, x);
		x++;
	}
}

int				wolf_render(t_wolf *wolf)
{
	render_wolf(wolf);
	mlx_key(wolf);
	mlx_mouse(wolf);
	flat_draw(wolf);
	mlx_put_image_to_window(wolf->mlx_ptr,
		wolf->win_ptr, wolf->image_ptr, 0, 0);
	ft_bzero(wolf->addr_str, (wolf->bits_ppixel / 8) * HEIGHT * WIDTH);
	return (0);
}
