/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlechapt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 15:38:24 by rlechapt          #+#    #+#             */
/*   Updated: 2015/01/19 22:50:26 by rlechapt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vertical(t_env *e, int i)
{
	e->cumul = e->dy / 2;
	i = 1;
	while (i <= e->dy)
	{
		e->y += e->yinc;
		e->cumul += e->dx;
		if (e->cumul >= e->dy)
		{
			e->cumul -= e->dy;
			e->x += e->xinc;
		}
//		mlx_pixel_put(e->mlx, e->win, e->x, e->y, 0xFFFFFF);
		draw_image(e, e->x, e->y);
		i++;
	}

}

void	draw_horizontal(t_env *e, int i)
{
	e->cumul = e->dx / 2;
	i = 1;
	while (i <= e->dx)
	{
		e->x += e->xinc;
		e->cumul += e->dy;
		if (e->cumul >= e->dx)
		{
			e->cumul -= e->dx;
			e->y += e->yinc;
		}
//		mlx_pixel_put(e->mlx, e->win, e->x, e->y, 0xFFFFFF);
		draw_image(e, e->x, e->y);
		i++;
	}
}

void	draw_line(t_env *e, int xi,int yi,int xf,int yf)
{
	int	i;

	e->x = xi;
	e->y = yi;
	e->dx = xf - xi;
	e->dy = yf - yi;
	e->xinc = (e->dx > 0) ? 1 : -1;
	e->yinc = (e->dy > 0) ? 1 : -1;
	if (e->dx < 0)
		e->dx = -e->dx;
	if (e->dy < 0)
		e->dy = -e->dy;
	mlx_pixel_put(e->mlx, e->win, e->x, e->y, 0xFFFFFF);
	if (e->dx > e->dy)
		draw_horizontal(e, i);
	else
		draw_vertical(e, i);
}

void		vertical_projection(t_env *e, int i, int j)
{
	e->x1 = ((e->cste * e->mp[i]->x) - (e->cste * e->mp[i]->y)) + e->moveX;
	e->y1 = ((-e->mp[i]->z + ((e->cste/2) * e->mp[i]->x) +
				((e->cste/2) * e->mp[i]->y))) + e->moveY;
	e->x2 = ((e->cste * e->mp[i]->x) - (e->cste * e->mp[j]->y)) + e->moveX;
	e->y2 = ((-e->mp[j]->z + ((e->cste/2) * e->mp[i]->x) +
				((e->cste/2) * e->mp[j]->y))) + e->moveY;
	draw_line(e, e->x1, e->y1, e->x2, e->y2);
}

void		horizontal_projection(t_env *e, int i, int j)
{
	e->x1 = ((e->cste * e->mp[i]->x) - (e->cste * e->mp[i]->y)) + e->moveX;
	e->y1 = ((-e->mp[i]->z + ((e->cste/2) * e->mp[i]->x) +
				((e->cste/2) * e->mp[i]->y))) + e->moveY;
	e->x2 = ((e->cste * e->mp[j]->x) - (e->cste * e->mp[i]->y)) + e->moveX;
	e->y2 = ((-e->mp[j]->z + ((e->cste/2) * e->mp[j]->x) +
				((e->cste/2) * e->mp[i]->y))) + e->moveY;
	draw_line(e, e->x1, e->y1, e->x2, e->y2);
}
