/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2d_vis.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mminkjan <mminkjan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 14:10:44 by mminkjan       #+#    #+#                */
/*   Updated: 2020/02/22 16:40:50 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		put_pixel(t_wolf *wolf, t_point point)
{
	int		index;
	int		color;

	color = 0xffffff;
	if (point.x >= 0 && point.x < WIDTH && point.y >= 0
	&& point.y < HEIGHT)
	{
		index = ((int)point.y * wolf->size_line) + ((int)point.x *
			wolf->bits_ppixel / 8);
		wolf->addr_str2[index] = color;
		index++;
		wolf->addr_str2[index] = color >> 8;
		index++;
		wolf->addr_str2[index] = color >> 16;
	}
}

static void		draw_y_dominant(t_wolf *wolf, t_line *line,
					t_point start, t_point end)
{
	t_point point;

	point = start;
	while (point.y < end.y)
	{
		if (line->error_y <= 0)
			line->error_y += 2 * line->delta_x_abs;
		else
		{
			if ((line->delta_x < 0 && line->delta_y < 0) ||
			(line->delta_x > 0 && line->delta_y > 0))
				point.x++;
			else
				point.x--;
			line->error_y += 2 * (line->delta_x_abs - line->delta_y_abs);
		}
		put_pixel(wolf, point);
		point.y++;
	}
}

static void		draw_x_dominant(t_wolf *wolf, t_line *line,
					t_point start, t_point end)
{
	t_point point;

	point = start;
	while (point.x < end.x)
	{
		if (line->error_x < 0)
			line->error_x += 2 * line->delta_y_abs;
		else
		{
			if ((line->delta_x < 0 && line->delta_y < 0) ||
			(line->delta_x > 0 && line->delta_y > 0))
				point.y++;
			else
				point.y--;
			line->error_x += 2 * (line->delta_y_abs - line->delta_x_abs);
		}
		put_pixel(wolf, point);
		point.x++;
	}
}

static void		set_direction(t_wolf *wolf, t_line *line,
					t_point start, t_point end)
{
	t_point hold;

	if ((line->delta_x < 0 && line->delta_y_abs <= line->delta_x_abs) ||
		(line->delta_y < 0 && line->delta_y_abs > line->delta_x_abs))
	{
		hold = start;
		start = end;
		end = hold;
	}
	if (line->delta_y_abs <= line->delta_x_abs)
		draw_x_dominant(wolf, line, start, end);
	else
		draw_y_dominant(wolf, line, start, end);
}

void			draw_line(t_wolf *wolf, t_point start, t_point end)
{
	t_line line;

	line.delta_x = end.x - start.x;
	line.delta_y = end.y - start.y;
	line.delta_x_abs = abs((int)line.delta_x);
	line.delta_y_abs = abs((int)line.delta_y);
	line.error_x = 2 * line.delta_y_abs - line.delta_x_abs;
	line.error_y = 2 * line.delta_x_abs - line.delta_y_abs;
	set_direction(wolf, &line, start, end);
}

void		draw_ray(t_wolf *wolf, t_point r_start, t_point r_end)
{
	t_point start;
	t_point end;
	
	start.x = (int)r_start.x / 3;
	start.y = (int)r_start.y / 3;
	end.x = (int)r_end.x / 3;
	end.y = (int)r_end.y / 3;
	draw_line(wolf, start, end);
}

void		draw_map(t_wolf *wolf, t_item *item)
{
	t_point start;
	t_point end;

	while (item != NULL)
	{
		start.x = (int)item->start.x / 3;
		start.y = (int)item->start.y / 3;
		end.x = (int)item->end.x / 3;
		end.y = (int)item->end.y / 3;
		draw_line(wolf, start, end);
		item = item->next;
	}
}

int			flat_draw(t_wolf *wolf)
{
	draw_map(wolf, wolf->item);
	return (0);
}